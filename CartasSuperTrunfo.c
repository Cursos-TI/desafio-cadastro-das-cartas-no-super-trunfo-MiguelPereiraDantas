#include <stdio.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char estado[3];
    char codigo[5];
    char nome[50];
    unsigned long int populacao;
    float pib;          // em bilhoes
    float area;         // km2
    int pontosTuristicos;
    float densidade;    // populacao / area
    float pibPerCapita; // PIB / populacao
} Carta;

// Funcao para exibir o nome do atributo
const char* nomeAtributo(int attr) {
    switch(attr) {
        case 1: return "Populacao";
        case 2: return "PIB (bilhoes)";
        case 3: return "Area (km2)";
        case 4: return "Pontos Turisticos";
        case 5: return "Densidade Demografica";
        case 6: return "PIB per Capita";
        default: return "Atributo invalido";
    }
}

// Funcao para obter o valor numerico do atributo
double valorAtributo(Carta c, int attr) {
    switch(attr) {
        case 1: return (double)c.populacao;
        case 2: return (double)c.pib;
        case 3: return (double)c.area;
        case 4: return (double)c.pontosTuristicos;
        case 5: return (double)c.densidade;
        case 6: return (double)c.pibPerCapita;
        default: return -1;
    }
}

// Funcao para comparacao
int comparaAtributos(int attr, double v1, double v2) {
    if (attr == 5) { // Densidade Demografica: menor vence
        if (v1 < v2) return 1;
        else if (v1 > v2) return 2;
        else return 0;
    } else { // Outros: maior vence
        if (v1 > v2) return 1;
        else if (v1 < v2) return 2;
        else return 0;
    }
}

int main() {
    setlocale(LC_ALL, "");

    Carta c1, c2;

    printf("Cadastro da Carta 1:\n");
    printf("Estado: "); scanf("%s", c1.estado);
    printf("Codigo: "); scanf("%s", c1.codigo);
    printf("Nome: "); scanf(" %[^\n]", c1.nome);
    printf("Populacao: "); scanf("%lu", &c1.populacao);
    printf("PIB (bilhoes): "); scanf("%f", &c1.pib);
    printf("Area (km2): "); scanf("%f", &c1.area);
    printf("Pontos Turisticos: "); scanf("%d", &c1.pontosTuristicos);

    printf("\nCadastro da Carta 2:\n");
    printf("Estado: "); scanf("%s", c2.estado);
    printf("Codigo: "); scanf("%s", c2.codigo);
    printf("Nome: "); scanf(" %[^\n]", c2.nome);
    printf("Populacao: "); scanf("%lu", &c2.populacao);
    printf("PIB (bilhoes): "); scanf("%f", &c2.pib);
    printf("Area (km2): "); scanf("%f", &c2.area);
    printf("Pontos Turisticos: "); scanf("%d", &c2.pontosTuristicos);

    // Calculos automaticos
    c1.densidade = c1.populacao / c1.area;
    c1.pibPerCapita = (c1.pib * 1e9f) / c1.populacao;

    c2.densidade = c2.populacao / c2.area;
    c2.pibPerCapita = (c2.pib * 1e9f) / c2.populacao;

    // Menu de escolha
    int atr1, atr2;
    printf("\n=== Escolha dos Atributos ===\n");
    printf("1 - Populacao\n2 - PIB\n3 - Area\n4 - Pontos Turisticos\n5 - Densidade Demografica\n6 - PIB per Capita\n");
    printf("Escolha o primeiro atributo: ");
    scanf("%d", &atr1);

    printf("Escolha o segundo atributo (diferente do primeiro): ");
    scanf("%d", &atr2);

    if (atr1 == atr2 || atr1 < 1 || atr1 > 6 || atr2 < 1 || atr2 > 6) {
        printf("Opcao invalida.\n");
        return 1;
    }

    // Comparacao dos atributos escolhidos
    double v1a1 = valorAtributo(c1, atr1);
    double v2a1 = valorAtributo(c2, atr1);

    double v1a2 = valorAtributo(c1, atr2);
    double v2a2 = valorAtributo(c2, atr2);

    double soma1 = v1a1 + v1a2;
    double soma2 = v2a1 + v2a2;

    printf("\n=== Resultado da Comparacao ===\n");
    printf("%-25s | %-15.2f | %-15.2f | %s\n", nomeAtributo(atr1), v1a1, v2a1,
           comparaAtributos(atr1, v1a1, v2a1) == 1 ? "Carta 1 vence" :
           comparaAtributos(atr1, v1a1, v2a1) == 2 ? "Carta 2 vence" : "Empate");

    printf("%-25s | %-15.2f | %-15.2f | %s\n", nomeAtributo(atr2), v1a2, v2a2,
           comparaAtributos(atr2, v1a2, v2a2) == 1 ? "Carta 1 vence" :
           comparaAtributos(atr2, v1a2, v2a2) == 2 ? "Carta 2 vence" : "Empate");

    printf("\nSoma dos atributos: Carta 1 = %.2f | Carta 2 = %.2f\n", soma1, soma2);
    if (soma1 > soma2)
        printf(">>> Carta 1 venceu na soma dos atributos! <<<\n");
    else if (soma2 > soma1)
        printf(">>> Carta 2 venceu na soma dos atributos! <<<\n");
    else
        printf(">>> Empate na soma dos atributos! <<<\n");

    // Calculo e comparacao do Super Poder
    float superPoder1 = c1.populacao + c1.pib + c1.area + c1.pontosTuristicos + (1.0f / c1.densidade) + c1.pibPerCapita;
    float superPoder2 = c2.populacao + c2.pib + c2.area + c2.pontosTuristicos + (1.0f / c2.densidade) + c2.pibPerCapita;

    printf("\nSuper Poder Carta 1: %.2f\n", superPoder1);
    printf("Super Poder Carta 2: %.2f\n", superPoder2);

    if (superPoder1 > superPoder2)
        printf(">>> Carta 1 venceu no Super Poder! <<<\n");
    else if (superPoder2 > superPoder1)
        printf(">>> Carta 2 venceu no Super Poder! <<<\n");
    else
        printf(">>> Empate no Super Poder! <<<\n");

    return 0;
}
