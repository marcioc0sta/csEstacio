#!/bin/bash

# Script para iniciar o projeto com Docker

echo "=========================================="
echo "  Sistema de Monitoria 2.0 - Docker"
echo "=========================================="
echo ""

# Verificar se Docker está rodando
if ! docker info > /dev/null 2>&1; then
    echo "❌ Docker não está rodando!"
    echo "Por favor, inicie o Docker Desktop e tente novamente."
    exit 1
fi

echo "✓ Docker está rodando"
echo ""

# Perguntar se deve reconstruir
read -p "Deseja reconstruir as imagens? (s/N): " rebuild
echo ""

if [[ $rebuild =~ ^[Ss]$ ]]; then
    echo "🔨 Reconstruindo imagens..."
    docker-compose build --no-cache
    echo ""
fi

# Iniciar os containers
echo "🚀 Iniciando containers..."
docker-compose up -d

# Aguardar o banco estar pronto
echo ""
echo "⏳ Aguardando PostgreSQL estar pronto..."
sleep 5

# Criar migrations
echo ""
echo "📝 Criando migrations..."
docker-compose run --rm web python manage.py makemigrations

# Executar migrations
echo ""
echo "📦 Aplicando migrations..."
docker-compose run --rm web python manage.py migrate

# Perguntar se deve carregar dados de teste
echo ""
read -p "Deseja carregar dados de teste? (S/n): " loaddata

if [[ ! $loaddata =~ ^[Nn]$ ]]; then
    echo ""
    echo "📊 Carregando dados de teste..."
    docker-compose run --rm web python setup_project.py
fi

# Coletar static files
echo ""
echo "📁 Coletando arquivos estáticos..."
docker-compose run --rm web python manage.py collectstatic --noinput

echo ""
echo "=========================================="
echo "✅ Aplicação iniciada com sucesso!"
echo "=========================================="
echo ""
echo "🌐 Acesse: http://localhost:8000"
echo "👤 Admin: http://localhost:8000/admin"
echo ""
echo "📋 Credenciais:"
echo "   Admin: admin / admin123"
echo "   Monitor: monitor1 / monitor123"
echo "   Aluno: aluno1 / aluno123"
echo ""
echo "📊 Ver logs: docker-compose logs -f"
echo "🛑 Parar: docker-compose down"
echo ""
echo "=========================================="

