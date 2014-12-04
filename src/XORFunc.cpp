#include "XORFunc.h"

#include <vector>
#include <memory>
#include <string>

#ifndef _MSC_VER
#include <cstdio>
#endif

using namespace std;


XORFunc::XORFunc(shared_ptr<Node> a, shared_ptr<Node> b, shared_ptr<Node> out, int delay)
{
	callCount = 0;
	inputs.push_back(a);
	a->assignedFunctions.push_back(this);
	inputs.push_back(b);
	b->assignedFunctions.push_back(this);

	outputs.push_back(make_shared< outputBuffer<bool> >(new outputBuffer<bool>(out.get(), new RingBuffer<bool>(delay))));
	for(int i = 0; i < delay; i++)
	{
		outputs[0]->buffer->push_back(out->state);
	}
}

XORFunc::~XORFunc()
{
	inputs.clear();
	outputs.clear();
}

void XORFunc::Update(int cycleTime)
{
	bool state = false;
	callCount++;
	callCount %= inputs.size();
	if(_cycleTime < cycleTime)
	{
		callCount = 0;
		_cycleTime = cycleTime;
	}
	if(inputs.size() < 2)
	{
		char text[100];
		#ifdef _MSC_VER
		sprintf_s(text, "To few inputs for XOR operation, minimum is 2, inputs has %d elements", inputs.size());
		#else
		sprintf(text, "To few inputs for XOR operation, minimum is 2, inputs has %d elements", inputs.size());
		#endif
		throw text;
	}
	if(outputs.size() != 1)
		throw "More or less than 1 output for XOR operation!";

	for(auto it = inputs.begin(); it != inputs.end(); it++)
	{
		//TODO: This will cause problems with latches, as they feed back
		if(it->get()->cycleTime < cycleTime && cycleTime > 0 && callCount > 0)    //Not all input nodes were updated within this cycle, abort and wait for last input to update. 
			return;
		state ^= it->get()->state;
	}
	outputs[0]->buffer->push_back(state);
	outputs[0]->output->state = outputs[0]->buffer->GetFirst();
}

char * XORFunc::GetType()
{
	return "XOR";
}

char * XORFunc::GetState()
{
	char * state = new char[100];
#ifdef _MSC_VER
	sprintf_s(state, 100, "a = %d, b = %d, q = %d", inputs[0].get()->state, inputs[1].get()->state, outputs[0].get()->output->state);
#else
	sprintf(state, "a = %d, b = %d, q = %d", inputs[0].get()->state, inputs[1].get()->state, outputs[0].get()->output->state);
#endif
	return state;
}