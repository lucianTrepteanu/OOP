//#include "VectorDyn.cpp"

template <class T>
class Iterator{
public:
    virtual void begin()=0;
    virtual void getNext()=0;
    virtual bool isDone()const=0;
    virtual T currentItem()const=0;
protected:
    //Iterator();
};

template <class T>
class VectorIterator:public Iterator<T>{
public:
    VectorIterator(const VectorDyn<T>*vec);
    virtual void begin();
    virtual void getNext();
    virtual bool isDone()const;
    virtual T currentItem()const;
private:
    const VectorDyn<T>*_vec;
    int currIdx;
};

template <class T>
VectorIterator<T>::VectorIterator(const VectorDyn<T>*vec):_vec(vec),currIdx(1){}

template <class T>
void VectorIterator<T>::begin(){
    currIdx=1;
}

template <class T>
void VectorIterator<T>::getNext(){
    currIdx++;
}

template <class T>
bool VectorIterator<T>::isDone()const{
    return currIdx>_vec->getSize();
}

template <class T>
T VectorIterator<T>::currentItem()const{
    if(isDone()){
        throw -1;
    }
    return (*_vec)[currIdx];
}