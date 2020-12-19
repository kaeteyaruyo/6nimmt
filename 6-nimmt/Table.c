#include <stdio.h>
#include <stdlib.h>
#include "Card.c"
# define NUM 4 

int Card_Filled(Card* card){
      Card_Node*  cur=card->head;
      int n=0;
      while (cur!=NULL){
             n++;
             cur=cur->next;
      }
      if(n>=6)
        return 1;
      return 0;  
}

int Sum_Card(Card* card){
     int sum=0;
     for(int i=0;i<5;++i)
        sum+=PopCard(card);
     return sum;
}

typedef struct Table{
    Card* card[NUM];
}Table;

void Init_Table(Table* table){
     //printf("init Table\n");
     for(int i=0;i<4;++i){
       table->card[i]=(Card*) malloc(sizeof(Card));  
       Init_Card(table->card[i]);
     }
}

void Set_Table(Table* table,int * num){
    for(int i=0;i<NUM;++i)
       AddCard(table->card[i], num[i]); 
}

int Add_Card_To_Table(Table* table,int num){
    int pointer=-1;
    int diffence=-1;
    for(int i=0;i<NUM;++i){
        if(table->card[i]->tail->num < num){
            if(diffence==-1){
                   diffence=num- table->card[i]->tail->num;
                   pointer=i;
            }
            if(diffence > num- table->card[i]->tail->num){
                pointer=i;
                diffence=num- table->card[i]->tail->num;
            }
        }
    }

    if(pointer==-1){
        return -1;
    }
    AddCard(table->card[pointer], num);
    if(Card_Filled(table->card[pointer])){
         return Sum_Card(table->card[pointer]);
    }
    return 0;
}

int Reset_Card_On_Table(Table* table, int index, int num){
    int tmp=PopCard(table->card[index]) , sum=0;
    while(tmp!=-1){
        sum+=tmp;
        tmp=PopCard(table->card[index]);
    }
    AddCard(table->card[index],num) ;
    return sum;   
} 

void Print_Table(Table* table){
    for(int i=0;i<NUM;++i){
        printf("*-- ");
        Prinf_Card(table->card[i]);
        printf("\n");
    }
}