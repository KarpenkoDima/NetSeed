#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../../../core/include/netseed/memory.h"

#define TEST_HEAP_SIZE (1024 * 1024) // 1MB
#define TEST_ITERATIONS 1000

// 
typedef struct {
	char data[256];
	size_t size;
}test_data_t;

//
void fill_test_data(void* ptr, size_t size, int pattern) {
	memset(ptr, pattern, size);
}

//
int verify_test_data(void* ptr, size_t size, int pattern)
{
	unsigned char* data = (unsigned char*)ptr;
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] != pattern)
		{
			return 0;
		}		
	}
	return 1;
}

	// 
void test_basic_alloc_free() {
	printf("Running basic allocation/free test ...\n");

	// Инициализация
	static uint8_t heap[TEST_HEAP_SIZE];
	memory_manager_t mm;
	mem_init(&mm, heap, TEST_HEAP_SIZE);

	// Создание пула
	int pool_id = mem_create_pool(&mm, 128, 10);
	assert(pool_id >= 0);

	// Тест выделения
	void* ptr = mem_alloc(&mm, 64);
	assert(ptr != NULL);

	// Заполнение и проверка данных
	fill_test_data(ptr, 64, 0xAA);
	assert(verify_test_data(ptr, 64, 0xAA));

	//Освобождение
	mem_free(&mm, ptr);

	printf("Basic allocation/free test passed\n");
}

int main() {
	printf("Starting memory manager tests...\n");

	test_basic_alloc_free();


	printf("All test passed successfully\n");
	return 0;
}