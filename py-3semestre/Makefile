# Makefile para facilitar comandos Docker

.PHONY: help build up down restart logs shell migrate test clean

help:
	@echo "Sistema de Monitoria 2.0 - Comandos Docker"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make build       - Construir as imagens Docker"
	@echo "  make up          - Iniciar os containers"
	@echo "  make down        - Parar os containers"
	@echo "  make restart     - Reiniciar os containers"
	@echo "  make logs        - Ver logs em tempo real"
	@echo "  make shell       - Abrir shell no container web"
	@echo "  make dbshell     - Abrir shell do PostgreSQL"
	@echo "  make migrate     - Executar migrations"
	@echo "  make makemigrations - Criar migrations"
	@echo "  make superuser   - Criar superusuário"
	@echo "  make loaddata    - Carregar dados de teste"
	@echo "  make test        - Executar testes"
	@echo "  make clean       - Limpar containers e volumes"
	@echo "  make reset       - Reset completo (limpa tudo e reconstrói)"

build:
	docker-compose build

up:
	docker-compose up -d
	@echo "✅ Containers iniciados!"
	@echo "🌐 Acesse: http://localhost:8000"

down:
	docker-compose down

restart:
	docker-compose restart

logs:
	docker-compose logs -f

shell:
	docker-compose exec web bash

dbshell:
	docker-compose exec db psql -U monitoria_user -d monitoria_db

migrate:
	docker-compose exec web python manage.py migrate

makemigrations:
	docker-compose exec web python manage.py makemigrations

superuser:
	docker-compose exec web python manage.py createsuperuser

loaddata:
	docker-compose exec web python setup_project.py

collectstatic:
	docker-compose exec web python manage.py collectstatic --noinput

test:
	docker-compose exec web python manage.py test

clean:
	docker-compose down -v
	docker system prune -f

reset: clean
	docker-compose build --no-cache
	docker-compose up -d
	sleep 5
	docker-compose exec web python manage.py migrate
	docker-compose exec web python setup_project.py
	@echo "✅ Reset completo finalizado!"
	@echo "🌐 Acesse: http://localhost:8000"

start: build up migrate loaddata collectstatic
	@echo "✅ Setup completo!"
	@echo "🌐 Acesse: http://localhost:8000"

