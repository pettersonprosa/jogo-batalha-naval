#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n");
    printf("    ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("Legenda: 0 = Água, 3 = Navio\n");
}

// Função para validar se uma posição está dentro do tabuleiro
int posicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO_TABULEIRO && 
            coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Função para verificar sobreposição de navios
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                         int linha, int coluna, int direcao, int tamanho) {
    // direcao: 0 = horizontal, 1 = vertical
    
    for (int i = 0; i < tamanho; i++) {
        int posL, posC;
        
        if (direcao == 0) { // Horizontal
            posL = linha;
            posC = coluna + i;
        } else { // Vertical
            posL = linha + i;
            posC = coluna;
        }
        
        if (!posicaoValida(posL, posC) || tabuleiro[posL][posC] == NAVIO) {
            return 0; // Sobreposição detectada ou posição inválida
        }
    }
    return 1; // Sem sobreposição
}

// Função para posicionar um navio
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                   int linha, int coluna, int direcao, int tamanho) {
    // Validar posições
    if (!verificarSobreposicao(tabuleiro, linha, coluna, direcao, tamanho)) {
        printf("Erro: Navio sobrepõe outro ou está fora do tabuleiro!\n");
        return 0;
    }
    
    // Posicionar navio
    for (int i = 0; i < tamanho; i++) {
        int posL, posC;
        
        if (direcao == 0) { // Horizontal
            posL = linha;
            posC = coluna + i;
        } else { // Vertical
            posL = linha + i;
            posC = coluna;
        }
        
        tabuleiro[posL][posC] = NAVIO;
    }
    
    return 1; // Navio posicionado com sucesso
}

int main() {
    printf("=== JOGO DE BATALHA NAVAL - NÍVEL NOVATO ===\n");
    printf("Desenvolvido conforme especificações do documento\n\n");
    
    // Declarar e inicializar o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);
    
    // Posicionar navio horizontal (linha 2, coluna 3)
    printf("Posicionando navio horizontal na linha 2, coluna 3...\n");
    if (posicionarNavio(tabuleiro, 2, 3, 0, TAMANHO_NAVIO)) {
        printf("Navio horizontal posicionado com sucesso!\n");
    }
    
    // Posicionar navio vertical (linha 5, coluna 7)
    printf("Posicionando navio vertical na linha 5, coluna 7...\n");
    if (posicionarNavio(tabuleiro, 5, 7, 1, TAMANHO_NAVIO)) {
        printf("Navio vertical posicionado com sucesso!\n");
    }
    
    // Exibir tabuleiro final
    exibirTabuleiro(tabuleiro);
    
    return 0;
}