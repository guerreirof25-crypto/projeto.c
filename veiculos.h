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
