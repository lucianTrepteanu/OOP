/**
 * TODO: x
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

    /*BigNumArray arr1=BigNumArray(3);
    BigNumArray arr2=BigNumArray(3);
    cin>>arr1>>arr2;
    cout<<arr1.maxAbsArray()<<endl;
    cout<<arr1*arr2<<endl;
    cout<<arr1<<endl;*/

    /*cin>>a;
    cout<<getSqrt(a)<<" "<<getSqrt(b)<<endl;*/

    /*if(arr1==arr2){
        cout<<"EGALE\n";
    } else if(arr1!=arr2){
        cout<<"DIFERITE\n";
    }
    if(arr1<arr2){
        cout<<"MAI MIC\n";
    }*/

    //cin>>a>>b;
    //cout<<a+b<<" "<<a-b<<" "<<a*b<<" "<<a/b<<" "<<a%b<<" "<<getSqrt(b)<<endl;
    BigNum d=BigNum(365*365+13);
    cout<<getSqrt(d);
    //cout<<" "<<BigNum(2004)/BigNum(2);

    /*BigNum c;
    cin>>c;
    a=b=c;
    cout<<a<<" "<<b<<" "<<c<<endl;*/

    return 0;
}
