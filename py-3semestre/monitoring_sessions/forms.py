from django import forms
from .models import MonitoringSession, Subject, Attendance


class MonitoringSessionForm(forms.ModelForm):
    """Form for creating and editing monitoring sessions"""
    
    class Meta:
        model = MonitoringSession
        fields = ['subject', 'title', 'description', 'location', 'weekday', 
                  'start_time', 'end_time', 'max_students', 'status', 'is_active']
        widgets = {
            'subject': forms.Select(attrs={'class': 'form-control'}),
            'title': forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'Título da sessão'}),
            'description': forms.Textarea(attrs={'class': 'form-control', 'rows': 4, 'placeholder': 'Descrição da sessão'}),
            'location': forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'Local da monitoria'}),
            'weekday': forms.Select(attrs={'class': 'form-control'}),
            'start_time': forms.TimeInput(attrs={'class': 'form-control', 'type': 'time'}),
            'end_time': forms.TimeInput(attrs={'class': 'form-control', 'type': 'time'}),
            'max_students': forms.NumberInput(attrs={'class': 'form-control'}),
            'status': forms.Select(attrs={'class': 'form-control'}),
            'is_active': forms.CheckboxInput(attrs={'class': 'form-check-input'}),
        }


class SubjectForm(forms.ModelForm):
    """Form for creating and editing subjects"""
    
    class Meta:
        model = Subject
        fields = ['name', 'code', 'description']
        widgets = {
            'name': forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'Nome da disciplina'}),
            'code': forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'Código da disciplina'}),
            'description': forms.Textarea(attrs={'class': 'form-control', 'rows': 3, 'placeholder': 'Descrição'}),
        }


class AttendanceForm(forms.ModelForm):
    """Form for recording attendance"""
    
    class Meta:
        model = Attendance
        fields = ['date', 'present', 'notes']
        widgets = {
            'date': forms.DateInput(attrs={'class': 'form-control', 'type': 'date'}),
            'present': forms.CheckboxInput(attrs={'class': 'form-check-input'}),
            'notes': forms.Textarea(attrs={'class': 'form-control', 'rows': 3}),
        }


class SessionSearchForm(forms.Form):
    """Form for searching sessions"""
    
    subject = forms.ModelChoiceField(
        queryset=Subject.objects.all(),
        required=False,
        empty_label="Todas as disciplinas",
        widget=forms.Select(attrs={'class': 'form-control'})
    )
    monitor = forms.CharField(
        required=False,
        widget=forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'Nome do monitor'})
    )
    weekday = forms.ChoiceField(
        choices=[('', 'Todos os dias')] + list(MonitoringSession.WEEKDAY_CHOICES),
        required=False,
        widget=forms.Select(attrs={'class': 'form-control'})
    )
    status = forms.ChoiceField(
        choices=[('', 'Todos os status')] + list(MonitoringSession.STATUS_CHOICES),
        required=False,
        widget=forms.Select(attrs={'class': 'form-control'})
    )

