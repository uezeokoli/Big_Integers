// /****************************************************************************************
// *  Ugonna Ezeokoli
// *  uezeokol
// *  2024 Winter CSE101 PA6
// *  Arithmetic.cpp
// *  Outputs operations of A and B into a new file
// *****************************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include <fstream>
#include"BigInteger.h"

using namespace std;

int main(int argc, char *argv[]){
    if (argc != 3){
        fprintf(stderr, "Invalid number of command line arguments\n");
        exit(EXIT_FAILURE);
    }

    string outfile_name =  argv[2];
    fstream infile;
    infile.open(argv[1],ios::in);
    fstream outfile;             //openning output file
    outfile.open(outfile_name, ios::out);  //ios::out specifies openning a file for writing

    string A_str;
    string B_str;
    string discard;
    getline(infile,A_str);
    getline(infile,discard);
    getline(infile,B_str);

    
    BigInteger A = BigInteger(A_str);
    BigInteger B = BigInteger(B_str);

    outfile << A<< endl;
    outfile << endl;
    outfile << B << endl;
    outfile << endl;
    outfile << A+B << endl;
    outfile<<endl;
    outfile << A-B << endl;
    outfile<<endl;
    outfile << A-A << endl;
    outfile<<endl;
    outfile << (3*A) - (2*B) << endl;
    outfile<<endl;
    outfile << A*B << endl;
    outfile<<endl;
    outfile << A*A << endl;
    outfile<<endl;
    outfile << B*B << endl;
    outfile<<endl;
    outfile << 9*(A*A*A*A) + 16*(B*B*B*B*B) << endl;
    outfile<<endl;

    
    outfile.close();
    infile.close();

}