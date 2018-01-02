#include "header.h"

card CARDS[104]={{NULL,1,1,NULL},{NULL,2,1,NULL},{NULL,3,1,NULL},{NULL,4,1,NULL},{NULL,5,2,NULL},{NULL,6,1,NULL},{NULL,7,1,NULL},{NULL,8,1,NULL},{NULL,9,1,NULL},{NULL,10,3,NULL},
{NULL,11,5,NULL},{NULL,12,1,NULL},{NULL,13,1,NULL},{NULL,14,1,NULL},{NULL,15,2,NULL},{NULL,16,1,NULL},{NULL,17,1,NULL},{NULL,18,1,NULL},{NULL,19,1,NULL},{NULL,20,3,NULL},
{NULL,21,1,NULL},{NULL,22,5,NULL},{NULL,23,1,NULL},{NULL,24,1,NULL},{NULL,25,2,NULL},{NULL,26,1,NULL},{NULL,27,1,NULL},{NULL,28,1,NULL},{NULL,29,1,NULL},{NULL,30,3,NULL},
{NULL,31,1,NULL},{NULL,32,1,NULL},{NULL,33,5,NULL},{NULL,34,1,NULL},{NULL,35,2,NULL},{NULL,36,1,NULL},{NULL,37,1,NULL},{NULL,38,1,NULL},{NULL,39,1,NULL},{NULL,40,3,NULL},
{NULL,41,1,NULL},{NULL,42,1,NULL},{NULL,43,1,NULL},{NULL,44,5,NULL},{NULL,45,2,NULL},{NULL,46,1,NULL},{NULL,47,1,NULL},{NULL,48,1,NULL},{NULL,49,1,NULL},{NULL,50,3,NULL},
{NULL,51,1,NULL},{NULL,52,1,NULL},{NULL,53,1,NULL},{NULL,54,1,NULL},{NULL,55,7,NULL},{NULL,56,1,NULL},{NULL,57,1,NULL},{NULL,58,1,NULL},{NULL,59,1,NULL},{NULL,60,3,NULL},
{NULL,61,1,NULL},{NULL,62,1,NULL},{NULL,63,1,NULL},{NULL,64,1,NULL},{NULL,65,2,NULL},{NULL,66,5,NULL},{NULL,67,1,NULL},{NULL,68,1,NULL},{NULL,69,1,NULL},{NULL,70,3,NULL},
{NULL,71,1,NULL},{NULL,72,1,NULL},{NULL,73,1,NULL},{NULL,74,1,NULL},{NULL,75,2,NULL},{NULL,76,1,NULL},{NULL,77,5,NULL},{NULL,78,1,NULL},{NULL,79,1,NULL},{NULL,80,3,NULL},
{NULL,81,1,NULL},{NULL,82,1,NULL},{NULL,83,1,NULL},{NULL,84,1,NULL},{NULL,85,2,NULL},{NULL,86,1,NULL},{NULL,87,1,NULL},{NULL,88,5,NULL},{NULL,89,1,NULL},{NULL,90,3,NULL},
{NULL,91,1,NULL},{NULL,92,1,NULL},{NULL,93,1,NULL},{NULL,94,1,NULL},{NULL,95,2,NULL},{NULL,96,1,NULL},{NULL,97,1,NULL},{NULL,98,1,NULL},{NULL,99,5,NULL},{NULL,100,3,NULL},
{NULL,101,1,NULL},{NULL,102,1,NULL},{NULL,103,1,NULL},{NULL,104,1,NULL}};

card *player[10]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}; 
int score[10]={0};
card *table[4]={NULL,NULL,NULL,NULL};

int main(int argc, char *argv[]){

 int people=atoi(argv[1]),rank[people],i,j,k=0;

 deal_card(people);
 print_table(people);
 play(people);
 for(i=0; i<170; i++){
  for(j=0; j<people; j++) if(score[j]==i) { rank[k]=j; k++; };
  if(k==people) break;
 };

 printf("winner: player %d\n", rank[0]+1);
 for(i=0; i<people; i++) if(rank[i]==0) printf("your rank: %d\n", i+1);
 if(rank[0]==0) printf("You win!\n");

 return 0;

}

void deal_card(int n){ //n for number of player

 int t,i,j;
 card buf;
 srand(time(NULL));

 for(t=0; t<100000; t++){
  i=rand()%104;
  j=rand()%104;
  buf=CARDS[i];
  CARDS[i]=CARDS[j];
  CARDS[j]=buf;
 };

 i=0; j=10;
 for(t=0; t<n; t++){
  for(i; i<j; i++){ player[t]=insert(player[t],&CARDS[i]); };
 j+=10; 
 };

 for(t=0; t<4; t++, i++){
  table[t]=insert(table[t],&CARDS[i]);
 };

}

void print_table(int n){ //n for number of player

 int i;

 printf("\nSCORE BOARD |");
 for(i=0; i<n; i++) printf(" %d |", score[i]);
 printf("\n");
 for(i=0; i<4; i++) print_link(table[i]);
 printf("\n");
// print_link(player[0]);

}

void play(int n){

 int i;

 for(i=0; i<10; i++){

  int j,k=1,l,C,p[n],cards[n],heads[n];

  printf("\n");
  print_link(player[0]);
  printf("Choose a card.(key a number from 1-%d.)\n", 10-i); //player choose card
  scanf("%d",&C);
  card* c=choose_card(player[0],C);
  cards[0]=c->num;
  heads[0]=c->head;

  for(j=1; j<n; j++){ //PC choose card
   C=1+rand()%(10-i);
   card* c=choose_card(player[j],C);
   cards[j]=c->num;
   heads[j]=c->head;
  };

  j=0; //decide players' priority
  for(k; k<105; k++){
   for(l=0; l<n; l++) if(cards[l]==k){ p[j]=l; j++; break; };
   if(j==n) break;
  };

  printf("\n\ncard:     "); //print information
  for(j=0; j<n; j++) printf(" |%d,%d|",cards[j], heads[j]);
  printf("\nIn order: ");
  for(j=0; j<n; j++) { int k=p[j]; printf(" |%d,%d|",cards[k], heads[k]); };
  printf("\n");

  for(j=0; j<n; j++){ //put cards onto table
   int t,a;
   a=p[j];
   t=select_row(table,cards[a],a);
   if(count_table(table[t])==5) score[a]+=count_head(&table[t]);
   card* buf=delete(&player[a],cards[a]);
   table[t]=insert(table[t],buf);
  print_table(n);
  };

 };

}
