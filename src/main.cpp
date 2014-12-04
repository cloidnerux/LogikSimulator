#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <random>
#include <time.h>

#include "state.h"

using namespace std;

//Parses an input string of a csv file to a list of states, returns the number of states
int parse(char * data, vector<shared_ptr<state>> & states);
int LoadFileAndParse(const char * fileName, vector<shared_ptr<state>> & states);
void DisplayStates(vector<shared_ptr<state>> & states);

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		cout << "To few arguments! Expected File" << endl;
		cout << "Quit" << endl;
		getchar();
		return 0;
	}
	vector<shared_ptr<state>> states;
	try
	{
		cout << "Loaded " << LoadFileAndParse(argv[1], states) << " States" << endl;
	}
	catch(string s)
	{
		cout << s << endl;
		getchar();
		return 0;
	}
	catch(...)
	{
		cout << "Unknown exception!" << endl;
		getchar();
		return 0;
	}
	DisplayStates(states);
	cout << "Start sim with random data" << endl;
	int cycles = 100;
	state * currentState = states[0].get();
	srand(time(NULL));
	bool input = (rand() % 2) > 0;
	for(int i = 0; i < cycles; i++)
	{
		input = (rand() % 2) > 0;
		cout << "State " << currentState->stateName << ", input: " << input;
		if(input)
		{
			cout << ", output: " << currentState->outputTrue << endl;
			currentState = currentState->nextStateTrue;
		}
		else
		{
			cout << ", output: " << currentState->outputFalse << endl;
			currentState = currentState->nextStateFalse;
		}
	}
	getchar();
	return 0;
}

int LoadFileAndParse(const char * fileName, vector<shared_ptr<state>> & states)
{
	ifstream * f = new ifstream(fileName, ios::in);
	if(!f->is_open())
	{
		cout << "File could not be opend!" << endl;
		f->close();
		delete f;
		return 0;
	}
	size_t start = f->tellg();
	f->seekg(0, ios::end);
	size_t length = f->tellg();
	length = length - start;
	char * buffer = new char[length];
	cout << "lenght: " << length << endl;
	f->seekg(0, ios::beg);
	f->read(buffer, length);
	int count = parse(buffer, states);
	delete buffer;
	delete f;
	return count;
}

int parse(char * data, vector<shared_ptr<state>> & states)
{
	char * end = strtok(data, "\n");
	char * delim;
	int filePos = 0;
	vector<char*> lines;
	do
	{
		if(strchr(end, '#') == NULL)
			lines.push_back(end);
		end=strtok(NULL, "\n");
	}while(end != NULL);
	for(int i = 0; i < lines.size(); i++)
	{
		try
		{
			states.push_back(make_shared<state>(new state(lines[i])));	
		}
		catch(...)
		{
			cout << "Error parsing line: " << i+1 << endl;
		}
	}
	for(int i = 0; i < states.size(); i++)
	{
		for(int a = 0; a < states.size(); a++)
		{
			if(strcmp(states[i]->nextStateNameFalse, states[a]->stateName) == 0)
			{
				states[i]->nextStateFalse = states[a].get();
			}
			if(strcmp(states[i]->nextStateNameTrue, states[a]->stateName) == 0)
			{
				states[i]->nextStateTrue = states[a].get();
			}
			if(states[i]->nextStateTrue != NULL && states[i]->nextStateFalse != NULL)
				break;
		}
	}
	return lines.size();
}

void DisplayStates(vector<shared_ptr<state>> & states)
{
	for (int i = 0; i < states.size(); i++)
	{
		cout << i << ": State " << states[i]->stateName << ", " << states[i]->nextStateNameFalse << ", " << states[i]->nextStateNameTrue << ", " << states[i]->outputFalse << ", " << states[i]->outputTrue << endl;
	}
}