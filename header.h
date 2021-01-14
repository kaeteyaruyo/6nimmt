#include <stdio.h>
#include <stdlib.h>
# define NUM 4 

/* ----- Card ----- */
typedef struct Card_Node{
   int index;  
   int num;
   struct Card_Node * next;
}Card_Node;

typedef struct Card{
    Card_Node* head;
    Card_Node* tail;
}Card;

void Setup_Card_Node(Card_Node* , int);
void Init_Card_Node(Card_Node*);
void Init_Card(Card* );
void AddCard(Card* , int );
int  PopCard(Card* );
void Prinf_Card(Card*);
void AddCard_With_index(Card* , int , int );
int  Get_Head_Number(Card* );
int  Get_Head_index(Card* );


/* ----- Computer ----- */
typedef struct Computer{
     Card* card;
    int score;
}Computer;

void Init_Computer(Computer* );
void Add_Computer_Card(Computer* ,int );
int  Select_Computer_Card(Computer* );
void Add_Computer_Score(Computer* , int );
void Printf_Computer_Card(Computer* );


/* ----- Player ----- */
void DeleteCard(Card* , int );
Card_Node* SearchCard(Card* , int );
int  SelectCard(Card* , int );

typedef struct Player{
    Card* card;
    int score;
}Player;

void Init_Player(Player* );
void Add_Player_Card(Player* , int);
void Print_Player_Card(Player* );
int  Select_Player_Card(Player* );
void Add_Player_Score(Player* , int );

/* ----- Table ----- */

int Card_Filled(Card* );
int Sum_Card(Card* );

typedef struct Table{
    Card* card[NUM];
}Table;

void Init_Table(Table* );
void Set_Table(Table* ,int *);
int  Add_Card_To_Table(Table* ,int );
int  Reset_Card_On_Table(Table* , int , int );
void Print_Table(Table* );