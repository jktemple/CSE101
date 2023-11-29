// Josh Temple
// CruzID: jktemple
// PA5

#include<stdexcept>
#include<iostream>
#include<string>
#include "List.h"

List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

List::List(){
	frontDummy = new Node(-50);
	backDummy = new Node(-50);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

List::List(const List& L){
	frontDummy = new Node(-50);
	backDummy = new Node(-50);
	frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
	Node *N = L.frontDummy->next;
	while(N != nullptr && N != L.backDummy){
		this->insertBefore(N->data);
		N = N->next;
	}
	moveFront();
}

List::~List(){
	Node *N = backDummy;
	while(N != nullptr){
		Node* temp = N;
		N = N->prev;
		delete(temp);
	}
}

int List::length() const{
	return(num_elements);
}

ListElement List::front() const{
	if( num_elements==0 ){
      throw std::length_error("List: front(): empty List");
   }
   return(frontDummy->next->data);
}

ListElement List::back() const{
	if( num_elements==0 ){
		throw std::length_error("List: back(): empty List");
   }
   return(backDummy->prev->data);
}

int List::position() const{
	return(pos_cursor);
}

ListElement List::peekNext() const{
	if(pos_cursor >= num_elements){
		throw std::range_error("List: peekNext(): cursor at back");
	}
	return(afterCursor->data);
}

ListElement List::peekPrev() const{
	if(pos_cursor <= 0){
		throw std::range_error("List: peekPrev(): cursor at front");
	}
	return(beforeCursor->data);
}

void List::clear(){
	moveFront();
	while(num_elements>0){
		//std::cout << "num_elements = " << num_elements << std::endl;
		eraseAfter();
	}
}

void List::moveFront(){
	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
}

void List::moveBack(){
	pos_cursor = num_elements;
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
}

ListElement List::moveNext(){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: moveNext(): cursor at back");
	}
	pos_cursor++;
	afterCursor = afterCursor->next;
	beforeCursor = beforeCursor->next;
	return (beforeCursor->data);
}

ListElement List::movePrev(){
	if(pos_cursor <= 0){
		throw std::range_error("List: movePrev(): cursor at front");
	}
	pos_cursor--;
	afterCursor = afterCursor->prev;
	beforeCursor = beforeCursor->prev;
	return (afterCursor->data);
}

   // insertAfter()
   // Inserts x after cursor.
void List::insertAfter(ListElement x){
	Node* N = new Node(x);
	N->next = afterCursor;
	N->prev = afterCursor->prev;
	beforeCursor->next = N;
	afterCursor->prev = N;
	afterCursor = N;
	num_elements++;
}

void List::insertBefore(ListElement x){
	Node* N = new Node(x);
	//cout << "node created" << endl;
	N->next = beforeCursor->next;
	//cout << "N->next = beforeCursor->next" << endl;
	N->prev = beforeCursor;
	//cout<< "N->prev = beforeCursor->prev" << endl;
	afterCursor->prev = N;
	//cout<< "beforeCursor->next->prev = N;" << endl;
	beforeCursor->next = N;
	beforeCursor = N;
	num_elements++;
	pos_cursor++;
}

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
void List::setAfter(ListElement x){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: setAfter(): cursor at back");
	}
	afterCursor->data = x;
}

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
void List::setBefore(ListElement x){
	if(pos_cursor <= 0){
		throw std::range_error("List: setBefore(): cursor at front");
	}
	beforeCursor->data = x;
}

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
void List::eraseAfter(){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: eraseAfter(): cursor at back");
	}
	Node* temp = afterCursor;
	//std::cout<< "temp = afterCursor" << std::endl;
	beforeCursor->next = afterCursor->next;
	//std::cout<< "beforeCursor->next = afterCursor->next;" << std::endl;
	//bool t = (afterCursor->next == backDummy);
	//std::cout <<"afterCursor->next == backDummy: "<< t << std::endl;
	afterCursor->next->prev = beforeCursor;
	//std::cout<< "afterCursor->next->prev = beforeCursor" << std::endl;
	afterCursor = afterCursor->next;
	//std::cout<< "afterCursor = afterCursor->next" << std::endl;
	num_elements--;
	delete(temp);
}

void List::eraseBefore(){
	if(pos_cursor <= 0){
		throw std::range_error("List: eraseBefore(): cursor at front");
	}
	Node * temp = beforeCursor;
	beforeCursor->prev->next = beforeCursor->next;
	beforeCursor->next->prev = beforeCursor->prev;
	beforeCursor = beforeCursor->prev;
	num_elements--;
	pos_cursor--;
	delete(temp);
}

int List::findNext(ListElement x){
	while(pos_cursor < num_elements){
		ListElement temp = moveNext();
		if(temp == x){	
			return (pos_cursor);
		}
	}
	return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
	while(pos_cursor >  0){
		ListElement temp = movePrev();
		if(temp == x){	
			return (pos_cursor);
		}
	}
	return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
	Node *N = frontDummy->next;
	while(N != nullptr){
		ListElement d = N->data;
		Node* I = N->next;
		while(I != nullptr){
			if(d == I->data){
				Node* temp = I;
				if(I == beforeCursor){
					beforeCursor = I->prev;
				} else if(I == afterCursor){
					afterCursor = I->next;
				}
				I->prev->next = I->next;
				I->next->prev = I->prev;
				I = I->next;
				delete(temp);
				num_elements--;
			} else {
				I = I->next;
			}
		}
		N = N->next;
	}
	int count = 0; 
	N = frontDummy;
	while(N != nullptr){
		if(N == beforeCursor){
			pos_cursor = count;
			return;
		}
		N = N->next;
		count++;
	}
	pos_cursor = num_elements;
}

List List::concat(const List& L) const{
	List R= List();
	Node* inL = frontDummy->next;
	while(inL != nullptr && inL != backDummy){
                R.insertBefore(inL->data);
                inL = inL->next;
        }
	inL = L.frontDummy->next;
	while(inL != nullptr && inL != L.backDummy){
		R.insertBefore(inL->data);
		inL = inL->next;
	}
	R.moveFront();
	return R;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
	if(num_elements == 0){
		return "";
	}
	Node* N = nullptr;
	std::string s = "(";
    	for(N=frontDummy->next; N!=backDummy; N=N->next){
		s += std::to_string(N->data);
		if(N->next != backDummy){
			s += ", ";
		}
    	}
	s += ")";
   	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
	if(num_elements != R.num_elements){
		return false;
	}
	Node *N = frontDummy->next;
	Node *M = R.frontDummy->next;
	while(M != nullptr && N != nullptr){
		if(N->data != M->data){
			return false;
		}
		N = N->next;
		M = M->next;
	}
	return true;
}

std::ostream& operator<<( std::ostream& stream, const List& L ){
	return stream << L.List::to_string();
}

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
	return A.List::equals(B);
}

   // operator=()
   // Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
	if(this != &L){ // not self assignment
      // make a copy of L
      List temp = List(L);
      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
	  std::swap(pos_cursor, temp.pos_cursor);
	  std::swap(beforeCursor, temp.beforeCursor);
	  std::swap(afterCursor, temp.afterCursor);
   }
   // return this with the new data installed
   return *this;
   // the copy, if there is one, is deleted upon return
}



