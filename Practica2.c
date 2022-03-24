#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>

int main(int argc, char const *argv[])
{
    int Checked = 0;
    char Reemplazo[50],Test[20];
    DIR *direction;

    if(argc < 2)
    {
        printf("Se necesitan dos argumentos:\n 1er argumento.Nombre del directorio\n 2do argumento.Nombre del archivo\n");
        return 1;
    }

    while (Checked == 0)
    {
        if((direction = opendir(argv[1])) == NULL){
            printf("Archivo valido\n");
            Checked =1;
        }
        else
        {
            printf("--ERROR-- El directorio ya existe, proporcione un nombre diferente\n");
            fflush(stdin);
            scanf("%s",Test);
            argv[1]= Test;
            printf("%s Se definio como el nuevo nombre del directorio\n",argv[1]);

        }

    }

    printf("Creando el directorio %s\n",argv[1]);
    mkdir(argv[1],0755);

    char path[255];
    FILE *PTR_File;
    FILE *Probe_file;


    Checked =0;
    while (Checked == 0)
    {
        sprintf(path,"./%s/%s.txt",argv[1],argv[2]);
        Probe_file = fopen(path,"r");
        if(!Probe_file){
            printf("Creando el directorio %s\n",path);
            creat(path,0777);
        }
        else{
            printf("--ERROR-- El documento ya existe, proporcione un nombre diferente\n");
            fflush(stdin);
            scanf("%s",Test);
            argv[1]= Test;
            printf("%s se definio como el nuevo nombre del documento\n",argv[2]);
        }
    }

    int Desc_file;
    char mensaje[250];
    char *mensaje_Ptr = &(mensaje[0]);
    int SizeMsg;
    int NumBytes;

    return 0;
}
