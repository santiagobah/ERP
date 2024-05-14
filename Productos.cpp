#include "Productos.h"

Productos::Productos(int id_unique, string UPC, string name, int id_presentation, float price, float cost, bool has_iva, int stock){
}

Productos::~Productos(){
}

void Productos::set_id(int id_unique){
    _id_unique = id_unique;
}
int Productos::get_id(){
    return _id_unique;
}
void Productos::set_UPC(string UPC){
    _UPC = UPC;
}
string Productos::get_UPC(){
    return _UPC;
}
void Productos::set_name(string name){
    _name = name;
}
string Productos::get_name(){
    return _name;
}
void Productos::set_id_presentation(int id_presentation){
    _id_presentation = id_presentation;
}
int Productos::get_id_presentation(){
    return _id_presentation;
}
void Productos::set_price(float price){
    _price = price;
}
float Productos::get_price(){
    return _price;
}
void Productos::set_cost(float cost){
    _cost = cost;
}
float Productos::get_cost(){
    return _cost;
}
void Productos::set_has_iva(bool has_iva){
    _has_iva = has_iva;
}
bool Productos::get_has_iva(){
    return _has_iva;
}
void Productos::set_stock(int stock){
    _stock = stock;
}
int Productos::get_stock(){
    return _stock;
}

