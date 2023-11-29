//Josh Temple
//CruzID: jktemple
//PA6

#include<stdexcept>
#include "BigInteger.h"

#define BASE 1000000000
#define POWER 9

BigInteger::BigInteger(){
	signum = 0;
	digits = List();
}

BigInteger::BigInteger(std::string s){
	if(s.empty()){
		throw std::invalid_argument("BigInteger: Constructor: empty string\n");
	} else if(s.find_first_not_of("+-1234567890") != std::string::npos) {
		throw std::invalid_argument("BigInteger: Constructor: non-numeric string\n");
	}
	digits = List();
	if(s.length() == 1 && s.at(0) == '0'){
		return;
	}
	if(s.at(0) == '+'){
		signum = 1;
		s.erase(0,1);
	} else if(s.at(0) == '-'){
		signum = -1;
		s.erase(0,1);
	} else {
		signum = 1;
	}
	while(s.at(0) == '0'){
		s.erase(0,1);
	}
	//std::cout<< s << std::endl;
	int i = s.length();
	while(i > POWER){
		//std::cout<< s.substr(i-POWER, POWER) << std::endl;
		digits.insertAfter(std::stol(s.substr(i-POWER, POWER), nullptr, 10));
		i = i - POWER;
	}
	//std::cout<< s.substr(0,i) << " Done printing constructor stuff" << std::endl;
	digits.insertAfter(std::stol(s.substr(0,i), nullptr, 10));
}

BigInteger::BigInteger(const BigInteger& N){
	signum = N.sign();
	digits = N.digits; 
}


int BigInteger::sign() const { 
	return signum;
}
void BigInteger::negate(){
	signum *= -1;
}

int BigInteger::compare(const BigInteger& N) const{
	if(signum < N.sign()){
		return -1;
	} else if(signum > N.sign()){
		return 1;
	} else if(signum == 0 && N.sign() == 0){
		return 0;
	}
	BigInteger T = N;
	BigInteger thisTemp = *this;
	if(digits.length() > N.digits.length()){
		return 1;
	} else if(digits.length() < N.digits.length()){
		return -1;
	} else {
		if(digits == N.digits){
			return 0;
		}
		
		thisTemp.digits.moveFront();
		T.digits.moveFront();
		while(1){
			ListElement d;
			ListElement n;
			try {
				d = thisTemp.digits.moveNext();
				n = T.digits.moveNext();
			} catch(std::range_error& e){
				break;
			}
			if(d > n) {
				return 1;
			} else if ( d < n) {
				return -1;
			}
		}
		return 0;
	}
}

void BigInteger::makeZero(){
	signum = 0;
	digits.clear();
}

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
	L.moveFront();
	while(L.position()<L.length()){
		ListElement l = L.moveNext();
		L.setBefore(-l);
	}
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
List sumList(List A, List B, int sgn){
	if(sgn < 0){
		negateList(B);
	}
	List S = List();
	A.moveBack();
	B.moveBack();
	while(A.position() > 0 && B.position() > 0){
		ListElement a = A.movePrev();
		ListElement b  = B.movePrev();
		//std::cout<< "a = " << a << std::endl << "b = " << b << std::endl;
		S.insertAfter(a+b);
	}
	
	while(A.position() > 0){
		S.insertAfter(A.movePrev());
	}
	
	while(B.position() > 0){
		S.insertAfter(B.movePrev());
	}
	
	S.moveFront();
	while(S.length() > 0){
		if(S.front() == 0)
			S.eraseAfter();
		else
			break;
	}
	return S;
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
 	L.moveBack();
	if(L.position() == 0){
                return 0;
        }
	ListElement carryVal = 0;
	while(L.position() > 0){
		ListElement l = L.movePrev();
		l += carryVal;
		carryVal = l/BASE;
		l = l%BASE;
		//if(l < 0){l*= -1;}
		L.setAfter(l);
	}
	int returnVal = 0;
	if(carryVal < 0){ 
		L.insertAfter(-carryVal);
		returnVal = -1;
	} else if(carryVal > 0){
		L.insertAfter(carryVal);
		returnVal =  -1;
	}
	if(L.front() < 0) { 
		returnVal = -1;
	} else {
		returnVal = 1;
	}
	L.moveFront();
	while(L.position() < L.length()){
		ListElement n = L.moveNext();
		if(n<0){
			L.setBefore(-n);
		}
	}
	return returnVal;	
}
// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
	L.moveBack();
	for(int i = 0; i < p; i++){
		L.insertBefore(0);
	}
}
// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
List scalarMultList(List& L, ListElement m){
	List R = List();
	L.moveBack();
	while(L.position() > 0){
		ListElement l = L.movePrev();
		R.insertAfter(l*m); 
	}
	return R;
}

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
	BigInteger TempThis = *this;
	BigInteger tempN = N;
	BigInteger R = BigInteger();
	if(TempThis.sign()<0){
		negateList(TempThis.digits);
	}
	if(tempN.sign() < 0) {
		negateList(tempN.digits);
	}	
	R.digits = sumList(TempThis.digits, tempN.digits, 1);
	R.signum = normalizeList(R.digits);
	return R;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
	BigInteger R = BigInteger();
	BigInteger TempThis = *this;
        BigInteger tempN = N;
	if(TempThis.sign()<0){
                negateList(TempThis.digits);
        }
        if(tempN.sign() < 0) {
                negateList(tempN.digits);
        }
	R.digits = sumList(TempThis.digits, tempN.digits, -1);
	//std::cout<< "R before normalizing: " << R.digits << std::endl; 
	R.signum = normalizeList(R.digits);
	return R;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
	BigInteger R = BigInteger();
	if(this->sign() == 0 || N.sign() == 0)
		return R;
	BigInteger Temp = N;
	BigInteger ThisTemp = *this;
	Temp.digits.moveBack();
	int i = 0;
	while(Temp.digits.position() > 0){
		ListElement s = Temp.digits.movePrev();
		//std::cout << "multipling " << ThisTemp << " by " << s << std::endl;
		List T = scalarMultList(ThisTemp.digits, s);
		//std::cout << "result : " << T << std::endl;
		normalizeList(T);
		//std::cout << "T normalized: " << T << std::endl;
		shiftList(T, i);
		R.digits = sumList(R.digits, T, 1);
		normalizeList(R.digits);
		i++;
	}
	if(this->sign() < 0 && N.sign() < 0)
		R.signum = 1;
	else if(this->sign() < 0 || N.sign() < 0)
		R.signum = -1;
	else
		R.signum = 1;
	normalizeList(R.digits);
	return R;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.

std::string BigInteger::to_string() {
	if(signum == 0){
		return "0";
	}
	std::string s = "";
	if(signum < 0){
		s = "-";
	}
	digits.moveFront();
	while(digits.position() < digits.length()){
		ListElement t = digits.moveNext();
		std::string temp = std::to_string(t);
		std::string z = "";
		if(temp.length() < POWER && digits.position() > 1){
			for(size_t i = 0; i < (POWER-temp.length()); i++){
				z += "0";
			}
			temp = z + temp;
		}
		s += temp;
	}
	return s;
}

std::ostream& operator<< (std::ostream& stream, BigInteger N){
	return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator== ( const BigInteger& A, const BigInteger& B ){
	return (A.compare(B) == 0);
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator< ( const BigInteger& A, const BigInteger& B ){
	return (A.compare(B) < 0);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<= ( const BigInteger& A, const BigInteger& B ){
	return (A.compare(B) <= 0);
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator> ( const BigInteger& A, const BigInteger& B ){
	return (A.compare(B) > 0);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>= ( const BigInteger& A, const BigInteger& B ){
	return (A.compare(B) >= 0);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
	return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+= (BigInteger& A, const BigInteger& B ){
	A = A.add(B);
	return A;
}


// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
	return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=(BigInteger& A, const BigInteger& B ){
	A = A.sub(B);
	return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
	return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=(BigInteger& A, const BigInteger& B ){
	A = A.mult(B);
	return A;
}
