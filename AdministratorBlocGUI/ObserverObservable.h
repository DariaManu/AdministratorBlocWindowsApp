#pragma once
#include <vector>

class Observer
{
public:
	virtual void update() = 0;

};

class Observable
{
private:
	std::vector<Observer*> observeri;

public:
	
	void adauga_observer(Observer* observer)
	{
		observeri.push_back(observer);
	}

	void notifica()
	{
		for (auto observer : observeri)
			observer->update();
	}

};

