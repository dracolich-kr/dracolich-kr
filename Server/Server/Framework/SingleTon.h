#pragma once

#include <mutex>

template <typename Type>
class Singleton
{
public:
	virtual  ~Singleton() {}

	static Type* GetInstance();
	static void Destory();

protected:
	Singleton() {}
private:
	static Type* m_instance;
	static std::mutex m_mutex;
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;
};

template <typename Type>
Type* Singleton<Type>::GetInstance()
{
	if (m_instance == nullptr)
	{
		std::lock_guard<std::mutex> guard(m_mutex);

		if (m_instance == nullptr)
		{
			m_instance = new Type;
		}
	}

	return m_instance;
}

template <typename Type>
void Singleton<Type>::Destory()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

template <typename Type>
Type* Singleton<Type>::m_instance = nullptr;

template <typename Type>
std::mutex Singleton<Type>::m_mutex;