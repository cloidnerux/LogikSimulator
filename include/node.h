#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include "tFunc.h"

template<class T>
class node
{
public:
	int weight;
	T state;		//Every node has only one source
	int ID;
	std::vector <tFunc*> assignedFunctions;		//but multiple sinks
	int cycleTime;
	node()
	{
		state = 0;
		ID = 0;
		weight = 0;
		cycleTime = 0;
	}
	node(int Weight)
	{
		state = false;
		ID = 0;
		cycleTime = 0;
		weight = Weight;
	}
	node(const node<T> &a)
	{
		state = a.state;
		ID = a.ID;
		weight = a.weight;
		cycleTime = a.cycleTime;
		assignedFunctions.clear();
		assignedFunctions = a.assignedFunctions;
	}
	node(const node<T> *a)
	{
		state = a->state;
		ID = a->ID;
		weight = a->weight;
		cycleTime = a->cycleTime;
		assignedFunctions.clear();
		assignedFunctions = a->assignedFunctions;
	}
	~node()
	{
		assignedFunctions.clear();
	}
	void Update(int CycleTime)
	{
		cycleTime = CycleTime;
		for(auto it = assignedFunctions.begin(); it != assignedFunctions.end(); it++)
		{
			(*it)->Update(cycleTime);
		}
	}
};
