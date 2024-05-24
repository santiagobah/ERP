#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "DateTime.h"

using namespace std;

enum Roles
{
	ADMIN = 1,
	VENDEDOR = 2,
	RH = 3,
	ALMACEN = 4
};

class Usuarios
{
public:
	Usuarios(string name, string surname, string username, string password, string role, int id, DateTime date_joined);
	~Usuarios();
	
	void setId(int id);
	int getId();
	void setUsername(string username);
	string getUsername();
	void setPassword(string password);
	string getPassword();
	void setRole(string role);
	string getRole();
	int getRoleInt();
	void setName(string name);
	string getName();
	void setLastname(string lastname);
	string getLastname();
	void setDateJoined(DateTime date_joined);
	DateTime getDateJoined();

	string Encrypt(string password);

private:
    int _id;
    string _username;
    string _password;
    string _role;
    string _name;
    string _lastname;
	DateTime _date_joined;
};