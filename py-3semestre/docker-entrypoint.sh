#!/bin/sh

# Exit on error
set -e

echo "Waiting for PostgreSQL to be ready..."
# Only wait if POSTGRES_HOST is set (Docker Compose)
if [ -n "$POSTGRES_HOST" ]; then
    while ! nc -z $POSTGRES_HOST $POSTGRES_PORT; do
        sleep 0.1
    done
    echo "PostgreSQL is ready!"
else
    echo "No POSTGRES_HOST set, assuming external database (Render/Railway)"
fi

echo "Running migrations..."
python manage.py migrate --noinput

echo "Collecting static files..."
python manage.py collectstatic --noinput

echo "Loading initial data (if needed)..."
python setup_project.py || echo "Initial data already loaded or error occurred"

echo "Starting Gunicorn..."
exec gunicorn --bind 0.0.0.0:8000 --workers 3 monitoria_system.wsgi:application

