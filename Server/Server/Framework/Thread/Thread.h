#pragma once

#include <Pch.h>

enum class ThreadType
{
	None = 0
	, Test
	, SingleTest
	, DefaultTest
};

enum class ThreadState
{
	None = 0
	, Run
	, Close
};

class Thread
{
public:
	Thread(ThreadType type) :
		m_type(type)
		, m_state(ThreadState::None)
	{}

	virtual ~Thread()
	{
		SetState(ThreadState::Close);
	}

	void SetIndex(const ThreadIndex index) { m_thread_index = index; }
	const ThreadIndex& GetIndex() const { return m_thread_index; }

	void SetState(const ThreadState state) { m_state = state; }
	const std::atomic<ThreadState>& GetState() const { return m_state; }

	const ThreadType& GetType() const { return m_type; }

	void Run();
	virtual void Work() {};

	std::thread& GetThread() { return m_thread; }
private:
	const ThreadType m_type = ThreadType::None;

	std::thread m_thread;
	std::atomic<ThreadState> m_state = ThreadState::None;

	ThreadIndex m_thread_index = 0;	// ThreadManager���� �߱��ϴ� �ε���.

};

using PThread = std::shared_ptr<Thread>;