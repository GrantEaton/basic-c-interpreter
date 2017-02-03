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
			cout <<boolVal << "\n";
		}
		else if(type == "string"){
			cout << strVal << "\n";
		}
		else if(type == "int"){
			cout << intVal << "\n";
		}
	}
};

bool crashBool = false;
int lineCount;
map<string,anyType> vars;
map<string, bool> reservedStrings;

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


vector<string> split(string &s, char delim, bool parseFor) {
	//cout << "FOUND:"<<nthSubstr(1,s,"FOR");
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
	string loopString = "";
	for(int j = 0; j < s.length(); j++){
		
		if(s.at(j) == '"'){
			isString = !isString;
		}
		if(isString && s.at(j) == ' '){
			s[j] = '~';
		}
	}
	if(parseFor){
		int forIndex = (nthSubstr(1,s, "FOR")); 
		if(forIndex != -1){
			int endForIndex;
			for(int j = forIndex; j < s.length()-6; j++){
				endForIndex = nthSubstr(1,s,"ENDFOR") + 6;
				if(s.substr(j,j+6) == "ENDFOR"){
					endForIndex = j+6;	
					//cout << "ENDFOR INDEX:" << endForIndex << "\n";
				}
			}

			loopString = s.substr(forIndex, endForIndex);
			//cout <<"FOUND LOOPSTRING:"<< loopString << "\n";
			s = s.substr(0,forIndex) +"% ;"+ s.substr(endForIndex, s.length());
			//cout << "AFTER ADDING %:" << s << "\n";
		}
	}
	splitHelper(s, delim, back_inserter(elems));
	//fix string to have spaces again
	for(int i = 0; i< elems.size(); i++){
		//chop off spaces at start and finish
		if(elems.at(i)[0] == ' '){
			elems.at(i) = elems.at(i).substr(1,elems.at(i).length());
			//cout << "CHOPPED OFF START: " << elems.at(i) << "\n";
		}
		if(elems.at(i)[elems.at(i).length()-1] == ' '){
			elems.at(i) = elems.at(i).substr(0,elems.at(i).length()-1);
			//cout << "CHOPPED OFF END: " << elems.at(i)  << "\n";
		}

		if(elems.at(i)[0] != '"' && elems.at(i)[0] != '%'){
			continue;
		}
		if(elems.at(i)[0] == '%'){
				elems[i] = loopString;
		}
		for(int k = 0; k < elems.at(i).size(); k++){
			if(elems.at(i).at(k) == '~'){
				elems.at(i)[k] = ' ';
			}
		
		}
	}
	

	return elems;
}
vector<string> handleFOR(string line, char delim){
	int secondSpace = nthSubstr(2,line," ");
	//cout << "SECOND SPACE INDEX: " << secondSpace << "\n";
	line = line.substr(secondSpace, line.length());
	line = line.substr(0, line.length()-8);
	vector<string> statements = split(line, ';',true);
	return statements;
}



void initializeReservedStrings( map<string,bool> *reservedStrings){
	reservedStrings->insert(pair<string,bool>("FOR", true));
	reservedStrings->insert(pair<string,bool>("PRINT", true));
	reservedStrings->insert(pair<string,bool>("ENDFOR", true));
	reservedStrings->insert(pair<string,bool>("PROC", true));
	reservedStrings->insert(pair<string,bool>("CALL",true));
}

vector<string> tokenize(string line){
	vector<string> lineList = split(line, ' ',false); 	
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
void executeStatement(string statement){
	vector<string> tokens = tokenize(statement);
	//cout << "tokens: ";
	//printVector(tokens);
	//cout << "\n";
	if(isReservedString(tokens[0], &reservedStrings)){
				// do reserved strings stuff
				if(tokens.at(0) == "PRINT"){
					//cout << "printing : ";
					anyType var = vars[tokens.at(1)];
					var.printVal();
					//cout << "\n";
				}
				else if(tokens.at(0) == "FOR"){
					int numRepeat;
					stringstream convert(tokens.at(1));
					convert >> numRepeat;
					
					for(int j=0; j<numRepeat; j++){
						vector<string> statements = handleFOR(statement, ';');
						for(int i = 0; i< statements.size(); i++){
							//cout << "statement:" <<statements.at(i);
							executeStatement(statements.at(i));
						}
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
								//cout << "adding value: " << num.intVal;
								vars[tokens.at(0)] = num;
								//cout << "\n";
					
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
							//cout << "after +=: " << var.intVal << "\n";
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
							//cout << "after *=: " << var.intVal << "\n";
							vars[tokens.at(0)] = var;	
					}
					else if (tokens.at(1) == "/="){
						anyType var = vars[tokens.at(0)];
					
							int intVal;
							if(isdigit(tokens.at(2)[0])){
								stringstream convert(tokens.at(2));
								convert >> intVal;
								var.intVal = var.intVal / intVal;	
					
							}else{//its a variable
							
								var.intVal = var.intVal / vars[tokens.at(2)].intVal;
								
							}
							//cout << "after /=: " << var.intVal << "\n";
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
							//cout << "after -=: " << var.intVal << "\n";
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
						//cout << "adding value: " << num.intVal << "\n";
						vars.insert(pair<string,anyType>(tokens.at(0),num ));
					
					}

				}
}
										 
int main(int argc, char* argv[]) {
	string a = "hello my name is  x = i ;";
	string line;
	//cout << *argv[1];
	string arg = argv[1];
	string file = ("TesterPrograms/" + arg);
	cout << file;
	ifstream programFile(""+ file);
	initializeReservedStrings(&reservedStrings);

	if (programFile.is_open()){
		while(getline(programFile, line)){
			lineCount++;
			//cout << "line count" << lineCount << "\n";
						//cout << lineCount << ": ";
			//cout << "line: " <<  line << endl;
			
			
			if(crashBool){
				return 1;
			}	
			else{
				executeStatement(line);
			}
		}


			//}
		}

	else cout << "Unable to open file. Check its the right file name.";

	programFile.close();
	return 0;
}


