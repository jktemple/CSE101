//Josh Temple
//CruzID: Jktemple
//PA8
#include "Dictionary.h"
#include <string>

using namespace std;
int main(void){
	Dictionary A;
	Dictionary B;
	cout << "A==B " << (A==B?"true":"false") << endl;
	string stringArray[] = {"agent", "enter", "chaos", "plain", "whole", "delay", "cower", "brown", "vague", "black"};
	for(int i = 0; i < 10; i++){
		A.setValue(stringArray[i], i);
	}
	cout << "test" << endl;
	cout << A << endl;
	cout<< "A.contains brown " << (A.contains("brown")?"true":"false") << endl;
	cout << "A==B " << (A==B?"true":"false") << endl;
	cout << "clearing A" << endl;
	A.clear();
	cout << "A == B after clear " << (A==B?"true":"false")<< endl;
	for(int i = 0; i < 10; i++){
                A.setValue(stringArray[i], i);
        }
	B = A;
	cout << "A==B after Copying A" << (A==B?"true":"false") << endl;
	cout << "A.hasCurrent() " << A.hasCurrent() << endl;
	cout << "A.setValue(vague, 70)  " << endl;
	A.setValue("vague", 70);
	cout << A << endl;
	cout << "A.remove(cower) " << endl;
	A.remove("cower");
	cout << A << endl;
	cout << "traversing A" << endl;
	for(A.begin(); A.hasCurrent(); A.next()){
      		string s = A.currentKey();
      		int x = A.currentVal();
      		cout << "("+s+", " << x << ") ";
   	}
}
