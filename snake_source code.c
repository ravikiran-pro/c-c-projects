/* for more detail contact proraviki@gmail.com
and advices to optimize the code,prefixing bugs,
adding features are welcome*/
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
const int max_row=22;
const int max_col=30;
typedef struct snake
{
    int row;///collects the y coordinates
    int col;///collects the x coordinates
}snake;
snake move[101],food;
int size=3;
int score=0;
void start_game();///displays the border and loads the game
void start_snake();///print the base snake
void create_food(char);///generates food
void snake_movement(char,int);///logic of the game
void sort_data();///to keep track of the coordinates of snake
void check_validmove(); ///check whether snake its wall or itself
void print_score(int score); ///generates and prints score
void increase_snake(char); ///snake length increase while catching special food
void start_memo() ///instructions and rules of the game
{
    FILE *file;
    char ch;
    file=fopen("startup.txt","r");
    while(ch!=EOF)
    {
        ch=fgetc(file);
        printf("%c",ch);
    }
    ch=getchar();
    if(ch=='n')
    {
        exit(0);
    }
    fclose(file);
}
void gotoxy(int col,int row,char ch)///setting cursor control position
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position={col,row};
    SetConsoleCursorPosition(h,position);
    printf("%c",ch);
}
void clrscr()
{
    system("cls");
}
void end_game()
{
            char ch;
            int high_score=0;
            clrscr();
            printf("\n\n\n\t\tgame over\n\t\tbetter luck next time\a");
            clrscr();
            FILE *file;
            file=fopen("score.txt","r");
            while((ch=fgetc(file))!=EOF)
            {
                high_score*=10;
                high_score+=ch-48;
            }
            fclose(file);
            if(high_score<score) ///collects high score and compare it with current
            {
                printf("\n\n\t\tHIGH  SCORE %d",score);
                file=fopen("score.txt","w");
                fprintf(file,"%d",score);
            }
            fclose(file);
            Sleep(1000);
            clrscr();
            exit(0);
}
int main()
{
    start_memo();
    start_game();
    start_snake();
    create_food('X');
    snake_movement(RIGHT,120);
}

void start_game()
{
    int i,j;
    clrscr();
    gotoxy(max_col/2,max_row/2,' ');
    printf("loading|||");
    for(i=0;i<10;i++)
    {
        Sleep(400);
        printf("%c",177);
    }
    clrscr();
   char ch;
   for(i=0;i<max_row;i++)
    {
      for(j=0;j<max_col;j++)
      {
          if(i==0 || i==max_row-1) printf("~");
          else printf(" ");
      }
       printf("~\n~");
    }
}
void start_snake() ///prints the base snake of size 3
{
    int i;
    move[0].row=1;
    move[0].col=1;
    for(i=1;i<=size;i++)
    {
        move[i].col=i+1;
        move[i].row=move[0].row;
        gotoxy(move[i].col,move[i].row,'0');
    }
}
void create_food(char ch)
{
    food.col=rand()%max_col;
    food.row=rand()%max_row;
    if(food.row<2 || food.row>max_row-2 || food.col<2 || food.col>max_col-2) create_food(ch);///generating within map
    {
        int i;
        for(i=0;i<=size;i++)
        {
            if(move[i].row==food.row && move[i].col==food.col)
                create_food(ch);
        }
        gotoxy(food.col,food.row,ch);
    }
}
void snake_movement(char ch,int speed)
{
            while(!_kbhit()) ///key handling ..until no key pressed
        {
            Sleep(speed);
            sort_data();    ///keep tracking of snake coordinates continuosly;
            gotoxy(move[0].col,move[0].row,' ');
            if(ch==LEFT)
            {
                move[size].col-=1;
            }
            if(ch==RIGHT)
            {
                move[size].col+=1;
            }
            if(ch==UP)
            {
                move[size].row-=1;
            }
            if(ch==DOWN)
            {
                move[size].row+=1;
            }gotoxy(move[size].col,move[size].row,'0');
        check_validmove();  ///check the snake head inside wall and not touching its body
        if(move[size].row==food.row && move[size].col==food.col)
        {
            static int food_count=0;
            print_score(score+=3);
                if(food_count==2)
                {
                    create_food('$'); ///special food for 3 individual count
                    food_count++;
                    continue;
                }
                if(food_count==3)
                {
                    print_score(score+=10);
                    speed-=0.5; ///increasing snake speed when catches special food
                    increase_snake(ch);
                    food_count=0;
                }
           create_food('X');
           food_count++;
        }
        }
        ch=_getch();
        snake_movement(ch,speed);
}
void sort_data()
{
    int i;
    for(i=0;i<size;i++)
    {
        move[i]=move[i+1];
        gotoxy(move[i].col,move[i].row,'0');
    }
}
void check_validmove()
{
    int i;
    for(i=0;i<size-1;i++)
    {
        if(move[size].row==move[i].row && move[size].col==move[i].col)
        end_game();
    }
    if(move[size].col==0||move[size].col==max_col+1||move[size].row==0||move[size].row==max_row-1)
        {
            end_game();
        }
}
void print_score(int score)
{
    gotoxy(0,max_row+1,' ');
    printf("$$\t\tscore=%d\n",score);
}
void increase_snake(char ch) ///increasing snake length by size 2
{
            if(size==100)
            {
                printf("winner\a\a");
                Sleep(5000);
                exit(0);
            }
            move[size+2]=move[size+1]=move[size];
            if(ch==LEFT)
            {
                move[size+1].col-=1;
                move[size+2].col-=2;
            }
            if(ch==RIGHT)
            {
                move[size+1].col+=1;
                move[size+2].col+=2;
            }
            if(ch==UP)
            {
                move[size+1].row-=1;
                move[size+2].row-=2;
            }
            if(ch==DOWN)
            {
                move[size+1].row+=1;
                move[size+1].row+=2;
            }
            size+=2;
}
