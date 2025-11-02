# 🐳 Docker Quick Start - 5 Minutos!

## ⚡ Início Ultra-Rápido

### Opção 1: Usando Scripts (Recomendado)

```bash
# Dar permissão de execução
chmod +x docker-start.sh docker-stop.sh

# Iniciar tudo
./docker-start.sh

# Parar quando terminar
./docker-stop.sh
```

### Opção 2: Usando Makefile

```bash
# Iniciar tudo (primeira vez)
make start

# Ver comandos disponíveis
make help

# Parar
make down
```

### Opção 3: Comandos Manuais

```bash
# Iniciar
docker-compose up -d

# Migrations
docker-compose exec web python manage.py migrate

# Carregar dados
docker-compose exec web python setup_project.py

# Parar
docker-compose down
```

## 🌐 Acessar a Aplicação

**URL:** http://localhost:8000

### Credenciais:
- **Admin:** admin / admin123
- **Monitor:** monitor1 / monitor123  
- **Aluno:** aluno1 / aluno123

## 📊 Comandos Úteis

```bash
# Ver logs
docker-compose logs -f

# Entrar no container
docker-compose exec web bash

# Acessar banco de dados
docker-compose exec db psql -U monitoria_user -d monitoria_db

# Parar tudo e limpar
docker-compose down -v
```

## 🔄 Resetar Tudo

```bash
# Opção 1: Makefile
make reset

# Opção 2: Manual
docker-compose down -v
docker-compose up --build -d
docker-compose exec web python manage.py migrate
docker-compose exec web python setup_project.py
```

## 🆘 Problemas?

### Container não inicia
```bash
docker-compose logs
docker-compose down -v
docker-compose up --build
```

### Porta em uso
Edite `docker-compose.yml` e mude a porta:
```yaml
ports:
  - "8001:8000"  # Mude para 8001
```

### Resetar banco de dados
```bash
docker-compose down -v
docker-compose up -d
docker-compose exec web python manage.py migrate
docker-compose exec web python setup_project.py
```

## 📚 Documentação Completa

Para mais detalhes, consulte:
- **DOCKER_README.md** - Guia completo
- **README.md** - Documentação do projeto

---

✨ **Pronto! Seu ambiente está rodando!**

