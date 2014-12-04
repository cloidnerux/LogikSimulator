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
	CLKNode() : node<T>()
	{
		frequency = 1;
		cycleDelta = 0;
	}
	CLKNode(unsigned int Frequency) : node<T>()
	{
		this->state = false;
		this->ID = 0;
		this->cycleTime = 0;
		this->weight = 0;
		this->frequency = Frequency;
		this->cycleDelta = 0;
	}
	CLKNode(const CLKNode<T> &a)
	{
		this->state = a.state;
		this->ID = a.ID;
		this->weight = a.weight;
		this->cycleTime = a.cycleTime;
		this->assignedFunctions.clear();
		this->assignedFunctions = a.assignedFunctions;
		this->frequency = a.frequency;
		this->cycleDelta = a.cycleDelta;
	}
	CLKNode(const CLKNode<T> *a)
	{
		this->state = a->state;
		this->ID = a->ID;
		this->weight = a->weight;
		this->cycleTime = a->cycleTime;
		this->assignedFunctions.clear();
		this->assignedFunctions = a->assignedFunctions;
		this->frequency = a->frequency;
		this->cycleDelta = a->cycleDelta;
	}
	~CLKNode()
	{
		this->assignedFunctions.clear();
	}
	
	virtual void Update(int CycleTime)
	{
		this->cycleTime = CycleTime;
		cycleDelta++;
		if(cycleDelta == frequency)
		{
			this->state = !(this->state);
			cycleDelta = 0;
		}
		for(auto it = this->assignedFunctions.begin(); it != this->assignedFunctions.end(); it++)
		{
			(*it)->Update(this->cycleTime);
		}
	}
};
