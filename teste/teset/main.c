#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
    char current_patch[1024];
    char file_name[]="layout/teste.txt";
    char absolute[2048];
    if(getcwd(current_patch,sizeof(current_patch))!= NULL)
    {
        snprintf(absolute,sizeof(absolute),"%s/%s",current_patch,"");
    }
    
    unsigned tamanho=strlen(absolute)-6;
    char n1[tamanho];
    strncpy(n1,absolute,tamanho);
    strcat(n1,file_name);
    printf("ola %s",n1);
}