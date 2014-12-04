#pragma once

#include <memory>
#include <string>

void strcpy_e(char * dst, const char * src)
{
	int start = 0;
	while(src[start] == ' ')
		start++;
	strcpy(dst, src+start);
}

struct state
{
	char stateName[10];
	char nextStateNameFalse[10];
	char nextStateNameTrue[10];
	state * nextStateFalse;	//Next state to jump to, if the input is false
	state * nextStateTrue;	//Next state to jump to, if the input is true
	bool outputFalse;
	bool outputTrue;

	state()
	{
		nextStateFalse = NULL;
		nextStateTrue = NULL;
		outputFalse = false;
		outputTrue = false;
	}

	state(char * init)
	{
		char * ptr = strtok(init, ",");
		strcpy_e(stateName, ptr);
		ptr = strtok(NULL, ",");
		strcpy_e(nextStateNameFalse, ptr);
		ptr = strtok(NULL, ",");
		strcpy_e(nextStateNameTrue, ptr);
		ptr = strtok(NULL, ",");
		outputFalse = strcmp(ptr, " 1") == 0;
		ptr = strtok(NULL, ",");
		outputTrue = strcmp(ptr, " 1") == 0;
		nextStateTrue = NULL;
		nextStateFalse = NULL;
	}

	state(const state & c)
	{
		strcpy(stateName, c.stateName);
		strcpy(nextStateNameTrue, c.nextStateNameTrue);
		strcpy(nextStateNameFalse, c.nextStateNameFalse);
		nextStateFalse = c.nextStateFalse;
		nextStateTrue = c.nextStateTrue;
		outputFalse = c.outputFalse;
		outputTrue = c.outputTrue;
	}

	state(const state *c)
	{
		strcpy(stateName, c->stateName);
		strcpy(nextStateNameTrue, c->nextStateNameTrue);
		strcpy(nextStateNameFalse, c->nextStateNameFalse);
		nextStateFalse = c->nextStateFalse;
		nextStateTrue = c->nextStateTrue;
		outputFalse = c->outputFalse;
		outputTrue = c->outputTrue;
	}
};