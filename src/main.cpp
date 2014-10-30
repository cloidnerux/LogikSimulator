#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "node.h"
#include "tFunc.h"
#include "XORFunc.h"
#include "ORFunc.h"
#include "ANDFunc.h"
#include "NotFunc.h"

using namespace std;

int main(int argc, char ** argv)
{
	vector<shared_ptr<node<bool>>> nodes;
	vector<shared_ptr<tFunc>> tFuncs;

	int INIT_CYCLES = 7;
	int SIM_CYCLES = 20;
	int MAX_CYCLES = SIM_CYCLES + INIT_CYCLES;

	//nodes.push_back(make_shared<node<bool>>(new node<bool>(0)));		//ID 0
	//nodes.push_back(make_shared<node<bool>>(new node<bool>(0)));		//ID 1
	//nodes.push_back(make_shared<node<bool>>(new node<bool>(0)));		//ID 2
	//nodes.push_back(make_shared<node<bool>>(new node<bool>(1)));		//ID 3
	//nodes.push_back(make_shared<node<bool>>(new node<bool>(1)));		//ID 4
	//nodes.push_back(make_shared<node<bool>>(new node<bool>(2)));		//ID 5
	//nodes.push_back(make_shared<node<bool>>(new node<bool>(2)));		//ID 6
	//nodes.push_back(make_shared<node<bool>>(new node<bool>(3)));		//ID 7

	//tFuncs.push_back(make_shared<XORFunc>(new XORFunc(nodes[0], nodes[1], nodes[3], 2)));
	//tFuncs.push_back(make_shared<XORFunc>(new XORFunc(nodes[2], nodes[3], nodes[5], 2)));
	//tFuncs.push_back(make_shared<ANDFunc>(new ANDFunc(nodes[0], nodes[1], nodes[4], 1)));
	//tFuncs.push_back(make_shared<ANDFunc>(new ANDFunc(nodes[2], nodes[3], nodes[6], 1)));
	//tFuncs.push_back(make_shared<ORFunc>(new ORFunc(nodes[6], nodes[4], nodes[7], 1)));

	nodes.push_back(make_shared<node<bool>>(new node<bool>(0)));		//ID 0
	nodes.push_back(make_shared<node<bool>>(new node<bool>(0)));		//ID 1
	nodes.push_back(make_shared<node<bool>>(new node<bool>(1)));		//ID 2
	nodes.push_back(make_shared<node<bool>>(new node<bool>(1)));		//ID 3
	nodes.push_back(make_shared<node<bool>>(new node<bool>(3)));		//ID 4
	nodes.push_back(make_shared<node<bool>>(new node<bool>(3)));		//ID 5
	nodes.push_back(make_shared<node<bool>>(new node<bool>(2)));		//ID 6
	nodes.push_back(make_shared<node<bool>>(new node<bool>(2)));		//ID 7
	nodes.push_back(make_shared<node<bool>>(new node<bool>(5)));		//ID 8
	nodes.push_back(make_shared<node<bool>>(new node<bool>(5)));		//ID 9

	nodes.push_back(make_shared<node<bool>>(new node<bool>(4)));		//ID 10
	nodes.push_back(make_shared<node<bool>>(new node<bool>(4)));		//ID 11
	nodes.push_back(make_shared<node<bool>>(new node<bool>(6)));		//ID 12
	nodes.push_back(make_shared<node<bool>>(new node<bool>(6)));		//ID 13
	nodes.push_back(make_shared<node<bool>>(new node<bool>(7)));		//ID 14
	nodes.push_back(make_shared<node<bool>>(new node<bool>(7)));		//ID 15
	nodes.push_back(make_shared<node<bool>>(new node<bool>(8)));		//ID 16
	nodes.push_back(make_shared<node<bool>>(new node<bool>(8)));		//ID 17
	nodes.push_back(make_shared<node<bool>>(new node<bool>(9)));		//ID 18
	nodes.push_back(make_shared<node<bool>>(new node<bool>(9)));		//ID 19

	nodes.push_back(make_shared<node<bool>>(new node<bool>(10)));		//ID 20
	nodes.push_back(make_shared<node<bool>>(new node<bool>(10)));		//ID 21

	tFuncs.push_back(make_shared<ORFunc>(new ORFunc(nodes[3], nodes[4], nodes[6], 1)));
	tFuncs.push_back(make_shared<ORFunc>(new ORFunc(nodes[2], nodes[5], nodes[7], 1)));
	tFuncs.push_back(make_shared<ORFunc>(new ORFunc(nodes[15], nodes[19], nodes[20], 1)));
	tFuncs.push_back(make_shared<ORFunc>(new ORFunc(nodes[18], nodes[14], nodes[21], 1)));
	tFuncs.push_back(make_shared<ANDFunc>(new ANDFunc(nodes[0], nodes[6], nodes[5], 1)));
	tFuncs.push_back(make_shared<ANDFunc>(new ANDFunc(nodes[1], nodes[7], nodes[4], 1)));
	tFuncs.push_back(make_shared<ANDFunc>(new ANDFunc(nodes[5], nodes[8], nodes[11], 1)));
	tFuncs.push_back(make_shared<ANDFunc>(new ANDFunc(nodes[4], nodes[9], nodes[10], 1)));
	tFuncs.push_back(make_shared<ANDFunc>(new ANDFunc(nodes[4], nodes[12], nodes[15], 1)));
	tFuncs.push_back(make_shared<ANDFunc>(new ANDFunc(nodes[5], nodes[13], nodes[14], 1)));

	tFuncs.push_back(make_shared<ANDFunc>(new ANDFunc(nodes[12], nodes[16], nodes[18], 1)));
	tFuncs.push_back(make_shared<ANDFunc>(new ANDFunc(nodes[13], nodes[17], nodes[19], 1)));
	tFuncs.push_back(make_shared<NOTFunc>(new NOTFunc(nodes[1], nodes[3], 1)));
	tFuncs.push_back(make_shared<NOTFunc>(new NOTFunc(nodes[0], nodes[2], 1)));
	tFuncs.push_back(make_shared<NOTFunc>(new NOTFunc(nodes[10], nodes[8], 1)));
	tFuncs.push_back(make_shared<NOTFunc>(new NOTFunc(nodes[11], nodes[9], 1)));
	tFuncs.push_back(make_shared<NOTFunc>(new NOTFunc(nodes[8], nodes[13], 1)));
	tFuncs.push_back(make_shared<NOTFunc>(new NOTFunc(nodes[9], nodes[12], 1)));
	tFuncs.push_back(make_shared<NOTFunc>(new NOTFunc(nodes[15], nodes[16], 1)));
	tFuncs.push_back(make_shared<NOTFunc>(new NOTFunc(nodes[14], nodes[17], 1)));


	auto_ptr<bool> data(new bool[nodes.size() * MAX_CYCLES]);		//In this array we store the state of all nodes for each iteration

	memset(data.get(), 0, sizeof(bool) * nodes.size() * MAX_CYCLES);	//Ensure the array is cleared

	string s;

	for(int cycle = 0; cycle < MAX_CYCLES; cycle++)
	{
		try
		{
			if( cycle >= INIT_CYCLES)
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
			}
			else
			{
				nodes[0].get()->state = false;
				nodes[1].get()->state = false;
			}
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
			cout << "Result - q1 = " << nodes[20].get()->state << ", q2 = " << nodes[21].get()->state << endl;
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