/*
################## TODO ##################
1) mat vals...
    1    snake
    2    wall
    3    bounty
    -1   free space
2)

w         H                        //exchange 
s         P
a         K
d         M
###########################################
*/

#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<graphics.h>
#include<string.h>

#ifdef WIN32
#include <windows.h>


int headx=0,heady=0;
void cleardevice(){
    // system("cls");
}
void moveto(int x, int y)
{
  COORD cur = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}
#else
void gotoxy(int x, int y)
{
  printf("\033[%dG\033[%dd", x+1, y+1);
}
#endif


void setColor(unsigned short color){
     HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(a,color);
}

using namespace std;

const int boardx=41;
const int boardy=41;
const int begx=0;
const int begy=0;
const int endx=40;
const int endy=40;
int points=0;

class snake
    {
           int snakemat[boardx][boardy];
           int snake_size;
           struct node
                {     
                      node *next;
                      node *prev;
                      int x,y;                      //x an y in coord terms...
                }*start;                            //when use in mat...interchange
           
           public:
                  
    snake()
       {
           start=NULL;
           int i,j;
           for(i=0;i<=40;i++)
                         for(j=0;j<=40;j++)
                              snakemat[i][j]==-1;
                              
       }   //end constructor
            
    void board()
        {
          int i,j;
          
          i=0;
             for(j=0;j<=40;j++)
                 {
                  snakemat[j][i]=2;
                               }
                               
          i=40;
          for(j=0;j<=40;j++)
                 {
                        snakemat[j][i]=2;
                        
                               }
          
          j=0;
            for(i=0;i<=40;i++)
                 {
                      snakemat[j][i]=2;
                               
                               }
                                         
          
          j=40;
            for(i=0;i<40;i++)
                 {
                    snakemat[j][i]=2;
                               
                               }
                                               
                            
           }         //end board
           
           void init()
           {
                int i,j;
                 for(i=begx+1;i<=endx-1;i++)
                         for(j=begy+1;j<=endy-1;j++)
                              {
                                                snakemat[i][j]=-1;
                                                }
                
                
                }
           
           
    void board_gen()
          {
                     int i,j;
                     char l;
                     
                     for(i=begx;i<=endx;i++)
                         for(j=begy;j<=endy;j++)
                              {
                              if(snakemat[i][j]==2)
                                 {
                                                   //wall
                                 moveto(j,i);
                                setColor(12);
                                  l=177;
                                cout<<l;
                                
                                 }
                               if(snakemat[i][j]==3)
                                 {
                                 moveto(j,i);
                                setColor(11);
                                 l=2;
                                cout<<l;
                                 }
                                if(snakemat[i][j]==1)
                                {moveto(j,i);
                               setColor(7);
                                   l=219;
                                cout<<l;
                                }  
                                 if(snakemat[i][j]==-1)
                                {moveto(j,i);
                               setColor(5);
                                   l=219;
                                cout<<l;
                                } 
                                           
                              
                              }  
                     
                     
               }            //end board_gen()
           
        
        
    void bounty_locator()
         {
                         
          int i,j;
            static int varx=2;
            static int vary=1;
     
               int jgx=varx;
               int jgy=vary;
               snakemat[jgy][jgx]=-1;
      upb:
           varx=rand();
              varx=varx%40;
           vary=rand();               //SOLVED!!!gens same start...solve prob..temp soln in main comnt   :D
              vary=vary%40;
              
                         
           if((snakemat[vary][varx]!=1)&&(snakemat[vary][varx]!=2))
                       snakemat[vary][varx]=3;
            else
              goto upb;
           
         }
        
        void isnake()
              {
                     node *p=new node;
                     p->next=NULL;
                     p->prev=NULL;        
                     p->x=1;                    
                     p->y=4;
                     start=p;
                     
           snakemat[p->y][p->x]=1;              
           
           
                     }        
    
         void score()
             {
                     points+=10;
             }
             
         int wall_hit(int shx,int shy)                        //WALLHIT AND BOUNTY HIT CALLED EVERY TIME SNAKY MOVES... 
             {                     
                                                //CHECKING CONDITIONS ALL PLACED IN HIT FUNCS..    :p
                if((snakemat[shy][shx]==2)||(snakemat[shy][shx]==1))
                        {
                           return 1;
                           }
                      else
                        return 0;                     
             }

     void eras()
         {
                int i,j;
             for(i=1;i<40;i++)
                 for(j=1;j<40;j++)
                      {
                         moveto(i,j);
                        // cout<<"\0";
                      }
         moveto(0,0);
         }
             
             void movesetter(int tx,int ty,char c)
                   {      int ptx,pty;
                          ptx=tx;






                          pty=ty;
                          int ntx,nty;       
                     node *p;
                     p=start;
                     
                     if(bounty_hit(tx,ty))
                        {
                            bounty_locator();
                            score();
                            stretch_snake(tx,ty);
                            
                            switch(c)
                            {
                                  case 'H':
                                 movesetter(tx,ty-1,c);
                                    break;
                                 case 'K':
                                 movesetter(tx-1,ty,c);
                                    break;
                                 case 'P':
                                 movesetter(tx,ty+1,c);
                                    break;
                                 case 'M':
                                 movesetter(tx+1,ty,c);
                                    break;
                                          
                            }         
                     
                        }                    
 
                else if(wall_hit(tx,ty))
                         {  
                                         int i=2;
                            
                         while(i>=0)
                            {
                            Sleep(200);
                            //system("cls");
                            system("cls");
                          //  eras();
                            Sleep(200);
                            board_gen();
 
                            i--;
                            
                            }
                           // getch();
                           // cleardevice();
                            //eras();
                            moveto(0,0);
                            display();
                            getch();
                            exit(0);
                         }                                
                     
                     snakemat[pty][ptx]=1;
                     while(p->next!=NULL)
                        {
                          ntx=p->x;
                          nty=p->y;
                          p->x=ptx;
                          p->y=pty;
                          ptx=ntx;
                          pty=nty;
                          p=p->next;                          
                        }
                        
                          ntx=p->x;
                          nty=p->y;
                          p->x=ptx;
                          p->y=pty;
                          snakemat[p->y][p->x]=1;
                         
                              
                       
                       snakemat[nty][ntx]=-1;
                       
                       
                       }                                                                                
             
    void snake_control(char ch)
          {             
                        /* y++ = go down , y-- = go up , x++ = go right , x-- =go left*/
                         ////////////////////////////////////////////////////////////////////
          static int bcount=0;
          char pch=ch;
                         
          int x,y;
          node *p;
          system("cls");
          while(1){
          moveto(45,45);
                  cout<<"Press END to exit";
                  
         moveto(0,0);
         
         if(bcount%90==0)
            {
               bounty_locator();
               
            }
            bcount++;
         
                     if(kbhit())
                        {ch=getch();}
                     switch(ch)
                        {
                               case 'H':
                                    
                                    p=start;
                                    heady=y=p->y;
                                    headx=x=p->x;
                                    y--;
                                    movesetter(x,y,ch);
                                    
                                    cleardevice();
                                   // eras();
                                    board_gen();
                                    
                                    break;
                                    
                               case 'K':
                                    
                                    
                                    p=start;
                                 
                                    heady=y=p->y;
                                    headx=x=p->x;
                                    x--;
                                    movesetter(x,y,ch);
          
                                    cleardevice();
                                    //eras();
                                    board_gen();

                                    
                                    break;
                                    
                               case 'P':
                                    
                                    p=start;
                               
                                    heady=y=p->y;
                                    headx=x=p->x;
                                    y++;
                                    movesetter(x,y,ch);
                
                                    cleardevice();         
                                    //eras();
                                    board_gen();
   
                                    
                                    
                                    
                                    break;
                                    
                               case 'M':
                                    
                                    p=start;
                                
                                    heady=y=p->y;
                                    headx=x=p->x;
                                    x++;
                                    movesetter(x,y,ch);
   
                                    cleardevice();
                                    //eras();
                                    board_gen();
   
                                    break;
                       
                                case 79:
                                       cleardevice();
                                       //eras();
                                       display();
                                       getch();
                                       exit(0);
                                                     
                               default:
                                      ch=pch;    
                                       
                                       }
                        
                        //Sleep(100);
                        }//snake_control(ch);
                        
                        
                        //////////////////////////////////////////////////////////
          }
          
    int bounty_hit(int shx,int shy)          //shx an shy are coords
          {
                    
                     if(snakemat[shy][shx]==3)
                        {
                        
                       system("notify.wav");
                      // system("ac.mp3");
                        return 1;
                        }
                           
                     else
                        return 0;
                     
          }
          
          void stretch_snake(int bx,int by)
               {
                      node *p=new node;
                    //  node *r;            //bx an by are coord val inputs
                      p->next=start;
                      p->prev=NULL;//was start->next 
                      p->x=bx;
                      p->y=by;
                      start=p;
               
                    //  r=p->next;
                      snakemat[by][bx]=1;
               
               }
           
            void temp_stretch(int bx,int by)
             {
              node *p=new node;
              p->x=bx;
              p->y=by;
              p->next=NULL;
//              node *r=start;
                          
              node *r=start;
                while(r->next!=NULL)            
                   r=r->next;
             r->next=p;
             p->prev=r;
              snakemat[p->y][p->x]=1;  
             }          
                                
    void logo_gen()
        {
                   int i;
 
    for(i=60;i>=10;i=i-5)
      {     
            cleardevice();
            system("cls");
      moveto(0,i);
               
      cout<<"                    ##########                    &&&&&&                                 \n"              
            "                    ##        ##                &&      &&&&                             \n"
            "                    ##          ##             &&           &&                           \n"    
            "                    ##           ***          &&              &                          \n"
            "                    ##        *********       &&               &                         \n"
            "                    ##      **        **     &&                                          \n"
            "                    ##     **   ##    **     &&                                          \n"  
            "                    ##     *  ##      **     &&                                          \n"     
            "                    ###########     **       &&&                                         \n"
            "                    ##             **          &&&           &&&&&&&                     \n"        
            "                    ##           **             &&            &                          \n"     
            "                    ##          **                 &&          &&                        \n"      
            "                    ##        **                     &&      &&                          \n"       
            "                    ##       **                       &&&&&&&&                           \n"                       
            "                    ##     *********************************************                 \n"
            "                           *********************************************                 \n";
        
            moveto(0,0);
            Sleep(50);
            
            }
            system("intro.wav");
            Sleep(300);
                       
        }
        
    void display()
          { 
                  system("cls");
                   
                     if (points<30)
                 cout<<"\n\n\n\n :P  !! u scored : "<<points;
                  else if(points<50)    
                     cout<<"\n\n\n\n :D !! u scored : "<<points;
                  else if(points<80)
                      cout<<"\n\n\n\n :) !! u scored : "<<points;
                   else if(points<130)
                         cout<<"\n\n\n\n :| !! u scored : "<<points;
                  else if(points<200)
                          cout<<"\n\n\n\n :S!! u scored : "<<points;
                  else if(points>200)
                          cout<<"\n\n\n\n :O !! u scored : "<<points;  
                    
                         setColor(15);            
                     getch();
                         
          }
          
}fangs;

main()
{
      setColor(10);
          int i,lnum=5,var;
        char c='s';              
              cleardevice();
              
              fangs.logo_gen();
              system("cls");
      cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\tEnter a number  (0<num<100) :  ";
      cin>>lnum;
      
      for(i=0;i<lnum;i++)
           var=rand();
       
       cleardevice();
     
     fangs.init();      
      fangs.board();
      fangs.board_gen(); 
      fangs.isnake();               
      fangs.temp_stretch(1,3);
      fangs.temp_stretch(1,2);        
      fangs.temp_stretch(1,1);
      fangs.snake_control('v');
      
      getch();      
}
