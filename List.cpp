// /****************************************************************************************
// *  List.cpp
// *  Implementation file for List ADT
// *****************************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}


// // Class Constructors & Destructors -------------------------------------------

// // Creates a new List in the empty state.
List::List(){
    frontDummy = nullptr;
    backDummy = nullptr;
    beforeCursor = nullptr;
    afterCursor = nullptr;
    num_elements = 0;
    pos_cursor = 0;
}

// // Copy Constructor.
List::List(const List& L){
// make this an empty List
    frontDummy = nullptr;
    backDummy = nullptr;
    beforeCursor = nullptr;
    afterCursor = nullptr;
    num_elements = 0;
    pos_cursor = 0;

    // load elements of L into this List
    Node* N = L.frontDummy;
    while( N!=nullptr ){
        this->insertBefore(N->data);
        N = N->next;
    }
    // std::cout << "***called copy constructor: " << this->to_string() << std::endl;
}

// // Destructor
List::~List(){
    this->moveFront();
    while( num_elements>0 ){
        this->eraseAfter();
    }

    
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}
// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if (num_elements == 0){
        throw std::length_error("List: front(): empty list");
    }
    return frontDummy->data;
}
// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if (num_elements == 0){
        throw std::length_error("List: back(): empty list ");
    }
    return backDummy->data;
}
// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return pos_cursor;
}
// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if (pos_cursor >= num_elements){
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}
// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if (pos_cursor == 0){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    this->moveFront();
    while (num_elements > 0){
        this->eraseAfter();
    }

}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = nullptr;
    afterCursor = frontDummy;
}
// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    pos_cursor = num_elements;
    afterCursor = nullptr;
    beforeCursor= backDummy;
}
// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    if (pos_cursor >= num_elements){
        throw std::range_error("List: moveNext(): cursor at back");
    }
    
    if (afterCursor->next == nullptr){
        beforeCursor = afterCursor;
        afterCursor = nullptr;
    }
    else{
        afterCursor = afterCursor->next;
        beforeCursor = afterCursor->prev;
    }

    pos_cursor++;
    return beforeCursor->data;
}
// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if (pos_cursor == 0){
        throw std::range_error("List: movePrev(): cursor at front");
    }


    if (beforeCursor->prev == nullptr){
        afterCursor = beforeCursor;
        beforeCursor = nullptr;
    }
    else{
        beforeCursor = beforeCursor->prev;
        afterCursor = beforeCursor->next;
    }
    pos_cursor--;
    return afterCursor->data;
}
// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){

    if (num_elements == 0){
        frontDummy = backDummy = afterCursor = new Node(x);
        num_elements++;
        return;
    }

    Node* temp = afterCursor;
    afterCursor = new Node(x);
    afterCursor->next = temp;
    afterCursor->prev = beforeCursor;
    if (beforeCursor != nullptr){
        beforeCursor->next = afterCursor;
    }
    else{
        frontDummy = afterCursor;
    }
    if(temp != nullptr){
        temp->prev = afterCursor;
    }
    else{
        backDummy = afterCursor;
    }
    num_elements++;
    
}
// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){

    if (num_elements == 0){
        frontDummy = backDummy = beforeCursor = new Node(x);
        num_elements++;
        pos_cursor++;
        return;
    }

    Node* temp = beforeCursor;
    beforeCursor = new Node(x);
    beforeCursor->prev = temp;
    beforeCursor->next = afterCursor;
    if (afterCursor != nullptr){
        afterCursor->prev = beforeCursor;
    }
    else{
        backDummy = beforeCursor;
    }
    if(temp != nullptr){
        temp->next = beforeCursor;
    }
    else{
        frontDummy = beforeCursor;
    }
    num_elements++;
    pos_cursor++;

}
// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if( pos_cursor>=num_elements ){
      throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}
// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if( pos_cursor==0 ){
      throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;
}
// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    
    if( pos_cursor>=num_elements ){
      throw std::range_error("List: eraseAfter(): cursor at back");
   }
   
   Node* N = afterCursor;
   if( num_elements>1 ) {
    if (afterCursor->next == nullptr){
        afterCursor = nullptr;
        beforeCursor->next = nullptr;
        backDummy = beforeCursor;
      }
      else if (beforeCursor == nullptr){
        afterCursor = afterCursor->next;
        afterCursor->prev = nullptr;
        frontDummy = afterCursor;
      }
      else{ 
        afterCursor = afterCursor->next;
        afterCursor->prev = beforeCursor;
        beforeCursor->next = afterCursor;
      }
   }
   else{ 
      afterCursor = beforeCursor = frontDummy = backDummy =nullptr; 
   }
   num_elements--;
   delete N;
}
// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if( pos_cursor==0 ){
      throw std::range_error("List: eraseBefore(): cursor at front");
   }
   
   Node* N = beforeCursor;
   if( num_elements>1 ) { 
      if (beforeCursor->prev == nullptr){
        beforeCursor = nullptr;
        afterCursor->prev = nullptr;
        frontDummy = afterCursor;
      }
      else if (afterCursor == nullptr){
        beforeCursor = beforeCursor->prev;
        beforeCursor->next = nullptr;
        backDummy = beforeCursor;
      }
      else{
        beforeCursor = beforeCursor->prev;
        beforeCursor->next = afterCursor;
        afterCursor->prev = beforeCursor;
      }

   }else{ 
      afterCursor = beforeCursor = frontDummy = backDummy =nullptr;
   }
   num_elements--;
   pos_cursor--;
   delete N;
}
// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    Node* N = afterCursor;
    int steps = 0;
    while (N!=nullptr){
        if (N->data == x){
            steps++;
            pos_cursor += steps;
            beforeCursor = N;
            afterCursor = beforeCursor->next;
            return pos_cursor;
        }
        N = N->next;
        steps++;
    }
    pos_cursor = num_elements;
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    Node* N = beforeCursor;
    int steps = 0;
    while (N!=nullptr){
        if (N->data == x){
            steps++;
            pos_cursor -= steps;
            afterCursor = N;
            beforeCursor = afterCursor->prev;
            return pos_cursor;
        }
        N = N->prev;
        steps++;
    }
    pos_cursor = 0;
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    int steps = 1;
    int target;
    int end_pos = pos_cursor;
    while (steps < num_elements){
        this->moveFront();
        for(int i = 0; i < steps; i++){
            this->moveNext();
        }
        target = beforeCursor->data;
        while(this->findNext(target) != -1){
            if (pos_cursor <= end_pos){
                end_pos--;
            }
            this->eraseBefore();
        }
        steps++;  
    }
    this->moveFront();
    for (int i = 0; i < end_pos; i++){
        this->moveNext();
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List C;
    Node* N = this->frontDummy;
    while (N != nullptr){
        C.insertBefore(N->data);
        N = N->next;
    }
    N = L.frontDummy;
    while (N != nullptr){
        C.insertBefore(N->data);
        N = N->next;
    }

    C.pos_cursor = 0;
    C.afterCursor = C.frontDummy;
    C.beforeCursor = nullptr;
    return C;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    Node* N = nullptr;
    std::string s = "(";
    for(N=frontDummy; N!=nullptr; N=N->next){
        if(N->next == nullptr){
            s+= std::to_string(N->data);
            break;
        }
        s += std::to_string(N->data)+", ";
    }
    s += ")";
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = ( this->num_elements == R.num_elements);
    N = this->frontDummy;
    M = R.frontDummy;
    while (eq && N!=nullptr){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;

}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){

    if( this != &L ){ // not self assignment
      // make a copy of Q
      List temp = L;
      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return

}
