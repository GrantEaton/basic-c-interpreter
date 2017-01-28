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

	bool boolVal;
	string strVal;
	int intVal;
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
		}
	}
	return elems;
}

bool isReserved(string token){

}	

void initializeReservedStrings( map<string,bool> *reservedStrings){
	reservedStrings->insert(pair<string,int>("FOR", true));
	reservedStrings->insert(pair<string,int>("PRINT", true));
	reservedStrings->insert(pair<string,int>("ENDFOR", true));
	reservedStrings->insert(pair<string,int>("PROC", true));
	reservedStrings->insert(pair<string,int>("CALL",true));
}

vector<string> tokenize(string line){
	vector<string> lineList = split(line, ' '); 	
	return lineList;
}
int main() {
	string a = "hello my name is  x = i ;";
	vector<string> list = split(a, ' ');
	printVector(list);
	string line;
	ifstream programFile ("TesterPrograms/prog1.zpm");
	map<string,anyType> values;
	map<string, bool> reservedStrings;
	initializeReservedStrings(&reservedStrings);

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
								




			}
		}
	programFile.close();

	}	
	else cout << "Unable to open file. Check its the right file name.";

	return 0;
}



