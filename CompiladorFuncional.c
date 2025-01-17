#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_BITS 8
#define INPUT_FILE "input.asm"
#define OUTPUT_FILE "output.txt"

void preencher_com_zeros(char *binario) {
    int tamanho = strlen(binario);
    if (tamanho < MAX_BITS) {
        char auxiliar[MAX_BITS];
        int zeros_restantes = MAX_BITS - tamanho;
        for (int i = 0; i < zeros_restantes; ++i) {
            auxiliar[i] = '0';
        }
        auxiliar[zeros_restantes] = '\0';
        strcat(auxiliar, binario);
        strcpy(binario, auxiliar);
    }
}

void converter_hexa_para_binario(char *linha, char *saida) {
    char *ptr = linha + 2;       // Remove o prefixo
    // ptr[strlen(ptr) - 1] = '\0'; // Remover \n do final da string
    char auxiliar[5];
    saida[0] = '\0';             // Limpa a saida de operações passadas e não sobrepõe
    while (*ptr != '\0') {
        switch(toupper(*ptr)) {
            case '0': 
            strcpy(auxiliar, "0000"); break; 
            case '1': 
            strcpy(auxiliar, "0001"); break; 
            case '2': 
            strcpy(auxiliar, "0010"); break; 
            case '3': 
            strcpy(auxiliar, "0011"); break; 
            case '4': 
            strcpy(auxiliar, "0100"); break; 
            case '5': 
            strcpy(auxiliar, "0101"); break; 
            case '6': 
            strcpy(auxiliar, "0110"); break; 
            case '7': 
            strcpy(auxiliar, "0111"); break; 
            case '8': 
            strcpy(auxiliar, "1000"); break; 
            case '9': 
            strcpy(auxiliar, "1001"); break; 
            case 'A': 
            strcpy(auxiliar, "1010"); break; 
            case 'B': 
            strcpy(auxiliar, "1011"); break; 
            case 'C':
            strcpy(auxiliar, "1100"); break; 
            case 'D':
            strcpy(auxiliar, "1101"); break; 
            case 'E':
            strcpy(auxiliar, "1110"); break; 
            case 'F':
            strcpy(auxiliar, "1111"); break; 
            default:
                printf("Caractere hexadecimal incorreto!\n");
                break;
        }
        strcat(saida, auxiliar);
        // printf("%s\n", auxiliar);
        ++ptr;
    }
    preencher_com_zeros(saida);
}

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

int verifica_hexadecimal(char *frase) {
    if (strncmp(frase, "0x", 2) == 0) return 1;
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

void remove_comentarios(char* frase)
{
    char* comentario = strchr(frase, ';'); // Procura o caractere ';'
    if (comentario != NULL)
    {
        *comentario = '\0'; // Trunca a linha no ponto onde o comentário começa
    }
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
    "ADD", "SUB", "MUL", "DIV", "AND", "OR", "NOT", "XOR", "NAND", "NOR", "XNOR", "SHL", "SHR", "CMP", "MOV", "GOTO", "JMP", "CALL", "RET", "JZ", "JZN"
    };

    int num_reservadas = sizeof(reservadas) / sizeof(reservadas[0]);
    
    char line[50];
    char binario[8];

    while(fgets(line, 50, input_file))//fgets tenta ler cada linha do arquivo e armazenar no vetor temporário line, se for bem-sucedido retorna um ponteiro para line, se não retorna NULL, funcionando assim como condição para o laço
    {
        line[strcspn(line, "\n")] = '\0'; //strcspn procura a substring passada dentro da string passada e retorna seu índice. Substituo "\n" por '\0' para evitar problemas de comparação posteriores com "ADD" por exemplo
        
        remove_comentarios(line); // Remove comentários da linha

        if (strlen(line) == 0) // Ignora linhas vazias (após remover comentários)
        {
            continue;
        }

        if(!verifica_binario(line))
        {
            if(!verifica_reservada(line, reservadas, num_reservadas) && !verifica_hexadecimal(line)) //Se não for binário e nem reservada, trata-se de um erro de sintaxe
            {
                printf("\n-ERRO DE SINTAXE-\nInstrucao errada '%s' corrija e recompile\n", line);
                return 1;
            }
        }

        if(strcmp(line, "ADD") == 0)      fprintf(output_file, "00000001\n");  //série de comparações utilizando strcmp, retorna 0 se verdadeiro, fprintf escreve no output a string passada
        else if(strcmp(line, "SUB") == 0) fprintf(output_file, "00000010\n"); 
        else if(strcmp(line, "MUL") == 0) fprintf(output_file, "00000011\n"); 
        else if(strcmp(line, "DIV") == 0) fprintf(output_file, "00000100\n"); 
        else if(strcmp(line, "AND") == 0) fprintf(output_file, "01110101\n"); 
        else if(strcmp(line, "OR") == 0)  fprintf(output_file, "01110110\n");
        else if(strcmp(line, "NOT") == 0) fprintf(output_file, "01111000\n"); 
        else if(strcmp(line, "XOR") == 0) fprintf(output_file, "01110111\n");
        else if(strcmp(line, "NAND") == 0) fprintf(output_file, "01111001\n");
        else if(strcmp(line, "NOR") == 0) fprintf(output_file, "01111010\n");
        else if(strcmp(line, "XNOR") == 0) fprintf(output_file, "01111011\n");
        else if(strcmp(line, "SHL") == 0) fprintf(output_file, "00111100\n");  
        else if(strcmp(line, "SHR") == 0) fprintf(output_file, "00111101\n");
        else if(strcmp(line, "CMP") == 0) fprintf(output_file, "00011111\n");
        else if(strcmp(line, "MOV") == 0) fprintf(output_file, "10000000\n");
        else if(strcmp(line, "JMP") == 0) fprintf(output_file, "10000001\n"); 
        else if(strcmp(line, "CALL") == 0) fprintf(output_file, "10000010\n");
        else if(strcmp(line, "RET") == 0) fprintf(output_file, "10000011\n");
        else if(strcmp(line, "GOTO") == 0) fprintf(output_file, "10000100\n");
        else if(strcmp(line, "JZ") == 0) fprintf(output_file, "10000101\n"); 
        else if(strcmp(line, "JNZ") == 0) fprintf(output_file, "10000111\n"); 
        // A linha possui o prefixo 0x
        else if (strncmp(line, "0x", 2) == 0) { 
            converter_hexa_para_binario(line, binario);
            fprintf(output_file, "%s\n",binario);
        }
        else fprintf(output_file,"%s\n" ,line);
    }


    fclose(input_file);
    fclose(output_file);
}