#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

void printhelper(int size, ifstream& the_file){
	if (size==0){}//there's nothing to do
	else
	{   string word;
		the_file>>word;
		printhelper(size-1, the_file);
		cout<<word<<endl;
	}	
	return;
}


int main ( int argc, char *argv[]) {
if (argc!=2) //the wrong command
	{ cout<< "I'm sorry but that command doesnt make sense!"<<endl;
	}
else
{
 ifstream file (argv[1]);
 //see if the file is open
    if ( !file.is_open() )
    { cout <<"This file wasn't able to be opened"<<endl;
    }
  string s;
  file>>s;
  int size = atoi(s.c_str());

  printhelper(size, file);
  
}

}