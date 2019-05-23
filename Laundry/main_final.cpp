#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <map>

using namespace std;

const double K_PANTALONI=300;
const double K_ROCHIE=400;
const double K_CAMASA=500;

ifstream f("data.in");

class Cloth{
public:
    double weight;
    bool ironing;
    bool rinse;

    int color;
    string clothType;

    vector<pair<int,int> >history; // (machine_index and time spent)

    friend istream &operator >>(istream &in, Cloth &alt);
    friend ostream &operator <<(ostream &out,Cloth &alt);

    virtual double getDetergent(){};
    virtual int getIronTime(){};
};

ostream &operator <<(ostream &out,Cloth &alt){
    out<<alt.clothType<<" "<<alt.weight<<'\n';

    return out;
}

class Pantaloni:public Cloth{
public:
    static double detergent;

    Pantaloni(){}
    double getDetergent(){
        if(color==1){
            return 2*Pantaloni::detergent;
        } else {
            return Pantaloni::detergent;
        }
    }

    int getIronTime(){
        return 90*weight;
    }
};
double Pantaloni::detergent=K_PANTALONI;

class Rochie:public Cloth{
public:
    static double detergent;

    Rochie(){}

    double getDetergent(){
        return Rochie::detergent;
    }

    int getIronTime(){
        return 0;
    }
};
double Rochie::detergent=K_ROCHIE;

class Camasa:public Cloth{
public:
    static double detergent;

    Camasa(){}

    double getDetergent(){
        return Camasa::detergent;
    }

    int getIronTime(){
        return 120*weight;
    }
};
double Camasa::detergent=K_CAMASA;

class Palton:public Cloth{
public:
    Palton(){rinse=false; ironing=false;}

    double getDetergent(){
        return 100*weight;
    }
};

class Geaca:public Cloth{
public:
    Geaca(){rinse=false; ironing=false;}

    double getDetergent(){
        return 100*weight;
    }
};

class Costum:public Cloth{
public:
    Costum(){}

    double getDetergent(){
        return 100*weight;
    }

    int getIronTime(){
        return (150+90)*weight/2;
    }
};

class Machine{
public:
    static int nrMachines; 

    double capacity;
    double currCap;
    bool isActive;
    int index;
    string machineType;

    int timeStart;
    int timeStop;
    int timeNeed;
    map<string,int> nrOfCloth;

    vector<Cloth*> clothes;

    int getTimeNeed(Cloth *cloth){}

    virtual void start(int tstart){}

    void stop(){
        currCap=0;
        clothes.clear();
        for(auto it:nrOfCloth){
            it.second=0;
        }
        isActive=false;
    }

    virtual bool canAdd(Cloth *cloth){}

    void addCloth(Cloth *cloth){
        if(!canAdd(cloth)){
            return;
        }

        double addToCap=cloth->weight;
        if(machineType=="uscat" || machineType=="calcat"){
            addToCap=1;
        }

        nrOfCloth[cloth->clothType]++;
        clothes.push_back(cloth);
        currCap+=addToCap;
    }

    Machine(){
        index=nrMachines+1;
        nrMachines++;
    }
};
int Machine::nrMachines=0;

class WashMachine:public Machine{
public:
    WashMachine(double cap){
        capacity=cap;
        currCap=0;
        isActive=false;
    }

    bool canAdd(Cloth *cloth){
        if(cloth->clothType=="costum"){
            for(auto it:nrOfCloth){
                if(it.first!="costum" && it.second>0){
                    return false;
                }
            }
        }
        for(auto it:clothes){
            if(it->color!=cloth->color){
                return false;
            }
        }

        return true;
    }

    int getTimeNeed(Cloth *cloth){
        return timeNeed;
    }

    void start(int tstart){
        isActive=true;
        timeStart=tstart;
        for(auto it:clothes){
            //cout<<this->getTimeNeed(it)<<'\n';
            it->history.push_back(make_pair(index,this->getTimeNeed(it)));
        }
    }
};

class RinseMachine:public Machine{
public:
    RinseMachine(double cap){
        capacity=cap;
        currCap=0;
        isActive=false;
    }

    bool canAdd(Cloth *cloth){
        if(cloth->clothType=="palton" || cloth->clothType=="geaca"){
            return false;
        }

        return true;
    }

    int getTimeNeed(Cloth *cloth){
        return timeNeed;
    }

    void start(int tstart){
        isActive=true;
        timeStart=tstart;
        for(auto it:clothes){
            //cout<<this->getTimeNeed(it)<<'\n';
            it->history.push_back(make_pair(index,this->getTimeNeed(it)));
        }
    }
};

class DryMachine:public Machine{
public:
    DryMachine(int cap){
        capacity=cap;
        currCap=0;
        isActive=false;
    }

    bool canAdd(Cloth *cloth){
        return true;
    }

    int getTimeNeed(Cloth *cloth){
        return timeNeed;
    }

    void start(int tstart){
        isActive=true;
        timeStart=tstart;
        for(auto it:clothes){
            //cout<<this->getTimeNeed(it)<<'\n';
            it->history.push_back(make_pair(index,this->getTimeNeed(it)));
        }
    }
};

class IronMachine:public Machine{
public:
    IronMachine(){
        capacity=1;
        currCap=0;
        isActive=false;
    }

    bool canAdd(Cloth *cloth){
        if(cloth->clothType=="palton" || cloth->clothType=="geaca"){
            return false;
        }
        return true;
    }

    int getTimeNeed(Cloth *cloth){
        if(cloth->clothType=="pant"){
            return cloth->getIronTime();
        } else if(cloth->clothType=="camasa"){
            return cloth->getIronTime();
        } else if(cloth->clothType=="costum"){
            return cloth->getIronTime();
        } else if(cloth->clothType=="rochie"){
            return cloth->getIronTime();
        } else {
            return 0;
        }
    }

    void start(int tstart){
        isActive=true;
        timeStart=tstart;
        for(auto it:clothes){
            it->history.push_back(make_pair(index,this->getTimeNeed(it)));
        }
    }
};

class Comand{
public:
    int timeStart;
    vector<Cloth*> clothes;
    int timeStop;

    void printDetails(){
        int totalTime=0;
        double totalDetergent=0;
        for(auto cloth:clothes){
            for(int i=0;i<cloth->history.size();i++){
                //cout<<cloth->history[i].second<<" ";
                totalTime+=cloth->history[i].second;
            }
            cout<<'\n';
            totalDetergent+=cloth->getDetergent();
        }

        cout<<"Timp total: "<<totalTime<<'\n'<<"Detergent total: "<<totalDetergent<<'\n'<<'\n';
    }
};

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

class Solver{
private:
    static Solver* solverInstance;
public:
    int cntMachines;
    vector<Machine*> machines;
    vector<Comand> comands;

private:
    Solver(){
        cout<<"Introduceti nr de masini\n";
        f>>cntMachines;
        machines.resize(cntMachines);

        for(int i=0;i<cntMachines;i++){
            cout<<"Introduceti tipul masinii cu numarul "<<i<<'\n';
            string machineType;
            double timeNeed;
            f>>machineType;
            if(machineType=="spalat"){
                cout<<"Introduceti capacitatea masinii cu numarul "<<i<<'\n';
                double cap;
                f>>cap;
                machines[i]=new WashMachine(cap);
            } else if(machineType=="stors"){
                cout<<"Introduceti capacitatea masinii cu numarul "<<i<<'\n';
                double cap;
                f>>cap;
                
                machines[i]=new RinseMachine(cap);
            } else if(machineType=="uscat"){
                cout<<"Introduceti capacitatea masinii cu numarul "<<i<<'\n';
                int cap;
                f>>cap;
                
                machines[i]=new DryMachine(cap);
            } else {
                machines[i]=new IronMachine();
            }
            f>>timeNeed;
            machines[i]->machineType=machineType;
            machines[i]->timeNeed=timeNeed;
        }
    }
public:
    template<class T>
    void addQuery(Client<T> *client){
        Comand newComand;

        cout<<"Ora primirii comenzii: \n";
        f>>newComand.timeStart;

        int nrClothes;
        cout<<"Nr de haine: \n";
        f>>nrClothes;
        for(int i=0;i<nrClothes;i++){
            Cloth *toAdd;
            
            string clothType;
            cout<<"Tipul si nr hainei \n";

            f>>clothType;
            double weight;
            f>>weight;
            if(clothType=="pant"){
                toAdd=new Pantaloni();
            } else if(clothType=="rochie"){
                toAdd=new Rochie();
            } else if(clothType=="camasa"){
                toAdd=new Camasa();
            } else if(clothType=="costum"){
                toAdd=new Costum();
            }

            f>>toAdd->color;
            toAdd->weight=weight;
            toAdd->clothType=clothType;
            //cout<<typeid((*toAdd)).name()<<"\n\n";
            newComand.clothes.push_back(toAdd);
        }
        comands.push_back(newComand);
        client->addComand(newComand);
    }

    void solveQuery(){
        Comand comand=comands.back();
        comands.pop_back();

        int readyForNext=comand.timeStart;
        for(int step=0;step<4;step++){
            /*
                Step=0 spalare
                Step=1 stoarcere
                Step=2 uscare
                Step=3 calcare
            */
           string currentMachineType;
           if(step==0){
               currentMachineType="spalat";
           } else if(step==1){
               currentMachineType="stors";
           } else if(step==2){
               currentMachineType="uscat";
           } else {
               currentMachineType="calcat";
           }

           for(auto cloth:comand.clothes){
               for(int i=0;i<cntMachines;i++){
                   if(machines[i]->machineType==currentMachineType){
                       double addToCap=cloth->weight;
                       if(machines[i]->machineType=="calcat" || machines[i]->machineType=="uscat"){
                           addToCap=1;
                       }

                       if(/*machines[i]->isActive==false &&*/ machines[i]->canAdd(cloth) /*&& machines[i]->currCap+addToCap <= machines[i]->capacity*/){
                           machines[i]->addCloth(cloth);
                           break;
                       }
                   }
               }
           }

           int oldTime=readyForNext; 
           for(auto mach:machines){
               if(mach->machineType==currentMachineType && mach->clothes.size()){
                    readyForNext=max(readyForNext,oldTime+mach->getTimeNeed(mach->clothes.back()));
                    mach->start(oldTime);
               }
           }

           for(auto mach:machines){
               if(mach->isActive){
                   mach->stop();
               }
           }
        }
    }

    static Solver* getInstance(){
        if(solverInstance==nullptr){
            solverInstance=new Solver();
            return solverInstance;
        } else {
            return solverInstance;
        }
    }
};

Solver * Solver::solverInstance=nullptr;

int main(){
    Solver *solver=Solver::getInstance();
    
    Client<int> client1(Client<int>::cntClients);
    Client<int> client2(Client<int>::cntClients);
    Client<int> client3(Client<int>::cntClients);
    Client<int> client(Client<int>::cntClients);
    
    
    Client<string> namedClient("SefuVostru");
    
    solver->addQuery(&client);
    solver->addQuery(&client);
    /*for(auto it:solver->comands){
        for(auto it2:it.clothes){
            cout<<*it2<<" ";
        }
        cout<<'\n';
    }
    cout<<"\n\n";*/
    
    solver->solveQuery();
    solver->solveQuery();
    
    client.printHistory();
    /*for(auto comm:solver.comands){
        for(auto cloth:comm.clothes){
            for(auto it:cloth->history){
                cout<<cloth->clothType<<" "<<it.first<<" "<<it.second<<'\n';
            }
            cout<<'\n';
        }
    }*/
    //solver->comands.back().printDetails();

    return 0;
}