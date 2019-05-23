#pragma once

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