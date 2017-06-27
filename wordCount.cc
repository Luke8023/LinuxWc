#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


struct Options{
  bool all;
  bool chars;
  bool words;
  bool lines;
  int numFiles;
  string* files;
  Options(): all(true), chars(false), words(false), lines(false), numFiles(0), files(nullptr) {}
  ~Options(){
    delete[] files;
  }
};

struct Counts{
  string name; 
  int chars;
  int words;
  int lines;
  Counts(): chars(0), words(0), lines(0){}
};

void printCounts(Counts& count, Options& ops){
	if(ops.numFiles == 0) {
		if((ops.lines == true) && (ops.words == true) && (ops.chars == false)) {
			cout << count.lines << ' ' << count.words << endl;
		} else if((ops.lines == true) && (ops.words == false) && (ops.chars == true)) {
			cout << count.lines << ' ' << count.chars << endl;
		} else if((ops.lines == false) && (ops.words == true) && (ops.chars == true)) {
			cout << count.words << ' ' << count.chars << endl;
		} else if((ops.lines == true) && (ops.words == false) && (ops.chars == false)) {
			cout << count.lines << endl;
		} else if((ops.lines == false) && (ops.words == true) && (ops.chars == false)) {
			cout << count.words << endl;
		} else if((ops.lines == false) && (ops.words == false) && (ops.chars == true)) {
			cout << count.chars << endl;
		} else {
			cout << count.lines << ' ' << count.words << ' ' << count.chars << endl;
		}
	} else {
		if((ops.lines == true) && (ops.words == true) && (ops.chars == false)) {
			cout << count.lines << ' ' << count.words << ' ' << count.name << endl;
		} else if((ops.lines == true) && (ops.words == false) && (ops.chars == true)) {
			cout << count.lines << ' ' << count.chars << ' ' << count.name << endl;
		} else if((ops.lines == false) && (ops.words == true) && (ops.chars == true)) {
			cout << count.words << ' ' << count.chars << ' ' << count.name << endl;
		} else if((ops.lines == true) && (ops.words == false) && (ops.chars == false)) {
			cout << count.lines << ' ' << count.name << endl;
		} else if((ops.lines == false) && (ops.words == true) && (ops.chars == false)) {
			cout << count.words << ' ' << count.name << endl;
		} else if((ops.lines == false) && (ops.words == false) && (ops.chars == true)) {
			cout << count.chars << ' ' << count.name << endl;
		} else {
			cout << count.lines << ' ' << count.words << ' ' << count.chars << ' ' << count.name << endl;
		}
	} 
}

void fillCounts(Counts& c, string input = "" ){
	char cur;
	string curs;
	istringstream ss{ input };
	istringstream temp{ input };
	while(ss >> noskipws >> cur) {
		if(cur == '\n') {
			c.lines++;
		} 
		c.chars++;
	}
	while(temp >> curs) {
		c.words++;
	}
}


string handleInputs(Counts& c, string name){
	ifstream fs{ name };
	ostringstream oss;
	string line;
	while(getline(fs, line)) {
		oss << line << endl;
	}
	string ret = oss.str();
	c.name = name;
	return ret;
}

void handleArgs(int argc, char* argv[], Options& ops){

	for (int i = 1; i < argc; ++i ){
		string s = argv[i];
		if(s == "-l") {
			ops.lines = true;
		} else if(s == "-w") {
			ops.words = true;
		} else if(s == "-c") {
			ops.chars = true;
		} else {
			(ops.numFiles)++;
		}
	}

	if ((!ops.lines) || (!ops.chars) || (!ops.words)) {
		ops.all = false;
	}
	ops.files = new string[ops.numFiles];
	for (int i = 1, k = 0; i < argc; ++i){
		string s = argv[i];
		if((s != "-l") && (s != "-w") && (s != "-c")) {
			ops.files[k] = s;
			++k;
		}
	}
}

int main(int argc, char* argv[]){
	Options ops;
	Counts c;
	int tl = 0;
	int tw = 0;
	int tc = 0;

	handleArgs(argc, argv, ops);
	
	if(ops.numFiles == 0) {
		string line;
		ostringstream oss;
		while(getline(cin, line)) {
			oss << line << endl;
		}
		string inputlines = oss.str();
		fillCounts(c, inputlines);
		printCounts(c, ops);
	} else if(ops.numFiles == 1) {
		string in = handleInputs(c, ops.files[0]);
		fillCounts(c, in);
		printCounts(c, ops);
	} else {	
		for(int i = 0; i < ops.numFiles; ++i) {
			string in = handleInputs(c, ops.files[i]);
			fillCounts(c, in);
			printCounts(c, ops);
			tl += c.lines;
			tw += c.words;
			tc += c.chars;
			c.lines = 0;
			c.chars = 0;
			c.words = 0;
		}
		if((ops.lines == true) && (ops.words == true) && (ops.chars == false)) {
			cout << tl << ' ' << tw << " total" << endl;
		} else if((ops.lines == true) && (ops.words == false) && (ops.chars == true)) {
			cout << tl << ' ' << tc << " total" << endl;
		} else if((ops.lines == false) && (ops.words == true) && (ops.chars == true)) {
			cout << tw << ' ' << tc << " total" << endl;
		} else if((ops.lines == true) && (ops.words == false) && (ops.chars == false)) {
			cout << tl << " total" << endl;
		} else if((ops.lines == false) && (ops.words == true) && (ops.chars == false)) {
			cout << tw << " total" << endl;
		} else if((ops.lines == false) && (ops.words == false) && (ops.chars == true)) {
			cout << tc << " total" << endl;
		} else {
			cout << tl << ' ' << tw << ' ' << tc << " total" << endl;
		}
	}
}
			
