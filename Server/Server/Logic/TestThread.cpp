#include "TestThread.h"
#include <Framework/TickCounter.h>

void TestThread::Work()
{
	std::cout << "TestThread run : " << this->GetIndex() << std::endl;

	TestValue* test = nullptr;
	TickCounter time;

	for (int i = 0; i < 1'000'000; ++i)
	{
		test = TestPool::GetInstance()->Pool.Alloc();

		TestPool::GetInstance()->Pool.DeAlloc(test);
	}

	std::cout << "TestThread run : " << this->GetIndex() << "time " << time.Getduration() << std::endl;
}

void TestSingleThread::Work()
{
	std::cout << "TestSingleThread run : " << this->GetIndex() << std::endl;

	TestValue* test = nullptr;
	TickCounter time;

	for (int i = 0; i < 10'000'000; ++i)
	{
		test = TestPool::GetInstance()->SinglePool.Alloc();

		TestPool::GetInstance()->SinglePool.DeAlloc(test);
	}

	std::cout << "TestSingleThread run : " << this->GetIndex() << " time " << time.Getduration() << std::endl;
}

void TestDefaultThread::Work()
{
	std::cout << "TestDefaultThread run : " << this->GetIndex() << std::endl;

	TestValue* test = nullptr;
	TickCounter time;

	for (int i = 0; i < 10'000'000; ++i)
	{
		test = new TestValue();

		delete test;
	}

	std::cout << "TestDefaultThread run : " << this->GetIndex() << " time " << time.Getduration() << std::endl;
}
