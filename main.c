#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _REG_FIXO_AUX {
    char uf[2];
    char nomeUf[17];
    char mesorregiaoGeo[20];
    char nomeMeso[31];
    char microGeo[20];
    char nomeMicro[33];
    char municipiCod[8];
    char codMunCompl[23];
    char nomeMunicipi[29];
} REG_FIXO_AUX;

typedef struct _REGISTRO {
    int uf;
    char nomeUf[18];
    int mesorregiaoGeo;
    char nomeMeso[32];
    int microGeo;
    char nomeMicro[34];
    int municipiCod;
    int codMunCompl;
    char nomeMunicipi[30];
} REGISTRO;

int main()
{
    FILE *fp;
    char buffer[4096], *p, estadoAtual[18];
    REG_FIXO_AUX aux;
    int countMun = -1;
    REGISTRO reg;

    if( (fp=fopen("ibge_municipios_coluna_fixa.txt","rt")) == NULL ) {
        printf("Arquivo nao encontrado.\n");
        exit(-1);
    }
    // pular o cabeçalho
    fgets(buffer,4096,fp);
    //
    while( !feof(fp) ) {
        // limpa o buffer
        memset(buffer,0, 4096);
        fgets(buffer,4096,fp);
        if( strlen(buffer) < 20 ) {
           break;
        }
        p = buffer;
        // remove a quebra de linha
        while( *p != '\0' ) {
            if( *p == '\n' || *p == '\r' ) {
                *p='\0';
                break;
            }
            p++;
        }
        // comeca a conversao da linha buffer para o registro auxiliar
        memcpy((void *)&aux, buffer, sizeof(REG_FIXO_AUX));
        // colocando o \0 nos delimitadores
        //
        // faz a conversao dos tipos
        memset((void *)&reg , 0, sizeof(REGISTRO) );
        // por causa da funcao strcpy, forcar o \0 no final da string
        aux.uf[1] = '\0';
        aux.nomeUf[16] = '\0';
        aux.mesorregiaoGeo[19] = '\0';
        aux.nomeMeso[30] = '\0';
        aux.microGeo[19] = '\0';
        aux.nomeMicro[32] = '\0';
        aux.municipiCod[7] = '\0';
        aux.codMunCompl[22] = '\0';
        aux.nomeMunicipi[28] = '\0';
        //
        // realiza as conversoes
        //
        reg.uf = atoi(aux.uf);
        strcpy(reg.nomeUf , aux.nomeUf );
        reg.mesorregiaoGeo = atoi(aux.mesorregiaoGeo);
        strcpy(reg.nomeMeso , aux.nomeMeso );
        reg.microGeo = atoi(aux.microGeo);
        strcpy(reg.nomeMicro , aux.nomeMicro );
        reg.municipiCod = atoi(aux.municipiCod);
        reg.codMunCompl = atoi(aux.codMunCompl);

        countMun++;
        if(strcmp(estadoAtual, reg.nomeUf) != 0 && strcmp(estadoAtual, "") != 0){
            printf("%s\t%d\n", estadoAtual  , countMun );
            countMun = 0;
        }
        strcpy(estadoAtual , reg.nomeUf);
    }
    printf("%s\t%d\n", estadoAtual  , countMun + 1 );
}


