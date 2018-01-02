#include"header.h"

extern card CARDS[104],*player[10],*table[4];
extern int score[10];

void print_link(card *link){ //link for link list you want to print

 card *buf=link;
 while(buf!=NULL){
  printf("|%d,%d| ", buf->num, buf->head);
  buf=buf->next;
 };
 printf("\n");

}

card* choose_card(card* link, int n){ //link for a row contain the card chosen, n for the card's position

 int i;

 for(i=1; i<n; i++) link=link->next;
 return link; 

}

int select_row(card* table[], int C, int P){ //table, C for the card chosen, P for the player

 int i,buf=0,entry=-1,last[4]={0};

 for(i=0; i<4; i++){
  card* buf=table[i];
  while(buf->next!=NULL) buf=buf->next;
  last[i]=buf->num;
 };

 for(i=0; i<4; i++)
  if(last[i]<C && last[i]>buf){
   buf=last[i];
   entry=i;
  };

 if(entry>=0) return entry;
 else{
  if(P==0){
   printf("No row can your card insert, please choose a row to eat.(key a number from 1-4.)\n");
   scanf("%d",&entry);}
  else entry=1+rand()%4;
  score[P]+=count_head(&table[entry-1]);
  return entry-1;
 }; 

}

card* insert(card* h, card* new){ //h for the row you want to insert, new for the card inserted

 card* buf=h;

 if(h==NULL){
  return new;
 };

 if(new->num <= h->num){
  new->next=h;
  h->prev=new;
  return new;
 };

 while(buf->next!=NULL && buf->next->num < new->num) buf=buf->next;

 if(buf->next!=NULL){
  buf->next->prev=new;
  new->next=buf->next;
 };
 new->prev=buf;
 buf->next=new;
 return h;

}

card* delete(card** link, int C){

 card* buf=*link;

 while(buf!=NULL && buf->num!=C) buf=buf->next;

 if(buf==NULL) return NULL;
 if(buf->prev==NULL) {
  if(buf->next!=NULL)buf->next->prev=NULL;
  *link=buf->next;
  buf->next=NULL;
  return buf;
 };
 if(buf->next!=NULL) buf->next->prev=buf->prev;
 buf->prev->next=buf->next;
 buf->prev=NULL;
 buf->next=NULL;
 return buf;

}


int count_table(card* link){

 int count=0;

 while(link!=NULL){
  count++;
  link=link->next;
 };

 return count;

}

int count_head(card** link){

 int count=0;
 card* buf=*link;

 do{
  count+=buf->head;
  buf=buf->next;
 }while(buf!=NULL);

 *link=NULL;

 return count;

}
