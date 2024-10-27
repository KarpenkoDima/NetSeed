
#ifndef __NETSEED_MEMORY_TYPES_H__
#define __NETSEED_MEMORY_TYPES_H__

#include <stddef.h>
#include <stdint.h>

#define MAX_POOLS 4

// Структура для отслеживания блока памяти
typedef struct mem_block {
	struct mem_block* next;	// Сдедующий блок в списке
	size_t size;			// Размер блока
	uint8_t in_use;			// Флаг использования
	uint8_t pool_id;		// ID пула
} mem_block_t;

typedef struct buffer_pool {
	mem_block_t* blocks;	// Массив блоков
	size_t block_size;		// Размер каждого блока
	size_t total_blocks;	// Общее количествоблоков
	size_t free_blocks;		// Количество свободных блоков
	uint8_t pool_id;		// Уникальный ID пула
}buffer_pool_t;

//
typedef struct {
	buffer_pool_t pools[MAX_POOLS]; // Массив пулов
	size_t pool_count;				// Количество пулов
	void* heap_start;				// Начало кучи для динамического выдиления памяти
	size_t heap_size;				// Размер кучи
	size_t heap_used;				// Использовано памяти
}memory_manager_t;

//статистика использования памяти
typedef struct {
	size_t total_memory;		// Общий объем памяти
	size_t used_memory;			// Использование памяти
	size_t free_memory;			// Свободная память
	size_t fragmentation;		// Процент фрагментации
} mem_stats_t;
#endif // !__NETSEED_MEMORY_TYPES_H___

