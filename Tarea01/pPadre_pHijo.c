
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main () {
    int i = 0;

    switch (fork()) {
        case -1:
            perror ("Error al crear procesos");
            exit (-1);
            break;
        case 0: /* Código para el hijo */
            while (i < 10000) {
                sleep (1);
                printf ("\t\tSoy el proceso hijo: %d\n", i++);
            }
            break;
        default: /* Código para el padre */
            while (i < 10000) {
                printf ("Soy el proceso padre: %d\n", i++);
                sleep (2);
            }
    };
    exit (0);
}