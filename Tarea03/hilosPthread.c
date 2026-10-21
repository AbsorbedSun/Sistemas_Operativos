/* Compilación: gcc -Wall -o hilos hilosPthread.c -pthread */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define LIMITE 10000
#define RETARDO_US 0  

int i;/* 1000 (1 ms) para ver mejor el entrelazado */

/* Función que ejecutará el hilo secundario (hijo) */
void *codigoHiloHijo(void *arg) {
    for (int i = LIMITE; i >= 1; i--) {
        printf("\t\t[Hilo hijo]: %d\n", i);
        if (RETARDO_US) usleep(RETARDO_US);
    }
    pthread_exit(NULL); /*Finalización explicita del hijo*/
}

int main(void) {
    pthread_t hiloHijo;
    int error;

    /*Creación del hilo hijo que inicia en la función 'codigoHiloHijo'*/
    error = pthread_create(&hiloHijo, NULL, codigoHiloHijo, NULL);
    if (error != 0) {
        fprintf(stderr, "Error al crear el hilo: %s\n", strerror(error));
        exit(EXIT_FAILURE);
    }

    /* Hilo principal (Padre)*/
    for (int i = 1; i <= LIMITE; i++) {
        printf("[Hilo principal]: %d\n", i);
        if (RETARDO_US) usleep(RETARDO_US);
    }

    /* SIN pthread_join: main termina y el proceso completo muere,
     * junto con el hilo hijo, aunque no haya acabado sus 10,000 impresiones */


    /*El hilo principal espera a que el hilo hijo concluya sus 10000 impresiones para concluir la tarea*/
    error = pthread_join(hiloHijo, NULL);
    if (error != 0) {
        fprintf(stderr, "Error en pthread_join: %s\n", strerror(error));
        exit(EXIT_FAILURE);
    }
    return 0;

}