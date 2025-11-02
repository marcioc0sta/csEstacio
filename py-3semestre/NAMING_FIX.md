# 🔧 Correção de Conflitos de Nomes - Apps Django

## ⚠️ Problemas Identificados

### Problema 1: App `queue`
O Django app estava nomeado como `queue`, o que causava um conflito com o módulo Python built-in `queue`.

**Erro Encontrado:**
```
AttributeError: module 'queue' has no attribute 'SimpleQueue'
```

**Causa:** Python tentava importar o módulo padrão `queue` mas encontrava o app Django `queue/` primeiro no path de importação.

### Problema 2: App `sessions`  
O Django app estava nomeado como `sessions`, o que causava um conflito com o app Django built-in `django.contrib.sessions`.

**Erro Encontrado:**
```
django.core.exceptions.ImproperlyConfigured: Application labels aren't unique, duplicates: sessions
```

**Causa:** Conflito entre nosso app customizado e o app de sessões do Django.

---

## ✅ Soluções Aplicadas

### 1. Renomeação dos Apps
```bash
queue/    → queue_management/
sessions/ → monitoring_sessions/
```

### 2. Arquivos Atualizados

#### settings.py
```python
# ANTES
INSTALLED_APPS = [
    ...
    'sessions',
    'queue',
    ...
]

# DEPOIS
INSTALLED_APPS = [
    ...
    'monitoring_sessions',
    'queue_management',
    ...
]
```

#### apps.py
```python
# ANTES
class QueueConfig(AppConfig):
    name = 'queue'

# DEPOIS  
class QueueManagementConfig(AppConfig):
    name = 'queue_management'
```

#### urls.py (main)
```python
# ANTES
path('queue/', include('queue.urls')),

# DEPOIS
path('queue/', include('queue_management.urls')),
```

#### urls.py (app)
```python
# ANTES
app_name = 'queue'

# DEPOIS
app_name = 'queue_management'
```

### 3. Imports Atualizados

Todos os imports foram alterados em:
- `feedback/views.py`
- `feedback/models.py`
- `accounts/views.py`
- `queue_management/views.py`
- `queue_management/models.py`
- `setup_project.py`

```python
# ANTES
from queue.models import QueueEntry
from sessions.models import MonitoringSession

# DEPOIS
from queue_management.models import QueueEntry
from monitoring_sessions.models import MonitoringSession
```

### 4. Templates Atualizados

Todas as referências de URL nos templates foram atualizadas:

```django
<!-- ANTES -->
{% url 'sessions:list' %}
{% url 'sessions:detail' session.id %}
{% url 'queue:join' session.id %}
{% url 'queue:my_queue' %}

<!-- DEPOIS -->
{% url 'monitoring_sessions:list' %}
{% url 'monitoring_sessions:detail' session.id %}
{% url 'queue_management:join' session.id %}
{% url 'queue_management:my_queue' %}
```

**Diretórios de templates movidos:**
- `templates/sessions/` → `templates/monitoring_sessions/`
- `templates/queue/` → `templates/queue_management/`

**Templates atualizados (todos):**
- Todos os arquivos HTML em `templates/`

---

## 🚀 Após a Correção

### Comandos para Aplicar (Docker)

```bash
# 1. Parar containers
docker-compose down

# 2. Rebuild (necessário devido à mudança de estrutura)
docker-compose build --no-cache

# 3. Iniciar novamente
docker-compose up -d

# 4. Criar novas migrations (se necessário)
docker-compose exec web python manage.py makemigrations

# 5. Aplicar migrations
docker-compose exec web python manage.py migrate

# 6. Carregar dados de teste
docker-compose exec web python setup_project.py
```

### Comandos para Aplicar (Local)

```bash
# 1. Criar migrations
python manage.py makemigrations

# 2. Aplicar migrations
python manage.py migrate

# 3. Carregar dados
python setup_project.py

# 4. Iniciar servidor
python manage.py runserver
```

---

## 📝 Nota sobre Migrations

Django pode criar novas migrations devido à mudança do nome do app. As tabelas do banco de dados permanecem as mesmas, mas as referências no código de migração serão atualizadas.

### Se houver erro de migrations:

```bash
# Opção 1: Fake a migration
docker-compose exec web python manage.py migrate queue_management --fake

# Opção 2: Reset do banco (CUIDADO: perde dados)
docker-compose down -v
docker-compose up --build -d
docker-compose exec web python manage.py migrate
docker-compose exec web python setup_project.py
```

---

## ✅ Verificação

Após aplicar a correção, verifique:

1. **Servidor inicia sem erros:**
   ```bash
   docker-compose logs web
   # Deve mostrar "Listening at: http://0.0.0.0:8000"
   ```

2. **Acesse a aplicação:**
   - http://localhost:8000
   - Deve carregar normalmente

3. **Teste as funcionalidades:**
   - Login ✓
   - Visualizar sessões ✓
   - Entrar na fila ✓
   - Ver minha fila ✓

---

## 🎯 Boas Práticas Aprendidas

### ❌ Evite nomear apps Django com:
- Nomes de módulos Python built-in (`queue`, `json`, `time`, `os`, etc.)
- Nomes de apps Django built-in (`sessions`, `auth`, `admin`, `messages`, etc.)
- Nomes muito genéricos que podem causar conflitos
- Palavras reservadas do Python

### ✅ Prefira nomes:
- Descritivos e específicos: `queue_management`, `monitoring_sessions`, `user_authentication`
- Com contexto do projeto: `monitoria_queue`, `academic_feedback`
- Únicos e sem ambiguidade
- Com prefixo ou sufixo descritivo

---

## 📚 Referências

- [Django App Naming Best Practices](https://docs.djangoproject.com/en/4.2/intro/reusable-apps/)
- [Python Module Search Path](https://docs.python.org/3/tutorial/modules.html#the-module-search-path)
- [Common Naming Conflicts to Avoid](https://stackoverflow.com/questions/54835697/how-to-fix-attributeerror-module-queue-has-no-attribute-simplequeue)

---

## ✨ Status Final

✅ **Problemas resolvidos!**  
✅ **Apps renomeados:**
   - `queue` → `queue_management`
   - `sessions` → `monitoring_sessions`
✅ **Todas as referências atualizadas**  
✅ **Templates corrigidos e movidos**  
✅ **Imports corrigidos**  
✅ **URLs atualizadas**  
✅ **Sistema funcional**

---

**Data da Correção:** 2024
**Versão:** 1.0 → 1.1

