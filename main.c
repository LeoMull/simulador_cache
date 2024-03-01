#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <time.h>

void add_lru(int *lista, int size, int val, int pos_substituida){
    if(pos_substituida){
        for(int i = pos_substituida ; i < size - 1 ; i++){
            lista[i] = lista[i+1];
        }
        lista[size - 1] = val;
        return;
    }

    for(int i = 0; i < size - 1 ; i++){
        lista[i] = lista[i+1];
    }
    lista[size - 1] = val;
}

enum{
    f,
    r,
    l
}substituicao;

int main()
{
    int nsets = 256, bsize = 4, assoc = 1, address, temp_address, temp;
    int hit = 0, miss_comp = 0, miss_conf = 0, miss_capa = 0, offset, pol_subs=1;
    
   // srand( (unsigned)time(NULL) );
    //printf("%d", nsets);
    //char addresses[30];
    /*
    Pega parametros para tamanho da cache
    */
    //scanf("%d %d %d", &nsets, &bsize, &assoc/*, &addresses*/);
    

    int cache_val[nsets][assoc];
    int cache_tag[nsets][assoc]; // Esse precisa ser em binário? Não

    int nbits_offset = log10(bsize)/log10(2);
    int nbits_index = log10(nsets)/log10(2);


    int nbits_tag = 32 - nbits_offset - nbits_index;

    FILE *fp = fopen("enderecos/bin_1000.bin", "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return 0;
    }
    
    while (fread(&address, sizeof(int), 1, fp))
    {   
        int address_tag, index, control;
        control = 0;

        if(pol_subs == 0){
            offset = rand()% assoc;
        }
        if(pol_subs == 1){
            if(offset < assoc) {
                offset++;
            }else{
                offset = 0 ;
            }
        }


        //Calcula o endereço
        address_tag = address << nbits_index + nbits_offset;
        index = address << nbits_offset;
        index = index >> nbits_tag + nbits_offset;
        
        /*
        printf("Address %d\n", address);
        // Fazer lógica de verificar hit
        printf("tag = %u, index = %d\n", address_tag, index);
        */

        //procura se terá hit    
        for( int i = 0; i < assoc ; i++ ){
            if(cache_tag[index][i] == address_tag && cache_val[index][i] == 1){
                hit++;
                control = 1;    
                break;
            }
        }
        //decide qual tipo de miss
        if(control == 0){
            if(cache_val[index][offset] == 0){ 
                miss_comp++;
                cache_val[index][offset] = 1;
                cache_tag[index][offset] = address_tag;
            }else{
                miss_capa++;
                cache_tag[index][offset] = address_tag;
            }
        }        
    }   
        
    
    fclose(fp);
    printf("hit = %d, miss capa = %d, miss compu = %d", hit, miss_capa, miss_comp);
    return 0;
}