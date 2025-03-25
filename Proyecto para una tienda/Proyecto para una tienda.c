#include <stdio.h> //Con esta librería permitimos funciones estándar de entrada y salida
#include <stdlib.h>//Esta librería se usa para funciones malloc y fre (las cuales he trabajado por primera vez en este código)

typedef struct { //Con esta estructura definimos las distintas estructuras que tendrá un producto
    char Nombre_producto[30];
    int codigo_barras;
    int cantidad;
    float precio;
} Producto;

int Pedir_cantidad();//Aquí declararemos distintas funciones que se usarán más adelante.Aquí también usé por primera vez funciones aisladas como void
Producto Agregar_producto();//Todas estas funciones han sido declaradas aquí, antes de la función principal del código. En principio sería un problema ya que no las he definido antes del código, pero al haberlas declarado aquí, puedo definirlas después de la parte principal del código
void Mostrar_productos(Producto* productos, int Num_productos);
void Mostrar_producto(Producto* productos, int posicion);
int Busqueda(Producto* productos, int Codigo, int contador);
void Comprar_producto(Producto* productos, int posicion);

int main() {//Función principal del código en la que llamaremos a las funciones que se han definido más adelante
    int Num_productos, eleccion = 0, contador_productos = 0;//Definimos variables para usar en el código

    Num_productos = Pedir_cantidad();//Llamamos la función para que el usuario ingrese cúantos productos manejará
    printf("Has elegido manejar %d productos.\n", Num_productos);

    // Pausar antes de limpiar pantalla
    printf("Presiona Enter para continuar...");
    getchar(); //Capturará el enter que queda en el buffer(un buffer es una memoria temporal, también es la primera vez que la uso)
    getchar(); // Espera un nuevo enter del usuario

    system("cls"); // Ahora limpia la pantalla despues de la pausa

    Producto* productos = (Producto*)malloc(Num_productos * sizeof(Producto));//Usamos malloc para reservar la memoria según los productos ingresados, primera vez que uso esta función también
    if (productos == NULL) {
        printf("Error al asignar memoria\n");
        return 1;//Si la memoria es NULL, el programa termina con return 1, esto quiere decir que ocurrió un error y el programa no puede continuar
    }

    while (eleccion != 5) {//Bucle que se irá ejecutando hasta que el usuario presione 5
        printf("\n¿Qué deseas realizar?\n");
        printf("1) Agregar productos\n");
        printf("2) Buscar producto\n");
        printf("3) Mostrar productos\n");
        printf("4) Comprar Producto\n");
        printf("5) Salir\n");
        scanf_s("%d", &eleccion);//Se usa scanf_s, una manera más segura que ayuda a evitar problemas de buffer

        switch (eleccion) {//Este control analiza que ha presionado el usuario y procede con sus funciones. Primera vez que lo uso
        case 1: {//Si el usuario presiona 1, le permite agregar productos a la tienda
            int bandera = 0;//Inicializamos una variable para sabe si se encontró un espacio vacío para reutilizar
            if (contador_productos == 0) {//Si no hay productos agregados aún
                productos[contador_productos] = Agregar_producto();//Se agrega un producto
                contador_productos++;//Incrementamos el valor del contador de productos
            }
            else {
                for (char i = 0; i < contador_productos; i++) {//Si hay productos en la tienda, se revisan si aún hay espacios en la tienda
                    if (productos[i].cantidad == 0) {//Si hay un producto con cantidad igual  0, lo reemplazará con uno nuevo en la siguiente línea
                        productos[i] = Agregar_producto();//Llama a la función para agregar productos
                        bandera = 1;//Ya se ha utilizado el espacio
                        break;//Forzamos detener el bucle
                    }
                }
                if (bandera == 0) {//Si no hay espacio disponible
                    if (contador_productos == Num_productos) {//Significa que la tienda está llena, por lo tanto no se pueden añadir más productos
                        printf("\nYa no es posible agregar mas productos\n");
                    }
                    else {//Si aún hay espacio, se agrega el producto
                        productos[contador_productos] = Agregar_producto();
                        contador_productos++;
                    }
                }
            }
            break;
        }

        case 2: {//Si el usuario presiona 2
            int buscado, Codigo;
            printf("Dame el codigo de barras para encontrar el producto: ");
            scanf_s("%d", &Codigo);
            buscado = Busqueda(productos, Codigo, contador_productos);//Aquí estamos llamando a la función, esta función recorre el array productos y devuelve la posición donde se encuentra el código de barras, o si no lo encuentra devuelve -1

            if (buscado == -1) {//Si la funcion Busqueda(), encuentra el producto, devuelve su posición en el array, si no, devuelve -1, lo que siginifica que el producto no existe
                printf("\nProducto no encontrado\n");
            }
            else {//Si tiene otro numero, quiere decir que el producto existe y muestra la función Mostrar_producto()
                Mostrar_producto(productos, buscado);
            }
            break;
        }

        case 3://Si el usuario presiona 3
            Mostrar_productos(productos, contador_productos);//Printa una lista de los productos que se han añadido hata ahora
            break;

        case 4: {//Si el usuario presiona 4
            int buscado, Codigo;//Declaramos variables para almacenar el codigo ingresado por el usuario y para guardar la posiciñon del producto en el array
            printf("Dame el codigo de barras para encontrar el producto: ");
            scanf_s("%d", &Codigo);
            buscado = Busqueda(productos, Codigo, contador_productos);//Se llama a la función que recorrerá el array de productos, devolviendo la posición si lo encuentra o -1 si no lo hace

            if (buscado == -1) {//Si devuelve -1, printará que no lo encuentra
                printf("\nProducto no encontrado\n");
            }
            else {//Por lo contrario si lo encuentra mostrará el producto y le preguntará si quiere comprar una cantidad del producto
                Mostrar_producto(productos, buscado);
                Comprar_producto(productos, buscado);
            }
            break;
        }

        case 5://Si el usuario presiona 5
            printf("\nAdios\n");//El código se acaba
            break;

        default://Si la persona presiona otra tecla que no sea 1,2,3,4,5 se printará automáticamente lo definido
            printf("\nOpcion invalida, intenta de nuevo.\n");
        }
    }

    free(productos);//Liberamos la memoria usada previamente que fue reservada para malloc. De esta manera evitamos fugas de memoria
    return 0;
}
//Separé el código en partes para diferenciar la estructura principal de la estrutura en la que defino las distintas funciones que se han utilizado arriba
int Pedir_cantidad() {//Función para pedir al usuario que ingrese la cantidad de producto que desea agregar a la tienda
    int cantidad;
    printf("Dame la cantidad de productos que deseas agregar a tu tienda: ");
    scanf_s("%d", &cantidad);
    return cantidad;
}

Producto Agregar_producto() {//Solicita al usuario los datos de un nuevo producto
    Producto articulo;
    printf("\nDame el nombre del producto: ");
    scanf_s("%s", articulo.Nombre_producto, (unsigned)_countof(articulo.Nombre_producto));//Usamos _countof para devolver el tamaño del arreglo [Nombre_producto], devolviendo 30. (unsigned) espera un valor entero. De esta manera nos aseguramos que solo se pueda añadir un máximo de 30 carácteres, si són más el programa lo omitirá. Primera vez usando esta función.
    printf("\nDame el precio del producto: ");
    scanf_s("%f", &articulo.precio);
    printf("\nDame la cantidad disponible del producto: ");
    scanf_s("%d", &articulo.cantidad);
    printf("\nDame el codigo de barras: ");
    scanf_s("%d", &articulo.codigo_barras);
    return articulo;
}

void Mostrar_productos(Producto* productos, int Num_productos) {//Muestra todos los productos del arrreglo productos. Gracias a los punteros, tenemos más eficiencia a la hora de hacer el código. Si no, deberíamos de escribir el arreglo entero. Primera vez que uso los punteros de esta manera.
    for (char j = 0; j < Num_productos; j++) {
        printf("Producto: %s\n", productos[j].Nombre_producto);
        printf("Precio: %.2f\n", productos[j].precio);
        printf("Cantidad: %d\n", productos[j].cantidad);
        printf("Codigo de barras: %d\n", productos[j].codigo_barras);
        printf("\n");
    }
}

void Mostrar_producto(Producto* productos, int posicion) {//Muestra la información de un producto en concreto, el cual se decidirá previamente al haber introducido el código de barras del producto
    printf("Producto: %s\n", productos[posicion].Nombre_producto);
    printf("Precio: %.2f\n", productos[posicion].precio);
    printf("Cantidad: %d\n", productos[posicion].cantidad);
    printf("Codigo de barras: %d\n", productos[posicion].codigo_barras);
    printf("\n");
}

int Busqueda(Producto* productos, int Codigo, int contador) {//Busca un producto en el arreglo productos, gracias al código de barras proporcionado anteriormente
    for (char k = 0; k < contador; k++) {
        if (productos[k].codigo_barras == Codigo) {
            return k;
        }
    }
    return -1;
}

void Comprar_producto(Producto* productos, int posicion) {//Función aislada para realizar una compra del producto
    if (productos[posicion].cantidad == 0) {//Verifica si hay productos para vender
        printf("No hay productos disponibles para la venta\n");
    }
    else {//Si hay productos disponibles, pide al usuario cuántos productos desea comprar
        int comprar;
        printf("¿Cuantos productos vas a adquirir?: ");
        scanf_s("%d", &comprar);
        if (productos[posicion].cantidad >= comprar) {
            productos[posicion].cantidad -= comprar;
            printf("\nPagaras en total: %.2f\n", productos[posicion].precio * comprar);
            Mostrar_producto(productos, posicion);
        }
        else {
            printf("No hay suficientes productos, solo hay %d disponibles.\n", productos[posicion].cantidad);
        }
    }
}
