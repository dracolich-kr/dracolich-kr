#pragma once
#include "ObjectPool.h"

template<class T>
T* ObjectPool<T>::Alloc()
{
	ThreadId id = GetCurrentThreadId();
	auto deque = m_buffer.find(id);
	if (deque == m_buffer.end())
	{
		m_buffer[id] = new ObjectBuffer<T>();
		deque = m_buffer.find(id);
	}
	
	return deque->second->Pop();
}

template<class T>
void ObjectPool<T>::DeAlloc(T* free)
{
	BYTE* buffer = (BYTE*)free;
	ObjectHeader* header = (ObjectHeader*)(buffer - sizeof(ObjectHeader));

	auto deque = m_buffer.find(header->m_threadid);
	if (deque == m_buffer.end())
	{
		/// ’o¹Ì
		return;
	}

	deque->second->Push(free);
}

template<class T>
T* SingleObjectPool<T>::Alloc()
{
	std::lock_guard<std::mutex> guard(m_mutex);
	return m_buffer.Pop();
}

template<class T>
void SingleObjectPool<T>::DeAlloc(T* free)
{
	std::lock_guard<std::mutex> guard(m_mutex);
	return m_buffer.Push(free);
}

