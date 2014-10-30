#pragma once

#include "tFunc.h"
#include "node.h"
#include <memory>

class NOTFunc : public tFunc
{
public:
	NOTFunc():tFunc(){};
	NOTFunc(const NOTFunc &a):tFunc(a){};
	NOTFunc(const NOTFunc *a):tFunc(a){};
	NOTFunc(std::shared_ptr<Node> a, std::shared_ptr<Node> out, int delay);
	~NOTFunc();
	void Update(int cycleTime);
	char * GetType();
	char * GetState();
};