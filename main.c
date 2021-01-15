//Trabalho3. ED1.
//Marianna Karenina de Almeida Flores


//<<< Tradutor >>>>
 
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

//Definicoes

struct NO{
	
	int acessos;
    char portugues [25]; //palavra em portugues
    char ingles [25]; 	//palavra em ingles
    
    int altura;
    struct NO *esq;
    struct NO *dir;
    
};

typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada n�
    free(raiz);//libera a raiz
}


int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}



//<<<<<<<<< Insere >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void RotacaoLL(ArvAVL *A){//LL
    //printf("RotacaoLL\n");
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A){//RR
   // printf("RotacaoRR\n");
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}


//<<<<< Insere >>>>>>>>
int insere_ArvAVL(ArvAVL *raiz, char valor_ing[], char valor_por[], int valor_acessos ){ 	//valor = palavra em ingles 
    int res;
    
    if(*raiz == NULL){//�rvore vazia ou n� folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;
		
		strcpy((*novo).ingles, valor_ing);
		strcpy((*novo).portugues, valor_por);
        novo->acessos = valor_acessos;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
      if (strcmp (valor_ing, (atual->ingles)) < 0){	
    //if(valor < atual->info){
        if((res = insere_ArvAVL(&(atual->esq), valor_ing, valor_por, valor_acessos)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                //if(valor_ing < (*raiz)->esq->ingles ){
                if(strcmp (valor_ing, (*raiz)->esq->ingles) < 0  ){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
    	if (strcmp (valor_ing, (atual->ingles)) > 0){
        //if(valor > atual->info){
            if((res = insere_ArvAVL(&(atual->dir), valor_ing, valor_por, valor_acessos)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                   // if((*raiz)->dir->ingles < valor_ing){
                   if(strcmp (valor_ing, (*raiz)->dir->ingles) > 0  ){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        //printf("%d\n",(*raiz)->info);
        printf("acessos: %d \n", (*raiz)->acessos);
		printf("portugues: %s \n", (*raiz)->portugues);
		printf("ingles: %s \n", (*raiz)->ingles);
		printf("H(%d) fb(%d) \n", altura_NO(*raiz),fatorBalanceamento_NO(*raiz));
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

//<<<<<<<<<<<<< Traducao >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int traducao(ArvAVL *raiz){
	
	char valor[25]; //palavra que ser� traduzida
	
	scanf("%s", valor);

	
    if(raiz == NULL){
  
    	 return 0;
	}
    
	 
    struct NO* atual = *raiz;
    
    if(strcmp (valor, (*raiz)->ingles ) == 0){
    	
			printf("%s\n", atual ->portugues);
        	atual ->acessos = atual ->acessos +1;
      
            return 1;
            
	}

   	while(strcmp (valor, (*raiz)->ingles ) != 0){
   		  		
       if (strcmp (valor, (atual->ingles)) == 0){
	   	
        	printf("%s\n", atual ->portugues);
        	atual ->acessos = atual ->acessos +1;
  
            return 1;
        }
    
       if (strcmp (valor, (atual->ingles)) > 0 ){

            atual = atual->dir;
        }else{
     
            atual = atual->esq;
        }
         
        
}

    return 0;
}



//<<<<<< Auto_Completa>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void auto_completar (ArvAVL *raiz, char valor[], int num_min_acessos){
	
	int tamanho = 0;

		tamanho = strlen(valor); //recebe o tamanho da string que deve ser auto_completada
	
	char teste [25];
	
	if(raiz == NULL)
        return;
    
    if(*raiz != NULL){
    	
       auto_completar (&((*raiz)->esq), valor, num_min_acessos );
       
     
     		if((*raiz)->acessos >= num_min_acessos){
  
     			memset(teste, '\0', sizeof(teste));
     			
     			strncpy(teste,(*raiz)->ingles, tamanho);
     
     		
     				if(strcmp (valor, teste) == 0){
     			
						 printf("%s\n", (*raiz)->ingles);
				 
					 }	
			 }
      
        auto_completar (&((*raiz)->dir), valor, num_min_acessos);
    }
	
}

// main
int main (){
	
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Arquivo dict.txt e add em arvore

	FILE *file;							
	file = fopen ("dict.txt", "r");

	if(file == NULL){
		printf ("Nao foi possivel abrir o arquivo. \n");
		getchar();
			exit(0);
	}	

	ArvAVL* arvore;
	
	char ingles[25];
	char portugues[25];
	int acessos = 0;
	char auto_complete [25];

	
	arvore = cria_ArvAVL();

	 fscanf(file, "%d%*c", &acessos);
	 
	while (acessos != -1) {
		
	
		fscanf(file,"%s%*c%s%*c", ingles, portugues);
	    	insere_ArvAVL(arvore, ingles, portugues, acessos);
	    	
		fscanf(file, "%d%*c", &acessos);
	}

	fclose (file);
	
 //  emOrdem_ArvAVL(arvore);
    
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Comandos usuario

	int comando;

	 scanf("%d", &comando);
	//getchar();
	
	while (comando != -1) {

		if (comando == 0){		//chama_traducao
			traducao(arvore);
		 }
		if (comando > 0 ) { 	//chama_autocompletar
		
			scanf("%s", auto_complete);
			auto_completar(arvore, auto_complete, comando);
		 }
		
		scanf("%d", &comando);
		
	}
		
		libera_ArvAVL(arvore);
	
		return 0;
}
