#include "Common Utilities_Precompiled.h"
#include "Worker.h"
#include "EventManager.h"


namespace CommonUtilities
{
	Worker::Worker()
	{
		myWork = nullptr;
		myQuit = false;
		auto function = [&]()
		{
			&Worker::Start;
		};
		//myThread = new std::thread(&Worker::Start, std::reference_wrapper<Worker>(*this));
		myThread = new std::thread(function);
	}

	void Worker::Start()
	{
		std::unique_lock<std::mutex> lock(myMutex);
		CU::EventManager::GetInstance()->RegisterThread();

		while (myQuit == false)
		{
			myConditionVariable.wait_for(lock, std::chrono::milliseconds(1));

			if (myWork != nullptr)
			{
				myWork->DoWork();
				if (myQuit == false)
				{
					myWork = nullptr;
				}
			}
		}
		myConditionVariable._Unregister(myMutex);
		//myMutex.unlock();
	}


	const bool Worker::IsWorking() const
	{
		if (myWork == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool Worker::AddWork(Work* someWork)
	{
		if (IsWorking() == false)
		{
			myWork = someWork;
			myConditionVariable.notify_one();
			return true;
		}
		else
		{
			return false;
		}
	}

	void Worker::Destroy()
	{
		if (myThread != nullptr)
		{
			myQuit = true;
			myConditionVariable.notify_all();
			myThread->join();
			delete myThread;
			myThread = nullptr;
		}
	}


	Worker::~Worker()
	{
		if (myThread != nullptr)
		{
			DL_ASSERT("Worker not destroyed.");
		}
	}
}