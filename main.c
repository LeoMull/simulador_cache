#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>

void decimalParaBinario(int numero) {
    if (numero == 0) {
        printf("0");
        return;
    }

    int binario[32];  // Assumindo que um inteiro é de 32 bits
    int indice = 0;

    // Converte para binário
    while (numero > 0) {
        binario[indice++] = numero % 2;
        numero /= 2;
    }

    // Imprime o resultado em ordem reversa
    printf("\nRepresentação binária: ");
    for (int i = indice - 1; i >= 0; i--) {
        printf("%d", binario[i]);
    }
}

int main()
{
    int nsets = 128, bsize = 1, assoc = 1, address, temp_address;
    int hit = 0, miss_comp = 0, miss_conf = 0, miss_capa = 0;
    printf("%d", nsets);
    //char addresses[30];
    /*
    Pega parametros para tamanho da cache
    */
    //scanf("%d %d %d", &nsets, &bsize, &assoc/*, &addresses*/);
    

    int cache_val[nsets * bsize];
    int cache_tag[nsets * bsize]; // Esse precisa ser em binário? Não

    int nbits_offset = 0;
    int nbits_index = 7;


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

        address_tag = address << nbits_index;
        
        temp_address = address_tag >> nbits_index;
        
        //index = address ^ temp_address;

        index = address >> nbits_tag;
        
        
        

        printf("Address %d\n", address);
        // Fazer lógica de verificar hit
        printf("tag = %u, index = %d\n", address_tag, index);
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