#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODOS_LOS_MANGAS 500
#define TODOS_LOS_CLIENTES 100000

struct manga{
    char nombre[50];
    char autor[50];
    char editorial[50];
    char isbn[14];
    int disponibilidad;
};

int cargar_biblioteca(struct manga*,int*);
void inicializar_cad_isbn(char*);
void ver_alquilar_manga(struct manga*,int*);
void ordena_mangas_por_tomo(struct manga*,int*);
void consultar_libros(struct manga*,int*);

int main(){
    int todos_los_mangas = TODOS_LOS_MANGAS,mangas_cargados,todos_los_clientes = TODOS_LOS_CLIENTES;
    struct manga biblioteca[TODOS_LOS_MANGAS];
    int op;


    mangas_cargados = cargar_biblioteca(biblioteca,&todos_los_mangas);
    ordena_mangas_por_tomo(biblioteca,&mangas_cargados);

    do{
        system("cls");
        printf("\n * BIBLIOTECA DE MANGAS * \n");
        printf("   ======================== \n");
        printf("\n - Menu Principal - \n");
        printf("\n");
        printf("\n |1| - Ver y alquilar manga/s. \n");
        printf("\n |2| - Consultar mangas faltantes. \n");
        printf("\n |3| - Realizar devolucion de manga. <no disponible> \n");
        printf("\n |4| - Salir. \n");
        printf("\n");
        do{

            fflush(stdin);
            printf("\n - Seleccione opcion: ");
            scanf("%i",&op);
            if(op < 1 || op > 4){
                printf("\n x ERROR. INGRESE UN NUMERO ENTRE EL RANDO DE 1 Y 4 x \n");
            }
        } while(op < 1 || op > 4);
        switch(op){
            case 1:
                system("cls");
                ver_alquilar_manga(biblioteca,&mangas_cargados);
            break;

            case 2:
                system("cls");
                consultar_libros(biblioteca,&mangas_cargados);
            break;

        }

    } while(op != 4);

    return 0;
}

void inicializar_cad_isbn(char *cad_isbn){
    int i;
    for(i = 0; i < 14; i++){
        cad_isbn[i] = '\0';
    }
}

int cargar_biblioteca(struct manga *biblioteca, int *todos_los_mangas){
    int i,long_isbn,cantidad_estantes_disponibles,cantidad_mangas_cargados,flag,j,nuevo_indice;
    static char cad_isbn[14],op;

    flag = 0;

    do{
    cantidad_mangas_cargados = 0;
    for(i = 0; i < *todos_los_mangas; i++){
        system("cls");
        fflush(stdin);
        printf("\n SI QUIERE FINALIZAR CON LA CARGA, A LA HORA DE USAR EL NOMBRE, SIMPLEMENTE COLOQUE '*' \n");
        printf("======================================================================================== \n");
        printf("\n ESPACIO NRO %i\n", i + 1);
        printf(" -------------\n");
        printf("\n + Ingrese nombre del manga: ");
        fgets(biblioteca[i].nombre,sizeof(biblioteca[i].nombre),stdin);
        biblioteca[i].nombre[strcspn(biblioteca[i].nombre,"\n")] = '\0';
        if(strcmp(biblioteca[i].nombre,"*") == 0){
            cantidad_estantes_disponibles = TODOS_LOS_MANGAS - cantidad_mangas_cargados;
            break;
        } else{
            printf("\n + Ingrese autor del manga: ");
            fgets(biblioteca[i].autor,sizeof(biblioteca[i].autor),stdin);
            biblioteca[i].autor[strcspn(biblioteca[i].autor,"\n")] = '\0';
            printf("\n + Ingrese editorial del manga: ");
            fgets(biblioteca[i].editorial,sizeof(biblioteca[i].editorial),stdin);
            biblioteca[i].editorial[strcspn(biblioteca[i].editorial,"\n")] = '\0';
            do{
                fflush(stdin);
                inicializar_cad_isbn(cad_isbn);
                printf("\n + Ingrese ISBN del manga: ");
                fgets(cad_isbn,sizeof(cad_isbn),stdin);
                cad_isbn[strcspn(cad_isbn,"\n")] = '\0';
                long_isbn = strlen(cad_isbn);
                if(long_isbn != 13){
                    printf("\n x ERROR. EL ISBN DEBE CONTENER EXACTAMENTE 13 DIGITOS x \n");
                }
            } while(long_isbn != 13);
            strcpy(biblioteca[i].isbn,cad_isbn);
            biblioteca[i].disponibilidad = 1;
            cantidad_mangas_cargados++;

            printf("\n *** MANGA CARGADO CORRECTAMENTE *** \n");
            printf("\n");
            system("pause");
        }
    }

    if(cantidad_estantes_disponibles > cantidad_mangas_cargados){
        printf("\n # AUN QUEDAN %i ESPACIOS DISPONIBLES # \n",cantidad_estantes_disponibles);

        do{
            fflush(stdin);
            printf("\n - Deseas seguir agregando mas mangas? Ingrese < s | n > : ");
            scanf("%c",&op);
            if(op != 's' && op != 'n'){
                printf("\n x ERROR. INGRESE s O n. x \n");
            }
        } while(op != 's' && op != 'n');

        if(op == 's'){

        do{
            system("cls");
            fflush(stdin);
            printf("\n SI QUIERE FINALIZAR CON LA CARGA, A LA HORA DE USAR EL NOMBRE, SIMPLEMENTE COLOQUE '*' \n");
            printf("======================================================================================== \n");
            printf("\n ESPACIO NRO %i\n", cantidad_mangas_cargados + 1);
            printf(" -------------\n");
            printf("\n + Ingrese nombre del manga: ");
            fgets(biblioteca[cantidad_mangas_cargados].nombre,sizeof(biblioteca[cantidad_mangas_cargados].nombre),stdin);
            biblioteca[cantidad_mangas_cargados].nombre[strcspn(biblioteca[cantidad_mangas_cargados].nombre,"\n")] = '\0';
            while(cantidad_mangas_cargados < *todos_los_mangas && strcmp(biblioteca[cantidad_mangas_cargados].nombre,"*") != 0){
                    printf("\n + Ingrese autor del manga: ");
                    fgets(biblioteca[cantidad_mangas_cargados].autor,sizeof(biblioteca[cantidad_mangas_cargados].autor),stdin);
                    biblioteca[cantidad_mangas_cargados].autor[strcspn(biblioteca[cantidad_mangas_cargados].autor,"\n")] = '\0';
                    printf("\n + Ingrese editorial del manga: ");
                    fgets(biblioteca[cantidad_mangas_cargados].editorial,sizeof(biblioteca[cantidad_mangas_cargados].editorial),stdin);
                    biblioteca[cantidad_mangas_cargados].editorial[strcspn(biblioteca[cantidad_mangas_cargados].editorial,"\n")] = '\0';
                do{
                    fflush(stdin);
                    inicializar_cad_isbn(cad_isbn);
                    printf("\n + Ingrese ISBN del manga: ");
                    fgets(cad_isbn,sizeof(cad_isbn),stdin);
                    cad_isbn[strcspn(cad_isbn,"\n")] = '\0';
                    long_isbn = strlen(cad_isbn);
                    if(long_isbn != 13){
                        printf("\n x ERROR. EL ISBN DEBE CONTENER EXACTAMENTE 13 DIGITOS x \n");
                    }
                } while(long_isbn != 13);
                    strcpy(biblioteca[cantidad_mangas_cargados].isbn,cad_isbn);
                    biblioteca[cantidad_mangas_cargados].disponibilidad = 1;
                    cantidad_mangas_cargados++;
                    cantidad_estantes_disponibles = TODOS_LOS_MANGAS - cantidad_mangas_cargados;
                    printf("\n *** MANGA CARGADO CORRECTAMENTE *** \n");
                    printf("\n");
                    system("pause");

              system("cls");
              fflush(stdin);
              printf("\n SI QUIERE FINALIZAR CON LA CARGA, A LA HORA DE USAR EL NOMBRE, SIMPLEMENTE COLOQUE '*' \n");
              printf("======================================================================================== \n");
              printf("\n ESPACIO NRO %i\n", cantidad_mangas_cargados + 1);
              printf(" -----------\n");
              printf("\n + Ingrese nombre del manga: ");
              fgets(biblioteca[cantidad_mangas_cargados].nombre,sizeof(biblioteca[cantidad_mangas_cargados].nombre),stdin);
              biblioteca[cantidad_mangas_cargados].nombre[strcspn(biblioteca[cantidad_mangas_cargados].nombre,"\n")] = '\0';
            }

            if(cantidad_estantes_disponibles > cantidad_mangas_cargados){
                printf("\n # AUN QUEDAN %i ESPACIOS DISPONIBLES # \n",cantidad_estantes_disponibles);

            do{
                fflush(stdin);
                printf("\n - Deseas seguir agregando mas mangas? Ingrese < s | n > : ");
                scanf("%c",&op);
                if(op != 's' && op != 'n'){
                    printf("\n x ERROR. INGRESE 's' O 'n' x \n");
                }
             } while(op != 's' && op != 'n');

            }

        } while(op != 'n');
    }

    } else{
        flag = 1;
        printf("\n x YA NO QUEDAN ESPACIOS DISPONIBLES x \n");
        printf("\n");
        printf("\n *** TODOS LOS MANGAS HAN SIDO CARGADOS CORRECTAMENTE *** \n");
        printf("\n");
        system("pause");
    }

    } while(op != 'n' && flag == 0);

    if(op == 'n'){
        return cantidad_mangas_cargados;
    }
}

void ver_alquilar_manga(struct manga *biblioteca, int *mangas_cargados){
    int i,pos,flag;
    char op,nombre[50];

    printf("\n                              BIBLIOTECA ACTUAL               \n");
    printf("                              =================               \n");
    printf("----------------------------------------------------------------------\n");
    printf(" NOMBRE\t\t\t AUTOR\t\t\t EDITORIAL\t ISBN\t\t\t \n");
    printf("----------------------------------------------------------------------\n");
    for(i = 0; i < *mangas_cargados; i++){
        printf(" %s\t\t %s\t\t %s\t\t %s\t",biblioteca[i].nombre,biblioteca[i].autor,biblioteca[i].editorial,biblioteca[i].isbn);
        printf("\n\n");
    }
    printf("\n");

  do{
    do{
        fflush(stdin);
        printf("\n Desea llevar algun manga? Ingese < s | n > : ");
        scanf("%c",&op);
        if(op != 's' && op != 'n'){
                printf("\n x ERROR. DEBE INGRESAR 's' O 'n' x \n");
        }
    } while(op != 's' && op != 'n');
    if(op == 's'){
     do {
        fflush(stdin);
        printf("\n PARA REALIZAR UNA BUSQUEDA ESCRIBA EL NOMBRE DEL MANGA JUNTO A SU NRO DE TOMO. EJ: MANGA #02 \n");
        printf("------------------------------------------------------------------------------------------------ \n");
        printf("\n + Escriba el nombre aqui: ");
        fgets(nombre,sizeof(nombre),stdin);
        nombre[strcspn(nombre,"\n")] = '\0';
        flag = 0;
        pos = 0;
        do{
            if(strcmp(nombre,biblioteca[pos].nombre) == 0 && biblioteca[pos].disponibilidad == 1){
                flag = 1;
                break;
            } else{
                pos++;
            }
        } while(pos < *mangas_cargados && flag == 0);
        if(flag == 1){
            printf("\n *** MANGA ENCONTRADO *** \n");
            biblioteca[pos].disponibilidad = 0;
            printf("\n *** DISFRUTE DE UNA BUENA LECTURA! *** \n");
        } else{
            printf("\n x MANGA NO ENCONTRADO O NO DISPONIBLE x \n");
        }

        do{
            fflush(stdin);
            printf("\n - Desea llevarse otro? Ingrese < s | n >: ");
            scanf("%c",&op);
            if(op != 's' && op != 'n'){
                printf("\n x ERROR. INGRESE 's' O 'n' x \n");
            }
        } while(op != 's' && op != 'n');

    } while(op != 'n');
  }

  } while(op != 'n');
}

void ordena_mangas_por_tomo(struct manga *biblioteca, int *mangas_cargados){
    int i,j;
    char nombre_manga_aux[50], autor_manga_aux[50], editorial_manga_aux[50],isbn_aux[14];

    for(i = 0; i < *mangas_cargados - 1; i++){
        for(j = i + 1; j < *mangas_cargados; j++){
            if(strcmp(biblioteca[i].nombre,biblioteca[j].nombre) > 0){
                strcpy(nombre_manga_aux,biblioteca[i].nombre);
                strcpy(autor_manga_aux,biblioteca[i].autor);
                strcpy(editorial_manga_aux,biblioteca[i].editorial);
                strcpy(isbn_aux,biblioteca[i].isbn);
                strcpy(biblioteca[i].nombre,biblioteca[j].nombre);
                strcpy(biblioteca[i].autor,biblioteca[j].autor);
                strcpy(biblioteca[i].editorial,biblioteca[j].editorial);
                strcpy(biblioteca[i].isbn,biblioteca[j].isbn);
                strcpy(biblioteca[j].nombre,nombre_manga_aux);
                strcpy(biblioteca[j].autor,autor_manga_aux);
                strcpy(biblioteca[j].editorial,editorial_manga_aux);
                strcpy(biblioteca[j].isbn,isbn_aux);
            }
        }
    }
}

void consultar_libros(struct manga *biblioteca, int *mangas_cargados){
    int i,pos,flag;
    char nombre[50];

    for(i = 0; i < *mangas_cargados; i++){
        if(biblioteca[i].disponibilidad == 0){
            printf("\n - NOMBRE: %s",biblioteca[i].nombre);
            printf("\n - AUTOR: %s",biblioteca[i].autor);
            printf("\n - EDITORIAL: %s",biblioteca[i].editorial);
            printf("\n - ISBN: %s",biblioteca[i].isbn);
            printf("\n x NO DISPONIBLE x \n");
        }

        printf("\n");
    }

    printf("\n");
    system("pause");
}
