from django.db import models
from django.conf import settings
from django.core.validators import MinValueValidator, MaxValueValidator
from monitoring_sessions.models import MonitoringSession
from queue_management.models import QueueEntry


class Feedback(models.Model):
    """Feedback and rating for monitoring sessions"""
    
    session = models.ForeignKey(
        MonitoringSession,
        on_delete=models.CASCADE,
        related_name='feedbacks',
        verbose_name='Sessão'
    )
    queue_entry = models.OneToOneField(
        QueueEntry,
        on_delete=models.CASCADE,
        related_name='feedback',
        null=True,
        blank=True,
        verbose_name='Entrada na Fila'
    )
    student = models.ForeignKey(
        settings.AUTH_USER_MODEL,
        on_delete=models.CASCADE,
        related_name='feedbacks_given',
        verbose_name='Aluno'
    )
    monitor = models.ForeignKey(
        settings.AUTH_USER_MODEL,
        on_delete=models.CASCADE,
        related_name='feedbacks_received',
        verbose_name='Monitor'
    )
    
    # Ratings (1-5 scale)
    rating_overall = models.IntegerField(
        validators=[MinValueValidator(1), MaxValueValidator(5)],
        verbose_name='Avaliação Geral'
    )
    rating_knowledge = models.IntegerField(
        validators=[MinValueValidator(1), MaxValueValidator(5)],
        verbose_name='Conhecimento do Monitor'
    )
    rating_communication = models.IntegerField(
        validators=[MinValueValidator(1), MaxValueValidator(5)],
        verbose_name='Comunicação'
    )
    rating_patience = models.IntegerField(
        validators=[MinValueValidator(1), MaxValueValidator(5)],
        verbose_name='Paciência'
    )
    
    # Feedback text
    comment = models.TextField(verbose_name='Comentário', blank=True)
    was_helpful = models.BooleanField(default=True, verbose_name='Foi útil?')
    would_recommend = models.BooleanField(default=True, verbose_name='Recomendaria?')
    
    # Metadata
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)
    is_anonymous = models.BooleanField(default=False, verbose_name='Anônimo')
    
    class Meta:
        verbose_name = 'Avaliação'
        verbose_name_plural = 'Avaliações'
        ordering = ['-created_at']
    
    def __str__(self):
        student_name = "Anônimo" if self.is_anonymous else self.student.get_full_name()
        return f"Avaliação de {student_name} para {self.monitor.get_full_name()} ({self.rating_overall}/5)"
    
    def get_average_rating(self):
        """Calculate average of all ratings"""
        return (self.rating_overall + self.rating_knowledge + 
                self.rating_communication + self.rating_patience) / 4


class MonitorReport(models.Model):
    """Statistical report for monitors"""
    
    monitor = models.ForeignKey(
        settings.AUTH_USER_MODEL,
        on_delete=models.CASCADE,
        related_name='reports',
        verbose_name='Monitor'
    )
    period_start = models.DateField(verbose_name='Início do Período')
    period_end = models.DateField(verbose_name='Fim do Período')
    
    # Statistics
    total_sessions = models.IntegerField(default=0, verbose_name='Total de Sessões')
    total_students = models.IntegerField(default=0, verbose_name='Total de Alunos')
    average_rating = models.FloatField(default=0.0, verbose_name='Avaliação Média')
    total_feedbacks = models.IntegerField(default=0, verbose_name='Total de Avaliações')
    
    created_at = models.DateTimeField(auto_now_add=True)
    
    class Meta:
        verbose_name = 'Relatório de Monitor'
        verbose_name_plural = 'Relatórios de Monitores'
        ordering = ['-created_at']
    
    def __str__(self):
        return f"Relatório de {self.monitor.get_full_name()} ({self.period_start} - {self.period_end})"

