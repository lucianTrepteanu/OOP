//#include "PositiveBigNum.cpp"

class BigNum:public PositiveBigNum{
public:
    char sign;
    BigNum():PositiveBigNum(){sign=1;}
    BigNum(char pSign):PositiveBigNum(){sign=pSign;}
    BigNum(const int &val):PositiveBigNum(abs(val)){
        if(val<0){
            sign=-1;
        } else {
            sign=1;
        }
    }

    /*BigNum(const BigNum &alt):PositiveBigNum(alt){
        sign=alt.sign;
    }*/
    BigNum(const BigNum &alt){
        sign=alt.sign;
        digits=alt.digits;
    }

    ~BigNum(){};

    BigNum &operator =(const BigNum &alt);
    //BigNum &operator =(PositiveBigNum alt);

    bool operator==(const BigNum &alt);
    bool operator!=(const BigNum &alt);
    bool operator<(const BigNum &alt);

    friend istream &operator >>(istream &in,BigNum &x);
    friend ostream &operator <<(ostream &out,const BigNum &x);

    BigNum operator +(const BigNum &alt);
    BigNum operator -(const BigNum &alt);
    BigNum operator *(const BigNum &alt);
    BigNum operator /(const BigNum &alt);
    BigNum operator %(const BigNum &alt);

    PositiveBigNum getSqrt();
};

void swap(BigNum &a,BigNum &b){
    BigNum aux=a;
    a=b;
    b=aux;
}

BigNum &BigNum::operator =(const BigNum &alt){
    digits=alt.digits;
    /*for(int i=0;i<=alt.digits.getSize();i++){
		digits[i]=alt.digits[i];
	}*/
	sign=alt.sign;
	return (*this);
}

/*BigNum &BigNum::operator =(PositiveBigNum alt){
    sign=1;
    digits=alt.digits;
    return (*this);
}*/

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

bool BigNum::operator<(const BigNum &alt){
    PositiveBigNum positiveA=(*this);
    PositiveBigNum positiveB=alt;

    if(sign==1 && alt.sign==1){
        return positiveA<positiveB;
    } else if(sign==1 && alt.sign==-1){
        return false;
    } else if(sign==-1 && alt.sign==1){
        return true;
    } else {
        return positiveB<positiveA;
    }
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
    while(st<dr){
        int a=x.digits[st];
        x.digits[st]=x.digits[dr];
        x.digits[dr]=a;
        st++;dr--;
    }

    return in;
}

ostream &operator << (ostream &out,const BigNum &x){
    if(x.sign==-1){
        out<<'-';
    }
    for(int i=x.digits.getSize();i>0;i--){
        out<<x.digits[i];
    }
    return out;
}

BigNum BigNum::operator +(const BigNum &alt){
    BigNum res;
    PositiveBigNum posRes;
    BigNum auxAlt=alt;
	
	cout<<alt<<endl;

    PositiveBigNum positiveA=(*this);
    PositiveBigNum positiveB=alt;

    if(sign==1 && alt.sign==1){
        PositiveBigNum posRes=positiveA+positiveB;
        res.digits=posRes.digits;
        res.sign=1;
    } else if(sign==1 && alt.sign==-1){
        posRes=positiveA-positiveB;
        res.digits=posRes.digits;
    } else if(sign==-1 && alt.sign==1){
        posRes=positiveB-positiveA;
        res.digits=posRes.digits;
    } else {
        posRes=positiveA-positiveB;
        res.digits=posRes.digits;
        res.sign=-res.sign;
    }

    while(res.digits.getSize()>1 && res.digits[res.digits.getSize()]==0){
        res.digits.shrinkTo(res.digits.getSize()-1);
    }

    return res;
}

BigNum BigNum::operator -(const BigNum &alt){
    BigNum res;
    PositiveBigNum posRes;
    
    PositiveBigNum positiveA;
    PositiveBigNum positiveB;

    positiveA.digits=(*this).digits;
    positiveB.digits=alt.digits;

    if(sign==1 && alt.sign==1){
        if(positiveB<positiveA){
            posRes=positiveA-positiveB;
            res.digits=posRes.digits;
        } else {
            posRes=positiveB-positiveA;
            res.digits=posRes.digits;
            res.sign=-res.sign;
        }
    } else if(sign==1 && alt.sign==-1){
        posRes=positiveA+positiveB;
        res.digits=posRes.digits;
    } else {
        if(positiveB<positiveA){
            posRes=positiveA-positiveB;
            res.digits=posRes.digits;
        } else {
            posRes=positiveB-positiveA;
            res.digits=posRes.digits;
            res.sign=-res.sign;
        }
        
        res.sign=-res.sign;
    }

    while(res.digits.getSize()>1 && res.digits[res.digits.getSize()]==0){
        res.digits.shrinkTo(res.digits.getSize()-1);
    }

    return res;
}

BigNum BigNum::operator *(const BigNum &alt){
	BigNum res;
	res.digits.shrinkTo(digits.getSize()+alt.digits.getSize()+1);
	
	int t;
	res.sign=(*this).sign*alt.sign;
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

BigNum BigNum::operator/(const BigNum &alt){
	PositiveBigNum positiveA;
	PositiveBigNum positiveB;
	
	positiveA.digits=(*this).digits;
	positiveB.digits=alt.digits;
	
	if(positiveB==BigNum(0)){
		throw -1;
	}
	
	PositiveBigNum res=positiveA/positiveB;
	
	BigNum k;
	k.digits=res.digits;
	k.sign=this->sign*alt.sign;
	
	return k;
}

PositiveBigNum BigNum::getSqrt(){
    if(this->sign==-1){
        throw -1;
    }
    
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