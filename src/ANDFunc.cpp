#include "ANDFunc.h"

#include <vector>
#include <memory>

using namespace std;

ANDFunc::ANDFunc(shared_ptr<Node> a, shared_ptr<Node> b, shared_ptr<Node> out, int delay)
{
	callCount = 0;
	inputs.push_back(a);
	a->assignedFunctions.push_back(this);
	inputs.push_back(b);
	b->assignedFunctions.push_back(this);
	
	outputs.push_back(make_shared<outputBuffer<bool>>(new outputBuffer<bool>(out.get(), new RingBuffer<bool>(delay))));
}

ANDFunc::~ANDFunc()
{
	inputs.clear();
	outputs.clear();
}

void ANDFunc::Update(int cycleTime)
{
	bool state = true;
	if(_cycleTime < cycleTime)
	{
		callCount = 0;
		_cycleTime = cycleTime;
	}
	callCount++;
	callCount %= inputs.size();

	if(inputs.size() < 2)
		throw "To few inputs for AND operation, minimum is 2";
	if(outputs.size() != 1)
		throw "More or less than 1 output for AND operation!";

	for(auto it = inputs.begin(); it != inputs.end(); it++)
	{
		if(it->get()->cycleTime < cycleTime && cycleTime > 0  && callCount > 0)    //Not all input nodes were updated within this cycle, abort and wait for last input to update
			return;
		state &= it->get()->state;
	}
	outputs[0]->buffer->push_back(state);
	outputs[0]->output->state = outputs[0]->buffer->GetFirst();
}

char * ANDFunc::GetType()
{
	return "AND";
}

char * ANDFunc::GetState()
{
	char * state = new char[100];
	sprintf_s(state, 100, "a = %d, b = %d, q = %d", inputs[0].get()->state, inputs[1].get()->state, outputs[0].get()->output->state);
	return state;
}