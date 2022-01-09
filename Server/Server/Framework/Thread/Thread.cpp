#include "Thread.h"

void Thread::Run()
{
	m_thread = std::thread(&Thread::Work, this);
	SetState(ThreadState::Run);

	m_thread.join();

	return;
}
