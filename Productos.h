#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


struct product{
    int id;
    string UPC;
    string name;
    int id_presentation;
    float price;
    float cost;
    bool has_iva;
    int stock;
};

class Productos
{
public:
	Productos();
	~Productos();
    
    void Menu_Principal();
    void Agregar_Productos();
    void Editar_Productos();
    void Ver_Productos();
    void Eliminar_Productos();
    void Decision_IVA();
    void Assign_ID();

private:
    vector <product> _productos;
};
