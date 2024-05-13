//Entidades
	//Usuarios.csv
		// Usuarios clase
		//id, nombre,apellido,usuario,contraseña,rol
		//1,Daniel,Alvarez,dalvarez,12345678,valor_enum
		//rol: 1-Administrador, 2-Ventas, 3-Administrador, 4-RH
		// Amdmin tiene acceso a todo
		// Ventas solo a ventas (Productos Vendidos, clientes)
		// Almacen solo a almacen (Productos)
		// RH solo a RH (Usuarios)
	//Clientes.csv
		// Estado: vector<String>
		// municipio
		// Regimen fiscal: (#, "") <map>int, string
		// Clientes clase
		// 1, Publico general,
		//id, razon_social, rfc, direccion, estado, munoicipio, cp, regimen_fiscal
		// 1,Alvarez,ALVD123456,Av. Siempre Viva 123,CDMX,CDMX,12345,General
	//Productos.csv
		// Productos clase
		//id, upc, nombre, presentacion, stock, costo, precio
	//Ventas.csv
		// Ventas clase
		//id, id_cliente, #productos, subtotal, iva, total
	//Productos_vendidos.csv
		//id, id_venta, id_producto, cantidad_vendida
//Los ids de todos los productos, clientes y usuarios son secuenciales

#include <iostream>
#include "SistemaDeVentas.h"



using namespace std;

int main() 
{
	SistemaDeVentas	sistemaDeVentas;
	sistemaDeVentas.MenuInicial();

	return 0;
}


//struct Usuario
//{
//	int id;
//	std::string nombre;
//	std::string apellido;
//	std::string usuario;
//	std::string contrasena;
//	int rol;
//};
	//int a = 10;
	//cout << "a = " << a << endl;
	//cout << "dir a =" << &a << endl;

	//int* ptr = &a;
	//cout << "ptr = " << ptr << endl;
	//cout << "dir ptr = " << &ptr << endl;

	//*ptr = 20;
	//cout << "a = " << a << endl;


	//int x = 10;
	//int y = 20;
	//intercambiar(&x, &y);

	//int capacity;
	//int* numbers = new int(capacity);
	//int entries = 0;

	//while (true)
	//{
	//	cout << "numers: " << endl;
	//	cin >> numbers[entries];
	//	if (cin.fail()) {
	//		break;
	//	}
	//	entries++;
	//	if (entries == capacity)
	//	{
	//		int* temp = new int[capacity * 2];
	//		for (int i = 0; i < i < capacity; i++)
	//		{
	//			temp[i] = numbers[i];
	//		}
	//		delete numbers;
	//		numbers = temp;
	//		capacity *= 2;
	//	}

	//}

	////Lectura de usuarios
	//vector<Usuario> usuarios;
	///*for (int i = 0; i < 5; i++)
	//{
	//	Usuario aux;
	//	cout << "Introduce el nombre del nombre: ";
	//	cin >> aux.nombre;
	//	cout << "Introduce el apellido del usuario: ";
	//	cin >> aux.apellido;
	//	cout << "Tu usuario es: " << aux.nombre[0] << aux.apellido << endl;
	//	aux.usuario = aux.nombre[0] + aux.apellido;
	//	cout << "Introduce la contrasena: ";
	//	cin >> aux.contrasena;
	//	cout << "Introduce el rol: ";
	//	cin >> aux.rol;
	//	usuarios.push_back(aux);
	//}*/
	////Escritura de usuarios
	///*ofstream archivo_usuarios("Usuarios.csv");
	//for (int i = 0; i < usuarios.size(); i++)
	//{
	//	archivo_usuarios << i + 1 << "," << usuarios[i].nombre << "," << usuarios[i].apellido << "," << usuarios[i].usuario << "," << usuarios[i].contrasena << "," << usuarios[i].rol << endl;
	//}
	//archivo_usuarios.close();*/

	////Lectura de documento de usuarios
	//ifstream archivo_usuarios_lectura("Usuarios.csv");
	//string linea;
	//while (getline(archivo_usuarios_lectura, linea))
	//{
	//	cout << linea << endl;
	//}
	//archivo_usuarios_lectura.close();
	//for (int i = 0; i < usuarios.size(); i++)
	//{
	//	cout << usuarios[i].id << " " << usuarios[i].nombre << " " << usuarios[i].apellido << " " << usuarios[i].usuario << " " << usuarios[i].contrasena << " " << usuarios[i].rol << endl;
	//}
	//return 0;


//void intercambiar(int* a, int* b) {
//	int temp = *a;
//	*a = *b;
//	*b = temp;
//	cout << "a: " << *a << endl;
//	cout << "b: " << *b << endl;
//}
