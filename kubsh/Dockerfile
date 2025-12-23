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

RUN pip3 install pytest

WORKDIR /workspace

COPY . /workspace/

# Создаем тестовую директорию
RUN mkdir -p /opt/tests/users
RUN chmod a+rw /etc/passwd

# Компилируем проект В ПАПКЕ kubsh
RUN echo "=== Building kubsh ===" && \
    cd kubsh && \
    make && \
    echo "=== Build result ===" && \
    ls -la && \
    echo "=== Binary info ===" && \
    file ./kubsh

# Создаем скрипт для запуска тестов, который ЗНАЕТ где бинарник
RUN echo '#!/bin/bash\n\
cd /workspace/kubsh\n\
echo "=== Current directory for tests: \$(pwd) ==="\n\
ls -la\n\
echo "=== Running unit tests ==="\n\
pytest tests/ -v\n\
echo "=== Memory check ==="\n\
if [ -f "./kubsh" ]; then\n\
    valgrind --leak-check=full --error-exitcode=1 ./kubsh --help 2>&1 | tail -20\n\
else\n\
    echo "ERROR: kubsh binary not found in \$(pwd)!"\n\
    exit 1\n\
fi\n\
echo "=== Basic functionality test ==="\n\
echo "exit" | timeout 5 ./kubsh || true\n\
' > /usr/local/bin/run_tests.sh && chmod +x /usr/local/bin/run_tests.sh

CMD ["/usr/local/bin/run_tests.sh"]
