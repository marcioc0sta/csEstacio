from django.contrib import admin
from .models import QueueEntry


@admin.register(QueueEntry)
class QueueEntryAdmin(admin.ModelAdmin):
    list_display = ['student', 'session', 'topic', 'priority', 'status', 'position', 'created_at']
    list_filter = ['status', 'priority', 'session']
    search_fields = ['student__first_name', 'student__last_name', 'topic', 'session__title']
    ordering = ['-created_at']
    readonly_fields = ['created_at', 'started_at', 'completed_at']

