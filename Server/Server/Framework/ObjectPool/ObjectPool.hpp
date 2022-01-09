#pragma once
#include "ObjectPool.h"

template<class T>
T* ObjectPool<T>::Alloc()
{
	ThreadId id = GetCurrentThreadId();
	auto deque = m_buffer.find(id);
	if (deque == m_buffer.end())
	{
		deque = m_buffer[id] = new ObjectBuffer<T>();
	}

	return deque->second->pop_back();
}

template<class T>
void ObjectPool<T>::DeAlloc(void* free)
{
	ObjectHeader* header = free - sizeof(ObjectHeader);

	auto deque = m_buffer.find(header->m_threadid);
	if (deque == m_buffer.end())
	{
		/// ’o¹Ì
		return;
	}

	deque->second->push_back(free);
}
