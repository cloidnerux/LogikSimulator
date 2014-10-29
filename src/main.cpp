#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "node.h"
#include "tFunc.h"
#include "XORFunc.h"
#include "ORFunc.h"
#include "ANDFunc.h"

using namespace std;

int main(int argc, char ** argv)
{
	vector<shared_ptr<node<bool>>> nodes;
	vector<shared_ptr<tFunc>> tFuncs;

	int MAX_CYCLES = 10;

	nodes.push_back(make_shared<node<bool>>(new node<bool>(0)));		//ID 0
	nodes.push_back(make_shared<node<bool>>(new node<bool>(0)));		//ID 1
	nodes.push_back(make_shared<node<bool>>(new node<bool>(0)));		//ID 2
	nodes.push_back(make_shared<node<bool>>(new node<bool>(1)));		//ID 3
	nodes.push_back(make_shared<node<bool>>(new node<bool>(1)));		//ID 4
	nodes.push_back(make_shared<node<bool>>(new node<bool>(2)));		//ID 5
	nodes.push_back(make_shared<node<bool>>(new node<bool>(2)));		//ID 6
	nodes.push_back(make_shared<node<bool>>(new node<bool>(3)));		//ID 7

	tFuncs.push_back(make_shared<XORFunc>(new XORFunc(nodes[0], nodes[1], nodes[3], 2)));
	tFuncs.push_back(make_shared<XORFunc>(new XORFunc(nodes[2], nodes[3], nodes[5], 2)));
	tFuncs.push_back(make_shared<ANDFunc>(new ANDFunc(nodes[0], nodes[1], nodes[4], 1)));
	tFuncs.push_back(make_shared<ANDFunc>(new ANDFunc(nodes[2], nodes[3], nodes[6], 1)));
	tFuncs.push_back(make_shared<ORFunc>(new ORFunc(nodes[6], nodes[4], nodes[7], 1)));

	auto_ptr<bool> data(new bool[nodes.size() * MAX_CYCLES]);		//In this array we store the state of all nodes for each iteration

	memset(data.get(), 0, sizeof(bool) * nodes.size() * MAX_CYCLES);	//Ensure the array is cleared

	string s;

	for(int cycle = 0; cycle < MAX_CYCLES; cycle++)
	{
		try
		{
			/////////////////////////////////////////////////////////////////////
			//One way of providing inputs
			cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
			cout << "cycle time: " << cycle << endl << endl;
			cout << "Input state for a (0, 1, keep): ";
			cin >> s;
			if(s == "1")
				nodes[0].get()->state = true;
			else if(s == "0")
				nodes[0].get()->state = false;
			cout << "Input state for b (0, 1, keep): ";
			cin >> s;
			if(s == "1")
				nodes[1].get()->state = true;
			else if(s == "0")
				nodes[1].get()->state = false;
			cout << "Input state for c (0, 1, keep): ";
			cin >> s;
			if(s == "1")
				nodes[2].get()->state = true;
			else if(s == "0")
				nodes[2].get()->state = false;
			/////////////////////////////////////////////////////////////////////

			//main simulation loop, iterate through every node and update everything
			for(auto it = nodes.begin(); it != nodes.end(); it++)
			{
				it->get()->Update(cycle);
			}
			/////////////////////////////////////////////////////////////////////
			//DEBUG - Output the type, inputs and outputs of every transfer function to see if some have wrong inputs or errors in the transfer function
#ifdef DEBUG
			for(auto it = tFuncs.begin(); it != tFuncs.end(); it++)
			{
				cout << "Type: " << it->get()->GetType() << " with " << it->get()->GetState() << endl;
			}
#endif
			/////////////////////////////////////////////////////////////////////
			//output the result for this particular case
			cout << "Result - q = " << nodes[5].get()->state << ", c = " << nodes[7].get()->state << endl;
			/////////////////////////////////////////////////////////////////////
			//save the actuall node states in an array to analyse later
			for(unsigned int i = 0; i < nodes.size(); i++)
			{
				data.get()[i + cycle * nodes.size()] = nodes[i].get()->state;
			}
		}
		catch(const char * a)
		{
			cout << a << endl;
			cout.flush();
			cin >> s;
			return 0;
		}
		catch(...)
		{
			cout << "Exception in cycle " << cycle << endl;
			cout.flush();
			cin >> s;
			return 0;
		}
	}

	for(int a = 0; a < nodes.size(); a++)
	{
		cout << "Node " << a << ": ";
		for(int i = 0; i < MAX_CYCLES; i++)
		{
			cout << data.get()[a + i * nodes.size()];
		}
		cout << endl;
	}
	cout.flush();
	cin >> s;
	return 0;
}