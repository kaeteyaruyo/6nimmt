#include "header.h"

/* -------- Card -------- */
void Init_Card(Card* card){
    card->head=NULL;
    card->tail=NULL;
}

void Init_Card_Node(Card_Node* node){
  node->index=-1; 
  node->num=0;
  node->next = NULL;
}

void Setup_Card_Node(Card_Node* node, int number){
    node->num=number;
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


/* --- Computer --- */

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


/* ---------- Player ---------- */
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


/* ---------- Table ---------- */

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