#include <iostream>

const int ADD_SIZE=100;

template <class T>
class VectorDyn{
public:
    int cap;
    int sz;
    T *v;
public:
    VectorDyn();
    VectorDyn(const VectorDyn<T>&v);
    virtual ~VectorDyn();
    VectorDyn(T* ptr, int nrElem);

    VectorDyn<T>&operator=(const VectorDyn<T>&alt);

    void setSize(int newSize);
    int getSize()const;

    void push(T value);
    void Clear();
    void setPos(int pos, T value);
    void shrinkTo(int x);

    T operator [](int idx)const;
    T&operator [](int idx);
};

template <class T>
VectorDyn<T>::VectorDyn(){
    cap=2;
    sz=0;
    v=new T[2];
    //v[0]=v[1]=0;
}

template <class T>
VectorDyn<T>::VectorDyn(const VectorDyn<T>&alt){
    sz=alt.sz;
    cap=alt.cap;
    
    delete[] v;
    v=new T[cap];
    for(int i=0;i<=sz;i++){
        v[i]=alt.v[i];
    }
}

template <class T>
VectorDyn<T>::~VectorDyn(){
    cap=0;
    sz=0;
    delete[] v;
}

template <class T>
VectorDyn<T>::VectorDyn(T *ptr, int nrElem){
    sz=nrElem;
    cap=nrElem+1;
    v=new T[cap];

    for(int i=1;i<=nrElem;i++){
        v[i]=ptr[i-1];
    }
}

template <class T>
VectorDyn<T>&VectorDyn<T>::operator=(const VectorDyn<T>&alt){
    if(this==&alt){
        return (*this);
    }

    sz=alt.sz;
    cap=alt.cap;

    delete[]v;
    v=new T[cap];
    for(int i=1;i<=sz;i++){
        v[i]=alt.v[i];
    }

    return (*this);
}

template <class T>
int VectorDyn<T>::getSize()const{
    return sz;
}

template <class T>
void VectorDyn<T>::setSize(int value){
    sz=value;
}

template <class T>
void VectorDyn<T>::push(T value){
    if(sz+1==cap){
        T *v2=new T[cap+ADD_SIZE];
        for(int i=0;i<cap;i++){
            v2[i]=v[i];
        }

        delete[]v;
        cap=cap+ADD_SIZE;
        v=v2;
    }

    v[++sz]=value;
}

template <class T>
void VectorDyn<T>::Clear(){
    delete[]v;
    sz=0;
    cap=2;
    v=new T[cap];
    //v[0]=v[1]=0;
}

template <class T>
void VectorDyn<T>::shrinkTo(int x){
    T *v2=new T[x+1];
    for(int i=1;i<=x;i++){
        v2[i]=0;
    }

    for(int i=1;i<=x && i<=sz;i++){
        v2[i]=v[i];
    }

    delete []v;
    v=v2;
    sz=x;
    cap=x+1;
}

template <class T>
void VectorDyn<T>::setPos(int pos,T value){
    if(pos<cap){
        v[pos]=value;
        if(sz<pos){
            sz=pos;
        }
    } else {
        T *v2=new T[pos+ADD_SIZE];
        for(int i=0;i<pos+ADD_SIZE;i++){
            v2[i]=0;
        }

        for(int i=0;i<=cap;i++){
            v2[i]=v[i];
        }

        delete[]v;
        v=v2;
        cap=pos+ADD_SIZE;
        sz=pos;
    }
}

template <class T>
T VectorDyn<T>::operator[](int idx)const{
    if(idx>sz){
        return 0;
    }
    return v[idx];
}

template <class T>
T& VectorDyn<T>::operator[](int idx){
    if(idx>=cap){
        T *v2=new T[idx+ADD_SIZE];
        for(int i=0;i<=cap;i++){
            v2[i]=v[i];
        }
        for(int i=cap+1;i<idx+ADD_SIZE;i++){
            v2[i]=0;
        }

        delete []v;
        v=v2;
        cap=idx+ADD_SIZE;
        sz=idx;
    }

    if(idx>=sz){
        sz=idx;
    }

    return v[idx];
}