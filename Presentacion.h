#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Presentacion
{
public:
	Presentacion(int ID, string Name);
	~Presentacion();

	void setID(int ID);
	int getID();
	void setName(string Name);
	string getName();
private:
	int _ID;
	string _Name;
};
