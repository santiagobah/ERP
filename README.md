
# ERP

### Archivos CSV
El sistema utiliza varios archivos CSV para almacenar datos:

- `./Scr/Usuarios.csv`: Información de usuarios.
- `./Scr/Clientes.csv`: Información de clientes.
- `./Scr/Productos.csv`: Información de productos.
- `./Scr/Ventas.csv`: Información de ventas.
- `./Scr/ProductosVendidos.csv`: Información de productos vendidos.
- `./Scr/Presentaciones.csv`: Información de presentaciones de productos.
- `./Scr/RegimenesFiscales.csv`: Información de regímenes fiscales.
- `./Scr/RegistrosUsuarios.csv`: Información de registros de usuarios.

### Inicialización del Sistema
Para inicializar el sistema, asegúrese de que todos los archivos CSV mencionados anteriormente estén en la ubicación correcta. La ruta por defecto es `./Scr/`.

## Guía del Usuario

### Menú Inicial

El menú inicial presenta las siguientes opciones:

1. Iniciar Sesión
2. Salir del Sistema

### Iniciar Sesión

Permite al usuario ingresar sus credenciales para acceder al sistema. Si es la primera vez que se ejecuta el sistema, se creará un usuario administrador por defecto.

### Menú Principal

El menú principal varía según el rol del usuario:

- **Administrador**:
  - Gestión de Usuarios
  - Gestión de Clientes
  - Gestión de Productos
  - Gestión de Ventas
  - Gestión de Informes

- **Vendedor**:
  - Gestión de Clientes
  - Gestión de Ventas
  - Gestión de Informes

- **Recursos Humanos (RH)**:
  - Gestión de Usuarios
  - Gestión de Clientes
  - Gestión de Informes

- **Almacén**:
  - Gestión de Productos
  - Gestión de Informes

### Funcionalidades del Sistema

#### Gestión de Usuarios

Permite agregar, editar y eliminar usuarios.

#### Gestión de Clientes

Permite agregar, editar, ver y eliminar clientes.

#### Gestión de Productos

Permite agregar, editar, ver y eliminar productos.

#### Gestión de Ventas

Permite agregar y ver ventas.

#### Gestión de Informes

Genera informes sobre ventas, inventarios y actividades de usuarios.

## Descripción Detallada de las Funcionalidades del Sistema

### Métodos del Sistema

#### `SistemaDeVentas::SistemaDeVentas()`
Constructor de la clase. Inicializa las rutas de los archivos CSV y establece el usuario actual como `nullptr`.

**Detalles:**
- Inicializa las rutas de los archivos CSV donde se almacenan los datos del sistema.
- Establece `usuarioActual` como `nullptr`, lo que indica que no hay ningún usuario logueado al iniciar el sistema.

#### `SistemaDeVentas::~SistemaDeVentas()`
Destructor de la clase. Libera la memoria asignada al usuario actual.

**Detalles:**
- Libera la memoria asignada al objeto `usuarioActual` para evitar fugas de memoria cuando el objeto `SistemaDeVentas` es destruido.

#### `void SistemaDeVentas::MenuInicial()`
Muestra el menú inicial al usuario y permite seleccionar entre iniciar sesión o salir del sistema.

**Detalles:**
- Limpia la pantalla antes de mostrar el menú.
- Muestra opciones para iniciar sesión o salir del sistema.
- Captura la opción seleccionada por el usuario y llama a los métodos correspondientes (`IniciarSesion` o salir).

#### `void SistemaDeVentas::IniciarSesion()`
Muestra la pantalla de inicio de sesión, valida las credenciales del usuario y, si es la primera vez que se ejecuta el sistema, crea un usuario administrador por defecto.

**Detalles:**
- Limpia la pantalla y abre el archivo `Usuarios.csv`.
- Si el archivo no existe, lo crea y añade un usuario administrador por defecto.
- Carga los usuarios del archivo a un vector de usuarios.
- Llama al método `ValidacionDeCredenciales` para validar el inicio de sesión.

#### `void SistemaDeVentas::ValidacionDeCredenciales()`
Valida las credenciales del usuario ingresadas en la pantalla de inicio de sesión. Permite hasta tres intentos antes de bloquear el acceso.

**Detalles:**
- Solicita el nombre de usuario y la contraseña.
- Compara las credenciales ingresadas con las almacenadas en el vector de usuarios.
- Si las credenciales son válidas, establece `usuarioActual` y llama al `MenuPrincipal`.
- Si las credenciales son inválidas, permite hasta tres intentos antes de cerrar el sistema.

#### `vector<Usuarios> SistemaDeVentas::LeerUsuarios()`
Lee los datos de los usuarios desde el archivo CSV y los almacena en un vector de objetos `Usuarios`.

**Detalles:**
- Abre el archivo `Usuarios.csv` en modo lectura.
- Lee cada línea del archivo y separa los atributos usando comas como delimitadores.
- Crea objetos `Usuarios` con los datos leídos y los añade a un vector.
- Devuelve el vector de usuarios.

#### `void SistemaDeVentas::MenuPrincipal()`
Muestra el menú principal basado en el rol del usuario actual.

**Detalles:**
- Determina el rol del `usuarioActual` y llama al menú correspondiente:
  - `MenuAdministrador`
  - `MenuVendedor`
  - `MenuRH`
  - `MenuAlmacen`

#### `void SistemaDeVentas::MenuAdministrador()`
Muestra el menú principal para el rol de administrador, permitiendo la gestión de usuarios, clientes, productos, ventas e informes.

**Detalles:**
- Muestra opciones específicas para el rol de administrador.
- Permite al administrador gestionar usuarios, clientes, productos, ventas e informes.
- Llama a los métodos correspondientes basados en la opción seleccionada por el usuario.

#### `void SistemaDeVentas::MenuVendedor()`
Muestra el menú principal para el rol de vendedor, permitiendo la gestión de clientes, ventas e informes.

**Detalles:**
- Muestra opciones específicas para el rol de vendedor.
- Permite al vendedor gestionar clientes, ventas e informes.
- Llama a los métodos correspondientes basados en la opción seleccionada por el usuario.

#### `void SistemaDeVentas::MenuRH()`
Muestra el menú principal para el rol de Recursos Humanos, permitiendo la gestión de usuarios, clientes e informes.

**Detalles:**
- Muestra opciones específicas para el rol de Recursos Humanos.
- Permite al usuario de RH gestionar usuarios, clientes e informes.
- Llama a los métodos correspondientes basados en la opción seleccionada por el usuario.

#### `void SistemaDeVentas::MenuAlmacen()`
Muestra el menú principal para el rol de almacén, permitiendo la gestión de productos e informes.

**Detalles:**
- Muestra opciones específicas para el rol de almacén.
- Permite al usuario de almacén gestionar productos e informes.
- Llama a los métodos correspondientes basados en la opción seleccionada por el usuario.

#### `void SistemaDeVentas::GestionDeUsuarios()`
Permite agregar, editar y eliminar usuarios.

**Detalles:**
- Muestra un menú con opciones para agregar, editar y eliminar usuarios.
- Llama a los métodos `AgregarUsuario`, `EditarUsuario` y `EliminarUsuario` según la opción seleccionada.

#### `void SistemaDeVentas::AgregarUsuario()`
Agrega un nuevo usuario al sistema. Solicita el nombre, apellido, nombre de usuario, contraseña y rol del nuevo usuario.

**Detalles:**
- Solicita al usuario administrador los detalles del nuevo usuario.
- Asigna un ID único al nuevo usuario.
- Crea un objeto `Usuarios` con los detalles proporcionados.
- Añade el nuevo usuario al vector de usuarios y lo guarda en el archivo `Usuarios.csv`.

#### `void SistemaDeVentas::EditarUsuario()`
Edita los datos de un usuario existente. Permite modificar el nombre, apellido, nombre de usuario, contraseña y rol del usuario.

**Detalles:**
- Muestra una lista de usuarios para seleccionar cuál editar.
- Solicita la nueva información del usuario seleccionado.
- Actualiza los detalles del usuario en el vector de usuarios y guarda los cambios en el archivo `Usuarios.csv`.

#### `void SistemaDeVentas::EliminarUsuario()`
Elimina un usuario existente del sistema.

**Detalles:**
- Muestra una lista de usuarios para seleccionar cuál eliminar.
- Solicita confirmación antes de eliminar al usuario seleccionado.
- Elimina el usuario del vector y actualiza el archivo `Usuarios.csv`.

#### `void SistemaDeVentas::GestionDeClientes()`
Permite agregar, editar, ver y eliminar clientes.

**Detalles:**
- Muestra un menú con opciones para agregar, editar, ver y eliminar clientes.
- Llama a los métodos `AgregarCliente`, `EditarCliente`, `VerClientes` y `EliminarCliente` según la opción seleccionada.

#### `void SistemaDeVentas::AgregarCliente()`
Agrega un nuevo cliente al sistema. Solicita el nombre, RFC, dirección, ciudad, estado, código postal y régimen fiscal del cliente.

**Detalles:**
- Solicita los detalles del nuevo cliente.
- Asigna un ID único al nuevo cliente.
- Crea un objeto `Clientes` con los detalles proporcionados.
- Añade el nuevo cliente al vector de clientes y lo guarda en el archivo `Clientes.csv`.

#### `void SistemaDeVentas::EditarCliente()`
Edita los datos de un cliente existente. Permite modificar el nombre, RFC, dirección, ciudad, estado, código postal y régimen fiscal.

**Detalles:**
- Muestra una lista de clientes para seleccionar cuál editar.
- Solicita la nueva información del cliente seleccionado.
- Actualiza los detalles del cliente en el vector de clientes y guarda los cambios en el archivo `Clientes.csv`.

#### `void SistemaDeVentas::EliminarCliente()`
Elimina un cliente existente del sistema.

**Detalles:**
- Muestra una lista de clientes para seleccionar cuál eliminar.
- Solicita confirmación antes de eliminar al cliente seleccionado.
- Elimina el cliente del vector y actualiza el archivo `Clientes.csv`.

#### `void SistemaDeVentas::GestionDeProductos()`
Permite agregar, editar, ver y eliminar productos.

**Detalles:**
- Muestra un menú con opciones para agregar, editar, ver y eliminar productos.
- Llama a los métodos `AgregarProducto`, `EditarProducto`, `VerProductos` y `EliminarProducto` según la opción seleccionada.

#### `void SistemaDeVentas::AgregarProducto()`
Agrega un nuevo producto al sistema. Solicita el nombre, UPC, precio, costo, IVA y stock del producto.

**Detalles:**
- Solicita los detalles del nuevo producto.
- Asigna un ID único al nuevo producto.
- Crea un objeto `Productos` con los detalles proporcionados.
- Añade el nuevo producto al vector de productos y lo guarda en el archivo `Productos.csv`.

#### `void SistemaDeVentas::EditarProducto()`
Edita los datos de un producto existente. Permite modificar el nombre, precio, costo, IVA, stock y nombre de la presentación.

**Detalles:**
- Muestra una lista de productos para seleccionar cuál editar.
- Solicita la nueva información del producto seleccionado.
- Actualiza los detalles del producto en el vector de productos y guarda los cambios en el archivo `Productos.csv`.

#### `void SistemaDeVentas::EliminarProducto()`
Elimina un producto existente del sistema.

**Detalles:**
- Muestra una lista de productos para seleccionar cuál eliminar.
- Solicita confirmación antes de eliminar el producto seleccionado.
- Elimina el producto del vector y actualiza el archivo `Productos.csv`.

#### `void SistemaDeVentas::GestionDeVentas()`
Permite agregar y ver ventas.

**Detalles:**
- Muestra un menú con opciones para agregar y ver ventas.
- Llama a los métodos `AgregarVenta` y `VerVentas` según la opción seleccionada.

#### `void SistemaDeVentas::AgregarVenta()`
Registra una nueva venta escaneando los códigos UPC de los productos vendidos. El total de la compra se calcula automáticamente.

**Detalles:**
- Solicita al usuario que seleccione un cliente para la venta.
- Permite escanear productos, calculando y mostrando el total de la venta en tiempo real.
- Guarda los detalles de la venta en el vector de ventas y en el archivo `Ventas.csv`.
- Guarda los detalles de los productos vendidos en el vector de productos vendidos y en el archivo `ProductosVendidos.csv`.

#### `void SistemaDeVentas::VerVentas()`
Permite visualizar todas las ventas registradas, con opciones para filtrar por fecha, cliente y vendedor.

**Detalles:**
- Muestra un menú con opciones para ver todas las ventas o filtrar por fecha, cliente o vendedor.
- Muestra los detalles de las ventas según el filtro seleccionado.

#### `void SistemaDeVentas::GestionDeInformes()`
Genera informes sobre ventas, inventarios y actividades de usuarios. El menú de informes varía según el rol del usuario actual.

**Detalles:**
- Determina el rol del `usuarioActual` y llama al menú de informes correspondiente:
  - `MenuInformesAdministrador`
  - `MenuInformesVendedor`
  - `MenuInformesRH`
  - `MenuInformesAlmacen`

#### `void SistemaDeVentas::MenuInformesAdministrador()`
Muestra el menú de informes para el rol de administrador, permitiendo la generación de informes de ventas, inventarios y actividades de usuarios.

**Detalles:**
- Muestra un menú con opciones para generar informes de ventas, inventarios y actividades de usuarios.
- Llama a los métodos `InformeDeVentas`, `InformeDeInventarios` y `InfromesDeActividadDeUsuarios` según la opción seleccionada.

#### `void SistemaDeVentas::MenuInformesVendedor()`
Muestra el menú de informes para el rol de vendedor, permitiendo la generación de informes de ventas.

**Detalles:**
- Muestra un menú con opciones para generar informes de ventas.
- Llama al método `InformeDeVentas` según la opción seleccionada.

#### `void SistemaDeVentas::MenuInformesRH()`
Muestra el menú de informes para el rol de Recursos Humanos, permitiendo la generación de informes de actividades de usuarios.

**Detalles:**
- Muestra un menú con opciones para generar informes de actividades de usuarios.
- Llama al método `InfromesDeActividadDeUsuarios` según la opción seleccionada.

#### `void SistemaDeVentas::MenuInformesAlmacen()`
Muestra el menú de informes para el rol de almacén, permitiendo la generación de informes de inventarios.

**Detalles:**
- Muestra un menú con opciones para generar informes de inventarios.
- Llama al método `InformeDeInventarios` según la opción seleccionada.

#### `void SistemaDeVentas::InformeDeVentas()`
Genera un informe detallado de las ventas registradas en el sistema.

**Detalles:**
- Lee los datos de las ventas desde el archivo `Ventas.csv`.
- Muestra un informe detallado de todas las ventas registradas, con opciones para filtrar por fecha, cliente y vendedor.

#### `void SistemaDeVentas::InformeDeInventarios()`
Genera un informe detallado del inventario de productos.

**Detalles:**
- Lee los datos de los productos desde el archivo `Productos.csv`.
- Muestra un informe detallado del inventario actual, incluyendo información sobre stock, precios y costos.

#### `void SistemaDeVentas::InfromesDeActividadDeUsuarios()`
Genera un informe detallado de las actividades de los usuarios en el sistema.

**Detalles:**
- Lee los registros de actividad desde el archivo `RegistrosUsuarios.csv`.
- Muestra un informe detallado de todas las actividades registradas, con opciones para filtrar por usuario, acción y fecha.

#### `void SistemaDeVentas::RegistroDeActividad(string action)`
Registra la actividad de un usuario en el sistema.

**Detalles:**
- Crea un registro de actividad para la acción realizada por el usuario actual.
- Guarda el registro en el archivo `RegistrosUsuarios.csv`.

#### `void SistemaDeVentas::EscribirRegistro(string actionER)`
Escribe un registro de actividad en el archivo CSV correspondiente.

**Detalles:**
- Abre el archivo `RegistrosUsuarios.csv` en modo append.
- Escribe un registro de actividad con el ID del usuario, la fecha y hora de la acción, y la descripción de la acción.
- Cierra el archivo.

#### `vector<RegistroDeActividadUser> SistemaDeVentas::leerRegistrosUsuarios()`
Lee los registros de actividad de usuarios desde el archivo CSV y los almacena en un vector de objetos `RegistroDeActividadUser`.

**Detalles:**
- Abre el archivo `RegistrosUsuarios.csv` en modo lectura.
- Lee cada línea del archivo y separa los atributos usando comas como delimitadores.
- Crea objetos `RegistroDeActividadUser` con los datos leídos y los añade a un vector.
- Devuelve el vector de registros de actividad.

#### `DateTime SistemaDeVentas::ConvertirFechaADateTime()`
Convierte la fecha y hora actual a un objeto `DateTime`.

**Detalles:**
- Obtiene la fecha y hora actual del sistema.
- Crea un objeto `DateTime` con la fecha y hora actual.
- Devuelve el objeto `DateTime`.

#### `void SistemaDeVentas::PausaConEnter()`
Pausa la ejecución del programa hasta que el usuario presione Enter.

**Detalles:**
- Muestra un mensaje solicitando al usuario que presione Enter para continuar.
- Espera a que el usuario presione Enter antes de continuar la ejecución del programa.

#### `void SistemaDeVentas::LimpiarPantalla()`
Limpia la pantalla de la consola.

**Detalles:**
- Ejecuta un comando del sistema para limpiar la pantalla de la consola.
- Utiliza el comando `cls` en sistemas Windows.

#### `vector<Productos> SistemaDeVentas::leer_productos()`
Lee los datos de los productos desde el archivo CSV y los almacena en un vector de objetos `Productos`.

**Detalles:**
- Abre el archivo `Productos.csv` en modo lectura.
- Lee cada línea del archivo y separa los atributos usando comas como delimitadores.
- Crea objetos `Productos` con los datos leídos y los añade a un vector.
- Devuelve el vector de productos.

#### `vector<Presentacion> SistemaDeVentas::leer_presentaciones()`
Lee los datos de las presentaciones desde el archivo CSV y los almacena en un vector de objetos `Presentacion`.

**Detalles:**
- Abre el archivo `Presentaciones.csv` en modo lectura.
- Lee cada línea del archivo y separa los atributos usando comas como delimitadores.
- Crea objetos `Presentacion` con los datos leídos y los añade a un vector.
- Devuelve el vector de presentaciones.

#### `vector<ProductosVendidos> SistemaDeVentas::LeerProductosVendidos()`
Lee los datos de los productos vendidos desde el archivo CSV y los almacena en un vector de objetos `ProductosVendidos`.

**Detalles:**
- Abre el archivo `ProductosVendidos.csv` en modo lectura.
- Lee cada línea del archivo y separa los atributos usando comas como delimitadores.
- Crea objetos `ProductosVendidos` con los datos leídos y los añade a un vector.
- Devuelve el vector de productos vendidos.

#### `void SistemaDeVentas::Actualizar_Productos_Vendidos()`
Actualiza los datos de los productos vendidos en el archivo CSV.

**Detalles:**
- Abre el archivo `ProductosVendidos.csv` en modo escritura.
- Escribe los datos de los productos vendidos almacenados en el vector en el archivo CSV.
- Cierra el archivo.

#### `void SistemaDeVentas::Actualizar_Productos()`
Actualiza los datos de los productos en el archivo CSV.

**Detalles:**
- Abre el archivo `Productos.csv` en modo escritura.
- Escribe los datos de los productos almacenados en el vector en el archivo CSV.
- Cierra el archivo.

#### `void SistemaDeVentas::Actualizar_Presentaciones()`
Actualiza los datos de las presentaciones en el archivo CSV.

**Detalles:**
- Abre el archivo `Presentaciones.csv` en modo escritura.
- Escribe los datos de las presentaciones almacenadas en el vector en el archivo CSV.
- Cierra el archivo.

#### `void SistemaDeVentas::Actualizar_Clientes()`
Actualiza los datos de los clientes en el archivo CSV.

**Detalles:**
- Abre el archivo `Clientes.csv` en modo escritura.
- Escribe los datos de los clientes almacenados en el vector en el archivo CSV.
- Cierra el archivo.

#### `vector<Clientes> SistemaDeVentas::leer_clientes()`
Lee los datos de los clientes desde el archivo CSV y los almacena en un vector de objetos `Clientes`.

**Detalles:**
- Abre el archivo `Clientes.csv` en modo lectura.
- Lee cada línea del archivo y separa los atributos usando comas como delimitadores.
- Crea objetos `Clientes` con los datos leídos y los añade a un vector.
- Devuelve el vector de clientes.

#### `vector<RegimenFiscal> SistemaDeVentas::leer_regimenes_fiscales()`
Lee los datos de los regímenes fiscales desde el archivo CSV y los almacena en un vector de objetos `RegimenFiscal`.

**Detalles:**
- Abre el archivo `RegimenesFiscales.csv` en modo lectura.
- Lee cada línea del archivo y separa los atributos usando comas como delimitadores.
- Crea objetos `RegimenFiscal` con los datos leídos y los añade a un vector.
- Devuelve el vector de regímenes fiscales.

#### `vector<Ventas> SistemaDeVentas::LeerVentas()`
Lee los datos de las ventas desde el archivo CSV y los almacena en un vector de objetos `Ventas`.

**Detalles:**
- Abre el archivo `Ventas.csv` en modo lectura.
- Lee cada línea del archivo y separa los atributos usando comas como delimitadores.
- Crea objetos `Ventas` con los datos leídos y los añade a un vector.
- Devuelve el vector de ventas.

#### `void SistemaDeVentas::InformeFiltroPorAccion(vector<RegistroDeActividadUser>& registros)`
Filtra los registros de actividad por acción y muestra los resultados.

**Detalles:**
- Muestra un menú con opciones para filtrar por diferentes tipos de acciones (e.g., creación de usuario, edición de producto, etc.).
- Filtra los registros de actividad basados en la acción seleccionada.
- Muestra los registros filtrados.

#### `void SistemaDeVentas::Actualizar_Regimenes()`
Actualiza los datos de los regímenes fiscales en el archivo CSV.

**Detalles:**
- Abre el archivo `RegimenesFiscales.csv` en modo escritura.
- Escribe los datos de los regímenes fiscales almacenados en el vector en el archivo CSV.
- Cierra el archivo.
