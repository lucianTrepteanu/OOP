//#include "VectorDyn.cpp"

using namespace std;

class PositiveBigNum{
public:
    VectorDyn<int> digits;
public:
    PositiveBigNum(){};
    PositiveBigNum(const int &val){
        digits.Clear();
        int aux=val;
        do{
            digits.push(aux%10);
            aux=aux/10;
        }while(aux);
    }

    PositiveBigNum(const PositiveBigNum&alt){
        digits=alt.digits;
    }

    ~PositiveBigNum(){};

    PositiveBigNum &operator =(const PositiveBigNum &alt);
    
    bool operator==(const PositiveBigNum &alt);
    bool operator!=(const PositiveBigNum &alt);
    bool operator <(const PositiveBigNum &alt);

    friend istream &operator >>(istream &in,PositiveBigNum &x);
    friend ostream &operator <<(ostream &out,const PositiveBigNum &x);

    virtual PositiveBigNum operator +(const PositiveBigNum &alt);
    virtual PositiveBigNum operator -(const PositiveBigNum &alt);
    virtual PositiveBigNum operator *(const PositiveBigNum &alt);
    virtual PositiveBigNum operator /(const PositiveBigNum &alt);
    virtual PositiveBigNum operator %(const PositiveBigNum &alt);

    virtual PositiveBigNum getSqrt();
};

PositiveBigNum &PositiveBigNum::operator =(const PositiveBigNum &alt){
    digits=alt.digits;
    return (*this);
}

bool PositiveBigNum::operator<(const PositiveBigNum &alt){
    int idx=(*this).digits.getSize();
    if(this->digits.getSize()<alt.digits.getSize()){
        return true;
    } else if(this->digits.getSize()>alt.digits.getSize()){
        return false;
    }

    while(idx>0 && this->digits[idx]==alt.digits[idx]){
        idx--;
    }

    if(this->digits[idx]<alt.digits[idx]){
        return true;
    }
    return false;
}

bool PositiveBigNum::operator==(const PositiveBigNum &alt){
    if(this->digits.getSize()!=alt.digits.getSize()){
        return false;
    }

    int idx=1;
    while(idx<=this->digits.getSize() && this->digits[idx]==alt.digits[idx]){
        idx++;
    }

    if(idx>this->digits.getSize()){
        return true;
    }
    return false;
}

bool PositiveBigNum::operator!=(const PositiveBigNum &alt){
    if((*this)==alt){
        return false;
    }
    return true;
}

ostream &operator <<(ostream &out,const PositiveBigNum &x){
    for(int i=x.digits.getSize();i>0;i--){
        out<<x.digits[i];
    }
    return out;
}

istream &operator>>(istream &in,PositiveBigNum &x){
    char ch;
    x.digits.Clear();

    while(!in.eof()){
        in.get(ch);
        if(!(ch>='0' && ch<='9')){
            break;
        }
        x.digits.push(ch-'0');
    }

    int st=1,dr=x.digits.getSize();
    while(st<dr){
        int a=x.digits[st];
        x.digits[st]=x.digits[dr];
        x.digits[dr]=a;
        //x.digits.setPos(st,x.digits[dr]);
        //x.digits.setPos(dr,a);
        st++;dr--;
    }

    return in;
}

PositiveBigNum PositiveBigNum::operator +(const PositiveBigNum &alt){
    PositiveBigNum res;
    res.digits.shrinkTo(max(alt.digits.getSize(),digits.getSize())+1);

    int i,t=0;
    for(i=1;i<=digits.getSize() || i<=alt.digits.getSize() || t;i++,t/=10){
        t+=digits[i]+alt.digits[i];
        res.digits[i]=t%10;
    }

    while(res.digits.getSize()>1 && res.digits[res.digits.getSize()]==0){
        res.digits.shrinkTo(res.digits.getSize()-1);
    }

    return res;
}

PositiveBigNum PositiveBigNum::operator -(const PositiveBigNum &alt){
    PositiveBigNum res=(*this);
    int i,t=0;

    for(i=1;i<=res.digits.getSize();i++){
        if(i<=alt.digits.getSize()){
            int pastValue=res.digits[i];
            res.digits[i]=pastValue-alt.digits[i]-t;
        } else {
            int pastValue=res.digits[i];
            res.digits[i]=pastValue-t;
        }

        if(res.digits[i]<0){
            t=1;
        } else {
            t=0;
        }

        int pastValue=res.digits[i];
        res.digits[i]=pastValue+10*t;
    }

    while(res.digits.getSize()>1 && res.digits[res.digits.getSize()]==0){
        res.digits.shrinkTo(res.digits.getSize()-1);
    }

    return res;
}

PositiveBigNum PositiveBigNum::operator *(const PositiveBigNum &alt){
    PositiveBigNum res;
    res.digits.shrinkTo(digits.getSize()+alt.digits.getSize()+1);

    int t=0;
    for(int i=1;i<=digits.getSize();i++){
        for(int t=0,j=1;j<=alt.digits.getSize()||t;j++,t/=10){
            int pastValue=res.digits[i+j-1];
            t+=pastValue+digits[i]*alt.digits[j];
            res.digits[i+j-1]=t%10;
        }
    }

    while(res.digits.getSize()>1 && res.digits[res.digits.getSize()]==0){
        res.digits.shrinkTo(res.digits.getSize()-1);
    }

    return res;
}

PositiveBigNum PositiveBigNum::operator /(const PositiveBigNum &alt){
    PositiveBigNum auxB=alt;

    if(auxB==PositiveBigNum(0)){
        throw -1;
    }

    PositiveBigNum ten=PositiveBigNum(10);
    PositiveBigNum k=PositiveBigNum(0);
    PositiveBigNum rem=PositiveBigNum(0);

    k.digits.shrinkTo((*this).digits.getSize());

    for(int i=(*this).digits.getSize();i>0;i--){
        rem=rem*ten;
        rem.digits[1]=(*this).digits[i];

        while(rem.digits.getSize()>1 && rem.digits[rem.digits.getSize()]==0){
            rem.digits.shrinkTo(rem.digits.getSize()-1);
        }

        k.digits[i]=0;
        
        while(rem==auxB || auxB<rem){
            int pastValue=k.digits[i];
            k.digits[i]=pastValue+1;
            rem=rem-auxB;
        }
    }

    while(k.digits.getSize()>1 && k.digits[k.digits.getSize()]==0){
        k.digits.shrinkTo(k.digits.getSize()-1);
    }

    return k;
}

PositiveBigNum PositiveBigNum::operator %(const PositiveBigNum &alt){
    PositiveBigNum auxB=alt;

    if(auxB==PositiveBigNum(0)){
        throw -1;
    }

    PositiveBigNum ten=PositiveBigNum(10);
    PositiveBigNum k=PositiveBigNum(0);
    PositiveBigNum rem=PositiveBigNum(0);

    k.digits.shrinkTo((*this).digits.getSize());

    for(int i=(*this).digits.getSize();i>0;i--){
        rem=rem*ten;
        rem.digits[1]=(*this).digits[i];

        while(rem.digits.getSize()>1 && rem.digits[rem.digits.getSize()-1]==0){
            rem.digits.shrinkTo(rem.digits.getSize()-1);
        }

        k.digits[i]=0;

        while(rem==auxB || auxB<rem){
            int pastValue=k.digits[i];
            k.digits[i]=pastValue+1;
            rem=rem-auxB;
        }
    }

    while(k.digits.getSize()>1 && k.digits[k.digits.getSize()]==0){
        k.digits.shrinkTo(k.digits.getSize()-1);
    }

    return rem;
}

PositiveBigNum PositiveBigNum::getSqrt(){
    PositiveBigNum aux=PositiveBigNum(1);
    PositiveBigNum x0=(*this);
    PositiveBigNum a(*this);
    PositiveBigNum x1=x0+aux;

    x1=x1/2;
    while(x1<x0){
        x0=x1;
        
        aux=a/x1;
        x1=x1+aux;
        x1=x1/2;
    }

    return x0;
}