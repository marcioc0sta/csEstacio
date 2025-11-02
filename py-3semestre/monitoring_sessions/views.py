from django.shortcuts import render, redirect, get_object_or_404
from django.contrib.auth.decorators import login_required
from django.contrib import messages
from django.db.models import Q
from django.core.paginator import Paginator
from .models import MonitoringSession, Subject, Attendance
from .forms import MonitoringSessionForm, SubjectForm, AttendanceForm, SessionSearchForm


def session_list(request):
    """List all monitoring sessions with search/filter"""
    sessions = MonitoringSession.objects.filter(is_active=True).select_related('monitor', 'subject')
    
    form = SessionSearchForm(request.GET)
    if form.is_valid():
        if form.cleaned_data['subject']:
            sessions = sessions.filter(subject=form.cleaned_data['subject'])
        if form.cleaned_data['monitor']:
            monitor_name = form.cleaned_data['monitor']
            sessions = sessions.filter(
                Q(monitor__first_name__icontains=monitor_name) |
                Q(monitor__last_name__icontains=monitor_name)
            )
        if form.cleaned_data['weekday']:
            sessions = sessions.filter(weekday=form.cleaned_data['weekday'])
        if form.cleaned_data['status']:
            sessions = sessions.filter(status=form.cleaned_data['status'])
    
    paginator = Paginator(sessions, 12)
    page_number = request.GET.get('page')
    page_obj = paginator.get_page(page_number)
    
    context = {
        'page_obj': page_obj,
        'form': form,
    }
    return render(request, 'monitoring_sessions/session_list.html', context)


def session_detail(request, pk):
    """View session details"""
    session = get_object_or_404(MonitoringSession, pk=pk)
    return render(request, 'monitoring_sessions/session_detail.html', {'session': session})


@login_required
def session_create(request):
    """Create a new monitoring session (monitors only)"""
    if not request.user.is_monitor() and not request.user.is_admin_user():
        messages.error(request, 'Apenas monitores podem criar sessões.')
        return redirect('monitoring_sessions:list')
    
    if request.method == 'POST':
        form = MonitoringSessionForm(request.POST)
        if form.is_valid():
            session = form.save(commit=False)
            session.monitor = request.user
            session.save()
            messages.success(request, 'Sessão criada com sucesso!')
            return redirect('monitoring_sessions:detail', pk=session.pk)
    else:
        form = MonitoringSessionForm()
    
    return render(request, 'monitoring_sessions/session_form.html', {'form': form, 'action': 'Criar'})


@login_required
def session_update(request, pk):
    """Update a monitoring session"""
    session = get_object_or_404(MonitoringSession, pk=pk)
    
    if session.monitor != request.user and not request.user.is_admin_user():
        messages.error(request, 'Você não tem permissão para editar esta sessão.')
        return redirect('monitoring_sessions:detail', pk=pk)
    
    if request.method == 'POST':
        form = MonitoringSessionForm(request.POST, instance=session)
        if form.is_valid():
            form.save()
            messages.success(request, 'Sessão atualizada com sucesso!')
            return redirect('monitoring_sessions:detail', pk=pk)
    else:
        form = MonitoringSessionForm(instance=session)
    
    return render(request, 'monitoring_sessions/session_form.html', {'form': form, 'action': 'Editar', 'session': session})


@login_required
def session_delete(request, pk):
    """Delete a monitoring session"""
    session = get_object_or_404(MonitoringSession, pk=pk)
    
    if session.monitor != request.user and not request.user.is_admin_user():
        messages.error(request, 'Você não tem permissão para excluir esta sessão.')
        return redirect('monitoring_sessions:detail', pk=pk)
    
    if request.method == 'POST':
        session.delete()
        messages.success(request, 'Sessão excluída com sucesso!')
        return redirect('monitoring_sessions:list')
    
    return render(request, 'monitoring_sessions/session_confirm_delete.html', {'session': session})


@login_required
def my_sessions(request):
    """View monitor's own sessions"""
    if not request.user.is_monitor():
        messages.error(request, 'Apenas monitores podem acessar esta página.')
        return redirect('home')
    
    sessions = MonitoringSession.objects.filter(monitor=request.user)
    return render(request, 'monitoring_sessions/my_sessions.html', {'sessions': sessions})


# Subject views
@login_required
def subject_list(request):
    """List all subjects"""
    subjects = Subject.objects.all()
    return render(request, 'monitoring_sessions/subject_list.html', {'subjects': subjects})


@login_required
def subject_create(request):
    """Create a new subject (admin only)"""
    if not request.user.is_admin_user():
        messages.error(request, 'Apenas administradores podem criar disciplinas.')
        return redirect('monitoring_sessions:subject_list')
    
    if request.method == 'POST':
        form = SubjectForm(request.POST)
        if form.is_valid():
            form.save()
            messages.success(request, 'Disciplina criada com sucesso!')
            return redirect('monitoring_sessions:subject_list')
    else:
        form = SubjectForm()
    
    return render(request, 'monitoring_sessions/subject_form.html', {'form': form, 'action': 'Criar'})

