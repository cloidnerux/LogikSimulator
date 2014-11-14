#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include "node.h"

template<class T>
class CLKNode : public node<T>
{
public:
	//int weight;
	unsigned int frequency;
	int cycleDelta;
	//T state;		//Every node has only one source
	//int ID;
	//std::vector <tFunc*> assignedFunctions;		//but multiple sinks
	//int cycleTime;
	CLKNode() : node()
	{
		frequency = 1;
		cycleDelta = 0;
	}
	CLKNode(unsigned int Frequency)
	{
		state = false;
		ID = 0;
		cycleTime = 0;
		weight = 0;
		frequency = Frequency;
		cycleDelta = 0;
	}
	CLKNode(const CLKNode<T> &a)
	{
		state = a.state;
		ID = a.ID;
		weight = a.weight;
		cycleTime = a.cycleTime;
		assignedFunctions.clear();
		assignedFunctions = a.assignedFunctions;
		frequency = a.frequency;
		cycleDelta = a.cycleDelta;
	}
	CLKNode(const CLKNode<T> *a)
	{
		state = a->state;
		ID = a->ID;
		weight = a->weight;
		cycleTime = a->cycleTime;
		assignedFunctions.clear();
		assignedFunctions = a->assignedFunctions;
		frequency = a->frequency;
		cycleDelta = a->cycleDelta;
	}
	~CLKNode()
	{
		assignedFunctions.clear();
	}
	
	virtual void Update(int CycleTime)
	{
		cycleTime = CycleTime;
		cycleDelta++;
		if(cycleDelta == frequency)
		{
			state = !state;
			cycleDelta = 0;
		}
		for(auto it = assignedFunctions.begin(); it != assignedFunctions.end(); it++)
		{
			(*it)->Update(cycleTime);
		}
	}
};
