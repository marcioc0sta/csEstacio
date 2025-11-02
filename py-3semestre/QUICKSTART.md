# 🚀 Guia Rápido de Inicialização

## Passo a Passo para Rodar o Projeto

### 1. Instalar Dependências
```bash
pip install -r requirements.txt
```

### 2. Executar Migrações
```bash
python manage.py makemigrations
python manage.py migrate
```

### 3. Carregar Dados de Teste
```bash
python setup_project.py
```

Este comando criará:
- 1 administrador
- 3 monitores
- 3 alunos
- 5 disciplinas
- 5 sessões de monitoria

### 4. Iniciar o Servidor
```bash
python manage.py runserver
```

### 5. Acessar o Sistema
Abra seu navegador em: **http://localhost:8000**

## 🔑 Credenciais de Acesso

### Administrador
- **Usuário:** `admin`
- **Senha:** `admin123`
- **Acesso ao painel admin:** http://localhost:8000/admin

### Monitores
- **monitor1** / monitor123 (João Silva - Estruturas de Dados)
- **monitor2** / monitor123 (Ana Santos - Banco de Dados)
- **monitor3** / monitor123 (Carlos Lima - POO e Web)

### Alunos
- **aluno1** / aluno123 (Maria Oliveira)
- **aluno2** / aluno123 (Pedro Costa)
- **aluno3** / aluno123 (Julia Mendes)

## 📝 Testando Funcionalidades

### Como Aluno:
1. Login com `aluno1` / `aluno123`
2. Vá em "Sessões" → Escolha uma sessão
3. Clique em "Entrar na Fila"
4. Preencha sua dúvida e entre na fila
5. Acompanhe seu status em "Minha Fila"

### Como Monitor:
1. Login com `monitor1` / `monitor123`
2. Vá em "Minhas Sessões" ou Dashboard
3. Clique em "Ver Fila" em uma sessão
4. Gerencie os atendimentos (Iniciar/Concluir)
5. Veja suas estatísticas em "Estatísticas"

### Como Admin:
1. Login com `admin` / `admin123`
2. Acesse `/admin` para o painel administrativo
3. Gerencie usuários, sessões e disciplinas
4. Visualize estatísticas gerais no dashboard

## 🆘 Problemas Comuns

### Erro de Migração
```bash
python manage.py makemigrations
python manage.py migrate --run-syncdb
```

### Recriar Banco de Dados
```bash
# Remover banco existente
rm db.sqlite3

# Recriar tudo
python manage.py migrate
python setup_project.py
```

### Criar Superusuário Manualmente
```bash
python manage.py createsuperuser
```

## 📚 Documentação Completa
Consulte o arquivo **README.md** para documentação detalhada.

---
✨ **Pronto para usar!** Aproveite o sistema de monitoria!

