# 📚 Sistema de Gestão de Monitoria Acadêmica 2.0 - Visão Geral

## 🎯 Objetivo do Projeto

Sistema web desenvolvido em Django para gerenciamento completo de sessões de monitoria acadêmica, facilitando a interação entre monitores e alunos através de agendamentos, filas dinâmicas e sistema de avaliação.

## 🏗️ Arquitetura do Sistema

### Backend
- **Framework:** Django 4.2
- **Banco de Dados:** SQLite (dev) / PostgreSQL (prod)
- **Autenticação:** Django Authentication System
- **Arquitetura:** MVT (Model-View-Template)

### Frontend
- **Framework CSS:** Bootstrap 5.3
- **Ícones:** Bootstrap Icons
- **JavaScript:** Vanilla JS (auto-refresh)
- **Responsividade:** Mobile-first design

## 📦 Estrutura de Apps

### 1. **accounts** - Gestão de Usuários
**Responsabilidade:** Autenticação e perfis de usuários

**Models:**
- `CustomUser`: Usuário customizado com roles (student, monitor, admin)

**Views principais:**
- `register_view`: Cadastro de novos usuários
- `login_view`: Autenticação
- `profile_view`: Visualização de perfil
- `dashboard_view`: Dashboard por tipo de usuário

**Features:**
- Login/Logout/Registro
- Perfis com foto, bio, matrícula
- Dashboards personalizados por role
- Edição de perfil

---

### 2. **sessions** - Sessões de Monitoria
**Responsabilidade:** CRUD de sessões de monitoria e disciplinas

**Models:**
- `Subject`: Disciplinas (código, nome, descrição)
- `MonitoringSession`: Sessões de monitoria (horário, local, monitor)
- `Attendance`: Registro de presença

**Views principais:**
- `session_list`: Lista com filtros e busca
- `session_create/update/delete`: CRUD completo
- `my_sessions`: Sessões do monitor

**Features:**
- Criação de sessões por monitores
- Filtros por disciplina, monitor, dia, status
- Paginação de resultados
- Controle de status (agendada, em andamento, concluída)

---

### 3. **queue** - Fila de Atendimento
**Responsabilidade:** Gerenciamento dinâmico de filas

**Models:**
- `QueueEntry`: Entrada na fila (student, sessão, status, posição)

**Views principais:**
- `join_queue`: Aluno entra na fila
- `session_queue`: Monitor gerencia fila
- `start_service`: Inicia atendimento
- `complete_service`: Finaliza atendimento

**Features:**
- Entrada na fila com descrição da dúvida
- Priorização (baixa, normal, alta, urgente)
- Status: aguardando → em atendimento → concluído
- Auto-reordenação da fila
- Atualização automática a cada 30s

---

### 4. **feedback** - Avaliações
**Responsabilidade:** Sistema de feedback e rankings

**Models:**
- `Feedback`: Avaliação com múltiplos critérios
- `MonitorReport`: Relatórios estatísticos

**Views principais:**
- `submit_feedback`: Aluno avalia atendimento
- `my_feedbacks`: Visualização de avaliações
- `monitor_stats`: Estatísticas do monitor
- `monitors_ranking`: Ranking geral

**Features:**
- Avaliação em 4 critérios (geral, conhecimento, comunicação, paciência)
- Comentários opcionais
- Avaliações anônimas
- Ranking de monitores
- Estatísticas detalhadas

---

## 🔐 Sistema de Permissões

### Aluno (student)
✅ Ver sessões disponíveis  
✅ Entrar em filas  
✅ Cancelar entrada na fila  
✅ Avaliar atendimentos  
✅ Ver ranking de monitores  
❌ Criar sessões  
❌ Gerenciar filas  

### Monitor (monitor)
✅ Tudo que aluno pode  
✅ Criar/editar/excluir próprias sessões  
✅ Gerenciar fila das próprias sessões  
✅ Iniciar/finalizar atendimentos  
✅ Ver estatísticas pessoais  
❌ Criar disciplinas  
❌ Gerenciar outros monitores  

### Administrador (admin)
✅ Tudo que monitor pode  
✅ Acessar painel admin do Django  
✅ Criar/editar disciplinas  
✅ Gerenciar todos os usuários  
✅ Ver todas as sessões e filas  
✅ Excluir qualquer conteúdo  

---

## 📊 Fluxo de Uso Principal

### Fluxo do Aluno
```
1. Cadastro/Login
2. Navegar em "Sessões"
3. Filtrar por disciplina/monitor
4. Ver detalhes da sessão
5. Entrar na fila
6. Aguardar atendimento
7. Ser atendido
8. Avaliar atendimento
```

### Fluxo do Monitor
```
1. Login
2. Criar sessão de monitoria
3. Definir horários e local
4. Acessar fila da sessão
5. Ver alunos aguardando
6. Iniciar atendimento
7. Finalizar atendimento
8. Ver estatísticas e avaliações
```

---

## 🎨 Design System

### Cores Principais
- **Primary:** #4a90e2 (Azul)
- **Success:** #50c878 (Verde)
- **Warning:** #f39c12 (Laranja)
- **Danger:** #e74c3c (Vermelho)

### Componentes
- Cards com hover effects
- Badges para status
- Progress bars para estatísticas
- Rating stars (⭐) para avaliações
- Gradientes nos headers
- Sombras suaves

### Responsividade
- **Mobile:** Menu hambúrguer, cards full-width
- **Tablet:** 2 colunas
- **Desktop:** 3-4 colunas, sidebar

---

## 🔄 Integrações e APIs

### API JSON (queue_status_api)
**Endpoint:** `/queue/api/status/<session_id>/`  
**Método:** GET  
**Resposta:**
```json
{
  "total_waiting": 5,
  "entries": [
    {
      "id": 1,
      "student": "Maria Oliveira",
      "topic": "Dúvida sobre árvores",
      "position": 1,
      "priority": "Normal"
    }
  ]
}
```

---

## 📈 Métricas e Analytics

### Para Monitores
- Avaliação média geral
- Média por critério (conhecimento, comunicação, paciência)
- Total de alunos atendidos
- Total de sessões
- Tempo médio de espera
- Número de avaliações recebidas

### Para Sistema
- Total de usuários
- Total de monitores/alunos
- Sessões ativas
- Atendimentos concluídos
- Rankings

---

## 🚀 Performance

### Otimizações Implementadas
- `select_related()` para reduzir queries N+1
- Paginação em listagens (12 itens por página)
- Índices em campos de busca
- Cache de queries repetitivas
- Lazy loading de imagens

### Tempo de Resposta Esperado
- Homepage: < 200ms
- Lista de sessões: < 300ms
- Dashboard: < 400ms

---

## 🔒 Segurança

### Implementações
- CSRF Protection em todos os forms
- Autenticação baseada em sessão
- Senhas hasheadas (PBKDF2)
- XSS Protection
- Clickjacking Protection
- SQL Injection Protection (Django ORM)

### Recomendações para Produção
- HTTPS obrigatório
- SECRET_KEY em variável de ambiente
- DEBUG=False
- ALLOWED_HOSTS configurado
- Session cookies seguros

---

## 🧪 Testes

### Testes Manuais Recomendados

**Autenticação:**
- [ ] Cadastro com todos os roles
- [ ] Login/Logout
- [ ] Edição de perfil
- [ ] Upload de foto

**Sessões:**
- [ ] Criar sessão como monitor
- [ ] Filtrar sessões
- [ ] Editar/excluir própria sessão
- [ ] Tentar editar sessão de outro (deve falhar)

**Fila:**
- [ ] Entrar na fila como aluno
- [ ] Cancelar entrada
- [ ] Gerenciar fila como monitor
- [ ] Iniciar/finalizar atendimento

**Feedback:**
- [ ] Avaliar atendimento
- [ ] Avaliação anônima
- [ ] Ver estatísticas
- [ ] Ranking de monitores

---

## 📝 Próximas Melhorias (Futuras)

### Funcionalidades
- [ ] Notificações em tempo real (WebSockets)
- [ ] Chat entre aluno e monitor
- [ ] Agendamento de horários específicos
- [ ] Calendário de sessões
- [ ] Exportação de relatórios em PDF
- [ ] API REST completa

### Técnicas
- [ ] Testes automatizados (pytest)
- [ ] CI/CD pipeline
- [ ] Docker containerization
- [ ] Redis para cache
- [ ] Celery para tarefas assíncronas
- [ ] Elasticsearch para busca

---

## 📚 Documentação Adicional

- **README.md:** Documentação principal e instalação
- **QUICKSTART.md:** Guia rápido para começar
- **DEPLOY.md:** Guia completo de deployment
- **requirements.txt:** Dependências Python
- **setup_project.py:** Script de inicialização com dados

---

## 🎓 Aprendizados do Projeto

Este projeto demonstra:
- ✅ CRUD completo em Django
- ✅ Autenticação com múltiplos perfis
- ✅ Relacionamentos complexos entre models
- ✅ Sistema de permissões
- ✅ Interface responsiva moderna
- ✅ Boas práticas de UX
- ✅ Código organizado e documentado
- ✅ Deploy em produção

---

## 📞 Suporte

Para dúvidas ou problemas:
1. Consulte o README.md
2. Verifique o QUICKSTART.md
3. Leia os comentários no código
4. Acesse o painel admin

---

**Desenvolvido com 💙 para otimizar o aprendizado colaborativo!**

