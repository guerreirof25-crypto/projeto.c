#ifndef VEICULOS_H
#define VEICULOS_H

// Enumeração que define os tipos de veículos possíveis

typedef enum{CARRO=1,MOTO,CAMINHAO} Tipo;

/*
Estrutura principal que representa um veículo no sistema.

Campos comuns:
 - id: identificador único do veículo.
 - removido: indica se o registro foi removido logicamente (0 = ativo, 1 = removido).
 - tipo: define se é carro, moto ou caminhão.
 - nome: nome ou modelo do veículo.

Campos específicos (dentro da união):
 - carro: possui quantidade de portas e manutenção (3 registros, cada um com data e custo).
 - moto: possui número de cilindradas.
 - caminhão: possui capacidade de carga.
*/

typedef struct{
  int id;
  int removido;
  Tipo tipo;
  char nome[40];

  // União que guarda as informações específicas de cada tipo de veículo

  union{
    struct{int portas;int manut[3][2];} carro; // Cada linha: [data, custo] ou outro formato definido no projeto
    struct{int cilindradas;} moto;
    struct{float carga;} caminhao;
  }info;
}Veiculo;

#endif // VEICULOS_H
