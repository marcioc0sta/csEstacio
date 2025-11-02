from django.urls import path
from . import views

app_name = 'monitoring_sessions'

urlpatterns = [
    # Session URLs
    path('', views.session_list, name='list'),
    path('<int:pk>/', views.session_detail, name='detail'),
    path('create/', views.session_create, name='create'),
    path('<int:pk>/update/', views.session_update, name='update'),
    path('<int:pk>/delete/', views.session_delete, name='delete'),
    path('my-sessions/', views.my_sessions, name='my_sessions'),
    
    # Subject URLs
    path('subjects/', views.subject_list, name='subject_list'),
    path('subjects/create/', views.subject_create, name='subject_create'),
]

