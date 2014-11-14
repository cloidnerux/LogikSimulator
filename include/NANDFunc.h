#pragma once

#include "tFunc.h"
#include "node.h"
#include <memory>

class NANDFunc : public tFunc
{
public:
	NANDFunc():tFunc(){};
	NANDFunc(const NANDFunc &a):tFunc(a){};
	NANDFunc(const NANDFunc *a):tFunc(a){};
	NANDFunc(std::shared_ptr<Node> a, std::shared_ptr<Node> b, std::shared_ptr<Node> out, int delay);
	~NANDFunc();
	void Update(int cycleTime);
	char * GetType();
	char * GetState();
};