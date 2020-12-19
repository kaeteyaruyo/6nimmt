
#ifndef _CARD_C_
#define _CARD_C_

#include <stdio.h>
#include <stdlib.h>

typedef struct Card_Node{
   int index;  
   int num;
   struct Card_Node * next;
}Card_Node;

void Init_Card_Node(Card_Node* node){
  node->index=-1; 
  node->num=0;
  node->next = NULL;
}

void Setup_Card_Node(Card_Node* node, int number){
    node->num=number;
}

typedef struct Card{
    Card_Node* head;
    Card_Node* tail;
}Card;

void Init_Card(Card* card){
    card->head=NULL;
    card->tail=NULL;
}

void AddCard(Card* card, int number){
    Card_Node* tmp=(Card_Node*)malloc(sizeof(Card_Node));
    Init_Card_Node(tmp); 
    Setup_Card_Node(tmp, number);

    if(card->head==NULL){
       card->head=tmp;
       card->tail=tmp;
       return;
    }
    Card_Node* cur=card->head, *pre=NULL;
    while(cur!=NULL && cur->num < tmp->num){
        pre=cur;
        cur=cur->next;
    }
    if(cur==NULL){
        card->tail->next = tmp;
        card->tail=tmp;
        return;
    }
    if(pre==NULL){
      tmp->next=card->head;
      card->head=tmp;
       return;
    }
    tmp->next=cur;
    pre->next=tmp;

}

int PopCard(Card* card){
    if(card->head==NULL)
      return -1;
    if(card->head==card->tail)
      card->tail=NULL;   
    Card_Node* tmp=card->head;
    int num=tmp->num;
    card->head=card->head->next;
    free(tmp);
    return num;
}

void Prinf_Card(Card* card){
    Card_Node* tmp=card->head;
    while(tmp!=NULL){
        printf("%d ", tmp->num);
        tmp=tmp->next;
    }
}


/* for wait cards */
void AddCard_With_index(Card* card, int number, int index){
    Card_Node* tmp=(Card_Node*)malloc(sizeof(Card_Node));
    Init_Card_Node(tmp); 
    Setup_Card_Node(tmp, number);
    tmp->index=index;

    if(card->head==NULL){
       card->head=tmp;
       card->tail=tmp;
       return;
    }
    Card_Node* cur=card->head, *pre=NULL;
    while(cur!=NULL && cur->num < tmp->num){
        pre=cur;
        cur=cur->next;
    }
    if(cur==NULL){
        card->tail->next = tmp;
        card->tail=tmp;
        return;
    }
    if(pre==NULL){
      tmp->next=card->head;
      card->head=tmp;
       return;
    }
    tmp->next=cur;
    pre->next=tmp;

}

int Get_Head_Number(Card* card){
    if(card->head==NULL)
      return -1;  
    return card->head->num;
}

int Get_Head_index(Card* card){
    if(card->head==NULL)
      return -1;  
    return card->head->index;
}

#endif