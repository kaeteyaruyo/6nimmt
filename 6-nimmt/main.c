#include <stdio.h>
#include <stdlib.h>

#include "Player.c"
#include "Computer.c"
#include "Table.c"

int cards[104]={0};

int main(){
    Player *player;
    Computer* computer[3];
    Table* table;
    Card* wait;


/*--  Init Part --*/
    // -- 1. malloc 
    player=(Player*) malloc (sizeof(Player)) ;
    for(int i=0;i<3;++i)
       computer[i]=(Computer*) malloc (sizeof(Computer));
    table=(Table*)malloc (sizeof(Table)) ; 
    wait=(Card*) malloc (sizeof(Card));

    // -- 2. init  
    Init_Player(player);
    for(int i=0;i<3;++i)
       Init_Computer(computer[i]);
    Init_Table(table);  
    Init_Card(wait);

    // -- 3. send card
    int n=0, tmp=0;
    while (n<10){
        tmp=rand()%104;
        if(cards[tmp]==0){
            cards[tmp]=1;
            Add_Player_Card(player, tmp+1);
            n++;
        }
    }
    for(int i=0;i<3;++i){
        n=0;
        while(n<10){
            tmp=rand()%104;
            if(cards[tmp]==0){
               cards[tmp]=1;
               Add_Computer_Card(computer[i], tmp+1);
               n++;
            }
        }
    }
    int num[4]={0};
    n=0;
    while(n<4){
        tmp=rand()%104;
        if(cards[tmp]==0){
           cards[tmp]=1;
           num[n++]=tmp+1;
        }
    }
    Set_Table(table, num);

/* -- Game Start -- */
    for(int i=0;i<10;++i){
        printf("/-----------------------------------------------------/\n");
        printf("/--------------------    Round %d    ------------------/\n",i+1);
        printf("/-----------------------------------------------------/\n");
        // -- 1. printf all info for user
        printf("*-----  Cards on table : \n");
        Print_Table(table);
        printf("*------------------------\n");
        Print_Player_Card(player);

         /*  for debug -- show cards in computer.
         printf("Computer : \n");
         for(int i=0;i<3;++i){
            printf("%d : ",i);
            Printf_Computer_Card(computer[i]);
            printf("\n");
          }
          */

        //-- 2. ask user to select cards 
        AddCard_With_index( wait,Select_Player_Card(player),0);
        for(int i=0;i<3;++i){
            AddCard_With_index(wait, Select_Computer_Card(computer[i]), i+1);
        }

        printf("Cards form other Players : ");
        Prinf_Card(wait);
        printf("\n");
        
        //-- 3. Start add cards to table  
        for(int i=0;i<4;++i){
            int tmp=Get_Head_Number(wait);
            int index=Get_Head_index(wait);
            PopCard(wait);
            int number=Add_Card_To_Table(table, tmp);
            if(number>0){
                if(index==0)
                  Add_Player_Score(player, number);
                else 
                  Add_Computer_Score(computer[index-1],number);  
            }
            else if(number == -1){
                if(index==0){
                    int x=0;
                    printf("Choise a  row (1-4): ");
                    scanf("%d",&x);
                    while(x<1||x>4){
                        printf("Wrong Choise !! , Please choise again :");
                        scanf("%d",&x);
                    }
                    Add_Player_Score(player, Reset_Card_On_Table(table, x-1, tmp));
                }
                else{
                    int x=rand()%4;
                    Add_Computer_Score(computer[index-1],Reset_Card_On_Table(table, x, tmp));
                }
            }
        }
        printf("\n");
    }  

    // -- 4. ending  
    printf("/-----------------------------------------------------/\n");
    printf("/--------------------    Game End   ------------------/\n");
    printf("/-----------------------------------------------------/\n");
    printf("Your Score : %d\n",player->score);
    for(int i=0;i<3;++i) 
     printf("Computer  %d Score : %d\n",i,computer[i]->score);

    return 0;
}