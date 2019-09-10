#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class TuringMachine {
	public:
		
};


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
