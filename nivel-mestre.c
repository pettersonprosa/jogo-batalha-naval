#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

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
    printf("Legenda: 0 = Água, 3 = Navio, 5 = Área de Habilidade\n");
}

// Função para validar se uma posição está dentro do tabuleiro
int posicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO_TABULEIRO && 
            coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Função para verificar sobreposição de navios
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                         int linha, int coluna, int direcao, int tamanho) {
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
                return 0;
        }
        
        if (!posicaoValida(posL, posC) || tabuleiro[posL][posC] == NAVIO) {
            return 0;
        }
    }
    return 1;
}

// Função para posicionar um navio
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                   int linha, int coluna, int direcao, int tamanho) {
    if (!verificarSobreposicao(tabuleiro, linha, coluna, direcao, tamanho)) {
        return 0;
    }
    
    for (int i = 0; i < tamanho; i++) {
        int posL, posC;
        
        switch (direcao) {
            case 0: posL = linha; posC = coluna + i; break;
            case 1: posL = linha + i; posC = coluna; break;
            case 2: posL = linha + i; posC = coluna + i; break;
            case 3: posL = linha + i; posC = coluna - i; break;
            default: return 0;
        }
        
        tabuleiro[posL][posC] = NAVIO;
    }
    return 1;
}

// Habilidade 1: CONE (conforme exemplo: 3 linhas, 5 colunas)
void criarHabilidadeCone(int habilidade[3][5]) {
    // Inicializar toda a matriz com 0
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Linha 0: centro apenas (índice 2)
    habilidade[0][2] = 1;
    
    // Linha 1: centro e adjacentes (índices 1, 2, 3)
    habilidade[1][1] = 1;
    habilidade[1][2] = 1;
    habilidade[1][3] = 1;
    
    // Linha 2: linha completa (índices 0 a 4)
    for (int j = 0; j < 5; j++) {
        habilidade[2][j] = 1;
    }
}

// Habilidade 2: CRUZ
void criarHabilidadeCruz(int habilidade[3][5]) {
    // Inicializar toda a matriz com 0
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Linha 0: centro apenas (índice 2)
    habilidade[0][2] = 1;
    
    // Linha 1: linha completa (índices 0 a 4)
    for (int j = 0; j < 5; j++) {
        habilidade[1][j] = 1;
    }
    
    // Linha 2: centro apenas (índice 2)
    habilidade[2][2] = 1;
}

// Habilidade 3: OCTAEDRO
void criarHabilidadeOctaedro(int habilidade[3][5]) {
    // Inicializar toda a matriz com 0
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            habilidade[i][j] = 0;
        }
    }
    
    // Linha 0: centro apenas (índice 2)
    habilidade[0][2] = 1;
    
    // Linha 1: centro e adjacentes (índices 1, 2, 3)
    habilidade[1][1] = 1;
    habilidade[1][2] = 1;
    habilidade[1][3] = 1;
    
    // Linha 2: centro apenas (índice 2)
    habilidade[2][2] = 1;
}

// Função para exibir uma matriz de habilidade
void exibirHabilidade(int habilidade[3][5], char* nome) {
    printf("\n=== HABILIDADE: %s ===\n", nome);
    
    // Mostrar apenas o formato gerado uma vez
    printf("Formato:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

// Função para aplicar habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      int habilidade[3][5], 
                      int centroLinha, int centroColuna) {
    
    printf("Aplicando habilidade com centro em [%d][%d]...\n", centroLinha, centroColuna);
    
    int offsetLinha = 1; // Centro na linha 1 (de 0-2)
    int offsetColuna = 2; // Centro na coluna 2 (de 0-4)
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            int posL = centroLinha - offsetLinha + i;
            int posC = centroColuna - offsetColuna + j;
            
            // CORREÇÃO: Só marca como habilidade se for água (0)
            // Navios (3) mantêm seu valor e NÃO são sobrescritos
            if (posicaoValida(posL, posC) && habilidade[i][j] == 1) {
                if (tabuleiro[posL][posC] == AGUA) { // SÓ marca água
                    tabuleiro[posL][posC] = HABILIDADE;
                }
                // Se for navio (3), mantém o navio - NÃO substitui
            }
        }
    }
}

// Função para demonstrar as habilidades
void demonstrarHabilidades() {
    printf("\n=== DEMONSTRAÇÃO DAS HABILIDADES (3x5) ===\n");
    
    int cone[3][5];
    int cruz[3][5];
    int octaedro[3][5];
    
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);
    
    exibirHabilidade(cone, "CONE");
    exibirHabilidade(cruz, "CRUZ");
    exibirHabilidade(octaedro, "OCTAEDRO");
}

int main() {
    // Demonstrar formatos das habilidades
    demonstrarHabilidades();
    
    // Declarar e inicializar o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);
    
    printf("\n=== FASE 1: POSICIONAMENTO DE NAVIOS ===\n");
    
    // Posicionar os 4 navios (do nível aventureiro)
    printf("Posicionando navios...\n");
    posicionarNavio(tabuleiro, 2, 3, 0, TAMANHO_NAVIO); // Horizontal
    posicionarNavio(tabuleiro, 5, 7, 1, TAMANHO_NAVIO); // Vertical
    posicionarNavio(tabuleiro, 0, 0, 2, TAMANHO_NAVIO); // Diagonal direita
    posicionarNavio(tabuleiro, 1, 7, 3, TAMANHO_NAVIO); // Diagonal esquerda
    
    printf("✓ 4 navios posicionados com sucesso!\n");
    
    // Exibir tabuleiro apenas com navios
    printf("\n--- Tabuleiro com Navios ---");
    exibirTabuleiro(tabuleiro);
    
    printf("\n=== FASE 2: APLICAÇÃO DAS HABILIDADES ESPECIAIS ===\n");
    
    // Criar matrizes de habilidades
    int cone[3][5];
    int cruz[3][5];
    int octaedro[3][5];
    
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);
    
    // Aplicar habilidades em posições estratégicas
    printf("\n1. Aplicando Habilidade CONE...\n");
    aplicarHabilidade(tabuleiro, cone, 7, 5);
    
    printf("\n2. Aplicando Habilidade CRUZ...\n");
    aplicarHabilidade(tabuleiro, cruz, 3, 3);
    
    printf("\n3. Aplicando Habilidade OCTAEDRO...\n");
    aplicarHabilidade(tabuleiro, octaedro, 5, 5);
    
    // Exibir tabuleiro final com habilidades
    printf("\n--- TABULEIRO FINAL COM HABILIDADES ---");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}