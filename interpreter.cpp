#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
	
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

bool crashBool = false;
int lineCount;
map<string,anyType> vars;
map<string, bool> reservedStrings;


void printVector(vector<string> list){
	for( int j = 0; j <list.size(); j++){
	    cout << list[j] << ", ";
	}
	cout << "\n";		
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

vector<string> split(string &s, char delim) {
    vector<string> elems;
	//check for two spaces in a row
	for( int j = 0; j <s.size()-1; j++){
		if(s.at(j) == ' ' && s.at(j+1) == ' '){
			elems.erase(elems.begin()+j);
			handleError("two spaces", "Fixed error, attempting to continue.");
			j--;
		}
		
	}
	//if there are spaces in a string
	bool isString = false;
	for(int j = 0; j < s.length(); j++){
			
		if(s.at(j) == '"'){
			isString = !isString;
		}
		if(isString && s.at(j) == ' '){
			s[j] = '~';
		}
	}
	splitHelper(s, delim, back_inserter(elems));
	//fix string to have spaces again
	for(int i = 0; i< elems.size(); i++){
		//chop off spaces at start and finish
		if(elems.at(i)[0] == ' '){
			elems.at(i) = elems.at(i).substr(1,elems.at(i).length());
			cout << "CHOPPED OFF START: " << elems.at(i) << "\n";
		}
		if(elems.at(i)[elems.at(i).length()-1] == ' '){
			elems.at(i) = elems.at(i).substr(0,elems.at(i).length()-2);
			cout << "CHOPPED OFF END: " << elems.at(i)  << "\n";
		}

		if(elems.at(i)[0] != '"'){
			continue;
		}
		for(int k = 0; k < elems.at(i).size(); k++){
			if(elems.at(i).at(k) == '~'){
				elems.at(i)[k] = ' ';
			}
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
//check if string is in vars map
bool isVariable(string var, map<string,anyType> *vars){
	if(vars->count(var) > 0){
		return true;
	}
	return false;

}
//check if string is a reserved string
bool isReservedString(string reservedString, map<string,bool> *reservedStrings){
	if(reservedStrings->count(reservedString) > 0){
		return true;
	}
	return false;

}
void executeStatement(vector<string> tokens){
	if(isReservedString(tokens[0], &reservedStrings)){
				// do reserved strings stuff
				if(tokens.at(0) == "PRINT"){
					cout << "printing : ";
					anyType var = vars[tokens.at(1)];
					var.printVal();
					cout << "\n";
				}
				else if(tokens.at(0) == "FOR"){
					int numRepeat;
					stringstream convert(tokens.at(1));
					convert >> numRepeat;
					
					for(int j=0; j<numRepeat; j++){
						
					}
				}
	}

	 else if(vars.count(tokens[0]) > 0){
					if(tokens.at(1) == "="){
						anyType newVal;
						//if first value of next token is a previous value
						//ex A = B
						if(isVariable(tokens.at(2),&vars)){
							//assign B's val to A
							anyType val = vars[tokens.at(2)];
							vars.insert(pair<string,anyType>(tokens.at(2), val));
						}
						//assigning var to new string/int
						else{
							if(tokens.at(2).at(0) == '"'){
								anyType str;
								str.type = "string";
								str.strVal = tokens.at(2).substr(1,tokens.at(2).length()-2);
								vars[tokens.at(0)] = str;

							//add string values
							}else {
								anyType num;
								num.type = "int";
								stringstream convert(tokens.at(2));
								convert >> num.intVal;
								cout << "adding value: " << num.intVal;
								vars[tokens.at(0)] = num;
								cout << "\n";
					
							}
						
						}
							
					vars.insert(pair<string,anyType>(tokens.at(0),newVal));	
					}
						
					else if (tokens.at(1) == "+="){
						anyType var = vars[tokens.at(0)];
						if(var.type == "string"){
							string newStr;
							//check if value is string or variable
							if(tokens.at(2)[0] == '"'){
								newStr = var.strVal + tokens.at(2).substr(1,tokens.at(2).length()-2);
							}
							else{//its a variable
								newStr = var.strVal + vars[tokens.at(2)].strVal;
							}
							var.strVal = newStr;
							vars[tokens.at(0)] = var;	
						}
						else{//it must be an int
							int intVal;
							if(isdigit(tokens.at(2)[0])){
								stringstream convert(tokens.at(2));
								convert >> intVal;
								var.intVal = var.intVal + intVal;	
					
							}else{//its a variable
							
								var.intVal = var.intVal + vars[tokens.at(2)].intVal;
								
							}
							cout << "after +=: " << var.intVal << "\n";
							vars[tokens.at(0)] = var;	
						}
					}
					else if (tokens.at(1) == "*="){
						anyType var = vars[tokens.at(0)];
					
							int intVal;
							if(isdigit(tokens.at(2)[0])){
								stringstream convert(tokens.at(2));
								convert >> intVal;
								var.intVal = var.intVal * intVal;	
					
							}else{//its a variable
							
								var.intVal = var.intVal * vars[tokens.at(2)].intVal;
								
							}
							cout << "after *=: " << var.intVal << "\n";
							vars[tokens.at(0)] = var;	
					}
					else if (tokens.at(1) == "-="){
						anyType var = vars[tokens.at(0)];
					
							int intVal;
							if(isdigit(tokens.at(2)[0])){
								stringstream convert(tokens.at(2));
								convert >> intVal;
								var.intVal = var.intVal - intVal;	
					
							}else{//its a variable
							
								var.intVal = var.intVal - vars[tokens.at(2)].intVal;
								
							}
							cout << "after -=: " << var.intVal << "\n";
							vars[tokens.at(0)] = var;	
					}
				}
				//add variables if not in vars
				else{
					//add int values
					if(tokens.at(2).at(0) == '"'){
						anyType str;
						str.type = "string";
						str.strVal = tokens.at(2).substr(1,tokens.at(2).length()-2);
						vars.insert(pair<string,anyType>(tokens.at(0),str ));
					//add string values
					}else {
						anyType num;
						num.type = "int";
						stringstream convert(tokens.at(2));
						convert >> num.intVal;
						cout << "adding value: " << num.intVal << "\n";
						vars.insert(pair<string,anyType>(tokens.at(0),num ));
					
					}

				}
}
int nthSubstr(int n, const string& s,
			 const string& p) {
			string::size_type i = s.find(p);     // Find the first occurrence

			int j;
	  	   for (j = 1; j < n && i != string::npos; ++j)
		        i = s.find(p, i+1); // Find the next occurrence

			    if (j == n)
				     return(i);
			    else
					return(-1);
}
											 
vector<string> handleFOR(string line, char delim){
	int secondSpace = nthSubstr(2,line," ");
	cout << "SECOND SPACE INDEX: " << secondSpace << "\n";
	line = line.substr(secondSpace, line.length()-7);
	cout << "LINE AFTER: " << line  << "\n";
	vector<string> statements = split(line, ';');
	return statements;
}

int main() {
	string a = "hello my name is  x = i ;";
	string line;
	ifstream programFile ("TesterPrograms/prog3.zpm");
	initializeReservedStrings(&reservedStrings);

	if (programFile.is_open()){
		while(getline(programFile, line)){
			lineCount++;
			//cout << "line count" << lineCount << "\n";
						//cout << lineCount << ": ";
			//cout << "line: " <<  line << endl;
			

			vector<string> tokens = tokenize(line); 
			if(tokens.at(0) == "FOR"){
				int numRepeat;
				stringstream convert(tokens.at(1));
				convert >> numRepeat;
					
				for(int j=0; j<numRepeat; j++){
					vector<string> statements = handleFOR(line, ';');
					for(int i = 0; i< statements.size(); i++){
						cout << "statement:" <<statements.at(i);
						vector<string> tokens = tokenize(statements.at(i));
						executeStatement(tokens);
					}
				}
			}
			cout << "tokens: ";
			printVector(tokens);
			if(crashBool){
				return 1;
			}	
			else{
				executeStatement(tokens);
			}
		}


			//}
		}

	else cout << "Unable to open file. Check its the right file name.";

	programFile.close();
	return 0;
}


