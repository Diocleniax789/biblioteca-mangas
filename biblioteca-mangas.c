#include <stdio.h>
#include <stdlib.h>

void menu_principal();

int main(){
     menu_principal();

    return 0;
}

void menu_principal(){
    int op;

    do {
        system("cls");
        printf("|1| -                    Cargar biblioteca                      - |1|\n");
        printf("---------------------------------------------------------------------\n");
        printf("|2| -        Ver biblioteca y escoger un manga para leer        - |2|\n");
        printf("---------------------------------------------------------------------\n");
        printf("|3| -          Cuantas paginas me faltan para terminar?         - |3|\n");
        printf("---------------------------------------------------------------------\n");
        printf("|4| -           Cuantos tomos me faltan para terminar?          - |4|\n");
        printf("---------------------------------------------------------------------\n");
        printf("|5| -               Colocar tomo en la biblioteca               - |5|\n");
        printf("---------------------------------------------------------------------\n");
        printf("|6| -                           Salir                           - |6|\n");
        printf("---------------------------------------------------------------------\n");
        do {
          printf("\n--------------------------------------------\n");
          printf("Seleccione una opcion valida < 1 y 6> : ");
          scanf("%i",&op);
          if(op < 1 || op > 6){
            printf("\n X opcion no valida, intente de nuevo X \n");
          }
        } while(op < 1 && op > 6);
        switch(op){
            case 1:
            break;

            case 2:
            break;

            case 3:
            break;

            case 4:
            break;

            case 5:
            break;
        }

    } while( op =! 6);
}
