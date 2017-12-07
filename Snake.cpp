#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

// Definindo aparÃªncia 
#define cabenhoca '@'         //variavel definida da parte inicial da cobra
char tronconhoca='O';         // Variaveis Globais  parte do corpo e comida que aparecerá no programa
char comidoca='x';             

// struct de posicao
struct posicao{
  int posix;   //estrutura com 2 posiçoes (linha e coluna)
  int posiy;                
};

// init cabeca
void preencherinicio(struct posicao *pont,int tam){ // Função irá preencher apenas a posição inicial da cobra
  for(int i=0;i<tam;i++){
    (pont+i)->posix=3;
    (pont+i)->posiy=5;
  }
}

// init comida
void preenchercomida(struct posicao *pont){   //Função utilizada para preencher onde a comida aparecerá  inicialmente
  pont->posix=3;
  pont->posiy=0;
}

  
// Atualiza posiÃ§Ã£o dos elementos na matriz
void mostramatrizcampo(char matriz[10][10],struct posicao *pont,struct posicao *comida,int tam){    //Função para colocar cobra e comida na area
  for(int x=0;x<10;x++){
    for(int y=0;y<10;y++){
      matriz[x][y]=' ';
    }
  }
 
  for(int n=0;n<tam;n++){                                                                                  	//	Pecorre a quantidade de pedaços da cobra
    for(int x=0;x<10;x++){
      for(int y=0;y<10;y++){
        if(((pont+n)->posix == x) && ((pont+n)->posiy == y)){
          if(n==0){
            matriz[x][y] = cabenhoca;                    //Preenche o inicio da cobra com "@" declarado no começo do codigo
          }
          else{
            matriz[x][y] = tronconhoca;                  //Preenche com o pedaço do tronco da cobra "O" declarado com variavel global no inicio
          }
        }
      }
    }
  }
  for(int x=0;x<10;x++){                                      //Preenche a posição da comida na matriz
    for(int y=0;y<10;y++){
      if((comida->posix == x) && (comida->posiy == y)){
        matriz[x][y] = comidoca;                              
      }
    }
  }
  for(int x=0;x<10;x++){
    printf("|");                       //Cria a matriz campo
    for(int y=0;y<10;y++){
      printf("%c",matriz[x][y]);
    }
    printf("|\n");
  }
}
// Atualiza posiÃ§Ã£o da cabeÃ§a apÃ³s movimento
void salvaposicao(struct posicao *pont,struct posicao *corpo){          //Pega a posição antiga da cobra e salva a posição que a msm se moveu
  corpo->posix = pont->posix;
  corpo->posiy = pont->posiy;
}

// Atualiza a posiÃ§Ã£o do corpo apÃ³s movimento
void attposicao(struct posicao *pont,struct posicao *corpo,int tam){        //Move o corpo para a posição seguinte
  for(int i=1;i<tam;i++){
    (pont+i)->posix = (corpo+(i-1))->posix;
    (pont+i)->posiy = (corpo+(i-1))->posiy;
  }
}

// Muda posiÃ§Ã£o da comida aleatoriamente
void mudacomida(struct posicao *comida,struct posicao *pont,int tam){      //Função colocar aleatoriamente a comida na matriz
  srand(time(NULL));
  comida->posix = rand()%9;
  comida->posiy = rand()%9;
}


// Game over 
int gameover(struct posicao *pont,int tam){
  int x=0;
  for(int i=1;i<tam;i++){                                                	//Verifica se a posição da cabeça é igual ao corpo da cobra
    if((pont->posix) == ((pont+i)->posix) && (pont->posiy) == ((pont+i)->posiy)){
      x=x+1;
    }
  }
  if((pont->posix)<0 || (pont->posiy)<0 || (pont->posix)>9 || (pont->posiy)>9){        //Verifica se a cobra bateu nas paredes
    x=x+1;
    
  }
  if(x>0){
    puts("GAMEOVER!!!\n");
		  puts("SNAKE C 2K17\n");
    puts("Dupla:Gilmar de Pontes e Marco Felipe\n");
		  puts("Obrigado por testar o nosso jogo!!!");        //Caso x seja incrementado ou ele bateu na parede ou em seu corpo, o que resultará no final do jogo
    return(1);
  }
  else {
    return(0);
  }
}

// verifica se a allocaÃ§Ã£o foi feita corretamente 
int allocPosicao(struct posicao *pont){                 //Verificação de alocação
  if(pont==NULL){
    puts("Erro de alloc");
    return 1;
  }
}
void menu(){
	puts("1.Novo jogo");
	puts("2.Continuar jogo");
	puts("3.Sair");
}


/****** MAIN *******/
int main(){
  int op;
  char matrizcampo[10][10];  // mundo fisico
  int flag=0;
  int tam=4;  // tamanho da cobra
  
  // posiÃ§Ã£o dos elementos do jogo
  struct posicao *cobra;
  struct posicao *corpo;
  struct posicao *comida;
  
  // init dos elementos do jogo
  cobra  = (struct posicao*) malloc(sizeof(struct posicao)*tam);
  corpo  = (struct posicao*) malloc(sizeof(struct posicao)*tam);          //Cria espaço e preenche funçoes iniciais
  comida = (struct posicao*) malloc(sizeof(struct posicao)*1);
  
  allocPosicao(cobra);
  allocPosicao(corpo);
  allocPosicao(comida);
  
  preencherinicio(cobra,tam);
  preenchercomida(comida);
  
  mostramatrizcampo(matrizcampo,cobra,comida,tam);
  
  char tecla;                             //Controle do usuario
  int tempo = 0;
  
  while(1) {
	if(flag==0){
		system("cls");
    	menu();
    	scanf("%d",&op);
    	while(op>3){		//enquanto o usuario teclar errado
       		system("cls");
       		menu();
       		puts("Comando invalido!");
       		scanf("%d",&op);
		}
			switch(op){
				 case 1:
        			system("cls");
					// Removendo se tiver algo
					remove("snake.txt");
					if((allocPosicao(cobra)==1)||(allocPosicao(corpo)==1)||(allocPosicao(comida)==1)){  
	    				free(cobra);    
						free(corpo);     
						free(comida);
					}
					tam=4;
				    cobra=(struct posicao*) malloc(sizeof(struct posicao)*tam);    //Alocando denovo     
				    allocPosicao(cobra);                                    
				    corpo=(struct posicao*) malloc(sizeof(struct posicao)*tam);             
				    allocPosicao(corpo);
				    comida=(struct posicao*) malloc(sizeof(struct posicao)*1);               
				    allocPosicao(comida);
				    // Preenchendo as base
				    preenchercomida(comida);
				    preencherinicio(cobra,tam);
    				mostramatrizcampo(matrizcampo,cobra,comida,tam); 
    				flag=flag+1;
    				break; 
    			case 2:
        	        system("cls");
    				FILE *carregar;
					carregar=fopen("snake.txt","r");
					if(carregar==NULL){			//Verifica se há algum arquivo
						puts("Erro");
						break;
					}
					free(cobra);    //Limpa a memoria 
					free(corpo);     
					free(comida);
					fscanf(carregar,"%d",&tam);
					cobra =(struct posicao*) malloc(sizeof(struct posicao)*tam);		//Aloca denovo
					allocPosicao(cobra);
					corpo =(struct posicao*) malloc(sizeof(struct posicao)*tam);
					allocPosicao(corpo);
					comida =(struct posicao*) malloc(sizeof(struct posicao)*1);
					allocPosicao(comida);
					for(int i=0;i<tam;i++){										//Ler os arquivos
						fscanf(carregar,"%d",&(cobra+i)->posix);
						fscanf(carregar,"%d",&(cobra+i)->posiy);
					}
					for(int j=0;j<tam;j++){
						fscanf(carregar,"%d",&(corpo+j)->posix);
						fscanf(carregar,"%d",&(corpo+j)->posiy);
					}
					fscanf(carregar,"%d",&tempo);
					printf("%d\n",tempo);
					
					fscanf(carregar,"%d",&comida->posix);
					fscanf(carregar,"%d",&comida->posiy);
					fclose(carregar);
					mostramatrizcampo(matrizcampo,cobra,comida,tam);
					flag=flag+1;
					break;	
			case 3:
    				system("cls");
							  puts("SNAKE C 2K17\n");
    						  puts("Dupla:Gilmar de Pontes e Marco Felipe\n");
		  					  puts("Obrigado por testar o nosso jogo!!!"); 
					return 0;
					break;
		}
	}
    tecla=getch();
    
    if((tecla == 'q')||(tecla == 'a')||(tecla == 's')||(tecla == 'd')||(tecla == 'w')||(tecla == 'r')){            //Verifica se usuario aperta as teclas corretas  
	  if((tecla != 'r')&&(tecla != 'q')){
	  tempo=tempo+1;
	  }
      if(tempo>5){                                                       //Acrescenta tempo para limitar a cobra a chegar a comida
        mudacomida(comida,cobra,tam);
        tempo=0;                                               	
      }
      
      switch(tecla){
        case 's': cobra->posix = cobra->posix+1;        //Movimento da cobra
        break;
        case 'w': cobra->posix = cobra->posix-1;
        break;
        case 'd': cobra->posiy = cobra->posiy+1;
        break;
        case 'a': cobra->posiy = cobra->posiy-1;
        break;
        case 'q':
        		puts("SNAKE C 2K17\n");
    			puts("Dupla:Gilmar de Pontes e Marco Felipe\n");
		  		puts("Obrigado por testar o nosso jogo!!!"); 
				return 0;
        
        case 'r':
        FILE *carregar;				//Colocando as variveis no arquivo
		carregar=fopen("snake.txt","w");
		fprintf(carregar," %d",tam);
		for(int i=0;i<tam;i++){
		fprintf(carregar," %d", (cobra+i)->posix);
		fprintf(carregar," %d", (cobra+i)->posiy);
		}
		for(int i=0;i<tam;i++){
		fprintf(carregar," %d", (corpo+i)->posix);
		fprintf(carregar," %d", (corpo+i)->posiy);
		}
		fprintf(carregar," %d",tempo);
		fprintf(carregar," %d",(comida)->posix);
		fprintf(carregar," %d",(comida)->posiy);
		fclose(carregar);
        break;
        system("cls");
        puts("SNAKE C 2K17\n");
        puts("Dupla:Gilmar de Pontes e Marco Felipe\n");
				    puts("Obrigado por testar o nosso jogo!!!");
        break;
      }

      if(gameover(cobra,tam)){                //Verificação de game over
        return 0;
        break;
      };
      
      if((cobra->posix == comida->posix) && (cobra->posiy == comida->posiy)){ //verifica se cabeça esta junto com doce no mesmo lugar da matriz
        attposicao(cobra,corpo,tam);
        tempo=0;
        tam = tam+1;                            //aumenta o tamnho da cobra
        cobra= (struct posicao*) realloc(cobra,sizeof(struct posicao)*(tam));      // realoca a posição
        allocPosicao(cobra);
        (cobra+(tam-1))->posix = (corpo+(tam-2))->posix;              // corpo recebe a posição do proximo elemento
        (cobra+(tam-1))->posiy = (corpo+(tam-2))->posiy;
        mudacomida(comida,cobra,tam);          	// muda a posição da comida aleatoriamente	
        system("cls"); //apaga a area
      } else {
      	if(tecla!='r'){
        	attposicao(cobra,corpo,tam);
        }
        system("cls");
      }
      
      corpo = (struct posicao*) realloc(corpo,sizeof(struct posicao)*(tam));      //realoca após o movimento
      if(allocPosicao(corpo)==1){
        return 0;
      };
      for(int i=0;i<tam;i++){                            //Reorganização da cobra
        salvaposicao((cobra+i),(corpo+i));               
      }

    } else {
      system("cls");                       
      puts("Aperte A,W,S,D para jogar,Q para fechar e R para salvar.");
    }
  	mostramatrizcampo(matrizcampo,cobra,comida,tam); // mostra a area atualizada com nova posição da cobra
  }

  free(cobra);     //Libera a memória
  free(comida);
  system("pause");
}
