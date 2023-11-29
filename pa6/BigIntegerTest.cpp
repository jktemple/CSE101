//Josh Temple
//CruzID: jktemple
//PA6

#include "BigInteger.h"

using namespace std;
int main(void){
	string s = "-0041085449";
	BigInteger T = BigInteger(s);
	//std::cout << T.digits << std::endl;
	cout << T << endl;
	BigInteger R;
	cout << "R.sign() = " << R.sign() << endl;
	BigInteger Tcopy = T;
	cout << "T.compare(Tcopy)" << T.compare(Tcopy) << endl;
	BigInteger A = BigInteger("12345678910");
	BigInteger B = BigInteger("10987654321");
	BigInteger C = A + B;
	cout << "A = " << A << endl;
	cout << "B = " << B << endl;
	cout << "A == B: " << (A == B) << endl;
	cout << "A < B: " << (A < B) << endl;
	cout << "A > B: " << (A > B) << endl;
	cout << "A - A  = " << (A-A) << endl;
        cout << "B - A  = " << (B-A) << endl;
	cout << "C = " << C << endl;
	cout << "C should be " << 12345678910 + 10987654321 << endl;
	A += B;
	cout << "A += B: A = " << A << endl;
	cout << "A == C: " << (A == C) << endl;
       	A -= C;
	cout << "A -= C: A= " << A << endl; 
	BigInteger D = A * B; 
	cout << "D = A* D = " << D << endl;
       	BigInteger E = B * C;
	cout <<"E = B*C E= " << E << endl;
	B = BigInteger("-112122223333");
	A = BigInteger("-221211110000");
    	D = BigInteger("-333333333333");
    	C = A + B;
	cout << "C = "<< C << endl << "D = " << D << endl;
	A = BigInteger("111122223333");
    	B = BigInteger("111122223333");
    	C = BigInteger();
    	D = BigInteger("12348148518469129628889");
	C = A*B;
	cout << "C = "<< C << endl << "D = " << D << endl;
	BigInteger F = BigInteger("10000000000000000000000000000000000005");
	cout<< "F = " << F << endl;
	cout<< "S = " << "10000000000000000000000000000000000005" << endl;
	BigInteger Q = BigInteger("9063574346363325007361058");
	BigInteger P = BigInteger("+4597814412658653960738664");
	cout << "Q = " << Q << endl;
	cout << "P = " << P << endl;
	cout << (Q-P) << endl;

}
