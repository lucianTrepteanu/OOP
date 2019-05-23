#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <map>
#include "Cloth.cpp"
#include "Machine.cpp"
#include "Comand.cpp"
#include "Client.cpp"

using namespace std;

ifstream f("data.in");

#include "Solver.cpp"

int main(){
    Solver *solver=Solver::getInstance();
    
    Client<int> client1(Client<int>::cntClients);
    Client<int> client2(Client<int>::cntClients);
    Client<int> client3(Client<int>::cntClients);
    Client<int> client(Client<int>::cntClients);
    
    
    Client<string> namedClient("SefuVostru");
    
    solver->addQuery(&client);
    solver->addQuery(&client);

    solver->solveQuery();
    solver->solveQuery();
    
    client.printHistory();
 
    //solver->comands.back().printDetails();

    return 0;
}