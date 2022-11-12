#include <stdio.h>
#include <iomanip>
#include <chrono>
#include <math.h>
#include <omp.h>
#include <iostream>

float calculopi(int precision, int nhilos, int idHilo){

    int i;
    double pi=0;
    int maximo = precision/nhilos;

    int inicio = idHilo*maximo;

    for(i=inicio; i<maximo; i++){

        pi = pi + (((2*pow(-1.0,i)*pow(3,((0.5)-i))))/((2*i)+1));

    }
    return pi;

}
using namespace std;
int main(){

    int numeroHilos;
    printf("ingresar el numero de hilos a utilizar: ");
    scanf("%d", &numeroHilos);

    using namespace std;
    using namespace std::chrono;

    int precision;

    printf("ingresar precision: ");
    scanf("%d", &precision);

    omp_set_num_threads(numeroHilos);

    double arreglo[numeroHilos] = {};

    double resultado = 0;

    using clk = high_resolution_clock;
    auto t1 = clk::now();

    #pragma omp parallel
    {
        int idHilo = omp_get_thread_num();
        printf("Hola, soy el hilo %d, en este momento se estan ejecutando %d hilos \n", idHilo, omp_get_num_threads());

        double pi = calculopi(precision, numeroHilos, idHilo);

        arreglo[idHilo] = pi;
    }

    for (int j=0; j<numeroHilos; j++){

        resultado = resultado + arreglo[j];

    }

    printf("Pi = %f \n", resultado);

    auto t2 = clk::now();
    auto diff = duration_cast<microseconds>(t2-t1);

    cout << "tiempo= " << setprecision(10) << diff.count()<< endl;

    return 0;
}
