#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 50
#define MAX_NAME 50

// Função para contar linhas de um arquivo
int countLines(FILE* file) {
    int lines = 0;
    char buffer[MAX_LINE];

    while (fgets(buffer, MAX_LINE, file) != NULL) {
        lines++;
    }
    rewind(file); // Volta para o início do arquivo
    return lines;
}

// Função para extrair nome antes do _
char* getNameBeforeUnderscore(char* str) {
    char* result = strtok(str, "_");
    return strdup(result);
}

int main() {
    FILE* file1, * file2, * output;
    char line[MAX_LINE];
    char* names[MAX_LINE];
    char* diagonal[MAX_LINE];
    double diagonal_values[MAX_LINE];
    int lineCount1, lineCount2;
    int i = 0, j = 0;

    // Abre o primeiro arquivo
    file1 = fopen("fractions.txt", "r");
    if (file1 == NULL) {
        printf("Erro ao abrir arquivo1.txt\n");
        return 1;
    }

    // Abre o segundo arquivo
    file2 = fopen("fit_result.txt", "r");
    if (file2 == NULL) {
        printf("Erro ao abrir arquivo2.txt\n");
        fclose(file1);
        return 1;
    }

    // Conta linhas dos arquivos
    lineCount1 = countLines(file1);
    lineCount2 = countLines(file2);

    // Pega elementos da diagonal do primeiro arquivo
    i = 0;
    while (fgets(line, MAX_LINE, file1) != NULL && i < lineCount1) {
        char* token = strtok(line, " \t\n");
        int col = 0;

        while (token != NULL && col < i) {
            token = strtok(NULL, " \t\n");
            col++;
        }

        if (token != NULL) {
            diagonal[i] = strdup(token);
            diagonal_values[i] = atof(token) * 100;
        }
        i++;
    }

    // Pega nomes da primeira coluna a cada 2 linhas do segundo arquivo
    i = 0;
    j = 1;
    while (fgets(line, MAX_LINE, file2) != NULL && j < lineCount2) {
        if (j % 2 == 0) {  // A cada 2 linhas
            char* token = strtok(line, " \t\n");
            if (token != NULL) {
                names[i] = getNameBeforeUnderscore(token);
                i++;
            }
        }
        j++;
    }

    // Cria arquivo de saída
    output = fopen("saida.txt", "w");
    if (output == NULL) {
        printf("Erro ao criar arquivo de saída\n");
        goto cleanup;
    }
    double sum=0;
    // Escreve no arquivo de saída
    for (int k = 0; k < i && k < lineCount1; k++) {
        fprintf(output, "%s\t%.2f\n", names[k], diagonal_values[k]);
        sum+= diagonal_values[k];
    }
    fprintf(output, "\nSum\t%.2f\n",sum);


    printf("Arquivo de saída criado com sucesso!\n");

    // Libera memória e fecha arquivos
cleanup:
    for (int k = 0; k < i; k++) {
        free(names[k]);
    }
    for (int k = 0; k < lineCount1; k++) {
        free(diagonal[k]);
    }
    fclose(file1);
    fclose(file2);
    if (output != NULL) {
        fclose(output);
    }

    return 0;
}