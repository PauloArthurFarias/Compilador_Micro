#include <stdio.h>
#include <string.h>

#define INPUT_FILE "input.asm"
#define OUTPUT_FILE "output.txt"

int verifica_binario(const char* frase) //Verifica se é binário, caso não, trata-se de uma instrução
{
    if(strlen(frase) == 8)
    {
        for(int i = 0; frase[i] != '\0'; i++)
        {
            if(frase[i] != '0' && frase[i] != '1')
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int verifica_reservada(const char* frase, const char* reservadas[], int num_reservadas) //Verifica se é uma das palavras reservadas
{
    for(int i = 0; i < num_reservadas; i++)
    {
        if(strcmp(frase, reservadas[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}


int main()
{
    FILE* input_file = fopen(INPUT_FILE, "r");
    FILE* output_file = fopen(OUTPUT_FILE, "wb");

    if(input_file == NULL || output_file == NULL) //testando se a abertura foi bem-sucedida
    {
        printf("Erro na abertura do arquivo");
        return 1;
    }
    else
    {
        printf("Arquivo aberto com sucesso");
    }

    const char* reservadas[] = {
    "ADD", "SUB", "MUL", "DIV"
    };

    int num_reservadas = sizeof(reservadas) / sizeof(reservadas[0]);
    
    char line[50];

    while(fgets(line, sizeof(line), input_file))//fgets tenta ler cada linha do arquivo e armazenar no vetor temporário line, se for bem-sucedido retorna um ponteiro para line, se não retorna NULL, funcionando assim como condição para o laço
    {
        line[strcspn(line, "\n")] = '\0'; //strcspn procura a substring passada dentro da string passada e retorna seu índice. Substituo "\n" por '\0' para evitar problemas de comparação posteriores com "ADD" por exemplo
        if(verifica_binario(line) == 0)
        {
            if(verifica_reservada(line, reservadas, num_reservadas) == 0) //Se não for binário e nem reservada, trata-se de um erro de sintaxe
            {
                printf("\n-ERRO DE SINTAXE-\nInstrucao errada '%s' corrija e recompile\n", line);
                return 1;
            }
        }
        if(strcmp(line, "ADD") == 0) fprintf(output_file, "00000000\n"); //série de comparações utilizando strcmp, retorna 0 se verdadeiro, fprintf escreve no output a string passada
        else if(strcmp(line, "SUB") == 0) fprintf(output_file, "00101000\n");
        else if(strcmp(line, "MUL") == 0) fprintf(output_file, "11110110\n");
        else if(strcmp(line, "DIV")== 0) fprintf(output_file, "11110110\n");
        else fprintf(output_file,"%s\n" ,line);
    }


    fclose(input_file);
    fclose(output_file);
}

