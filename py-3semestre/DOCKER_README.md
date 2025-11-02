# 🐳 Docker Setup - Sistema de Monitoria 2.0

## 📋 Pré-requisitos

- Docker Desktop instalado ([download](https://www.docker.com/products/docker-desktop))
- Docker Compose (incluído no Docker Desktop)

## 🚀 Início Rápido

### 1. Construir e Iniciar os Containers

```bash
# Construir as imagens e iniciar os serviços
docker-compose up --build
```

### 2. Acessar a Aplicação

Abra seu navegador em: **http://localhost:8000**

### 3. Parar os Containers

```bash
# Parar os containers (mantém os dados)
docker-compose down

# Parar e remover volumes (remove os dados)
docker-compose down -v
```

## 🔧 Comandos Úteis

### Visualizar Logs
```bash
# Todos os serviços
docker-compose logs -f

# Apenas o Django
docker-compose logs -f web

# Apenas o PostgreSQL
docker-compose logs -f db
```

### Executar Comandos Django
```bash
# Migrations
docker-compose exec web python manage.py migrate

# Criar superusuário
docker-compose exec web python manage.py createsuperuser

# Carregar dados de teste
docker-compose exec web python setup_project.py

# Shell Django
docker-compose exec web python manage.py shell

# Coletar static files
docker-compose exec web python manage.py collectstatic --noinput
```

### Acessar o Container
```bash
# Bash no container web
docker-compose exec web bash

# Shell do PostgreSQL
docker-compose exec db psql -U monitoria_user -d monitoria_db
```

### Reconstruir Containers
```bash
# Reconstruir após mudanças no código
docker-compose up --build

# Forçar reconstrução completa
docker-compose build --no-cache
docker-compose up
```

## 📦 Estrutura de Serviços

### 1. **db** (PostgreSQL)
- **Imagem:** postgres:15-alpine
- **Porta:** 5432
- **Banco:** monitoria_db
- **Usuário:** monitoria_user
- **Senha:** monitoria_pass123
- **Volume:** postgres_data (persistente)

### 2. **web** (Django)
- **Build:** Dockerfile local
- **Porta:** 8000
- **Comando:** Gunicorn com 3 workers
- **Volumes:**
  - Código fonte: `/app`
  - Static files: `static_volume`
  - Media files: `media_volume`

### 3. **nginx** (Opcional - Produção)
- **Imagem:** nginx:alpine
- **Porta:** 80
- **Profile:** production
- **Serve:** Static e Media files

## 🔐 Credenciais Padrão

### PostgreSQL
- **Host:** db (ou localhost:5432 do host)
- **Database:** monitoria_db
- **User:** monitoria_user
- **Password:** monitoria_pass123

### Django Admin (após setup_project.py)
- **Usuário:** admin
- **Senha:** admin123

## 🌍 Variáveis de Ambiente

Edite `docker-compose.yml` ou crie um arquivo `.env` na raiz:

```env
DEBUG=True
SECRET_KEY=sua-chave-secreta
POSTGRES_DB=monitoria_db
POSTGRES_USER=monitoria_user
POSTGRES_PASSWORD=monitoria_pass123
```

## 🎯 Modos de Execução

### Desenvolvimento (Padrão)
```bash
docker-compose up
```
- Django em modo debug
- Sem Nginx
- Hot-reload habilitado

### Produção (com Nginx)
```bash
docker-compose --profile production up
```
- Nginx como proxy reverso
- Static/Media servidos pelo Nginx
- Debug desabilitado

## 🔄 Fluxo de Desenvolvimento

### Primeira Execução
```bash
# 1. Construir e iniciar
docker-compose up --build

# 2. Em outro terminal, carregar dados
docker-compose exec web python setup_project.py
```

### Desenvolvimento Diário
```bash
# Iniciar containers
docker-compose up

# Fazer alterações no código (hot-reload automático)

# Se adicionar dependências ao requirements.txt
docker-compose up --build

# Ao terminar
docker-compose down
```

### Após Mudanças no Modelo
```bash
# Criar migrations
docker-compose exec web python manage.py makemigrations

# Aplicar migrations
docker-compose exec web python manage.py migrate
```

## 🗃️ Gerenciamento de Dados

### Backup do Banco de Dados
```bash
# Exportar dump
docker-compose exec db pg_dump -U monitoria_user monitoria_db > backup.sql

# Restaurar dump
docker-compose exec -T db psql -U monitoria_user monitoria_db < backup.sql
```

### Resetar Banco de Dados
```bash
# Parar containers e remover volumes
docker-compose down -v

# Reconstruir e recriar tudo
docker-compose up --build

# Carregar dados novamente
docker-compose exec web python setup_project.py
```

### Acessar Dados Persistentes
```bash
# Listar volumes
docker volume ls

# Inspecionar volume
docker volume inspect py-3semestre_postgres_data

# Remover volume específico
docker volume rm py-3semestre_postgres_data
```

## 🐛 Troubleshooting

### Container não inicia
```bash
# Ver logs detalhados
docker-compose logs

# Verificar status
docker-compose ps

# Remover tudo e recomeçar
docker-compose down -v
docker-compose up --build
```

### Erro de conexão com banco
```bash
# Verificar se o PostgreSQL está rodando
docker-compose ps db

# Ver logs do PostgreSQL
docker-compose logs db

# Reiniciar apenas o banco
docker-compose restart db
```

### Mudanças no código não aparecem
```bash
# Verificar se o volume está montado
docker-compose config

# Reconstruir a imagem
docker-compose up --build
```

### Porta já em uso
```bash
# Mudar porta no docker-compose.yml
ports:
  - "8001:8000"  # Host:Container
```

### Erro de permissão
```bash
# Linux: dar permissão aos volumes
sudo chown -R $USER:$USER .
```

## 📊 Monitoramento

### Ver uso de recursos
```bash
# Estatísticas em tempo real
docker stats

# Apenas containers do projeto
docker stats monitoria_web monitoria_db
```

### Inspecionar containers
```bash
# Informações detalhadas
docker-compose exec web python manage.py check
docker-compose exec web python manage.py check --deploy
```

## 🚢 Deploy em Produção

### Usando Docker Compose
```bash
# 1. Atualizar docker-compose.yml para produção
# 2. Definir variáveis de ambiente seguras
# 3. Usar profile production

docker-compose --profile production up -d

# 4. Verificar se está rodando
docker-compose ps
```

### Usando Docker Swarm/Kubernetes
Veja documentação específica para orquestração de containers.

## 📝 Boas Práticas

### Segurança
- ✅ Nunca commitar senhas reais
- ✅ Usar secrets do Docker em produção
- ✅ Mudar SECRET_KEY e senhas
- ✅ Desabilitar DEBUG em produção
- ✅ Usar HTTPS (com Nginx + Let's Encrypt)

### Performance
- ✅ Usar volumes nomeados para dados persistentes
- ✅ Multi-stage builds para imagens menores
- ✅ Cache de layers do Docker
- ✅ .dockerignore otimizado

### Desenvolvimento
- ✅ Hot-reload para desenvolvimento
- ✅ Volumes montados para código
- ✅ Logs acessíveis
- ✅ Health checks configurados

## 🔗 Links Úteis

- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose Documentation](https://docs.docker.com/compose/)
- [PostgreSQL Docker Hub](https://hub.docker.com/_/postgres)
- [Django Deployment Checklist](https://docs.djangoproject.com/en/4.2/howto/deployment/checklist/)

## 🆘 Suporte

### Logs importantes para debug:
```bash
# Ver tudo
docker-compose logs -f

# Últimas 100 linhas
docker-compose logs --tail=100

# Desde timestamp
docker-compose logs --since 2023-01-01T00:00:00
```

### Limpeza completa:
```bash
# Remover tudo (cuidado!)
docker-compose down -v --rmi all
docker system prune -a --volumes
```

---

🐳 **Docker Setup Completo!** Agora você pode desenvolver e deployar com facilidade!

