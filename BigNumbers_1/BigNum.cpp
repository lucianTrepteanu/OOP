using namespace std;

class BigNum{
private:
    int sign;
    VectorDyn<int>digits;
public:
    BigNum(){sign=1;} //apeleaza constructorul de vector 
    BigNum(const int &val){
        digits.Clear();
        sign=1;
        int aux=val;
        if(aux<0){
            sign=-1;
            aux=-aux;
        }

        do{
            digits.push(aux%10);
            aux/=10;
        }while(aux);
    }
    BigNum(const BigNum&alt){
        sign=alt.sign;
        digits=alt.digits; //apelez copierea din VectorDyn
    }
    ~BigNum(){}

    BigNum &operator=(BigNum alt);
    bool operator==(const BigNum &alt);
    bool operator!=(const BigNum &alt);
    bool operator<(const BigNum &alt);

    friend bool cmpPositive(const BigNum &a,const BigNum &b);

    friend istream &operator >>(istream &in,BigNum &x);
    friend ostream &operator <<(ostream &out,const BigNum &x);

    friend BigNum addPositive(BigNum a,BigNum b);
    friend BigNum subPositive(BigNum a,BigNum b);

    BigNum operator +(const BigNum &alt);
    BigNum operator -(const BigNum &alt);
    BigNum operator *(const BigNum &alt);
    BigNum operator /(BigNum const &alt);
    BigNum operator %(BigNum &alt);

    friend BigNum maxAbs(const BigNum &a,const BigNum &b);

    friend BigNum getSqrt(BigNum a);

    friend class BigNumArray;
};

BigNum& BigNum:: operator =(BigNum alt){
    sign=alt.sign;
    digits=alt.digits;
    return (*this);
}

bool cmpPositive(const BigNum &a,const BigNum &b){
    int idx=a.digits.getSize();
    if(a.digits.getSize()<b.digits.getSize()){
        return true;
    } else if(a.digits.getSize()>b.digits.getSize()){
        return false;
    }
    while(idx>0 && a.digits[idx]==b.digits[idx]){
        idx--;
    }

    if(a.digits[idx]<b.digits[idx]){
        return true;
    }
    return false;
}

bool BigNum::operator==(const BigNum &alt){
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

bool BigNum::operator !=(const BigNum &alt){
    if((*this)==alt){
        return false;
    }
    return true;
}

bool BigNum::operator <(const BigNum &alt){
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

ostream &operator <<(ostream &out,const BigNum &x){
    if(x.sign==-1){
        out<<'-';
    }
    for(int i=x.digits.getSize();i>0;i--){
        out<<x.digits[i];
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
        if(!(ch>='0' && ch<='9')){
            break;
        }
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

    return res;
}

BigNum maxAbs(const BigNum &a,const BigNum &b){
    BigNum auxA=a;
    BigNum auxB=b;

    auxA.sign=1;
    auxB.sign=1;

    if(auxA<auxB){
        return b;
    } else {
        return a;
    }
}

BigNum BigNum::operator+(const BigNum &alt){
    BigNum res;
    BigNum auxAlt=alt;
    if(sign==1 && alt.sign==1){
        res=addPositive((*this),alt);
    } else if(sign==1 && alt.sign==-1){
        BigNum aux=alt;
        aux.sign=-aux.sign;
        res=(*this)-aux;
    } else if(sign==-1 && alt.sign==1){
        BigNum aux=(*this);
        aux.sign=-aux.sign;
        res=auxAlt-aux;
    } else {
        BigNum aux1=(*this),aux2=alt;
        aux1.sign=-aux1.sign;
        aux2.sign=-aux2.sign;
        res=aux1+aux2;
        res.sign=-res.sign;
    }

    while(res.digits.getSize()>1 && res.digits[res.digits.getSize()]==0){
        res.digits.shrinkTo(res.digits.getSize()-1);
    }

    return res;
}

BigNum BigNum::operator-(const BigNum &alt){
    BigNum res;
    BigNum auxAlt=alt;
    if(sign==1 && alt.sign==1){
        if(auxAlt<(*this)){
            res=subPositive((*this),alt);
        } else {
            res=subPositive(alt,(*this));
            res.sign=-res.sign;
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

        if(aux2<aux1){
            res=aux1-aux2;
        } else {
            res=subPositive(aux2,aux1);
            res.sign=-res.sign;
        }

        res.sign=-res.sign;
    }

    while(res.digits.getSize()>1 && res.digits[res.digits.getSize()]==0){
        res.digits.shrinkTo(res.digits.getSize()-1);
    }

    return res;
}

BigNum BigNum::operator*(const BigNum &alt){
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

BigNum BigNum::operator/(BigNum const &alt){
    BigNum auxA=(*this);
    //auxA.sign=1;
    BigNum auxB=alt;
    auxB.sign=1;

    if(auxB==BigNum(0)){
        throw -1;
    }

    BigNum ten=BigNum(10);
    BigNum k=BigNum(0);
    BigNum rem=BigNum(0);

    k.digits.shrinkTo(auxA.digits.getSize());

    for(int i=auxA.digits.getSize();i>0;i--){
        rem=rem*ten;
        rem.digits.setPos(1,auxA.digits[i]);

        while(rem.digits.getSize()>1 && rem.digits[rem.digits.getSize()]==0){
            rem.digits.shrinkTo(rem.digits.getSize()-1);
        }

        k.digits.setPos(i,0);

        while(rem==auxB || auxB<rem){
            int pastValue=k.digits[i];
            k.digits.setPos(i,pastValue+1);
            rem=rem-auxB;
        }
    }

    while(k.digits.getSize()>1 && k.digits[k.digits.getSize()]==0){
        k.digits.shrinkTo(k.digits.getSize()-1);
    }

    k.sign=this->sign*alt.sign;
    
    return k;
}

BigNum BigNum::operator%(BigNum &alt){
    BigNum zero=BigNum(0);
    if(alt==zero){
        throw -1;
    }

    BigNum res=(*this);
    alt.sign=1;

    while(res<zero){
        res=res+alt;
    }

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

//Newton sqrt
BigNum getSqrt(BigNum a){
    if(a.sign==-1){
        throw -1;
    }

    BigNum aux=BigNum(1);
    BigNum x0=a;
    BigNum x1=x0+aux;

    x1=x1/2;

    while(x1<x0){
        x0=x1;

        aux=a/x1;
        x1=x1+aux;
        x1=x1/2;
    }
    
    /*while(x1<x0){
        x0=x1;

        BigNum aux1=a;
        BigNum aux2=x1;
        aux=aux1/aux2;
        aux1=x1;
        x1=aux1+aux;
        aux1=x1;
        aux2=BigNum(2);
        x1=aux1/aux2;
    }*/

    return x0;
}