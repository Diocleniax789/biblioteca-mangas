#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define TOTAL_MANGAS 2

struct manga {
    char nombre[50];
    char autor[50];
    char editorial[20];
    char ISBN[13];
    int nro_tomo;
    int colocado;
};

struct manga biblioteca[TOTAL_MANGAS];
void menu_principal();
void cargar_biblioteca();
struct manga* agregar_a_la_biblioteca(struct manga*, int*);
int verificar_estantes(struct manga*, int*);

int main() {
    for (int i = 0; i < TOTAL_MANGAS; i++) {
        biblioteca[i].colocado = 0;
    }
    menu_principal();
    return 0;
}

void menu_principal() {
    int op;

    do {
        system("cls");
        printf("---------------------------------------------------------------------\n");
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
            scanf("%i", &op);
            if (op < 1 || op > 6) {
                printf("\n X opcion no valida, intente de nuevo X \n");
            }
        } while (op < 1 || op > 6);

        switch (op) {
            case 1:
                system("cls");
                cargar_biblioteca();
                break;

            /* Otros casos del menú aquí */
        }

    } while (op != 6);
}

void cargar_biblioteca() {
    int total_mangas = TOTAL_MANGAS;
    struct manga* ptr_mangas;

    int biblioteca_cargada = verificar_estantes(biblioteca, &total_mangas);

    if (biblioteca_cargada == 1) {
        ptr_mangas = agregar_a_la_biblioteca(biblioteca, &total_mangas);
    } else {
        printf("\n# La biblioteca esta llena, no se pueden cargar más mangas #\n");
        Sleep(2000);
    }
}

int verificar_estantes(struct manga* mangas, int* indice) {
    int i, contador_casillas_vacias = 0;

    for (i = 0; i < *indice; i++) {
        if (mangas[i].colocado == 0) {
            contador_casillas_vacias++;
        }
    }

    if (contador_casillas_vacias > 0) {
        return 1;
    } else {
        return 0;
    }
}

struct manga* agregar_a_la_biblioteca(struct manga* mangas, int* indice) {
    int i, op2;
    char op;

    for (i = 0; i < *indice; i++) {
        if (mangas[i].colocado == 0) {
            system("cls");
            fflush(stdin);
            printf("Casilla nro %i\n", i + 1);
            printf(">>> Ingrese nombre del manga: ");
            fgets(mangas[i].nombre, sizeof(mangas[i].nombre), stdin);
            mangas[i].nombre[strcspn(mangas[i].nombre, "\n")] = '\0';
            printf(">>> Ingrese autor: ");
            fgets(mangas[i].autor, sizeof(mangas[i].autor), stdin);
            mangas[i].autor[strcspn(mangas[i].autor, "\n")] = '\0';
            printf(">>> Ingrese editorial: ");
            fgets(mangas[i].editorial, sizeof(mangas[i].editorial), stdin);
            mangas[i].editorial[strcspn(mangas[i].editorial, "\n")] = '\0';
            printf(">>> Ingrese ISBN: ");
            fgets(mangas[i].ISBN, sizeof(mangas[i].ISBN), stdin);
            mangas[i].ISBN[strcspn(mangas[i].ISBN, "\n")] = '\0';
            printf(">>> Ingrese nro de tomo: ");
            scanf("%i", &mangas[i].nro_tomo);

            do {
                printf(">>> Colocar? < 1 por si, 0 por no > : ");
                scanf("%i", &op2);
                if (op2 != 1 && op2 != 0) {
                    printf("\n X ingrese un valor valido X \n");
                }
            } while (op2 != 1 && op2 != 0);

            mangas[i].colocado = op2;

            if (op2 == 1) {
                printf("\n*** Manga cargado correctamente ***\n");
            }

            do {
                printf("--------------------------------------\n");
                printf("Desea agregar otro manga <s/n>? : ");
                scanf(" %c", &op);
                if (op != 's' && op != 'n') {
                    printf("\nX opcion incorrecta, intente nuevamente X\n");
                }
            } while (op != 's' && op != 'n');

            if (op == 'n') {
                return mangas;
            }
        }
    }

    printf("\n# No quedan más casillas vacías en la biblioteca #\n");
    Sleep(2000);
    return mangas;
}
