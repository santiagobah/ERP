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
#include "Presentacion.h"

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
    
    //Productos:
    void GestionDeProductos();
    void AgregarProducto();
    void EditarProducto();
    void VerProductos();
    void EliminarProducto();
    vector<Productos> productos;
    string rutaProductos;
    
    void MenuPrincipal();
    void MenuAdministrador();
    void MenuVendedor();
    void MenuRH();
    void MenuAlmacen();
    
    //Usuarios:
    void GestionDeUsuarios();
    void AgregarUsuario();
    void EditarUsuario();
    void EliminarUsuario();
    vector<Usuarios> usuarios;
    
    //Clientes:
    void GestionDeClientes();
    void AgregarCliente();
    void EditarCliente();
    void VerClientes();
    void EliminarCliente();
    vector<Clientes> clientes;
    
    //Ventas:
    void GestionDeVentas();
    void AgregarVenta();
    void VerVentas();
    vector<Ventas> ventas;
    
    //Informes:
    void GestionDeInformes();
    void InformeDeVentas();
    void InformeDeInventarios();
    void InfromesDeActividadDeUsuarios();

	DateTime ConvertirFechaADateTime();
	DateTimeV ConvertirFechaADateTimeV();
	void PausaConEnter();
	void LimpiarPantalla();

    /*vector<Clientes> LeerClientes();
     vector<Productos> LeerProductos();
     vector<Ventas> LeerVentas();
     vector<ProductosVendidos> LeerProductosVendidos();
     
     void GuardarUsuarios(vector<Usuarios> usuarios);
     void GuardarClientes(vector<Clientes> clientes);
     void GuardarProductos(vector<Productos> productos);
     void GuardarVentas(vector<Ventas> ventas);
     void GuardarProductosVendidos(vector<ProductosVendidos> productosVendidos);*/

	vector<ProductosVendidos> productosVendidos;
	vector<Presentacion> presentaciones;
	vector<RegimenFiscal> regimenesFiscales;
	string rutaUsuarios;
	string rutaClientes;
	string rutaVentas;
	string rutaProductosVendidos;
	string rutaPresentaciones;
	string rutaRegimenesFiscales;


};
