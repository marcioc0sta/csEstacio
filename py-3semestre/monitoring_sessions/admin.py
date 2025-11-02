from django.contrib import admin
from .models import Subject, MonitoringSession, Attendance


@admin.register(Subject)
class SubjectAdmin(admin.ModelAdmin):
    list_display = ['code', 'name', 'created_at']
    search_fields = ['name', 'code']
    ordering = ['name']


@admin.register(MonitoringSession)
class MonitoringSessionAdmin(admin.ModelAdmin):
    list_display = ['title', 'monitor', 'subject', 'weekday', 'start_time', 'status', 'is_active']
    list_filter = ['status', 'is_active', 'weekday', 'subject']
    search_fields = ['title', 'monitor__first_name', 'monitor__last_name', 'subject__name']
    ordering = ['-created_at']


@admin.register(Attendance)
class AttendanceAdmin(admin.ModelAdmin):
    list_display = ['student', 'session', 'date', 'present']
    list_filter = ['present', 'date']
    search_fields = ['student__first_name', 'student__last_name', 'session__title']
    ordering = ['-date']

