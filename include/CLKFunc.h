#pragma once

#include "tFunc.h"
#include "node.h"
#include <memory>

class CLKFunc : public tFunc
{
private:
	unsigned int frequency;
	unsigned int cycleDelta;
public:
	CLKFunc():tFunc(){};
	CLKFunc(const CLKFunc &a):tFunc(a){};
	CLKFunc(const CLKFunc *a):tFunc(a){};
	//The frequency is the time between a falling and rising edge in cycles
	CLKFunc(std::shared_ptr<Node> out, unsigned int Frequency);	
	~CLKFunc();
	void Update(int cycleTime);
	char * GetType();
	char * GetState();
};