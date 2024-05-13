#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Presentacion.h"

using namespace std;

class Productos
{
public:
	Productos(int ID, int UPC, string Name, int ID_Presentation, float Price, float Cost, bool hasIVA, int stock);
	~Productos();

	void setID(int ID);
	int getID();
	void setUPC(int UPC);
	int getUPC();
	void setName(string Name);
	string getName();
	void setID_Presentation(int ID_Presentation);
	int getID_Presentation();
	void setPrice(float Price);
	float getPrice();
	void setCost(float Cost);
	float getCost();
	void setHasIVA(bool hasIVA);
	bool getHasIVA();
	void setStock(int stock);
	int getStock();

private:
	int _ID;
	int _UPC;
	string _Name;
	int _ID_Presentation;
	float _Price;
	float _Cost;
	bool _hasIVA;
	int _stock;
};
