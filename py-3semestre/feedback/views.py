from django.shortcuts import render, redirect, get_object_or_404
from django.contrib.auth.decorators import login_required
from django.contrib import messages
from django.db.models import Avg, Count
from queue_management.models import QueueEntry
from monitoring_sessions.models import MonitoringSession
from accounts.models import CustomUser
from .models import Feedback, MonitorReport
from .forms import FeedbackForm


@login_required
def submit_feedback(request, entry_id):
    """Submit feedback for a completed queue entry"""
    entry = get_object_or_404(QueueEntry, pk=entry_id)
    
    if entry.student != request.user:
        messages.error(request, 'Você não tem permissão para avaliar esta entrada.')
        return redirect('queue_management:my_queue')
    
    if entry.status != 'completed':
        messages.warning(request, 'Você só pode avaliar atendimentos concluídos.')
        return redirect('queue_management:my_queue')
    
    # Check if feedback already exists
    if hasattr(entry, 'feedback'):
        messages.info(request, 'Você já avaliou este atendimento.')
        return redirect('queue_management:my_queue')
    
    if request.method == 'POST':
        form = FeedbackForm(request.POST)
        if form.is_valid():
            feedback = form.save(commit=False)
            feedback.queue_entry = entry
            feedback.session = entry.session
            feedback.student = request.user
            feedback.monitor = entry.session.monitor
            feedback.save()
            messages.success(request, 'Avaliação enviada com sucesso!')
            return redirect('queue_management:my_queue')
    else:
        form = FeedbackForm()
    
    context = {
        'form': form,
        'entry': entry,
    }
    return render(request, 'feedback/submit_feedback.html', context)


@login_required
def my_feedbacks(request):
    """View feedbacks received (monitors) or given (students)"""
    if request.user.is_monitor():
        feedbacks = Feedback.objects.filter(monitor=request.user).select_related('student', 'session')
        
        # Calculate statistics
        stats = feedbacks.aggregate(
            avg_overall=Avg('rating_overall'),
            avg_knowledge=Avg('rating_knowledge'),
            avg_communication=Avg('rating_communication'),
            avg_patience=Avg('rating_patience'),
            total_feedbacks=Count('id')
        )
        
        context = {
            'feedbacks': feedbacks,
            'stats': stats,
            'is_monitor': True,
        }
    else:
        feedbacks = Feedback.objects.filter(student=request.user).select_related('monitor', 'session')
        context = {
            'feedbacks': feedbacks,
            'is_monitor': False,
        }
    
    return render(request, 'feedback/my_feedbacks.html', context)


def monitor_profile(request, monitor_id):
    """View monitor profile with ratings and feedbacks"""
    monitor = get_object_or_404(CustomUser, pk=monitor_id, role='monitor')
    
    feedbacks = Feedback.objects.filter(monitor=monitor).order_by('-created_at')[:10]
    
    stats = Feedback.objects.filter(monitor=monitor).aggregate(
        avg_overall=Avg('rating_overall'),
        avg_knowledge=Avg('rating_knowledge'),
        avg_communication=Avg('rating_communication'),
        avg_patience=Avg('rating_patience'),
        total_feedbacks=Count('id')
    )
    
    sessions = MonitoringSession.objects.filter(monitor=monitor, is_active=True)
    
    context = {
        'monitor': monitor,
        'feedbacks': feedbacks,
        'stats': stats,
        'sessions': sessions,
    }
    return render(request, 'feedback/monitor_profile.html', context)


@login_required
def monitor_stats(request):
    """Detailed statistics for monitors"""
    if not request.user.is_monitor():
        messages.error(request, 'Apenas monitores podem acessar esta página.')
        return redirect('home')
    
    # Get all feedbacks for this monitor
    feedbacks = Feedback.objects.filter(monitor=request.user)
    
    # Overall statistics
    overall_stats = feedbacks.aggregate(
        avg_overall=Avg('rating_overall'),
        avg_knowledge=Avg('rating_knowledge'),
        avg_communication=Avg('rating_communication'),
        avg_patience=Avg('rating_patience'),
        total_feedbacks=Count('id')
    )
    
    # Session statistics
    sessions = MonitoringSession.objects.filter(monitor=request.user)
    total_sessions = sessions.count()
    
    # Queue statistics
    from queue_management.models import QueueEntry
    queue_entries = QueueEntry.objects.filter(session__monitor=request.user, status='completed')
    total_students_served = queue_entries.count()
    avg_wait_time = sum([e.get_wait_time() or 0 for e in queue_entries]) / max(total_students_served, 1)
    
    context = {
        'overall_stats': overall_stats,
        'total_sessions': total_sessions,
        'total_students_served': total_students_served,
        'avg_wait_time': round(avg_wait_time, 1),
        'recent_feedbacks': feedbacks.order_by('-created_at')[:5],
    }
    
    return render(request, 'feedback/monitor_stats.html', context)


def monitors_ranking(request):
    """Ranking of monitors by rating"""
    monitors = CustomUser.objects.filter(role='monitor')
    
    monitor_stats = []
    for monitor in monitors:
        stats = Feedback.objects.filter(monitor=monitor).aggregate(
            avg_rating=Avg('rating_overall'),
            total_feedbacks=Count('id')
        )
        if stats['total_feedbacks'] and stats['total_feedbacks'] > 0:
            monitor_stats.append({
                'monitor': monitor,
                'avg_rating': round(stats['avg_rating'], 2) if stats['avg_rating'] else 0,
                'total_feedbacks': stats['total_feedbacks'],
            })
    
    # Sort by average rating
    monitor_stats.sort(key=lambda x: x['avg_rating'], reverse=True)
    
    context = {
        'monitor_stats': monitor_stats,
    }
    return render(request, 'feedback/monitors_ranking.html', context)

