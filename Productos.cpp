#include "Productos.h"

Productos::Productos(int id, string UPC, string name, int id_p, float price, float cost, bool has_iva, int stock){
    _id = id;
    _UPC = UPC;
    _name = name;
    _id_presentation = id_p;
    _price = price;
    _cost = cost;
    _has_iva = has_iva;
    _stock = stock;
}

Productos::~Productos(){
}

void Productos::set_id(int id_s){
    _id = id_s;
}
void Productos::set_UPC(string UPC){
    _UPC = UPC;
}
void Productos::set_name(string name){
    _name = name;
}
void Productos::set_id_p(int id_p){
    _id = id_p;
}
void Productos::set_price(float price){
    _price = price;
}
void Productos::set_cost(float cost){
    _cost = cost;
}
void Productos::set_h_iva(bool has_iva){
    _has_iva = has_iva;
}
void Productos::set_stock(int stock){
    _stock = stock;
}

int Productos::get_id(){
    return _id;
}
string Productos::get_UPC(){
    return _UPC;
}
string Productos::get_name(){
    return _name;
}
int Productos::get_id_p(){
    return _id_presentation;
}
float Productos::get_price(){
    return _price;
}
float Productos::get_cost(){
    return _cost;
}
int Productos::get_iva(){
    return _has_iva;
}
int Productos::get_stock(){
    return _stock;
}
void Productos::Menu_Principal(){
    cout << "\nBienvenido al menú de Productos" << endl;
    int opc_men_pod = 0;
    cout <<
    "1. Add Products" <<
    "\n2. Edit Products" <<
    "\n3. See Products" << //SEE?
    "\n4. Delete Products" <<
    "\nOpción elegida: ";
    cin >> opc_men_pod;
    switch(opc_men_pod){
        case 1:
        {
            Agregar_Productos();
            break;
        }
        case 2:
        {
            Editar_Productos();
            break;
        }
        case 3:
        {
            Ver_Productos();
            break;
        }
        case 4:
        {
            Eliminar_Productos();
            break;
        }
        default:
        {
            cout << "Seleccione una opción válida" << endl;
            Menu_Principal();
            break;
        }
    }
}
void Productos::Agregar_Productos(){
    cout << "Let´s start by scanning the product barcode: " << endl;
    //cin >> escanear con pistola;
    cout << "Type the product name: ";
    cin >> _name;
    cout << "Type the ID for this presentation of " << _name << ": ";
    cin >> _id_presentation;
    cout << "Type the price of " << _name << ": ";
    cin >> _price;
    cout << "Type the cost of " << _name << ": ";
    cin >> _cost;
    Decision_IVA();
    cout << "Type the stock of " << _name << ": ";
}
void Productos::Eliminar_Productos(){
    cout << "Type or scan the product barcode: " << endl;
    //cin >> pistola
}
void Productos::Ver_Productos(){
}
void Productos::Editar_Productos(){
}
void Productos::Decision_IVA(){
    int opc_iva = 0;
    cout << _name << " has IVA? " << endl;
    cout << "(1. YES/2.NO): ";
    cin >> opc_iva;
    switch(opc_iva){
        case 1:
        {
            _has_iva = true;
            break;
        }
        case 2:
        {
            _has_iva = false;
            break;
        }
    }
}
