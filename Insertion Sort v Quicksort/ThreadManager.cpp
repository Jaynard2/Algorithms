/*********************************************************
* Summary: This file includes the implementation for the ThreadManager class.
*
* Author: Joshua Grieve
* Created: Aug 2021
*
* ęCopyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/
#include "ThreadManager.h"

ThreadManager ThreadManager::s_man = ThreadManager();

ThreadManager::~ThreadManager()
{
	if (_worker.joinable())
	{
		//Joining with worker joins with all active threads
		_worker.join();
	}
}

void ThreadManager::setMaxThreads(int newMax)
{
	if (newMax > std::thread::hardware_concurrency() - USED_THREADS)
	{
		throw std::exception("Thread count cannot exceed " + std::thread::hardware_concurrency());
	}

	_maxThreads = newMax;
}

std::any ThreadManager::check(unsigned id)
{
	std::lock_guard guard(_dataLock);

	if (_data.find(id) == _data.end())
	{
		throw NoSuchThread("No such thread with id " + id);
	}

	std::any temp = _data.at(id);

	if (temp.has_value())
	{
		_data.erase(id);
	}

	return temp;
}

std::any ThreadManager::get(unsigned id)
{
	std::unique_lock guard(_dataLock);

	if (_data.find(id) == _data.end())
	{
		throw NoSuchThread("No such thread with id " + id);
	}

	if (!_data.find(id)->second.has_value())
	{
		guard.unlock();
		std::lock_guard lock(_threadLock);
		if (_threads.at(id).joinable())
		{
			_threads.at(id).join();
		}
		guard.lock();
	}

	std::any temp = _data.at(id);
	_data.erase(id);

	return temp;
}

void ThreadManager::joinAll()
{
	if (_worker.joinable())
	{
		_worker.join();
		_dead = false;
	}
}

ThreadManager::ThreadManager() : _maxThreads(std::thread::hardware_concurrency() - USED_THREADS), _lastID(0), _data(),
_futureThreads(), _dead(false), _threads(), _finishedThreads(), _dataLock(), _finshedLock(), _worker(), _deadLock(), _startCleanup()
{
	
}

//Cleans up any dead threads and starts new ones when there is space
void ThreadManager::manage()
{
	std::unique_lock mainLock(_threadLock);
	while (_threads.size() > 0)
	{
		mainLock.unlock();
		std::unique_lock startCleanupLock(_finshedLock);
		//Wait until there are threads to clean up
		while(_finishedThreads.size() == 0) _startCleanup.wait(startCleanupLock);

		while (!_finishedThreads.empty())
		{
			unsigned i = _finishedThreads.front();

			std::lock_guard lock(_threadLock);
			if (_threads.at(i).joinable())
			{
				_threads.at(i).join();
			}

			_threads.erase(i);

			_finishedThreads.pop();

			startCleanupLock.unlock();

			std::unique_lock future(_futureLock);
			if(!_futureThreads.empty())
			{
				auto next = _futureThreads.front();

				_threads.emplace
				(
					next.first,
					std::thread
					(
						[this, func = next.second](unsigned id)
						{
							std::any data = func();

							std::unique_lock lock1(_dataLock);
							_data.insert(std::make_pair(id, data));
							lock1.unlock();

							std::lock_guard lock2(_finshedLock);
							_finishedThreads.push(id);
							_startCleanup.notify_all();
						},
						next.first
					)
				);

				_futureThreads.pop();
				future.unlock();
			}

			startCleanupLock.lock();
			
		}
		
		startCleanupLock.unlock();
		mainLock.lock();
	}

	//No more work to be done - let worker die
	std::lock_guard dead(_deadLock);
	_dead = true;
}
