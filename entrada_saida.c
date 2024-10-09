#include <stdio.h>
#include <stdlib.h>

int main() {
    char texto[256];

    // Solicita que o usuário insira um texto
    printf("Digite o texto que deseja imprimir: ");
    fgets(texto, sizeof(texto), stdin);

    // Envia o texto para a impressora usando o comando lp
    FILE *fp = popen("lp", "w");
    if (fp == NULL) {
        printf("Erro ao abrir a impressora.\n");
        return 1;
    }

    // Escreve o texto digitado na impressora
    fprintf(fp, "%s", texto);
    pclose(fp);

    printf("Texto enviado para a impressora.\n");
    return 0;
}
