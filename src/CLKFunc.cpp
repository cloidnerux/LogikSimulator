#include "CLKFunc.h"

#include <vector>
#include <memory>

using namespace std;

CLKFunc::CLKFunc(shared_ptr<Node> out, unsigned int Frequency)
{
	callCount = 0;
	outputs.push_back(make_shared<outputBuffer<bool>>(new outputBuffer<bool>(out.get(), new RingBuffer<bool>(0))));
	frequency = Frequency;
	cycleDelta = 0;
}

CLKFunc::~CLKFunc()
{
	inputs.clear();
	outputs.clear();
}

void CLKFunc::Update(int cycleTime)
{
	if(outputs.size() != 1)
		throw "More or less than 1 output for CLK operation!";

	cycleDelta++;
	if(cycleDelta >= frequency)
	{
		outputs[0]->buffer->push_back(!outputs[0]->buffer->GetLast());
		cycleDelta = 0;
	}
	outputs[0]->output->state = outputs[0]->buffer->GetFirst();
}

char * CLKFunc::GetType()
{
	return "Clock";
}

char * CLKFunc::GetState()
{
	char * state = new char[100];
	sprintf_s(state, 100, "clk = %d", outputs[0].get()->output->state);
	return state;
}