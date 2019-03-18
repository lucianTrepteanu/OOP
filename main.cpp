/**
 * TODO: Restructurare in mai multe fisiere
 * TODO: Aranjat cod la +,-,/,*
*/

#include <iostream>
#include <cstring>
#include "vectordyn.cpp"
#include "BigNum.cpp"
#include "BigNumArray.cpp"
using namespace std;

int main(){
    BigNum a=BigNum(25);
    BigNum b=BigNum(24);

    BigNumArray arr1=BigNumArray(3);
    cin>>arr1;
    cout<<arr1.maxAbsArray()<<endl;

    //cout<<getSqrt(a)<<" "<<getSqrt(b)<<endl;

    /*if(arr1==arr2){
        cout<<"EGALE\n";
    } else if(arr1!=arr2){
        cout<<"DIFERITE\n";
    }
    if(arr1<arr2){
        cout<<"MAI MIC\n";
    }*/

    return 0;
}
