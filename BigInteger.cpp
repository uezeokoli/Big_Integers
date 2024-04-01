// /****************************************************************************************
// *  BigInteger.cpp
// *  Implementation file for List ADT
// *****************************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"
#include"List.h"
#include<ctype.h>

#define base 1000000000
#define power 9

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    //creates BigInteger in empty state
    List empty;
    signum = 0;
    digits = empty;
}

// BigInteger()
   // Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    //creates BigInteger in empty state
    List empty;
    signum = 0;
    digits = empty;

    std::string str_x = std::to_string(x);
    *this = BigInteger(str_x);

}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    if (s.length() == 0){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    
    //creates BigInteger in empty state
    List empty;
    digits = empty;
    bool zero = true;       // checks that number is equal to zero 
    bool pos = true;        // checks that number is positive or not
    long element;
    int i = s.length()-1;       // used to travese string backwards
    int num_digits = 1;         // used to keep track of # of digits
    std::string str_element = "";
    
    while(true){
        if (!isdigit(s[i])){
            if ( s[i] != '-' && s[i] != '+' ){
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }
            if (i != 0){
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }
        }
        // Condition when first number in string reached
        if(i == 0){
            if (s[i] == '-'){

                pos = false;
                //nothing to add
                if (digits.length()==0){
                    throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
                }
                if (str_element.length() == 0){
                    break;
                }
                element = stol(str_element);
                if (element != 0){
                    zero = false;
                }
                digits.insertAfter(element);
                break;
            }
            else if(s[i] == '+'){
                if (digits.length()==0){
                    throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
                }
                if (str_element.length() == 0){
                    break;
                }
                element = stol(str_element);
                if (element != 0){
                    zero = false;
                }
                digits.insertAfter(element);
                break;
            }
            else{
                str_element = s[i] + str_element;
                if (str_element.length() == 0){
                    break;
                }
                element = stol(str_element);
                if (element != 0){
                    zero = false;
                }
                digits.insertAfter(element);
                break;
            }
        }

        else{
            str_element = s[i] + str_element;
        }


        if (num_digits == power){
            num_digits = 0;
            element = stol(str_element);
            if (element != 0){
                zero = false;
            }
            digits.insertAfter(element);
            str_element = "";
        }
        num_digits++;
        i--;
    }

    if (zero){
        signum = 0;
        return;
    }
    else if (pos){
        signum = 1;
    }
    else{
        signum = -1;
    }
    
    //gets rid of unneccessary zeros at the beginning
    digits.moveFront();
    while (true){
        if (digits.peekNext() != 0){
            break;
        }
        else{
            digits.eraseAfter();
        }
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    digits = N.digits;
    signum = N.signum;
}

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    List this_temp = digits;
    List N_temp = N.digits;
    if (digits.length() < N.digits.length()){
        return -1;
    }
    else if (digits.length() > N.digits.length()){
        return 1;
    }
    else if(signum < N.signum){
        return -1;
    }
    else if(signum > N.signum){
        return 1;
    }
    else{
        this_temp.moveFront();
        N_temp.moveFront();
        for(int i = 0; i<digits.length(); i++){
            if(this_temp.peekNext() < N_temp.peekNext()){
                return -1;
            }
            else if(this_temp.peekNext() > N_temp.peekNext()){
                return 1;
            }
            this_temp.moveNext();
            N_temp.moveNext();
        }
        return 0;
    }
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    List empty;
    signum = 0;
    digits = empty;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if (signum == 0){
        return;
    }
    else{
        signum *= -1;
    }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger result;
    BigInteger this_copy;
    BigInteger N_copy;
    this_copy.digits = this->digits;
    this_copy.signum = this->signum;
    N_copy.digits = N.digits;
    N_copy.signum = N.signum;
    result.signum = this->signum;
    List this_temp = digits;
    List N_temp = N.digits;
    int carry = 0;      

    // (-B) + A == A - B
    if (this->signum == -1 && N.signum == 1){
        this_copy.signum = 1;
        return N_copy.sub(this_copy);
    }
    // B + (-A) == B - A
    if (this->signum == 1 && N.signum == -1){
        N_copy.signum = 1;
        return this_copy.sub(N_copy);
    }
    // 0 + (A) == A
    if (this->signum == 0 && N.signum == 1){
        result.signum = 1;
        result.digits = N.digits;
        return result;
    }
    // 0 + (-A) == -A
    if (this->signum == 0 && N.signum == -1){
        result.signum = -1;
        result.digits = N.digits;
        return result;
    }
    // (B) + 0 == B
    if (this->signum == 1 && N.signum == 0){
        result.signum = 1;
        result.digits = this->digits;
        return result;
    }
    // (-B) + 0 == -B
    if (this->signum == -1 && N.signum == 0){
        result.signum = -1;
        result.digits = this->digits;
        return result;
    }
    // 0 + 0 = 0
    if (this->signum == 0 && N.signum == 0){
        result.signum = 0;
        return result;
    }
    this_temp.moveBack();
    N_temp.moveBack();
    if ((this_temp.length() < N_temp.length()) || (this_temp.length() == N_temp.length())){
        for (int i = 0; i<this_temp.length();i++){
            if ((this_temp.peekPrev() + N_temp.peekPrev() + carry) >= base){
                result.digits.insertAfter(this_temp.peekPrev() + N_temp.peekPrev() - base + carry);     
                carry = 1;
            }
            else{
                result.digits.insertAfter(this_temp.peekPrev() + N_temp.peekPrev() + carry);
                carry = 0;  
            }
            this_temp.movePrev();
            N_temp.movePrev();

        }
        while (N_temp.position() != 0){
            if((N_temp.peekPrev() + carry) >= base){
                result.digits.insertAfter(N_temp.peekPrev() - base + carry);     
                carry = 1;
            }
            else{
                result.digits.insertAfter(N_temp.peekPrev() + carry);
                carry = 0; 
            }
            N_temp.movePrev();
        }
        if (carry){
            result.digits.insertAfter(carry);
        }
        return result;
    }
    else{
        for (int i = 0; i<N_temp.length();i++){
            if ((this_temp.peekPrev() + N_temp.peekPrev() + carry) >= base){
                result.digits.insertAfter(this_temp.peekPrev() + N_temp.peekPrev() - base + carry);     
                carry = 1;
            }
            else{
                result.digits.insertAfter(this_temp.peekPrev() + N_temp.peekPrev() + carry);
                carry = 0;  
            }
            this_temp.movePrev();
            N_temp.movePrev();

        }
        while (this_temp.position() != 0){
            if((this_temp.peekPrev() + carry) >= base){
                result.digits.insertAfter(this_temp.peekPrev() - base + carry);     
                carry = 1;
            }
            else{
                result.digits.insertAfter(this_temp.peekPrev() + carry);
                carry = 0; 
            }
            this_temp.movePrev();
        }
        if (carry){
            result.digits.insertAfter(carry);
        }
        return result;
    }
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger result;
    BigInteger this_copy;
    BigInteger N_copy;
    this_copy.digits = this->digits;
    this_copy.signum = this->signum;
    N_copy.digits = N.digits;
    N_copy.signum = N.signum;
    result.signum = 1;
    List this_temp = digits;
    List N_temp = N.digits;
    int borrow = 0;      

    // (-B) - A == (-B) + (-A)
    if (this->signum == -1 && N.signum == 1){
        N_copy.signum = -1;
        return this_copy.add(N_copy);
    }
    // B - (-A) == B + A
    if (this->signum == 1 && N.signum == -1){
        N_copy.signum = 1;
        return this_copy.add(N_copy);
    }
    // (-B) - (-A) == A - B
    if (this->signum == -1 && N.signum == -1){
        this_copy.signum = 1;
        N_copy.signum = 1;
        return N_copy.sub(this_copy);
    }

    // 0 - (A) == A
    if (this->signum == 0 && N.signum == 1){
        result.signum = 1;
        result.digits = N.digits;
        return result;
    }
    // 0 - (-A) == -A
    if (this->signum == 0 && N.signum == -1){
        result.signum = -1;
        result.digits = N.digits;
        return result;
    }
    // (B) - 0 == B
    if (this->signum == 1 && N.signum == 0){
        result.signum = 1;
        result.digits = this->digits;
        return result;
    }
    // (-B) - 0 == -B
    if (this->signum == -1 && N.signum == 0){
        result.signum = -1;
        result.digits = this->digits;
        return result;
    }
    // 0 - 0 = 0
    if (this->signum == 0 && N.signum == 0){
        result.signum = 0;
        return result;
    }

    this_temp.moveBack();
    N_temp.moveBack();
    if (this_copy.compare(N_copy) ==  -1){
        result.signum = -1;
        for (int i = 0; i<this_temp.length();i++){
            if ((N_temp.peekPrev() - this_temp.peekPrev() - borrow) < 0){
                result.digits.insertAfter( N_temp.peekPrev()-this_temp.peekPrev() + base - borrow);     
                borrow = 1;
            }
            else{
                result.digits.insertAfter(N_temp.peekPrev() - this_temp.peekPrev() - borrow);
                borrow = 0;  
            }
            this_temp.movePrev();
            N_temp.movePrev();

        }
        while (N_temp.position() != 0){
            if((N_temp.peekPrev() - borrow) < 0){
                result.digits.insertAfter(N_temp.peekPrev() + base - borrow);     
                borrow = 1;
            }
            else{
                result.digits.insertAfter(N_temp.peekPrev() - borrow);
                borrow = 0; 
            }
            N_temp.movePrev();
        }

        return result;
    }
    else if (this_copy.compare(N_copy) ==  1){
        result.signum = 1;
        for (int i = 0; i<N_temp.length();i++){
            if ((this_temp.peekPrev() - N_temp.peekPrev() - borrow) < 0){
                result.digits.insertAfter(this_temp.peekPrev() - N_temp.peekPrev() + base - borrow);     
                borrow = 1;
            }
            else{
                result.digits.insertAfter(this_temp.peekPrev() - N_temp.peekPrev() - borrow);
                borrow = 0;  
            }
            this_temp.movePrev();
            N_temp.movePrev();

        }
        while (this_temp.position() != 0){
            if((this_temp.peekPrev() - borrow) < 0){
                result.digits.insertAfter(this_temp.peekPrev() + base - borrow);     
                borrow = 1;
            }
            else{
                result.digits.insertAfter(this_temp.peekPrev() - borrow);
                borrow = 0; 
            }
            this_temp.movePrev();
        }

        return result;
    }
    else{
        result.signum = 0;
        return result;
    }
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    
    BigInteger result;
    BigInteger temp_products;
    temp_products.signum = 1;
    long product;
    // List products;
    List this_temp = digits;
    List N_temp = N.digits;
    int shift = 1;
    long carry = 0;

    if (this->signum == 0 || N.signum == 0){
        result.signum = 0;
        return result;
    }
   
    for(N_temp.moveBack(); N_temp.position()!=0;N_temp.movePrev()){
        for(this_temp.moveBack(); this_temp.position()!=0;this_temp.movePrev()){
            product = ((this_temp.peekPrev() * N_temp.peekPrev())+carry);
            carry = 0;
            if (product > base){
                carry = product/base;
                product -= carry*base;
            }

            temp_products.digits.insertAfter(product);
            if (this_temp.position() == 1){
                while (carry){
                    product = carry;
                    carry = 0;
                    if (product > base){
                        carry = product/base;
                        product -= carry*base;
                    }
                    temp_products.digits.insertAfter(product);
                }
            }
        }
        result = result.add(temp_products);
        temp_products.digits.clear();
        for (int i = 0 ; i<shift ;i++){
            temp_products.digits.insertAfter(0);
        }
        shift++;

    } 
    if (this->signum == N.signum){
        result.signum = 1;
    }
    else{
        result.signum = -1;
    }
    return result;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    std::string add = ""; 
    std::string s = "";
    std::string zeros = "";
    int bound;
    if (signum == -1){
        s += "-";
        for(digits.moveFront(); digits.position()!=digits.length(); digits.moveNext()){
            add = std::to_string(digits.peekNext());
            if (add.length() != power){
                bound = power - add.length();
                if (digits.position()!=0 && isdigit(s[s.length()-1])){
                    for (int i = 0; i < bound; i++){
                        zeros += "0";
                    }
                    add = zeros + add;
                    zeros = "";
                }

            }
            if (add != "0"){
                s += add;
            }
        }
    } 
    else if (signum == 1){
        for(digits.moveFront(); digits.position()!=digits.length(); digits.moveNext()){
            add = std::to_string(digits.peekNext());
            if (add.length() != power){
                bound = power - add.length();
                if (digits.position()!=0 && isdigit(s[s.length()-1])){
                    for (int i = 0; i < bound; i++){
                        zeros += "0";
                    }
                    add = zeros + add;
                    zeros = "";
                }

            }
            if (add != "0"){
                s += add;
            }
        }
    }
    else{
        s += "0";
    }
    return s;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B)==0);
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == -1);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    return ((A.compare(B) == -1) || (A.compare(B)==0));
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == 1);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    return ((A.compare(B) == 1) || (A.compare(B)==0));
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    return A = A.add(B);
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    return A = A.sub(B);
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    return A = A.mult(B);
}
