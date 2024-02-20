#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
    int nsets = 128, bsize = 1, assoc = 1, address;
    int hit = 0, miss_comp = 0, miss_conf = 0, miss_capa = 0;
    //char addresses[30];
    /*
    Pega parametros para tamanho da cache
    */
    //scanf("%d %d %d", &nsets, &bsize, &assoc/*, &addresses*/);
    

    int cache_val[nsets * assoc];
    int cache_tag[nsets * assoc]; // Esse precisa ser em binário? Não

    int nbits_offset = 0;
    int nbits_index = 7 ;

    int nbits_tag = 32 - nbits_offset - nbits_index;

    FILE *fp = fopen("bin_100.bin", "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return 0;
    }
    
    while (fread(&address, sizeof(int), 1, fp))
    {
        int address_tag, index;
        printf("%d \n", address);
        address_tag = address >> (32 - nbits_tag);
        index = address << nbits_tag;
        index = index >> (32 - nbits_offset + nbits_tag);

        //printf("%d\n", address);
        // Fazer lógica de verificar hit
        printf("tag = %d, index = %d\n", address_tag, index);
        if(cache_tag[index] == address_tag && cache_val[index] == 1){
            hit++;   
        }else{
            if(cache_val[index] == 0){ 
                miss_comp++;
                cache_val[index] = 1;
                cache_tag[index] = address_tag;
            }else{
                miss_capa++;
                cache_tag[index] = address_tag;
            }

        }
        
    }
    fclose(fp);
    printf("hit = %d, miss capa = %d, miss compu = %d", hit, miss_capa, miss_comp);
    return 0;
}