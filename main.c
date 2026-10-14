#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_USERS 1000
#define MAX_USERNAME 50
#define MAX_TOURNAMENTS 5000

void main_menu();
void player_menu();
void tournament_menu();
void update_score(char name[MAX_USERNAME], int points);
int search_username(char username[MAX_USERNAME]);

char usernames[MAX_USERS][MAX_USERNAME];
int score[MAX_USERS];
int users = 0;

int total_players[MAX_TOURNAMENTS];
int tournaments_points[MAX_TOURNAMENTS][MAX_USERS]; 
char tournaments_players[MAX_TOURNAMENTS][MAX_USERS][MAX_USERNAME];
int tournaments = 0;

void update_score(char name[MAX_USERNAME], int points){
    int index = search_username(name);
    if (index == -1){
        strcpy(usernames[users], name);
        score[users] = points;
        users++;
    } else {
        score[index] += points;
    }
}

int search_username(char username[MAX_USERNAME]){
    for (int i = 0; i < users; i++){
        if (strcmp(username, usernames[i]) == 0){
            return i;
        } 
    }
    return -1;
}

void player_menu(){
    while(1) {
        printf("########################\n");
        printf("####### Jogadores ######\n");
        printf("########################\n");
        printf("## Escolha uma opção ###\n");
        printf("########################\n");
        printf("##### [1] Novo #########\n");
        printf("##### [2] Consultar ####\n");
        printf("##### [3] Remover ######\n");
        printf("##### [4] Sair #########\n");
        printf("########################\n");
        char option = ' ';
        while(option != '1' && option != '2' && option != '3' && option != '4'){
            option = getchar();
        } 
        if (option == '1'){
            char username[MAX_USERNAME];
            printf("Informe o nome do novo jogador: ");
            scanf("%s", username);
            int index = search_username(username);
            if (index != -1){
                printf("Erro: Usuário já cadastrado");
            } else{
                strcpy(usernames[users], username);
                score[users] = 0;
                users++;
                printf("Jogador cadastrado com sucesso!");
            } 
        } else if (option == '2'){
            char username[MAX_USERNAME];
            printf("Informe o nome do jogador que quer consultar ou *: ");
            scanf("%s", username);
            if (strcmp(username, "*") == 0){
                for (int i = 0; i < users; i++){
                    printf("%d = %s(%d)\n", i+1, usernames[i], score[i]);
                }
                printf("\n \n");
            }
            else {
                int index = search_username(username);
                if (index == -1){
                    printf("Erro: usuário não encontrado");
                } else{
                    printf("Usuário: %s(%d)", username, score[index]);
                } 
            }
        } else if (option == '3') {
            char username[MAX_USERNAME];
            printf("Informe o nome do jogador a ser removido: ");
            scanf("%s", username);
            int index = search_username(username);
            if (index == -1){
                printf("Erro: Usuário não encontrado");
            } else{
                for (int j = index; j+1 < users; j++){
                    strcpy(usernames[j], usernames[j+1]);
                    score[j] = score[j+1];
                }
                users--;
                printf("Jogador removido com sucesso!");
            } 
        } else { //sair 
            break;
        }
    }
}

void tournament_menu(){
    while(1) {
        printf("########################\n");
        printf("####### Torneios #######\n");
        printf("########################\n");
        printf("## Escolha uma opção ###\n");
        printf("########################\n");
        printf("##### [1] Novo #########\n");
        printf("##### [2] Consultar ####\n");
        printf("##### [3] Atualizar ####\n");
        printf("##### [4] Sair #########\n");
        printf("########################\n");
        char option = ' ';
        while(option != '1' && option != '2' && option != '3' && option != '4'){
            option = getchar();
        } 
        if (option == '1'){
            printf("Quantos jogadores jogaram o torneio?");
            scanf("%d", &total_players[tournaments]);
            for (int i = 0; i < total_players[tournaments]; i++){
                printf("Digite o nome do jogador %d: ", i+1);
                char name[MAX_USERNAME];
                scanf("%s", name);
                printf("Digite a pontuação do jogador %d: ", i+1);
                int points;
                scanf("%d", &points);
                update_score(name, points);
                strcpy(tournaments_players[tournaments][i], name);
                tournaments_points[tournaments][i] = points;
            }
            tournaments++;
        } else if (option == '2'){
            if (tournaments == 0){
                printf("Erro: Nenhum torneio cadastrado\n");
            } else {
                printf("Qual o número do seu torneio(1 a %d)?",tournaments);
                int id;
                scanf("%d", &id);
                if (id < 1 || id > tournaments){
                    printf("Erro: Id de torneio inválido\n");
                } else{
                    for (int i = 0; i < total_players[id-1]; i++){
                        printf("%d %s(%d)\n", i+1, tournaments_players[id-1][i], tournaments_points[id-1][i]);
                    }
                }
            }
        } else if (option == '3'){
            if (tournaments == 0){
                printf("Erro: Nenhum torneio cadastrado\n");
            } else {
                printf("Qual o número do torneio que deseja alterar(1 a %d)?",tournaments);
                int id;
                scanf("%d", &id);
                if (id < 1 || id > tournaments){
                    printf("Erro: Id de torneio inválido\n");
                } else{
                    printf("Qual o nome do jogador que deseja alterar a pontuação? ");
                    char name[MAX_USERNAME];
                    scanf("%s", name);
                    int found = 0;
                    for (int i = 0; i < total_players[id-1]; i++){
                        if (strcmp(name, tournaments_players[id-1][i]) == 0){
                            int update_points;
                            printf("Qual a nova pontuação? ");
                            scanf("%d", &update_points);
                            int dif = update_points - tournaments_points[id-1][i];
                            update_score(name, dif);
                            tournaments_points[id-1][i] = update_points;
                            found = 1;
                            break;
                        }
                    }
                    if (found == 0){
                        printf("Erro: jogador não encontrado no torneio\n");
                    } 
                }
            }
        } else {
            break;
        }
    }
}

void ranking_menu(){
    int ids[MAX_USERS];
    for(int i=0; i<users; i++) 
        ids[i]=i;
    for(int i=0; i<users; i++) {
        for(int j=i+1; j<users; j++){
            if(score[ids[j]]>score[ids[i]]){
                int aux = ids[i];
                ids[i] = ids[j];
                ids[j] = aux;
            }
        }
    }

    for(int i=0; i<users; i++){
        printf("%d = %s(%d)\n", i+1, usernames[ids[i]], score[ids[i]]);
    }
}

void main_menu(){
    while(1) {
        printf("########################\n");
        printf("## Sistema de Ranking ##\n");
        printf("########################\n");
        printf("## Escolha uma opção ###\n");
        printf("########################\n");
        printf("##### [1] Jogador ######\n");
        printf("##### [2] Torneio ######\n");
        printf("##### [3] Ranking ######\n");
        printf("##### [4] Sair #########\n");
        printf("########################\n");
        char option = ' ';
        while(option != '1' && option != '2' && option != '3' && option != '4'){
            option = getchar();
        } 
        if (option == '1'){
            player_menu();
        } else if (option == '2'){
            tournament_menu();
        } else if (option == '3') {
            ranking_menu();
        } else {
            printf("Obrigado por usar nosso sistema!\n\n\n");
            break;
        }
    }
}

int main()
{
    main_menu();
    return 0;
}

