#pragma once

#include "tFunc.h"
#include "node.h"
#include <memory>

class ORFunc : public tFunc
{
public:
	ORFunc():tFunc(){};
	ORFunc(const ORFunc &a):tFunc(a){};
	ORFunc(const ORFunc *a):tFunc(a){};
	ORFunc(std::shared_ptr<Node> a, std::shared_ptr<Node> b, std::shared_ptr<Node> out, int delay);
	~ORFunc();
	void Update(int cycleTime);
	char * GetType();
	char * GetState();
};