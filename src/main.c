#include <stdio.h>
#include <string.h>

int main()
{
    int nsets, bsize, assoc;
    char addresses[30];
    
    scanf("%d %d %d %s", &nsets, &bsize, &assoc, &addresses);

    int cache_val[nsets * assoc];
    int cache_tag[nsets * assoc]; // Esse precisa ser em binário né?

    int nbits_offset = bsize % 2;
    int nbits_index = nsets % 2;

    int nbits_tag = 32 - nbits_offset - nbits_index;

    FILE *fp = fopen("addresses", "rb");

    int miss_comp = 0, miss_conf = 0, miss_capa = 0;

    if (fp = NULL)
    {
        prinf("Erro ao abrir arquivo.\n");
        return;
    }

    while (!EOF)
    {
        int *address, tag, index;

        fread(address, sizeof(int), 1, fp); // Não tenho ctz se tá certo
        
        // Fazer lógica de verificar hit

        fclose(fp);
    }

    return 0;
}
