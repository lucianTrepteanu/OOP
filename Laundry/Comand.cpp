#pragma once
#include "Cloth.cpp"
#include <iostream>
#include <vector>

using namespace std;

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