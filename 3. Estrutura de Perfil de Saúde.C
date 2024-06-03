#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int dia, mes, ano;
} DataNascimento;

typedef struct {
    char nome[100];
    float peso;
    float altura;
    DataNascimento dataNascimento;
} PerfilSaude;

void calcularIdade(DataNascimento* data) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int idade = tm.tm_year + 1900 - data->ano;
    if (tm.tm_mon + 1 < data->mes || (tm.tm_mon + 1 == data->mes && tm.tm_mday < data->dia)) {
        idade--;
    }
    printf("Idade: %d anos\n", idade);
}

float calcularIMC(float peso, float altura) {
    return peso / (altura * altura);
}

void classificarIMC(float imc) {
    if (imc < 18.5) {
        printf("Classificação: Abaixo do peso\n");
    } else if (imc < 24.9) {
        printf("Classificação: Peso normal\n");
    } else if (imc < 29.9) {
        printf("Classificação: Sobrepeso\n");
    } else {
        printf("Classificação: Obesidade\n");
    }
}

void exibirPerfil(PerfilSaude* perfil) {
    printf("Nome: %s\n", perfil->nome);
    printf("Peso: %.2f kg\n", perfil->peso);
    printf("Altura: %.2f m\n", perfil->altura);
    printf("Data de Nascimento: %02d/%02d/%04d\n", perfil->dataNascimento.dia, perfil->dataNascimento.mes, perfil->dataNascimento.ano);
    calcularIdade(&perfil->dataNascimento);
    float imc = calcularIMC(perfil->peso, perfil->altura);
    printf("IMC: %.2f\n", imc);
    classificarIMC(imc);
}

int main() {
    PerfilSaude perfil;

    printf("Digite o nome: ");
    scanf(" %[^\n]s", perfil.nome);
    printf("Digite o peso (kg): ");
    scanf("%f", &perfil.peso);
    printf("Digite a altura (m): ");
    scanf("%f", &perfil.altura);
    printf("Digite a data de nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &perfil.dataNascimento.dia, &perfil.dataNascimento.mes, &perfil.dataNascimento.ano);

    exibirPerfil(&perfil);

    return 0;
}
