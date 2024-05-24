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

struct RegistroDeActividadUser
{
	int ID_user;
	string action;
	DateTime date;
};

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

    void MenuPrincipal();
    void MenuAdministrador();
    void MenuVendedor();
    void MenuRH();
    void MenuAlmacen();

    //Productos:
    void GestionDeProductos();
    void AgregarProducto();
    void EditarProducto();
    void VerProductos();
    void EliminarProducto();
    void Actualizar_Productos();
    void Actualizar_Presentaciones();
    vector<Productos> productos;
    vector<Productos> leer_productos();
    vector<Presentacion> presentaciones;
    vector<Presentacion> leer_presentaciones();
    string rutaProductos;

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
    void Actualizar_Clientes();
    void Actualizar_Regimenes();
    vector<RegimenFiscal> regimenesFiscales;
    vector<RegimenFiscal> leer_regimenes_fiscales();
    vector<Clientes> clientes;
    vector<Clientes> leer_clientes();
    string rutaClientes;

    //Ventas:
    void GestionDeVentas();
    void AgregarVenta();
    void VerVentas();
    vector<Ventas> ventas_vector;
    vector<ProductosVendidos> productosVendidos;
    vector<Ventas> LeerVentas();
    vector<ProductosVendidos> LeerProductosVendidos();
    void Actualizar_Productos_Vendidos();


    //Informes:
    void GestionDeInformes();
    void MenuInformesAdministrador();
    void MenuInformesVendedor();
    void MenuInformesRH();
    void MenuInformesAlmacen();
    void InformeDeVentas();
    void InformeDeInventarios();
    void InformeProductosConMayorInventario();
    void InformeProductosConCeroInventario();
    void InformeProductosResurtir();
    void InfromesDeActividadDeUsuarios();
    void InformeFiltroPorAccion(vector<RegistroDeActividadUser>& registros);
    void RegistroDeActividad(string action);
    void EscribirRegistro(string actionER);
    vector<RegistroDeActividadUser> leerRegistrosUsuarios();


    DateTime ConvertirFechaADateTime();
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

  
    string rutaUsuarios;
    string rutaVentas;
    string rutaProductosVendidos;
    string rutaPresentaciones;
    string rutaRegimenesFiscales;
    string rutaRegistrosUsuarios;
    Usuarios* usuarioActual;
};
/*
*/