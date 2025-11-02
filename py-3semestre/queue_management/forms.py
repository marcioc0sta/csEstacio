from django import forms
from .models import QueueEntry


class QueueEntryForm(forms.ModelForm):
    """Form for joining a queue"""
    
    class Meta:
        model = QueueEntry
        fields = ['topic', 'description', 'priority']
        widgets = {
            'topic': forms.TextInput(attrs={
                'class': 'form-control',
                'placeholder': 'Ex: Dúvida sobre ponteiros em C'
            }),
            'description': forms.Textarea(attrs={
                'class': 'form-control',
                'rows': 4,
                'placeholder': 'Descreva sua dúvida com detalhes...'
            }),
            'priority': forms.Select(attrs={'class': 'form-control'}),
        }

