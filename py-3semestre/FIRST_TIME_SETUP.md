# 🚀 Setup da Primeira Vez - Passo a Passo

## ⚠️ IMPORTANTE - Leia Isto Primeiro!

Este é um projeto Django que precisa de **migrations** antes do primeiro uso.

---

## 📋 Ordem Correta de Comandos

### Opção 1: Script Automatizado (Mais Fácil) ✅

```bash
chmod +x docker-start.sh
./docker-start.sh
```

O script agora inclui automaticamente:
1. ✅ Build das imagens
2. ✅ Criação de migrations
3. ✅ Aplicação de migrations
4. ✅ Carregamento de dados
5. ✅ Início do servidor

---

### Opção 2: Comandos Manuais (Passo a Passo)

```bash
# 1. Build e iniciar containers
docker-compose up --build -d

# 2. Aguardar PostgreSQL (importante!)
sleep 10

# 3. CRIAR MIGRATIONS (essencial!)
docker-compose run --rm web python manage.py makemigrations

# 4. APLICAR MIGRATIONS
docker-compose run --rm web python manage.py migrate

# 5. CARREGAR DADOS DE TESTE
docker-compose run --rm web python setup_project.py

# 6. ACESSAR
open http://localhost:8000
```

---

### Opção 3: Makefile

```bash
# Tudo de uma vez
make start

# Ou passo a passo:
make build
make up
make makemigrations
make migrate
make loaddata
```

---

## 🔍 Por Que Makemigrations?

Django precisa criar arquivos de migração baseados nos models antes de criar as tabelas no banco de dados.

### O Que Acontece:

```
1. makemigrations → Analisa models.py e cria arquivos migration
2. migrate → Lê os arquivos e cria tabelas no PostgreSQL
3. setup_project.py → Popula tabelas com dados de teste
```

### Sem makemigrations:
❌ `relation "accounts_customuser" does not exist`

### Com makemigrations:
✅ Tabelas criadas corretamente!

---

## 🎯 Comandos Explicados

### makemigrations
```bash
docker-compose run --rm web python manage.py makemigrations
```

**O que faz:**
- Lê os arquivos `models.py` de todos os apps
- Cria arquivos de migração em `app/migrations/`
- Exemplo: `0001_initial.py`, `0002_auto_...py`

**Output esperado:**
```
Migrations for 'accounts':
  accounts/migrations/0001_initial.py
    - Create model CustomUser
Migrations for 'monitoring_sessions':
  monitoring_sessions/migrations/0001_initial.py
    - Create model Subject
    - Create model MonitoringSession
    - Create model Attendance
```

### migrate
```bash
docker-compose run --rm web python manage.py migrate
```

**O que faz:**
- Lê os arquivos de migração
- Executa SQL para criar/atualizar tabelas
- Registra quais migrations foram aplicadas

**Output esperado:**
```
Operations to perform:
  Apply all migrations: accounts, admin, auth, ...
Running migrations:
  Applying accounts.0001_initial... OK
  Applying monitoring_sessions.0001_initial... OK
  ...
```

---

## ✅ Verificar Se Funcionou

### 1. Ver status das migrations:
```bash
docker-compose run --rm web python manage.py showmigrations
```

**Esperado:**
```
accounts
 [X] 0001_initial
monitoring_sessions
 [X] 0001_initial
queue_management
 [X] 0001_initial
feedback
 [X] 0001_initial
```

### 2. Listar tabelas no PostgreSQL:
```bash
docker-compose exec db psql -U monitoria_user -d monitoria_db -c "\dt"
```

**Deve mostrar:**
- `accounts_customuser`
- `monitoring_sessions_subject`
- `monitoring_sessions_monitoringsession`
- `queue_management_queueentry`
- `feedback_feedback`
- e outras...

### 3. Acessar o site:
```bash
open http://localhost:8000
```

**Se funcionar:** ✅ Setup correto!  
**Se erro 500:** ❌ Verificar logs

---

## 🐛 Troubleshooting

### Erro: "no such table: accounts_customuser"
**Causa:** Migrations não foram aplicadas  
**Solução:**
```bash
docker-compose run --rm web python manage.py makemigrations
docker-compose run --rm web python manage.py migrate
```

### Erro: "relation already exists"
**Causa:** Tentou criar migrations/migrate múltiplas vezes  
**Solução:** Fake a migration
```bash
docker-compose run --rm web python manage.py migrate --fake
```

### Erro: Containers não iniciam
**Solução:** Reset completo
```bash
docker-compose down -v
docker-compose up --build -d
sleep 10
docker-compose run --rm web python manage.py makemigrations
docker-compose run --rm web python manage.py migrate
docker-compose run --rm web python setup_project.py
```

### Ver logs detalhados:
```bash
docker-compose logs -f web
docker-compose logs -f db
```

---

## 📦 Estrutura de Migrations Criadas

Após `makemigrations`, você verá:

```
accounts/
└── migrations/
    ├── __init__.py
    └── 0001_initial.py ✅ NOVO

monitoring_sessions/
└── migrations/
    ├── __init__.py
    └── 0001_initial.py ✅ NOVO

queue_management/
└── migrations/
    ├── __init__.py
    └── 0001_initial.py ✅ NOVO

feedback/
└── migrations/
    ├── __init__.py
    └── 0001_initial.py ✅ NOVO
```

---

## 🎓 Desenvolvendo Depois

### Sempre que mudar um Model:

```bash
# 1. Editar models.py
# 2. Criar migration
docker-compose exec web python manage.py makemigrations

# 3. Aplicar migration
docker-compose exec web python manage.py migrate

# 4. Verificar
docker-compose exec web python manage.py showmigrations
```

### Exemplo:
```python
# Adicionar campo em accounts/models.py
class CustomUser(AbstractUser):
    ...
    nickname = models.CharField(max_length=50)  # NOVO CAMPO
```

```bash
docker-compose exec web python manage.py makemigrations accounts
docker-compose exec web python manage.py migrate
```

---

## 📚 Documentação Relacionada

- **MIGRATION_SETUP.md** - Detalhes técnicos
- **ALL_FIXED.md** - Correções aplicadas
- **IMPORTANT_UPDATE.md** - Atualização importante
- **DOCKER_QUICKSTART.md** - Guia Docker

---

## ✨ Resumo - Comandos Essenciais

```bash
# Setup Inicial (UMA VEZ)
docker-compose up --build -d
docker-compose run --rm web python manage.py makemigrations
docker-compose run --rm web python manage.py migrate
docker-compose run --rm web python setup_project.py

# Uso Diário
docker-compose up -d        # Iniciar
docker-compose down         # Parar

# Desenvolvimento (quando mudar models)
docker-compose exec web python manage.py makemigrations
docker-compose exec web python manage.py migrate

# Reset Completo
docker-compose down -v
# ... repetir setup inicial
```

---

✅ **Após seguir este guia, o sistema estará 100% funcional!**

**Credenciais:**
- Admin: admin / admin123
- Monitor: monitor1 / monitor123
- Aluno: aluno1 / aluno123

**URL:** http://localhost:8000

