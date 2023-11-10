#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char * argv[]){
	ifstream in(argv[1]);
	string opd1;
	string opr;
	string opd2;
	std::getline(in, opd1, ' ');
	std::getline(in, opr, ' ');
	std::getline(in, opd2, ' ');
	int opd1int = atoi(opd1.c_str());
	int opd2int = atoi(opd2.c_str());

	  if (opr == "*")
          {
		cout << opd1int * opd2int << "\n";
	  } 
          else if (opr == "/")
          {
		if (opd2int == 0)
                {
			cerr << "divide by 0\n"; 
		}
                else
                {
		        cout << opd1int / opd2int << "\n";
                }
	  } 
          else if (opr == "-")
          {
		cout << opd1int - opd2int << "\n";
	  } 
          else if (opr == "+")
          {
		cout << opd1int + opd2int << "\n";
	  } 
          else 
          {
                cerr << "bad opr " << opr << "\n";
	  }
}