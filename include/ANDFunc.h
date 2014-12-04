#pragma once

#include "tFunc.h"
#include "node.h"
#include <memory>

class ANDFunc : public tFunc
{
public:
	ANDFunc():tFunc(){};
	ANDFunc(const ANDFunc &a):tFunc(a){};
	ANDFunc(const ANDFunc *a):tFunc(a){};
	ANDFunc(std::shared_ptr<Node> a, std::shared_ptr<Node> b, std::shared_ptr<Node> out, int delay);
	~ANDFunc();
	void Update(int cycleTime);
	char * GetType();
	char * GetState();
};