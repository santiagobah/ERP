#include "ProductosVendidos.h"

ProductosVendidos::ProductosVendidos(int ID, int ID_Sale, int ID_Product, int Quantity, float salePricePerUnit)
{
	_ID = ID;
	_ID_Sale = ID_Sale;
	_ID_Product = ID_Product;
	_Quantity = Quantity;
	_salePricePerUnit = salePricePerUnit;
}

ProductosVendidos::~ProductosVendidos()
{
}

void ProductosVendidos::setID(int ID)
{
	_ID = ID;
}

int ProductosVendidos::getID()
{
	return _ID;
}

void ProductosVendidos::setID_Sale(int ID_Sale)
{
	_ID_Sale = ID_Sale;
}

int ProductosVendidos::getID_Sale()
{
	return _ID_Sale;
}

void ProductosVendidos::setID_Product(int ID_Product)
{
	_ID_Product = ID_Product;
}

int ProductosVendidos::getID_Product()
{
	return _ID_Product;
}

void ProductosVendidos::setQuantity(int Quantity)
{
	_Quantity = Quantity;
}

int ProductosVendidos::getQuantity()
{
	return _Quantity;
}

void ProductosVendidos::setSalePricePerUnit(float salePricePerUnit)
{
	_salePricePerUnit = salePricePerUnit;
}

float ProductosVendidos::getSalePricePerUnit()
{
	return _salePricePerUnit;
}