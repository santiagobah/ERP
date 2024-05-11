#pragma once
#include <iostream>
#include <string>

using namespace std;

class Clientes
{
public:
	Clientes();
	~Clientes();

private:
    int id;
    string name;
    string RFC;
    int fiscal_regimen_id; // esto podría ser un arreglo que guarde lo de la estructura
    string address;
    string city;
    string state;
    string zip_code;
};
