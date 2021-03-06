/********************************************************
* Provides a simple to use interface for creating and using threads. It manages the amount
* of active threads so that there are no more than the hardware supported amount running at any one time.
* It also provides methods for checking if a thread has finshed without blocking and a way to join with all
* threads that have been requested.
*
* ęCopyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
* *******************************************************/
#pragma once
#include <thread>
#include <queue>
#include <map>
#include <functional>
#include <mutex>
#include <exception>
#include <condition_variable>
#include <any>

class NoSuchThread : public std::exception
{
public:
	NoSuchThread(std::string_view str) : std::exception(str.data()) {}
};

class ThreadManager
{
public:
	ThreadManager(const ThreadManager&) = delete;
	ThreadManager& operator=(const ThreadManager&) = delete;
	~ThreadManager();

	static ThreadManager& getManager() { return s_man; }

	/*
	* Request a thread gets created. If there is currently the same amount of threads as
	* the hardware supports concurrently, the thread is not started until another dies
	*/
	template <typename T>
	int requestThread(std::function <T()> func);

	void setMaxThreads(int newMax);

	//Check for return values without blocking
	std::any check(unsigned id);
	//Block until thread returns
	std::any get(unsigned id);
	void joinAll();

private:
	ThreadManager();
	void manage();

	static ThreadManager s_man;
	//Used for accounting the main thread and the worker thread used by the manager
	constexpr static unsigned USED_THREADS = 2;

	int _maxThreads;
	unsigned _lastID;
	std::map<unsigned, std::thread> _threads;
	std::map<unsigned, std::any> _data;
	std::queue<unsigned> _finishedThreads;

	std::mutex _dataLock;
	std::mutex _futureLock;
	std::mutex _finshedLock;
	std::mutex _threadLock;
	std::condition_variable _startCleanup;

	std::thread _worker;
	std::mutex _deadLock;
	bool _dead;
	

	std::queue<std::pair<unsigned, std::function<std::any ()>>> _futureThreads;

};

template<typename T>
inline int ThreadManager::requestThread(std::function<T()> func)
{

	if (_threads.size() < _maxThreads)
	{
		std::unique_lock thread(_threadLock);

		_threads.emplace
		(
			_lastID,
			std::thread
			(
				[this, func](unsigned id)
				{
					std::any data = func();

					std::unique_lock lock1(_dataLock);

					if (_data.find(id) == _data.end())
					{
						_data.insert(std::make_pair(id, data));
					}
					else
					{
						_data.at(id) = data;
					}

					lock1.unlock();

					std::lock_guard lock2(_finshedLock);
					_finishedThreads.push(id);
					_startCleanup.notify_all();
				},
				_lastID
			)
		);

		thread.unlock();

		//Reset worker if it ran out of work and died
		std::unique_lock dead(_deadLock);
		if (_dead)
		{
			_worker.join();
			_dead = false;
		}
		dead.unlock();

		//Start worker if not already running
		if (!_worker.joinable())
		{
			_worker = std::thread(&ThreadManager::manage, this);
		}
	}
	else
	{
		std::lock_guard lock(_futureLock);
		_futureThreads.push(std::make_pair(_lastID, func));
	}

	std::lock_guard lock(_dataLock);
	if (_data.find(_lastID) == _data.end())
	{
		_data.insert(std::make_pair(_lastID, std::any()));
	}

	return _lastID++;
}
