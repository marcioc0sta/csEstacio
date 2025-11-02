# 🔧 Setup de Migrations - Importante!

## ⚠️ Passo Necessário Antes de Usar

O projeto precisa que as migrations sejam criadas antes do primeiro uso. 

## 🚀 Execute Este Comando PRIMEIRO:

### Opção 1: Com Docker (Recomendado)

```bash
# 1. Criar migrations para todos os apps
docker-compose run --rm web python manage.py makemigrations

# 2. Aplicar migrations
docker-compose run --rm web python manage.py migrate

# 3. Carregar dados de teste
docker-compose run --rm web python setup_project.py

# 4. Iniciar normalmente
docker-compose up -d
```

### Opção 2: Script Automatizado Atualizado

O script `docker-start.sh` precisa ser atualizado para incluir `makemigrations`.

Execute manualmente:

```bash
# Parar containers se estiverem rodando
docker-compose down

# Criar migrations
docker-compose run --rm web python manage.py makemigrations accounts
docker-compose run --rm web python manage.py makemigrations monitoring_sessions
docker-compose run --rm web python manage.py makemigrations queue_management
docker-compose run --rm web python manage.py makemigrations feedback

# Aplicar migrations
docker-compose run --rm web python manage.py migrate

# Carregar dados
docker-compose run --rm web python setup_project.py

# Iniciar
docker-compose up -d
```

### Opção 3: Makefile Atualizado

```bash
# Criar migrations
make makemigrations

# Aplicar migrations  
make migrate

# Ou tudo de uma vez
make reset
```

## 📝 O Que São Migrations?

Migrations são arquivos que Django usa para criar e atualizar o esquema do banco de dados. Elas precisam ser geradas antes do primeiro uso.

## 🔍 Por Que Esse Erro?

O erro `relation "accounts_customuser" does not exist` acontece porque:

1. Django tenta aplicar migrations dos apps built-in (`admin`, `contenttypes`)
2. Esses apps dependem do modelo `CustomUser`
3. Mas as migrations do app `accounts` ainda não foram criadas
4. Resultado: tabela não existe no banco

## ✅ Solução

Criar migrations para todos os apps customizados ANTES de aplicar as migrations:

```bash
docker-compose run --rm web python manage.py makemigrations
```

Isso criará arquivos em:
- `accounts/migrations/0001_initial.py`
- `monitoring_sessions/migrations/0001_initial.py`
- `queue_management/migrations/0001_initial.py`
- `feedback/migrations/0001_initial.py`

## 🎯 Ordem Correta de Execução

1. **makemigrations** - Cria os arquivos de migração
2. **migrate** - Aplica as migrations no banco
3. **setup_project.py** - Carrega dados de teste
4. **runserver/up** - Inicia a aplicação

## 📦 Estrutura Esperada

```
accounts/
├── migrations/
│   ├── __init__.py
│   └── 0001_initial.py    ← Será criado
├── models.py
└── ...

monitoring_sessions/
├── migrations/
│   ├── __init__.py
│   └── 0001_initial.py    ← Será criado
├── models.py
└── ...
```

## 🔧 Troubleshooting

### Se ainda houver erro:

```bash
# 1. Parar tudo
docker-compose down -v

# 2. Reconstruir
docker-compose build --no-cache

# 3. Criar migrations
docker-compose run --rm web python manage.py makemigrations

# 4. Aplicar migrations
docker-compose run --rm web python manage.py migrate

# 5. Carregar dados
docker-compose run --rm web python setup_project.py

# 6. Iniciar
docker-compose up -d
```

### Verificar se migrations foram criadas:

```bash
# Listar migrations
docker-compose run --rm web python manage.py showmigrations

# Deve mostrar:
# accounts
#  [ ] 0001_initial
# monitoring_sessions
#  [ ] 0001_initial
# queue_management
#  [ ] 0001_initial
# feedback
#  [ ] 0001_initial
```

## 💡 Dica

Se você está desenvolvendo e mudando models frequentemente:

```bash
# Sempre que mudar um model:
docker-compose exec web python manage.py makemigrations
docker-compose exec web python manage.py migrate
```

---

✅ **Após seguir estes passos, o sistema funcionará normalmente!**

