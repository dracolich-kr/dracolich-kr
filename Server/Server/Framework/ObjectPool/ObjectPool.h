#pragma once

#include <Pch.h>
#include <mutex>

using ObjectIndex = int;
using ThreadId = DWORD;


struct ObjectHeader
{
	ThreadId m_threadid = 0;
};

template<class T, size_t BLOCK_SIZE = 1024>
class ObjectBuffer 
{
public:
	ObjectBuffer() 
	{
		m_alloc_size = sizeof(T) + sizeof(ObjectHeader);
	}

	T* Pop()
	{
		if (m_buffer.empty() == true)
			allocate();

		m_use_count++;
		BYTE* buffer = nullptr;
		m_buffer.try_pop(buffer);
		
		return (T*)buffer;
	}

	void Push(T* block)
	{
		m_use_count--;
		m_buffer.push((BYTE*)block);
	}

private:
	void allocate()
	{
		BYTE* page = new BYTE[m_alloc_size * BLOCK_SIZE];
		ZeroMemory(page, m_alloc_size * BLOCK_SIZE);
		BYTE* buffer = page;

		for (int index = 0; index < BLOCK_SIZE; ++index)
		{
			ObjectHeader* header = (ObjectHeader*)buffer;
			header->m_threadid = (int)GetCurrentThreadId();
			buffer += sizeof(ObjectHeader);

			m_buffer.push((BYTE*)buffer);
			buffer += sizeof(sizeof(T));
		}
	}

private:
	concurrency::concurrent_queue<BYTE*> m_buffer;
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
	void DeAlloc(T *free);

private:
	concurrency::concurrent_unordered_map<ThreadId, ObjectBuffer<T>*> m_buffer;
};

template<class T>
class SingleObjectPool
{
public:
	SingleObjectPool() {}
	virtual ~SingleObjectPool() {}

	T* Alloc();
	void DeAlloc(T* free);
private:
	ObjectBuffer<T> m_buffer;
	std::mutex m_mutex;
};

#include "ObjectPool.hpp"