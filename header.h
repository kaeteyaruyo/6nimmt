#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct card {struct card* prev; int num; int head; struct card* next;} card;

void print_table(int n); //print the cards on table and player's hand
void print_link(card *link); //print a row of card(used in print_table)
void deal_card(int n); //deal cards
card* insert(card* h, card* new); //insert a card into a row
card* choose_card(card* link, int n); //choose which card to play
card* delete(card** link, int C); //delete a card from a row
void play(int n); //play a card(choose-delete from hand-insert to table)
int select_row(card* table[], int C, int P); //select which row to insert
int count_table(card* link); //to see if a row has been filled
int count_head(card** link); //to count heads and clear a row
