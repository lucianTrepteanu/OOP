// TODO: x

#include <iostream>
#include "VectorDyn.cpp"
#include "PositiveBigNum.cpp"
#include "BigNum.cpp"
#include "VectorIterator.cpp"

#include <algorithm>

using namespace std;

int main(){
    /*BigNum a=BigNum();
    cin>>a;
    cout<<a.getSqrt();
    cout<<" "<<a.getSqrt();
    cout<<" "<<a.getSqrt();*/

	VectorDyn<int> v1;
	for(int i=1;i<=5;i++){
		v1.push(i);
	}
	VectorIterator<int> it=VectorIterator<int>(&v1);

    for(it.begin();!it.isDone();it.getNext()){
        cout<<it.currentItem()<<" ";
    }

    VectorDyn<BigNum> v;
    v.push(BigNum(123));
    v.push(BigNum(21));
    v.push(BigNum(-1));
    v.push(BigNum(-41));

    sort(v.v+1,v.v+v.getSize()+1);

    cout<<endl;
    VectorIterator<BigNum>bigIt=VectorIterator<BigNum>(&v);
    for(bigIt.begin();!bigIt.isDone();bigIt.getNext()){
        cout<<bigIt.currentItem()<<" ";
    }
	
	/*BigNum a=BigNum(123);
	BigNum b=BigNum(-21);
	
    cout<<a/b;*/
    /*PositiveBigNum a=PositiveBigNum(213);
    BigNum b;
    b=a;
    cout<<b;*/

    /*if(a<b){
        cout<<"MIC\n";
    } else if(a==b){
        cout<<"EGAL\n";
    } else if(b<a){
        cout<<"MARE\n";
    }*/

    //cout<<a<<" "<<b<<endl;

    //cin>>a>>b;

    /*if(a<b){
        cout<<"DA";
    } else {
        cout<<"NU";
    }*/
    /*if(a/b*b+a%b==a){
        cout<<"DA";
    } else {
        cout<<"NU";
    }*/

    /*int *a=new int[10];
    for(int i=0;i<10;i++){
        a[i]=i;
    }

    VectorDyn<int> v=VectorDyn<int>(a,10);

    for(int i=1;i<=10;i++){
        cout<<v[i]<<" ";
    }*/

    return 0;
}