#!/bin/bash

# Script para parar o projeto Docker

echo "🛑 Parando containers do Sistema de Monitoria..."
echo ""

# Parar containers
docker-compose down

echo ""
echo "✅ Containers parados!"
echo ""
read -p "Deseja remover os volumes (dados do banco)? (s/N): " remove_volumes

if [[ $remove_volumes =~ ^[Ss]$ ]]; then
    echo ""
    echo "🗑️  Removendo volumes..."
    docker-compose down -v
    echo "✅ Volumes removidos!"
fi

echo ""
echo "Até logo! 👋"

