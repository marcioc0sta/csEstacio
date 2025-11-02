from django.db import models
from django.conf import settings
from monitoring_sessions.models import MonitoringSession


class QueueEntry(models.Model):
    """Queue entry for students waiting for monitoring"""
    
    STATUS_CHOICES = [
        ('waiting', 'Aguardando'),
        ('in_service', 'Em atendimento'),
        ('completed', 'Atendido'),
        ('cancelled', 'Cancelado'),
    ]
    
    PRIORITY_CHOICES = [
        ('low', 'Baixa'),
        ('normal', 'Normal'),
        ('high', 'Alta'),
        ('urgent', 'Urgente'),
    ]
    
    session = models.ForeignKey(
        MonitoringSession,
        on_delete=models.CASCADE,
        related_name='queue_entries',
        verbose_name='Sessão'
    )
    student = models.ForeignKey(
        settings.AUTH_USER_MODEL,
        on_delete=models.CASCADE,
        related_name='queue_entries',
        verbose_name='Aluno'
    )
    topic = models.CharField(max_length=200, verbose_name='Tópico/Dúvida')
    description = models.TextField(verbose_name='Descrição')
    priority = models.CharField(
        max_length=10,
        choices=PRIORITY_CHOICES,
        default='normal',
        verbose_name='Prioridade'
    )
    status = models.CharField(
        max_length=20,
        choices=STATUS_CHOICES,
        default='waiting',
        verbose_name='Status'
    )
    position = models.IntegerField(default=0, verbose_name='Posição na Fila')
    created_at = models.DateTimeField(auto_now_add=True, verbose_name='Entrada na Fila')
    started_at = models.DateTimeField(null=True, blank=True, verbose_name='Início do Atendimento')
    completed_at = models.DateTimeField(null=True, blank=True, verbose_name='Fim do Atendimento')
    
    class Meta:
        verbose_name = 'Entrada na Fila'
        verbose_name_plural = 'Entradas na Fila'
        ordering = ['priority', 'created_at']
    
    def __str__(self):
        return f"{self.student.get_full_name()} - {self.session.title} ({self.get_status_display()})"
    
    def get_wait_time(self):
        """Calculate wait time in minutes"""
        if self.started_at:
            delta = self.started_at - self.created_at
            return int(delta.total_seconds() / 60)
        return None
    
    def get_service_time(self):
        """Calculate service time in minutes"""
        if self.completed_at and self.started_at:
            delta = self.completed_at - self.started_at
            return int(delta.total_seconds() / 60)
        return None
    
    def save(self, *args, **kwargs):
        # Auto-calculate position if new entry
        if not self.pk and self.status == 'waiting':
            last_position = QueueEntry.objects.filter(
                session=self.session,
                status='waiting'
            ).aggregate(models.Max('position'))['position__max']
            self.position = (last_position or 0) + 1
        super().save(*args, **kwargs)

