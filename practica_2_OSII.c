#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
    int Cheked=0;
    char Reemplazo[50],Test[20];
    DIR *Direction;

    if(argc < 2)
    {
        printf("Se necesitan dos argumentos:\n 1er argumento.Nombre del directorio\n 2do argumento.Nombre del archivo\n");
        return 1;
    }

    while (Cheked == 0)
    {
        if((Direction = opendir(argv[1])) ==NULL){
            printf("Archivo valido\n);
            Cheked =1;
        }
        else
        {
            printf("--ERROR-- El directorio ya existe, proporcione un nombre diferente\n");
            fflush(stdin);
            scanf("%s",Test);
            argv[1] = Test;
            printf("%s Se definio como el nuevo nombre del directorio\n",argv[1]);

        }

    }

    printf("Creando el directorio %s\n",argv[1]);
    mkdir(argv[1],0755);

    char path[255];
    FILE *filePtr;
    FILE *test_file;

    Cheked =0;
    while (Cheked == 0)
    {
        sprintf(path,"./%s/%s.txt",argv[1],argv[2]);
        test_file = fopen(path,"r");
        if(!test_file){
            printf("Creando el directorio %s\n",path);
            creat(path,0777);
            Cheked =1;
        }
        else{
            printf("--ERROR-- El documento ya existe, proporcione un nombre diferente\n");
            fflush(stdin);
            scanf("%s",Test);
            argv[1]= Test;
            printf("%s se definio como el nuevo nombre del documento\n",argv[2]);
        }
    }

    int desc_file;
    char mensaje[250];
    char *mensaje_Ptr = &(mensaje[0]);
    int SizeMsg;
    int NumBytes;

    desc_file = open(path,O_RDWR);
    if(desc_file == -1){
        printf("Error al abrir el archivo\n");
        return -1;
    }
    else{
        printf("Exito al abrir el archivo\n");
    }

    sprintf(mensaje_Ptr,"%s","Equipo: Los Bichos\nIntegrantes:\nRendo Deloya Alan\nHernandez Martinez Ramon\nCassandra Astrid Paulin\n");
    SizeMsg = strlen(mensaje_Ptr);
    NumBytes = write(desc_file,mensaje_Ptr,SizeMsg);

    if(NumBytes == -1){
        printf("--ERROR-- no se logro escribir en el archivo\n");
        return -1;
    }

    int links;
    char path_linkshard[255];
    char path_linksoft[255];


    sprintf(path_linkshard,"./%sHard.txt",argv[2]);
    printf("%s\n",path_linkshard);

    links = link(path,path_linkshard);

    if(links == -1){
        printf("Error al crear la liga\n");
        return -1;
    }
    else{
        printf("Liga creada\n");
    }

    sprintf(path_linksoft,"./%sSoft.txt",argv[2]);
    printf("%s\n",path_linksoft);
    links = symlink(path,path_linksoft);
    if(links == -1){
        printf("Error al crear la liga\n");
        return -1;
    }
    else{
        printf("Liga creada\n");
    }

    struct stat archInfo;
    stat(path,&archInfo);
    printf("El inodo de %s es: %ld\n",path,archInfo.st_ino);
    printf("El tamaño de %s es de: %ld bytes\n",path,archInfo.st_size);
    printf("El numero de enlaces que tiene %s es: %ld\n",path,archInfo.st_nlink);

    DIR *dir;
    struct dirent *entry;

    if((dir = opendir("./"))==NULL){
        printf("--ERROR-- No se logro abrir el archivo\n");
    }
    else{
        printf("Contenido de la carpeta de trabajo\n");
        while ((entry=readdir(dir))!=NULL)
        {
            printf("Nombre: %s\ninodo: %ld\n\n",entry->d_name,entry->d_ino);
        }
        closedir(dir);

    }




    return 0;
}
