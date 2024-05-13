#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Usuarios.h"
#include "Clientes.h"
#include "Productos.h"
#include "Ventas.h"
#include "ProductosVendidos.h"

using namespace std;

// SistemaDeVentas
class SistemaDeVentas
{
public:
	SistemaDeVentas();
	~SistemaDeVentas();

	void MenuInicial();

private:
	void IniciarSesion();
	void ValidacionDeCredenciales();
	vector<Usuarios> LeerUsuarios();
	/*vector<Clientes> LeerClientes();
	vector<Productos> LeerProductos();
	vector<Ventas> LeerVentas();
	vector<ProductosVendidos> LeerProductosVendidos();

	void GuardarUsuarios(vector<Usuarios> usuarios);
	void GuardarClientes(vector<Clientes> clientes);
	void GuardarProductos(vector<Productos> productos);
	void GuardarVentas(vector<Ventas> ventas);
	void GuardarProductosVendidos(vector<ProductosVendidos> productosVendidos);*/

	void MenuPrincipal();
	/*void MenuAdministrador();
	void MenuVendedor();
	void MenuRH();
	void MenuAlmacen();

	void GestionDeUsuarios();
		void AgregarUsuario();
		void EditarUsuario();
		void EliminarUsuario();
	void GestionDeClientes();
		void AgregarCliente();
		void EditarCliente();
		void VerClientes();
		void EliminarCliente();
	void GestionDeProductos();
		void AgregarProducto();
		void EditarProducto();
		void VerProductos();
		void EliminarProducto();
	void GestionDeVentas();
		void AgregarVenta();
		void VerVentas();
	void GestionDeInformes();
		void InformeDeVentas();
		void InformeDeInventarios();
		void InfromesDeActividadDeUsuarios();*/



	DateTime ConvertirFechaADateTime();
	DateTimeV ConvertirFechaADateTimeV();
	void PausaConEnter();
	void LimpiarPantalla();


	vector<Ventas> ventas;
	vector<ProductosVendidos> productosVendidos;
	vector<Usuarios> usuarios;
	vector<Productos> productos;
	vector<Clientes> clientes;
	vector<Presentacion> presentaciones;
	vector<RegimenFiscal> regimenesFiscales;
	string rutaUsuarios;
	string rutaClientes;
	string rutaProductos;
	string rutaVentas;
	string rutaProductosVendidos;
	string rutaPresentaciones;
	string rutaRegimenesFiscales;


};