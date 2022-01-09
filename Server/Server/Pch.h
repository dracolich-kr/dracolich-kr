#pragma once

#include <Windows.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <map>
#include <list>
#include <deque>
#include <concurrent_unordered_map.h>

using ThreadIndex = INT32;
using ErrorResult = INT32;

#define IF_RETURN(val, ret) if(val) { return ret; }
#define IF_DO(val, _do) if(val) { _do; }
#define SAFE_DELETE(val)	\
	if(val != null)			\
	{						\
		delete val;			\
		val = null 			\
	}		