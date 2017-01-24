#include <iostream>
#include <fstream>
using namespace std;


int main() {
cout << "hello";
string line;
ifstream programFile ("TesterPrograms/prog1.zpm");

	if (programFile.is_open()){
		while(! programFile.eof()){
            		programFile >> line;
            		cout << line << endl;
        	}
	 	programFile.close();

	 }
	else cout << "Unable to open file. Check you have the right file name.";

	return 0;
}

