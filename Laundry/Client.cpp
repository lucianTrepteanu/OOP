#pragma once

template <class T>
class Client{
public:
    static int cntClients;
    T clientId;
    vector<Comand> comands;

    Client(T name){
        clientId=name;
        cntClients++;
    }

    void addComand(Comand comand){
        comands.push_back(comand);
    }

    void printHistory(){
        cout<<"Istoricul clientului "<<clientId<<": \n";
        for(auto comand:comands){
            cout<<comand.timeStart<<' ';
            comand.printDetails();
        }
    }
};

template<class T>
int Client<T>::cntClients=0;