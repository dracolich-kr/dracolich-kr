#pragma once

#include <Pch.h>

using ObjectIndex = int;
using ThreadId = DWORD;


struct ObjectHeader
{
	ThreadId m_threadid = 0;
};

template<class T, size_t BLOCK_SIZE = 1024>
class ObjectBuffer : private std::deque<T>
{
public:
	ObjectBuffer() 
	{
		m_alloc_size = sizeof(T) + sizeof(ObjectHeader);
	}

	T* Pop()
	{
		if (this->empty() == true)
			allocate();

		m_use_count++;
		return this->pop_front();
	}

	void PushBack(T* block)
	{
		m_use_count--;
		this->push_back(block);
	}

private:
	void allocate()
	{
		BYTE* page = new BYTE[m_alloc_size * BLOCK_SIZE];
		
		for (int index = 0; index < BLOCK_SIZE; ++index)
		{
			BYTE* buffer = page;
			ObjectHeader* header = (ObjectHeader*)buffer;
			header->m_threadid = (int)GetCurrentThreadId();
			buffer += sizeof(ObjectHeader);
			this->push_back(buffer);

			page += m_alloc_size;
		}
	}

private:
	int m_use_count = 0;
	int m_alloc_size = 0;
};

template <class T>
class ObjectPool
{
public:
	ObjectPool() {}
	virtual ~ObjectPool() {}

	T* Alloc();
	void DeAlloc(void *free);

private:
	concurrency::concurrent_unordered_map<ThreadId, ObjectBuffer<T>*> m_buffer;
	int m_pool_index = 0;
};

#include "ObjectPool.hpp"