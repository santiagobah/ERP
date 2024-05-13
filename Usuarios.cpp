#include "Usuarios.h"

Usuarios::Usuarios(string name, string surname, string username, string password, string role, int id, DateTime date_joined)
{
	_name = name;
	_lastname = surname;
	_username = username;
	_password = password;
	_role = role;
	_id = id;
	_date_joined = date_joined;
}

Usuarios::~Usuarios()
{
}

void Usuarios::setId(int id)
{
	_id = id;
}

int Usuarios::getId()
{
	return _id;
}

void Usuarios::setUsername(string username)
{
	_username = username;
}

string Usuarios::getUsername()
{
	return _username;
}

void Usuarios::setPassword(string password)
{
	_password = password;
}

string Usuarios::getPassword()
{
	return _password;
}

void Usuarios::setRole(string role)
{
	_role = role;
}

string Usuarios::getRole()
{
	return _role;
}

void Usuarios::setName(string name)
{
	_name = name;
}

string Usuarios::getName()
{
	return _name;
}

void Usuarios::setLastname(string lastname) 
{
	_lastname = lastname;
}
string Usuarios::getLastname() 
{
	return _lastname;
}

void Usuarios::setDateJoined(DateTime date_joined)
{
	_date_joined = date_joined;
}

DateTime Usuarios::getDateJoined()
{
	return _date_joined;
}

string Usuarios::Encrypt(string password)
{
	//Obtiene hash por medio de los códigos ascii
	unsigned int hash = 0;
	for (int i = 0; i < password.length(); ++i) {
		hash = hash * 37 + password[i];
	}
	int hashInt = hash;
	string final = to_string(hashInt);
	return final;
}
