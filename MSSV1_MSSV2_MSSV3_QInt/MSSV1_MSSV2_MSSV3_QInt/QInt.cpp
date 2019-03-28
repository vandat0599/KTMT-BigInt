//
//  QInt.cpp
//  abcxyz
//
//  Created by Đạt on 3/17/19.
//  Copyright © 2019 Đạt. All rights reserved.
//

#include "QInt.h"

QInt::QInt(){
    arrayBits = vector< long long>(2,0);
}

QInt::QInt(string s, int flag){
    QInt::arrayBits = vector<long long>(2,0);
    switch(flag){
        case DEC:{
            if(s[0] == '-'){
                *this = towCompelementOf(QInt(s.substr(1),10).toBinString());
            }else{
                int i = 0;
                while(s!="0"){
                    int bit = (s[s.size()-1] - 48)%2;
                    QInt::setBitAt(i,bit);
                    s = div2StringAsNumber(s);
                    i++;
                }
            }
            break;
        }
        case OCT:{
            cout << "still working!!" << endl;
            break;
        }
        case BIN:{
            *this = binStringToQInt(s);
            break;
        }
        case HEX:{
            *this = QInt::binStringToQInt(QInt::hexToBin(s));
            break;
        }
    }
}

vector<long long> QInt::getArrayBits(){
    return arrayBits;
}

string QInt::div2StringAsNumber(string s){
    string s1;
    char s2[5];
    int chia = s[0] - 48;
    int i = 1;
    if (s.length() != 1){
        while (i < s.length()){
            if (chia < 2){
                int temp = s[i] - 48;
                chia = chia * 10 + temp;
            }else{
                i--;
            }
            s1 = s1 + to_string(chia/2);
            chia = chia % 2;
            i++;
        }
    }else{
        s1 = s1 + to_string(chia/2);
    }
    return s1;
}

void QInt::push_bit_back(int bit){
    *this = *this<<1;
    setBitAt(0,bit);
}


void QInt::onBitQIntAt(int position){
    int tmp = 1;
    if(position > MAX_POSITION_64_BIT){
        position -= (MAX_POSITION_64_BIT+1);
        tmp = 0;
//        cout << " bug " << endl;
    }
    QInt::onBitLongLongAt(arrayBits[tmp],position);
}

void QInt::onBitLongLongAt( long long &a,int position){
    unsigned long long k = 1;
    a = (k<<position)|a;
}

void QInt::offBitQIntAt(int position){
    int tmp = 1;
    if(position > MAX_POSITION_64_BIT){
        position -= (MAX_POSITION_64_BIT + 1);
        tmp = 0;
        //        cout << " bug " << endl;
    }
    QInt::offBitLongLongAt(arrayBits[tmp],position);
}

void QInt::offBitLongLongAt( long long &a,int position){
    unsigned long long k = 1;
    a = a&~(k<<position);
}

bool QInt::getBitLongLongAt( long long &a, int position){
    unsigned long long k = 1;
    return (k<<position)&a;
}

bool QInt::getBitAt(int position){
    int tmp = 1;
    if(position > MAX_POSITION_64_BIT){
        position -= (MAX_POSITION_64_BIT + 1);
        tmp = 0;
    }
    return getBitLongLongAt(arrayBits[tmp],position);
}

void QInt::setBitAt(int position, int bit){
    if(bit == 1){
        onBitQIntAt(position);
    }else{
        offBitQIntAt(position);
    }
}

void QInt::exportBitsOf(string number){
    
}


QInt QInt::operator>>(int c){
    if(c > MAX_POSITION_64_BIT){
        QInt::arrayBits[1] = QInt::arrayBits[0];
        QInt::arrayBits[0] = QInt::arrayBits[0]>>MAX_POSITION_64_BIT;
        QInt::arrayBits[1] = QInt::arrayBits[1]>>(c - (MAX_POSITION_64_BIT + 1));
    }else{
        QInt::arrayBits[1] = QInt::arrayBits[1]>>c;
        for(int i=0;i<c;i++){
            QInt::setBitAt(MAX_POSITION_64_BIT + 1 - c + i,getBitAt(MAX_POSITION_64_BIT + 1 + i));
//            cout << "set bit: " <<getBitAt(MAX_POSITION_64_BIT + 1 + i) << " p: " << MAX_POSITION_64_BIT + 1 + i << " at: " <<MAX_POSITION_64_BIT + 1 - c + i << endl;
        }
        QInt::arrayBits[0] = QInt::arrayBits[0]>>c;
    }
//    if(c>MAX_POSITION_64_BIT+1){
//        QInt::arrayBits[1] = QInt::arrayBits[1]>>(c - (MAX_POSITION_64_BIT + 1));
//    }else{
//        QInt::arrayBits[1] = QInt::arrayBits[1]>>c;
//    }
//
//    for(int i=0;i<c;i++){
//        QInt::setBitAt(MAX_POSITION_64_BIT + 1 - c + i,getBitAt(MAX_POSITION_64_BIT + 1 + i));
//    }
//
//    if(c > MAX_POSITION_64_BIT){
//        QInt::arrayBits[0] = QInt::arrayBits[0]>>MAX_POSITION_64_BIT;
//    }else{
//        QInt::arrayBits[0] = QInt::arrayBits[0]>>c;
//    }
    return *this;
}

QInt QInt::operator<<(int c){
    if(c > MAX_POSITION_64_BIT){
        QInt::arrayBits[0] = QInt::arrayBits[1];
        QInt::arrayBits[1] = 0;
        QInt::arrayBits[0] = QInt::arrayBits[0]<<(c - (MAX_POSITION_64_BIT + 1));
    }else{
        QInt::arrayBits[0] = QInt::arrayBits[0]<<c;
        for(int i=0;i<c;i++){
            QInt::setBitAt(MAX_POSITION_64_BIT + c - i,getBitAt(MAX_POSITION_64_BIT - i));
//            cout << "set bit: " << getBitAt(MAX_POSITION_64_BIT - i) << " at: " <<MAX_POSITION_64_BIT + c - i << endl;
        }
        QInt::arrayBits[1] = QInt::arrayBits[1]<<c;
    }
    
    
    return *this;
}

QInt QInt::operator&(QInt t){
    vector< long long> tmp = t.getArrayBits();
    QInt::arrayBits[1] = QInt::arrayBits[1]&tmp[1];
    QInt::arrayBits[0] = QInt::arrayBits[0]&tmp[0];
    return *this;
}

QInt QInt::operator|(QInt t){
    vector< long long> tmp = t.getArrayBits();
    QInt::arrayBits[1] = QInt::arrayBits[1]|tmp[1];
    QInt::arrayBits[0] = QInt::arrayBits[0]|tmp[0];
    return *this;
}

QInt QInt::operator~(){
    QInt::arrayBits[1] = ~QInt::arrayBits[1];
    QInt::arrayBits[0] = ~QInt::arrayBits[0];
    return *this;
}

QInt QInt::operator^(QInt t){
    vector< long long> tmp = t.getArrayBits();
    QInt::arrayBits[1] = QInt::arrayBits[1]^tmp[1];
    QInt::arrayBits[0] = QInt::arrayBits[0]^tmp[0];
    return *this;
}

QInt QInt::operator=(QInt t){
    QInt::arrayBits = t.getArrayBits();
    return *this;
}

string QInt::toBinString(){
    string res ="";
    for(int i =MAX_POSITION_128_BIT;i>=0;i--){
        res.push_back(getBitAt(i) + 48);
    }
    return res;
}

string QInt::convertToBin(){
    return QInt::simpleBin(QInt::toBinString());
}

string QInt::convertToDec(){
    if(QInt::getBitAt(MAX_POSITION_128_BIT) == 1){
        return "-" + QInt::simpleDec(QInt::binToDec((~(*this - QInt("1",10))).convertToBin()));
    }
    return QInt::simpleDec(QInt::binToDec(QInt::convertToBin()));
}

string QInt::convertToHex(){
    return QInt::simpleHex(QInt::binToHex(QInt::convertToBin()));
}

string QInt::decToBin(string s){
    return QInt(s,DEC).toBinString();
}

string QInt::decToHex(string dec){
    return QInt::binToHex(QInt::decToBin(dec));
}

QInt QInt::towCompelementOf(string s){
    string res ="";
    char tmp = '1';
    for(int i=s.size() - 1;i>=0;i--){
        s[i]=='1'?s[i]='0':s[i]='1';
        pair<char,char> p = plusBit(s[i],tmp);
        res += p.first;
        tmp = p.second;
    }
    reverse(res.begin(), res.end());
    return QInt::binStringToQInt(res);
}

pair<char,char> QInt::plusBit(char a,char b){
    if(a != b){
        return {'1','0'};
    }else{
        if(a == '0'){
            return {'0','0'};
        }else{
            return {'0','1'};
        }
    }
}

QInt QInt::binStringToQInt(string bit){
    QInt res = QInt();
    for(int i=0;i<bit.size();i++){
        res.setBitAt(bit.size()-1-i, bit[i] - 48);
    }
    return res;
}

int QInt::value4BitOf(string bit){
    char res = 0;
    for(int i = 0;i<bit.size();i++){
        res = (res<<1)|(bit[i]-48);
    }
    return (int)res;
}

string QInt::plus3ToBinSuportBinToDec(string s){
    string res = "00000000";
    unsigned char mask = 0x80;
    int tmp = value4BitOf(s) + 3;
    for(int i=0;i<8;i++){
        if((tmp&mask) !=0){
            res[i] = '1';
        }
        mask = mask >> 1;
    }
    return res.substr(4);
}

vector<string> QInt::group4Bit(string bit){
    vector<string> res = vector<string>();
    int size = bit.size()/4;
    int t = bit.size()-size*4;
    res.push_back(bit.substr(0,t));
    for(int i=0;i<size;i++){
        string tmp = bit.substr(t,4);
        res.push_back(tmp);
        t+=4;
    }
    return res;
}

string QInt::updateStringSuportBinToDec(string s){
    string res = "";
    vector<string> tmp = group4Bit(s);
    for(int i=0;i<tmp.size();i++){
        if(tmp[i].size() > 0 && value4BitOf(tmp[i]) > 4){
            tmp[i] = plus3ToBinSuportBinToDec(tmp[i]);
        }
    }
    for(int i=0;i<tmp.size();i++){
        res += tmp[i];
    }
    return res;
}

string QInt::binToDec(string bit){
    string res = "";
    for(int i=0;i<bit.size()-1;i++){
        res += bit[i];
        res = updateStringSuportBinToDec(res);
    }
    res += bit[bit.size()-1];
    vector<string> tmp = group4Bit(res);
    res.clear();
    for(string s:tmp){
        res += to_string(value4BitOf(s));
    }
    return QInt::simpleDec(res);
}

map<char,string> QInt::hexSuportGetMapCharBin(){
    map<char,string> m = {
        {'a',"1010"},
        {'b',"1011"},
        {'c',"1100"},
        {'d',"1101"},
        {'e',"1110"},
        {'f',"1111"},
        {'A',"1010"},
        {'B',"1011"},
        {'C',"1100"},
        {'D',"1101"},
        {'E',"1110"},
        {'F',"1111"},
    };
    return m;
}

map<string,char> QInt::hexSuportGetMapBinChar(){
    map<string,char> m = {
        
//        {"1010",'a'},
//        {"1011",'b'},
//        {"1100",'c'},
//        {"1101",'d'},
//        {"1110",'e'},
//        {"1111",'f'},
        {"1010",'A'},
        {"1011",'B'},
        {"1100",'C'},
        {"1101",'D'},
        {"1110",'E'},
        {"1111",'F'},
    };
    return m;
}

string QInt::full4BitOf(string bit){
    for(int i = bit.size();i<4;i++){
        bit = "0"+bit;
    }
    return bit;
}

string QInt::binToHex(string bit){
    string res = "";
    vector<string> bits = QInt::group4Bit(bit);
    map<string,char> mapHexBinChar = QInt::hexSuportGetMapBinChar();
    bits[0] = QInt::full4BitOf(bits[0]);
    for(int i=0;i<bits.size();i++){
        int tmp = value4BitOf(bits[i]);
        if(tmp > 9){
            res += mapHexBinChar[bits[i]];
        }else{
            res += to_string(tmp);
        }
    }
    return QInt::simpleHex(res);
}

string QInt::hexToBin(string hex){
    string res = "";
    map<char,string> mapHexCharBin = QInt::hexSuportGetMapCharBin();
    for(int i=0;i<hex.size();i++){
        int tmp = hex[i] - 48;
        if(tmp>9){
            res += mapHexCharBin[char(tmp+48)];
        }else{
            res += QInt::full4BitOf(QInt::simpleBin(QInt::decToBin(to_string(tmp))));
        }
    }
    return QInt::simpleBin(res);
}

string QInt::hexToDec(string hex){
    return QInt::binToDec(QInt::hexToBin(hex));
}


string QInt::simpleBin(string bit){
    int tmp = bit.find('1');
    if(tmp!=string::npos){
        return bit.substr(tmp);
    }else{
        return "0";
    }
    return bit;
}

string QInt::simpleDec(string dec){
    while(dec[0]=='0'){
        dec.erase(0,1);
    }
    if(dec.size() > 0){
        return dec;
    }
    return "0";
}

string QInt::simpleHex(string dec){
    while(dec[0]=='0'){
        dec.erase(0,1);
    }
    if(dec.size()>0){
        return dec;
    }
    return "0";
}

QInt QInt::rotateLeft(){
    string tmp = QInt::simpleBin(this->toBinString());
    char leftBit = tmp[0];
    for(int i = 0;i<tmp.size()-1;i++){
        tmp[i] = tmp[i+1];
    }
    tmp[tmp.size()-1] = leftBit;
    *this =QInt(tmp,2);
    return *this;
    
}

QInt QInt::rotateRight(){
    string tmp = QInt::simpleBin(this->toBinString());
    char rightBit = tmp[tmp.size()-1];
    for(int i = tmp.size()-1;i>=1;i--){
        tmp[i] = tmp[i-1];
    }
    tmp[0] = rightBit;
    *this =QInt(tmp,2);
    return *this;
}

QInt QInt::operator+(QInt t)
{
    QInt result;
    char temp = '0';
    int a, b;
    for (int i = 0; i < 128; i++)
    {
        a = this->getBitAt(i);
        b = t.getBitAt(i);
        pair<int, char> p = plusBit1(a, b,temp);
        result.setBitAt(i, p.first);
        temp = p.second;
    }
    return result;
}
//Qui ước phép cộng 1 +1, 0+1...
pair<int, char> QInt::plusBit1(int a, int b, char c)
{
    if (c == '0')
    {
        if (a != b)
        {
            return { 1,'0'};
        }
        else
        {
            if (a == 0)
            {
                return { 0,'0'};
            }
            else
            {
                return { 0,'1'};
            }
        }
    }
    else
    {
        if (a != b)
        {
            return { 0,'1'};
        }
        else
        {
            if (a == 0)
            {
                return { 1,'0'};
            }
            else
            {
                return { 1,'1'};
            }
        }
    }
}
//Phép trừ, xong rồi.
QInt QInt::operator-(QInt t)
{
    QInt result;
    t = t.towCompelementOf(t.toBinString());
    return result = *this + t;
}
//phép nhân, xong rồi.
QInt QInt::operator*(QInt t) {
    QInt A = QInt();
    int k = 128;
    int Q1 = 0;
    int temp;
    while (k > 0)
    {
        temp = t.getBitAt(0);
        if (temp == 1 && Q1 == 0)
        {
            A = A - *this;
        }
        if (temp == 0 && Q1 == 1)
        {
            A = A + *this;
        }
        Q1 = t.getBitAt(0);
        t = t >> 1;
        t.setBitAt(127, A.getBitAt(0));
        A = A >> 1;
        k--;
    }
    string s = A.toBinString();
    s = s + t.toBinString();
    QInt result = binStringToQInt(s);
    return result;
}

pair<QInt,QInt> QInt::operator/(QInt t) {
    
    QInt A = QInt();
    int n = 128;
    int temp,temp2;
    while (n > 0)
    {
        temp = A.getBitAt(127);
        if (temp == 0)
        {
            A = A << 1;
            A.setBitAt(0, t.getBitAt(127));
            t = t << 1;
            A = A - *this;
        }
        else
        {
            A = A << 1;
            A.setBitAt(0, t.getBitAt(127));
            t = t << 1;
            A = A + *this;
        }
        temp2 = A.getBitAt(127);
        if (temp2 == 0)
        {
            t.setBitAt(0, 1);
        }
        else
        {
            t.setBitAt(0, 0);
        }
        n--;
    }
    if (A.getBitAt(127) == 1)
    {
        A = A + *this;
    }
    
    return { t,A };  //thương: t, số dư: A
}

string QInt::convertWithFlag(int flag){
    switch (flag) {
        case BIN:
            return QInt::convertToBin();
        case DEC:
            return QInt::convertToDec();
        case HEX:
            return QInt::convertToHex();
        default:
            break;
    }
    return "";
}




