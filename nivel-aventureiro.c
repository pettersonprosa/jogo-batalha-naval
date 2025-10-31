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

// Função para verificar sobreposição de navios (versão melhorada)
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                         int linha, int coluna, int direcao, int tamanho) {
    // direcao: 0 = horizontal, 1 = vertical, 2 = diagonal direita, 3 = diagonal esquerda
    
    for (int i = 0; i < tamanho; i++) {
        int posL, posC;
        
        switch (direcao) {
            case 0: // Horizontal
                posL = linha;
                posC = coluna + i;
                break;
            case 1: // Vertical
                posL = linha + i;
                posC = coluna;
                break;
            case 2: // Diagonal direita (linha e coluna aumentam)
                posL = linha + i;
                posC = coluna + i;
                break;
            case 3: // Diagonal esquerda (linha aumenta, coluna diminui)
                posL = linha + i;
                posC = coluna - i;
                break;
            default:
                return 0; // Direção inválida
        }
        
        if (!posicaoValida(posL, posC) || tabuleiro[posL][posC] == NAVIO) {
            return 0; // Sobreposição detectada ou posição inválida
        }
    }
    return 1; // Sem sobreposição
}

// Função para posicionar um navio (versão melhorada)
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
        
        switch (direcao) {
            case 0: // Horizontal
                posL = linha;
                posC = coluna + i;
                break;
            case 1: // Vertical
                posL = linha + i;
                posC = coluna;
                break;
            case 2: // Diagonal direita
                posL = linha + i;
                posC = coluna + i;
                break;
            case 3: // Diagonal esquerda
                posL = linha + i;
                posC = coluna - i;
                break;
            default:
                return 0; // Direção inválida
        }
        
        tabuleiro[posL][posC] = NAVIO;
    }
    
    return 1; // Navio posicionado com sucesso
}

// Função para exibir informações dos navios posicionados
void exibirInformacoesNavios() {
    printf("\n=== INFORMAÇÕES DOS NAVIOS ===\n");
    printf("Navio 1: Horizontal - Linha 2, Coluna 3\n");
    printf("Navio 2: Vertical - Linha 5, Coluna 7\n");
    printf("Navio 3: Diagonal Direita - Linha 0, Coluna 0\n");
    printf("Navio 4: Diagonal Esquerda - Linha 1, Coluna 7\n");
    printf("Todos os navios têm tamanho: %d\n", TAMANHO_NAVIO);
}

int main() {
    printf("=== JOGO DE BATALHA NAVAL - NÍVEL AVENTUREIRO ===\n");
    printf("Desenvolvido conforme especificações do documento\n\n");
    
    // Declarar e inicializar o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);
    
    printf("Posicionando 4 navios no tabuleiro...\n\n");
    
    // 1. Navio horizontal (do nível anterior)
    printf("1. Posicionando navio horizontal na linha 2, coluna 3...\n");
    if (posicionarNavio(tabuleiro, 2, 3, 0, TAMANHO_NAVIO)) {
        printf("   ✓ Navio horizontal posicionado com sucesso!\n");
    }
    
    // 2. Navio vertical (do nível anterior)
    printf("2. Posicionando navio vertical na linha 5, coluna 7...\n");
    if (posicionarNavio(tabuleiro, 5, 7, 1, TAMANHO_NAVIO)) {
        printf("   ✓ Navio vertical posicionado com sucesso!\n");
    }
    
    // 3. Navio diagonal direita (NOVO - nível aventureiro)
    printf("3. Posicionando navio diagonal direita na linha 0, coluna 0...\n");
    if (posicionarNavio(tabuleiro, 0, 0, 2, TAMANHO_NAVIO)) {
        printf("   ✓ Navio diagonal direita posicionado com sucesso!\n");
    }
    
    // 4. Navio diagonal esquerda (NOVO - nível aventureiro)
    printf("4. Posicionando navio diagonal esquerda na linha 1, coluna 7...\n");
    if (posicionarNavio(tabuleiro, 1, 7, 3, TAMANHO_NAVIO)) {
        printf("   ✓ Navio diagonal esquerda posicionado com sucesso!\n");
    }
    
    // Exibir informações detalhadas
    exibirInformacoesNavios();
    
    // Exibir tabuleiro final
    exibirTabuleiro(tabuleiro);
    
    // Verificação visual dos navios diagonais
    printf("\n=== VERIFICAÇÃO DOS NAVIOS DIAGONAIS ===\n");
    printf("Navio Diagonal Direita (linha 0, coluna 0):\n");
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        printf("  Posição [%d][%d] = %d\n", 0+i, 0+i, tabuleiro[0+i][0+i]);
    }
    
    printf("Navio Diagonal Esquerda (linha 1, coluna 7):\n");
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        printf("  Posição [%d][%d] = %d\n", 1+i, 7-i, tabuleiro[1+i][7-i]);
    }
    
    return 0;
}