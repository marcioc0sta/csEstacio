from django.shortcuts import render, redirect, get_object_or_404
from django.contrib.auth.decorators import login_required
from django.contrib import messages
from django.utils import timezone
from django.http import JsonResponse
from monitoring_sessions.models import MonitoringSession
from .models import QueueEntry
from .forms import QueueEntryForm


@login_required
def join_queue(request, session_id):
    """Student joins a queue"""
    if not request.user.is_student():
        messages.error(request, 'Apenas alunos podem entrar na fila.')
        return redirect('monitoring_sessions:detail', pk=session_id)
    
    session = get_object_or_404(MonitoringSession, pk=session_id)
    
    # Check if student is already in queue for this session
    existing_entry = QueueEntry.objects.filter(
        session=session,
        student=request.user,
        status__in=['waiting', 'in_service']
    ).first()
    
    if existing_entry:
        messages.warning(request, 'Você já está na fila desta sessão.')
        return redirect('queue:my_queue')
    
    if request.method == 'POST':
        form = QueueEntryForm(request.POST)
        if form.is_valid():
            entry = form.save(commit=False)
            entry.session = session
            entry.student = request.user
            entry.save()
            messages.success(request, f'Você entrou na fila! Posição: {entry.position}')
            return redirect('queue_management:my_queue')
    else:
        form = QueueEntryForm()
    
    context = {
        'form': form,
        'session': session,
    }
    return render(request, 'queue_management/join_queue.html', context)


@login_required
def my_queue(request):
    """View student's queue entries"""
    if not request.user.is_student():
        messages.error(request, 'Apenas alunos podem acessar esta página.')
        return redirect('home')
    
    entries = QueueEntry.objects.filter(student=request.user).select_related('session').order_by('-created_at')
    
    context = {
        'entries': entries,
    }
    return render(request, 'queue_management/my_queue.html', context)


@login_required
def cancel_queue_entry(request, entry_id):
    """Cancel a queue entry"""
    entry = get_object_or_404(QueueEntry, pk=entry_id)
    
    if entry.student != request.user:
        messages.error(request, 'Você não tem permissão para cancelar esta entrada.')
        return redirect('queue:my_queue')
    
    if entry.status not in ['waiting', 'in_service']:
        messages.warning(request, 'Esta entrada já foi finalizada.')
        return redirect('queue:my_queue')
    
    entry.status = 'cancelled'
    entry.save()
    
    # Reorder remaining queue entries
    remaining_entries = QueueEntry.objects.filter(
        session=entry.session,
        status='waiting',
        position__gt=entry.position
    ).order_by('position')
    
    for i, remaining_entry in enumerate(remaining_entries, start=entry.position):
        remaining_entry.position = i
        remaining_entry.save()
    
    messages.success(request, 'Entrada na fila cancelada.')
    return redirect('queue:my_queue')


@login_required
def session_queue(request, session_id):
    """View queue for a specific session (monitor/admin)"""
    session = get_object_or_404(MonitoringSession, pk=session_id)
    
    if not (request.user.is_monitor() or request.user.is_admin_user()):
        messages.error(request, 'Apenas monitores podem acessar esta página.')
        return redirect('sessions:detail', pk=session_id)
    
    if session.monitor != request.user and not request.user.is_admin_user():
        messages.error(request, 'Você não é o monitor desta sessão.')
        return redirect('sessions:detail', pk=session_id)
    
    waiting_entries = QueueEntry.objects.filter(
        session=session,
        status='waiting'
    ).select_related('student').order_by('position')
    
    in_service_entries = QueueEntry.objects.filter(
        session=session,
        status='in_service'
    ).select_related('student')
    
    completed_entries = QueueEntry.objects.filter(
        session=session,
        status='completed'
    ).select_related('student').order_by('-completed_at')[:10]
    
    context = {
        'session': session,
        'waiting_entries': waiting_entries,
        'in_service_entries': in_service_entries,
        'completed_entries': completed_entries,
    }
    return render(request, 'queue_management/session_queue.html', context)


@login_required
def start_service(request, entry_id):
    """Monitor starts service for a queue entry"""
    entry = get_object_or_404(QueueEntry, pk=entry_id)
    
    if entry.session.monitor != request.user and not request.user.is_admin_user():
        messages.error(request, 'Você não tem permissão para atender esta entrada.')
        return redirect('queue_management:session_queue', session_id=entry.session.id)
    
    if entry.status != 'waiting':
        messages.warning(request, 'Esta entrada não está aguardando.')
        return redirect('queue_management:session_queue', session_id=entry.session.id)
    
    entry.status = 'in_service'
    entry.started_at = timezone.now()
    entry.save()
    
    messages.success(request, f'Atendimento iniciado para {entry.student.get_full_name()}')
    return redirect('queue_management:session_queue', session_id=entry.session.id)


@login_required
def complete_service(request, entry_id):
    """Monitor completes service for a queue entry"""
    entry = get_object_or_404(QueueEntry, pk=entry_id)
    
    if entry.session.monitor != request.user and not request.user.is_admin_user():
        messages.error(request, 'Você não tem permissão para finalizar esta entrada.')
        return redirect('queue_management:session_queue', session_id=entry.session.id)
    
    if entry.status != 'in_service':
        messages.warning(request, 'Esta entrada não está em atendimento.')
        return redirect('queue_management:session_queue', session_id=entry.session.id)
    
    entry.status = 'completed'
    entry.completed_at = timezone.now()
    entry.save()
    
    messages.success(request, f'Atendimento finalizado para {entry.student.get_full_name()}')
    return redirect('queue_management:session_queue', session_id=entry.session.id)


@login_required
def queue_status_api(request, session_id):
    """API endpoint for real-time queue status"""
    session = get_object_or_404(MonitoringSession, pk=session_id)
    
    waiting_entries = QueueEntry.objects.filter(
        session=session,
        status='waiting'
    ).select_related('student').order_by('position')
    
    data = {
        'total_waiting': waiting_entries.count(),
        'entries': [
            {
                'id': entry.id,
                'student': entry.student.get_full_name(),
                'topic': entry.topic,
                'position': entry.position,
                'priority': entry.get_priority_display(),
            }
            for entry in waiting_entries
        ]
    }
    
    return JsonResponse(data)

