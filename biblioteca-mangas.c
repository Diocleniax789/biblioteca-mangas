#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

#define TOTAL_MANGAS 2
#define TOTAL_MANGAS_POR_LEER 10

struct manga {
    char nombre[50];
    char autor[50];
    char editorial[20];
    char ISBN[13];
    int nro_tomo;
    int cant_paginas;
    int colocado;
};

struct manga biblioteca[TOTAL_MANGAS];

void menu_principal();
void cargar_biblioteca();
struct manga* agregar_a_la_biblioteca(struct manga*, int*);
int verificar_estantes(struct manga*, int*);
void mostrar_biblioteca(struct manga*,int*);
void ver_y_escojer_manga();
int verificar_estantes_vacios(struct manga*, int*);
int busca_manga_y_tomo(struct manga*, char*, int*, int);

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
        printf("\n BIBLIOTECA MANGAS\n");
        printf(" =================\n");
        printf("\n MENU PRINCIPAL \n");
        printf(" -------------- \n");
        printf(" ---------------------------------------------------------------------\n");
        printf(" |1| -                    Cargar biblioteca                      - |1|\n");
        printf(" ---------------------------------------------------------------------\n");
        printf(" |2| -        Ver biblioteca y escoger un manga para leer        - |2|\n");
        printf(" ---------------------------------------------------------------------\n");
        printf(" |3| -              Ver disponibilidad del manga                 - |3|\n");
        printf(" ---------------------------------------------------------------------\n");
        printf(" |4| -                     Devolver manga                        - |4|\n");
        printf(" ---------------------------------------------------------------------\n");
        printf(" |5| -                           Salir                           - |5|\n");
        printf(" ---------------------------------------------------------------------\n");
        do {
            printf("\n--------------------------------------------\n");
            printf("Seleccione una opcion valida < 1 y 6> : ");
            scanf("%i", &op);
            if (op < 1 || op > 5) {
                printf("\n X opcion no valida, intente de nuevo X \n");
            }
        } while (op < 1 || op > 5);

        switch (op) {
            case 1:
                system("cls");
                cargar_biblioteca();
                break;

            case 2:
                system("cls");
                ver_y_escojer_manga();
                break;

          /*  case 3:
                system("cls");

                break;
            Otros casos del menú aquí */
        }

    } while (op != 5);
}

void cargar_biblioteca() {
    int total_mangas = TOTAL_MANGAS;
    struct manga* ptr_mangas;

    int biblioteca_cargada = verificar_estantes_vacios(biblioteca,&total_mangas);

    if (biblioteca_cargada == 1) {
        ptr_mangas = agregar_a_la_biblioteca(biblioteca, &total_mangas);
    } else {
        printf("\n# La biblioteca esta llena, no se pueden cargar más mangas #\n");
        Sleep(2000);
    }
}

int verificar_estantes(struct manga* mangas, int* indice) {
    int i, mangas_colocados = 0;
    for (i = 0; i < *indice; i++) {
        if (mangas[i].colocado == 1) {
            mangas_colocados++;
        }
    }

    if (mangas_colocados > 0) {
        return 0;
    } else {
        return 1;
    }
}

int verificar_estantes_vacios(struct manga *mangas, int *indice){
    int i, estantes_vacios = 0;
    for(i = 0; i < *indice; i++){
        if(mangas[i].colocado == 0){
            estantes_vacios++;
        }
    }
    if(estantes_vacios > 0){
        return 1;
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
            printf(">>> Cantidad de paginas: ");
            scanf("%i",&mangas[i].cant_paginas);

            do {
                printf(">>> Colocar? < 1 por si, 0 por no >: ");
                scanf("%i", &op2);
                if (op2 != 1 && op2 != 0) {
                    printf("\n X ingrese un valor valido X \n");
                }
            } while (op2 != 1 && op2 != 0);

            mangas[i].colocado = op2;

            if (op2 == 1) {
                printf("\n");
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

void mostrar_biblioteca(struct manga* mangas,int *indice){
    int i,encontrado,manga_encontrado;
    char op;
    int ptr_ind = *indice;
    static char nombre_tomo[50];
    static int tomo;

    for(i = 0; i < *indice; i++){
      if(mangas[i].colocado == 1){
        printf("\n===================================================\n");
        printf("--> NOMBRE: %s\n",mangas[i].nombre);
        printf("--> AUTOR: %s\n",mangas[i].autor);
        printf("--> EDITORIAL%s\n",mangas[i].editorial);
        printf("--> ISBN: %s\n",mangas[i].ISBN);
        printf("--> TOMO:%i\n",mangas[i].nro_tomo);
        printf("--> NRO DE PAGINAS: %i\n",mangas[i].cant_paginas);
      }
    }
    do {
    do{
        fflush(stdin);
        printf("\n Deseas llevar alguno <s/n>?: ");
        scanf("%c",&op);
        if(op != 's' && op != 'n'){
            printf("\n X valor incorrecto. Ingrese nuevamente X\n");
        }
    } while(op != 's' && op != 'n');

    if(op == 's'){
    printf("\n Para seleccionar el manga selecciona el que desees llevar y el nro de tomo \n");
    printf("\n----------------------------------------------------------------------------\n");
    printf("\n");
    printf(">>> Ingrese nombre del tomo que deseas llevar: \n");
    getchar();
    fgets(nombre_tomo,sizeof(nombre_tomo),stdin);
    nombre_tomo[strcspn(nombre_tomo, "\n")] = '\0';
    printf("Ingrese un numero de tomo: ");
    scanf("%i",&tomo);
    getchar();

    manga_encontrado = busca_manga_y_tomo(biblioteca, nombre_tomo, &ptr_ind,tomo);

    if(manga_encontrado == 1){
        printf("\n *** El manga fue encontrado junto con el tomo ***\n");
    } else {
        printf("\n El manga no se ha encontrado \n");
    }
        }

    } while(op != 'n');

}

void ver_y_escojer_manga() {
    int total_mangas = TOTAL_MANGAS;
    int biblioteca_vacia = verificar_estantes(biblioteca, &total_mangas);

    if (biblioteca_vacia == 1) {
        printf("\n# ACTUALMENTE LA BIBLIOTECA ESTA VACIA. INTENTE MAS TARDE #\n");
        Sleep(2000);
    } else {
        mostrar_biblioteca(biblioteca, &total_mangas);
    }
}

int busca_manga_y_tomo(struct manga *mangas, char *nombre_tomo, int *indice, int tomo){
    int i,flag,pos,compara_cadena;

    flag = 0;
    pos = 0;
    for (i = 0; i < *indice; i++) {
        if (strcmpi(nombre_tomo, mangas[i].nombre) == 0 && mangas[i].nro_tomo == tomo) {
            flag = 1;
            break;
        }
    }
    return flag;
}






