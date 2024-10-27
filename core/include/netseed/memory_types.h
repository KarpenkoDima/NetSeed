
#ifndef __NETSEED_MEMORY_TYPES_H__
#define __NETSEED_MEMORY_TYPES_H__

#include <stddef.h>
#include <stdint.h>

#define MAX_POOLS 4

// ��������� ��� ������������ ����� ������
typedef struct mem_block {
	struct mem_block* next;	// ��������� ���� � ������
	size_t size;			// ������ �����
	uint8_t in_use;			// ���� �������������
	uint8_t pool_id;		// ID ����
} mem_block_t;

typedef struct buffer_pool {
	mem_block_t* blocks;	// ������ ������
	size_t block_size;		// ������ ������� �����
	size_t total_blocks;	// ����� ����������������
	size_t free_blocks;		// ���������� ��������� ������
	uint8_t pool_id;		// ���������� ID ����
}buffer_pool_t;

//
typedef struct {
	buffer_pool_t pools[MAX_POOLS]; // ������ �����
	size_t pool_count;				// ���������� �����
	void* heap_start;				// ������ ���� ��� ������������� ��������� ������
	size_t heap_size;				// ������ ����
	size_t heap_used;				// ������������ ������
}memory_manager_t;

//���������� ������������� ������
typedef struct {
	size_t total_memory;		// ����� ����� ������
	size_t used_memory;			// ������������� ������
	size_t free_memory;			// ��������� ������
	size_t fragmentation;		// ������� ������������
} mem_stats_t;
#endif // !__NETSEED_MEMORY_TYPES_H___

