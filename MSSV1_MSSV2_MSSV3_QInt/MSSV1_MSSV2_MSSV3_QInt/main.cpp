//
//  main.cpp
//  abcxyz
//
//  Created by Đạt on 3/7/19.
//  Copyright © 2019 Đạt. All rights reserved.
//

#include <iostream>
#include <string>
#include <bitset>
#include<vector>
#include<algorithm>
#include"QInt.h"
#include <fstream>

using namespace std;

vector<string> splitString(string s, char c){
    vector<string> res = vector<string>();
    while(s.find(c)!=string::npos){
        res.push_back(s.substr(0,s.find(c)));
        s = s.substr(s.find(c) + 1);
    }
    res.push_back(s);
    return res;
}

string getOperator(vector<string> s){
    vector<string> myOperator = {"+","-","*","/","<<",">>","rol","ror","&","|","^","~"};
    for(int j = 0;j<myOperator.size();j++){
        if(find(s.begin(),s.end(),myOperator[j])!=s.end()){
            return myOperator[j];
        }
    }

    return "null";
}

string calWithOperator(string s){
    string res = "";
    vector<string> tmp = splitString(s,' ');
    int flag1,flag2;
    string num1,num2,myOperator;
    myOperator = getOperator(tmp);
    
    //truong hop chung cho + - * / & | ^
    if(myOperator == "+"|| myOperator == "-"|| myOperator == "*"|| myOperator == "/" ||
       myOperator == "&" || myOperator == "|" || myOperator == "^"){
        flag1 = stoi(tmp[0]);
        num1 = tmp[1];
        num2 = tmp[3];
        if(myOperator == "-"){
            return (QInt(num1,flag1) - QInt(num2,flag1)).convertWithFlag(flag1);
        }
        
        if(myOperator == "*"){
            return (QInt(num1,flag1) * QInt(num2,flag1)).convertWithFlag(flag1);
        }
        
        if(myOperator == "/"){
            return (QInt(num1,flag1) / QInt(num2,flag1)).first.convertWithFlag(flag1);
        }
        
        if(myOperator == "&"){
            return (QInt(num1,flag1) & QInt(num2,flag1)).convertWithFlag(flag1);
        }
        
        if(myOperator == "|"){
            return (QInt(num1,flag1) | QInt(num2,flag1)).convertWithFlag(flag1);
        }
        
        if(myOperator == "^"){
            return (QInt(num1,flag1) ^ QInt(num2,flag1)).convertWithFlag(flag1);
        }
        return (QInt(num1,flag1) + QInt(num2,flag1)).convertWithFlag(flag1);
    }
    
    //dich bit trai phai
    if(myOperator == "<<" || myOperator == ">>"){
        flag1 = stoi(tmp[0]);
        num1 = tmp[1];
        int c = stoi(tmp[3]);
        if(myOperator == "<<"){
            return (QInt(num1,flag1)<<c).convertWithFlag(flag1);
        }
        return (QInt(num1,flag1)>>c).convertWithFlag(flag1);
    }
    
    //xoay trai phai
    if(myOperator == "rol" || myOperator == "ror"){
        flag1 = stoi(tmp[0]);
        num1 = tmp[2];
        if(myOperator == "ror"){
            return QInt(num1,flag1).rotateRight().convertWithFlag(flag1);
        }
        return QInt(num1,flag1).rotateLeft().convertWithFlag(flag1);
    }
    
    //truong hop rieng
    if(myOperator == "~"){
        flag1 = stoi(tmp[0]);
        num1 = tmp[2];
        return (~QInt(num1,flag1)).convertWithFlag(flag1);
    }
    
    //truong hop khong co toan tu -> chuyen doi so
    flag1 = stoi(tmp[0]);
    flag2 = stoi(tmp[1]);
    num1 = tmp[2];
    
    return QInt(num1,flag1).convertWithFlag(flag2);
    
}

void progress(string fileIn,string fileOut){
    ifstream fIn (fileIn);
    ofstream fOut (fileOut);
    string line;
    while(getline(fIn,line)){
        fOut << calWithOperator(line) << endl;
    }
    fIn.close();
    fOut.close();
}




int main(int argc, const char * argv[]) {
    progress(argv[1],argv[2]);
	system("pause");
    return 0;
}
