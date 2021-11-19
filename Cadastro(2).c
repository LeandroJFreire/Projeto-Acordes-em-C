#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (!(arq = fopen("arq.bin", "rb")))
    {
        printf("Erro ao abrir o arquivo!\n\n");
        return;
    }
    printf("\n\nLISTA DE CLIENTE ATE O MOMENTO!\n\n");
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
    int matricula, op, op2, alterou, cpf;
    char nome[15];

    FILE *arq;
    arq = fopen ("arq.bin", "rb");

    if (arq == NULL)
    {
        printf ("Erro ao abrir o arquivo!\n");
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
                            gets(nome);
                            strcpy (usuario.nome, nome);
                            printf("\n");
                            alterou = 1;
                            if (alterou=1){
                    			fseek(arq, sizeof(Usuario), SEEK_SET);
                    			if (fwrite(&usuario, sizeof(Usuario), 1, arq) == 1)
                    			{
                    		    printf("Alteracao salva com sucesso!\n\n");
                   				} else{
                        		printf("Erro na gravacao do arquivo!\n\n");
                    			}
                    			fflush(arq);
                    			fclose(arq);
                			}else{
                 			    printf("Nenhuma alteracao realizada!\n");
                			}
                		
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

                if (alterou=1)
                {
                	printf("dddddd\n");
                    fseek(arq, sizeof(Usuario), SEEK_SET);
                    if (fwrite(&usuario, sizeof(Usuario), 1, arq) == NULL)
                    {
                        printf("Erro na gravacao do arquivo!\n\n");
                    }
                    else
                    {
                        printf("Alteracao salva com sucesso!\n\n");
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
void menuCliente()
{
    int opCliente;

    system("cls");
    printf ("\n");
    printf("MENU CLIENTE\n");
    printf ("1. xxxxx\n");
    printf ("2. xxxxx\n");
    printf ("0. Sair\n");
    printf ("Qual sua opcao? ");
    scanf ("%d", &opCliente);
    switch (opCliente)
    {
    case 1:

        break;
    case 2:

        break;
    case 0:
        exit(1);
        break;
    default:
        break;
    }
}

int main()
{
    int opcao;

    system("cls");
    printf ("BEM-VINDO!\n\n");
    printf ("1. Funcionario\n");
    printf ("2. Cliente\n");
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

