//Josh Temple
//CruzID: jktemple
//PA6

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int testFunction(List* ap, List* bp){
	List A = *ap;
  	List B = *bp;
 	A.insertAfter(60);
    	A.insertAfter(50);
    	A.insertAfter(40);
    	A.insertBefore(10);
    	A.insertBefore(20);
    	A.insertBefore(30);
    if (A.peekPrev() != 30){
      cout<<"A.peekPrev() == "<< A.peekPrev() << endl;
	    return 1;
    }

    A.eraseBefore();
    if (A.peekPrev() != 20)
      return 2;

    A.moveBack();
    if (A.peekPrev() != 60)
      return 3;
    return 0;
}


int main(){
	List A;
	List B;
	cout << "lists created" << endl;
	cout << "A = " << A << " A.length() = " << A.length() << endl;
        cout << "B = " << B << endl;
        cout << endl;
	cout << testFunction(&A, &B) << endl;
	A.clear();
	B.clear();
	for(int i = 0; i<=10; i++){
		cout << "inserting " << i << endl;
		A.insertBefore(i);
		A.insertBefore(i);
		B.insertBefore(i);
		B.insertBefore(i);
	}
	cout << "inserted values" << endl;
	cout << "A = " << A << endl;
   	cout << "B = " << B << endl;
   	bool t = (A == B);
	cout << "A == B: " << t << endl;
	cout << "A pos = " << A.position() << endl;
	A.cleanup();
	cout << "A = " << A << endl;
	cout << "A pos = " << A.position() << endl;
	t = (A == B);
        cout << "A == B: " << t << endl;
	B.moveFront();
	cout << "B.findNext(4) = " << B.findNext(4) << endl;
	List C = A.concat(B);
	cout << "A.concat(B) = " << C << endl;
	A.clear();
	cout << "cleared A = " << A << endl;
	return(0);
}
