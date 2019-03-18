using namespace std;

class BigNumArray{
private:
    VectorDyn<BigNum> v;
public:
    BigNumArray(){
        v.shrinkTo(2);
    }
    BigNumArray(int sz){
        v.shrinkTo(sz);
    }

    int getSize();
    BigNum operator[](int idx);
    void setPos(int pos,BigNum val);

    friend istream &operator>>(istream &in,BigNumArray &arr);
    friend ostream &operator<<(ostream &out,BigNumArray arr);

    bool operator==(const BigNumArray &alt);
    bool operator!=(const BigNumArray &alt);
    bool operator<(const BigNumArray &alt);

    BigNum operator *(BigNumArray alt);

    BigNum maxAbsArray();
};

int BigNumArray::getSize(){
    return v.getSize();
}

BigNum BigNumArray::operator[](int idx){
    return v[idx];
} 

void BigNumArray::setPos(int pos,BigNum val){
    v.setPos(pos,val);
}

bool BigNumArray::operator==(const BigNumArray &alt){
    BigNumArray aux=alt;
    if((*this).getSize()!=aux.getSize()){
        return false;
    }

    int idx=0;
    while(idx<=(*this).getSize() && (*this)[idx]==aux[idx]){
        idx++;
    }

    if(idx>(*this).getSize()){
        return true;
    }
    return false;
}

bool BigNumArray::operator!=(const BigNumArray &alt){
    if((*this)==alt){
        return false;
    }
    return true;
}

bool BigNumArray::operator<(const BigNumArray &alt){
    BigNumArray aux=alt;
    int idx=0;
    while(idx<=(*this).getSize() && idx<=aux.getSize() && (*this)[idx]==aux[idx]){
        idx++;
    }

    if((*this)[idx]<aux[idx]){
        return true;
    }
    return false;
}

istream &operator >>(istream &in,BigNumArray &arr){
    for(int i=0;i<arr.getSize();i++){
        BigNum aux;
        in>>aux;
        arr.setPos(i,aux);
    }
    return in;
}

ostream &operator<<(ostream &out,BigNumArray arr){
    for(int i=0;i<arr.getSize();i++){
        out<<arr[i]<<" ";
    }
    return out;
} 

BigNum BigNumArray::operator *(BigNumArray alt){
    BigNum res=BigNum(0);
    for(int i=0;i<(*this).getSize();i++){
        res=res+(*this)[i]*alt[i];
    }

    return res;
}

BigNum BigNumArray::maxAbsArray(){
    BigNum res=BigNum(0);
    for(int i=0;i<(*this).getSize();i++){
        BigNum newRes=maxAbs(res,(*this)[i]);
        res=newRes;
    }

    res.sign=1;
    return res;
}