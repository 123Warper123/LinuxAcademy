FROM ubuntu:22.04

# Установка системных зависимостей
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    cmake \
    make \
    autoconf \
    automake \
    libtool \
    pkg-config \
    python3 \
    python3-pip \
    git \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

# Устанавливаем pytest и зависимости для тестов
RUN pip3 install pytest

# Создаем рабочую директорию
WORKDIR /workspace

# Копируем исходный код
COPY . /workspace/

# Создаем тестовую директорию
RUN mkdir -p /opt/tests/users

# Разрешаем запись в /etc/passwd для тестов
RUN chmod a+rw /etc/passwd

# Компилируем проект
RUN make

# Создаем скрипт для запуска тестов
RUN echo '#!/bin/bash\n\
cd /workspace\n\
echo "=== Running unit tests ==="\n\
pytest tests/ -v\n\
echo "=== Memory check ==="\n\
valgrind --leak-check=full --error-exitcode=1 ./kubsh --help 2>&1 | tail -20\n\
echo "=== Basic functionality test ==="\n\
echo "exit" | timeout 5 ./kubsh || true\n\
' > /usr/local/bin/run_tests.sh && chmod +x /usr/local/bin/run_tests.sh

CMD ["/usr/local/bin/run_tests.sh"]
