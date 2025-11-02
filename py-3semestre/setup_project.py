#!/usr/bin/env python
"""
Script to initialize the project with test data
Run with: python setup_project.py
"""

import os
import django

# Setup Django
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'monitoria_system.settings')
django.setup()

from django.contrib.auth import get_user_model
from monitoring_sessions.models import Subject, MonitoringSession
from datetime import time

User = get_user_model()

def create_users():
    """Create test users"""
    print("Creating users...")
    
    # Admin
    if not User.objects.filter(username='admin').exists():
        admin = User.objects.create_superuser(
            username='admin',
            email='admin@monitoria.com',
            password='admin123',
            first_name='Admin',
            last_name='Sistema',
            role='admin'
        )
        print(f"✓ Admin created: admin / admin123")
    
    # Monitors
    monitors_data = [
        {
            'username': 'monitor1',
            'email': 'joao.silva@monitoria.com',
            'password': 'monitor123',
            'first_name': 'João',
            'last_name': 'Silva',
            'registration_number': 'M001',
            'course': 'Ciência da Computação',
            'semester': 6,
            'bio': 'Monitor de Estruturas de Dados com 2 anos de experiência.'
        },
        {
            'username': 'monitor2',
            'email': 'ana.santos@monitoria.com',
            'password': 'monitor123',
            'first_name': 'Ana',
            'last_name': 'Santos',
            'registration_number': 'M002',
            'course': 'Sistemas de Informação',
            'semester': 7,
            'bio': 'Apaixonada por banco de dados e SQL.'
        },
        {
            'username': 'monitor3',
            'email': 'carlos.lima@monitoria.com',
            'password': 'monitor123',
            'first_name': 'Carlos',
            'last_name': 'Lima',
            'registration_number': 'M003',
            'course': 'Engenharia de Software',
            'semester': 8,
            'bio': 'Especialista em algoritmos e programação.'
        },
    ]
    
    for data in monitors_data:
        if not User.objects.filter(username=data['username']).exists():
            User.objects.create_user(**data, role='monitor')
            print(f"✓ Monitor created: {data['username']} / monitor123")
    
    # Students
    students_data = [
        {
            'username': 'aluno1',
            'email': 'maria.oliveira@monitoria.com',
            'password': 'aluno123',
            'first_name': 'Maria',
            'last_name': 'Oliveira',
            'registration_number': 'A001',
            'course': 'Ciência da Computação',
            'semester': 3
        },
        {
            'username': 'aluno2',
            'email': 'pedro.costa@monitoria.com',
            'password': 'aluno123',
            'first_name': 'Pedro',
            'last_name': 'Costa',
            'registration_number': 'A002',
            'course': 'Sistemas de Informação',
            'semester': 2
        },
        {
            'username': 'aluno3',
            'email': 'julia.mendes@monitoria.com',
            'password': 'aluno123',
            'first_name': 'Julia',
            'last_name': 'Mendes',
            'registration_number': 'A003',
            'course': 'Ciência da Computação',
            'semester': 4
        },
    ]
    
    for data in students_data:
        if not User.objects.filter(username=data['username']).exists():
            User.objects.create_user(**data, role='student')
            print(f"✓ Student created: {data['username']} / aluno123")


def create_subjects():
    """Create subjects"""
    print("\nCreating subjects...")
    
    subjects_data = [
        {
            'name': 'Estruturas de Dados',
            'code': 'CC101',
            'description': 'Listas, pilhas, filas, árvores e grafos. Análise de complexidade.'
        },
        {
            'name': 'Banco de Dados',
            'code': 'CC201',
            'description': 'SQL, modelagem relacional, normalização e otimização de consultas.'
        },
        {
            'name': 'Algoritmos',
            'code': 'CC102',
            'description': 'Algoritmos de ordenação, busca e técnicas de programação.'
        },
        {
            'name': 'Programação Orientada a Objetos',
            'code': 'CC301',
            'description': 'Conceitos de POO, herança, polimorfismo e padrões de projeto.'
        },
        {
            'name': 'Desenvolvimento Web',
            'code': 'CC401',
            'description': 'HTML, CSS, JavaScript, Django e APIs REST.'
        },
    ]
    
    for data in subjects_data:
        subject, created = Subject.objects.get_or_create(
            code=data['code'],
            defaults=data
        )
        if created:
            print(f"✓ Subject created: {subject.code} - {subject.name}")


def create_sessions():
    """Create monitoring sessions"""
    print("\nCreating sessions...")
    
    monitor1 = User.objects.get(username='monitor1')
    monitor2 = User.objects.get(username='monitor2')
    monitor3 = User.objects.get(username='monitor3')
    
    estruturas = Subject.objects.get(code='CC101')
    banco = Subject.objects.get(code='CC201')
    algoritmos = Subject.objects.get(code='CC102')
    poo = Subject.objects.get(code='CC301')
    web = Subject.objects.get(code='CC401')
    
    sessions_data = [
        {
            'monitor': monitor1,
            'subject': estruturas,
            'title': 'Monitoria de Estruturas de Dados',
            'description': 'Atendimento para dúvidas sobre listas, pilhas, filas, árvores e grafos.',
            'location': 'Sala 201 - Laboratório de Informática',
            'weekday': 1,  # Terça
            'start_time': time(14, 0),
            'end_time': time(16, 0),
            'max_students': 15,
        },
        {
            'monitor': monitor1,
            'subject': algoritmos,
            'title': 'Monitoria de Algoritmos',
            'description': 'Ajuda com algoritmos de ordenação, busca e análise de complexidade.',
            'location': 'Sala 201 - Laboratório de Informática',
            'weekday': 3,  # Quinta
            'start_time': time(14, 0),
            'end_time': time(16, 0),
            'max_students': 12,
        },
        {
            'monitor': monitor2,
            'subject': banco,
            'title': 'Monitoria de Banco de Dados',
            'description': 'SQL, modelagem, normalização e otimização de queries.',
            'location': 'Sala 305 - Sala de Estudos',
            'weekday': 2,  # Quarta
            'start_time': time(15, 0),
            'end_time': time(17, 0),
            'max_students': 10,
        },
        {
            'monitor': monitor3,
            'subject': poo,
            'title': 'Monitoria de POO',
            'description': 'Programação orientada a objetos, padrões de projeto e boas práticas.',
            'location': 'Sala 401 - Laboratório Avançado',
            'weekday': 0,  # Segunda
            'start_time': time(16, 0),
            'end_time': time(18, 0),
            'max_students': 15,
        },
        {
            'monitor': monitor3,
            'subject': web,
            'title': 'Monitoria de Desenvolvimento Web',
            'description': 'HTML, CSS, JavaScript, Django, APIs e deploy.',
            'location': 'Sala 401 - Laboratório Avançado',
            'weekday': 4,  # Sexta
            'start_time': time(14, 0),
            'end_time': time(16, 0),
            'max_students': 12,
        },
    ]
    
    for data in sessions_data:
        session, created = MonitoringSession.objects.get_or_create(
            monitor=data['monitor'],
            subject=data['subject'],
            weekday=data['weekday'],
            defaults={**data, 'status': 'scheduled', 'is_active': True}
        )
        if created:
            print(f"✓ Session created: {session.title}")


def main():
    print("=" * 60)
    print("SETUP - Sistema de Gestão de Monitoria Acadêmica 2.0")
    print("=" * 60)
    
    try:
        create_users()
        create_subjects()
        create_sessions()
        
        print("\n" + "=" * 60)
        print("✓ Setup completed successfully!")
        print("=" * 60)
        print("\nCREDENCIAIS DE ACESSO:")
        print("\nAdministrador:")
        print("  Usuário: admin")
        print("  Senha: admin123")
        print("\nMonitores:")
        print("  Usuário: monitor1, monitor2, monitor3")
        print("  Senha: monitor123")
        print("\nAlunos:")
        print("  Usuário: aluno1, aluno2, aluno3")
        print("  Senha: aluno123")
        print("\nAcesse: http://localhost:8000")
        print("=" * 60)
        
    except Exception as e:
        print(f"\n✗ Error during setup: {e}")
        import traceback
        traceback.print_exc()


if __name__ == '__main__':
    main()

