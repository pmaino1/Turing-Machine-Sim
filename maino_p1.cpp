#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
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

//This is the class for special states. Regular states will NOT be kpet track of using this class.
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
		Transition(int cst, char is, int nst, char ns, char d);
};

Transition:: Transition(int cst, char is, int nst, char ns, char d) {
	currState = cst;
	initSymbol = is;
	newState = nst;
	newSymbol = ns;
	direction = d;
}

//Takes a value and a vector of states, and determines if the state with that value is an accept state
bool isAccept(int value, vector<State> states) {
	for(auto i = states.begin(); i != states.end(); i++) {
		if( (*i).type == "accept" && value == (*i).value ) {
			return true;
		}
	}
	return false;
}

//Takes a value and a vector of states, and determines if the state with that value is a reject state
bool isReject(int value, vector<State> states) {
	for(auto i = states.begin(); i != states.end(); i++) {
		if( (*i).type == "reject" && (*i).value == value ) {
			return true;
		}
	}
	return false;
}

void runMachine(string inputString, vector<State> states, vector<Transition> transitions, int maxTrans) {
	int numTrans = 0;
	int currState;
	auto inputIndex = inputString.begin();

	//determine start state
	for(auto i = states.begin(); i!= states.end(); i++) {
		if( (*i).type == "start") {
			currState = (*i).value;
		}
	}
	cout << currState;

	while(!isAccept(currState, states) && !isReject(currState,states) && numTrans != maxTrans ) {
		char currSymbol = (*inputIndex);
		Transition nextTrans = Transition(-1,'a',-1,'a','a'); //junk Transition

		//search through transitions for one that matches our current state and symbol
		for(auto i = transitions.begin(); i != transitions.end(); i++) {
			if(currState == (*i).currState && currSymbol == (*i).initSymbol ) {
				nextTrans = (*i);
			} 
		}
		if(nextTrans.currState == -1) { cout << "Error. No matching transition found for state " << currState << " and symbol " << currSymbol << endl; }

		//apply the next transition
		currState = nextTrans.newState;
		(*inputIndex) = nextTrans.newSymbol;
		
		if(nextTrans.direction == 'R') {
			inputIndex++;
		} else {
			inputIndex--;
		}
		numTrans++;
		//print out this transition
		cout << "->" << currState;
	}
	if(isAccept(currState,states)) {
		cout << " accept" << endl;
	}
	else if(isReject(currState,states)) {
		cout << " reject" << endl;
	}
	else if(numTrans == maxTrans) {
		cout << " quit" << endl;
	}
	else{
		cout<< "I really don't know how this could have happened but if you see this, something went awfully wrong." << endl;
	}

	//print out final portion, depending on how the machine finishes
}


int main(int argc, char** argv) {
	if (argc !=4) {
		cout << "Error. Wrong amount of command line arguments." << endl;
		 exit(0);
	}

	string filename = argv[1];
	string inputString = argv[2];
	unsigned int maxTrans = stoi(argv[3], nullptr, 10);

	//Read in file
	vector<string> lines;
	fstream file;
	//cout << filename <<endl;
	file.open(filename);

	if(file.is_open()) {
		string line;
		while(getline(file,line)) {
			//cout << line << endl;
			lines.push_back(line);
		}
		file.close();
	}
	else {
		cout << "Error. File not found/Error opening file." << endl;
		exit(0);
	}

	//Create necessary objects
	vector<State> states;
	vector<Transition> transitions;

	for(auto i = lines.begin(); i != lines.end(); i++) {
	// (*i) is the individual string, one for each line
    		istringstream iss(*i);
    		string tok;
    		getline(iss, tok, '	');
		
		//gets rid of any extra whitespace
		int pos = tok.find_first_of(" ");
		while(pos != -1) {
			tok.erase(pos,1);
			pos = tok.find_first_of(" ");
		}


		if( tok == "state" ) {
			//cout << "State Tokenize" << endl;
			int val;
			string type;

			getline(iss, tok, '	');
			val = stoi(tok, nullptr, 10);
			getline(iss, tok, '	');
			type = tok;

			//cout << val << " " << type << endl;
			State temp = State(val,type);
			states.push_back(temp);
		}
		else if( tok == "transition" ) {
			//cout <<"Transition Tokenize Placeholder" << endl;
			int cst;
			string is;
			int nst;
			string ns;
			string d;

			getline(iss, tok, '	');
			cst = stoi(tok, nullptr, 10);
			getline(iss, tok, '	');
			is = tok;
			getline(iss, tok, '	');
			nst = stoi(tok, nullptr, 10);
			getline(iss, tok, '	');
			ns = tok;
			getline(iss, tok, '	');
			d = tok;
			
			//cout << cst << " " << is << " " << nst << " " << ns << " " << d << endl;
			Transition temp = Transition(cst,is[0],nst,ns[0],d[0]);
			transitions.push_back(temp);
		}
		else {
			cout << "Error. Read '" << tok << "' as first token of line." << endl;
		}
	}

	runMachine(inputString, states, transitions, maxTrans);

	exit(0);
}
