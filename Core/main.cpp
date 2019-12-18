#include <iostream>
#include <fstream>
/*
#include "HaffCode.h"
#include "HaffCode.cpp"
*/
#include "HaffCode.cpp"
#include "Compressor.cpp"

using namespace std;

int main()
{
    /*
    HaffCode hc("C:\\Users\\11190\\Desktop\\1.txt");
    hc.printCode();
    hc.printCodeInfo();
    //cout << hc.getCode(100);
    */
    Compressor cpr;
    cpr.compress("C:\\Users\\11190\\Desktop\\1.txt","C:\\Users\\11190\\Desktop");
    //cpr.decompress("C:\\Users\\11190\\Desktop\\1.haff", "C:\\Users\\11190\\Desktop\\re.jpg");
    
    /*
    HaffCode hc("C:\\Users\\11190\\Desktop\\1.haff",HaffCode::DecompressFile);
    hc.printFileInfoStruct();
    hc.printCode();
    */
    /*
    fstream inFile;
    inFile.open("C:\\Users\\11190\\Desktop\\1.haff");
    char ch;
    while(!inFile.eof()){
        if(inFile.peek() == EOF)continue;
        inFile >> ch;
        cout << ch;
    }
    cout << endl;

    inFile.close();
    */
    return 0;
}