
#include "netseed/memory_types.h"

// ������������ ��������� ������
void mem_init(memory_manager_t* mm, void* heap, size_t heap_size) {
	mm->heap_start = heap;
	mm->heap_size = heap_size;
	mm->pool_count = 0;
	mm->heap_used = 0;
}

// �������� ������ ���� ��������
int mem_create_pool(memory_manager_t* mm, size_t block_size, size_t block_count) {
	if (mm->pool_count >= MAX_POOLS)
	{
		return -1; // �������� �����
	}

	buffer_pool_t* pool = &mm->pools[mm->pool_count];
	size_t total_size = block_size * block_count + sizeof(mem_block_t) * block_count;

	// ���������, ���������� �� ��������� ������ 
	if (total_size > mm->heap_size - mm->heap_used)
	{
		return -1; // ��������� ������
	}

	// ��������� ������ ��� ��� �� ����
	pool->blocks = (mem_block_t*)mm->heap_start;
	pool->block_size = block_size;
	pool->total_blocks = block_count;
	pool->free_blocks = block_count;
	pool->pool_id = mm->pool_count;

	// ������������� �����
	mem_block_t* current = pool->blocks;
	for (size_t i = 0; i < block_count; i++)
	{
		current->size = block_size;
		current->in_use = 0;
		current->pool_id = pool->pool_id;
		current->next = (i < block_count - 1) ? (mem_block_t*)((char*)current + block_size + sizeof(mem_block_t)) : NULL;
	}
	mm->heap_used += total_size;
	mm->pool_count++;
	return pool->pool_id;

}

// ��������� ������ �� ����������� ����
void* mem_alloc(memory_manager_t* mm, size_t size) {
	// ����� ����������� ����
	for (size_t i = 0; i < mm->pool_count; i++)
	{
		buffer_pool_t* pool = &mm->pools[i];
		if (pool->block_size >= size && pool->free_blocks > 0)
		{
			// ����� ���������� �����
			mem_block_t* block = pool->blocks;
			while (block)
			{
				if (!block->in_use)
				{
					block->in_use = 1;
					pool->free_blocks--;
					// ���������� ��������� �� ������ ����� ��������� �����
					return (void*)(block + 1);
				}
				block = block->next;
			}
		}
	}
	return NULL; // ��� ��������� ������
}

// ������������ ������
void mem_free(memory_manager_t* mm, void* ptr) {
	if (!ptr)
	{
		return;
	}

	// �������� ��������� �����
	mem_block_t* block = ((mem_block_t*)ptr) - 1;

	// ��������� ������������ ���������
	if (block->pool_id >= mm->pool_count)
	{
		return;
	}

	//����������� ����
	buffer_pool_t* pool = &mm->pools[block->pool_id];
	if (block->in_use)
	{
		block->in_use = 0;
		pool->free_blocks++;
	}
}

// ��������� ���������� � ��������� ������
void mem_get_stats(memory_manager_t* mm, mem_stats_t* stats) {
	stats->total_memory = 0;
	stats->used_memory = 0;
	stats->free_memory = 0;

	for (size_t i = 0; i < mm->pool_count; i++)
	{
		buffer_pool_t* pool = &mm->pools[i];
		size_t pool_total = pool->block_size * pool->total_blocks;
		stats->total_memory += pool_total;
		stats->used_memory += pool->block_size * (pool->total_blocks - pool->free_blocks);
		stats->free_memory += pool->block_size * pool->free_blocks;
	}

	//
	stats->fragmentation = (stats->free_memory > 0) ? 
		(stats->total_memory - stats->used_memory) * 100 / stats->free_memory 
		: 0;
}
