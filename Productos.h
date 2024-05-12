#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Productos
{
public:
	Productos(int id, string UPC, string name, int id_p, float price, float cost, bool has_iva, int stock);
	~Productos();
    
    void Menu_Principal();
    void Agregar_Productos();
    void Editar_Productos();
    void Ver_Productos();
    void Eliminar_Productos();
    void Decision_IVA();

    
    void set_id(int id);
    void set_UPC(string UPC);
    void set_name(string name);
    void set_id_p(int id_p);
    void set_price(float price);
    void set_cost(float cost);
    void set_h_iva(bool has_iva);
    void set_stock(int stock);
    
    int get_id();
    string get_UPC();
    string get_name();
    int get_id_p();
    float get_price();
    float get_cost();
    int get_iva();
    int get_stock();
    
private:
    int _id;
    string _UPC;
    string _name;
    int _id_presentation;
    float _price;
    float _cost;
    bool _has_iva;
    int _stock;
};
