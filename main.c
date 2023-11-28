/**
 * @file main.c
 * @brief Minesweeper Game Implementation
 * @author Luís Morais
 * @date 21 de novembro de 2023, 13:08
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLS 4
#define LINES 4

typedef enum { FALSE, TRUE } bool;

/**
 * @brief Generate a random number within a specified range.
 * @param from The lower bound of the range.
 * @param to The upper bound of the range.
 * @return A random number within the specified range.
 */
int Random(int from, int to);

/**
 * @brief Print the game board.
 * @param tabuleiro The game board array.
 * @param debug If TRUE, print the actual values; otherwise, hide non-zero values.
 */
void print(int tabuleiro[LINES][COLS], bool debug);

/**
 * @brief Fill the game board with random values within a specified range.
 * @param tabuleiro The game board array.
 * @param from The lower bound of the random values.
 * @param to The upper bound of the random values.
 */
void preencher(int tabuleiro[LINES][COLS], int from, int to);

/**
 * @brief Place bombs on the game board.
 * @param tabuleiro The game board array.
 * @param quantity The number of bombs to be placed.
 */
void bombas(int tabuleiro[LINES][COLS], int quantity);

/**
 * @brief Prompt the user for input and return the entered value.
 * @param question The prompt message.
 * @return The user's input.
 */
int pedir(char *question);

/**
 * @brief Verify the result of a move on the game board.
 * @param linha The row coordinate of the move.
 * @param coluna The column coordinate of the move.
 * @param tabuleiro The game board array.
 * @return 'n' if the move is successful, 'y' if the player loses.
 */
char verify(int linha, int coluna, int tabuleiro[LINES][COLS]);

/**
 * @brief Allow the user to choose the game difficulty.
 * @param tabuleiro The game board array.
 * @return The selected difficulty level ('1' for easy, '2' for medium, '3' for hard).
 */
char difficulty(int tabuleiro[LINES][COLS]);

/**
 * @brief The main function that executes the chocolate game.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return The exit status of the program.
 */
int main(int argc, char **argv) {
    //variables
    int tabuleiro[LINES][COLS];
    int linha;
    int coluna;
    char option;
    int chocolates = 0;
    char final;
    char bomb;
    
    // seed
    srand(time(NULL));
    
    bomb = difficulty(tabuleiro);
    
    switch (bomb) {
        case '1':
            preencher(tabuleiro, 1, 20);
            break;
        case '2':
            preencher(tabuleiro, 1, 40);
            break;
        case '3':
            preencher(tabuleiro, 1, 80);
            break;
    }
    
    switch(bomb) {
        case '1':
            bombas(tabuleiro, 3);
            break;
        case '2':    
            bombas(tabuleiro, 6);
            break;
        case '3':
            bombas(tabuleiro, 9);
            break;
    }
        
    do {
        system("clear");
        print(tabuleiro, FALSE);
        printf("Número total de chocolates: %d\n", chocolates);
        linha = pedir("Insira a coordenada da linha: ");
        coluna = pedir("Insira a coordenada da coluna: ");
        
        final = verify(linha, coluna, tabuleiro);

        if (final == 'n') {
            chocolates += tabuleiro[linha - 1][coluna - 1];
            tabuleiro[linha - 1][coluna - 1] = 0;
            printf("Pretende sair? (Y/n): ");
            scanf(" %c", &option);
        } else if (final == 'y') {
            option = 'y';
            chocolates = 0;
        }
    } while ((option != 'y' && option != 'Y'));
    
    printf("Chocolates Finais: %d", chocolates);
    
    return (EXIT_SUCCESS);
}


int Random(int from, int to) {
    // generate random number
    return (rand() % to) + from;
}

void print(int tabuleiro[LINES][COLS], bool debug) {
    int i, j;
    for (i = 0; i < LINES; i++) {
        printf("\n---------------------\n");
        printf("|");
         
        for (j = 0; j < COLS; j++) {
            if (debug == TRUE) {
                printf(" %2d |", tabuleiro[i][j]);
            } else if (tabuleiro[i][j] == 0) {
                printf("  0 |");
            } else {
                printf("    |");
            }
        }
    }
    printf("\n---------------------\n");
}

void preencher(int tabuleiro[LINES][COLS], int from, int to) {
    int i, j;
    
    for (i = 0; i < LINES; i++) {
        for (j = 0; j < COLS; j++) {
            tabuleiro[i][j] = Random(from, to);
        }
    }
}

void bombas(int tabuleiro[LINES][COLS], int quantity) {
    int linha;
    int coluna;
    
    do {
        linha = Random(0, 4);
        coluna = Random(0, 4);
        
        if (tabuleiro[linha][coluna] != -1) {
            tabuleiro[linha][coluna] = -1;
            quantity--;
        }
        
    } while (quantity != 0);
}

int pedir(char *question) {
    int linha;
    
    printf("%s", question);
    scanf("%d", &linha);
    
    return linha;
}

char verify(int linha, int coluna, int tabuleiro[LINES][COLS]) {
    if (tabuleiro[linha - 1][coluna - 1] > 0) {
        printf("Encontraste %d Milka de Morango! Parabéns!\n", tabuleiro[linha - 1][coluna - 1]);
        return 'n';
    } else if (tabuleiro[linha - 1][coluna - 1] == 0) {
        puts("Oh Quim, já jogaste aí!");
        return 'n';
    } else {
        puts("Calhou numa armadilha! PEERDESTE!");
        return 'y';
    }
}

char difficulty(int tabuleiro[LINES][COLS]) {
    char option;
    
    puts("-------------------------------");
    puts("Escolha a dificuldade do jogo: ");
    puts("-------------------------------");
    puts("1. Fácil");
    puts("2. Médio");
    puts("3. Difícil");
    puts("-------------------------------");
    printf(">>>");
    scanf(" %c", &option);
    
    return option;
}
