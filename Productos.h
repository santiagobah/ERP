#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Productos
{
public:
	Productos(int id_unique, string UPC, string name, int id_presentation, float price, float cost, bool has_iva, int stock);
	~Productos();
    
    void set_id(int id_unique);
    void set_UPC(string UPC);
    void set_name(string name);
    void set_id_presentation(int id_presentation);
    void set_price(float price);
    void set_cost(float cost);
    void set_has_iva(bool has_iva);
    void set_stock(int stock);
    
    int get_id();
    string get_UPC();
    string get_name();
    int get_id_presentation();
    float get_price();
    float get_cost();
    bool get_has_iva();
    int get_stock();
    
private:
    int _id_unique;
    string _UPC;
    string _name;
    int _id_presentation;
    float _price;
    float _cost;
    bool _has_iva;
    int _stock;
};
