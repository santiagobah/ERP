#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include "Ventas.h"
#include "ProductosVendidos.h"
#include "Usuarios.h"
#include "Productos.h"
#include "Clientes.h"
#include "Presentacion.h"
#include "RegimenFiscal.h"

using namespace std;

class SistemaDeVentas
{
public:
	SistemaDeVentas();
	~SistemaDeVentas();

	void MenuInicial();
	void IniciarSesion();
	void MenuPrincipal();
	void PausaConEnter();
	void LimpiarPantalla();

private:
	vector<Ventas> ventas;
	vector<ProductosVendidos> productosVendidos;
	vector<Usuarios> usuarios;
	vector<Productos> productos;
	vector<Clientes> clientes;
	vector<Presentacion> presentaciones;
	vector<RegimenFiscal> regimenesFiscales;
	string rutaUsuarios;
	string rutaProductos;
	string rutaClientes;
	string rutaPresentaciones;
	string rutaRegimenesFiscales;
	string rutaVentas;
	string rutaProductosVendidos;
};

