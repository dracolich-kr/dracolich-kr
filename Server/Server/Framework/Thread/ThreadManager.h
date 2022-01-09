#pragma once
#include <Pch.h>
#include "Thread.h"
#include <Framework/SingleTon.h>

class ThreadManager 
	: public Singleton<ThreadManager>
{
	friend Singleton<ThreadManager>;
	ThreadManager() {}

public:
	virtual ~ThreadManager() {}
	PThread AddThread(const ThreadType type);

private:
	PThread create(ThreadType type);

	std::map<ThreadIndex, PThread> m_threadMap;
	std::atomic<ThreadIndex> m_indexGenerator;
};