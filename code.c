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











