#pragma once
#include <iostream>
#include <string>

using namespace std;

class ProductosVendidos
{
public:
	ProductosVendidos();
	~ProductosVendidos();

private:
    int id;
    int id_sale;
    int id_product;
    int quantity;
    float sale_price_per_unit;
};