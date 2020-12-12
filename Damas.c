#include <stdlib.h>
#include <stdio.h>
#define cls system("cls")
#define pause system("pause")

char grid[10][10];
int num_grid[10][10];
typedef struct pos{
    int n1, n2, c1, c2;
}POS;

int move(POS *p, int player);
void start_grid();
void print_p1_grid();
void print_p2_grid();
int check_winner();

int main(){
    int player = 1, valid, winner;
    char C1, C2;
    POS *mov;
    start_grid();
    do{
        if (player == 1){
            cls;
            mov = (POS *)malloc(sizeof(POS));
            print_p1_grid();
            printf("Player 1 it's your turn:");
            fflush(stdin);
            scanf("%c%d %c%d",&C1,&mov->n1,&C2,&mov->n2);
            mov->c1 = (int)C1 - 65;
            mov->n1 = mov->n1 - 1;
            mov->c2 = (int)C2 - 65;
            mov->n2 = mov->n2 - 1;
            valid = move(mov, player);
            if (valid == 0)
                player = -1;
            else{
                printf("Invalid movment\n");
                pause;
            }
            free(mov);
            winner = check_winner();
            if (winner != 0)
                player = 0;
        }
        if (player == -1){
            cls;
            mov = (POS *)malloc(sizeof(POS));
            print_p2_grid();
            printf("Player 2 it's your turn:");
            fflush(stdin);
            scanf("%c%d %c%d",&C1,&mov->n1,&C2,&mov->n2);
            mov->c1 = (int)C1 - 65;
            mov->n1 = mov->n1 - 1;
            mov->c2 = (int)C2 - 65;
            mov->n2 = mov->n2 - 1;
            valid = move(mov, player);
            if (valid == 0)
                player = 1;
            else{
                printf("Invalid movement\n");
                pause;
            }
            free(mov);
            winner = check_winner();
            if (winner != 0)
                player = 0;
        }
    }while(player != 0);
    cls;
    if (winner == 1)
        printf("Player 1 won the game!!");
    else
        printf("Player 2 won the game!!");
    return 0;
}

void start_grid(){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (i < 4){
                if(i % 2 == 0){
                    if (j % 2 == 0){
                        grid[i][j] = 'X';
                        num_grid[i][j] = -1;
                    }else{
                        grid[i][j] = ' ';
                        num_grid[i][j] = 0;
                    }
                }else{
                    if (j % 2 == 0){
                        grid[i][j] = ' ';
                        num_grid[i][j] = 0;
                    }else{
                        grid[i][j] = 'X';
                        num_grid[i][j] = -1;
                    }
                }
            }else if(i > 5){
                if(i % 2 == 0){
                    if (j % 2 == 0){
                        grid[i][j] = 'O';
                        num_grid[i][j] = 1;
                    }else{
                        grid[i][j] = ' ';
                        num_grid[i][j] = 0;
                    }
                }else{
                    if (j % 2 == 0){
                        grid[i][j] = ' ';
                        num_grid[i][j] = 0;
                    }else{
                        grid[i][j] = 'O';
                        num_grid[i][j] = 1;
                    }
                }
            }else{
                grid[i][j] = ' ';
                num_grid[i][j] = 0;
            }
        }
    }
}

void print_p1_grid(){
    printf("       A   B   C   D   E   F   G   H   I   J  \n");
    printf("       |   |   |   |   |   |   |   |   |   |  \n");
    for (int i = 0; i < 10; i++){
        printf("     ");
        for (int j = 0; j < 10; j++){
            printf("----");
        }
        printf("-\n");
        if(i != 9)
            printf("%d----|",i+1);
        else
            printf("%d---|",i+1);
        for (int k = 0; k < 10; k++){
            printf(" %c |",grid[i][k]);
        }
        printf("\n");
    }
    printf("     -----------------------------------------\n");
}

void print_p2_grid(){
    printf("       J   I   H   G   F   E   D   C   B   A  \n");
    printf("       |   |   |   |   |   |   |   |   |   |  \n");
    for (int i = 9; i >= 0; i--){
        printf("     ");
        for (int j = 9; j >= 0; j--){
            printf("----");
        }
        printf("-\n");
        if(i != 9)
            printf("%d----|",i+1);
        else
            printf("%d---|",i+1);
        for (int k = 9; k >= 0; k--){
            printf(" %c |",grid[i][k]);
        }
        printf("\n");
    }
    printf("     -----------------------------------------\n");
}

int move(POS *p, int player){
    if (num_grid[p->n2][p->c2] != 0)
        return 1;
    if (p->n1 == p->n2 || p->c1 == p->c2)
        return 1;
    if (player == 1){
        if ((p->n1 - p->n2) <= 0){
            return 1;
        }else if ((p->n1 - p->n2) == 2){
            if ((p->c1 - p->c2) == 2){
                if(num_grid[p->n2 + 1][p->c2 + 1] == -1){
                    num_grid[p->n2 + 1][p->c2 + 1] = 0;
                    grid[p->n2 + 1][p->c2 + 1] = ' ';
                }
            }else if ((p->c1 - p->c2) == -2){
                if(num_grid[p->n2 + 1][p->c2 - 1] == -1){
                    num_grid[p->n2 + 1][p->c2 - 1] = 0;
                    grid[p->n2 + 1][p->c2 - 1] = ' ';
                }
            }
        }
    }
    if (player == -1){
        if((p->n1 - p->n2) >= 0){
            return 1;
        }else if ((p->n1 - p->n2) == -2){
            if ((p->c1 - p->c2) == 2){
                if(num_grid[p->n2 - 1][p->c2 + 1] == 1){
                    num_grid[p->n2 - 1][p->c2 + 1] = 0;
                    grid[p->n2 - 1][p->c2 + 1] = ' ';
                }
            }else if ((p->c1 - p->c2) == -2){
                if(num_grid[p->n2 - 1][p->c2 - 1] == 1){
                    num_grid[p->n2 - 1][p->c2 - 1] = 0;
                    grid[p->n2 - 1][p->c2 - 1] = ' ';
                }
            }
        }
    }
    num_grid[p->n1][p->c1] = 0;
    num_grid[p->n2][p->c2] = player;
    grid[p->n1][p->c1] = ' ';
    if (player == 1)
        grid[p->n2][p->c2] = 'O';
    else
        grid[p->n2][p->c2] = 'X';
    return 0;
}

int check_winner(){
    int sum_p1 = 0, sum_p2 = 0;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (num_grid[i][j] == 1)
                sum_p1++;
            if (num_grid[i][j] == -1)
                sum_p2++;
        }
    }
    if (sum_p1 == 0)
        return -1;
    if (sum_p2 == 0)
        return 1;
    return 0;
}
