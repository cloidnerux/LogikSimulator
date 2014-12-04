#include "NotFunc.h"

#include <vector>
#include <memory>

#ifndef _MSC_VER
#include <cstdio>
#endif

using namespace std;

NOTFunc::NOTFunc(shared_ptr<Node> a, shared_ptr<Node> out, int delay)
{
	callCount = 0;
	inputs.push_back(a);
	a->assignedFunctions.push_back(this);

	outputs.push_back(make_shared<outputBuffer<bool>>(new outputBuffer<bool>(out.get(), new RingBuffer<bool>(delay))));
	for(int i = 0; i < delay; i++)
	{
		outputs[0]->buffer->push_back(out->state);
	}
}

NOTFunc::~NOTFunc()
{
	inputs.clear();
	outputs.clear();
}

void NOTFunc::Update(int cycleTime)
{
	bool state = false;
	if(_cycleTime < cycleTime)
	{
		callCount = 0;
		_cycleTime = cycleTime;
	}
	callCount++;
	callCount %= inputs.size();

	if(inputs.size() < 1)
		throw "To few inputs for OR operation, minimum is 1";
	if(outputs.size() != 1)
		throw "More or less than 1 output for NOT operation!";

	state = !inputs[0].get()->state;
	outputs[0]->buffer->push_back(state);
	outputs[0]->output->state = outputs[0]->buffer->GetFirst();
}

char * NOTFunc::GetType()
{
	return "NOT";
}

char * NOTFunc::GetState()
{
	char * state = new char[100];
#ifdef _MSC_VER
	sprintf_s(state, 100, "a = %d, q = %d", inputs[0].get()->state, outputs[0].get()->output->state);
#else
	sprintf(state, "a = %d, q = %d", inputs[0].get()->state, outputs[0].get()->output->state);
#endif

	return state;
}