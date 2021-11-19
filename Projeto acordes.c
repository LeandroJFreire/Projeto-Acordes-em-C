#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char acorde[6][6];

void alterarUsuario();
void removerUsuario();
void listarUsuario();
void inserirUsuario();
void menuCliente();
void menuFuncionario();
void voltarMenuFuncionario();
void voltarMenuUsuario();

typedef struct Usuario_
{
    int matricula;
    int idade;
    char senha[6];
    char sexo;
    char ac_violao[6][6];
    char nome[31];
    int telefone;
    int cpf;
} Usuario;

Usuario usuario;

void inserirUsuario ()
{
    char nome [20], sobrenome[30];
    FILE *arq;
    arq = fopen ("arq.bin", "wb");
    if (arq == NULL)
    {
        printf ("Erro ao abrir o arquivo!\n");
        return;
    }

    do
    {
        printf("Matricula do usuario: ");
        scanf("%d", &usuario.matricula);
        fflush(stdin);
    }
    while (usuario.matricula <= 0 || usuario.matricula > 999999);

    do
    {
        printf("Primeiro nome do usuario: ");
        gets(nome);
        printf("Sobrenome do usuario: ");
        gets(sobrenome);
    }
    while (nome[0] == '\0' || sobrenome[0] == '\0');

    strcpy(usuario.nome, nome);
    strcat(usuario.nome, " ");
    strcat(usuario.nome, sobrenome);

    do
    {
        printf("Telefone do usuario (8 digitos): ");
        scanf("%d", &usuario.telefone);
        fflush(stdin);
    }
    while (usuario.telefone <= 00000000 && usuario.telefone > 100000000);

    do
    {
        printf("CPF do usuario (11 digitos): ");
        fflush(stdin);
        scanf("%d", &usuario.cpf);
    }
    while (usuario.cpf <= 00000000000 && usuario.cpf > 100000000000);

    do
    {
        printf("Senha do usuario (6 digitos): ");
        fflush(stdin);
        usuario.senha[0] = getch();
        printf("\4");
        usuario.senha[1] = getch();
        printf("\4");
        usuario.senha[2] = getch();
        printf("\4");
        usuario.senha[3] = getch();
        printf("\4");
        usuario.senha[4] = getch();
        printf("\4");
        usuario.senha[5] = getch();
        printf("\4");
    }
    while (usuario.senha[0] == '\0' && usuario.senha[1] == '\0' && usuario.senha[2] == '\0' && usuario.senha[3] == '\0' && usuario.senha[4] == '\0' && usuario.senha[5] == '\0');

    printf("\n");
    if ((fwrite(&usuario, sizeof (Usuario), 1, arq)) != 0)
    {
        printf("Usuario cadastrado com sucesso!\n\n");
        getchar();
        getchar();

    }
    else
    {
        printf("Erro ao salvar usuario no arquivo!\n\n");
        getchar();
        getchar();
    }
    printf("\n");
    fclose(arq);
    voltarMenuFuncionario();
}

void listarUsuario()
{

    FILE *arq;

    arq = fopen("arq.bin", "rb");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo!\n\n");
        return;
    }
    printf("\n\nLISTA DE CLIENTE(S) ATE O MOMENTO!\n\n");
    fread(&usuario, sizeof (Usuario), 1, arq);
    while (!feof(arq))
    {
        printf("\n");
        printf("Matricula: %d \n", usuario.matricula);
        printf("Nome: %s\n", usuario.nome);
        printf("CPF: %d\n", usuario.cpf);
        printf("--------------------------------------------------\n");

        fread(&usuario, sizeof (Usuario), 1, arq);
    }
    fclose(arq);
    getchar();
    getchar();
    voltarMenuFuncionario();
}

void removerUsuario()
{
    int matricula, op, excluiu = 0, cpf;
    char nome [31];

    FILE *arqOrigem, *arqDestino;

    arqOrigem = fopen ("arqOrigem.bin", "rb");
    arqDestino = fopen ("arqDestino.bin", "wb");

    if (arqOrigem == NULL)
    {
        printf ("Erro ao abrir o arquivo!\n");
        return;
    }

    if (arqDestino == NULL)
    {
        printf ("Erro ao abrir o arquivo temporario!\n");
        return;
    }

    do
    {
        printf("\n");
        printf("1. Buscar pela matricula\n2. Buscar pelo nome\n3. Buscar pelo CPF\n");
        printf("Qual sua opcao? ");
        scanf("%d",&op);
    }
    while(op < 1 && op > 3);

    if(op == 1)
    {
        printf("\n");
        printf("Digite a matricula: ");
        scanf("%d", &matricula);
        fread(&usuario, sizeof(Usuario), 1, arqOrigem);
        while(!feof(arqOrigem))
        {
            if (matricula == usuario.matricula)
            {
                printf("\n");
                printf("Matricula: %d \n", usuario.matricula);
                printf("Nome: %s\n", usuario.nome);
                printf("CPF: %d\n", usuario.cpf);
                printf("\n\n");
                printf("Deseja excluir este usuario? Informe 1 para confirmar ou 0 para sair.\n");
                scanf("%d", &excluiu);
            }
            else
            {
                fwrite(&usuario, sizeof(Usuario), 1, arqDestino);
            }
            fread(&usuario, sizeof(Usuario), 1, arqOrigem);
        }
        fclose(arqOrigem);
        fclose(arqDestino);
        if (excluiu==1)
        {
            rename("arqDestino.bin", "arqOrigem.bin");
            remove("arqOrigem.bin");
            printf("Exclusao realizada com sucesso!\n\n");
        }
        else
        {
            remove("arqDestino.bin");
            printf("Matricula nao cadastrada!\n\n");
        }
    }
    else if(op==2)
    {
        printf("\n");
        printf("Digite o nome: ");
        gets(nome);
        fread(&usuario, sizeof(Usuario), 1, arqOrigem);
        while(!feof(arqOrigem))
        {
            if (matricula == usuario.matricula)
            {
                printf("\n");
                printf("Matricula: %d \n", usuario.matricula);
                printf("Nome: %s\n", usuario.nome);
                printf("CPF: %d\n", usuario.cpf);
                printf("\n\n");
                printf("Deseja excluir este usuario? Informe 1 para confirmar ou 0 para sair.\n");
                scanf("%d", &excluiu);
            }
            else
            {
                fwrite(&usuario, sizeof(Usuario), 1, arqDestino);
            }
            fread(&usuario, sizeof(Usuario), 1, arqOrigem);
        }
        fclose(arqOrigem);
        fclose(arqDestino);
        if (excluiu==1)
        {
            rename("arqDestino.bin", "arqOrigem.bin");
            remove("arqOrigem.bin");
            printf("Exclusao realizada com sucesso!\n\n");
        }
        else
        {
            remove("arqDestino.bin");
            printf("Matricula nao cadastrada!\n\n");
        }
    }
    else if(op == 3)
    {
        printf("\n");
        printf("Digite o cpf: ");
        scanf("%d", &cpf);
        fread(&usuario, sizeof(Usuario), 1, arqOrigem);
        while(!feof(arqOrigem))
        {
            if (matricula == usuario.matricula)
            {
                printf("\n");
                printf("Matricula: %d \n", usuario.matricula);
                printf("Nome: %s\n", usuario.nome);
                printf("CPF: %d\n", usuario.cpf);
                printf("\n\n");
                printf("Deseja excluir este usuario? Informe 1 para confirmar ou 0 para sair.\n");
                scanf("%d", &excluiu);
            }
            else
            {
                fwrite(&usuario, sizeof(Usuario), 1, arqDestino);
            }
            fread(&usuario, sizeof(Usuario), 1, arqOrigem);
        }
        fclose(arqOrigem);
        fclose(arqDestino);
        if (excluiu==1)
        {
            rename("arqDestino.bin", "arqOrigem.bin");
            remove("arqOrigem.bin");
            printf("Exclusao realizada com sucesso!\n\n");
        }
        else
        {
            remove("arqDestino.bin");
            printf("Matricula nao cadastrada!\n\n");
        }
    }

}

void alterarUsuario()
{
    int matricula, op, op2, alterou = 0, cpf;
    char nome[50];

    FILE *arq;
    arq = fopen ("arq.bin", "rb");

    if (arq == NULL)
    {
        printf ("Erro ao abrir o arquivo!\n");
        return;
    }

    do
    {
        printf("=\n");
        printf("1. Buscar pela matricula\n2. Buscar pelo nome\n3. Buscar pelo CPF\n");
        printf("Qual sua opcao? ");
        scanf("%d",&op);
    }
    while(op < 1 && op > 3);

    if(op == 1)
    {
        printf("\n");
        printf("Digite a matricula: ");
        scanf("%d", &matricula);
        fread(&usuario, sizeof(Usuario), 1, arq);
        while(!feof(arq))
        {
            if (matricula == usuario.matricula)
            {
                printf("\n");
                printf("Matricula: %d \n", usuario.matricula);
                printf("Nome: %s\n", usuario.nome);
                printf("CPF: %d\n", usuario.cpf);
                printf("\n\n");

                do
                {
                    do
                    {
                        printf("1. Nome\n2. Idade\n3. Sexo\n4. Telefone\n5. CPF\n6. Senha\n0. Sair\n");
                        printf("Informe a opcao que deseja alterar: ");
                        fflush(stdin);
                        scanf("%d",&op);
                        printf("\n");

                        switch(op)
                        {

                        case 1:
                            printf("Digite o nome: ");
                            fflush(stdin);
                            gets(usuario.nome);
                            printf("\n");
                            alterou = 1;
                            break;

                        case 2:
                            printf("Digite a idade: ");
                            scanf("%d", &usuario.idade);
                            printf("\n");
                            alterou = 1;
                            break;

                        case 3:
                            printf("Digite o sexo: ");
                            fflush(stdin);
                            scanf("%c", &usuario.sexo);
                            printf("\n");
                            alterou = 1;
                            break;

                        case 4:
                            printf("Digite o telefone: ");
                            fflush(stdin);
                            scanf("%d", &usuario.telefone);
                            printf("\n");
                            alterou = 1;
                            break;

                        case 5:
                            printf ("Digite o CPF: ");
                            fflush(stdin);
                            scanf("%d", &usuario.cpf);
                            printf("\n");
                            alterou=1;
                            break;

                        case 6:
                            printf ("Digite a senha: ");
                            scanf("%s",usuario.senha);
                            printf("\n");
                            alterou=1;
                            break;

                        case 0:
                            exit(1);
                            break;

                        default:
                            printf("Opcao invalida!\n");
                            break;

                        }
                    }
                    while(op < 0 || op > 5);
                    printf("Deseja alterar outro dado? Informe 1 para continuar e 0 para sair.\n");
                    printf("Opcao: ");
                    scanf("%d",&op2);
                    printf("\n");
                }
                while(op2 == 1);

                if (alterou==1)
                {
                    fseek(arq, sizeof(Usuario), SEEK_CUR);
                    if (fwrite(&usuario, sizeof(Usuario), 1, arq) == 1)
                    {
                        printf("Alteracao salva com sucesso!\n\n");
                    }
                    else
                    {
                        printf("Erro na gravacao do arquivo!\n\n");
                    }
                    fflush(arq);
                }
                else
                {
                    printf("Nenhuma alteracao realizada!\n");
                }
                break;
            }
            fread(&usuario, sizeof(Usuario), 1, arq);
        }
        if (matricula != usuario.matricula)
        {
            printf("Conta nao cadastrada!\n\n");
        }
        fclose(arq);
        voltarMenuFuncionario();
    }
    else if(op == 2)
    {
        printf("\n");
        printf("Digite o nome: ");
        gets(nome);
        fread(&usuario, sizeof(Usuario), 1, arq);
        while(!feof(arq))
        {
            if (strstr(nome,usuario.nome) != NULL)
            {
                printf("\n");
                printf("Matricula: %d \n", usuario.matricula);
                printf("Nome: %s\n", usuario.nome);
                printf("CPF: %d\n", usuario.cpf);
                printf("\n\n");

                do
                {
                    do
                    {
                        printf("1. Nome\n2. Idade\n3. Sexo\n4. Telefone\n5. CPF\n6. Senha\n0. Sair\n");
                        printf("Informe a opcao que deseja alterar: ");
                        fflush(stdin);
                        scanf("%d",&op);
                        printf("\n");

                        switch(op)
                        {

                        case 1:
                            printf("Digite o nome: ");
                            fflush(stdin);
                            gets(usuario.nome);
                            printf("\n");
                            alterou = 1;
                            break;

                        case 2:
                            printf("Digite a idade: ");
                            scanf("%d", &usuario.idade);
                            printf("\n");
                            alterou = 1;
                            break;

                        case 3:
                            printf("Digite o sexo: ");
                            fflush(stdin);
                            scanf("%c", &usuario.sexo);
                            printf("\n");
                            alterou = 1;
                            break;

                        case 4:
                            printf("Digite o telefone: ");
                            fflush(stdin);
                            scanf("%d", &usuario.telefone);
                            printf("\n");
                            alterou = 1;
                            break;

                        case 5:
                            printf ("Digite o CPF: ");
                            fflush(stdin);
                            scanf("%d", &usuario.cpf);
                            printf("\n");
                            alterou=1;
                            break;

                        case 6:
                            printf ("Digite a senha: ");
                            scanf("%s",usuario.senha);
                            printf("\n");
                            alterou=1;
                            break;

                        case 0:
                            exit(1);
                            break;

                        default:
                            printf("Opcao invalida!\n");
                            break;

                        }
                    }
                    while(op < 0 || op > 5);
                    printf("Deseja alterar outro dado? Informe 1 para continuar e 0 para sair.\n");
                    printf("Opcao: ");
                    scanf("%d",&op2);
                    printf("\n");
                }
                while(op2 == 1);

                if (alterou==1)
                {
                    fseek(arq, sizeof(Usuario), SEEK_CUR);
                    if (fwrite(&usuario, sizeof(Usuario), 1, arq) == 1)
                    {
                        printf("Alteracao salva com sucesso!\n\n");
                    }
                    else
                    {
                        printf("Erro na gravacao do arquivo!\n\n");
                    }
                    fflush(arq);
                }
                else
                {
                    printf("Nenhuma alteracao realizada!\n");
                }
                break;
            }
            fread(&usuario, sizeof(Usuario), 1, arq);
        }
        if (matricula != usuario.matricula)
        {
            printf("Conta nao cadastrada!\n\n");
        }
        fclose(arq);
        voltarMenuFuncionario();
    }
    else if(op == 3)
    {
        printf("\n");
        printf("Digite o cpf: ");
        scanf("%d", &cpf);
        fread(&usuario, sizeof(Usuario), 1, arq);
        while(!feof(arq))
        {
            if (cpf == usuario.cpf)
            {
                printf("\n");
                printf("Matricula: %d \n", usuario.matricula);
                printf("Nome: %s\n", usuario.nome);
                printf("CPF: %d\n", usuario.cpf);
                printf("\n\n");

                do
                {
                    do
                    {
                        printf("1. Nome\n2. Idade\n3. Sexo\n4. Telefone\n5. CPF\n6. Senha\n0. Sair\n");
                        printf("Informe a opcao que deseja alterar: ");
                        fflush(stdin);
                        scanf("%d",&op);
                        printf("\n");

                        switch(op)
                        {

                        case 1:
                            printf("Digite o nome: ");
                            fflush(stdin);
                            gets(usuario.nome);
                            printf("\n");
                            alterou = 1;
                            break;

                        case 2:
                            printf("Digite a idade: ");
                            scanf("%d", &usuario.idade);
                            printf("\n");
                            alterou = 1;
                            break;

                        case 3:
                            printf("Digite o sexo: ");
                            fflush(stdin);
                            scanf("%c", &usuario.sexo);
                            printf("\n");
                            alterou = 1;
                            break;

                        case 4:
                            printf("Digite o telefone: ");
                            fflush(stdin);
                            scanf("%d", &usuario.telefone);
                            printf("\n");
                            alterou = 1;
                            break;

                        case 5:
                            printf ("Digite o CPF: ");
                            fflush(stdin);
                            scanf("%d", &usuario.cpf);
                            printf("\n");
                            alterou=1;
                            break;

                        case 6:
                            printf ("Digite a senha: ");
                            scanf("%s",usuario.senha);
                            printf("\n");
                            alterou=1;
                            break;

                        case 0:
                            exit(1);
                            break;

                        default:
                            printf("Opcao invalida!\n");
                            break;

                        }
                    }
                    while(op < 0 || op > 5);
                    printf("Deseja alterar outro dado? Informe 1 para continuar e 0 para sair.\n");
                    printf("Opcao: ");
                    scanf("%d",&op2);
                    printf("\n");
                }
                while(op2 == 1);

                if (alterou==1)
                {
                    fseek(arq, sizeof(Usuario), SEEK_CUR);
                    if (fwrite(&usuario, sizeof(Usuario), 1, arq) == 1)
                    {
                        printf("Alteracao salva com sucesso!\n\n");
                    }
                    else
                    {
                        printf("Erro na gravacao do arquivo!\n\n");
                    }
                    fflush(arq);
                }
                else
                {
                    printf("Nenhuma alteracao realizada!\n");
                }
                break;
            }
            fread(&usuario, sizeof(Usuario), 1, arq);
        }
        if (matricula != usuario.matricula)
        {
            printf("Conta nao cadastrada!\n\n");
        }
        fclose(arq);
        voltarMenuFuncionario();
    }
}

void menuFuncionario()
{
    int opFunc;

    system("cls");
    printf ("\n");
    printf("MENU FUNCIONARIO\n");
    printf ("1. Adicionar cliente\n");
    printf ("2. Alterar cliente\n");
    printf ("3. Remover cliente\n");
    printf ("4. Listar cliente\n");
    printf ("0. Sair\n");
    printf ("Qual sua opcao? ");
    scanf ("%d", &opFunc);

    switch (opFunc)
    {
    case 1:
        inserirUsuario();
        break;
    case 2:
        alterarUsuario();
        break;
    case 3:
        removerUsuario();
        break;
    case 4:
        listarUsuario();
        break;
    case 0:
        exit(1);
        break;
    default:
        break;
    }

}

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

void menuCliente()
{
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
        }else
        exit(1);

    system ("pause");

    }while(entrada!=0);

    voltarMenuUsuario();
}

int main()
{
    int opcao;
    
    system ("pause");
    printf ("BEM-VINDO!\n\n");
    printf ("1. Funcionario\n");
    printf ("2. Usuario\n");
    printf ("0. Sair\n");
    printf ("Qual sua opcao? ");
    scanf ("%d", &opcao);

    switch (opcao)
    {
    case 1:
        menuFuncionario();
        break;
    case 2:
        menuCliente();
        break;
    case 0:
        exit(1);
        break;
    default:
        break;
    }

    getchar ();
    getchar ();
}
void voltarMenuFuncionario()
{
    int opcao;

    system("cls");
    printf("\n");
    printf("0. Sair\n");
    printf("1. Menu principal\n");
    printf("2. Menu funcionario\n");
    printf("Qual sua opcao? ");
    scanf("%d", &opcao);
    printf("\n");

    switch (opcao)
    {
    case 0:
        exit(1);
        break;
    case 1:
        main();
        break;
    case 2:
        menuFuncionario();
        break;
    default:
        break;
    }
}

void voltarMenuUsuario()
{
    int opcao;

    system("cls");
    printf("\n");
    printf("0. Sair\n");
    printf("1. Menu principal\n");
    printf("2. Menu usuario\n");
    printf("Qual sua opcao? ");
    scanf("%d", &opcao);
    printf("\n");

    switch (opcao)
    {
    case 0:
        exit(1);
        break;
    case 1:
        main();
        break;
    case 2:
        menuCliente();
        break;
    default:
        break;
    }
}

