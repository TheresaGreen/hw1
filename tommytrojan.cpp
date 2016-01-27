#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int floors;
  int *floorsizes;
  string ***trojans;
  string curr;

  input >> floors;
  trojans = new string**[floors];
  //you will need to keep track of how many people are on each floor.
  floorsizes = new int[floors];
  
  for (int i = 0; i < floors; i++) {
	  floorsizes[i] = 0;
	  trojans[i] = NULL;
  }

  while(getline(input, curr)) {
	  stringstream ss;
	  ss << curr;
	  ss >> curr;
	  if (curr == "MOVEIN") //k students are going to live on floor i
	  {
		  int i,k;
		  ss >> i;
		  ss >> k;
		 
		  if (ss.fail()) {
			  output << "Error - incorrect command" << endl;
		  }
		  else {
		    
		    if (i>floors || i<0) //check if floor exists
		    	{output<< "Error - floor "<<i<<" does not exist"<<endl;}	
		    else if (floorsizes[i]!=0)//check if the floor is empty 
		    {   output<< "Error - floor "<<i<<" is not empty"<<endl;
		    }
		  	else//second lets move them in
		  	{  
		  	 floorsizes[i]= k;//change size of floor
              trojans[i]= new string*[k];
              for (int j=0; j<k; j++)
              {
               trojans[i][j]=NULL;
              }
            }
        
		  	}

		  }

	  else if (curr == "MOVEOUT") //kick out all students from floor i
	  {
	  	int i;
	  	ss>>i;
	  	if (ss.fail()) {
			  output << "Error - incorrect command" << endl;
		  }
		  else {
		  	if (i>floors || i<=0) //check if floor exists
		    	{output<< "Error - floor "<<i<<" does not exist"<<endl;}	
		    else if (floorsizes[i]==0)//check if the floor is empty 
		    {   output<< "Error - floor "<<i<<" is already empty"<<endl;
		    }
		  	else//second lets move them in
		  	{
             for (int j; j< floorsizes[i]; j++)//check if the student has stuff
             { if (trojans[i][j]!=NULL)//the student is not stuff free
                { delete trojans[i][j]; }
             }
             delete trojans[i];
             floorsizes[i]=0;//change size of floor
		  	}

		  }


	  }
	  else if (curr == "OBTAIN")
	   {
	  	int i,j,k;
	  	ss>>i;
	  	ss>>j;
	  	ss>>k;//k is the number of things the student have
	  	if (ss.fail()) {
			  output << "Error - incorrect command" << endl;
		  }
	    else 
	    {
		  	if (trojans[i][j]!= NULL)//already has stuff
		  	{
		  		output << "Error - student "<<j<<" living on floor "<<i<<" already has items"<<endl;
		    }
		    else if (floorsizes[i]<j)//if there is no person
		    { 
		    	output << "Error - this person doesn't exist"<<endl;
		    }
		    else
		    {  trojans[i][j] = new string[k+1];
		    	for (int f=0; f < k; f++)//loop through and add the items in
		    	{ string item;
		    	  ss>>item;
		    	  if (ss.fail())
		    	   {
			         output << "Error - incorrect command" << endl;
		          }
		    	  trojans[i][j][f]= item;
		        
		        }
		        trojans[i][j][k]= "stop";
		    }

		  }

	  }
	  else if (curr == "OUTPUT") //ouput possesions of student j living on floor i
	   {
	     int i,j;
	     ss>>i;
	     ss>>j;
	     if (ss.fail()) {
			  output << "Error - incorrect command" << endl;
		  }
		  else if (floorsizes[i]<j)
		  {
		  output<<"Error- There is no student "<<j<<" on this floor"<<endl;
		  }
		  else if (trojans[i][j]==NULL)
		  {
		  	output<<"Error - this student has no possesions"<<endl;
		  }
          else//you want to output all the items to output.txt
          {  int count = 0;
          	 while (trojans[i][j][count]!= "stop"){
          	 	output<<trojans[i][j][count]<<" ";
          	 	count++;
          	}
          	output<<endl;
		  }

        }
  }
//Everything is done everywhere now lets give back all the memory

for (int c=0; c <floors; c++)
{
	for (int r=1; r <floorsizes[c]; r++)
	{   if (trojans[c][r]!=NULL)
		{ 
			delete trojans[c][r];//have to delete "stop"
		}
		delete trojans[c][r];
	}
delete trojans[c];
}
delete[] trojans;

  return 0;
}