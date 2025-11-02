# 🐳 Docker Cheat Sheet - Sistema de Monitoria

## 🚀 Início Rápido (3 comandos)

```bash
# 1. Dar permissão
chmod +x docker-start.sh

# 2. Iniciar tudo
./docker-start.sh

# 3. Acessar
open http://localhost:8000
```

**Pronto!** Login: `admin` / `admin123`

---

## 📋 Comandos Essenciais

### Iniciar e Parar

```bash
# Iniciar (background)
docker-compose up -d

# Parar (mantém dados)
docker-compose down

# Parar e remover dados
docker-compose down -v
```

### Ver Status

```bash
# Status dos containers
docker-compose ps

# Logs (tempo real)
docker-compose logs -f

# Logs só do Django
docker-compose logs -f web

# Uso de recursos
docker stats
```

### Executar Comandos

```bash
# Shell Django
docker-compose exec web python manage.py shell

# Bash no container
docker-compose exec web bash

# PostgreSQL
docker-compose exec db psql -U monitoria_user -d monitoria_db
```

---

## 🔧 Django Commands

```bash
# Migrations
docker-compose exec web python manage.py migrate
docker-compose exec web python manage.py makemigrations

# Superuser
docker-compose exec web python manage.py createsuperuser

# Dados de teste
docker-compose exec web python setup_project.py

# Coletar static
docker-compose exec web python manage.py collectstatic

# Shell
docker-compose exec web python manage.py shell
```

---

## 🎯 Makefile (Atalhos)

```bash
make help          # Ver todos os comandos
make start         # Setup inicial completo
make up            # Iniciar
make down          # Parar
make logs          # Ver logs
make shell         # Django shell
make dbshell       # PostgreSQL shell
make migrate       # Migrations
make superuser     # Criar admin
make loaddata      # Dados de teste
make reset         # Reset completo
```

---

## 🗃️ Banco de Dados

### Backup

```bash
# Criar backup
docker-compose exec db pg_dump -U monitoria_user monitoria_db > backup.sql

# Restaurar
docker-compose exec -T db psql -U monitoria_user monitoria_db < backup.sql
```

### Acesso

```bash
# Via Docker
docker-compose exec db psql -U monitoria_user -d monitoria_db

# Via localhost
psql -h localhost -p 5432 -U monitoria_user -d monitoria_db
```

**Credenciais:**
- User: `monitoria_user`
- Password: `monitoria_pass123`
- Database: `monitoria_db`

---

## 🔄 Rebuild & Reset

```bash
# Rebuild imagem
docker-compose build --no-cache

# Restart serviço
docker-compose restart web

# Reset completo
docker-compose down -v
docker-compose up --build -d
docker-compose exec web python manage.py migrate
docker-compose exec web python setup_project.py
```

---

## 🐛 Troubleshooting

### Container não inicia

```bash
docker-compose logs web
docker-compose down
docker-compose up --build
```

### Erro de conexão DB

```bash
docker-compose ps db
docker-compose restart db
docker-compose logs db
```

### Porta em uso

Edite `docker-compose.yml`:
```yaml
ports:
  - "8001:8000"  # Muda de 8000 para 8001
```

### Limpar tudo

```bash
docker-compose down -v
docker system prune -a --volumes
```

---

## 📊 Volumes

```bash
# Listar volumes
docker volume ls

# Inspecionar
docker volume inspect py-3semestre_postgres_data

# Remover
docker volume rm py-3semestre_postgres_data
```

---

## 🌐 URLs

- **App:** http://localhost:8000
- **Admin:** http://localhost:8000/admin
- **Sessões:** http://localhost:8000/sessions
- **PostgreSQL:** localhost:5432

---

## 👤 Credenciais Padrão

### Django
- **Admin:** admin / admin123
- **Monitor:** monitor1 / monitor123
- **Aluno:** aluno1 / aluno123

### PostgreSQL
- **Host:** localhost (ou db dentro do Docker)
- **Port:** 5432
- **User:** monitoria_user
- **Password:** monitoria_pass123
- **Database:** monitoria_db

---

## 🎨 Modos

### Desenvolvimento (padrão)

```bash
docker-compose up
```

### Produção (com Nginx)

```bash
docker-compose --profile production up
```

---

## 📝 Logs

```bash
# Todos os logs
docker-compose logs

# Logs em tempo real
docker-compose logs -f

# Últimas 100 linhas
docker-compose logs --tail=100

# Desde timestamp
docker-compose logs --since 2024-01-01

# Só erros
docker-compose logs | grep ERROR
```

---

## 🔍 Inspeção

```bash
# Info do container
docker inspect monitoria_web

# Processos rodando
docker-compose top

# Estatísticas
docker stats monitoria_web monitoria_db

# Health check
docker-compose ps
```

---

## 🚀 Deploy

### Produção simples

```bash
# 1. Clonar repo
git clone <repo> && cd py-3semestre

# 2. Configurar variáveis
export SECRET_KEY="..."
export DEBUG=False

# 3. Iniciar com nginx
docker-compose --profile production up -d

# 4. Migrations
docker-compose exec web python manage.py migrate

# 5. Criar admin
docker-compose exec web python manage.py createsuperuser
```

---

## 💡 Dicas Rápidas

### Desenvolvimento eficiente

```bash
# Terminal 1: Logs
docker-compose logs -f web

# Terminal 2: Shell Django
docker-compose exec web python manage.py shell

# Terminal 3: Comandos
docker-compose exec web bash
```

### Hot reload

O código é montado como volume, mudanças são refletidas automaticamente!

### Múltiplos ambientes

```bash
# Dev
docker-compose up

# Staging
docker-compose -f docker-compose.staging.yml up

# Production
docker-compose -f docker-compose.prod.yml up
```

---

## 📚 Documentação

| Arquivo | Propósito |
|---------|-----------|
| DOCKER_QUICKSTART.md | Início rápido |
| DOCKER_README.md | Doc completa |
| DOCKER_SETUP_SUMMARY.md | Resumo técnico |
| DOCKER_CHEATSHEET.md | Este arquivo |

---

## ⚡ One-Liners Úteis

```bash
# Restart rápido
docker-compose restart web

# Ver IP dos containers
docker-compose exec web hostname -I

# Conectar dois containers
docker network connect monitoria_network outro_container

# Logs em arquivo
docker-compose logs > logs.txt

# Ver env vars
docker-compose exec web env

# Tamanho das imagens
docker images | grep monitoria
```

---

## 🎯 Workflows Comuns

### Adicionar nova feature

```bash
# 1. Fazer alterações no código
# 2. Se mudou models:
docker-compose exec web python manage.py makemigrations
docker-compose exec web python manage.py migrate

# 3. Se mudou requirements.txt:
docker-compose build web
docker-compose up -d web

# 4. Testar
open http://localhost:8000
```

### Atualizar produção

```bash
# 1. Pull novo código
git pull

# 2. Rebuild
docker-compose build

# 3. Restart
docker-compose up -d

# 4. Migrations
docker-compose exec web python manage.py migrate

# 5. Collect static
docker-compose exec web python manage.py collectstatic --noinput
```

---

🐳 **Coloque este arquivo nos favoritos para referência rápida!**

Para mais detalhes: `make help` ou leia `DOCKER_README.md`

