from django.urls import path
from . import views

app_name = 'feedback'

urlpatterns = [
    path('submit/<int:entry_id>/', views.submit_feedback, name='submit'),
    path('my-feedbacks/', views.my_feedbacks, name='my_feedbacks'),
    path('monitor/<int:monitor_id>/', views.monitor_profile, name='monitor_profile'),
    path('stats/', views.monitor_stats, name='monitor_stats'),
    path('ranking/', views.monitors_ranking, name='monitors_ranking'),
]

