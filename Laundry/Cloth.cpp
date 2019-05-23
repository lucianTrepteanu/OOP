#pragma once
#include <vector>
#include <iostream>
using namespace std;

const double K_PANTALONI=300;
const double K_ROCHIE=400;
const double K_CAMASA=500;

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