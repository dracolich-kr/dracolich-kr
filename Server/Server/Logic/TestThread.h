#pragma once
#include <Framework/Thread/Thread.h>
#include <Framework/SingleTon.h>
#include <Framework/ObjectPool/ObjectPool.h>

class TestThread : public Thread
{
public:
	TestThread() :
		Thread(ThreadType::Test)
	{}

	virtual void Work() override;
private:

};

class TestSingleThread : public Thread
{
public:
	TestSingleThread() :
		Thread(ThreadType::SingleTest)
	{}

	virtual void Work() override;
private:
};
class TestDefaultThread : public Thread
{
public:
	TestDefaultThread() :
		Thread(ThreadType::DefaultTest)
	{}

	virtual void Work() override;
};

struct TestValue
{
public:
	int value = 0;
	std::string str_data = { 0, };
};

class TestPool
	: public Singleton<TestPool>
{
	friend Singleton<TestPool>;
	TestPool() {}

public:
	virtual ~TestPool() {}

	ObjectPool<TestValue> Pool;
	SingleObjectPool<TestValue> SinglePool;
private:
};


