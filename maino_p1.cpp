#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
This program simulates a Turing machine. It takes in  3 command line arguments:
	1. The name of the input file
	2. The initial input string
	3. The maximum number of transitions before the program should halt

The input file will have the following info:
	- Any number of special states (accept, reject, and start), and the number
	  of that state. 
		- These will be in the format "state	3	start"
	- Any number of transitions q,a->r,b,x. q is the current state, a is the symbol that the machine reads,
	  r is the new state, b is the symbol written over a, and x will signify whether to move right or left to 
	  the next symbol.
		- These will be in the format "transition	q	a	r	b	x" 
*/

using namespace std;

//This is the class for special states
class State {
	public:
		int value;	//0 to 1000
		string type; //accept, reject, or start
		State(int v, string t); 
};

State::State(int v, string t) {
	if( (v<0 || v > 1000) || (t != "accept" && t != "reject" && t != "start") ) {
		cout << "Error. States inputted with v = " << v << " and t = " << t << endl;
		exit(0);
	}
	value = v;
	type = t;
}

class Transition {
	public:
		int currState; //0 to 1000
		char initSymbol; //0 to 9, a to z, $, #, _, @
		int newState; 
		char newSymbol;
		char direction; //L or R
		Transition(int cs, char is, int ns, char ns, char d);
};

Transition:: Transition(int cst, char is, int nst, char ns, char d) {
	currState = cst;
	initSymbol = is;
	newState = nst;
	newSymbol = ns;
	direction = d;
}

void runMachine(string inputString, vector<State> states, vector<Transition> transitions, int maxTrans) {
	exit(0);
}


int main(int argc, char** argv) {
	if (argc !=4) {
		cout << "Error. Wrong amount of command line arguments." << endl;
		 exit(0);
	}

	string filename = argv[1];
	string inputString = argv[2];
	unsigned int maxTrans = stoi(argv[3], nullptr, 10);

	vector<string> lines;
	fstream file;
	file.open(filename);
	
}
