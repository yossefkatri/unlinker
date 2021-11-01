#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>

void show_hex(unsigned char * obj , size_t size)
{   
    for(size_t i =0; i<size; ++i)
    {
        printf("%02x ", obj[i]);
        if(!((i+1)%16))
        {
            printf("\n");
        }
        else if(!((i+1)%8))
        {
             printf("   ");
        }
        
    }
    printf("\n");
}
int main(int argc, char* argv[])
{
    /*if(argc != 2)
    {
        printf("you should put one parmeter\n");
        exit(1);
    }*/
    //FILE* executable = fopen(argv[1],"rb");
    FILE* executable = fopen("a32.out","rb");
    if(executable == NULL)
    {
        printf("Error: could not open file %s \n", argv[1]);
        return -1;
    }
    char magic[5];
    fgets(magic, sizeof(magic), executable);
    if(magic[0] != 127 || strcmp(magic+1, "ELF"))
    {
        printf("Error: this file isn't a ELF file \n");
        fclose(executable);
        return -1;
    }
    int class = fgetc(executable);
    if(class == 1)
    {
        printf("32-bits file \n");
        fseek(executable,0,SEEK_SET); //move the pointer to the beginning
        Elf32_Ehdr elfheader;
        fread((void *) &elfheader,sizeof(Elf32_Ehdr),1,(FILE*)executable);
        show_hex((char *) &elfheader , sizeof(elfheader));
    }
    else if(class)
    {
        printf("64-bits file \n");
    }
    else
    {
        printf("none(invalid) \n");
    }
    fclose(executable);
    return 0;

    
}