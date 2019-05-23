#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "Machine.cpp"
#include "Comand.cpp"
#include "Client.cpp"
using namespace std;

class Solver{
private:
    static Solver* solverInstance;
public:
    int cntMachines;
    vector<Machine*> machines;
    vector<Comand> comands;

private:
    Solver(){
        f>>cntMachines;
        machines.resize(cntMachines);

        for(int i=0;i<cntMachines;i++){
            string machineType;
            double timeNeed;
            f>>machineType;
            if(machineType=="spalat"){
                double cap;
                f>>cap;
                machines[i]=new WashMachine(cap);
            } else if(machineType=="stors"){
                double cap;
                f>>cap;
                
                machines[i]=new RinseMachine(cap);
            } else if(machineType=="uscat"){
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

        f>>newComand.timeStart;

        int nrClothes;
        f>>nrClothes;
        for(int i=0;i<nrClothes;i++){
            Cloth *toAdd;
            
            string clothType;
        
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
            } else if(clothType=="palton"){
                toAdd=new Palton();
            } else if(clothType=="geaca"){
                toAdd=new Geaca();
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