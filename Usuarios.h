#pragma once
#include <iostream>
#include <string>
#include <chrono>

using namespace std;

class Usuarios
{
public:
	Usuarios(string name, string surname, string username, string password, string role, int id);
	~Usuarios();

    void add_user();
    void gen_id(string name, string surname);

    void setId(int id);
    void setUsername(string& username);
    void setPassword(string& password);
    void setRole(string& role);
    void setName(string& name);
    void setLastname(string& lastname);
    void setShift(int shift);

    int getId();
    string getUsername();
    string getPassword();
    string getRole();
    string getName();
    string getLastname();
    int getShift();
    string encrypt(string text);

private:
    int _id;
    string _username;
    string _password;
    string _role;
    string _name;
    string _lastname;
    int _shift;
    //auto date_joined; //auto identifica solito el tipo de dato que recibirá la variable
};
