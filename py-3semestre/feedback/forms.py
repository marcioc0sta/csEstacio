from django import forms
from .models import Feedback


class FeedbackForm(forms.ModelForm):
    """Form for submitting feedback"""
    
    class Meta:
        model = Feedback
        fields = ['rating_overall', 'rating_knowledge', 'rating_communication', 
                  'rating_patience', 'comment', 'was_helpful', 'would_recommend', 'is_anonymous']
        widgets = {
            'rating_overall': forms.Select(
                choices=[(i, f'{i} estrela{"s" if i > 1 else ""}') for i in range(1, 6)],
                attrs={'class': 'form-control'}
            ),
            'rating_knowledge': forms.Select(
                choices=[(i, f'{i} estrela{"s" if i > 1 else ""}') for i in range(1, 6)],
                attrs={'class': 'form-control'}
            ),
            'rating_communication': forms.Select(
                choices=[(i, f'{i} estrela{"s" if i > 1 else ""}') for i in range(1, 6)],
                attrs={'class': 'form-control'}
            ),
            'rating_patience': forms.Select(
                choices=[(i, f'{i} estrela{"s" if i > 1 else ""}') for i in range(1, 6)],
                attrs={'class': 'form-control'}
            ),
            'comment': forms.Textarea(attrs={
                'class': 'form-control',
                'rows': 4,
                'placeholder': 'Deixe seu comentário sobre o atendimento...'
            }),
            'was_helpful': forms.CheckboxInput(attrs={'class': 'form-check-input'}),
            'would_recommend': forms.CheckboxInput(attrs={'class': 'form-check-input'}),
            'is_anonymous': forms.CheckboxInput(attrs={'class': 'form-check-input'}),
        }
        labels = {
            'rating_overall': 'Avaliação Geral',
            'rating_knowledge': 'Conhecimento do Monitor',
            'rating_communication': 'Comunicação',
            'rating_patience': 'Paciência e Didática',
            'comment': 'Comentário',
            'was_helpful': 'Este atendimento foi útil?',
            'would_recommend': 'Você recomendaria este monitor?',
            'is_anonymous': 'Enviar avaliação anônima',
        }

