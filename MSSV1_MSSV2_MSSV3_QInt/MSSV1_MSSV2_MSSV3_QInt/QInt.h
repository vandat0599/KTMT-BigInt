//
//  QInt.h
//  abcxyz
//
//  Created by Đạt on 3/17/19.
//  Copyright © 2019 Đạt. All rights reserved.
//

#ifndef QInt_h
#define QInt_h

#include <iostream>
#include<vector>
#include<string>
#include<map>

#define MAX_POSITION_64_BIT 63
#define MAX_POSITION_128_BIT 127
#define OCT 8
#define BIN 2
#define DEC 10
#define HEX 16

using namespace std;

class QInt {
private:
    vector<long long> arrayBits;
public:
    //done
    QInt();
    QInt(string,int);

    //done
    vector<long long> getArrayBits();
    int getBitSize();
    
    //done
    void onBitQIntAt(int position);
    void onBitLongLongAt( long long &,int);
    void offBitQIntAt(int position);
    void offBitLongLongAt( long long &,int);
    
    
    //done: QInt
    void exportBitsOf(string);
    bool getBitAt(int);
    bool getBitLongLongAt( long long &,int);
    void setBitAt(int,int);
    string toBinString();
    string convertToBin();
    string convertToDec();
    string convertToHex();
    QInt binStringToQInt(string);
    
    
    //done
    void push_bit_back(int);
    string div2StringAsNumber(string);
    
    //done
    QInt operator+(QInt);
    QInt operator-(QInt);
    QInt operator*(QInt);
    pair<QInt,QInt> operator/(QInt);
    
    //dd lam: done
    pair<int, char> plusBit1(int a, int b,char c);
    
    //done
    QInt operator>>(int);
    QInt operator<<(int);
    
    //done
    QInt operator&(QInt);
    QInt operator~();
    QInt operator|(QInt);
    QInt operator^(QInt);
    QInt operator=(QInt);
    
    //done
    QInt towCompelementOf(string);
    pair<char,char> plusBit(char a,char b);
    
//    string convertOcToBin();
//    string convertHexToBin();
    
    // support fc done
    string updateStringSuportBinToDec(string);//done
    vector<string> group4Bit(string);//done
    string plus3ToBinSuportBinToDec(string);//done
    int value4BitOf(string);//done
    map<char,string> hexSuportGetMapCharBin();//DONE
    map<string,char> hexSuportGetMapBinChar();//DONE
    string full4BitOf(string);//DONE
    string simpleBin(string); //done
    string simpleDec(string);//done
    string simpleHex(string);//done
    
    //convert: done
    
    //bin
    string binToDec(string);//done
    string binToHex(string);//done
    
    //hex
    string hexToBin(string);//done
    string hexToDec(string);//done
    
    //dec
    string decToBin(string);//done
    string decToHex(string);//done
    
    //Rotate
    //left
    QInt rotateLeft();
    
    //right
    QInt rotateRight();
    
    //
    string convertWithFlag(int);
    
    
};


#endif /* QInt_h */
