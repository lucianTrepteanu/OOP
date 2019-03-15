/**
 * TODO: operator de citire!! : DONE
 * TODO: implementat scaderea pe intregi a-b=sign*(max-min)
*/

#include <iostream>
#include <cstring>
#include "vectordyn.cpp"
using namespace std;

class BigNum{
public:
    int sign;
    VectorDyn<int>digits;
public:
    BigNum(){sign=1;} //apeleaza constructorul de vector 
    BigNum(int val){
        digits.Clear();
        sign=1;
        if(val<0){
            sign=-1;
            val=-val;
        }

        int idx=0;
        do{
            idx++;
            //digits.setPos(idx,val%10); 
            digits.push(val%10);
            val/=10;
        }while(val);
    }
    BigNum(const BigNum&alt){
        sign=alt.sign;
        digits=alt.digits; //apelez copierea din VectorDyn
    }
    ~BigNum(){}

    BigNum &operator=(BigNum alt); //da
    bool operator==(BigNum &alt); //da
    bool operator<(BigNum &alt); //da

    friend bool cmpPositive(BigNum &a, BigNum &b); //da

    friend istream &operator >>(istream &in,BigNum &x); //da
    friend ostream &operator <<(ostream &out,BigNum &x); //da

    friend BigNum addPositive(BigNum a,BigNum b); //da
    friend BigNum subPositive(BigNum a,BigNum b); //da

    BigNum operator +(BigNum &alt); //da
    BigNum operator -(BigNum &alt); //da
    BigNum operator *(BigNum &alt); //da
    BigNum operator /(BigNum &alt);
    BigNum operator %(BigNum &alt); //da

    friend BigNum maxAbs(const BigNum &a,const BigNum &b); //imd

    friend BigNum getSqrt(BigNum &a); //imd
};

BigNum& BigNum:: operator =(BigNum alt){
    sign=alt.sign;
    digits=alt.digits;
    return (*this);
}

bool cmpPositive(BigNum &a,BigNum &b){
    int idx=1;
    if(a.digits.getSize()<b.digits.getSize()){
        return true;
    } else if(a.digits.getSize()>b.digits.getSize()){
        return false;
    }
    while(idx<=a.digits.getSize() && a.digits[idx]==b.digits[idx]){
        idx++;
    }

    if(a.digits[idx]<b.digits[idx]){
        return true;
    }
    return false;
}

bool BigNum::operator==(BigNum &alt){
    if(sign!=alt.sign){
        return false;
    }
    if(digits.getSize()!=alt.digits.getSize()){
        return false;
    }
    int idx=1;
    while(idx<=digits.getSize() && digits[idx]==alt.digits[idx]){
        idx++;
    }

    if(idx>digits.getSize()){
        return true;
    }
    return false;
}

bool BigNum::operator <(BigNum &alt){
    if(sign==1 && alt.sign==1){
        return cmpPositive((*this),alt);
    } else if(sign==1 && alt.sign==-1){
        return false;
    } else if(sign==-1 && alt.sign==1){
        return true;
    } else {
        return cmpPositive(alt,(*this));
    }
}

ostream &operator <<(ostream &out,BigNum &x){
    if(x.sign==-1){
        out<<'-';
    }
    for(int i=x.digits.getSize();i>0;i--){
        out<<x.digits[i]<<" ";
    }
    return out;
}

istream &operator >>(istream &in,BigNum &x){
    char ch;
    x.digits.Clear();
    x.sign=1;

    if(!in.eof()){
        in.get(ch);
    }
    if(ch=='-'){
        x.sign=-1;
    } else {
        x.digits.push(ch-'0');
    }
    while(!in.eof()){
        in.get(ch);
        x.digits.push(ch-'0');
    }

    int st=1,dr=x.digits.getSize();
    while(st<dr){  //dam reverse
        int a=x.digits[st];
        x.digits.setPos(st,x.digits[dr]);
        x.digits.setPos(dr,a);
        st++;dr--;
    }

    return in;
}

BigNum addPositive(BigNum a,BigNum b){
    BigNum res;
    res.digits.shrinkTo(max(b.digits.getSize(),a.digits.getSize())+1);
    int i,t=0;
    for(i=1;i<=a.digits.getSize() || i<=b.digits.getSize() || t;i++,t/=10){
        t+=a.digits[i]+b.digits[i];
        res.digits.setPos(i,t%10);
    }

    while(res.digits.getSize()>1 && res.digits[res.digits.getSize()]==0){
        res.digits.shrinkTo(res.digits.getSize()-1);
    }

    return res;
}

BigNum subPositive(BigNum a,BigNum b){
    BigNum res=a;
    int i,t=0;
    for(i=1;i<=res.digits.getSize();i++){
        if(i<=b.digits.getSize()){
            int pastValue=res.digits[i];
            res.digits.setPos(i,pastValue-b.digits[i]-t);
        } else {
            int pastValue=res.digits[i];
            res.digits.setPos(i,pastValue-t);
        }

        if(res.digits[i]<0){
            t=1;
        } else {
            t=0;
        }

        int pastValue=res.digits[i];
        res.digits.setPos(i,pastValue+10*t);
    }

    //leading zeros
    while(res.digits.getSize()>1 && res.digits[res.digits.getSize()]==0){
        res.digits.shrinkTo(res.digits.getSize()-1);
    }

    //!daca e nr 0???
    return res;
}

BigNum BigNum::operator+(BigNum &alt){
    BigNum res;
    if(sign==1 && alt.sign==1){
        res=addPositive((*this),alt);
    } else if(sign==1 && alt.sign==-1){
        BigNum aux=alt;
        aux.sign=-aux.sign;
        res=(*this)-aux;
    } else if(sign==-1 && alt.sign==1){
        BigNum aux=(*this);
        aux.sign=-aux.sign;
        res=alt-aux;
    } else {
        BigNum aux1=(*this),aux2=alt;
        aux1.sign=-aux1.sign;
        aux2.sign=-aux2.sign;
        res=aux1+aux2;
        res.sign=-res.sign;
    }
    return res;
}

BigNum BigNum::operator-(BigNum &alt){
    BigNum res;
    if(sign==1 && alt.sign==1){

        if(cmpPositive((*this),alt)){
            res=alt-(*this);
            res.sign=-res.sign;
        } else {
            res=subPositive((*this),alt);
        }
    } else if(sign==1 && alt.sign==-1){
        BigNum aux=alt;
        aux.sign=-aux.sign;
        res=(*this)+aux;
    } else if(sign==-1 && alt.sign==1){
        BigNum aux=(*this);
        aux.sign=-aux.sign;
        res=aux+alt;
        res.sign=-res.sign;
    }else{
        BigNum aux1=(*this);
        aux1.sign=-aux1.sign;
        BigNum aux2=alt;
        aux2.sign=-aux2.sign;

        if(cmpPositive(aux2,aux1)){
            res=subPositive(aux2,aux1);
        } else {
            res=subPositive(aux1,aux2);
            res.sign=-res.sign;
        }
    }

    return res;
}

BigNum BigNum::operator*(BigNum &alt){
    BigNum res;
    res.digits.shrinkTo(digits.getSize()+alt.digits.getSize()+1);

    int t;
    res.sign=sign*alt.sign;
    for(int i=1;i<=digits.getSize();i++){
        for(int t=0,j=1;j<=alt.digits.getSize() || t;j++,t/=10){
            int pastValue=res.digits[i+j-1];
            t+=pastValue+digits[i]*alt.digits[j];
            res.digits.setPos(i+j-1,t%10);
        }
    }

    while(res.digits.getSize()>1 && res.digits[res.digits.getSize()]==0){
        res.digits.shrinkTo(res.digits.getSize()-1);
    }

    return res;
}

BigNum BigNum::operator%(BigNum &alt){
    BigNum zero=BigNum(0);
    if(alt==zero){
        throw -1;
    }

    BigNum res=(*this);

    while(alt<res || alt==res){
        BigNum aux=res;
        aux=aux-alt;
        res=aux;
    }

    while(res.digits.getSize()>1 && res.digits[res.digits.getSize()]==0){
        res.digits.shrinkTo(res.digits.getSize()-1);
    }

    return res;
}

//!https://math.mit.edu/~stevenj/18.335/newton-sqrt.pdf
BigNum getSqrt(BigNum &a){
    if(a.sign==-1){
        throw -1;
    }

    BigNum lef=a;
    BigNum one=BigNum(1);
    BigNum rig=a+one;

}

int main(){
    BigNum a=BigNum(3);
    BigNum b=BigNum(10);

    cout<<a<<endl;
    cout<<b<<endl;
    try{
        BigNum c=a%b;
        cout<<c;
    }
    catch (int e){
        cout<<"EROARE\n";
    }

    /*VectorDyn<int> v;
    v.push(10);
    v.push(213);
    v.setPos(5,999);
    for(int i=1;i<=v.getSize();i++){
        cout<<v[i]<<" ";
    }*/

    //BigNum a=BigNum("0");
    //BigNum b=BigNum("0");
    //BigNum c;
    //c=a*b;
    //cout<<c;

    /*BigNum c=a-b;
    c.printNumber();*/

    return 0;
}
