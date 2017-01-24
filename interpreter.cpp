#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;


int main() {
string line;
ifstream programFile ("TesterPrograms/prog1.zpm");

	if (programFile.is_open()){
		while(! programFile.eof()){
            		getline(programFile, line);
            		//cout << line << endl;
					for(int j=0; j<line.length();j++){







					}
        	}
	 	programFile.close();

	 }
	else cout << "Unable to open file. Check its right file name.";

	return 0;
}

	
	
