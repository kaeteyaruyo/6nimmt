#include <stdio.h>
#include <stdlib.h>
#include  "Card.c"

typedef struct Computer{
     Card* card;
    int score;
}Computer;

void Init_Computer(Computer* computer){
      if(computer==NULL)
        return;
      //printf("Init Computer\n");
      computer->card=(Card*)malloc(sizeof(Card));
      Init_Card(computer->card);
      computer->score=0;
}

void Add_Computer_Card(Computer* computer,int number){
    AddCard(computer->card, number);
}

int  Select_Computer_Card(Computer* computer){
    return PopCard(computer->card);
}

void Add_Computer_Score(Computer* compuer, int number){
     compuer->score+=number;
}

void Printf_Computer_Card(Computer* computer){
    Prinf_Card(computer->card); 
    printf("score : %d.",computer->score);
}