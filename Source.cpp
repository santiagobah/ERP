//Main
//	Crear objeto de Sistema de Ventas
//	Ejecutar MenuInicial()
//SistemaDeVentas
//	MenuInicial()
//		IniciarSesion()
//		Salir
//	IniciarSesion()
//		(1)lla primera vez que se ejecuta se crea el usuario predeterminado
//		(2)Se leen los usuarios existentes del documento Usuarios.csv
//		(3)Se comparan las credenciales insertadas con las existentes
//		(4)Si son correctas se pasa a MenuPrincipal()
//		(5)Hay 3 intentos o se cierra el programa
//		***Falta vaciar el vector de lo leido despues de pasar al MenuPrincipal() para evitar falta de memoria
//		Solo es necesario que ese vector exista mientras se inicia sesion
//	MenuPrincipal()
//		Opciones para las diferentes tareas que se pueden realizar
//		Las opciones dependen según el tipo de usuario
//		Los niveles de acceso se pueden hacer de dos formas distintas :
//			Con switch evaluando el tipo de usuario que es
//			Con apuntadores de subclases y el menú da solo opciones a lo que pueden realizar
//			Admin tiene acceso a todo
//				Menu con estas opciones que lleva al menu de las acciones
//				Gestion de Usuarios
//				Gestion de Clientes
//				Gestion de Productos
//				Gestion de Ventas
//				Informes
//			Ventas
//				Menu con estas opciones que lleva al menu de las acciones
//				Gestion de Ventas
//				Informes de Ventas
//			RH
//				Menu con estas opciones que lleva al menu de las acciones
//				Gestion de Clientes
//				Informes de Actividad de Usuarios
//			Almacén
//				Menu con estas opciones que lleva al menu de las acciones
//				Gestion de Productos
//				Informes de Inventarios
//	GestionDeUsuarios
//		Se lee todo el documento Usuarios.csv
//		Menu con estas opciones
//		AgregarUsuario()
//			Crea un nuevo objeto de usuario
//			Lo añade al documento Usuarios.csv(append)
//			Vuelve al Menú
//		EditarUsuario()
//			Lee el documento Usuarios.csv
//			Guarda los datos en un vector con tipo de dato Usuario
//			Imprime ID, rol, nombre y apellido de todos los Usuarios
//			Permite Modificar cualquier cosa excepto el ID
//		VerUsuario()
//			Menu
//			Busqueda por rol
//			Busqueda por username
//			Busqueda por nombre
//			Mostrar todos
//		EliminarUsuario()
//			Te pide que introduzcas el ID del usuario que deseas eliminar
//			Antes de eliminarlo te muestra los datos del usuario y pide confirmación
//			Se elimina el vector con los datos de los usuarios
//	GestionDeClientes
//		Menu con estas opciones
//		AgregarCliente()
//			Crea un nuevo objeto de Cliente
//			Lo añade al documento Clientes.csv
//		EditarCliente()
//			Actualiza los detalles existentes del cliente.Los usuarios pueden cambiar cualquier información excepto el identificador único
//			Imprime ID, RFC, nombre y apellido de todos los Clientes
//			Se selecciona uno de los clientes
//			Muestra menu para elegir que deseas cambiar del cliente
//			Confirmación del cambio
//		VerClientes()
//			Mostrar menu
//			Mostrar todos
//			Busqueda por nombre
//			Busqueda por ciudad
//			Busqueda por estado
//		EliminarCliente()
//			Te pide que introduzcas el ID del cliente que deseas eliminar
//			Antes de eliminarlo te muestra los datos del cliente y pide confirmación
//	GestionDeProductos
//		Menu con estas opciones
//		AgregarProductos()
//			Introduce nuevos detalles del producto como UPC, nombre, tipo de presentación, precio, costo, inclusión del IVA y cantidad en stock.
//			Validar que aun no se haya agregado comparando UPC
//			Creación del objeto Productos
//			Agregar al documento Productos.csv
//		EditarProductos()
//			Modifica la información existente del producto.Todos los aspectos, excepto el identificador único del producto, pueden ser ajustados.
//			Mostrar la lista de productos
//			Seleccionar un producto
//			Mostrar menu con lo que se desea modificar del producto
//			Confirmar modificación
//		VerProductos()
//			Muestra todos los productos, proporcionando una vista clara de los niveles de stock, precios y otros detalles relevantes.Incluye opciones de ordenamiento y filtro para facilitar la búsqueda de productos.
//			Menu
//			Ordenar
//				Por Stock
//				Por ID
//				Por Precios
//				Por Costo
//			Filtrar
//				Por Nombre
//				Por ID
//				Por UPC
//			Mostrar todos los productos
//		EliminarProductos()
//			Habilita la eliminación de productos del inventario, incluyendo un paso de verificación para evitar errores
//			Se selecciona el producto escaneando el UPC
//			Se manda mensaje de confirmación
//	GestionDeVentas
//		Menu con estas opciones
//		RegistrarVenta()
//			Capturar Datos necesarios para la venta
//			Crear un objeto de Ventas
//			Añadirlo al documento Ventas.csv
//			*** Considerar que la cantidad de productos es variada por lo que se podria usar una estructura o vectores o un vector de una estructura para agregar los productos comprados en la venta
//		VerVentas()
//			Menu
//			Mostrar todas las ventas
//			Filtro por fecha
//			Por cliente
//			por vendedor
//	Informes
//		Menu con estas opciones
//		NO TODOS PUEDEN ACCEDER A TODOS LOS INFORMES
//		InformesDeVentas()
//			Generar Informes basados en datos de ventas
//			Menu
//				Informe basado en cliente
//				Informe basado en producto
//				Informe basado en Fechas
//		InformesDeInventarios()
//			sobre niveles de inventario, movimiento de productos y necesidades de reposición
//			Menu
//				Niveles de inventario
//				Movimiento de productos
//				Stock, Ventas
//				Necesidades de reposicion
//		InformesDeActividadDeUsuarios()
//			Rastrear  e informar sobre las actividades del usuario
//Usuarios
//	Getters y Setters
//	Para crear el nuevo ID se puede ver el último elemento del vector existen y ver que ID tiene y se le suma 1
//	usuarios[usuarios.size() - 1].getID
//	Encrypt()
//		Obtiene hash por medio de los códigos ascii
//		Regresa un número que hay que convertir a string
//Clientes
//	Hereda RegimenFiscal
//	Getters y Setters
//Productos
//	Hereda Presentacion
//	Getters y Setters
//Ventas
//	Getters y Setters
//Presentacion
//	Getters y Setters
//ProductosVendidos
//	Getters y Setters
//RegimenFiscal
//	Getters y Setters

#include "SistemaDeVentas.h"

using namespace std;

int main()
{
	SistemaDeVentas sistema;
	sistema.MenuInicial();
	return 0;
}


