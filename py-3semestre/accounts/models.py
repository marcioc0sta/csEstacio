from django.contrib.auth.models import AbstractUser
from django.db import models


class CustomUser(AbstractUser):
    """Custom user model with role-based access"""
    
    ROLE_CHOICES = [
        ('student', 'Aluno'),
        ('monitor', 'Monitor'),
        ('admin', 'Administrador'),
    ]
    
    role = models.CharField(max_length=10, choices=ROLE_CHOICES, default='student')
    phone = models.CharField(max_length=20, blank=True)
    registration_number = models.CharField(max_length=20, unique=True, null=True, blank=True)
    course = models.CharField(max_length=100, blank=True)
    semester = models.IntegerField(null=True, blank=True)
    bio = models.TextField(blank=True)
    profile_picture = models.ImageField(upload_to='profiles/', blank=True, null=True)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)
    
    class Meta:
        verbose_name = 'Usuário'
        verbose_name_plural = 'Usuários'
        ordering = ['-created_at']
    
    def __str__(self):
        return f"{self.get_full_name()} ({self.get_role_display()})"
    
    def is_student(self):
        return self.role == 'student'
    
    def is_monitor(self):
        return self.role == 'monitor'
    
    def is_admin_user(self):
        return self.role == 'admin'

