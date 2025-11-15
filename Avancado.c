#include <stdio.h>

#define TAM 10      // Tamanho do tabuleiro
#define NAVIO 3     // Tamanho dos navios
#define AGUA 0      // Representação de água
#define NAVIO_ID 3  // Representação dos navios
#define HABIL 5     // Representação da área de habilidade

#define HAB 5       // Tamanho das matrizes de habilidade (5x5)

// Função auxiliar para verificar sobreposição
int haSobreposicao(int t[TAM][TAM], int l, int c) {
    return t[l][c] != AGUA;
}

int main() {

    //----------------------------------------------------------
    // 1. TABULEIRO PRINCIPAL
    //----------------------------------------------------------
    int tabuleiro[TAM][TAM];

    // Inicialização
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;

    //----------------------------------------------------------
    // 2. POSICIONAMENTO DOS NAVIOS (REAPROVEITADO DO NÍVEL ANTERIOR)
    //----------------------------------------------------------

    // Navio horizontal
    int hLinha = 2, hColuna = 1;
    for (int i = 0; i < NAVIO; i++)
        tabuleiro[hLinha][hColuna + i] = NAVIO_ID;

    // Navio vertical
    int vLinha = 4, vColuna = 7;
    for (int i = 0; i < NAVIO; i++)
        tabuleiro[vLinha + i][vColuna] = NAVIO_ID;

    // Navio diagonal "\"
    int d1Linha = 0, d1Coluna = 0;
    for (int i = 0; i < NAVIO; i++)
        tabuleiro[d1Linha + i][d1Coluna + i] = NAVIO_ID;

    // Navio diagonal "/"
    int d2Linha = 7, d2Coluna = 5;
    for (int i = 0; i < NAVIO; i++)
        tabuleiro[d2Linha + i][d2Coluna - i] = NAVIO_ID;

    //----------------------------------------------------------
    // 3. MATRIZES DE HABILIDADE (5x5)
    //----------------------------------------------------------
    int cone[HAB][HAB];
    int cruz[HAB][HAB];
    int octa[HAB][HAB];

    //----------------------------------------------------------
    // 3.1 MATRIZ DO CONE (forma triangular)
    //     - O topo é a linha 0, coluna central
    //     - A base se expande gradualmente
    //----------------------------------------------------------

    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {

            // Condicional para construir o cone
            // Expansão lateral cresce conforme descemos
            int meio = HAB / 2;
            if (j >= meio - i && j <= meio + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }

    //----------------------------------------------------------
    // 3.2 MATRIZ DA CRUZ
    //     - Linha central e coluna central valem 1
    //----------------------------------------------------------

    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (i == HAB / 2 || j == HAB / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }

    //----------------------------------------------------------
    // 3.3 MATRIZ DO OCTAEDRO (losango)
    //     - Construção pelo valor absoluto
    //----------------------------------------------------------

    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {

            // Distância até o centro
            int dist = abs((HAB / 2) - i) + abs((HAB / 2) - j);

            // Se dentro do raio, pinta
            if (dist <= HAB / 2)
                octa[i][j] = 1;
            else
                octa[i][j] = 0;
        }
    }

    //----------------------------------------------------------
    // 4. SOBREPOR HABILIDADES NO TABULEIRO
    //----------------------------------------------------------

    // Pontos de origem (fixos, conforme o requisito)
    int origemConeLinha = 1, origemConeColuna = 5;
    int origemCruzLinha = 6, origemCruzColuna = 2;
    int origemOctLinha  = 5, origemOctColuna  = 5;

    //----------------------------------------------------------
    // Função auxiliar de sobreposição (feito inline com loops)
    //----------------------------------------------------------

    // Sobreposição do CONE
    for (int i = 0; i < HAB; i++)
        for (int j = 0; j < HAB; j++)
            if (cone[i][j] == 1) {
                int L = origemConeLinha + i - HAB / 2;
                int C = origemConeColuna + j - HAB / 2;

                // Verificação de limites do tabuleiro
                if (L >= 0 && L < TAM && C >= 0 && C < TAM)
                    tabuleiro[L][C] = HABIL;
            }

    // Sobreposição da CRUZ
    for (int i = 0; i < HAB; i++)
        for (int j = 0; j < HAB; j++)
            if (cruz[i][j] == 1) {
                int L = origemCruzLinha + i - HAB / 2;
                int C = origemCruzColuna + j - HAB / 2;

                if (L >= 0 && L < TAM && C >= 0 && C < TAM)
                    tabuleiro[L][C] = HABIL;
            }

    // Sobreposição do OCTAEDRO
    for (int i = 0; i < HAB; i++)
        for (int j = 0; j < HAB; j++)
            if (octa[i][j] == 1) {
                int L = origemOctLinha + i - HAB / 2;
                int C = origemOctColuna + j - HAB / 2;

                if (L >= 0 && L < TAM && C >= 0 && C < TAM)
                    tabuleiro[L][C] = HABIL;
            }

    //----------------------------------------------------------
    // 5. EXIBIR O TABULEIRO COMPLETO
    //----------------------------------------------------------

    printf("\n===== TABULEIRO FINAL COM HABILIDADES =====\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {

            // Representação visual
            if (tabuleiro[i][j] == AGUA)
                printf("0 ");
            else if (tabuleiro[i][j] == NAVIO_ID)
                printf("3 ");
            else
                printf("5 "); // área de habilidade
        }
        printf("\n");
    }

    return 0;
}
