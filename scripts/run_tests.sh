#!/bin/bash
# scripts/run_tests.sh

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Создаем директорию для сборки если её нет
mkdir -p build
cd build

# Конфигурация и сборка
cmake -DBUILD_TESTS=ON ..
if [ $? -ne 0 ]; then
    echo -e "${RED}Failed to configure project${NC}"
    exit 1
fi

make
if [ $? -ne 0 ]; then
    echo -e "${RED}Failed to build project${NC}"
    exit 1
fi

# Запуск тестов
echo "Running tests..."
CTEST_OUTPUT_ON_FAILURE=1 ctest --output-on-failure
TEST_RESULT=$?

if [ $TEST_RESULT -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
else
    echo -e "${RED}Some tests failed!${NC}"
fi

exit $TEST_RESULT