//Josh Temple 
//CruzID: Jktemple 
//PA5

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include "List.h"

using namespace std;

void shuffle(List& D){
	List left;
	List right;
	D.moveFront();
	for(int i = 0; i < D.length()/2; i++){
		try{
		       left.insertBefore(D.moveNext());	
		} catch(range_error& e) {
			break;
		}
	}
	while(1){
		try{ 
			right.insertBefore(D.moveNext());
		} catch(range_error& e) {
			break;
		}
	}
	D.clear();
	left.moveFront();
	right.moveFront();
	while(1){	
		try {
			D.insertBefore(right.moveNext());
		} catch (range_error& e){
			break;
		}
		try {
                        D.insertBefore(left.moveNext());
                } catch (range_error& e) {

                }
	}
}

int main(int argc, char * argv[]){
   //ofstream out;
   // check command line for correct number of arguments
   if( argc != 2 ){
      cerr << "Usage: " << argv[0] << " <Shuffle number>" << endl;
      return(EXIT_FAILURE);
   }

   int number = stoi(argv[1]);

   //out.open(argv[3]);
   //if( !out.is_open() ){
     // cerr << "Unable to open file " << argv[3] << " for writing" << endl;
     // return(EXIT_FAILURE);
   //}
   cout << "deck size" << setw(15) << "shuffle count" << endl;
   cout << "------------------------------" << endl;
   for(int i  = 1; i <=number; i++){
   	List D;
	List dCopy;
	for(int x = 1; x <= i; x++){
		D.insertBefore(x);
		dCopy.insertBefore(x);
	}
	shuffle(D);
	int count = 1;
	while(!D.equals(dCopy)){
		shuffle(D);
		count++;
	}
	cout << i << setw(15) << count << endl;
   }
   //out.close();
   return(EXIT_SUCCESS);
}
