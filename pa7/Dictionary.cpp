//Josh Temple
//CruzID: Jktemple
//PA7

#include "Dictionary.h"
#include <string>

#define NIL -50

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
	if(R != this->nil && R!=nullptr){
		this->inOrderString(s, R->left);
		s += R->key + " : " + std::to_string(R->val) + "\n";
		this->inOrderString(s,R->right);
	}
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
	if(R != this->nil && R!=nullptr){
		s += R->key + "\n";
		this->preOrderString(s,R->left);
		this->preOrderString(s,R->right);
	}
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
	if(R != N || R ==nullptr){	
		setValue(R->key, R->val);
		preOrderCopy(R->left, N);
		preOrderCopy(R->right, N);
	}
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
	Node* T = R;
	if(T == nil)
		return;
	postOrderDelete(T->left);
	postOrderDelete(T->right);
	delete(T);
	R = nil;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
	if(R == nil || R == nullptr)
		return this->nil;
	if(R->key == k)
		return R;
	else if(k < R->key)
		return search(R->left, k);
	else
		return search(R->right, k);
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
	if(R == nil)
		return nil;
	Node* T = R;
	while(T->left != nil){
		T = T->left;
	}
	return T;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
	if(R == nil)
		return nil;
	Node* T = R;
	while(T->right != nil){
		T = T->right;
	}
	return T;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
	if(N->right != nil){
	//	std::cout
		return findMin(N->right);
	}
	Node *y = N->parent;
	Node *t = N;
	while( y != nil && t == y->right){
		t = y;
		y = y->parent;
	}
	//std::cout << "y key: " << y->key << std::endl;
	return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
	if(N->left != nil)
		return findMax(N->left);
	Node *y = N->parent;
	Node *t = N;
	while( y != nil && t == y->left){
		t = y;
		y = y->parent;
	}
	return y;
}

// Class Constructors & Destructors ----------------------------------------
 
Dictionary::Node::Node(keyType k, valType v){
	key = k;
	val = v;
	parent = nullptr;
    	left = nullptr;
    	right = nullptr;
}
// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
	num_pairs = 0;
	nil = new Node("NIL",NIL);
	root = nil;
	current = nil;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
	num_pairs = 0;
        nil = new Node("NIL",NIL);
        root = nil;
        current = nil;
	this->preOrderCopy(D.root, D.nil);
	current = nil;
	num_pairs = D.num_pairs;
}

// Destructor
Dictionary::~Dictionary(){
	postOrderDelete(root);
	delete(nil);
	current = nullptr;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
	return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
	Node* T = search(root, k);
	return T != nil;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const { 
	Node * T = search(root, k);
	if(T==nil)
		throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist\n");
	return T->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
	return current != nil;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
	if(!hasCurrent())
		throw std::logic_error("Dictionary: currentKey(): current undefined\n");
	return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
	if(!hasCurrent())
		throw std::logic_error("Dictionary: currentVal(): current undefined\n");
	return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
	postOrderDelete(root);
	num_pairs = 0;
	root = nil;
	current = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
	Node * T = root;
	Node* Y = nil;
	while(T != nil){
		Y = T;
		if(k == T->key) {
			T->val = v;
			return;
		} else if (k < T->key) {
			T = T->left;
		} else {
			T = T->right;
		}
	}
	Node* Z = new Node(k,v);
	Z->parent = Y;
	Z->left = nil;
	Z->right = nil;
	if(Y==nil)
		root = Z;
	else if(k < Y->key){
		Y->left = Z;
	} else {
		Y->right = Z;
	}
	num_pairs++;
}

void Dictionary::transplant(Node* u, Node* v){
	if (u->parent == nil){
      		root = v;
	}
	else if (u == u->parent->left){
      		u->parent->left = v;
	}
	else {
      		u->parent->right = v;
	}
	if (v != nil){
      		v->parent = u->parent;
	}
}
// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
	Node* T = search(root, k);
	if(T==nil){
		throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist\n"); 
	}
	if (T->left == nil){               // case 1  or case 2.1 (right only)
		transplant(T, T->right);
	}
	else if (T->right == nil){         // case 2.2 (left only)
      		transplant(T, T->left);
	}
	else {                        // case 3
      		Node* y = findMin(T->right);
      		if (y->parent != T){
         		transplant(y, y->right);
         		y->right = T->right;
         		y->right->parent = y;
	  	}
      		transplant(T, y);
      		y->left = T->left;
      		y->left->parent = y;
   	}
	if(current == T) {
		current = nil;
	}	
   	delete(T);
	num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
	if(num_pairs == 0)
		return;
	current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
	if(num_pairs == 0)
		return;
	current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
	if(!hasCurrent())
		throw std::logic_error("Dictionary: next(): current undefined\n");
	//std::cout<<"going next from " << current->key << std::endl;
	current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
	if(!hasCurrent())
		throw std::logic_error("Dictionary: prev(): current undefined\n");
	current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
	std::string s = "";
	inOrderString(s,root);
	return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
	std::string s = "";
	preOrderString(s,root);
	return s;
}
	
// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
	std::string thisPre, thisOrder, thatPre, thatOrder;
	thisPre = this->pre_string();
	thisOrder = this->to_string();
	thatPre = D.pre_string();
	thatOrder = D.to_string();
	return (thisPre == thatPre) && (thisOrder == thatOrder);

}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
	return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
	return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
	if(this != &D){
		Dictionary temp = Dictionary(D);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);
		std::swap(nil, temp.nil);
	}
	return *this;
}
