#include <stdio.h>
#include <stdlib.h>
#include "Card.c"

void DeleteCard(Card* card, int number){
    Card_Node* cur=card->head, *pre=NULL;
     while(cur!=NULL && cur->num!=number){
        pre=cur;
        cur=cur->next;
    }
    if(cur==NULL)
     return;
    if(cur==card->head)
     {
         PopCard(card);
         return;
     }   
    pre->next=cur->next;
    free(cur);  
}

Card_Node* SearchCard(Card* card, int number){
    Card_Node* tmp=card->head;
    while(tmp!=NULL){
        if(tmp->num==number)
          return tmp;
        tmp=tmp->next; 
    }
  return NULL;
}

int SelectCard(Card* card, int number){
  Card_Node* tmp=SearchCard(card, number);
  if(tmp==NULL)
     return -1;
   DeleteCard(card, number);
  return number;
}

typedef struct Player{
    Card* card;
    int score;
}Player;

void  Init_Player(Player* player){
     player->card=(Card*)malloc(sizeof(Card));
     Init_Card(player->card);
     player->score=0;
}

void Add_Player_Card(Player* player, int num){
    AddCard(player->card,num);
}

void Print_Player_Card(Player* player){
    printf("Your Turn !!\nThere is your cards : ");
    Prinf_Card(player->card);
    printf("\n"); 
    printf("There is your score : %d\n",player->score);
}

int Select_Player_Card(Player* player){
    int tmp=0;
    printf("Your choise : ");
    scanf("%d",&tmp);
    int n=SelectCard(player->card, tmp);
    if(n==-1)
    {
        printf("Worng Choise , Pleae Choise again . \n");
        return Select_Player_Card(player);
    }
    return n;
}

void Add_Player_Score(Player* player, int add_score){
    player->score+=add_score;
}
