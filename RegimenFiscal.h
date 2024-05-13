#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class RegimenFiscal
{
public:
	RegimenFiscal(int ID, int code, string Name);
	~RegimenFiscal();

	void setID(int ID);
	int getID();
	void setCode(int code);
	int getCode();
	void setName(string Name);
	string getName();

private:
	int _ID;
	int _code;
	string _Name;
};

