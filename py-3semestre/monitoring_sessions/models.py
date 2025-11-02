from django.db import models
from django.conf import settings
from django.core.validators import MinValueValidator, MaxValueValidator


class Subject(models.Model):
    """Subject/Discipline model"""
    name = models.CharField(max_length=200, verbose_name='Nome')
    code = models.CharField(max_length=20, unique=True, verbose_name='Código')
    description = models.TextField(blank=True, verbose_name='Descrição')
    created_at = models.DateTimeField(auto_now_add=True)
    
    class Meta:
        verbose_name = 'Disciplina'
        verbose_name_plural = 'Disciplinas'
        ordering = ['name']
    
    def __str__(self):
        return f"{self.code} - {self.name}"


class MonitoringSession(models.Model):
    """Monitoring session model"""
    
    STATUS_CHOICES = [
        ('scheduled', 'Agendada'),
        ('in_progress', 'Em andamento'),
        ('completed', 'Concluída'),
        ('cancelled', 'Cancelada'),
    ]
    
    WEEKDAY_CHOICES = [
        (0, 'Segunda-feira'),
        (1, 'Terça-feira'),
        (2, 'Quarta-feira'),
        (3, 'Quinta-feira'),
        (4, 'Sexta-feira'),
        (5, 'Sábado'),
        (6, 'Domingo'),
    ]
    
    monitor = models.ForeignKey(
        settings.AUTH_USER_MODEL,
        on_delete=models.CASCADE,
        related_name='monitoring_sessions',
        verbose_name='Monitor'
    )
    subject = models.ForeignKey(
        Subject,
        on_delete=models.CASCADE,
        related_name='sessions',
        verbose_name='Disciplina'
    )
    title = models.CharField(max_length=200, verbose_name='Título')
    description = models.TextField(verbose_name='Descrição')
    location = models.CharField(max_length=200, verbose_name='Local')
    weekday = models.IntegerField(choices=WEEKDAY_CHOICES, verbose_name='Dia da Semana')
    start_time = models.TimeField(verbose_name='Horário de Início')
    end_time = models.TimeField(verbose_name='Horário de Término')
    max_students = models.IntegerField(
        default=10,
        validators=[MinValueValidator(1), MaxValueValidator(50)],
        verbose_name='Máximo de Alunos'
    )
    status = models.CharField(
        max_length=20,
        choices=STATUS_CHOICES,
        default='scheduled',
        verbose_name='Status'
    )
    is_active = models.BooleanField(default=True, verbose_name='Ativo')
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)
    
    class Meta:
        verbose_name = 'Sessão de Monitoria'
        verbose_name_plural = 'Sessões de Monitoria'
        ordering = ['weekday', 'start_time']
    
    def __str__(self):
        return f"{self.title} - {self.monitor.get_full_name()} ({self.get_weekday_display()})"
    
    def get_time_range(self):
        return f"{self.start_time.strftime('%H:%M')} - {self.end_time.strftime('%H:%M')}"


class Attendance(models.Model):
    """Attendance record for monitoring sessions"""
    
    session = models.ForeignKey(
        MonitoringSession,
        on_delete=models.CASCADE,
        related_name='attendances',
        verbose_name='Sessão'
    )
    student = models.ForeignKey(
        settings.AUTH_USER_MODEL,
        on_delete=models.CASCADE,
        related_name='attendances',
        verbose_name='Aluno'
    )
    date = models.DateField(verbose_name='Data')
    present = models.BooleanField(default=False, verbose_name='Presente')
    notes = models.TextField(blank=True, verbose_name='Observações')
    created_at = models.DateTimeField(auto_now_add=True)
    
    class Meta:
        verbose_name = 'Presença'
        verbose_name_plural = 'Presenças'
        ordering = ['-date']
        unique_together = ['session', 'student', 'date']
    
    def __str__(self):
        return f"{self.student.get_full_name()} - {self.session.title} ({self.date})"

