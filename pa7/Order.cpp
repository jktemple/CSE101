//Josh Temple
//CruzID: Jktemple
//PA7

#include <iomanip>
#include <fstream>
#include "Dictionary.h"
using namespace std;
int main(int argc, char * argv[]){
   //ofstream out;
   // check command line for correct number of arguments
   ifstream in;
   ofstream out;
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }
   in.open(argv[1]);
   if( !in.is_open() ){
     cerr << "Unable to open file " << argv[1] << " for reading" << endl;
     return(EXIT_FAILURE);
   }
   out.open(argv[2]);
   if( !out.is_open() ){
     cerr << "Unable to open file " << argv[2] << " for writing" << endl;
     return(EXIT_FAILURE);
   }
   string line;
   int i = 1;
   Dictionary A;
   while(getline(in, line)){
	   A.setValue(line, i);
	   i++;
   }
   out << A << endl << A.pre_string();
   out.close();
   in.close();
   return(EXIT_SUCCESS);
}

