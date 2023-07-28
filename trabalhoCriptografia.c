#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Aqui a Magica começa ☻
#define TAM 5000 // Define uma variável com o valor fixo de 5000

char * lerDados(){                                          //Esta função faz com que os dados sejam retornados para a main
    char * vetor;                                           //de forma que a string seja lida de forma completa.
    vetor = (char *)malloc(TAM * sizeof(char));             //Alocando o vetor de forma dinamica
                                                            
    printf("Digite a mensagem a ser criptografada :\n");    
    gets(vetor);                                            //Ultilizando a função gets para parar de ler somente quando encontar o '\0'

    return vetor;
}

int encontrarIndiceEspacos(char * vetPrinc,int * locEspacos){//Esta função recebe a String Principal e um Vetor que irá receber o índice dos espaços
    int numStr = strlen(vetPrinc);                           //utilizado nas string

    int i,j=0;

    for(i=0;i<=numStr;i++){                                  //Percorre a String principal carácter por carácter e todas vez que encontra  
        if((vetPrinc[i] == ' ')||(vetPrinc[i]== '\0')){      //um ' ' ele adiciona o valor do contador(índice) ao vetor de Espaços
            locEspacos[j] = i;                               //Que também irá retornar a quantidade de espaços contando com o '\0' 
            j++;                                             //assim também sendo a quantidade se Substrings 
        }
    }
    return j;
}

// Criptografar

char * adiantar(char * vetor,int localInicial,int locRecebe,int locEnvia){//Sendo uma função auxiliar, ela adianta caracteres em uma String
    int i;                                                                //Recebendo uma string, o local a qual ira inicial a troca de carácter,
    char * temp;                                                          //local que ira receber, e local que será enviado
    temp = (char*)calloc(TAM, sizeof(char));
    temp[0]='\0';

    strcat(temp,vetor);
    int num =strlen(vetor);

    for(i=localInicial;i<num;i++){                      //Tendo o local no qual ira inicial ele percorre a string até o fim
        temp[i+locRecebe]= vetor[i+locEnvia];           //Executando a troca de caracteres
    }                                                   //Retornando no fim a string com os carácteres adiantados
    
    return temp; //Ex: "@migo" -> "@mimigo"
}

char * abd(char * vetPrincipal,int inicio,int fim,char * caracter, int * contCaracter){//Esta função executa o primeiro padrão de criptografia Tudo e Abd
    char * temp;                                                                       //no qual deve trocar os carácteres '@', '#' e '$' por "Abd"
    int i,j=0,cont;                                                                    //Recebendo o vetor principal, o local de inicio e fim da Substring a ser
    temp = (char*)calloc(TAM, sizeof(char));                                           //trabalhada, assim como uma string de backup dos caracteres, e um contador
                                                                                       //que ira indicar o índice que deve se adicionado o carácter especial
    for(i=inicio;i<fim;i++){    //Preenche a String temporária                         //a string de backup
        temp[j] = vetPrincipal[i];
        j++;
    }

    cont=strlen(temp);
    int aux = *contCaracter;                //Para conseguir utilizar um índice, foi necessário utilizar uma variável auxiliar
    for(i=0;i<cont;i++){
        if(temp[i]=='#'){                   //Faz a comparação de cada carácter da string, assim que encontra um dos caracteres '@', '#' e '$', ele
            caracter[aux] = '#';            //será adicionado a string de backup, para que possa ser utilizada na descriptografia
            aux++;                          
            temp  = adiantar(temp,i,3,1);   //Em seguida ele utiliza a função auxiliar para adiantar a partir da posição do carácter mais 3 caracteres
            temp[i] = 'A';                  //ficando disponível para a substituição do "Abd", ja que ocupa 3 indices.
            temp[i+1] = 'b';                
            temp[i+2] = 'd';                
            cont =strlen(temp);             //Como o tamanho da string foi alterado, faço a conferencia novamente para não haver erros pelo tamanho
        }else if(temp[i]=='@'){             //Se repetindo o mesmo nas 3 condições, tendo apenas o carácter diferente
            caracter[aux] = '@';
            aux++;
            temp  = adiantar(temp,i,3,1);
            temp[i] = 'A';
            temp[i+1] = 'b';
            temp[i+2] = 'd';
            cont =strlen(temp);
        }else if(temp[i]=='$'){
            caracter[aux] = '$';
            aux++;
            temp  = adiantar(temp,i,3,1);
            temp[i] = 'A';
            temp[i+1] = 'b';
            temp[i+2] = 'd';
            cont =strlen(temp);
        }
    }

    *contCaracter += aux;                   //Para que o contador continue sem erros, ele recebe o valor da variável auxiliar

    return temp; //Ex: "Ol@" -> "OlAbd"
}

char * sufixoRabuu(char * vetPrincipal,int inicio,int fim){//Esta função executa o segundo padrão de criptografia Sufixo Rabbu
    char * temp;                                           //Recebendo a String Principal e inicio e fim da Substring desejada 
    int i,j=0;                                             
    int numPar = 0,numImpar = 0;                           
    int tamStr;
    temp = (char*)calloc(TAM,sizeof(char));
    for(i=inicio;i<fim;i++){    //Preenche a String temporária 
        temp[j]= vetPrincipal[i];
        j++;
    }

    tamStr = strlen(temp);
    for(i=0;i<tamStr;i++){       //Faz a verificação de carácter a carácter de seu valor na tabela Ascii
        if(temp[i]%2 == 0){      //Se o valor for par ele somado a um contador assim como se o valor for impar
            numPar++;
        }
        else{
            numImpar++;
        }
    }
    if(numPar>numImpar){        //Ao final ele confere se a quantidade de caracteres paras e maior que o de impar 
        strcat(temp,"Rabbu");   //neste caso ele irá adicionar "Rabbu" ao final da string temporária na qual será retornada 
    }
    return temp; //Ex: "Raror"-> "RarorRabbu"

}

char * inversaoQuasetotal(char * vetPrincipal,int inicio,int fim){//Esta função executa o terceiro padrão de criptografia Inversão quase total
	char * temp = (char *)calloc(TAM,sizeof(char));               //Recebendo a String Principal e inicio e fim da Substring desejada
    char * temp2 = (char*)calloc(TAM, sizeof(char));          
    int i,j=0,cont;
    int indice;


    for(i = inicio; i<fim;i++){    //Preenche a String temporária 
        temp[j] = vetPrincipal[i];
        j++;
    }

    cont = strlen(temp);
    j = cont - 1;               // índice do último carácter
    for(i = 0; i < cont; i++){  // Faz a inversão da Substring
        temp2[j] = temp[i];
        j--;
    }
    if(cont%2 == 0){                        //Faz a comparação se a Substring tiver um numero par de tamanho deve ser adicionado 
        indice = cont/2;                    //um '#' ao meio.    
        temp = adiantar(temp2,indice,1,0);
        temp[indice] = '#';
        return temp;                        //Ex: "Lado" -> "La#do"    
    }
    return temp2; //EX: "Nadar" -> "Nadar"

}

char * doisADois(char * vetPrinc,int inicio,int fim){//Esta função executa o quarto padrão de criptografia Inversão Dois a Dois
    char * temp = (char *)calloc(TAM,sizeof(char));  //Recebendo a String Principal e inicio e fim da Substring desejada
    char * temp2 = (char *)calloc(TAM,sizeof(char));
    int i,j=0,cont;
    for(i=inicio;i<fim;i++){    //Preenche a String temporária
        temp[j] = vetPrinc[i];
        j++;
    }
    cont = strlen(temp);
    temp2[cont]='\0';
    
    if(cont%2==0){                  //Verifica se o tamanho da Substring se e par ou impar 
        for(i=1;i <cont;i+=2){      //Caso  seja par
            temp2[i-1] = temp[i];   //Faz a inversão normalmente de dois em dois caracteres
            temp2[i] = temp[i-1];    
        }
    }else{
        for(i=1;i <cont;i+=2){      //Caso seja impar
            temp2[i-1] = temp[i];   //Faz a inversão normalmente de dois em dois caracteres
            temp2[i] = temp[i-1];   //Mas como o ultimo carácter troca de posição com o lixo que está após o '\0' 
        }                           //Faço com que assim que sair do for ele seja adicionado no local correto
        temp2[i-1] = temp[i-1];
    }

    return temp2; //Ex 1: "Abcd" -> "bAdc"   Ex 2: "Abc" -> "bAc"
}

char * juncao(char * vetPrincipal,int inicio,int fim,char * caracter,int * contCaracter){//Esta função executa o quinto padrão de criptografia Junção
    char * temp = (char *)calloc(TAM,sizeof(char));                                      //Recebendo a String Principal e inicio e fim da Substring desejada,
    int i,j=0;                                                                           //string de backup, e contador do índice
    int sInicio,sFim;                                                                    //Pois devem ser passados para a função Tudo e Abd

    for(i=inicio;i<fim;i++){    //Preenche a String temporária
        temp[j]=vetPrincipal[i];
        j++;
    }

    sInicio = 0;
    sFim = strlen(temp);    

    temp = abd(temp,sInicio,sFim,caracter,contCaracter);    //Utilizando uma String temporária passando para cada função, para ser modificada 
    sFim = strlen(temp);                                    //Decidi usar a mesma String pois ela só seria alterada após o termino de cada função 
    temp = sufixoRabuu(temp,sInicio,sFim);                  //como o tamanho pode mudar a cada função, para saber o fim, toda vez que
    sFim = strlen(temp);                                    //acaba uma função, novamente leio o seu tamanho  
    temp = inversaoQuasetotal(temp,sInicio,sFim);
    sFim = strlen(temp);
    temp = doisADois(temp,sInicio,sFim);

    return temp;    // Ex :  "@morr" -> "buabrRr#mobdA"
}

char * criptografarDados(char * vetorP,char * caracter){        //Está função faz com que seja feita a criptografia da frase inserida pelo usuário
    char * vetorPrincipal = (char *)calloc(TAM,sizeof(char));   //Chamando todas as funções em suas devida ordem, assim como também em
    char * vetor = (char *)calloc(TAM, sizeof(char));           //quais palavras aplicar
    char * vetorCript = (char *)calloc(TAM, sizeof(char));      //Recebendo a String lida na main e a String de backup dos caracteres especiais 

    int tamString = strlen(vetorP);
    int i;

    for(i=0;i<tamString;i++){            //Cria o vetor principal dentro da função 
        vetorPrincipal[i] = vetorP[i];
    }
    //Vetores tipo Int
    int * locEspacos;
    locEspacos = (int*)malloc(TAM * sizeof(int));   //Cria o vetor que irá guardar o índice do espaços encontrados na string principal

    //Variaveis tipo Int
    int qtdEspacos=0;       //Guarda a quantidade de espaços que também será a quantidade de SubStrings   
    int cont=1;             //Contador que irá decidir qual função deve ser aplicada
    int contStr = 0;        //Contador no qual irá dar o índice a ser utilizado para o inicio e fim da Substring 
    int contCaracter =0;    //Contador que irá ser utilizado para controlar a String de Backup de caracteres especiais
    qtdEspacos = encontrarIndiceEspacos(vetorPrincipal,locEspacos);

    printf("\n//-----Criptografia----//\n");
    for(i=1;i<=qtdEspacos;i++){       //Condição na qual irá repetir até que todas as Substrings sejam utilizadas 
        if(i==1){                                                                     //Condição que só irá ser utilizada na primeira SubString     
        	if(cont == 1){//ABD                                                       //devido seu inicio ser fixo em 0  
            vetor = abd(vetorPrincipal,0,locEspacos[contStr],caracter,&contCaracter); //Chama a função  
            strcat(vetorCript,vetor);                                                 //Adiciona a Substring já modificada a um String de Criptografia 
            // printf("//%s//\n", vetor);                                             //na qual já foi iniciada
            cont++;	                                                                  //Faz a soma para que seja feito o segundo padrão de criptografia
        	}
		}
        else{
			if(cont == 1){//ABD
            	vetor = abd(vetorPrincipal,locEspacos[contStr]+1,locEspacos[contStr+1],caracter,&contCaracter);
            	strcat(vetorCript,vetor);
                // printf("//%s//\n", vetor);
            	cont++;
                contStr++;
			}
            else if(cont == 2){//Rabbu 
                vetor = sufixoRabuu(vetorPrincipal,locEspacos[contStr]+1,locEspacos[contStr+1]);
                strcat(vetorCript,vetor);
                // printf("//%s//\n", vetor);
            	cont++;
                contStr++;
        	}
        	else if(cont == 3){//Inversão quase total
                vetor = inversaoQuasetotal(vetorPrincipal,locEspacos[contStr]+1,locEspacos[contStr+1]);
                strcat(vetorCript,vetor);
                // printf("//%s//\n", vetor);
            	cont++;
                contStr++;
        	}
        	else if(cont == 4){//Inversão dois a dois
                vetor = doisADois(vetorPrincipal,locEspacos[contStr]+1,locEspacos[contStr+1]);
                strcat(vetorCript,vetor);
                // printf("//%s//\n", vetor);
             	cont++;
                contStr++;
        	}
        	else{//Junção
                vetor = juncao(vetorPrincipal,locEspacos[contStr]+1,locEspacos[contStr+1],caracter,&contCaracter);
                strcat(vetorCript,vetor);
                // printf("//%s//\n", vetor);
            	cont=1;
                contStr++;
        	}
		}  
        if(i != qtdEspacos){            //Enquanto não for a ultima Substring, deve ser adicionado ao final de toda execução   
            strcat(vetorCript," ");     //um espaço ' ', para que seja feita a separação de Substrings
        }
        

    }
    // printf("/--/%s/--/\n",vetorCript);
    // printf("/--/%d/--/\n",contCaracter);
    return vetorCript; // Ex: "Ol@T#$xx# Amor abcd abcd @morr" -> "OlAbdTAbdAbdxxAbd Amor dc#ba badc buabrRr#mobdA" 

}

// Descriptografia

char * retroceder(char * vetor,int localInicial,int locRecebe,int locEnvia){//Sendo uma função auxiliar, ela retrocede caracteres em uma String
    int i;                                                                  //Recebendo uma string, o local a qual ira inicial a troca de carácter,
    char * temp;                                                            //local que ira receber, e local que será enviado
    temp = (char*)calloc(TAM, sizeof(char));
    temp[0]='\0';

    strcat(temp,vetor);    //Preenche a String temporária
    int num =strlen(vetor);

    for(i=localInicial;i<num;i++){             //Tendo o local no qual ira inicial ele percorre a string até o fim
        temp[i+locRecebe]= vetor[i+locEnvia];  //Executando a troca de caracteres
    }                                          //Retornando no fim a string com os carácteres retrocedido 
    return temp;      //Ex 1: "OlAbd" -> "OlA"  Ex 2: "La#do" -> "Lado" 
}

char * descriptAbd(char * vetCript,int inicio,int fim,char * caracter,int * contCaracter){//Esta função executa o primeiro padrão de descriptografia Tudo e Abd
    char * tempD;                                                                         //Recebendo o vetor principal, o local de inicio e fim da Substring a ser
    int i,j=0,cont;                                                                       //trabalhada, assim como uma string de backup dos caracteres, no qual  
    tempD = (char*)calloc(TAM, sizeof(char));                                             //irá ajudar a colocar os caracteres nas posições corretas, e o 
                                                                                          //contador, para determinar qual caracter da string de backup 
    for(i=inicio;i<fim;i++){   //Preenche a String temporária                             //deverá ser utilizado
        tempD[j] = vetCript[i];
        j++;
    }
    tempD[j+1] = '\0';
    cont =strlen(tempD);
	int aux = *contCaracter; //Para que o contador seja utilizado, usasse uma variável auxiliar  
	
    for(i=0;i<cont;i++){
        if(tempD[i]=='A'){
            if(tempD[i+1]=='b'){
                if(tempD[i+2]=='d'){                                       //Quando e encontrado a sequencia "Abd"  
                    tempD  = retroceder(tempD,i,1,3);                      //e chamada a função para retroceder os caracteres
                    cont =strlen(tempD);                                   //utilizando da string de backup, o caracter 'A' e substituído 
                    tempD[i] = caracter[aux];                              //pelo caracter especial correto
                    aux++;
                }
            }           
        }
    

    }
    *contCaracter += aux;    //O contador recebe a variável auxiliar
    return tempD;   //Ex: "OlAbd" -> "Ol@"
}

char * descriptRabuu(char * vetCript,int inicio, int fim){//Esta função executa o segundo padrão de descriptografia Sufixo Rabbu
    char * tempD;                                         //Recebendo a String Principal e inicio e fim da Substring desejada
    int i,j=0,cont;
    int tamString;
    tempD = (char*)calloc(TAM,sizeof(char));

    for(i=inicio;i<fim;i++){    //Preenche a String temporária
        tempD[j]=vetCript[i];
        j++;
    }
    i = strlen(tempD);//Pega o fim da String
    
    if((tempD[i-5]=='R')&&(tempD[i-4]=='a')&&(tempD[i-3]=='b')&&(tempD[i-2]=='b')&&(tempD[i-1]=='u')){//Faz uma comparação com os últimos 5 caracteres da String
        tempD[i-5]='\0';                                                                              //se forem "Rabbu", e colocado um '\0' na               
    }                                                                                                 //posição do caracter 'R'

    return tempD;   //Ex: "RarorRabbu" -> "Raror"
}

char * descriptInversao(char * vetCript,int inicio,int fim){//Esta função executa o terceiro padrão de descriptografia Inversão quase Total
    char * temp = (char *)calloc(TAM,sizeof(char));;        //Recebendo a String Principal e inicio e fim da Substring desejada
    char * temp2 = (char*)calloc(TAM, sizeof(char));
    int i,j=0,cont;
    int indice;

    for(i = inicio; i<fim;i++){//Preenche a String temporária
        temp[j] = vetCript[i];
        j++;
    }

    cont = strlen(temp);
    
    j = cont - 1; // índice do último caracter
    for(i = 0; i < cont; i++){     //Faz a inversão da SubString 
        temp2[j] = temp[i];     
        j--;
    }

    for(i = 0; i <= cont; i++){             //Percorre a Substring 
        if(temp2[i]=='#'){                  //Se for encontrado um '#'    
            temp = retroceder(temp2,i,0,1); //e retrocedido removendo o '#' 
            return temp;                    //Retorna a SubString que havia um '#' e foi removido  
        }   // Ex: "La#do" -> "Lado"
    }
    return temp2; //Retorna a SubString que não havia um '#' Ex: "Lado" -> "Lado"
}

char * descriptDoisADois(char * vetCript,int inicio, int fim){//Esta função executa o quarto padrão de descriptografia Inversão Dois a Dois
    char * temp;                            //Devido a sua simplicidade foi necessário apenas 
    temp = doisADois(vetCript,inicio,fim);  //chamar a função de criptografia novamente
    return temp; //Ex 1: "Abcd" -> "bAdc"   Ex 2: "Abc" -> "bAc" 
}

char * descriptJuncao(char * vetCript,int inicio,int fim,char * caracter,int * contCaracter){//Esta função executa o quarto padrão de descriptografia Junção
    char * tempD = (char *)calloc(TAM,sizeof(char));                                          //Recebendo a String Principal e inicio e fim da Substring desejada,
    int i,j=0;                                                                               //string de backup, e contador do índice
    int sInicio,sFim;                                                                        //Pois devem ser passados para a função Tudo e Abd

    for(i=inicio;i<fim;i++){    //Preenche a String temporária
        tempD[j]=vetCript[i];
        j++;
    }

    sFim = strlen(tempD);

    tempD = descriptDoisADois(tempD,0,sFim);                    //Utilizando uma String temporária passando para cada função, para ser modificada 
    sFim = strlen(tempD);                                       //Decidi usar a mesma String pois ela só seria alterada após o termino de cada função 
    tempD = descriptInversao(tempD,0,sFim);                     //como o tamanho pode mudar a cada função, para saber o fim, toda vez que
    sFim = strlen(tempD);                                       //acaba uma função, novamente leio o seu tamanho  
    tempD = descriptRabuu(tempD,0,sFim);                        //Fazendo a execução das funções, de forma inversa a de criptografia
    sFim = strlen(tempD);                                       //Sendo enviado a String de Backup e o contador, para que possam ser colocados os 
    tempD = descriptAbd(tempD,0,sFim,caracter,contCaracter);    //caracteres corretos

    return tempD;   // Ex : "buabrRr#mobdA" -> "@morr" ->
}

char * descriptografarDados(char * vetCript,char * caracter){ //Está função faz com que seja feita a descriptografia da String Criptografada
    char * vetorPrincipal = (char *)calloc(TAM,sizeof(char)); //Chamando todas as funções em suas devida ordem, assim como também em
    char * vetor = (char *)calloc(TAM, sizeof(char));         //quais palavras aplicar
    char * vetorDescript = (char *)calloc(TAM, sizeof(char)); //Recebendo a String Criptografada na main e a String de backup dos caracteres especiais 

    int tamString = strlen(vetCript);
    int i;

    for(i=0;i<tamString;i++){               //Cria o vetor principal dentro da função 
        vetorPrincipal[i] = vetCript[i];
    }
    //Vetores tipo Int
    int * locEspacos;
    locEspacos = (int*)malloc(TAM * sizeof(int));       //Cria o vetor que irá guardar o índice do espaços encontrados na string principal

    //Variaveis tipo Int
    int qtdEspacos=0;       //Guarda a quantidade de espaços que também será a quantidade de SubStrings   
    int cont=1;             //Contador que irá decidir qual função deve ser aplicada
    int contStr = 0;        //Contador no qual irá dar o índice a ser utilizado para o inicio e fim da Substring 
    int contCaracter =0;    //Contador que irá ser utilizado para controlar a String de Backup de caracteres especiais

    printf("\n//----Descriptografia----//\n");
    qtdEspacos = encontrarIndiceEspacos(vetorPrincipal,locEspacos);
     
    for(i=1;i<=qtdEspacos;i++){ //Condição na qual irá repetir até que todas as Substrings sejam utilizadas 
        if(i==1){                                                                             //Condição que só irá ser utilizada na primeira SubString
        	if(cont == 1){//ABD                                                               //devido seu inicio ser fixo em 0
            vetor = descriptAbd(vetorPrincipal,0,locEspacos[contStr],caracter,&contCaracter); //Chama a função
            strcat(vetorDescript,vetor);                                                      //Adiciona a Substring já modificada a um String de Criptografia 
            // printf("//%s//\n", vetor);                                                     //na qual já foi iniciada
            cont++;	                                                                          //Faz a soma para que seja feito o segundo padrão de descriptografia
        	}
		}else{
			if(cont == 1){//ABD
            	vetor = descriptAbd(vetorPrincipal,locEspacos[contStr]+1,locEspacos[contStr+1],caracter,&contCaracter);
            	strcat(vetorDescript,vetor);
                // printf("//%s//\n", vetor);
            	cont++;
                contStr++;	
			}
            else if(cont == 2){//Rabbu 
                vetor = descriptRabuu(vetorPrincipal,locEspacos[contStr]+1,locEspacos[contStr+1]);
                strcat(vetorDescript,vetor);
                // printf("//%s//\n", vetor);
            	cont++;
                contStr++;
        	}
        	else if(cont == 3){//Inversão quase total
                vetor = descriptInversao(vetorPrincipal,locEspacos[contStr]+1,locEspacos[contStr+1]);
                strcat(vetorDescript,vetor);
                // printf("//%s//\n",vetor);
            	cont++;
                contStr++;
        	}
        	else if(cont == 4){//Inversão dois a dois
                vetor = descriptDoisADois(vetorPrincipal,locEspacos[contStr]+1,locEspacos[contStr+1]);
                strcat(vetorDescript,vetor);
                // printf("//%s//\n", vetor);
             	cont++;
                contStr++;
        	}
        	else{//Junção
                vetor = descriptJuncao(vetorPrincipal,locEspacos[contStr]+1,locEspacos[contStr+1],caracter,&contCaracter);
                strcat(vetorDescript,vetor);
                // printf("//%s//\n", vetor);
            	cont=1;
                contStr++;
        	}
		}  
        if(i != qtdEspacos){            //Enquanto não for a ultima Substring, deve ser adicionado ao final de toda execução   
            strcat(vetorDescript," ");  //um espaço ' ', para que seja feita a separação de Substrings
        }
    }
    // printf("/--/%s/--/\n",vetorDescript);
    // printf("/--/%d/--/\n",contCaracter);
    return vetorDescript; // Ex: "OlAbdTAbdAbdxxAbd Amor dc#ba badc buabrRr#mobdA" -> "Ol@T#$xx# Amor abcd abcd @morr"

}


int main(){//Código principal
    //Vetores tipo Char
    char * vetPrincipal;                                        //Cria um ponteiro para a String Principal                                               
    char * caracter = (char *)calloc(TAM,sizeof(char));         //Cria e aloca na memoria a String de Backup
    char * vetorCript = (char *)calloc(TAM,sizeof(char));       //Cria e aloca na memoria a String de Criptografia
    char  * vetorDescript = (char *)calloc(TAM,sizeof(char));   //Cria e aloca na memoria a String de Descriptografia
    
    vetPrincipal = lerDados();                                  //Faz a leitura da String principal

    vetorCript = criptografarDados(vetPrincipal,caracter);      //Faz a Criptografia da String Principal
    printf("/--/%s/--/\n",vetorCript);

    vetorDescript = descriptografarDados(vetorCript,caracter);  //Faz a Descriptografia da String Criptografada
    printf("/--/%s/--/\n",vetorDescript);

    
    system("pause");

}

//Aqui a Magica termina ☺ ♥ 