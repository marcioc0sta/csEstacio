from django.contrib import admin
from .models import Feedback, MonitorReport


@admin.register(Feedback)
class FeedbackAdmin(admin.ModelAdmin):
    list_display = ['student', 'monitor', 'session', 'rating_overall', 'was_helpful', 'created_at']
    list_filter = ['rating_overall', 'was_helpful', 'would_recommend', 'is_anonymous']
    search_fields = ['student__first_name', 'student__last_name', 'monitor__first_name', 'monitor__last_name', 'comment']
    ordering = ['-created_at']
    readonly_fields = ['created_at', 'updated_at']


@admin.register(MonitorReport)
class MonitorReportAdmin(admin.ModelAdmin):
    list_display = ['monitor', 'period_start', 'period_end', 'total_sessions', 'average_rating', 'created_at']
    list_filter = ['period_start', 'period_end']
    search_fields = ['monitor__first_name', 'monitor__last_name']
    ordering = ['-created_at']

