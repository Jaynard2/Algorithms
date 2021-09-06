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

	template <typename T>
	int requestThread(std::function <T()> func);

	std::any check(unsigned id);
	std::any get(unsigned id);
	void joinAll();

private:
	ThreadManager();
	void manage();

	static ThreadManager s_man;

	const int _maxThreads;
	unsigned _lastID;
	std::map<int, std::thread> _threads;
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
