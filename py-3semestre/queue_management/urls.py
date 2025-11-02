from django.urls import path
from . import views

app_name = 'queue_management'

urlpatterns = [
    path('join/<int:session_id>/', views.join_queue, name='join'),
    path('my-queue/', views.my_queue, name='my_queue'),
    path('cancel/<int:entry_id>/', views.cancel_queue_entry, name='cancel'),
    path('session/<int:session_id>/', views.session_queue, name='session_queue'),
    path('start/<int:entry_id>/', views.start_service, name='start_service'),
    path('complete/<int:entry_id>/', views.complete_service, name='complete_service'),
    path('api/status/<int:session_id>/', views.queue_status_api, name='status_api'),
]

