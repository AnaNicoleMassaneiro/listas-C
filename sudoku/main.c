#include <stdio.h>
#include <stdlib.h>

#define NUM_VALORES 9
#define TAM_GRUPOS  3
const valores[NUM_VALORES] = {1,2,3,4,5,6,7,8,9};

void valoresAusentesLinha(char jogo[][NUM_VALORES], int numLinha, char lin[] );
void valoresAusentesColuna(char jogo[][NUM_VALORES], int numColuna, char col[] );
void valoresAusentesGrupo(char jogo[][NUM_VALORES], int grupo, char grp[] );
void valoresPossiveisCelula(char jogo[][NUM_VALORES], int lin, int col, char possiveis[] );
void valoresImpossiveisCelula(char jogo[][NUM_VALORES], int lin, int col, char impos[] );
void intersecao(char v1[],char v2[], char resultado[]);

void mostre(const char *str, char valores[]);

int main(int argc, char *argv[]) {
	// configuracao do jogo inicial
	char jogo[ NUM_VALORES ][ NUM_VALORES ]  = { { 9,4,0, 1,0,2, 0,5,8 } ,
	                    { 6,0,0, 0,5,0, 0,0,4 } ,
	                    { 0,0,2, 4,0,3, 1,0,0 } ,

	                    { 0,2,0, 0,0,0, 0,6,0 } ,
	                    { 5,0,8, 0,2,0, 4,0,1 } ,
	                    { 0,6,0, 0,0,0, 0,8,0 } ,

	                    { 0,0,1, 6,0,8, 7,0,0 } ,
	                    { 7,0,0, 0,4,0, 0,0,3 } ,
	                    { 4,3,0, 5,0,9, 0,1,2 } };
	// variaveis auxiliares para obter o retorno das funções
	// isso é necessario, porque não foi visto alocação dinâmica ainda.
	char linha[NUM_VALORES], coluna[NUM_VALORES], grupo[ NUM_VALORES ], pode[ NUM_VALORES ], naopode[ NUM_VALORES ] ;
	int i,j,qdade;

	// pergunta: 1.Quais valores faltam na linha X?
	valoresAusentesLinha(jogo, 0, linha);
	/*printf("Resultado pergunta 1 - Quais os valores ausentes na linha X? para x=1\n");
	for(i=0 ; i<NUM_VALORES ; i++ ) {
		if( linha[i] > 0 ) {
			printf(" %d ",linha[i]);
		}
	}
	printf("\n\n");*/
	mostre("Resultado pergunta 1 - Quais os valores ausentes na linha X? para x=1\n", linha);

	//
	// pergunta: 2.Quais valores faltam na coluna Y?
	valoresAusentesColuna(jogo, 0, coluna);
	mostre("Resultado pergunta 2 - Quais os valores ausentes na coluna Y? para y=1\n", coluna);

	//
	// pergunta: 3.Quais valores faltam no grupo Z?
	valoresAusentesGrupo(jogo,0,grupo);
	mostre("Resultado pergunta 3 - Quais os valores ausentes no grupo Z? para z=1\n", grupo);

	//
	// pergunta: 4.Quais valores uma determinada célula pode conter?
	valoresPossiveisCelula(jogo, 1, 1, pode);
	mostre("Resultado pergunta 4 - Quais valores uma determinada célula pode conter? para cel 2,2\n", pode);

	//
	// pergunta: 5.Quais valores uma determinada célula pode conter?
	valoresImpossiveisCelula(jogo, 1, 1, naopode);
	mostre("Resultado pergunta 5 - Quais valores uma determinada célula não pode ter? para cel 2,2\n", naopode);

	//
	// pergunta: 6.Quantos valores possíveis por célula?
	printf("Lin\tCol\tQde\n");
	for(i=0 ; i<NUM_VALORES ; i++ ) {
		for(j=0 ; j<NUM_VALORES ; j++ ) {
			if( jogo[i][j] > 0 )
			   continue;
			qdade = quantidadeValoresPossiveis(jogo,i,j);
			printf("%2d\t%2d\t%d\n",i,j,qdade);
		}
	}
	return 0;
}

void inicializa(char vet[], const char valor,const int numElementos) {
	register i;
	for(i=0 ; i<numElementos ; i++ ) {
		vet[i] = valor;
	}
}


/*
 * 1.Quais valores faltam na linha X?
 * valoresAusentesLinha
 * params: jogo[][] - matriz da configuracao inicial, onde o valor 0 indica célula vazia.
 *         numLinha - indice da matriz referente a linha, de 0 a 8.
 *         lin[] - vetor que retorna os valores ausentes na linha.
 */
void valoresAusentesLinha(char jogo[][NUM_VALORES], int numLinha, char lin[] ) {
	int indVet = 0,i,j;
	char achou = 0;
	inicializa(lin,0,NUM_VALORES);

	for(i=0 ; i<NUM_VALORES ; i++ ) {
		achou = 0;
		for(j=0 ; j<NUM_VALORES ; j++ ) {
			if( jogo[numLinha][j] == valores[i] ) {
				achou = 1;
				break;
			}
		}
		if( !achou ) {
			lin[indVet] = valores[i];
			indVet++;
		}
	}
}

/*
 * valoresAusentesColuna
 * params: jogo[][] - matriz da configuracao inicial, onde o valor 0 indica célula vazia.
 *         numColuna - indice da matriz referente a coluna, de 0 a 8.
 *         col[] - vetor que retorna os valores ausentes na coluna.
 */
void valoresAusentesColuna(char jogo[][NUM_VALORES], int numColuna, char col[] ) {
	int indVet = 0,i,j;
	char achou = 0;
	//inicializa(lin,0,NUM_VALORES);
	for(i=0 ; i<NUM_VALORES ; i++ ) {
	    achou = 0;
	    for(j=0 ; j<NUM_VALORES ; j++ ) {
	    	if( jogo[j][numColuna] == valores[i] ) {
	    		achou = 1;
	    		break;
	    	}
		}
		if( !achou ) {
			col[indVet++] = valores[i];
		}
	}
	for(i=indVet ; i<NUM_VALORES ; i++ ) {
		col[i] = 0;
	}
}

/*
 * valoresAusentesGrupo
 * params: jogo[][] - matriz da configuracao inicial, onde o valor 0 indica célula vazia.
 *         grupo - indice da matriz referente ao grupo (0 a 8)
 *         grp[] - vetor que retorna os valores ausentes no grupo.
 */
void valoresAusentesGrupo(char jogo[][NUM_VALORES], int grupo, char grp[] ) {
	int linInicio = (int)(grupo / TAM_GRUPOS) * TAM_GRUPOS;
	int colInicio = (int)(grupo % TAM_GRUPOS) * TAM_GRUPOS;
	int linFim = linInicio + 3, colFim = colInicio + 3;
	int indVet = 0,i,j,k;
	char ocorre = 0;
	// para teste e visualizar o resultado das formulas
	//printf("Grupo %d lin0 %d col0 %d  lin1 %d col1 %d\n",grupo, linInicio,colInicio,linFim,colFim);
	inicializa(grp,0,NUM_VALORES);
	for(k=0 ; k<NUM_VALORES ; k++ ) {
		ocorre = 0;
		for(i=linInicio ; i<linFim ; i++ ) {
			for(j=colInicio ; j<colFim ; j++ ) {
				if( jogo[i][j] == valores[k] ) {
					ocorre = 1;
					goto NAODevemosUsarGOTO;
				}
			}
		}
		NAODevemosUsarGOTO:
		if( !ocorre )
			grp[indVet++] = valores[k];
	}
}

/*
 * valoresPossiveisCelula - os valores possiveis são os valores que não
 *          ocorrem na linha, na coluna ou no grupo.
 * params: jogo[][] - matriz da configuracao inicial, onde o valor 0 indica célula vazia.
 *         lin - linha da matriz (0-8)
 *         col - coluna da matriz (0,8)
 *         possiveis[] - vetor que retorna os valores ausentes na linha, na coluna e no grupo
 */
void valoresPossiveisCelula(char jogo[][NUM_VALORES], int lin, int col, char possiveis[] ) {
	char linha[NUM_VALORES], coluna[NUM_VALORES], grupo[ NUM_VALORES ];
	char comum[NUM_VALORES];
	int grpnum = ((int)(lin/TAM_GRUPOS))*TAM_GRUPOS +  ((int)(col/TAM_GRUPOS)) % TAM_GRUPOS;
	//printf("DEBUG: linha %d coluna %d grupo %d\n",lin,col,grpnum);
	valoresAusentesLinha(jogo, lin, linha);
	valoresAusentesColuna(jogo, col, coluna);
	valoresAusentesGrupo(jogo, grpnum, grupo );
	inicializa(possiveis,0,NUM_VALORES);
	//
	// calcula a interseção dos 3 conjuntos de valores possiveis
	intersecao(linha,coluna,comum);
	intersecao(comum,grupo,possiveis);
}

/*
 * valoresImpossiveisCelula - os valores impossiveis são os valores que
 *          ocorrem na linha, na coluna ou no grupo.
 * params: jogo[][] - matriz da configuracao inicial, onde o valor 0 indica célula vazia.
 *         lin - linha da matriz (0-8)
 *         col - coluna da matriz (0,8)
 *         impos[] - valores que ocorrem na linha ou na coluna ou no grupo
 */
void valoresImpossiveisCelula(char jogo[][NUM_VALORES], int lin, int col, char impos[] ) {
	char aux[NUM_VALORES];
	int i,j,indVet=0;
	char ocorre;
	inicializa(aux,0,NUM_VALORES);
	inicializa(impos,0,NUM_VALORES);
	valoresPossiveisCelula(jogo, lin, col, aux);
	for(i=0 ; i<NUM_VALORES ; i++ ) {
		ocorre = 0;
		for(j=0 ; j<NUM_VALORES ; j++ ) {
			if( valores[i] == aux[j] ) {
				ocorre=1;
				break;
			}
		}
		if( !ocorre ) {
			impos[indVet++] = valores[i];
		}
	}
}


int quantidadeValoresPossiveis(char jogo[][NUM_VALORES], int lin, int col ) {
	char aux[NUM_VALORES];
	int qdade=0,i;

	valoresPossiveisCelula(jogo,lin,col,aux);
	for(i=0 ; i<NUM_VALORES ; i++ ) {
		if( aux[i] > 0 )
		   qdade++;
	}
	return qdade;
}

void mostre(const char *str, char valores[]) {
	int i;
	printf("%s",str);
	for(i=0 ; i<NUM_VALORES ; i++ ) {
		if( valores[i] > 0 ) {
			printf(" %d ",valores[i]);
		}
	}
	printf("\n\n");
}

void intersecao(char v1[],char v2[], char resultado[]) {
	int i,j,k;
	inicializa(resultado,0,NUM_VALORES);
	for(i=0,k=0 ; i<NUM_VALORES ; i++) {
		for(j=0 ; j<NUM_VALORES ; j++ ) {
			if( v1[i] == v2[j] && v1[i] > 0 ) {
				resultado[k++] = v1[i];
			}
		}
	}
}
