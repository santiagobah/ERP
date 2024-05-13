#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class ProductosVendidos
{
public:
	ProductosVendidos(int ID, int ID_Sale,	int ID_Product, int Quantity, float salePricePerUnit);
	~ProductosVendidos();

	void setID(int ID);
	int getID();
	void setID_Sale(int ID_Sale);
	int getID_Sale();
	void setID_Product(int ID_Product);
	int getID_Product();
	void setQuantity(int Quantity);
	int getQuantity();
	void setSalePricePerUnit(float salePricePerUnit);
	float getSalePricePerUnit();
private:
	int _ID;
	int _ID_Sale;
	int _ID_Product;
	int _Quantity;
	float _salePricePerUnit;
};

