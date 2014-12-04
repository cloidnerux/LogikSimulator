#pragma once

#include "tFunc.h"
#include "node.h"
#include <memory>

class XORFunc : public tFunc
{
public:
	XORFunc():tFunc(){};
	XORFunc(const XORFunc &a):tFunc(a){};
	XORFunc(const XORFunc *a):tFunc(a){};
	XORFunc(std::shared_ptr<Node> a, std::shared_ptr<Node> b, std::shared_ptr<Node> out, int delay);
	~XORFunc();
	void Update(int cycleTime);
	char * GetType();
	char * GetState();
};