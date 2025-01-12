#include <stdio.h>
#include <string.h>

#define INPUT_FILE "input.asm"
#define OUTPUT_FILE "output.txt"

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

    char line[50];

    while(fgets(line, sizeof(line), input_file))//fgets tenta ler cada linha do arquivo e armazenar no vetor temporário line, se for bem-sucedido retorna um ponteiro para line, se não retorna NULL, funcionando assim como condição para o laço
    {
        line[strcspn(line, "\n")] = '\0'; //strcspn procura a substring passada dentro da string passada e retorna seu índice. Substituo "\n" por '\0' para evitar problemas de comparação posteriores com "ADD" por exemplo
     
        if(strcmp(line, "ADD") == 0) fprintf(output_file, "00000000\n"); //série de comparações utilizando strcmp, retorna 0 se verdadeiro, fprintf escreve no output a string passada
        else if(strcmp(line, "SUB") == 0) fprintf(output_file, "00101000\n");
        else if(strcmp(line, "MUL") == 0) fprintf(output_file, "11110110\n");
        else if(strcmp(line, "DIV")== 0) fprintf(output_file, "11110110\n");
        else fprintf(output_file,"%s\n" ,line);
    }

    fclose(input_file);
    fclose(output_file);
}

