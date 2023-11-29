//Josh Temple
//CruzID: jktemple
//PA6

#include <iomanip>
#include <fstream>
#include "BigInteger.h"

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
   string S = "";
   string Z = "";
   getline(in, S);
   BigInteger A = BigInteger(S);
   getline(in, S);
   getline(in, Z);
   BigInteger B = BigInteger(Z);
   out << A << endl << endl;
   out << B << endl << endl;
   out << (A + B) << endl << endl;
   out << (A-B)<< endl << endl;
   out << (A-A) << endl << endl; 
   BigInteger C; //3A - 2B
   BigInteger D; 
   for(int i = 0; i < 3; i++){C += A;}
   for(int i = 0; i < 2; i++){D += B;}
   out << (C-D) << endl << endl;
   //AB
   out << (A*B) << endl << endl;
   //A^2
   out << (A*A) << endl << endl;
   //B^2
   out << (B*B) << endl << endl;
   //9A^4 + 16B^5
   C = A;
   for(int i = 0; i < 3; i++){C=(C*A);}
   BigInteger Temp = C;
   for(int i = 0; i < 8; i++){C+=Temp;}
   D = B;
   for(int i = 0; i < 4; i++){D=(D*B);}
   Temp = D;
   for(int i = 0; i < 15; i++){D=(D + Temp);} 
   out << (C+D) << endl;
   out.close();
   in.close();
   return(EXIT_SUCCESS);
}

