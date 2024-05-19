#include "SistemaDeVentas.h"
SistemaDeVentas::SistemaDeVentas()
{
    rutaUsuarios = "./Scr/Usuarios.csv";
    rutaClientes = "./Scr/Clientes.csv";
    rutaProductos = "./Scr/Productos.csv";
    rutaVentas = "./Scr/Ventas.csv";
    rutaProductosVendidos = "./Scr/ProductosVendidos.csv";
    rutaPresentaciones = "./Scr/Presentaciones.csv";
    rutaRegimenesFiscales = "./Scr/RegimenesFiscales.csv";
    rutaRegistrosUsuarios = "./Scr/RegistrosUsuarios.csv";
    usuarioActual = nullptr;

}

//Corregir: Ya no sirve el usuario admin una vez que se registraron nuevos, o eso fue por la prueba que hice? no estoy seguro xd, verificar al final

SistemaDeVentas::~SistemaDeVentas()
{
    delete usuarioActual;
}

void SistemaDeVentas::MenuInicial()
{
    // Limpia la pantalla antes de mostrar el menú
    LimpiarPantalla();
    // Variable para almacenar la opción seleccionada por el usuario
    int opcionMI = 0;
    // Bucle que se ejecuta hasta que el usuario elige salir del juego
    while (opcionMI != 2) {
        // Muestra las opciones del menú y solicita la entrada del usuario
        cout << "Menu de Inicio: " << endl
            << "1. Iniciar Sesion" << endl
            << "2. Salir del Sistema" << endl
            << "Opcion: ";
        cin >> opcionMI;
        // Realiza acciones basadas en la opción seleccionada por el usuario
        switch (opcionMI)
        {
        case 1:
            // Llama al método MenuPrincipal() para mostrar el menú principal del Sistema
            IniciarSesion();
            break;
        case 2:
            LimpiarPantalla();
            break;
        default:
            // En caso de que el usuario seleccione una opción no válida, muestra un mensaje de error
            // y espera a que el usuario presione Enter
            LimpiarPantalla();
            cout << "Selecciona una de las opciones validas" << endl;
            PausaConEnter();
            break;
        }
        // Limpia la pantalla antes de mostrar el menú nuevamente
        LimpiarPantalla();
        delete usuarioActual;
        usuarioActual = nullptr;
    }
}

void SistemaDeVentas::IniciarSesion()
{
    LimpiarPantalla();
    ifstream archivoLeido(rutaUsuarios.c_str());
    if (!archivoLeido) {
        ofstream archivo;
        archivo.open(rutaUsuarios.c_str(), fstream::out);
        DateTime dateJoined = ConvertirFechaADateTime();
        Usuarios auxUsuario = Usuarios("Admin", "Admin", "admin", "admin", "Admin", 1, dateJoined);
        archivo << "1,admin,admin,admin," << auxUsuario.Encrypt("admin") << ",Admin,"
            << dateJoined.year << "," << dateJoined.month << "," << dateJoined.day << ","
            << dateJoined.hour << "," << dateJoined.minute << "," << dateJoined.second << endl;
        archivo.close();
        string password = auxUsuario.Encrypt(auxUsuario.getPassword());
        auxUsuario.setPassword(password);
        usuarioActual = new Usuarios(auxUsuario.getName(), auxUsuario.getLastname(), auxUsuario.getUsername(), auxUsuario.getPassword(), auxUsuario.getRole(), auxUsuario.getId(), auxUsuario.getDateJoined());
        RegistroDeActividad("Creacion de Usuario");
        usuarios.push_back(auxUsuario);
    }
    else
    {
        usuarios = LeerUsuarios();
    }
    ValidacionDeCredenciales();
}

void SistemaDeVentas::ValidacionDeCredenciales()
{
    int contador = 1;
    bool bandera = false;
    do {
        string username, password;
        cout << "Ingrese su nombre de usuario: ";
        cin >> username;
        cout << "Ingrese su contrase–a: ";
        cin >> password;
        for (int i = 0; i < usuarios.size(); i++)
        {
            if (username == usuarios[i].getUsername() && usuarios[i].Encrypt(password) == usuarios[i].getPassword())
            {
                bandera = true;
                usuarioActual = new Usuarios(usuarios[i].getName(), usuarios[i].getLastname(), usuarios[i].getUsername(), usuarios[i].getPassword(), usuarios[i].getRole(), usuarios[i].getId(), usuarios[i].getDateJoined());
                RegistroDeActividad("Inicio de Sesion");
            }
        }
        if (bandera)
        {
            MenuPrincipal();
        }
        else
        {
            if (contador == 3)
            {
                cout << "Ha excedido el numero de intentos permitidos" << endl;
                PausaConEnter();
                RegistroDeActividad("Intento de Inicio de Sesion Fallido");
                exit(1);
            }
            cout << "Usuario o contrase–a incorrectos" << endl;
            PausaConEnter();
            contador++;
        }
    } while (bandera == false);
}

vector<Usuarios> SistemaDeVentas::LeerUsuarios()
{
    ifstream archivoLeido(rutaUsuarios.c_str());
    vector<Usuarios> usuarios1;
    string linea;
    while (getline(archivoLeido, linea))
    {
        string username, password, role, name, lastname;
        int id;
        DateTime dateJoined;
        vector<string> CargAtrib;
        string dato;
        for (int i = 0; i < linea.size(); i++)
        {
            if (linea[i] == ',')
            {
                CargAtrib.push_back(dato);
                dato = "";
            }
            else
            {
                dato += linea[i];
            }
        }
        CargAtrib.push_back(dato);
        id = stoi(CargAtrib[0]);
        name = CargAtrib[1];
        lastname = CargAtrib[2];
        username = CargAtrib[3];
        password = CargAtrib[4];
        role = CargAtrib[5];
        int year = stoi(CargAtrib[6]);
        int month = stoi(CargAtrib[7]);
        int day = stoi(CargAtrib[8]);
        int hour = stoi(CargAtrib[9]);
        int minute = stoi(CargAtrib[10]);
        int second = stoi(CargAtrib[11]);
        dateJoined = DateTime{ year, month, day, hour, minute, second };
        Usuarios auxUsuario = Usuarios(name, lastname, username, password, role, id, dateJoined);
        auxUsuario.setId(id);
        usuarios1.push_back(auxUsuario);
    }
    archivoLeido.close();
    return usuarios1;
}

void SistemaDeVentas::MenuPrincipal()
{
    switch (usuarioActual->getRoleInt())
    {
    case ADMIN:
        MenuAdministrador();
        break;
    case VENDEDOR:
        MenuVendedor();
        break;
    case RH:
        MenuRH();
        break;
    case ALMACEN:
        MenuAlmacen();
        break;
    default:
        break;
    }
}

void SistemaDeVentas::MenuAdministrador()
{
    // Variable para almacenar la opción seleccionada por el usuario
    int opcionMA = 0;
    // Bucle que se ejecuta hasta que el usuario elige salir del juego
    while (opcionMA != 6) {
        // Limpia la pantalla antes de mostrar el menú
        LimpiarPantalla();
        // Muestra las opciones del menú y solicita la entrada del usuario
        cout << "Menu de Administrador: " << endl
            << "1. Gestion de Usuarios" << endl
            << "2. Gestion de Clientes" << endl
            << "3. Gestion de Productos" << endl
            << "4. Gestion de Ventas" << endl
            << "5. Gestion de Informes" << endl
            << "6. Salir" << endl
            << "Opcion: ";
        cin >> opcionMA;
        // Realiza acciones basadas en la opción seleccionada por el usuario
        switch (opcionMA)
        {
        case 1:
            // Llama al método GestionDeUsuarios
            GestionDeUsuarios();
            break;
        case 2:
            // Llama al método GestionDeClientes
            GestionDeClientes();
            break;
        case 3:
            // Llama al método GestionDeProductos
            GestionDeProductos();
            break;
        case 4:
            // Llama al método GestionDeVentas
            GestionDeVentas();
            break;
        case 5:
            // Llama al método GestionDeInformes
            GestionDeInformes();
            break;
        case 6:
            LimpiarPantalla();
            break;
        default:
            // En caso de que el usuario seleccione una opción no válida, muestra un mensaje de error
            // y espera a que el usuario presione Enter
            LimpiarPantalla();
            cout << "Selecciona una de las opciones validas" << endl;
            PausaConEnter();
            break;
        }
    }
}

void SistemaDeVentas::MenuVendedor()
{
    // Variable para almacenar la opción seleccionada por el usuario
    int opcionMV = 0;
    // Bucle que se ejecuta hasta que el usuario elige salir del Sistema
    while (opcionMV != 4) {
		// Limpia la pantalla antes de mostrar el menú
		LimpiarPantalla();
		// Muestra las opciones del menú y solicita la entrada del usuario
		cout << "Menu de Vendedor: " << endl
			<< "1. Gestion de Clientes" << endl
			<< "2. Gestion de Ventas" << endl
            << "3. Gestion de Informes" << endl
			<< "4. Salir" << endl
			<< "Opcion: ";
		cin >> opcionMV;
		// Realiza acciones basadas en la opción seleccionada por el usuario
		switch (opcionMV)
		{
		case 1:
			// Llama al método GestionDeClientes
			GestionDeClientes();
			break;
		case 2:
			// Llama al método Gestión de Ventas
			GestionDeVentas();
			break;
		case 3:
			// Llama al método Gestión de Informes
			GestionDeInformes();
			break;
		case 4:
			LimpiarPantalla();
			break;
		default:
			// En caso de que el usuario seleccione una opción no válida, muestra un mensaje de error
			// y espera a que el usuario presione Enter
			LimpiarPantalla();
			cout << "Selecciona una de las opciones validas" << endl;
			PausaConEnter();
			break;
		}
	}
}

void SistemaDeVentas::MenuRH()
{
    // Variable para almacenar la opción seleccionada por el usuario
	int opcionMRH = 0;
	// Bucle que se ejecuta hasta que el usuario elige salir del Sistema
	while (opcionMRH != 4) {
		// Limpia la pantalla antes de mostrar el menú
		LimpiarPantalla();
		// Muestra las opciones del menú y solicita la entrada del usuario
		cout << "Menu de Recursos Humanos: " << endl
			<< "1. Gestion de Clientes" << endl
			<< "2. Gestion de Informes" << endl
			<< "3. Salir" << endl
			<< "Opcion: ";
		cin >> opcionMRH;
		// Realiza acciones basadas en la opción seleccionada por el usuario
		switch (opcionMRH)
		{
		case 1:
			// Llama al método GestionDeUsuarios
			GestionDeUsuarios();
			break;
		case 2:
			// Llama al método GestionDeClientes
			GestionDeClientes();
			break;
		case 3:
			// Llama al método GestionDeInformes
			GestionDeInformes();
			break;
		case 4:
			LimpiarPantalla();
			break;
		default:
			// En caso de que el usuario seleccione una opción no válida, muestra un mensaje de error
			// y espera a que el usuario presione Enter
			LimpiarPantalla();
			cout << "Selecciona una de las opciones validas" << endl;
			PausaConEnter();
			break;
		}
	}

}

void SistemaDeVentas::MenuAlmacen()
{
    // Variable para almacenar la opción seleccionada por el usuario
	int opcionMAL = 0;
	// Bucle que se ejecuta hasta que el usuario elige salir del Sistema
	while (opcionMAL != 3) {
		// Limpia la pantalla antes de mostrar el menú
		LimpiarPantalla();
		// Muestra las opciones del menú y solicita la entrada del usuario
		cout << "Menu de Almacen: " << endl
			<< "1. Gestion de Productos" << endl
			<< "2. Gestion de Informes" << endl
			<< "3. Salir" << endl
			<< "Opcion: ";
		cin >> opcionMAL;
		// Realiza acciones basadas en la opción seleccionada por el usuario
		switch (opcionMAL)
		{
		case 1:
			// Llama al método GestionDeProductos
			GestionDeProductos();
			break;
		case 2:
			// Llama al método GestionDeInformes
			GestionDeInformes();
			break;
		case 3:
			LimpiarPantalla();
			break;
		default:
			// En caso de que el usuario seleccione una opción no válida, muestra un mensaje de error
			// y espera a que el usuario presione Enter
			LimpiarPantalla();
			cout << "Selecciona una de las opciones validas" << endl;
			PausaConEnter();
			break;
		}
	}

}

void SistemaDeVentas::GestionDeProductos() {
    cout << "\nBienvenido al menú de Productos" << endl;
    int opc_men_pod = 0;
    do {
        cout <<
            "\n1. Add Products" <<
            "\n2. Edit Products" <<
            "\n3. See Products" << //SEE?
            "\n4. Delete Products" <<
            "\n5. Return" <<
            "\nOpción elegida: ";
        cin >> opc_men_pod;
        switch (opc_men_pod) {
        case 1:
        {
            RegistroDeActividad("Agregar Producto");
            SistemaDeVentas::AgregarProducto();
            break;
        }
        case 2:
        {
            RegistroDeActividad("Editar Producto");
            SistemaDeVentas::EditarProducto();
            break;
        }
        case 3:
        {
            RegistroDeActividad("Ver Productos");
            SistemaDeVentas::VerProductos();
            break;
        }
        case 4:
        {
            RegistroDeActividad("Eliminar Producto");
            SistemaDeVentas::EliminarProducto();
            break;
        }
        case 5:
        {
            break;
        }
        default:
        {
            cout << "Seleccione una opción válida" << endl;
            SistemaDeVentas::GestionDeProductos();
            break;
        }
        }


    } while (opc_men_pod != 5);
}

void SistemaDeVentas::AgregarProducto() { //Crear excepciones por si aún no se crea el archivo de productos
    //Hacer que ID vaya creciendo
    int id_u_actual; //Para hacer ID's consecutivos
    int id_p_actual; //Para hacer ID's consecutivos
    ifstream archivo_pr(rutaProductos.c_str());
    if (!archivo_pr) {
        ofstream archivo_prod(rutaProductos.c_str());
        id_u_actual = 0;
        id_p_actual = 0;
    }
    else {
        productos = SistemaDeVentas::leer_productos(); //Para que inicie el vector ya cargado con los productos que estén ya registrados
        int cant_prod_reg = productos.size();
        id_u_actual = productos[cant_prod_reg - 1].get_id();
        id_p_actual = presentaciones[cant_prod_reg-1].getID();
    }
    ofstream archivo_productos(rutaProductos, ios::app);
    string upc, name;
    float price, cost;
    bool has_iva;
    int stock;
    
//    cout << "The  ID for this " << name << " presentation is going to be: " << id_p_actual + 1 << endl; archivo_productos << id_p_actual + 1 << ",";
    string first_part_name;
    int n_presentations = 0;
    cout << "Type the main name of the new product: "; cin.ignore(); getline(cin, first_part_name);
    cout << "How many presentations are there for " << first_part_name << "? "; cin >> n_presentations;
    for (int i = 0; i < n_presentations; i++) {
        archivo_productos << first_part_name << ",";
        ofstream presentaciones_productos(rutaPresentaciones.c_str(), ios::app);
        cout << "\nAdd something to this name to create a unique name for presentation " << i+1 << " of " << first_part_name << ": " ;
        cin.ignore(); getline(cin, name); name = first_part_name +  " " + name;
        cout << "\nScan the barcode of " << name << ": ";
        cin >> upc; archivo_productos << upc << ",";
        cout << "\nThe unique ID for " << name << " is going to be: " << id_u_actual + 1 << endl; archivo_productos << id_u_actual + 1 << ",";
        cout << "\nType the price for " << name << ": ";
        cin >> price; archivo_productos << price << ",";
        cout << "Type the cost for " << name << ": ";
        cin >> cost; archivo_productos << cost << ",";
        //Implementar un switch para el IVA
        cout << name << " has IVA? (1. YES/ 0.NO): "; //implementar método que sea un switch para 1.yes, 2.no
        cin >> has_iva; archivo_productos << has_iva << ",";
        cout << "How many " << name << " are available right now? ";
        cin >> stock; archivo_productos << stock << ",";
        cout << "The ID for this presentation of " << name << " is " << id_p_actual + 1 << endl;
        presentaciones_productos << id_p_actual + 1 << ",";
        presentaciones_productos << name << endl;
        archivo_productos << id_p_actual + 1 << endl;
        Productos NuevoProducto(id_u_actual, upc, first_part_name, id_p_actual, price, cost, has_iva, stock, id_p_actual, name);
        productos.push_back(NuevoProducto);
        id_u_actual++;
        id_p_actual++;
    }
    archivo_productos.close();
}

void SistemaDeVentas::EditarProducto() { //crear confirmaciones de edit
    ifstream archivo_pr(rutaProductos.c_str());
    if (!archivo_pr) {
        cout << "There are not registered products" << endl;
        GestionDeProductos();
    }
    else {
        productos = SistemaDeVentas::leer_productos();
        presentaciones = leer_presentaciones();
    }
    cout << "Choose the product which you want to edit: " << endl;
    int prod_edit;
    for (int i = 0; i < presentaciones.size(); i++) {
        cout << i + 1 << ".- " << presentaciones[i].getName() << endl;
    }
    cout << "Product to edit: ";
    cin >> prod_edit;
    int var_edit;
    cout << "You are now editing " << productos[prod_edit - 1].get_name() << endl;
    cout << "Choose the variable to edit: " << endl;
    cout << "1. Name" << "\n2. Price" << "\n3. Cost" << "\n4. IVA" << "\n5. Stock" << "\n6. Presentation name" <<  "\nOption: ";
    cin >> var_edit;
    switch (var_edit)
    {
        case 1:
        {
            string new_name;
            cout << "Type the new name: "; cin.ignore(); getline(cin, new_name);
            productos[prod_edit - 1].set_name(new_name);
            break;
        }
        case 2:
        {
            float new_price;
            cout << "Type the new price for " << productos[prod_edit - 1].get_name() << ": "; cin >> new_price;
            productos[prod_edit - 1].set_price(new_price);
            break;
        }
        case 3:
        {
            float new_cost;
            cout << "Type the new cost for " << productos[prod_edit - 1].get_name() << ": "; cin >> new_cost;
            productos[prod_edit - 1].set_cost(new_cost);
            break;
        }
        case 4:
        {
            bool set_iva;
            cout << "Type the new IVA option: "; cin >> set_iva;
            productos[prod_edit - 1].set_has_iva(set_iva);
            break;
        }
        case 5:
        {
            int new_stock;
            cout << "Type the new stock for " << productos[prod_edit - 1].get_name() << ": "; cin >> new_stock;
            productos[prod_edit - 1].set_stock(new_stock);
            break;
        }
        case 6:
        {
            string new_presentation_name;
            cout << "Type the new presentation name for this " << productos[prod_edit-1].get_name() << ": "; cin.ignore(); getline(cin, new_presentation_name);
            string final_new_presentation_name;
            final_new_presentation_name = productos[prod_edit-1].get_name() + " " + new_presentation_name;
            presentaciones[prod_edit-1].setName(final_new_presentation_name);
            Actualizar_Presentaciones();
            break;
        }
    }
    Actualizar_Productos(); //Actualiza los cambios que se hayan realizado al momento del edit
}
void SistemaDeVentas::Actualizar_Presentaciones(){
    ofstream presentaciones_pr(rutaPresentaciones.c_str());
    for (int i  = 0; i < presentaciones.size(); i++) {
        presentaciones_pr << presentaciones[i].getID() << "," << presentaciones[i].getName() << endl;
    }
}
void SistemaDeVentas::VerProductos() {
    ifstream archivo_pr(rutaProductos.c_str());
    if (!archivo_pr) {
        cout << "There are not registered products" << endl;
        GestionDeProductos();
    }
    else {
        productos = SistemaDeVentas::leer_productos();
        presentaciones = leer_presentaciones();
    }
    vector <Productos> aux_ord_prod;
    aux_ord_prod = productos;
    vector <Presentacion> aux_ord_pres;
    aux_ord_pres = presentaciones;
    int sort_filter;
    cout << "1. Sort products" << "\n2. Filter products" << "\nOption: "; cin >> sort_filter;
    switch (sort_filter) {
    case 1:
    {
        int sort_opc;
        cout << "\nSort by: " << "\n1. Stock" << "\n2. ID" << "\n3. Price: Low to High" << "\n4. Price: High to Low" << "\n5. Cost" << "\nOption: "; cin >> sort_opc;
        switch (sort_opc) {
        case 1:
        {
            for (int i = 0; i < productos.size(); i++) {
                for (int j = 0; j < productos.size() - 1 ; j++) {
                    if (productos[j].get_stock() > productos[j+1].get_stock()) {
                        aux_ord_prod[j] = productos[j];
                        productos[j] = productos[j+1];
                        productos[j+1] = aux_ord_prod[j];
                        //Ordenar presentaci—n tambiŽn
                        aux_ord_pres[j] = presentaciones[j+1];
                        presentaciones[j+1] = presentaciones[j];
                        presentaciones[j] = aux_ord_pres[j];
                    }
                }
            }
            for (int i = 0; i < productos.size(); i++) {
                cout << i + 1 << ".- " << presentaciones[i].getName() << " con un stock de " << productos[i].get_stock() << endl;
            }
            break;
        }
        case 2:
        {
            for (int i = 0; i < productos.size(); i++) {
                for (int j = 0; j < productos.size() - 1 ; j++) {
                    if (productos[j].get_id() > productos[j+1].get_id()) {
                        aux_ord_prod[j] = productos[j];
                        productos[j] = productos[j+1];
                        productos[j+1] = aux_ord_prod[j];
                        //Ordenar presentaci—n tambiŽn
                        aux_ord_pres[j] = presentaciones[j+1];
                        presentaciones[j+1] = presentaciones[j];
                        presentaciones[j] = aux_ord_pres[j];
                    }
                }
            }            for (int i = 0; i < productos.size(); i++) {
                cout << i + 1 << ".- " << presentaciones[i].getName() << ". ID: " << productos[i].get_id() << endl;
            }
            break;
        }
        case 3:
        {
            for (int i = 0; i < productos.size(); i++) {
                for (int j = 0; j < productos.size() - 1 ; j++) {
                    if (productos[j].get_price() > productos[j+1].get_price()) {
                        aux_ord_prod[j] = productos[j];
                        productos[j] = productos[j+1];
                        productos[j+1] = aux_ord_prod[j];
                        //Ordenar presentaci—n tambiŽn
                        aux_ord_pres[j] = presentaciones[j+1];
                        presentaciones[j+1] = presentaciones[j];
                        presentaciones[j] = aux_ord_pres[j];
                    }
                }
            }            for (int i = 0; i < productos.size(); i++) {
                cout << i+1 << ".- " << presentaciones[i].getName() << " con un precio de $" << productos[i].get_price() << endl;
            }
            break;
        }
        case 4:
        {
            for (int i = 0; i < productos.size(); i++) {
                for (int j = 0; j < productos.size() - 1 ; j++) {
                    if (productos[j].get_price() > productos[j+1].get_price()) {
                        aux_ord_prod[j] = productos[j];
                        productos[j] = productos[j+1];
                        productos[j+1] = aux_ord_prod[j];
                        //Ordenar presentaci—n tambiŽn
                        aux_ord_pres[j] = presentaciones[j+1];
                        presentaciones[j+1] = presentaciones[j];
                        presentaciones[j] = aux_ord_pres[j];
                    }
                }
            }
            //Checar este despliegue de datos
            for (int i = productos.size(); i > 0; i--) {
                cout << i << ".- " << presentaciones[i].getName() << " con un precio de $" << productos[i].get_price() << endl;
            }
            break;
        }
        case 5:
        {
            for (int i = 0; i < productos.size(); i++) {
                for (int j = 0; j < productos.size() - 1 ; j++) {
                    if (productos[j].get_cost() > productos[j+1].get_cost()) {
                        aux_ord_prod[j] = productos[j];
                        productos[j] = productos[j+1];
                        productos[j+1] = aux_ord_prod[j];
                        //Ordenar presentaci—n tambiŽn
                        aux_ord_pres[j] = presentaciones[j+1];
                        presentaciones[j+1] = presentaciones[j];
                        presentaciones[j] = aux_ord_pres[j];
                    }
                }
            }
            for (int i = 0; i < productos.size(); i++) {
                cout << i + 1 << ".- " << productos[i].get_name() << " con un costo de $" << productos[i].get_cost() << endl;
            }
            break;
        }
        }
        //Restuarar el vector a estar ordenado por ID para que no ocasione problemas con el aumento de 1 en 1 para el ID
        for (int i = 0; i < productos.size(); i++) {
            for (int j = 0; j < productos.size(); j++) {
                if (productos[j].get_id() > productos[j + 1].get_id()) {
                    aux_ord_prod[0] = productos[j + 1];
                    productos[j + 1] = productos[j];
                    productos[j] = aux_ord_prod[0];
                    //Ordenar tambiŽn a las presentaciones
                    aux_ord_pres[0] = presentaciones[j+1];
                    presentaciones[j+1] = presentaciones[j];
                    presentaciones[j] = aux_ord_pres[0];
                }
            }
        }
        break;
    }
    case 2:
    {
        int opc_fil;
        vector <Productos> aux_bus;
        productos = leer_productos();
        presentaciones = leer_presentaciones();
        cout << "\nFilter by: " << "\n1. Name" << "\n2. ID" << "\n3. UPC" << "\nOption: "; cin >> opc_fil;
        switch (opc_fil) {
        case 1:
        {
            string nombre_bus;
            cout << "Type the name of the product: "; cin.ignore(); getline(cin, nombre_bus);
            for (int i = 0; i < productos.size(); i++) {
                if (nombre_bus == productos[i].get_name()) {
                    aux_bus.push_back(productos[i]);
                }
            }
            for (int j = 0; j < aux_bus.size(); j++) {
                for (int i  = 0; i < presentaciones.size(); i++) {
                    if (aux_bus[j].get_id_presentation() == presentaciones[i].getID()) {
                        cout << j+1 << ".- " << aux_bus[j].get_name() << ". ID: " << aux_bus[j].get_id() << endl;
                    }
                }
            }
            break;
        }
        case 2:
        {
            int id_bus;
            cout << "Type the ID of the product: "; cin >> id_bus;
            for (int i = 0; i < productos.size(); i++) {
                if (id_bus == productos[i].get_id()) {
                    aux_bus.push_back(productos[i]);
                }
            }
            for (int j = 0; j < aux_bus.size(); j++) {
                for (int i  = 0; i < presentaciones.size(); i++) {
                    if (aux_bus[j].get_id_presentation() == presentaciones[i].getID()) {
                        cout << j+1 << ".- " << aux_bus[j].get_name() << ". ID: " << aux_bus[j].get_id() << endl;
                    }
                }
            }

            break;
        }
        case 3:
        {
            string upc_bus;
            cout << "Scan the barcode of the product: "; cin.ignore(); getline(cin, upc_bus);
            for (int i = 0; i < productos.size(); i++) {
                if (upc_bus == productos[i].get_UPC()) {
                    aux_bus.push_back(productos[i]);
                }
            }
            for (int j = 0; j < aux_bus.size(); j++) {
                for (int i  = 0; i < presentaciones.size(); i++) {
                    if (aux_bus[j].get_id_presentation() == presentaciones[i].getID()) {
                        cout << j+1 << ".- " << aux_bus[j].get_name() << ". ID: " << aux_bus[j].get_id() << endl;
                    }
                }
            }

            break;
        }
        }
        break;
    }
    }
}

void SistemaDeVentas::EliminarProducto() { //crear confirmaciones de delete
    ifstream archivo_pr(rutaProductos.c_str());
    if (!archivo_pr) {
        cout << "There are not registered products" << endl;
        GestionDeProductos();
    }
    else {
        productos = SistemaDeVentas::leer_productos();
        presentaciones = leer_presentaciones();
    }
    string upc;
    int band_prod = 0;
    cout << "\nScan the barcode of the product which you want to delete: ";
    cin >> upc;
    for (int i = 0; i < productos.size(); i++) {
        if (upc == productos[i].get_UPC()) {
            for (int k = 0; k < presentaciones.size(); k++) {
                if (productos[i].get_id_presentation() == presentaciones[k].getID()) {
                    cout << presentaciones[k].getName() << " eliminado exitosamente" << endl;
                }
            }
            for (int j = 0; j < presentaciones.size(); j++) {
                if (productos[i].get_id_presentation() == presentaciones[j].getID()) {
                    presentaciones.erase(presentaciones.begin() + j);
                }
            }
            productos.erase(productos.begin() + i);
            band_prod = 1;
            break;
        }
    }
    if (band_prod == 0) {
        cout << "El artículo no fue encontrado" << endl;
    }
    Actualizar_Productos();
    Actualizar_Presentaciones();
}

void SistemaDeVentas::Actualizar_Productos() {
    ofstream archivo_p(rutaProductos.c_str());
    for (int i = 0; i < productos.size(); i++) {
        archivo_p << productos[i].get_name() << "," << productos[i].get_UPC() << "," << productos[i].get_id() << "," << productos[i].get_price() << "," << productos[i].get_cost() << "," << productos[i].get_has_iva() << "," << productos[i].get_stock() << "," << productos[i].get_id_presentation() << endl;
    }
    archivo_p.close();
}

vector<Productos> SistemaDeVentas::leer_productos() {
    vector<Productos> productos1;
    ifstream lectura_archivo(rutaProductos.c_str());
    string linea;
    while (getline(lectura_archivo, linea)) {
        string upc, name;
        int id_u, id_p, stock, has_iva;
        float price, cost;
        vector <string> carga_productos;
        string parte;
        for (int i = 0; i < linea.size(); i++) {
            if (linea[i] == ',') {
                carga_productos.push_back(parte);
                parte = "";
            }
            else {
                parte += linea[i];
            }
        }
        carga_productos.push_back(parte);
        name = carga_productos[0];
        upc = carga_productos[1];
        id_u = stoi(carga_productos[2]);
        price = stof(carga_productos[3]);
        cost = stof(carga_productos[4]);
        has_iva = stoi(carga_productos[5]);
        stock = stoi(carga_productos[6]);
        id_p = stoi(carga_productos[7]);
        presentaciones = leer_presentaciones();
        string nombre_p;
        int id_pr = 0;
        for (int i = 0; i < presentaciones.size(); i++) {
            id_pr = presentaciones[i].getID();
            nombre_p = presentaciones[i].getName();
        }
        Productos guardado_productos = Productos(id_u, upc, name, id_p, price, cost, has_iva, stock, id_pr, nombre_p);
        guardado_productos.set_id(id_u);
        guardado_productos.set_UPC(upc);
        guardado_productos.set_name(name);
        guardado_productos.set_id_presentation(id_p);
        guardado_productos.set_price(price);
        guardado_productos.set_cost(cost);
        guardado_productos.set_has_iva(has_iva);
        guardado_productos.set_stock(stock);
        guardado_productos.setID(id_pr);
        guardado_productos.setName(nombre_p);
        productos1.push_back(guardado_productos);
    }
    return productos1;
}
vector <Presentacion> SistemaDeVentas::leer_presentaciones(){
    vector<Presentacion> presentaciones1;
    ifstream lectura_presentaciones(rutaPresentaciones.c_str());
    string linea_p;
    while (getline(lectura_presentaciones, linea_p)) {
        vector <string> carga_presentaciones;
        string parte_p;
        string name_p;
        int id_p_pcsv;
        for (int i = 0; i < linea_p.size(); i++) {
            if (linea_p[i] == ',') {
                carga_presentaciones.push_back(parte_p);
                parte_p = "";
            }
            else{
                parte_p += linea_p[i];
            }
        }
        carga_presentaciones.push_back(parte_p);
        id_p_pcsv = stoi(carga_presentaciones[0]);
        name_p = carga_presentaciones[1];
        Presentacion lectura_pr = Presentacion(id_p_pcsv, name_p);
        lectura_pr.setID(id_p_pcsv);
        lectura_pr.setName(name_p);
        presentaciones1.push_back(lectura_pr);
    }
    return presentaciones1;
}
void SistemaDeVentas::GestionDeUsuarios()
{
    // Variable para almacenar la opción seleccionada por el usuario
    int opcionGU = 0;
    do {
        // Limpia la pantalla antes de mostrar el menú
        LimpiarPantalla();
        cout << "\nBienvenido al menú de Usuarios" << endl;
        // Muestra las opciones del menú y solicita la entrada del usuario
        cout <<
            "1. Add Users" <<
            "\n2. Edit Users" <<
            "\n3. Delete Users" <<
            "\n4. Return" <<
            "\nOpción elegida: ";
        cin >> opcionGU;
        switch (opcionGU) {
        case 1:
        {
            RegistroDeActividad("Creacion de Usuario");
            AgregarUsuario();
            break;
        }
        case 2:
        {
            RegistroDeActividad("Editar Usuario");
            EditarUsuario();
            break;
        }
        case 3:
        {
            RegistroDeActividad("Eliminar Usuario");
            EliminarUsuario();
            break;
        }
        case 4:
        {
            break;
        }
        default:
        {
            LimpiarPantalla();
            cout << "Seleccione una opción válida" << endl;
            PausaConEnter();
            break;
        }
        }
    } while (opcionGU != 4);
}

void SistemaDeVentas::AgregarUsuario()
{
    usuarios = LeerUsuarios();
    string name, surname, username, password, role;
    int id = 0;
    DateTime dateJoined = ConvertirFechaADateTime();
    cout << "\nType the name of the user: ";
    cin >> name;
    cout << "Type the surname of the user: ";
    cin.ignore();
    getline(cin, surname);
    cout << "Type the username of the user: ";
    cin >> username;
    cout << "Type the password of the user: ";
    cin >> password;
    while (id < 1 || id > 4) {
        cout << "Select the role of the user: " << endl
            << "1. Admin" << endl
            << "2. Vendedor" << endl
            << "3. RH" << endl
            << "4. Almacen" << endl
            << "Option: ";
        cin >> id;
        switch (id)
        {
        case 1:
            role = "Admin";
            break;
        case 2:
            role = "Vendedor";
            break;
        case 3:
            role = "RH";
            break;
        case 4:
            role = "Almacen";
            break;
        }
    }
    int cantidad_usuarios = usuarios.size();
    int current_id = 0;
    cout << "yamañovectorusuarios" << usuarios.size() << endl;
    if (usuarios.size() != 0) {
        current_id = usuarios[cantidad_usuarios - 1].getId(); //Para que el ID vaya creciendo
    }
    cout << "curentiddd: " << current_id << endl;
    id = current_id + 1;
    cout << "idaasignar " << id << endl;
    Usuarios NuevoUsuario = Usuarios(name, surname, username, password, role, id, dateJoined);
    NuevoUsuario.setName(name);
    NuevoUsuario.setLastname(surname);
    NuevoUsuario.setUsername(username);
    NuevoUsuario.setPassword(NuevoUsuario.Encrypt(password));
    NuevoUsuario.setRole(role);
    NuevoUsuario.setId(id);
    NuevoUsuario.setDateJoined(dateJoined);
    usuarios.push_back(NuevoUsuario);
    ofstream archivo;
    archivo.open(rutaUsuarios.c_str());
    for (int i = 0; i < usuarios.size(); i++) {
        archivo << usuarios[i].getId() << "," << usuarios[i].getName() << "," << usuarios[i].getLastname() << "," << usuarios[i].getUsername() << "," << usuarios[i].getPassword() << "," << usuarios[i].getRole() << "," << usuarios[i].getDateJoined().year << "," << usuarios[i].getDateJoined().month << "," << usuarios[i].getDateJoined().day << "," << usuarios[i].getDateJoined().hour << "," << usuarios[i].getDateJoined().minute << "," << usuarios[i].getDateJoined().second << endl;
    }
    archivo.close();
    //cout << usuarios[2].getDateJoined() << endl;

}

void SistemaDeVentas::EditarUsuario()
{
    usuarios = LeerUsuarios();
    cout << "Choose the user which you want to select: " << endl;
    int user_edit;
    for (int i = 0; i < usuarios.size(); i++) {
        cout << i + 1 << ".- " << usuarios[i].getName() << " " << usuarios[i].getLastname() << " (" << usuarios[i].getRole() << ") " << endl;
    }
    cout << "User to edit: ";
    cin >> user_edit;
    int var_edit;
    cout << "You are now editing " << usuarios[user_edit - 1].getName() << " " << usuarios[user_edit - 1].getLastname() << " (" << usuarios[user_edit - 1].getRole() << ") " << endl;
    cout << "Choose the variable to edit: " << endl;
    cout << "1. Name"
        << "\n2. Lastname"
        << "\n3. Username"
        << "\n4. Password"
        << "\n5. Role"
        << "\nOption: ";
    cin >> var_edit;
    switch (var_edit)
    {
    case 1:
    {
        string new_name;
        cout << "Type the new name: ";
        cin.ignore();
        getline(cin, new_name);
        usuarios[user_edit - 1].setName(new_name);
        break;
    }
    case 2:
    {
        string new_lastname;
        cout << "Type the new lastname: ";
        cin.ignore();
        getline(cin, new_lastname);
        usuarios[user_edit - 1].setLastname(new_lastname);
        break;
    }
    case 3:
    {
        string new_username;
        cout << "Type the new username: ";
        cin >> new_username;
        usuarios[user_edit - 1].setUsername(new_username);
        break;
    }
    case 4:
    {
        string new_password;
        cout << "Type the new password: ";
        cin >> new_password;
        usuarios[user_edit - 1].setPassword(usuarios[user_edit - 1].Encrypt(new_password));
        break;
    }
    case 5:
    {
        string new_role;
        int opc_role = 0;
        while (opc_role < 1 || opc_role > 4) {
            cout << "Select the role of the user: " << endl
                << "1. Admin" << endl
                << "2. Vendedor" << endl
                << "3. RH" << endl
                << " 4. Almacen" << endl
                << "Option: ";
            cin >> opc_role;
            switch (opc_role)
            {
            case 1:
                new_role = "Admin";
                break;
            case 2:
                new_role = "Vendedor";
                break;
            case 3:
                new_role = "RH";
                break;
            case 4:
                new_role = "Almacen";
                break;
            }
        }
        usuarios[user_edit - 1].setRole(new_role);
        break;
    }
    }
    ofstream archivo;
    archivo.open(rutaUsuarios.c_str(), fstream::out);
    for (int i = 0; i < usuarios.size(); i++) {
        archivo << usuarios[i].getId() << "," << usuarios[i].getName() << "," << usuarios[i].getLastname() << "," << usuarios[i].getUsername() << "," << usuarios[i].getPassword() << "," << usuarios[i].getRole() << "," << usuarios[i].getDateJoined().year << "," << usuarios[i].getDateJoined().month << "," << usuarios[i].getDateJoined().day << "," << usuarios[i].getDateJoined().hour << "," << usuarios[i].getDateJoined().minute << "," << usuarios[i].getDateJoined().second << endl;
    }
    archivo.close();
}

void SistemaDeVentas::EliminarUsuario()
{
    usuarios = LeerUsuarios();
    string username;
    int id_user = 0;
    for (int i = 0; i < usuarios.size(); i++) {
        cout << i + 1 << ".- " << usuarios[i].getName() << " " << usuarios[i].getLastname() << " (" << usuarios[i].getRole() << ") " << endl;
    }
    cout << "Type the username of the user to delete: ";
    cin >> id_user;
    //confirmar si se quiere eliminar
    int opc_del;
    cout << "Are you sure you want to delete this user? " << endl
        << "Data: " << usuarios[id_user - 1].getName() << " " << usuarios[id_user - 1].getLastname() << " (" << usuarios[id_user - 1].getRole() << ") " << endl
        << "1. YES" << endl
        << "2. NO" << endl
        << "Option: ";
    cin >> opc_del;
    if (opc_del == 1) {

        usuarios.erase(usuarios.begin() + id_user - 1);
        ofstream archivo;
        archivo.open(rutaUsuarios.c_str(), fstream::out);
        for (int i = 0; i < usuarios.size(); i++) {
            archivo << usuarios[i].getId() << "," << usuarios[i].getName() << "," << usuarios[i].getLastname() << ","
                << usuarios[i].getUsername() << "," << usuarios[i].getPassword() << "," << usuarios[i].getRole() << ","
                << usuarios[i].getDateJoined().year << "," << usuarios[i].getDateJoined().month
                << "," << usuarios[i].getDateJoined().day << "," << usuarios[i].getDateJoined().hour
                << "," << usuarios[i].getDateJoined().minute << "," << usuarios[i].getDateJoined().second
                << endl;
        }
        archivo.close();
    }

}

void SistemaDeVentas::GestionDeClientes() {
    int opc_cli;
    do {
        cout << "\nBienvenido al Menú de Clientes: " << "\n1. Add Client" << "\n2. Edit Client" << "\n3. See Clients" << "\n4. Delete Client" << "\n5. Return" << "\nOption: "; cin >> opc_cli;
        switch (opc_cli) {
        case 1:
        {
            RegistroDeActividad("Agregar Cliente");
            AgregarCliente();
            break;
        }
        case 2:
        {
            RegistroDeActividad("Editar Cliente");
            EditarCliente();
            break;
        }
        case 3:
        {
            RegistroDeActividad("Ver Clientes");
            VerClientes();
            break;
        }
        case 4:
        {
            RegistroDeActividad("Eliminar Cliente");
            EliminarCliente();
            break;
        }
        case 5:
        {
            break;
        }
        }
    } while (opc_cli != 5);
}

void SistemaDeVentas::AgregarCliente() { //Corregir con cin.ignore()
    int actual_id_cliente;
    ifstream archivo_cl(rutaClientes.c_str());
    if (!archivo_cl) {
        ofstream archivo_cll(rutaClientes.c_str());
        actual_id_cliente = 0;
    }
    else {
        clientes = leer_clientes();
        int cant_client_reg = clientes.size();
        actual_id_cliente = clientes[cant_client_reg - 1].getID();
    }
    string name, rfc, address, city, state, zipcode, name_reg_fis;
    int code_reg_fis;
    ofstream archivo_clientes(rutaClientes, ios::app);
    cout << "\nType the client´s name: "; cin >> name; archivo_clientes << name << ",";
    cout << "Type the rfc of " << name << ": "; cin >> rfc; archivo_clientes << rfc << ",";
    cout << "Type the address of " << name << ": "; cin >> address; archivo_clientes << address << ",";
    cout << "Type the city where " << name << " lives: "; cin >> city; archivo_clientes << city << ",";
    cout << "Type the state where " << name << " lives: "; cin >> state; archivo_clientes << state << ",";
    cout << "Type the zipcode where " << address << " is located: "; cin >> zipcode; archivo_clientes << zipcode << ",";
    cout << "The ID for the 'fiscal register' of " << name << " is: " << actual_id_cliente + 1; archivo_clientes << actual_id_cliente + 1 << ",";
    ofstream archivo_regimenes(rutaRegimenesFiscales, ios::app);
    archivo_regimenes << actual_id_cliente + 1 << ",";
    cout << "\nType the code of the fiscal register of " << name << ": "; cin >> code_reg_fis; archivo_regimenes << code_reg_fis << ",";
    cout << "Type the name of the fiscal register of " << name << ": "; cin.ignore(); getline(cin, name_reg_fis); archivo_regimenes << name_reg_fis << endl;
    cout << "The assigned id for " << name << " is " << actual_id_cliente + 1; archivo_clientes << actual_id_cliente + 1 << endl;
    Clientes nuevoCliente = Clientes(actual_id_cliente, name, rfc, actual_id_cliente, address, city, state, zipcode, actual_id_cliente, code_reg_fis, name_reg_fis );
    clientes.push_back(nuevoCliente);
    archivo_clientes.close();
}

void SistemaDeVentas::EditarCliente() {
    ifstream archivo_cl(rutaClientes.c_str());
    if (!archivo_cl) {
        cout << "There aren´t any registered clients" << endl;
        GestionDeClientes();
    }
    else {
        clientes = SistemaDeVentas::leer_clientes();
    }
    int opc_cli_edit;
    cout << "Choose the client which information you would like to edit: " << endl;
    for (int i = 0; i < clientes.size(); i++) {
        cout << i + 1 << ".- " << clientes[i].getName() << endl;
    }
    cout << "Client to edit: "; cin >> opc_cli_edit;
    int var_edit;
    cout << "You are now editing " << clientes[opc_cli_edit - 1].getName() << "'s data. " << "\nChoose the variable to edit: ";
    cout << "\n1. Name" << "\n2. RFC" << "\n3. Address" << "\n4. City" << "\n5. State" << "\n6. Zipcode" << "\n7. Fiscal Regimen" << "\nOption: ";  cin >> var_edit;
    switch (var_edit) {
    case 1:
    {
        string new_name;
        cout << "Type the new name: "; cin.ignore(); getline(cin, new_name);
        clientes[opc_cli_edit - 1].setName(new_name);
        break;
    }
    case 2:
    {
        string new_rfc;
        cout << "Type the new RFC of " << clientes[opc_cli_edit - 1].getName() << ": "; cin.ignore(); getline(cin, new_rfc);
        clientes[opc_cli_edit - 1].setRFC(new_rfc);
        break;
    }
    case 3:
    {
        string new_address;
        cout << "Type the new address of " << clientes[opc_cli_edit - 1].getName() << ": "; cin.ignore(); getline(cin, new_address);
        clientes[opc_cli_edit - 1].setAddress(new_address);
        break;
    }
    case 4:
    {
        string new_city;
        cout << "Type the new city of " << clientes[opc_cli_edit - 1].getName() << ": "; cin.ignore(); getline(cin, new_city);
        clientes[opc_cli_edit - 1].setCity(new_city);
        break;
    }
    case 5:
    {
        string new_state;
        cout << "Type the new state of " << clientes[opc_cli_edit - 1].getName() << ": "; cin.ignore(); getline(cin, new_state);
        clientes[opc_cli_edit - 1].setState(new_state);
        break;
    }
    case 6:
    {
        string new_zipcode;
        cout << "Type the new zipcode of " << clientes[opc_cli_edit - 1].getName() << ": "; cin.ignore(); getline(cin, new_zipcode);
        clientes[opc_cli_edit - 1].setZipCode(new_zipcode);
        break;
    }
    case 7:
    {
        int opc_edit_reg;
        cout << "1. Edit Fiscal Regimen Code " << "\n2. Edit Fiscal Regimen Name" << "\nOption: "; cin >> opc_edit_reg;
        switch(opc_edit_reg){
            case 1:
            {
                int new_code;
                cout << "Type the new code: "; cin >> new_code;
                //clientes[opc_cli_edit-1].setCode(new_code);
                for (int j = 0; j < regimenesFiscales.size(); j++) {
                    if (clientes[opc_cli_edit-1].getID() == regimenesFiscales[j].getID()) {
                        regimenesFiscales[j].setCode(new_code);
                    }
                }
                Actualizar_Regimenes();
                break;
            }
            case 2:
            {
                string new_name;
                cout << "Type the new name: "; cin.ignore(); getline(cin , new_name);
                clientes[opc_cli_edit-1].RegimenFiscal::setName(new_name);
                for (int j = 0; j < regimenesFiscales.size(); j++) {
                    if (clientes[opc_cli_edit-1].getID() == regimenesFiscales[j].getID()) {
                        regimenesFiscales[j].setName(new_name);
                    }
                }
                Actualizar_Regimenes();
                break;
            }
            default:
            {
                cout << "Introduzca una opci—n v‡lida" << endl;
                break;
            }
        }
        break;
    }
    }
    Actualizar_Clientes();
}
void SistemaDeVentas::Actualizar_Regimenes(){
    ofstream archivo_regimenes(rutaRegimenesFiscales.c_str());
    for (int i  = 0; i < regimenesFiscales.size(); i++) {
        archivo_regimenes << regimenesFiscales[i].getID() << "," << regimenesFiscales[i].getCode() << "," << regimenesFiscales[i].getName() << endl;
    }
}
void SistemaDeVentas::VerClientes() {
    ifstream archivo_cl(rutaClientes.c_str());
    if (!archivo_cl) {
        cout << "There aren´t any registered clients" << endl;
        GestionDeClientes();
    }
    else {
        clientes = SistemaDeVentas::leer_clientes();
    }
    int opc_bus_cli;
    cout << "\nChoose an option: " << "\n1. See all Clients" << "\n2. Seacrh by name" << "\n3. Search by city" << "\n4. Search by state" << "\nOption: "; cin >> opc_bus_cli;
    vector <Clientes> aux_bus_cli;
    switch (opc_bus_cli) {
    case 1:
    {
        for (int i = 0; i < clientes.size(); i++) {
            cout << i + 1 << ".- " << clientes[i].getName() << ". ID: " << clientes[i].getID() << endl;
        }
        break;
    }
    case 2:
    {
        string name_bus; cout << "Type the client you are searching for: "; cin.ignore(); getline(cin, name_bus);
        for (int i = 0; i < clientes.size(); i++) {
            if (name_bus == clientes[i].getName()) {
                aux_bus_cli.push_back(clientes[i]);
            }
        }
        for (int j = 0; j < aux_bus_cli.size(); j++) {
            cout << j + 1 << ".- " << aux_bus_cli[j].getName() << ". ID: " << aux_bus_cli[j].getID() << endl;
        }
        break;
    }
    case 3:
    {
        string city_bus; cout << "Type the city where the client is located: "; cin.ignore(); getline(cin, city_bus);
        for (int i = 0; i < clientes.size(); i++) {
            if (city_bus == clientes[i].getCity()) {
                aux_bus_cli.push_back(clientes[i]);
            }
        }
        for (int j = 0; j < aux_bus_cli.size(); j++) {
            cout << j + 1 << ".- " << aux_bus_cli[j].getName() << ". City: " << aux_bus_cli[j].getCity() << endl;
        }
        break;
    }
    case 4:
    {
        string state_bus; cout << "Type the state where the client is located: "; cin.ignore(); getline(cin, state_bus);
        for (int i = 0; i < clientes.size(); i++) {
            if (state_bus == clientes[i].getState()) {
                aux_bus_cli.push_back(clientes[i]);
            }
        }
        for (int j = 0; j < aux_bus_cli.size(); j++) {
            cout << j + 1 << ".- " << aux_bus_cli[j].getName() << ". State: " << aux_bus_cli[j].getState() << endl;
        }
        break;
    }
    }
}

void SistemaDeVentas::EliminarCliente() {
    ifstream archivo_cl(rutaClientes.c_str());
    if (!archivo_cl) {
        cout << "There aren´t any registered clients" << endl;
        GestionDeClientes();
    }
    else {
        clientes = SistemaDeVentas::leer_clientes();
    }
    cout << "Choose the client you would like to delete: " << endl;
    for (int i = 0; i < clientes.size(); i++) {
        cout << i + 1 << ".-  " << clientes[i].getName() << ". ID: " << clientes[i].getID() << endl;
    }
    int opc_cli_del;
    cout << "Client to delete (type the ID): "; cin >> opc_cli_del;
    int band_cli_elim = 0;
    for (int j = 0; j < clientes.size(); j++) {
        if (opc_cli_del == clientes[j].getID()) {
            cout << "The client " << clientes[j].getName() << " has been succesfully deleted." << endl;
            clientes.erase(clientes.begin() + j);
            band_cli_elim = 1;
            break;
        }
    }
    if (band_cli_elim == 0) {
        cout << "Make sure to type correctly the ID of the client. " << endl;
    }
    Actualizar_Clientes();
}

void SistemaDeVentas::Actualizar_Clientes() {
    ofstream archivo_clientes(rutaClientes);
    for (int i = 0; i < clientes.size(); i++) {
        archivo_clientes << clientes[i].getName() << "," << clientes[i].getRFC() << "," << clientes[i].getAddress() << "," << clientes[i].getCity() << "," << clientes[i].getState() << "," << clientes[i].getZipCode() << "," << clientes[i].getID() << "," << clientes[i].RegimenFiscal::getID() << endl;
    }
    archivo_clientes.close();
}

vector<Clientes> SistemaDeVentas::leer_clientes() {
    vector<Clientes> clientes1;
    ifstream lectura_clientes(rutaClientes.c_str());
    string linea;
    while (getline(lectura_clientes, linea)) {
        string name, rfc, address, city, state, zipcode, name_reg_fis;
        int id_c, reg_fis_id, code_reg_fis;
        vector<string> carga_clientes;
        string parte;
        for (int i = 0; i < linea.size(); i++) {
            if (linea[i] == ',') {
                carga_clientes.push_back(parte);
                parte = "";
            }
            else {
                parte += linea[i];
            }
        }
        carga_clientes.push_back(parte);
        name = carga_clientes[0];
        rfc = carga_clientes[1];
        address = carga_clientes[2];
        city = carga_clientes[3];
        state = carga_clientes[4];
        zipcode = carga_clientes[5];
        reg_fis_id = stoi(carga_clientes[6]);
        id_c = stoi(carga_clientes[7]);
        regimenesFiscales = leer_regimenes_fiscales();
        for (int j = 0; j < regimenesFiscales.size(); j++) { //buscando el id en el objeto de regimenes para asignar los correctos
            if (reg_fis_id == regimenesFiscales[j].getID()) {
                code_reg_fis = regimenesFiscales[j].getCode();
                name_reg_fis = regimenesFiscales[j].getName();
            }
        }
        Clientes cliente_guardado = Clientes(id_c, name, rfc, reg_fis_id, address, city, state, zipcode, reg_fis_id, code_reg_fis, name_reg_fis);
        cliente_guardado.setID(id_c);
        cliente_guardado.setName(name);
        cliente_guardado.setRFC(rfc);
        cliente_guardado.setRegimenFiscalID(reg_fis_id);
        cliente_guardado.setAddress(address);
        cliente_guardado.setCity(city);
        cliente_guardado.setState(state);
        cliente_guardado.setZipCode(zipcode);
        clientes1.push_back(cliente_guardado);
    }
    return clientes1;
}
vector <RegimenFiscal> SistemaDeVentas::leer_regimenes_fiscales(){
    vector<RegimenFiscal> regimenes;
    ifstream lectura_regimenes(rutaRegimenesFiscales.c_str());
    string linea;
    while (getline(lectura_regimenes, linea)) {
        string nombre_reg;
        int id, cod;
        vector <string> carga_regimenes;
        string parte;
        for (int i = 0; i < linea.size(); i++) {
            if (linea[i] == ',') {
                carga_regimenes.push_back(parte);
                parte = "";
            }
            else{
                parte += linea[i];
            }
        }
        carga_regimenes.push_back(parte);
        id = stoi(carga_regimenes[0]);
        cod = stoi(carga_regimenes[1]);
        nombre_reg = carga_regimenes[2];
        RegimenFiscal traslado_regimen = RegimenFiscal(id, cod, nombre_reg);
        traslado_regimen.setID(id);
        traslado_regimen.setCode(cod);
        traslado_regimen.setName(nombre_reg);
        regimenes.push_back(traslado_regimen);
    }
    return regimenes;
}
void SistemaDeVentas::GestionDeVentas()
{
	int opcionGV = 0;
	do {
		LimpiarPantalla();
		cout << "Bienvenido al menœ de Ventas" << endl;
		cout << "1. Agregar Venta" << endl
			<< "2. Ver Ventas" << endl
			<< "3. Return" << endl
			<< "Opción elegida: ";
		cin >> opcionGV;
		switch (opcionGV) {
		case 1:
		{
            RegistroDeActividad("Agregar Venta");
			AgregarVenta();
			break;
		}
		case 2:
		{
            RegistroDeActividad("Ver Ventas");
			VerVentas();
			break;
		}
		case 3:
		{
			break;
		}
		default:
		{
			LimpiarPantalla();
			cout << "Seleccione una opción válida" << endl;
			PausaConEnter();
			break;
		}
		}
	} while (opcionGV != 3);
}

void SistemaDeVentas::AgregarVenta()
{

}

void SistemaDeVentas::VerVentas()
{

}

void SistemaDeVentas::GestionDeInformes()
{
    switch (usuarioActual->getRoleInt())
    {
    case ADMIN:
        MenuInformesAdministrador();
        break;
    case VENDEDOR:
        MenuInformesVendedor();
        break;
    case RH:
		MenuInformesRH();
		break;
    case ALMACEN:
        MenuInformesAlmacen(); 
        break;
    default:
        LimpiarPantalla();
        cout << "No tiene permisos para acceder a este menú" << endl;
        PausaConEnter();
        break;
    }
}

void SistemaDeVentas::MenuInformesAdministrador()
{
    int opcionGI = 0;
    do {
        LimpiarPantalla();
        cout << "Bienvenido al menú de Informes" << endl;
        cout << "1. Informe de Ventas" << endl
            << "2. Informe de Inventarios" << endl
            << "3. Informe de Actividad de Usuarios" << endl
            << "4. Return" << endl
            << "Opción elegida: ";
        cin >> opcionGI;
        switch (opcionGI) {
        case 1:
        {
            RegistroDeActividad("Informe de Ventas");
            InformeDeVentas();
            break;
        }
        case 2:
        {
            RegistroDeActividad("Informe de Inventarios");
            InformeDeInventarios();
            break;
        }
        case 3:
        {
            RegistroDeActividad("Informe de Actividad de Usuarios");
            InfromesDeActividadDeUsuarios();
            break;
        }
        case 4:
        {
            break;
        }
        default:
        {
            LimpiarPantalla();
            cout << "Seleccione una opción válida" << endl;
            PausaConEnter();
            break;
        }
        }
    } while (opcionGI != 4);
}

void SistemaDeVentas::MenuInformesVendedor()
{
	int opcionGI = 0;
	do {
		LimpiarPantalla();
		cout << "Bienvenido al menú de Informes" << endl;
		cout << "1. Informe de Ventas" << endl
			<< "2. Return" << endl
			<< "Opción elegida: ";
		cin >> opcionGI;
		switch (opcionGI) {
		case 1:
		{
			RegistroDeActividad("Informe de Ventas");
			InformeDeVentas();
			break;
		}
		case 2:
		{
			break;
		}
		default:
		{
			LimpiarPantalla();
			cout << "Seleccione una opción válida" << endl;
			PausaConEnter();
			break;
		}
		}
	} while (opcionGI != 2);
}

void SistemaDeVentas::MenuInformesRH()
{
    int opcionGI = 0;
	do {
		LimpiarPantalla();
		cout << "Bienvenido al menú de Informes" << endl;
		cout << "1. Informe de Actividad de Usuarios" << endl
			<< "2. Return" << endl
			<< "Opción elegida: ";
		cin >> opcionGI;
		switch (opcionGI) {
		case 1:
		{
			RegistroDeActividad("Informe de Actividad de Usuarios");
			InfromesDeActividadDeUsuarios();
			break;
		}
		case 2:
		{
			break;
		}
		default:
		{
			LimpiarPantalla();
			cout << "Seleccione una opción válida" << endl;
			PausaConEnter();
			break;
		}
		}
	} while (opcionGI != 2);
}

void SistemaDeVentas::MenuInformesAlmacen()
{
    int opcionGI = 0;
	do {
		LimpiarPantalla();
		cout << "Bienvenido al menú de Informes" << endl;
		cout << "1. Informe de Inventarios" << endl
			<< "2. Return" << endl
			<< "Opción elegida: ";
		cin >> opcionGI;
		switch (opcionGI) {
		case 1:
		{
			RegistroDeActividad("Informe de Inventarios");
			InformeDeInventarios();
			break;
		}
		case 2:
		{
			break;
		}
		default:
		{
			LimpiarPantalla();
			cout << "Seleccione una opción válida" << endl;
			PausaConEnter();
			break;
		}
		}
	} while (opcionGI != 2);
}

void SistemaDeVentas::InformeDeVentas()
{
}

void SistemaDeVentas::InformeDeInventarios()
{
}

void SistemaDeVentas::InfromesDeActividadDeUsuarios()
{
	vector<RegistroDeActividadUser> registros = leerRegistrosUsuarios();
    int opc_inf;
    do{
		LimpiarPantalla();
		cout << "Bienvenido al menú de Informes de Actividad de Usuarios" << endl;
		cout << "1. Filter by User" << endl
            << "2. Filter by Action" << endl
            << "3. Filter by Date" << endl
            << "4. Show all" << endl
			<< "5. Return" << endl
			<< "Opción elegida: ";
		cin >> opc_inf;
        switch (opc_inf)
        {
        case 1:
        {
            bool band = false;
            int id_user;
            cout << "Type the ID of the user: "; cin >> id_user;
            for (int i = 0; i < registros.size(); i++)
            {
                if (registros[i].ID_user == id_user)
                {
                    band = true;
                    cout << "ID Usuario: " << registros[i].ID_user << " Acción: " << registros[i].action << " Fecha: " << registros[i].date.year << "/" << registros[i].date.month << "/" << registros[i].date.day << " Hora: " << registros[i].date.hour << ":" << registros[i].date.minute << ":" << registros[i].date.second << endl;
                }
            }
            if (!band)
			{
				cout << "No hay registros de actividad de usuarios con el ID " << id_user << endl;
			}
            PausaConEnter();
            break;
        }
        case 2:
        {
            InformeFiltroPorAccion(registros);
            break;
        }
        case 3:
        {
            int year, month, day;
            bool band = false;
            cout << "Type the year: "; cin >> year;
            cout << "Type the month: "; cin >> month;
            cout << "Type the day: "; cin >> day;
            for (int i = 0; i < registros.size(); i++)
            {
                if (registros[i].date.year == year && registros[i].date.month == month && registros[i].date.day == day)
                {
                    band = true;
                    cout << "ID Usuario: " << registros[i].ID_user << " Acción: " << registros[i].action << " Fecha: " << registros[i].date.year << "/" << registros[i].date.month << "/" << registros[i].date.day << " Hora: " << registros[i].date.hour << ":" << registros[i].date.minute << ":" << registros[i].date.second << endl;
                }
            }
            if (!band) {
                cout << "No hay registros de actividad de usuarios en la fecha " << year << "/" << month << "/" << day << endl;
            }
            PausaConEnter();
            break;
        }
        case 4:
            for (int i = 0; i < registros.size(); i++)
            {
                cout << "ID Usuario: " << registros[i].ID_user << " Acción: " << registros[i].action << " Fecha: " << registros[i].date.year << "/" << registros[i].date.month << "/" << registros[i].date.day << " Hora: " << registros[i].date.hour << ":" << registros[i].date.minute << ":" << registros[i].date.second << endl;
            }
       		PausaConEnter();
			break;
        }
	} while (opc_inf != 5);
}

void SistemaDeVentas::InformeFiltroPorAccion(vector<RegistroDeActividadUser>& registros)
{
    int opc_action = 0;
    string action;
    while (opc_action != 17) {
        cout << "Seleccione la acción por la que desea filtrar: " << endl
            << "1. Creacion de Usuario" << endl
            << "2. Editar Usuario" << endl
            << "3. Eliminar Usuario" << endl
            << "4. Agregar Producto" << endl
            << "5. Editar Producto" << endl
            << "6. Ver Productos" << endl
            << "7. Eliminar Producto" << endl
            << "8. Agregar Cliente" << endl
            << "9. Editar Cliente" << endl
            << "10. Ver Clientes" << endl
            << "11. Eliminar Cliente" << endl
            << "12. Agregar Venta" << endl
            << "13. Ver Ventas" << endl
            << "14. Informe de Ventas" << endl
            << "15. Informe de Inventarios" << endl
            << "16. Informe de Actividad de Usuarios" << endl
            << "17. Return" << endl
            << "Opción elegida: ";
        cin >> opc_action;
        switch (opc_action)
		{
        case 1:
        { action = "Creacion de Usuario"; break; }
        case 2:
		{ action = "Editar Usuario"; break; }
		case 3:
		{ action = "Eliminar Usuario"; break; }
		case 4:
		{ action = "Agregar Producto"; break; }
		case 5:
		{ action = "Editar Producto"; break; }
        case 6:
		{ action = "Ver Productos"; break; }
		case 7:
        { action = "Eliminar Producto"; break; }
        case 8:
		{ action = "Agregar Cliente"; break; }
		case 9:
		{ action = "Editar Cliente"; break; }
		case 10:
		{ action = "Ver Clientes"; break; }
		case 11:
		{ action = "Eliminar Cliente"; break; }
		case 12:
		{ action = "Agregar Venta"; break; }
        case 13:
        { action = "Ver Ventas"; break; }
		case 14:
		{ action = "Informe de Ventas"; break; }
		case 15:
		{ action = "Informe de Inventarios"; break; }
		case 16:
		{ action = "Informe de Actividad de Usuarios"; break; }
		case 17:
		{break;}
		}
        bool band = false;
        for (int i = 0; i < registros.size(); i++)
        {
            if (registros[i].action == action)
            {
                cout << "ID Usuario: " << registros[i].ID_user << " Acción: " << registros[i].action << " Fecha: " << registros[i].date.year << "/" << registros[i].date.month << "/" << registros[i].date.day << " Hora: " << registros[i].date.hour << ":" << registros[i].date.minute << ":" << registros[i].date.second << endl;
        	    band = true;
            }
        }
        if (!band)
	    {
		    cout << "No hay registros de actividad de usuarios con la acción " << action << endl;
	    }
	    PausaConEnter();
	}
}

void SistemaDeVentas::RegistroDeActividad(string action)
{
    ifstream archivoLeido(rutaUsuarios.c_str());
    if (!archivoLeido) {
        ofstream archivo;
        archivo.open(rutaUsuarios.c_str(), fstream::out);
        archivo << "";
        archivo.close();
        EscribirRegistro(action);
    }
    else
    {
        EscribirRegistro(action);
    }
}

void SistemaDeVentas::EscribirRegistro(string actionER)
{
    ofstream archivo;
    archivo.open(rutaRegistrosUsuarios.c_str(), fstream::app);
    DateTime dateOfAction = ConvertirFechaADateTime();
    archivo << usuarioActual->getId() << "," << dateOfAction.year << "," << dateOfAction.month << ","
        << dateOfAction.day << "," << dateOfAction.hour << "," << dateOfAction.minute << ","
        << dateOfAction.second << "," << actionER << endl;
    archivo.close();
}

vector<RegistroDeActividadUser> SistemaDeVentas::leerRegistrosUsuarios()
{
    vector<RegistroDeActividadUser> registros;
    ifstream lectura_archivo(rutaRegistrosUsuarios.c_str());
    string linea;
    if(!lectura_archivo)
	{
		cout << "No hay registros de actividad de usuarios" << endl;
	}
	else
	{
		while (getline(lectura_archivo, linea))
		{
			string parte;
			vector<string> carga_registros;
			for (int i = 0; i < linea.size(); i++)
			{
				if (linea[i] == ',')
				{
					carga_registros.push_back(parte);
					parte = "";
				}
				else
				{
					parte += linea[i];
				}
			}
			carga_registros.push_back(parte);
			int id_user = stoi(carga_registros[0]);
            DateTime dateOfAction = DateTime{ stoi(carga_registros[1]), stoi(carga_registros[2]), stoi(carga_registros[3]), stoi(carga_registros[4]), stoi(carga_registros[5]), stoi(carga_registros[6]) };
			string action = carga_registros[7];
            RegistroDeActividadUser registro = RegistroDeActividadUser{ id_user, action, dateOfAction };
			registros.push_back(registro);
		}
	}
    return registros;
}

DateTime SistemaDeVentas::ConvertirFechaADateTime()
{
    DateTime dateAux;
    time_t now = time(0);
    tm localTime;
    //localtime_s(&localTime, &now);
    dateAux.year = 1900 + localTime.tm_year;
    dateAux.month = 1 + localTime.tm_mon;
    dateAux.day = localTime.tm_mday;
    dateAux.hour = localTime.tm_hour;
    dateAux.minute = localTime.tm_min;
    dateAux.second = localTime.tm_sec;
    return dateAux;
}

void SistemaDeVentas::PausaConEnter()
{
    cout << "Presione enter para continuar...";
    cin.ignore();
    cin.get();
}

void SistemaDeVentas::LimpiarPantalla()
{
    system("cls");
}
