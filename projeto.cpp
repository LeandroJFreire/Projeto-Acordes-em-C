#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
char acorde[6][6];

int eMenor(char acord){
    if(acord == 'm'){
		return 1;
    }
    return 0;
}

int eSetima(char acord, char acordes){
    if(acord == '7'||acordes == '7'){
            return 1;
	}
    return 0;
}

int eSustenido(char acord[]){
    int i;
    for(i=0; i<6; i++){
        if(acord[i] == '#'){
            return 1;
        }
    }
    return 0;
}

int eBemol(char acord[]){
    int i;
    for(i=0; i<6; i++){
        if(acord[i] == 'b'){
            return 1;
        }
    }
    return 0;
}

void semAcorde(){
    int a,b;
    for(a=0; a<6; a++){
        for(b=0; b<6; b++){
            acorde[a][b]='=';
        }
    }
}

void doMenor (){

   acorde[1][2]='1';
   acorde[2][2]='1';
   acorde[3][2]='1';
   acorde[4][2]='1';
   acorde[5][2]='1';
   acorde[6][2]='1';
   acorde[4][3]='2';
   acorde[2][4]='3';
   acorde[3][6]='4';

}
void reMenor (){

   acorde[5][0] = '1';
   acorde[3][1] = '2';
   acorde[4][2] = '3';

}
void miMenor (){

   acorde[1][1]='1';
   acorde[2][1]='2';

}
void faMenor (){

    acorde[0][0]='1';
    acorde[1][0]='1';
    acorde[1][2]='3';
    acorde[2][0]='1';
    acorde[2][2]='4';
    acorde[3][0]='1';
    acorde[4][0]='1';
    acorde[5][0]='1';

}
void solMenor (){

   acorde[0][2]='1';
    acorde[1][2]='1';
    acorde[1][4]='3';
    acorde[2][2]='1';
    acorde[2][4]='4';
    acorde[3][2]='1';
    acorde[4][2]='1';
    acorde[5][2]='1';

}
void laMenor (){

   acorde[4][0]='1';
   acorde[2][1]='2';
   acorde[3][1]='3';

}
void siMenor (){

   acorde[2][2]='1';
   acorde[2][3]='2';
   acorde[4][4]='3';
   acorde[3][4]='4';
}

void doSetima (){

    acorde[1][3]='3';
    acorde[3][1]='2';
    acorde[4][0]='1';
	acorde[2][3]='4';
}
void reSetima (){

   acorde[2][1]='1';
   acorde[3][2]='2';
   acorde[1][2]='3';

}
void miSetima (){

   acorde[3][1]='2';
   acorde[5][2]='3';
   acorde[3][0]='1';
   acorde[4][2]='4';


}
void faSetima (){

   acorde[1][1]='1';
   acorde[2][1]='1';
   acorde[3][1]='1';
   acorde[4][1]='1';
   acorde[5][1]='1';
   acorde[3][2]='2';
   acorde[5][3]='3';

}
void solSetima (){

   acorde[1][1]='1';
   acorde[5][2]='2';
   acorde[6][3]='3';

}
void laSetima (){

   acorde[4][2]='1';
   acorde[2][2]='2';

}
void siSetima (){

   acorde[4][1]='1';
   acorde[5][2]='2';
   acorde[3][2]='3';
   acorde[1][2]='4';
}

void doMaior (){
    acorde[1][3]='3';
    acorde[3][1]='2';
    acorde[4][0]='1';
}

void reMaior (){
    acorde[3][1]='1';
    acorde[4][2]='3';
    acorde[5][1]='2';
    /*              {'-','-','-','-','-','-'},
                    {'-','-','-','-','-','-'},
                    {'-','-','-','-','-','-'},
                    {'-','1','-','-','-','-'},
                    {'-','-','3','-','-','-'},
                    {'-','2','-','-','-','-'}
    */
}

void miMaior (){
    acorde[1][1]='2';
    acorde[2][1]='3';
    acorde[3][0]='1';
    /*              {'-','-','-','-','-','-'},
                    {'-','2','-','-','-','-'},
                    {'-','3','-','-','-','-'},
                    {'1','-','-','-','-','-'},
                    {'-','-','-','-','-','-'},
                    {'-','-','-','-','-','-'}
    */
}

void faMaior (){
    acorde[0][0]='1';
    acorde[1][0]='1';
    acorde[1][2]='3';
    acorde[2][0]='1';
    acorde[2][2]='4';
    acorde[3][0]='1';
    acorde[3][1]='2';
    acorde[4][0]='1';
    acorde[5][0]='1';
    /*              {'1','-','-','-','-','-'},
                    {'1','-','3','-','-','-'},
                    {'1','-','4','-','-','-'},
                    {'1','2','-','-','-','-'},
                    {'1','-','-','-','-','-'},
                    {'1','-','-','-','-','-'}
    */
}

void solMaior (){
    acorde[0][2]='2';
    acorde[1][1]='1';
    acorde[4][2]='3';
    acorde[5][2]='4';
    /*              {'-','-','2','-','-','-'},
                    {'-','1','-','-','-','-'},
                    {'-','-','-','-','-','-'},
                    {'-','-','-','-','-','-'},
                    {'-','-','3','-','-','-'},
                    {'-','-','4','-','-','-'}
    */
}

void laMaior (){
    acorde[0][0]='X';
    acorde[2][1]='1';
    acorde[3][1]='2';
    acorde[4][1]='3';
    /*              {'X','-','-','-','-','-'},
                    {'-','-','-','-','-','-'},
                    {'-','1','-','-','-','-'},
                    {'-','2','-','-','-','-'},
                    {'-','3','-','-','-','-'},
                    {'-','-','-','-','-','-'}
    */
}

void siMaior (){
    acorde[0][0]='X';
    acorde[1][1]='1';
    acorde[2][1]='1';
    acorde[2][3]='3';
    acorde[3][1]='1';
    acorde[3][3]='4';
    acorde[4][1]='1';
    acorde[4][3]='2';
    acorde[5][1]='1';

    /*              {'X','-','-','-','-','-'},
                    {'-','1','-','-','-','-'},
                    {'-','1','-','3','-','-'},
                    {'-','1','-','4','-','-'},
                    {'-','1','-','2','-','-'},
                    {'-','1','-','-','-','-'}
    */
}

void func (char tom, int menor, int setima){

	if(menor == 1){
		if(setima == 1){

			switch (tom){
	            case 'C': doMenor();
	                    break;
	            case 'D': reMenor();
	                    break;
	            case 'E': miMenor();
	                    break;
	            case 'F': faMenor();
	                    break;
	            case 'G': solMenor();
	                    break;
	            case 'A': laMenor();
	                    break;
	            case 'B': siMenor();
	                    break;
	            }
		}else{
			switch (tom){
		            case 'C': doMenor();
		                    break;
		            case 'D': reMenor();
		                    break;
		            case 'E': miMenor();
		                    break;
		            case 'F': faMenor();
		                    break;
		            case 'G': solMenor();
		                    break;
		            case 'A': laMenor();
		                    break;
		            case 'B': siMenor();
		                    break;
		            }
		}
	}else{
		if(setima == 1){
			switch (tom){
	            case 'C': doSetima();
	                    break;
	            case 'D': reSetima();
	                    break;
	            case 'E': miSetima();
	                    break;
	            case 'F': faSetima();
	                    break;
	            case 'G': solSetima();
	                    break;
	            case 'A': laSetima();
	                    break;
	            case 'B': siSetima();
	                    break;
	            }

		}else{

			switch (tom){
		            case 'C': doMaior();
		                    break;
		            case 'D': reMaior();
		                    break;
		            case 'E': miMaior();
		                    break;
		            case 'F': faMaior();
		                    break;
		            case 'G': solMaior();
		                    break;
		            case 'A': laMaior();
		                    break;
		            case 'B': siMaior();
		                    break;
		            }
		}
	}
}
int main(){

    char entrada[6], i, j;

    do{

        system("cls");

        semAcorde();

        printf("\n\n\n\t\t\tDICIONARIO DE ACORDES 1.0\n\n\n");
        printf("\nDigite a opcao do acorde desejado:\n\nSao suportados apenas acordes maiores naturais, menores e com setima.\nExemplo: C7, Bm, Am7\n");
        gets(entrada);

		func(entrada[0], eMenor(entrada[1]), eSetima(entrada[1], entrada[2]));

        system("cls");


        printf("\n\n\n\t\t\tDICIONARIO DE ACORDES 1.0\n\n\n");
        if(entrada!=0){
            //LAÇO DE IMPRESSÃO DO ACORDE
            for(i=0; i<6; i++){
                printf("\t\t\t\tH");
                for(j=0; j<6; j++){
                    printf("%c", acorde[i][j]);
                    printf("|");
                }
                printf("\n");
            }
        }


        system("pause");
    }while(entrada!=0);

    system("cls");
    printf("\n\n\n\t\t\tDICIONARIO DE ACORDES 1.0\n\n\n");
    printf("\n\n\n\n\n\n\n\n\t\tObrigado por usar DICIONARIO DE ACORDES 1.0 (Beta)\a\n\n\n\n\n\n\n");
    return 0;
}


