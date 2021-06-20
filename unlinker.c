#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

void show_hex(char * obj , size_t size)
{   
    for(size_t i =0; i<size;++i)
    {
        printf("%02x ", obj[i]);
    }
    printf("\n");
}
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("you should put one parmeter\n");
        exit(1);
    }
    FILE* executable = fopen(argv[1],"rb");
    Elf32_Ehdr elfheader;
    fread((void *) &elfheader,sizeof(Elf32_Ehdr),1,(FILE*)executable);
    show_hex((char *) &elfheader , sizeof(Elf32_Ehdr));
    fclose(executable);
    return 0;
}