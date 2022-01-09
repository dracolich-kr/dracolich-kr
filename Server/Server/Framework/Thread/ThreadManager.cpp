#include "ThreadManager.h"


ErrorResult ThreadManager::AddThread(const ThreadType type)
{
	PThread thread = create(type);
	IF_RETURN(thread == nullptr, 1);

	m_threadMap.emplace(thread->GetIndex(), thread);

	return 0;
}

PThread ThreadManager::create(ThreadType type)
{
	PThread thread = nullptr;

	switch (type)
	{
	case ThreadType::None:
	{
		thread = std::make_shared<Thread>(type);
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