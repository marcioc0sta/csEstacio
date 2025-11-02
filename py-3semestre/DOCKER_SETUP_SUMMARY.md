# 🐳 Docker Setup - Resumo Completo

## 📦 Arquivos Docker Criados

### 1. **Dockerfile**
Container principal da aplicação Django
- Base: Python 3.11-slim
- PostgreSQL client instalado
- Gunicorn com 3 workers
- Porta 8000 exposta

### 2. **docker-compose.yml**
Orquestração de serviços
- **db:** PostgreSQL 15
- **web:** Django app
- **nginx:** Proxy reverso (opcional, profile production)

### 3. **nginx.conf**
Configuração do Nginx para produção
- Proxy para Django
- Serve static e media files
- Cache configurado

### 4. **.dockerignore**
Arquivos ignorados no build
- Cache Python
- Virtual envs
- Banco SQLite
- Arquivos temporários

### 5. **docker-entrypoint.sh**
Script de inicialização
- Aguarda PostgreSQL
- Executa migrations
- Coleta static files
- Carrega dados iniciais

### 6. **Configuração do Banco**
`settings.py` atualizado para suportar:
- PostgreSQL via DATABASE_URL
- Fallback para SQLite localmente
- Variáveis de ambiente

## 🚀 Scripts de Automação

### 1. **docker-start.sh**
Script interativo para iniciar tudo
- Verifica Docker
- Reconstrói se necessário
- Executa migrations
- Carrega dados de teste
- Mostra credenciais

### 2. **docker-stop.sh**
Script para parar containers
- Para containers
- Opção de remover volumes

### 3. **Makefile**
Comandos facilitados
```bash
make start      # Inicia tudo
make logs       # Ver logs
make shell      # Bash no container
make migrate    # Migrations
make reset      # Reset completo
```

## 🗃️ Configuração do PostgreSQL

### Credenciais Padrão
```
Host: db (ou localhost:5432)
Database: monitoria_db
User: monitoria_user
Password: monitoria_pass123
```

### Acesso ao Banco
```bash
# Via Docker
docker-compose exec db psql -U monitoria_user -d monitoria_db

# Via host (se porta exposta)
psql -h localhost -p 5432 -U monitoria_user -d monitoria_db
```

## 📊 Volumes Persistentes

### postgres_data
Dados do PostgreSQL
```bash
docker volume inspect py-3semestre_postgres_data
```

### static_volume
Arquivos estáticos (CSS, JS)

### media_volume
Uploads de usuários (fotos de perfil)

## 🔧 Comandos Principais

### Iniciar Projeto (Primeira Vez)
```bash
# Método 1: Script
./docker-start.sh

# Método 2: Makefile
make start

# Método 3: Manual
docker-compose up --build -d
docker-compose exec web python manage.py migrate
docker-compose exec web python setup_project.py
```

### Uso Diário
```bash
# Iniciar
docker-compose up -d

# Ver logs
docker-compose logs -f web

# Parar
docker-compose down
```

### Desenvolvimento
```bash
# Shell Django
docker-compose exec web python manage.py shell

# Criar migrations
docker-compose exec web python manage.py makemigrations

# Aplicar migrations
docker-compose exec web python manage.py migrate

# Criar superusuário
docker-compose exec web python manage.py createsuperuser
```

### Manutenção
```bash
# Ver status
docker-compose ps

# Reiniciar serviço
docker-compose restart web

# Reconstruir imagem
docker-compose build --no-cache web

# Ver uso de recursos
docker stats
```

### Backup e Restore
```bash
# Backup do banco
docker-compose exec db pg_dump -U monitoria_user monitoria_db > backup.sql

# Restore
docker-compose exec -T db psql -U monitoria_user monitoria_db < backup.sql
```

### Limpeza
```bash
# Parar e remover volumes
docker-compose down -v

# Limpar sistema Docker
docker system prune -a --volumes

# Reset completo
make reset
```

## 🌐 URLs e Portas

### Desenvolvimento
- **Django:** http://localhost:8000
- **Admin:** http://localhost:8000/admin
- **PostgreSQL:** localhost:5432

### Com Nginx (Production)
```bash
docker-compose --profile production up
```
- **Nginx:** http://localhost:80
- **Django:** (interno) web:8000

## 🔐 Variáveis de Ambiente

Configuráveis no `docker-compose.yml`:

```yaml
environment:
  - DEBUG=True
  - SECRET_KEY=sua-chave
  - DATABASE_URL=postgresql://...
  - POSTGRES_HOST=db
  - POSTGRES_PORT=5432
  - POSTGRES_DB=monitoria_db
  - POSTGRES_USER=monitoria_user
  - POSTGRES_PASSWORD=monitoria_pass123
```

## 🎯 Modos de Execução

### Desenvolvimento (Padrão)
```bash
docker-compose up
```
- DEBUG=True
- Hot-reload
- SQLite ou PostgreSQL
- Sem Nginx

### Produção
```bash
docker-compose --profile production up
```
- DEBUG=False
- PostgreSQL obrigatório
- Nginx como proxy
- Static/Media via Nginx

## 📈 Performance

### Otimizações Implementadas
- Multi-stage build
- .dockerignore otimizado
- Cache de layers
- Volumes nomeados
- Health checks
- Connection pooling (600s)

### Recursos Padrão
- **Web:** 3 workers Gunicorn
- **PostgreSQL:** 100 conexões max
- **Memory:** Sem limite (ajustável)

## 🆘 Troubleshooting

### Container web não inicia
```bash
docker-compose logs web
docker-compose down
docker-compose up --build
```

### Erro de conexão com banco
```bash
# Verificar se db está rodando
docker-compose ps db

# Reiniciar banco
docker-compose restart db

# Ver logs do banco
docker-compose logs db
```

### Migrations não aplicam
```bash
docker-compose exec web python manage.py migrate --run-syncdb
docker-compose exec web python manage.py showmigrations
```

### Porta já em uso
Edite `docker-compose.yml`:
```yaml
ports:
  - "8001:8000"  # Muda para 8001
```

### Reset completo
```bash
docker-compose down -v
docker volume prune -f
docker-compose up --build
```

## 📚 Documentação

1. **DOCKER_QUICKSTART.md** - Início rápido (5 min)
2. **DOCKER_README.md** - Documentação completa
3. **DOCKER_SETUP_SUMMARY.md** - Este arquivo
4. **README.md** - Documentação geral do projeto

## ✅ Checklist de Setup

- [ ] Docker Desktop instalado
- [ ] Dar permissão aos scripts: `chmod +x docker-start.sh docker-stop.sh`
- [ ] Executar: `./docker-start.sh`
- [ ] Acessar: http://localhost:8000
- [ ] Login com: admin / admin123
- [ ] Testar funcionalidades

## 🎓 Vantagens do Docker

### Para Desenvolvimento
✅ Ambiente isolado e reproduzível  
✅ Mesma configuração para todo o time  
✅ Setup em 5 minutos  
✅ Fácil de resetar  
✅ PostgreSQL sem instalação local  

### Para Produção
✅ Deploy consistente  
✅ Fácil escalabilidade  
✅ Rollback simples  
✅ Logs centralizados  
✅ Health checks automáticos  

## 🚀 Deploy em Produção

### Docker Swarm
```bash
docker swarm init
docker stack deploy -c docker-compose.yml monitoria
```

### Kubernetes
```bash
# Criar deployment
kubectl apply -f k8s/

# Ver status
kubectl get pods
```

### Docker Machine (VM remota)
```bash
docker-machine create --driver digitalocean monitoria-prod
docker-machine env monitoria-prod
eval $(docker-machine env monitoria-prod)
docker-compose up -d
```

## 💡 Dicas

1. **Use `make`** para comandos rápidos
2. **Logs em tempo real:** `docker-compose logs -f`
3. **Backup regular:** Automatize com cron
4. **Monitoramento:** Adicione Prometheus/Grafana
5. **CI/CD:** Integre com GitHub Actions

## 🔗 Links Úteis

- [Docker Docs](https://docs.docker.com/)
- [Docker Compose Docs](https://docs.docker.com/compose/)
- [PostgreSQL on Docker](https://hub.docker.com/_/postgres)
- [Django Deployment](https://docs.djangoproject.com/en/4.2/howto/deployment/)

---

🐳 **Setup Docker Completo!** 

Qualquer dúvida, consulte a documentação ou execute:
```bash
make help
```

