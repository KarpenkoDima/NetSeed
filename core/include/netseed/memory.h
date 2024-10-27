#pragma once
#include "memory_types.h"
#ifndef __NETSEED_MEMORY_H__
#define __NETSEED_MEMORY_H__
#include "memory_types.h"

// инициалзпция менеджера памяти
void mem_init(memory_manager_t* mm, void* heap, size_t heap_size);

// Создание нового пула буферров
int mem_create_pool(memory_manager_t* mm, size_t block_size, size_t block_count);

// Выделение памяти из подходящего пула
void* mem_alloc(memory_manager_t* mm, size_t size);

// Освобождение памяти
void mem_free(memory_manager_t* mm, void* ptr);

// Получение статистики о менеджере памяти
void mem_get_stats(memory_manager_t* mm, mem_stats_t* stats);
#endif