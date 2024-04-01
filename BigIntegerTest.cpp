//-----------------------------------------------------------------------------
// BigIntegerClient.cpp 
// A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"
#include<cassert>

using namespace std;

void TestFunctions(){
   
   string s1 = "91287346670000043892345634563400005619187236478";
   string s2 = "-330293847502398475";
   string s3 = "9876545439000000345634560000000002000034565430000000006543654365346534";
   string s4 = "9876545439000000000000000100000000000006543654365346534";
   string s5 = "98765454390000034563456191872363456345619187236000456456345756780000065436543";
   string s6 = "9876545439000000000000000000000000000006543";
   BigInteger B,A,C,R;

   cout<< endl <<"Access functions --------------------------------------------------------" << endl << endl;

   //test sign()
   B = BigInteger(s2);
   assert(B.sign()==-1);
   B = BigInteger("0");
   assert(B.sign()==0);
   B = BigInteger(s1);
   assert(B.sign()==1);
   cout << "sign() works!\n";

   //test compare()
   B = BigInteger("10000000000000000000");
   A = BigInteger("20000000000000000000");
   C = BigInteger("30000000000000000000");
   R = A.add(B);
   assert(R == C);
   cout << "compare() works!\n";
   
   cout<< endl <<"Manipulation procedures -------------------------------------------------" << endl << endl;


   //test makeZero()
   B = BigInteger(s1);
   assert(B.sign() != 0);
   B.makeZero();
   assert(B.sign()==0);
   cout << "makeZero() works!\n";

   //test negate()
   B = BigInteger(s1);
   assert(B.sign() == 1);
   B.negate();
   assert(B.sign() == -1);
   cout << "negate() works!\n";

   cout<< endl << "BigInteger Arithmetic operations ----------------------------------------" << endl << endl;

   //test add()
   B = BigInteger("10000000000000000000");
   A = BigInteger("20000000000000000000");
   C = BigInteger("30000000000000000000");
   R = A.add(B);
   assert(R == C);
   cout << "add() works!\n";
   //test sub()
   C = BigInteger("10000000000000000000");
   B = BigInteger("20000000000000000000");
   A = BigInteger("30000000000000000000");
   R = A.sub(B);
   assert(R == C);
   cout << "sub() works!\n";
   //test mult()
   B = BigInteger("1000000");
   A = BigInteger("2000000");
   C = BigInteger("2000000000000");
   R = A.mult(B);
   assert(R == C);
   cout << "mult() works!\n";

   cout<< endl <<"Overriden Operators -----------------------------------------------------" << endl << endl;

   //test operator==()
   B = BigInteger("10000000000000000000");
   A = BigInteger("20000000000000000000");
   C = BigInteger("30000000000000000000");
   R = A.add(B);
   assert(R == C);
   cout << "operator==() works!\n";

   //test operator<()
   B = BigInteger("10000000000000000000");
   C = BigInteger("30000000000000000000");
   R = B.add(B);
   assert(R < C);
   cout << "operator<() works!\n";

   //test operator<=()
   B = BigInteger("10000000000000000000");
   C = BigInteger("30000000000000000000");
   R = B.add(B);
   assert(R <= C);
   B = BigInteger("10000000000000000000");
   A = BigInteger("20000000000000000000");
   C = BigInteger("30000000000000000000");
   R = A.add(B);
   assert(R <= C);
   cout << "operator<=() works!\n";

   //test operator>()
   B = BigInteger("10000000000000000000");
   C = BigInteger("30000000000000000000");
   R = B.add(B);
   assert(C > R);
   cout << "operator<() works!\n";

   //test operator>=()
   B = BigInteger("10000000000000000000");
   C = BigInteger("30000000000000000000");
   R = B.add(B);
   assert(C >= R);
   B = BigInteger("10000000000000000000");
   A = BigInteger("20000000000000000000");
   C = BigInteger("30000000000000000000");
   R = A.add(B);
   assert(C >= R);
   cout << "operator<=() works!\n";

   //test operator+()
   B = BigInteger("10000000000000000000");
   A = BigInteger("20000000000000000000");
   C = BigInteger("30000000000000000000");
   R = A + B;
   assert(R == C);
   cout << "operator+() works!\n";

   //test operator+=()
   B = BigInteger("10000000000000000000");
   A = BigInteger("20000000000000000000");
   C = BigInteger("30000000000000000000");
   B += A;
   assert(B == C);
   cout << "operator+() works!\n";

   //test operator-()
   C = BigInteger("10000000000000000000");
   B = BigInteger("20000000000000000000");
   A = BigInteger("30000000000000000000");
   R = A - B;
   assert(R == C);
   cout << "operator-() works!\n";

   //test operator-=()
   C = BigInteger("10000000000000000000");
   B = BigInteger("20000000000000000000");
   A = BigInteger("30000000000000000000");
   A -= B;
   assert(A == C);
   cout << "operator-() works!\n";

   //test operator*()
   B = BigInteger("1000000");
   A = BigInteger("2000000");
   C = BigInteger("2000000000000");
   R = A * B;
   assert(R == C);
   cout << "operator*() works!\n";

   //test operator*=()
   B = BigInteger("1000000");
   A = BigInteger("2000000");
   C = BigInteger("2000000000000");
   B *= A;
   assert(B == C);
   cout << "operator*() works!\n";

   cout << endl;
}

int main(int argc, char* argv[]){

   TestFunctions();

   cout << "All Functions are working!\n";
}
