#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODOS_LOS_MANGAS 500

struct manga{
    char nombre[50];
    char autor[50];
    char editorial[50];
    char isbn[14];
    int disponibilidad;
};

void cargar_biblioteca(struct manga*,int*);
void inicializar_cad_isbn(char*);

int main(){
    int todos_los_mangas = TODOS_LOS_MANGAS;
    struct manga biblioteca[TODOS_LOS_MANGAS];

    cargar_biblioteca(biblioteca,&todos_los_mangas);

    return 0;
}

void inicializar_cad_isbn(char *cad_isbn){
    int i;
    for(i = 0; i < 14; i++){
        cad_isbn[i] = '\0';
    }
}

void cargar_biblioteca(struct manga *biblioteca, int *todos_los_mangas){
    int i,long_isbn,cantidad_estantes_disponibles,cantidad_mangas_cargados,flag;
    static char cad_isbn[14],op;

    flag = 0;

    do{
    cantidad_mangas_cargados = 0;
    for(i = 0; i < *todos_los_mangas; i++){
        system("cls");
        fflush(stdin);
        printf("\n SI QUIERE FINALIZAR CON LA CARGA, A LA HORA DE USAR EL NOMBRE, SIMPLEMENTE COLOQUE * \n");
        printf("======================================================================================== \n");
        printf("\n MANGA NRO %i\n", i + 1);
        printf("   ------------\n");
        printf("\n + Ingrese nombre del manga: ");
        fgets(biblioteca[i].nombre,sizeof(biblioteca[i].nombre),stdin);
        biblioteca[i].nombre[strcspn(biblioteca[i].nombre," \n")] = '\0';
        if(strcmp(biblioteca[i].nombre,"*") == 0){
            cantidad_estantes_disponibles = TODOS_LOS_MANGAS - cantidad_mangas_cargados;
            break;
        } else{
            printf("\n + Ingrese autor del manga: ");
            fgets(biblioteca[i].autor,sizeof(biblioteca[i].autor),stdin);
            biblioteca[i].autor[strcspn(biblioteca[i].autor," \n")] = '\0';
            printf("\n + Ingrese editorial del manga: ");
            fgets(biblioteca[i].editorial,sizeof(biblioteca[i].editorial),stdin);
            biblioteca[i].editorial[strcspn(biblioteca[i].editorial," \n")] = '\0';
            do{
                fflush(stdin);
                inicializar_cad_isbn(cad_isbn);
                printf("\n + Ingrese ISBN del manga: ");
                fgets(cad_isbn,sizeof(cad_isbn),stdin);
                cad_isbn[strcspn(cad_isbn," \n")] = '\0';
                long_isbn = strlen(cad_isbn);
                if(long_isbn != 13){
                    printf("\n x ERROR. EL ISBN DEBE CONTENER EXACTAMENTE 13 digitos x \n");
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
        printf("\n # AUN QUEDAN %i DISPONIBLES # \n",cantidad_estantes_disponibles);

        do{
            fflush(stdin);
            printf("\n - Deseas seguir agregando mas mangas? Ingrese <s | n > : ");
            scanf("%c",&op);
            if(op != 's' && op != 'n'){
                printf("\n x ERROR. INGRESE s O n. x \n");
            }
        } while(op != 's' && op != 'n');


    } else{
        flag = 1;
        printf("\n x YA NO QUEDAN ESPACIOS DISPONIBLES x \n");
        printf("\n");
        printf("\n *** TODOS LOS MANGAS HAN SIDO CARGADOS CORRECTAMENTE ** \n");
        printf("\n");
        system("pause");
    }

    } while(op != 'n' && flag == 0);

}



