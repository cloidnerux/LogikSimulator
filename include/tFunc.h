#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include "RingBuffer.h"

template<class T> class node;	//forward declaration
typedef node<bool> Node;

template <typename T>
class outputBuffer
{
public:
	Node* output;
	RingBuffer<T> * buffer;
public:
	outputBuffer(Node * out, RingBuffer<T> * buf)
	{
		output = out;
		buffer = buf;
	}

	outputBuffer(const outputBuffer<T> &a)
	{
		output = a.output;
		buffer = a.buffer;
	}

	outputBuffer(const outputBuffer<T> *a)
	{
		output = a->output;
		buffer = a->buffer;
	}

	~outputBuffer()
	{
		delete output;
		delete buffer;
	}
};

//Abstract base class for base class pointer
class tFunc
{
protected:
	std::vector<std::shared_ptr<Node>> inputs;
	std::vector<std::shared_ptr< outputBuffer<bool> > > outputs;
	int callCount;
	int _cycleTime;
public:
	tFunc() {callCount = 0;};
	tFunc(const tFunc &a)
	{
		callCount = 0;
		for(auto it = a.inputs.begin(); it != a.inputs.end(); it++)
		{
			inputs.push_back(*it);
		}
		for(auto it = a.outputs.begin(); it != a.outputs.end(); it++)
		{
			outputs.push_back(*it);
		}
	}

	tFunc(const tFunc *a)
	{
		callCount = 0;
		for(auto it = a->inputs.begin(); it != a->inputs.end(); it++)
		{
			inputs.push_back(*it);
		}
		for(auto it = a->outputs.begin(); it != a->outputs.end(); it++)
		{
			outputs.push_back(*it);
		}
	}

	virtual ~tFunc() {};
	virtual void Update(int cycleTime) = 0;
	virtual char * GetType() = 0;
	virtual char * GetState() = 0;
};