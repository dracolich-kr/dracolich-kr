#include "ThreadManager.h"
#include <Logic/TestThread.h>

PThread ThreadManager::AddThread(const ThreadType type)
{
	PThread thread = create(type);
	IF_RETURN(thread == nullptr, nullptr);

	m_threadMap.emplace(thread->GetIndex(), thread);

	return thread;
}

PThread ThreadManager::create(ThreadType type)
{
	PThread thread = nullptr;

	switch (type)
	{
	case ThreadType::Test:
	{
		thread = std::make_shared<TestThread>();
	}
	break;
	case ThreadType::SingleTest:
	{
		thread = std::make_shared<TestSingleThread>();
	}
	break;
	case ThreadType::DefaultTest:
	{
		thread = std::make_shared<TestDefaultThread>();
	}
	break;
	default:
		break;
	}

	IF_RETURN(thread == nullptr, nullptr);

	++m_indexGenerator;

	thread->SetIndex(m_indexGenerator);
	thread->Run();

	return thread;
}