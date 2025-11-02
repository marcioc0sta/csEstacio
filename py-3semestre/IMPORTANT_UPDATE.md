# ⚠️ ATUALIZAÇÃO IMPORTANTE - Leia Antes de Executar

## 🔧 Correções Críticas Aplicadas

Dois apps foram renomeados para resolver conflitos de nomes:

1. **`queue` → `queue_management`** (conflito com módulo Python built-in)
2. **`sessions` → `monitoring_sessions`** (conflito com Django built-in)

---

## 🚀 Como Iniciar o Projeto (ATUALIZADO)

### Primeira Vez com Docker:

```bash
# 1. Build e iniciar containers
docker-compose up --build -d

# 2. Aguardar PostgreSQL
sleep 5

# 3. Criar migrations (IMPORTANTE!)
docker-compose run --rm web python manage.py makemigrations

# 4. Aplicar migrations
docker-compose run --rm web python manage.py migrate

# 5. Carregar dados de teste
docker-compose run --rm web python setup_project.py

# 6. Acessar
open http://localhost:8000
```

### OU use o script:

```bash
chmod +x docker-start.sh
./docker-start.sh
```

---

## ✅ URLs Atualizadas no Código

Se você estiver editando o código, note que as URLs mudaram:

**ANTES:**
- `{% url 'sessions:list' %}`
- `{% url 'sessions:detail' %}`
- `{% url 'queue:join' %}`
- `{% url 'queue:my_queue' %}`

**AGORA:**
- `{% url 'monitoring_sessions:list' %}`
- `{% url 'monitoring_sessions:detail' %}`
- `{% url 'queue_management:join' %}`
- `{% url 'queue_management:my_queue' %}`

**As URLs públicas permanecem as mesmas:**
- http://localhost:8000/sessions/ (funciona normalmente)
- http://localhost:8000/queue/ (funciona normalmente)

---

## 📝 Credenciais (Inalteradas)

- **Admin:** admin / admin123
- **Monitor:** monitor1 / monitor123
- **Aluno:** aluno1 / aluno123

---

## 🐛 Se Encontrar Problemas

```bash
# Reset completo
docker-compose down -v
docker-compose up --build -d
docker-compose exec web python manage.py migrate
docker-compose exec web python setup_project.py
```

---

## 📚 Documentação Completa

Para detalhes sobre a correção, consulte: **NAMING_FIX.md**

---

✅ **Tudo pronto para uso!**

