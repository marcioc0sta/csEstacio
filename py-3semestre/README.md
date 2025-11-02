# Sistema de Gestão de Monitoria Acadêmica 2.0

Sistema completo desenvolvido em Django para gerenciamento de sessões de monitoria acadêmica, permitindo interação entre monitores e alunos, agendamento de atendimentos, fila dinâmica e sistema de feedback.

## 🚀 Funcionalidades

### ✅ Autenticação e Perfis
- Sistema completo de registro e login
- Três tipos de perfis: **Aluno**, **Monitor** e **Administrador**
- Perfis personalizáveis com foto, bio, curso e semestre
- Dashboards específicos para cada tipo de usuário

### ✅ Sessões de Monitoria (CRUD Completo)
- Monitores podem criar, editar e excluir sessões
- Definição de horários, dias da semana e locais
- Associação com disciplinas
- Status e controle de sessões ativas

### ✅ Fila de Espera Dinâmica
- Sistema de fila inteligente com posicionamento automático
- Priorização de atendimentos (normal, alta, urgente)
- Controle de status (aguardando, em atendimento, concluído)
- Atualização em tempo real para monitores
- Cancelamento de entradas na fila

### ✅ Feedback e Avaliações
- Sistema completo de avaliação com múltiplos critérios:
  - Avaliação geral
  - Conhecimento do monitor
  - Comunicação
  - Paciência e didática
- Comentários e avaliações anônimas opcionais
- Ranking de monitores baseado em avaliações
- Estatísticas detalhadas para monitores

### ✅ Busca e Filtros
- Filtro por disciplina
- Filtro por nome do monitor
- Filtro por dia da semana
- Filtro por status da sessão
- Sistema de paginação

### ✅ Interface Responsiva
- Design moderno com Bootstrap 5
- Totalmente responsivo para mobile, tablet e desktop
- Ícones Bootstrap Icons
- Gradientes e animações suaves
- UX otimizada

---

## 📋 Requisitos

- **Docker** 20.10+ (recomendado)
- **Docker Compose** 2.0+ (recomendado)
- OU Python 3.8+ e PostgreSQL (instalação manual)

---

## 🐳 Instalação com Docker (Recomendado)

### Pré-requisitos
Certifique-se de ter o Docker e Docker Compose instalados:

```bash
# Verificar versões
docker --version
docker-compose --version
```

### Quick Start

1. **Clone o repositório:**
```bash
cd py-3semestre
```

2. **Execute o script de inicialização:**
```bash
chmod +x docker-start.sh
./docker-start.sh
```

O script irá:
- ✅ Verificar se o Docker está rodando
- ✅ Perguntar se deseja reconstruir as imagens
- ✅ Iniciar os containers (PostgreSQL, Django, Nginx)
- ✅ Aplicar migrações do banco de dados
- ✅ Carregar dados de teste (opcional)
- ✅ Coletar arquivos estáticos

3. **Acesse a aplicação:**
```
🌐 Frontend: http://localhost
📊 Admin:    http://localhost/admin
```

### Credenciais de Teste

Após carregar os dados de teste:

```
👨‍💼 Administrador:
   Usuário: admin
   Senha:   admin123

👨‍🏫 Monitor:
   Usuário: monitor1
   Senha:   monitor123

👨‍🎓 Aluno:
   Usuário: aluno1
   Senha:   aluno123
```

### Comandos Docker Úteis

#### Gerenciamento de Containers

```bash
# Ver logs em tempo real
docker-compose logs -f

# Ver logs apenas do web
docker-compose logs -f web

# Ver status dos containers
docker-compose ps

# Reiniciar um serviço específico
docker-compose restart web
```

#### Banco de Dados

```bash
# Acessar shell do banco PostgreSQL
docker-compose exec db psql -U monitoria_user -d monitoria_db

# Criar novas migrations
docker-compose run --rm web python manage.py makemigrations

# Aplicar migrations
docker-compose run --rm web python manage.py migrate

# Carregar dados de teste novamente
docker-compose run --rm web python setup_project.py
```

#### Manutenção

```bash
# Parar containers (mantém dados)
docker-compose stop

# Parar e remover containers
docker-compose down

# Parar e remover TUDO (incluindo volumes/dados)
docker-compose down -v

# Reconstruir sem cache
docker-compose build --no-cache

# Executar comandos Django
docker-compose run --rm web python manage.py <comando>

# Criar superusuário
docker-compose run --rm web python manage.py createsuperuser
```

#### Scripts de Ajuda

```bash
# Iniciar aplicação (automático)
./docker-start.sh

# Parar aplicação (automático)
./docker-stop.sh
```

---

## 💻 Instalação Manual (Sem Docker)

### 1. Configure o Ambiente

```bash
# Clone o repositório
cd py-3semestre

# Crie ambiente virtual
python -m venv venv

# Ative o ambiente virtual
# Windows
venv\Scripts\activate

# Linux/Mac
source venv/bin/activate
```

### 2. Instale Dependências

```bash
pip install -r requirements.txt
```

### 3. Configure o Banco de Dados

Crie um banco PostgreSQL e configure as variáveis de ambiente:

```bash
# Exemplo de .env
DATABASE_URL=postgresql://usuario:senha@localhost:5432/monitoria_db
SECRET_KEY=seu-secret-key-aqui
DEBUG=True
```

### 4. Execute Migrations

```bash
python manage.py makemigrations
python manage.py migrate
```

### 5. Carregue Dados de Teste

```bash
python setup_project.py
```

### 6. Colete Arquivos Estáticos

```bash
python manage.py collectstatic --noinput
```

### 7. Inicie o Servidor

```bash
python manage.py runserver
```

Acesse: `http://localhost:8000`

---

## 📱 Como Usar

### Para Alunos:
1. Faça login ou cadastre-se como aluno
2. Navegue até "Sessões" para ver as monitorias disponíveis
3. Clique em uma sessão para ver detalhes
4. Entre na fila de atendimento
5. Aguarde ser chamado pelo monitor
6. Após o atendimento, avalie o monitor

### Para Monitores:
1. Faça login ou cadastre-se como monitor
2. Crie suas sessões de monitoria no dashboard
3. Gerencie a fila de atendimento em tempo real
4. Inicie e conclua atendimentos
5. Visualize suas estatísticas e avaliações

### Para Administradores:
1. Acesse o painel administrativo em `/admin`
2. Gerencie usuários, disciplinas e sessões
3. Visualize estatísticas gerais
4. Crie novas disciplinas

---

## 🗂️ Estrutura do Projeto

```
py-3semestre/
├── accounts/              # App de autenticação e usuários
│   ├── models.py         # Modelo CustomUser com roles
│   ├── views.py          # Login, registro, perfis
│   └── forms.py          # Formulários de autenticação
├── monitoring_sessions/   # App de sessões de monitoria
│   ├── models.py         # Sessões, disciplinas, presença
│   ├── views.py          # CRUD de sessões
│   └── forms.py          # Formulários de sessão
├── queue_management/      # App de fila de atendimento
│   ├── models.py         # Fila dinâmica
│   ├── views.py          # Gerenciamento de fila
│   └── forms.py          # Entrada na fila
├── feedback/              # App de avaliações
│   ├── models.py         # Feedbacks e relatórios
│   ├── views.py          # Sistema de avaliação
│   └── forms.py          # Formulários de feedback
├── templates/             # Templates HTML
│   ├── base.html         # Template base
│   ├── home.html         # Página inicial
│   ├── accounts/         # Templates de usuário
│   ├── monitoring_sessions/  # Templates de sessões
│   ├── queue_management/     # Templates de fila
│   └── feedback/         # Templates de feedback
├── monitoria_system/      # Configurações do projeto
│   ├── settings.py       # Configurações Django
│   └── urls.py           # URLs principais
├── docker-compose.yml    # Configuração Docker
├── Dockerfile            # Imagem Docker
├── docker-start.sh       # Script de inicialização
├── docker-stop.sh        # Script de parada
├── nginx.conf            # Configuração Nginx
├── manage.py
├── requirements.txt
└── README.md
```

---

## 🎨 Tecnologias Utilizadas

- **Backend:** Django 4.2
- **Frontend:** Bootstrap 5, Bootstrap Icons
- **Banco de Dados:** PostgreSQL
- **Web Server:** Nginx
- **WSGI Server:** Gunicorn
- **Containerização:** Docker, Docker Compose
- **Autenticação:** Django Auth System

---

## 🚀 Deploy em Produção

### Configurar Variáveis de Ambiente

Edite o `docker-compose.yml` para produção:

```yaml
environment:
  - DEBUG=False
  - SECRET_KEY=<sua-chave-secreta-forte>
  - ALLOWED_HOSTS=seu-dominio.com,www.seu-dominio.com
  - DATABASE_URL=postgresql://...
```

### Usar Nginx em Produção

```bash
# Iniciar com perfil de produção
docker-compose --profile production up -d

# Isso iniciará também o Nginx
```

### Backup do Banco de Dados

```bash
# Fazer backup
docker-compose exec db pg_dump -U monitoria_user monitoria_db > backup.sql

# Restaurar backup
docker-compose exec -T db psql -U monitoria_user monitoria_db < backup.sql
```

### Monitoramento

```bash
# Ver uso de recursos
docker stats

# Ver logs de erro
docker-compose logs --tail=100 web | grep ERROR
```

---

## 🔧 Desenvolvimento

### Adicionar Novos Pacotes

```bash
# Instalar novo pacote
docker-compose run --rm web pip install <pacote>

# Atualizar requirements.txt
docker-compose run --rm web pip freeze > requirements.txt
```

### Debugging

```bash
# Entrar no container
docker-compose exec web sh

# Executar shell Django
docker-compose run --rm web python manage.py shell

# Verificar logs de erros
docker-compose logs web | grep -i error
```

---

## 📊 Funcionalidades Técnicas

### Segurança
- CSRF Protection
- Autenticação baseada em sessão
- Senhas hasheadas com PBKDF2
- Permissões baseadas em roles
- Variáveis de ambiente para secrets

### Performance
- Queries otimizadas com select_related
- Paginação em listagens
- Static files servidos via Nginx
- Cache-Control headers
- PostgreSQL como banco principal

### Boas Práticas
- Código organizado em apps
- Templates reutilizáveis
- Forms validation
- Messages framework
- Responsive design
- Docker containerização
- Health checks

---

## 🤝 Contribuindo

Este é um projeto acadêmico, mas sugestões são bem-vindas!

## 📝 Licença

Este projeto foi desenvolvido para fins educacionais.

## 👨‍💻 Autor

Desenvolvido como trabalho individual da disciplina de Desenvolvimento Web com Django.

---

**Sistema de Gestão de Monitoria Acadêmica 2.0** - Otimizando o aprendizado colaborativo! 📚✨
