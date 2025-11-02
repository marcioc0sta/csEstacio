# Sistema de Gestão de Monitoria Acadêmica 2.0

Sistema completo desenvolvido em Django para gerenciamento de sessões de monitoria acadêmica, permitindo interação entre monitores e alunos, agendamento de atendimentos, fila dinâmica e sistema de feedback.

## 🚀 Funcionalidades

### ✅ Autenticação e Perfis
- Sistema completo de registro e login
- Três tipos de perfis: **Aluno**, **Monitor** e **Administrador**
- Perfis personalizáveis com foto, bio, curso e semestre
- Dashboards específicos para cada tipo de usuário

### ✅ Sessões de Monitoria (CRUD Completo)
- Monitores podem criar, editar e excluir sessões
- Definição de horários, dias da semana e locais
- Associação com disciplinas
- Status e controle de sessões ativas

### ✅ Fila de Espera Dinâmica
- Sistema de fila inteligente com posicionamento automático
- Priorização de atendimentos (normal, alta, urgente)
- Controle de status (aguardando, em atendimento, concluído)
- Atualização em tempo real para monitores
- Cancelamento de entradas na fila

### ✅ Feedback e Avaliações
- Sistema completo de avaliação com múltiplos critérios:
  - Avaliação geral
  - Conhecimento do monitor
  - Comunicação
  - Paciência e didática
- Comentários e avaliações anônimas opcionais
- Ranking de monitores baseado em avaliações
- Estatísticas detalhadas para monitores

### ✅ Busca e Filtros
- Filtro por disciplina
- Filtro por nome do monitor
- Filtro por dia da semana
- Filtro por status da sessão
- Sistema de paginação

### ✅ Interface Responsiva
- Design moderno com Bootstrap 5
- Totalmente responsivo para mobile, tablet e desktop
- Ícones Bootstrap Icons
- Gradientes e animações suaves
- UX otimizada

## 📋 Requisitos

- Python 3.8+
- Django 4.2+
- SQLite (desenvolvimento) / PostgreSQL (produção)

## 🔧 Instalação e Configuração

### 1. Clone o repositório
```bash
cd py-3semestre
```

### 2. Crie um ambiente virtual
```bash
python -m venv venv

# Windows
venv\Scripts\activate

# Linux/Mac
source venv/bin/activate
```

### 3. Instale as dependências
```bash
pip install -r requirements.txt
```

### 4. Execute as migrações
```bash
python manage.py makemigrations
python manage.py migrate
```

### 5. Crie um superusuário (admin)
```bash
python manage.py createsuperuser
```

### 6. Carregue dados de teste (opcional)
```bash
python manage.py shell
```

Então execute:
```python
from django.contrib.auth import get_user_model
from sessions.models import Subject, MonitoringSession
from datetime import time

User = get_user_model()

# Criar usuários de teste
admin = User.objects.create_superuser(
    username='admin',
    email='admin@monitoria.com',
    password='admin123',
    first_name='Admin',
    last_name='Sistema',
    role='admin'
)

monitor1 = User.objects.create_user(
    username='monitor1',
    email='monitor1@monitoria.com',
    password='monitor123',
    first_name='João',
    last_name='Silva',
    role='monitor',
    registration_number='M001',
    course='Ciência da Computação',
    semester=6
)

student1 = User.objects.create_user(
    username='aluno1',
    email='aluno1@monitoria.com',
    password='aluno123',
    first_name='Maria',
    last_name='Santos',
    role='student',
    registration_number='A001',
    course='Ciência da Computação',
    semester=3
)

# Criar disciplinas
disciplina1 = Subject.objects.create(
    name='Estruturas de Dados',
    code='CC101',
    description='Listas, pilhas, filas, árvores e grafos'
)

disciplina2 = Subject.objects.create(
    name='Banco de Dados',
    code='CC201',
    description='SQL, modelagem e otimização'
)

# Criar sessão de monitoria
sessao1 = MonitoringSession.objects.create(
    monitor=monitor1,
    subject=disciplina1,
    title='Monitoria de Estruturas de Dados',
    description='Atendimento para dúvidas em estruturas de dados',
    location='Sala 201 - Laboratório',
    weekday=1,  # Terça-feira
    start_time=time(14, 0),
    end_time=time(16, 0),
    max_students=15,
    status='scheduled',
    is_active=True
)

print("Dados de teste criados com sucesso!")
```

### 7. Execute o servidor
```bash
python manage.py runserver
```

Acesse: `http://localhost:8000`

## 👥 Credenciais de Teste

Após carregar os dados de teste, você pode usar:

### Administrador
- **Usuário:** admin
- **Senha:** admin123

### Monitor
- **Usuário:** monitor1
- **Senha:** monitor123

### Aluno
- **Usuário:** aluno1
- **Senha:** aluno123

## 📱 Como Usar

### Para Alunos:
1. Faça login ou cadastre-se como aluno
2. Navegue até "Sessões" para ver as monitorias disponíveis
3. Clique em uma sessão para ver detalhes
4. Entre na fila de atendimento
5. Aguarde ser chamado pelo monitor
6. Após o atendimento, avalie o monitor

### Para Monitores:
1. Faça login ou cadastre-se como monitor
2. Crie suas sessões de monitoria no dashboard
3. Gerencie a fila de atendimento em tempo real
4. Inicie e conclua atendimentos
5. Visualize suas estatísticas e avaliações

### Para Administradores:
1. Acesse o painel administrativo em `/admin`
2. Gerencie usuários, disciplinas e sessões
3. Visualize estatísticas gerais
4. Crie novas disciplinas

## 🗂️ Estrutura do Projeto

```
py-3semestre/
├── accounts/              # App de autenticação e usuários
│   ├── models.py         # Modelo CustomUser com roles
│   ├── views.py          # Login, registro, perfis
│   └── forms.py          # Formulários de autenticação
├── sessions/              # App de sessões de monitoria
│   ├── models.py         # Sessões, disciplinas, presença
│   ├── views.py          # CRUD de sessões
│   └── forms.py          # Formulários de sessão
├── queue/                 # App de fila de atendimento
│   ├── models.py         # Fila dinâmica
│   ├── views.py          # Gerenciamento de fila
│   └── forms.py          # Entrada na fila
├── feedback/              # App de avaliações
│   ├── models.py         # Feedbacks e relatórios
│   ├── views.py          # Sistema de avaliação
│   └── forms.py          # Formulários de feedback
├── templates/             # Templates HTML
│   ├── base.html         # Template base
│   ├── home.html         # Página inicial
│   ├── accounts/         # Templates de usuário
│   ├── sessions/         # Templates de sessões
│   ├── queue/            # Templates de fila
│   └── feedback/         # Templates de feedback
├── monitoria_system/      # Configurações do projeto
│   ├── settings.py       # Configurações Django
│   └── urls.py           # URLs principais
├── manage.py
├── requirements.txt
└── README.md
```

## 🎨 Tecnologias Utilizadas

- **Backend:** Django 4.2
- **Frontend:** Bootstrap 5, Bootstrap Icons
- **Banco de Dados:** SQLite (dev) / PostgreSQL (prod)
- **Autenticação:** Django Auth System
- **Deployment:** Gunicorn, WhiteNoise

## 🚀 Deploy

### Heroku

1. Instale o Heroku CLI
2. Crie um app no Heroku:
```bash
heroku create nome-do-app
```

3. Configure o PostgreSQL:
```bash
heroku addons:create heroku-postgresql:mini
```

4. Configure as variáveis de ambiente:
```bash
heroku config:set DEBUG=False
heroku config:set SECRET_KEY='sua-chave-secreta'
```

5. Deploy:
```bash
git push heroku main
heroku run python manage.py migrate
heroku run python manage.py createsuperuser
```

### Render

1. Crie uma conta no Render
2. Conecte seu repositório GitHub
3. Configure as variáveis de ambiente
4. O deploy será automático

## 📊 Funcionalidades Técnicas

### Segurança
- CSRF Protection
- Autenticação baseada em sessão
- Senhas hasheadas com PBKDF2
- Permissões baseadas em roles

### Performance
- Queries otimizadas com select_related
- Paginação em listagens
- Static files com WhiteNoise
- Cache-Control headers

### Boas Práticas
- Código organizado em apps
- Templates reutilizáveis
- Forms validation
- Messages framework
- Responsive design

## 🤝 Contribuindo

Este é um projeto acadêmico, mas sugestões são bem-vindas!

## 📝 Licença

Este projeto foi desenvolvido para fins educacionais.

## 👨‍💻 Autor

Desenvolvido como trabalho individual da disciplina de Desenvolvimento Web com Django.

## 📧 Contato

Para dúvidas ou sugestões, entre em contato através do sistema.

---

**Sistema de Gestão de Monitoria Acadêmica 2.0** - Otimizando o aprendizado colaborativo! 📚✨

