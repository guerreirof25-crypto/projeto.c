#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum{CARRO=1,MOTO,CAMINHAO} Tipo;

typedef struct{
  int id;
  int removido;
  Tipo tipo;
  char nome[40];
  union{
    struct{int portas;int manut[3][2];} carro;
    struct{int cilindradas;} moto;
    struct{float carga;} caminhao;
  }info;
}Veiculo;

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\FUNÇOES PARA AJUDAR A GENTE A FZR O TRABALHO\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int lerInt(const char *msg) {
    int n;
    printf("%s", msg);
    while (scanf("%d", &n) != 1) {
        printf("Valor inválido, digite novamente: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return n;
}

float lerFloat(const char *msg) {
    float n;
    printf("%s", msg);
    while (scanf("%f", &n) != 1) {
        printf("Valor inválido, digite novamente: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return n;
}

void lerString(const char *msg, char *dest, size_t tam) {
    printf("%s", msg);
    fgets(dest, tam, stdin);
    dest[strcspn(dest, "\n")] = 0;
}

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

\\editar o veiculo Anna
void editar() {
    int id = lerInt("ID do veículo a editar: ");
    FILE *f = fopen(ARQ, "rb+");
    if (!f) {
        puts("Arquivo não encontrado.");
        return;
    }
 Veiculo v;
    long pos = 0;
    int achou = 0;

    while (fread(&v, sizeof(Veiculo), 1, f)) {
        if (v.id == id && !v.removido) {
            pos = ftell(f) - sizeof(Veiculo);
            achou = 1;
            break;
        }
    }

    if (!achou) {
        puts("Veículo não encontrado.");
        fclose(f);
        return;
    }
  
    lerString("Novo nome: ", v.nome, sizeof(v.nome));
    fseek(f, pos, SEEK_SET);
    fwrite(&v, sizeof(Veiculo), 1, f);
    fclose(f);
    puts("Veículo atualizado com sucesso!");
}
///////////////////////////////
//remover lógoco Anna









 //PROXIMO ID
int proximoID() {
    FILE *f = fopen(ARQ, "rb");
    if (!f) return 1;
    Veiculo v;
    int max = 0;
    while (fread(&v, sizeof(Veiculo), 1, f))
        if (v.id > max) max = v.id;
    fclose(f);
    return max + 1;
}

\\\\\\\\\\\\\\\\PRA EXIBIR O VEICULO
void mostrarVeiculo(Veiculo v) {
    printf("\n--- Detalhes do veículo ---\n");
    printf("ID: %d\n", v.id);
    printf("Nome: %s\n", v.nome);
    printf("Tipo: ");
    switch (v.tipo) {
        case CARRO:
            printf("Carro\nPortas: %d\n", v.info.carro.portas);
            break;
        case MOTO:
            printf("Moto\nCilindradas: %d\n", v.info.moto.cilindradas);
            break;
        case CAMINHAO:
            printf("Caminhão\nCapacidade de carga: %.1f toneladas\n", v.info.caminhao.carga);
            break;
    }
    printf("---------------------------\n");
}





