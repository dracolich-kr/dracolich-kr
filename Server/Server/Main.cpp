#include <Pch.h>
#include <Framework/ObjectPool/ObjectPool.h>
#include <Framework/Thread/ThreadManager.h>
#include <Logic/TestThread.h>

int main()
{
	PThread t1;
	PThread t2;
	PThread t3;
	PThread t4;

	t1 = ThreadManager::GetInstance()->AddThread(ThreadType::Test);
	t2 = ThreadManager::GetInstance()->AddThread(ThreadType::Test);
	t3 = ThreadManager::GetInstance()->AddThread(ThreadType::Test);
	t4 = ThreadManager::GetInstance()->AddThread(ThreadType::Test);
	
	t1->GetThread().join();
	t2->GetThread().join();
	t3->GetThread().join();
	t4->GetThread().join();

	t1 = ThreadManager::GetInstance()->AddThread(ThreadType::SingleTest);
	t2 = ThreadManager::GetInstance()->AddThread(ThreadType::SingleTest);
	t3 = ThreadManager::GetInstance()->AddThread(ThreadType::SingleTest);
	t4 = ThreadManager::GetInstance()->AddThread(ThreadType::SingleTest);

	t1->GetThread().join();
	t2->GetThread().join();
	t3->GetThread().join();
	t4->GetThread().join();

	t1 = ThreadManager::GetInstance()->AddThread(ThreadType::DefaultTest);
	t2 = ThreadManager::GetInstance()->AddThread(ThreadType::DefaultTest);
	t3 = ThreadManager::GetInstance()->AddThread(ThreadType::DefaultTest);
	t4 = ThreadManager::GetInstance()->AddThread(ThreadType::DefaultTest);

	t1->GetThread().join();
	t2->GetThread().join();
	t3->GetThread().join();
	t4->GetThread().join();

	return 0;
}