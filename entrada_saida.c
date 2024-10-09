#include <stdio.h>
#include <stdlib.h>

int main() {
    char texto[256];
    FILE *arquivo;

    printf("Digite o texto que deseja imprimir: ");
    fgets(texto, sizeof(texto), stdin);

    arquivo = fopen("texto_para_impressao.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        return 1;
    }

    fprintf(arquivo, "%s", texto);
    fclose(arquivo);

    int resultado = system("lp texto_para_impressao.txt");
    if (resultado != 0) {
        printf("Erro ao enviar o arquivo para a impressora.\n");
        return 1;
    }

    remove("texto_para_impressao.txt");

    printf("Texto enviado para a impressora com sucesso.\n");
    return 0;
}

