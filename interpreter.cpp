#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
bool crashBool = false;
int lineCount;
	
struct anyType{
	string type;

	bool boolVal ;
	string strVal;
	int intVal;

	void printVal(){
		if(type == "bool"){
			cout <<boolVal;
		}
		else if(type == "string"){
			cout << strVal;
		}
		else if(type == "int"){
			cout << intVal;
		}
	}
};
void printVector(vector<string> list){
	for( int j = 0; j <list.size(); j++){
	    cout << list[j] << ", ";
	}
		
}
void handleError(string err, string extraInfo){
	cout << "ERROR: '" << err << "' at line " << lineCount << ". " << extraInfo << "\n";
	if(err != "two spaces"){
		crashBool = true;
	}
}

template<typename Out>
void splitHelper(const string &s, char delim, Out result) {
    stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		*(result++) = item;
	}
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
	splitHelper(s, delim, back_inserter(elems));
	for( int j = 0; j <s.size()-1; j++){
		if(s[j] == ' ' && s[j+1] == ' '){
			elems.erase(elems.begin()+j);
			handleError("two spaces", "Fixed error, attempting to continue.");
			j--;
		}
	}
	return elems;
}


void initializeReservedStrings( map<string,bool> *reservedStrings){
	reservedStrings->insert(pair<string,bool>("FOR", true));
	reservedStrings->insert(pair<string,bool>("PRINT", true));
	reservedStrings->insert(pair<string,bool>("ENDFOR", true));
	reservedStrings->insert(pair<string,bool>("PROC", true));
	reservedStrings->insert(pair<string,bool>("CALL",true));
}

vector<string> tokenize(string line){
	vector<string> lineList = split(line, ' '); 	
	return lineList;
}
int main() {
	string a = "hello my name is  x = i ;";
	string line;
	ifstream programFile ("TesterPrograms/prog1.zpm");
	map<string,anyType> values;
	map<string, bool> reservedStrings;
	initializeReservedStrings(&reservedStrings);
	string b = "hi";
	int c;
	istringstream(b) >> c;
	cout << c;

	if (programFile.is_open()){
		while(! programFile.eof()){
		lineCount++;
			getline(programFile, line);
			//cout << line << endl;
			vector<string> tokens = split(line, ' ');
			if(crashBool){
				return 1;
			}	
			for(int j=0; j<tokens.size();j++){					
				if(reservedStrings.count(tokens[j]) > 0){
					// do reserved strings stuff
				}
				else if(values.count(tokens[j]) > 0){
					if(tokens[j+1] == "="){
						anyType newVal;

						values.insert(pair<string,anyType>(tokens[j],newVal));	
					}
				}



			}
		}
	programFile.close();

	}	
	else cout << "Unable to open file. Check its the right file name.";

	return 0;
}



