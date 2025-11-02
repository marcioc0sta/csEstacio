# 🚀 Guia de Deploy - Sistema de Monitoria 2.0

Este guia mostra como fazer deploy do sistema em diferentes plataformas.

## 📋 Pré-requisitos para Deploy

1. Código em um repositório Git (GitHub, GitLab, etc.)
2. Conta na plataforma de deploy escolhida
3. Configurações de produção ajustadas

## 🔧 Preparação para Produção

### 1. Atualizar settings.py para produção

Crie um arquivo `monitoria_system/settings_prod.py`:

```python
from .settings import *
import os
import dj_database_url

DEBUG = False
ALLOWED_HOSTS = ['seu-dominio.com', 'www.seu-dominio.com']

# Security
SECRET_KEY = os.environ.get('SECRET_KEY')
SECURE_SSL_REDIRECT = True
SESSION_COOKIE_SECURE = True
CSRF_COOKIE_SECURE = True

# Database
DATABASES = {
    'default': dj_database_url.config(
        default=os.environ.get('DATABASE_URL')
    )
}

# Static files
STATIC_ROOT = BASE_DIR / 'staticfiles'
STATICFILES_STORAGE = 'whitenoise.storage.CompressedManifestStaticFilesStorage'
```

### 2. Adicionar WhiteNoise ao middleware

Em `settings.py`, adicione logo após SecurityMiddleware:

```python
MIDDLEWARE = [
    'django.middleware.security.SecurityMiddleware',
    'whitenoise.middleware.WhiteNoiseMiddleware',  # Add this
    # ... resto
]
```

## 🌐 Deploy no Heroku

### Passo 1: Instalar Heroku CLI
```bash
# Mac
brew tap heroku/brew && brew install heroku

# Windows
# Baixe de: https://devcenter.heroku.com/articles/heroku-cli
```

### Passo 2: Login no Heroku
```bash
heroku login
```

### Passo 3: Criar App
```bash
heroku create monitoria-sistema
```

### Passo 4: Adicionar PostgreSQL
```bash
heroku addons:create heroku-postgresql:mini
```

### Passo 5: Configurar Variáveis de Ambiente
```bash
heroku config:set SECRET_KEY='sua-chave-secreta-aqui'
heroku config:set DEBUG=False
heroku config:set DJANGO_SETTINGS_MODULE=monitoria_system.settings_prod
```

### Passo 6: Deploy
```bash
git push heroku main
```

### Passo 7: Migrar Banco de Dados
```bash
heroku run python manage.py migrate
heroku run python setup_project.py
```

### Passo 8: Criar Superusuário
```bash
heroku run python manage.py createsuperuser
```

### Passo 9: Abrir Aplicação
```bash
heroku open
```

## 🎯 Deploy no Render

### Passo 1: Criar conta no Render
Acesse [render.com](https://render.com) e crie uma conta.

### Passo 2: Novo Web Service
1. Clique em "New +"
2. Selecione "Web Service"
3. Conecte seu repositório GitHub

### Passo 3: Configurar Serviço
- **Name:** monitoria-sistema
- **Region:** Ohio (US East)
- **Branch:** main
- **Runtime:** Python 3
- **Build Command:** `pip install -r requirements.txt`
- **Start Command:** `gunicorn monitoria_system.wsgi:application`

### Passo 4: Adicionar PostgreSQL
1. Clique em "New +"
2. Selecione "PostgreSQL"
3. Nomeie como "monitoria-db"

### Passo 5: Configurar Variáveis de Ambiente
No dashboard do Web Service, adicione:
- `SECRET_KEY`: sua-chave-secreta
- `DEBUG`: False
- `DATABASE_URL`: (auto-preenchido ao conectar o PostgreSQL)
- `PYTHON_VERSION`: 3.11.6

### Passo 6: Deploy
O deploy será automático após commit no GitHub.

### Passo 7: Executar Migrações
No dashboard, vá em "Shell" e execute:
```bash
python manage.py migrate
python setup_project.py
```

## 🐙 Deploy no Railway

### Passo 1: Criar conta no Railway
Acesse [railway.app](https://railway.app)

### Passo 2: Novo Projeto
1. Clique em "New Project"
2. Selecione "Deploy from GitHub repo"
3. Escolha seu repositório

### Passo 3: Adicionar PostgreSQL
1. Clique em "+ New"
2. Selecione "Database" → "PostgreSQL"

### Passo 4: Configurar Variáveis
No serviço Django, adicione:
- `SECRET_KEY`: sua-chave-secreta
- `DEBUG`: False
- `DATABASE_URL`: (copie do PostgreSQL)
- `PORT`: 8000

### Passo 5: Deploy
O deploy é automático!

### Passo 6: Executar Comandos
```bash
railway run python manage.py migrate
railway run python setup_project.py
```

## ☁️ Deploy no PythonAnywhere

### Passo 1: Criar conta
Acesse [pythonanywhere.com](https://www.pythonanywhere.com)

### Passo 2: Abrir Console Bash
```bash
git clone https://github.com/seu-usuario/monitoria-sistema.git
cd monitoria-sistema
```

### Passo 3: Criar Virtual Environment
```bash
mkvirtualenv --python=/usr/bin/python3.10 monitoria
pip install -r requirements.txt
```

### Passo 4: Configurar Web App
1. Vá em "Web"
2. "Add a new web app"
3. Escolha "Manual configuration"
4. Python 3.10

### Passo 5: Configurar WSGI
Edite o arquivo WSGI com:
```python
import os
import sys

path = '/home/seuusername/monitoria-sistema'
if path not in sys.path:
    sys.path.append(path)

os.environ['DJANGO_SETTINGS_MODULE'] = 'monitoria_system.settings'

from django.core.wsgi import get_wsgi_application
application = get_wsgi_application()
```

### Passo 6: Configurar Static Files
- URL: `/static/`
- Directory: `/home/seuusername/monitoria-sistema/staticfiles/`

### Passo 7: Coletar Static Files
```bash
python manage.py collectstatic
python manage.py migrate
python setup_project.py
```

### Passo 8: Reload
Clique em "Reload" no dashboard.

## 🔒 Checklist de Segurança

Antes de colocar em produção:

- [ ] `DEBUG = False`
- [ ] `SECRET_KEY` em variável de ambiente
- [ ] `ALLOWED_HOSTS` configurado
- [ ] HTTPS habilitado
- [ ] Cookies seguros configurados
- [ ] PostgreSQL (não SQLite)
- [ ] Senhas fortes para admin
- [ ] Backup do banco de dados configurado

## 🔧 Troubleshooting

### Static files não carregam
```bash
python manage.py collectstatic --noinput
```

### Erro 500
Verifique logs:
```bash
# Heroku
heroku logs --tail

# Render
Veja "Logs" no dashboard

# Railway
Veja "Deployments" → "Logs"
```

### Banco de dados não migra
```bash
python manage.py migrate --run-syncdb
```

## 📊 Monitoramento

### Heroku
```bash
heroku logs --tail
heroku ps
heroku pg:info
```

### Logs de aplicação
Adicione logging em `settings.py`:
```python
LOGGING = {
    'version': 1,
    'disable_existing_loggers': False,
    'handlers': {
        'console': {
            'class': 'logging.StreamHandler',
        },
    },
    'root': {
        'handlers': ['console'],
        'level': 'INFO',
    },
}
```

## 🎉 Pronto!

Seu sistema está no ar! Compartilhe o link com os usuários.

### URLs importantes:
- **Home:** https://seu-app.herokuapp.com/
- **Admin:** https://seu-app.herokuapp.com/admin/
- **Sessões:** https://seu-app.herokuapp.com/sessions/

---
💡 **Dica:** Monitore os logs regularmente e faça backups do banco de dados!

