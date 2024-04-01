// /****************************************************************************************
// *  ListTest.cpp
// *  A test client for List ADT
// *****************************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include<cassert>
#include"List.h"

using namespace std;

void TestFunctions(){
   //test length()
   List L,T,M,C;
   assert(L.length()==0);
   L.insertAfter(1);
   assert(L.length() == 1);
   L.clear();
   cout << "length() works!\n";

   //test front()
   L.insertAfter(1);
   assert(L.front()==1);
   L.insertBefore(5);
   assert(L.front() == 5);
   L.clear();
   cout << "front() works!\n";

   //test back()
   L.insertBefore(1);
   assert(L.back()==1);
   L.insertAfter(5);
   assert(L.back()==5);
   L.clear();
   cout << "back() works!\n";

   //test position
   L.insertBefore(1);
   L.insertBefore(1);
   L.insertBefore(1);
   L.insertBefore(1);
   assert(L.position() == 4);
   L.clear();
   cout << "position() works!\n"; 

   //test peekNext()
   L.insertAfter(1);
   L.insertAfter(2);
   L.insertAfter(3);
   assert(L.peekNext() == 3);
   L.moveNext();
   assert(L.peekNext() == 2);
   L.clear();
   cout << "peekNext() works!\n";

   //test peekPrev()
   L.insertBefore(1);
   L.insertBefore(2);
   L.insertBefore(3);
   assert(L.peekPrev() == 3);
   L.movePrev();
   assert(L.peekPrev() == 2);
   L.clear();
   cout << "peekPrev() works! \n";

   //test clear()
   assert(L.length()==0);
   L.insertBefore(1);
   L.insertBefore(2);
   L.insertBefore(3);
   assert(L.length()==3);
   L.clear();
   assert(L.length()==0);
   cout << "clear() works!\n";

   //test moveFront()
   assert(L.position() == 0);
   L.insertBefore(1);
   L.insertBefore(2);
   L.insertBefore(3);
   assert(L.position()==3);
   L.moveFront();
   assert(L.position()==0);
   L.clear();
   cout << "moveFront() works!\n";

   //test moveBack()
   assert(L.position() == 0);
   L.insertAfter(1);
   L.insertAfter(2);
   L.insertAfter(3);
   assert(L.position()==0);
   L.moveBack();
   assert(L.position()==3);
   L.clear();
   cout << "moveBack() works!\n";

   //test moveNext()
   assert(L.position() == 0);
   L.insertAfter(1);
   L.insertAfter(2);
   L.insertAfter(3);
   assert(L.position()==0);
   L.moveNext();
   assert(L.position()==1);
   L.clear();
   cout << "moveNext() works!\n";

   //test movePrev()
   assert(L.position() == 0);
   L.insertBefore(1);
   L.insertBefore(2);
   L.insertBefore(3);
   assert(L.position()==3);
   L.movePrev();
   assert(L.position()==2);
   L.clear();
   cout << "movePrev() works!\n";

   //test insertBefore()
   L.insertBefore(1);
   assert(L.front()==1);
   L.moveFront();
   L.insertBefore(2);
   assert(L.front()==2);
   L.clear();
   cout << "insertBefore() works!\n";

   //test insertAfter()
   L.insertAfter(1);
   assert(L.back()==1);
   L.moveBack();
   L.insertAfter(2);
   assert(L.back()==2);
   L.clear();
   cout << "insertAfter() works!\n";

   //test setAfter() and setBefore()
   L.insertAfter(1);
   L.insertBefore(2);
   assert(L.front()==2);
   assert(L.back()==1);
   L.setAfter(2);
   L.setBefore(1);
   assert(L.front()==1);
   assert(L.back()==2);
   L.clear();
   cout << "setAfter() and setBefore() works!\n";

   //test eraseAfter() and eraseBefore()
   L.insertAfter(1);
   L.insertBefore(2);
   assert(L.length()==2);
   L.eraseAfter();
   L.eraseBefore();
   assert(L.length()==0);
   L.clear();
   cout << "eraseAfter() and eraseBefore() works!\n";
   
   //test findNext()
   L.insertAfter(1);
   L.insertAfter(2);
   L.insertAfter(3);
   assert(L.findNext(1) == 3);
   L.clear();
   cout << "findNext() works!\n";

   //test findPrev()
   L.insertBefore(1);
   L.insertBefore(2);
   L.insertBefore(3);
   assert(L.findPrev(1) == 0);
   L.clear();
   cout << "findPrev() works!\n";

   //test cleanup()
   L.insertBefore(1);
   L.insertBefore(2);
   L.insertBefore(3);
   L.insertBefore(1);
   L.insertBefore(2);
   L.insertBefore(3);
   L.insertBefore(1);
   L.insertBefore(2);
   L.insertBefore(3);
   assert(L.length() == 9);
   assert(L.position() ==9);
   L.cleanup();
   assert(L.length() == 3);
   assert(L.position() == 3);
   L.clear();
   cout << "cleanup() works \n";

   // test equals()
   L.insertBefore(1);
   L.insertBefore(2);
   L.insertBefore(3);
   T.insertAfter(3);
   T.insertAfter(2);
   T.insertAfter(1);
   assert(L.equals(T));
   L.clear();
   T.clear();
   cout << "equals() works!\n";

   //test concat()
   L.insertBefore(1);
   M.insertBefore(2);
   C = L.concat(M);
   T.insertAfter(2);
   T.insertAfter(1);
   assert(T.equals(C));
   T.clear();
   M.clear();
   L.clear();
   C.clear();
   cout << "concat() works!\n";

}

int main(int argc, char* argv[]){

   TestFunctions();

   cout << "All Functions are working!\n";
}
