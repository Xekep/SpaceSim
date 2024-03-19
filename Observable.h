#pragma once
#include "Observer.h"
#include <memory>
#include <vector>

class Observable
{
public:
	virtual ~Observable() {}
	void AddObserver(Observer* Observer)
	{
		_Observers.push_back(Observer);
	}
	void RemoveObserver(Observer* Observer)
	{
		std::erase(_Observers, Observer);
	}
	void NotifyObservers()
	{
		for (auto& observer : _Observers)
			observer->HandleEvent(this);
	}

private:
	std::vector<Observer*> _Observers;
};

