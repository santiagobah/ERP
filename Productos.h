#pragma once
#include <iostream>
#include <string>

using namespace std;

class Productos
{
public:
	Productos();
	~Productos();

private:
    int id;
    string UPC;
    string name;
    int id_presentation;
    float price;
    float cost;
    bool has_iva;
    int stock;
};