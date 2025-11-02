from django.shortcuts import render, redirect
from django.contrib.auth import login, logout, authenticate
from django.contrib.auth.decorators import login_required
from django.contrib import messages
from django.views.generic import CreateView, UpdateView, DetailView
from django.urls import reverse_lazy
from django.contrib.auth.mixins import LoginRequiredMixin
from .forms import CustomUserCreationForm, CustomAuthenticationForm, UserProfileForm
from .models import CustomUser


def register_view(request):
    """User registration view"""
    if request.method == 'POST':
        form = CustomUserCreationForm(request.POST)
        if form.is_valid():
            user = form.save()
            login(request, user)
            messages.success(request, 'Conta criada com sucesso!')
            return redirect('home')
    else:
        form = CustomUserCreationForm()
    return render(request, 'accounts/register.html', {'form': form})


def login_view(request):
    """User login view"""
    if request.method == 'POST':
        form = CustomAuthenticationForm(request, data=request.POST)
        if form.is_valid():
            username = form.cleaned_data.get('username')
            password = form.cleaned_data.get('password')
            user = authenticate(username=username, password=password)
            if user is not None:
                login(request, user)
                messages.success(request, f'Bem-vindo, {user.first_name}!')
                return redirect('home')
    else:
        form = CustomAuthenticationForm()
    return render(request, 'accounts/login.html', {'form': form})


@login_required
def logout_view(request):
    """User logout view"""
    logout(request)
    messages.info(request, 'Você saiu da sua conta.')
    return redirect('home')


@login_required
def profile_view(request, username):
    """View user profile"""
    user = CustomUser.objects.get(username=username)
    return render(request, 'accounts/profile.html', {'profile_user': user})


@login_required
def profile_edit_view(request):
    """Edit user profile"""
    if request.method == 'POST':
        form = UserProfileForm(request.POST, request.FILES, instance=request.user)
        if form.is_valid():
            form.save()
            messages.success(request, 'Perfil atualizado com sucesso!')
            return redirect('accounts:profile', username=request.user.username)
    else:
        form = UserProfileForm(instance=request.user)
    return render(request, 'accounts/profile_edit.html', {'form': form})


@login_required
def dashboard_view(request):
    """Dashboard view based on user role"""
    context = {
        'user': request.user,
    }
    
    if request.user.is_monitor():
        # Monitor dashboard
        from monitoring_sessions.models import MonitoringSession
        context['my_sessions'] = MonitoringSession.objects.filter(monitor=request.user)
        return render(request, 'accounts/dashboard_monitor.html', context)
    elif request.user.is_student():
        # Student dashboard
        from queue_management.models import QueueEntry
        context['my_queue_entries'] = QueueEntry.objects.filter(student=request.user).order_by('-created_at')[:5]
        return render(request, 'accounts/dashboard_student.html', context)
    else:
        # Admin dashboard
        context['total_users'] = CustomUser.objects.count()
        context['total_students'] = CustomUser.objects.filter(role='student').count()
        context['total_monitors'] = CustomUser.objects.filter(role='monitor').count()
        return render(request, 'accounts/dashboard_admin.html', context)

