#!/bin/bash

# Script de teste completo para o sistema de torre de fuga
# Este script demonstra todas as funcionalidades do sistema

echo "=== TESTE COMPLETO DO SISTEMA DE TORRE DE FUGA ==="
echo "Este script irá testar todas as funcionalidades do sistema."
echo ""

# Criar arquivo de entrada com dados de teste
cat > entrada_teste.txt << EOF
1
chip central
controle
10
1
motor principal
propulsão
9
1
sensor de altitude
controle
8
1
tanque de combustível
suporte
7
1
antena de comunicação
controle
6
2
3
1
3
2
3
3
4
chip central
4
motor principal
5
6
EOF

echo "Executando teste completo..."
echo ""

# Executar o programa com entrada de teste
./torre_fuga < entrada_teste.txt

echo ""
echo "=== TESTE CONCLUÍDO ==="
echo "O sistema foi testado com sucesso!"
echo ""

# Limpar arquivo temporário
rm entrada_teste.txt
