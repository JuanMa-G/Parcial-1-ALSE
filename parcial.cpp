#include <iostream>
#include <cmath>

// Definir la estructura de un punto en 2D
struct Point{
    double x, y;
};

// Función para calcular la distancia entre dos puntos
double calcularDistancia(const Point& p1, const Point& p2){
    
    return sqrt( pow(p1.x - p2.x , 2) + pow(p1.y - p2.y , 2) ); // Fórmula de distancia euclidiana de dos puntos en 2D
}

// Función para leer las coordenadas de varios puntos
void leerPuntos(Point puntos[], int n){
    
    char respuesta;
    std::cout << "¿Desea ingresar los puntos manualmente? (s/n). Cualquier entrada no válida se tomará como 'no': ";
    std::cin >> respuesta;

    if ((respuesta == 's') || (respuesta == 'S')){  // Si la respuesta es Si tanto en minúscula como en mayúscula:
        
        for (int i = 0; i < n; i++){    // Se recorre un for con la cantidad de puntos que deseó el usuario

            std::cout << "Ingrese las coordenadas del punto " << i + 1 << " (x, y): ";
            std::cin >> puntos[i].x >> puntos[i].y; // Se almacenan los puntos en las posiciones x y y de puntos[]
        }
    }
    else{
        std::cout << "Usando puntos predeterminados...\n";
        switch (n){     // Se elige la cantidad de puntos predeterminados a utilizar según cuántos deseó el usuario

        case 2:
            puntos[0] = {0, 0};  // Punto 1 (0, 0)
            puntos[1] = {3, 4};  // Punto 2 (3, 4)
            break;

        case 3:
            puntos[0] = {0, 0};  // Punto 1 (0, 0)
            puntos[1] = {3, 4};  // Punto 2 (3, 4)
            puntos[2] = {6, 8};  // Punto 3 (6, 8)
            break;

        case 4:
            puntos[0] = {0, 0};  // Punto 1 (0, 0)
            puntos[1] = {3, 4};  // Punto 2 (3, 4)
            puntos[2] = {6, 8};  // Punto 3 (6, 8)
            puntos[3] = {9, 12}; // Punto 4 (9, 12)
            break;

        default:
            break;
        }
     
    }

}

// Función para calcular la distancia más cercana entre un punto dado por el usuario y otro arreglo de puntos dados por el usuario o predeterminados, según aplique
double calcularDistanciaMasCercana(Point puntos[], int n, const Point &pUsuario, int *indiceMasCercano){

    double distancia[n];    // Se crea un arreglo que contendrá todas las distancias entre el punto de referencia y los demás puntos
    distancia[0] = calcularDistancia(pUsuario, puntos[0]);  // Se calcula la primera distancia
    double distanciaMinima = distancia[0];  // Se crea una variable que almacena la distancia mínima, inicializada con la primera distancia

    for (int i = 1; i < n; i++){    // Se recorre un for según la cantidad de puntos deseados por el usuario
        distancia[i] = calcularDistancia(pUsuario, puntos[i]);  // Se calcula la "i" distancia
        if (distancia[i] < distancia[i-1]){     // Si la distancia actual es menor que la anterior, se asigna una nueva distancia mínima
            distanciaMinima = distancia[i];
            *indiceMasCercano = i;  // Se actualiza el valor al que apunta el puntero con la "i" de la distancia menor, es decir el índice más cercano declarado en el main()
        }
    }

    return distanciaMinima;
}

// Función que muestra los tres resultados
void mostrarResultado(Point puntos[], int indiceMasCercano, double distancia, double distanciaTot)
{
    std::cout << "El punto más cercano es: (" << puntos[indiceMasCercano].x << ", " << puntos[indiceMasCercano].y << ")\n";
    std::cout << "La distancia al punto más cercano es: " << distancia << "\n";
    std::cout << "Adicionalmente, la distancia total entre todos los puntos recorridos en orden es: " << distanciaTot << std::endl;
}

// Función que calcula la distancia total acumulada del arreglo de puntos
void calcularDistanciaTotal(Point puntos[], int n, double *distanciaTotal) {    // Recibe los puntos, la cantidad de puntos, y el apuntador de la variable de distancia total
    *distanciaTotal = 0;
    for (int i = 0; i < n - 1; i++) {   // Se recorre el for cuantas veces como distancias entre puntos existan
        *distanciaTotal = calcularDistancia(puntos[i], puntos[i + 1]) + *distanciaTotal;    // Se acumulan las distancias entre el punto actual y el siguiente en el arreglo de puntos
    }
}

int main(){
    
    int cantidad_puntos;        // Se declara una variable que almacena la cantidad de puntos que el usuario desea utilizar
    int indiceMasCercano = 0;   // El índice más cercano se inicializa con 0 dado que puede ir desde 0 hasta "cantidad_puntos"
    double distanciaMinima;
    double distanciaTotal = 0;  // Se declara una variable inicializada con 0 que almacena la distancia total sumada de todos los puntos que el usuario desea utilizar

    std::cout << "Ingrese la cantidad de puntos que desea ingresar. Mínimo 2, máximo 4: ";
    std::cin >> cantidad_puntos;

    if ( (cantidad_puntos > 4) || (cantidad_puntos < 2) ){
        
        std::cout << "Cantidad ingresada fuera de los límites. Reinicie el programa\n";
        return 0;   // Si la cantidad ingresada está por fuera de los límites de los puntos válidos, se retorna 0 para salir del main()

    }

    Point puntos[cantidad_puntos];      // Se declara un arreglo que almacenará los puntos que ingresará el usuario
    Point puntoUsuario;                 // Se declara un arreglo que almacenará el punto que ingresará el usuario
    
    leerPuntos(puntos,cantidad_puntos);
    std::cout << "Ingrese las coordenadas del punto desde el que desea calcular la distancia (x, y): ";
    std::cin >> puntoUsuario.x >> puntoUsuario.y;

    distanciaMinima = calcularDistanciaMasCercana(puntos, cantidad_puntos, puntoUsuario, &indiceMasCercano);
    calcularDistanciaTotal(puntos, cantidad_puntos, &distanciaTotal);
    mostrarResultado(puntos, indiceMasCercano, distanciaMinima, distanciaTotal);

    return 0;
    
}