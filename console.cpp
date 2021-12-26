#include<iostream>
#include<windows.h>
#include <time.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
#define N 4
bool LossCondition(int maingrid[N][N]);
int twopower(int n);
void print2048(int maingrid[N][N],long int playerscore);
void SetColor(int colourno);
void combineElements(int maingrid[N][N],int input,long int &playerscore);
void moveElements(int maingrid[N][N],int input,int &flagchange);
void placeNewNumber(int maingrid[N][N]);
void gotoxy(int x, int y);
int GetRandomNumber(int n);



int main()
{
    srand(time(0));
    int maingrid[N][N]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    long int playerscore=0;
    int input,flagchange;

    placeNewNumber(maingrid);
    placeNewNumber(maingrid);
    print2048(maingrid,playerscore);
    while(!LossCondition(maingrid))
    {
        //cout<<"Next move?(1left 2down 3right 4up):";
        flagchange=0;
        getch();
        if (kbhit())
        {
            char ch = getch();
            if(ch==75){input=1;}
            else if(ch==72){input=4;}
            else if(ch==77){input=3;}
            else if(ch==80){input=2;}

            combineElements(maingrid,input,playerscore);

            moveElements(maingrid,input,flagchange);

            system("cls");

            if(flagchange==1){placeNewNumber(maingrid);}
            print2048(maingrid,playerscore);

        }

    }
    gotoxy(0,17);cout<<"              ";
    gotoxy(0,19);cout<<"You lost! Final Score:"<<playerscore<<endl;
    getch();
    system("pause");


    return 0;
}

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}
bool LossCondition(int maingrid[N][N])
{
    int row,col;
    bool flag1,flag2;

    for(col=0;col<N;col++)
    {
      for(row=0;row<N-1;row++)
      {
          if(maingrid[row][col]==maingrid[row+1][col]){return false;}
      }

    }
    for(row=0;row<N;row++)
    {
      for(col=0;col<N-1;col++)
      {
          if(maingrid[row][col]==maingrid[row][col+1]){return false;}
      }

    }
    for(col=0;col<N;col++)
    {
      for(row=0;row<N;row++)
      {
          if(maingrid[row][col]==0){return false;}
      }

    }
    return true;

}
int twopower(int n)
{
    int p=1;
    for(int i=0;i<n;i++)
    {
        p=2*p;
    }
    return p;
}
void SetColor(int colourno)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  colourno);
}
void print2048(int maingrid[N][N],long int playerscore)
{
     //main grid
    SetColor(15);
   gotoxy(1,0);{for(int i=1;i<28;i++){cout<<"_";}}

   for(int i=0;i<29;i=i+7)
   {
       for(int j=1;j<17;j++)
       {
           gotoxy(i,j);
           cout<<"|";
       }
   }

    for(int j=4;j<17;j=j+4)
    {
           gotoxy(1,j);
           cout<<"______";
           gotoxy(8,j);
           cout<<"______";
           gotoxy(15,j);
           cout<<"______";
           gotoxy(22,j);
           cout<<"______";
    }
   SetColor(7);
   cout<<endl;
    //end main grid
    for(int row=0;row<4;row++)
    {
      for(int col=0;col<4;col++)
      {
          if(maingrid[row][col]==0){continue;}
          else
          {
                switch(maingrid[row][col])
                {
                    case 1:SetColor(6);break;
                    case 2:SetColor(14);break;
                    case 3:SetColor(5);break;
                    case 4:SetColor(13);break;
                    case 5:SetColor(1);break;
                    case 6:SetColor(9);break;
                    case 7:SetColor(2);break;
                    case 8:SetColor(10);break;
                    case 9:SetColor(3);break;
                    case 10:SetColor(11);break;
                    case 11:SetColor(12);break;
                    case 12:SetColor(15);break;
                }
                gotoxy(1+(7*row),1+(4*col));cout<<" ____ ";
                gotoxy(1+(7*row),2+(4*col));cout<<"|";
                if(maingrid[row][col]<4){cout<<" "<<twopower(maingrid[row][col])<<"  |";}
                else if(maingrid[row][col]<7){cout<<" "<<twopower(maingrid[row][col])<<" |";}
                else if(maingrid[row][col]<10){cout<<" "<<twopower(maingrid[row][col])<<"|";}
                else{cout<<twopower(maingrid[row][col])<<"|";}

                gotoxy(1+(7*row),3+(4*col));cout<<"|____|";SetColor(7);

          }
      }
    }
    gotoxy(0,17);
    cout<<"Score:"<<playerscore;
    gotoxy(0,19);cout<<"Play with arrow keys!";

}
void combineElements(int maingrid[N][N],int input,long int &playerscore)
{
    int row,col,savedn=-1,savedncol=-1,savednrow=-1;

    if(input==1)//up
    {
        for(col=0;col<N;col++)
        {
            savedn=-1;savednrow=-1;
            for(row=0;row<N;row++)
            {
                if(maingrid[row][col]==0){continue;}

                else if(maingrid[row][col]==savedn)
                {
                    maingrid[savednrow][col]++;
                    playerscore=playerscore+twopower(maingrid[savednrow][col]);
                    maingrid[row][col]=0;
                    savedn=-1;
                    savednrow=-1;

                }
                else
                {
                    savednrow=row;
                    savedn=maingrid[row][col];
                }
            }
        }
    }
    else if(input==3)//down
    {
        for(col=0;col<N;col++)
        {
            savedn=-1;savednrow=-1;
            for(row=N-1;row>=0;row--)
            {
                if(maingrid[row][col]==0){continue;}

                else if(maingrid[row][col]==savedn)
                {
                    maingrid[savednrow][col]++;
                    playerscore=playerscore+twopower(maingrid[savednrow][col]);
                    maingrid[row][col]=0;
                    savedn=-1;
                    savednrow=-1;

                }
                else
                {
                    savednrow=row;
                    savedn=maingrid[row][col];
                }
            }
        }
    }
    else if(input==4)//left
    {
        for(row=0;row<N;row++)
        {
            savedn=-1;savedncol=-1;
            for(col=0;col<N;col++)
            {
                if(maingrid[row][col]==0){continue;}

                else if(maingrid[row][col]==savedn)
                {
                    maingrid[row][savedncol]++;
                    playerscore=playerscore+twopower(maingrid[row][savedncol]);
                    maingrid[row][col]=0;
                    savedn=-1;
                    savedncol=-1;

                }
                else
                {
                    savedncol=col;
                    savedn=maingrid[row][col];
                }
            }
        }
    }
    else if(input==2)//right
    {
        for(row=0;row<N;row++)
        {
            savedn=-1;savedncol=-1;
            for(col=N-1;col>=0;col--)
            {
                if(maingrid[row][col]==0){continue;}

                else if(maingrid[row][col]==savedn)
                {
                    maingrid[row][savedncol]++;
                    playerscore=playerscore+twopower(maingrid[row][savedncol]);
                    maingrid[row][col]=0;
                    savedn=-1;
                    savedncol=-1;

                }
                else
                {
                    savedncol=col;
                    savedn=maingrid[row][col];
                }
            }
        }
    }


}
void moveElements(int maingrid[N][N],int input,int &flagchange)
{
    int row,col,zerorow,zerocol;

    if(input==1)//UP
    {
        for(col=0;col<N;col++)
        {
            for(row=1;row<N;row++)
            {
                if(maingrid[row][col]==0){continue;}
                else
                {
                    for(zerorow=row-1 ; maingrid[zerorow][col]==0 && (zerorow>=0);zerorow--){}
                    zerorow++;
                    if(zerorow==row){continue;}
                    else
                    {
                        maingrid[zerorow][col]=maingrid[row][col];
                        flagchange=1;
                        maingrid[row][col]=0;
                    }
                }
            }
        }
    }

    if(input==3)//DOWN
    {
        for(col=0;col<N;col++)
        {
            for(row=N-2;row>=0;row--)
            {
                if(maingrid[row][col]==0){continue;}
                else
                {
                    for(zerorow=row+1 ; maingrid[zerorow][col]==0 && (zerorow<N);zerorow++){}
                    zerorow--;
                    if(zerorow==row){continue;}
                    else
                    {
                        maingrid[zerorow][col]=maingrid[row][col];
                        maingrid[row][col]=0;
                        flagchange=1;
                    }
                }
            }
        }
    }

    if(input==4)//LEFT
    {
        for(row=0;row<N;row++)
        {
            for(col=1;col<N;col++)
            {
                if(maingrid[row][col]==0){continue;}
                else
                {
                    for(zerocol=col-1 ; maingrid[row][zerocol]==0 && (zerocol>=0);zerocol--){}
                    zerocol++;
                    if(zerocol==col){continue;}
                    else
                    {
                        maingrid[row][zerocol]=maingrid[row][col];
                        maingrid[row][col]=0;
                        flagchange=1;
                    }
                }
            }
        }
    }

    if(input==2)//right
    {
        for(row=0;row<N;row++)
        {
            for(col=N-2;col>=0;col--)
            {
                if(maingrid[row][col]==0){continue;}
                else
                {
                    for(zerocol=col+1 ; maingrid[row][zerocol]==0 && (zerocol<N);zerocol++){}
                    zerocol--;
                    if(zerocol==col){continue;}
                    else
                    {
                        maingrid[row][zerocol]=maingrid[row][col];
                        maingrid[row][col]=0;
                        flagchange=1;
                    }
                }
            }
        }
    }
}
int GetRandomNumber(int n)
{
    return (rand() % (n+1));
}
void placeNewNumber(int maingrid[N][N])
{
    int row,col,probfactor;
    do{
        row=GetRandomNumber(3);
        col=GetRandomNumber(3);
    }while(maingrid[row][col]!=0);

    probfactor=GetRandomNumber(4);
    if(probfactor==4)
    {
        maingrid[row][col]=2;
    }
    else
    {
        maingrid[row][col]=1;
    }

}




#include<iostream>
#include<windows.h>
#include <time.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
#define N 4
bool LossCondition(int maingrid[N][N]);
int twopower(int n);
void print2048(int maingrid[N][N],long int playerscore);
void SetColor(int colourno);
void combineElements(int maingrid[N][N],int input,long int &playerscore);
void moveElements(int maingrid[N][N],int input);
void placeNewNumber(int maingrid[N][N]);
void gotoxy(int x, int y);
int GetRandomNumber(int n);
bool gridchange(int initgrid[N][N],int finalgrid[N][N]);//return true if grid has changed
//made for solving
void initGrid(int grid1[N][N],int grid2[N][N]);
long int playGridTillEnd(int maingrid[N][N],long int inscore); //plays a complete random game from current position , and returns score after game end
long int playGridTillEndv2(int maingrid[N][N],long int inscore);
int bestPlay(int maingrid[N][N],long int inscore); //return most favorable direction
int bestPlayv2(int maingrid[N][N],long int inscore);


int main()
{
    srand(time(0));
    int maingrid[N][N]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    int tempgrid[N][N];
    long int playerscore=0;
    int input,flagchange;

    placeNewNumber(maingrid);
    placeNewNumber(maingrid);

    print2048(maingrid,playerscore);
    while(!LossCondition(maingrid))
    {
        /*
        getch();
        if (kbhit())
        {
            char ch = getch();
            if(ch==75){input=1;}
            else if(ch==72){input=4;}
            else if(ch==77){input=3;}
            else if(ch==80){input=2;}
            initGrid(tempgrid,maingrid);
            combineElements(maingrid,input,playerscore);
            moveElements(maingrid,input);
            system("cls");
            if(gridchange(tempgrid,maingrid)){placeNewNumber(maingrid);}
            print2048(maingrid,playerscore);
            gotoxy(0,21);
            switch(bestPlay(maingrid,playerscore))
            {
                case 1: cout<<"Best move: Left ";break;
                case 2: cout<<"Best move: Down ";break;
                case 3: cout<<"Best move: Right";break;
                case 4: cout<<"Best move: Up   ";break;
            }
        }*/

        input=bestPlay(maingrid,playerscore);

        combineElements(maingrid,input,playerscore);
        moveElements(maingrid,input);

        system("cls");
        placeNewNumber(maingrid);

        print2048(maingrid,playerscore);


    }
    //print2048(maingrid,playerscore);
    gotoxy(0,17);cout<<"              ";
    gotoxy(0,19);cout<<"You lost! Final Score:"<<playerscore<<endl;
    getch();
    system("pause");


    return 0;
}
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}
bool LossCondition(int maingrid[N][N])
{
    int row,col;
    bool flag1,flag2;

    for(col=0;col<N;col++)
    {

      for(row=0;row<N-1;row++)
      {
          if(maingrid[row][col]==maingrid[row+1][col]){return false;}
      }

    }
    for(row=0;row<N;row++)
    {
      for(col=0;col<N-1;col++)
      {
          if(maingrid[row][col]==maingrid[row][col+1]){return false;}
      }

    }
    for(col=0;col<N;col++)
    {
      for(row=0;row<N;row++)
      {
          if(maingrid[row][col]==0){return false;}
      }

    }
    return true;

}
int twopower(int n)
{
    int p=1;
    for(int i=0;i<n;i++)
    {
        p=2*p;
    }
    return p;
}
void SetColor(int colourno)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  colourno);
}
void print2048(int maingrid[N][N],long int playerscore)
{
     //main grid
    SetColor(15);
   gotoxy(1,0);{for(int i=1;i<28;i++){cout<<"_";}}

   for(int i=0;i<29;i=i+7)
   {
       for(int j=1;j<17;j++)
       {
           gotoxy(i,j);
           cout<<"|";
       }
   }

    for(int j=4;j<17;j=j+4)
    {
           gotoxy(1,j);
           cout<<"______";
           gotoxy(8,j);
           cout<<"______";
           gotoxy(15,j);
           cout<<"______";
           gotoxy(22,j);
           cout<<"______";
    }
   SetColor(7);
   cout<<endl;
    //end main grid
    for(int row=0;row<4;row++)
    {
      for(int col=0;col<4;col++)
      {
          if(maingrid[row][col]==0){continue;}
          else
          {
                switch(maingrid[row][col])
                {
                    case 1:SetColor(6);break;
                    case 2:SetColor(14);break;
                    case 3:SetColor(5);break;
                    case 4:SetColor(13);break;
                    case 5:SetColor(1);break;
                    case 6:SetColor(9);break;
                    case 7:SetColor(2);break;
                    case 8:SetColor(10);break;
                    case 9:SetColor(3);break;
                    case 10:SetColor(11);break;
                    case 11:SetColor(12);break;
                    case 12:SetColor(15);break;
                }
                gotoxy(1+(7*row),1+(4*col));cout<<" ____ ";
                gotoxy(1+(7*row),2+(4*col));cout<<"|";
                if(maingrid[row][col]<4){cout<<" "<<twopower(maingrid[row][col])<<"  |";}
                else if(maingrid[row][col]<7){cout<<" "<<twopower(maingrid[row][col])<<" |";}
                else if(maingrid[row][col]<10){cout<<" "<<twopower(maingrid[row][col])<<"|";}
                else{cout<<twopower(maingrid[row][col])<<"|";}

                gotoxy(1+(7*row),3+(4*col));cout<<"|____|";SetColor(7);

          }
      }
    }
    gotoxy(0,17);
    cout<<"Score:"<<playerscore;
    gotoxy(0,19);cout<<"Play with arrow keys!";

}
void combineElements(int maingrid[N][N],int input,long int &playerscore)
{
    int row,col,savedn=-1,savedncol=-1,savednrow=-1;

    if(input==1)//up
    {
        for(col=0;col<N;col++)
        {
            savedn=-1;savednrow=-1;
            for(row=0;row<N;row++)
            {
                if(maingrid[row][col]==0){continue;}

                else if(maingrid[row][col]==savedn)
                {
                    maingrid[savednrow][col]++;
                    playerscore=playerscore+twopower(maingrid[savednrow][col]);
                    maingrid[row][col]=0;
                    savedn=-1;
                    savednrow=-1;

                }
                else
                {
                    savednrow=row;
                    savedn=maingrid[row][col];
                }
            }
        }
    }
    else if(input==3)//down
    {
        for(col=0;col<N;col++)
        {
            savedn=-1;savednrow=-1;
            for(row=N-1;row>=0;row--)
            {
                if(maingrid[row][col]==0){continue;}

                else if(maingrid[row][col]==savedn)
                {
                    maingrid[savednrow][col]++;
                    playerscore=playerscore+twopower(maingrid[savednrow][col]);
                    maingrid[row][col]=0;
                    savedn=-1;
                    savednrow=-1;

                }
                else
                {
                    savednrow=row;
                    savedn=maingrid[row][col];
                }
            }
        }
    }
    else if(input==4)//left
    {
        for(row=0;row<N;row++)
        {
            savedn=-1;savedncol=-1;
            for(col=0;col<N;col++)
            {
                if(maingrid[row][col]==0){continue;}

                else if(maingrid[row][col]==savedn)
                {
                    maingrid[row][savedncol]++;
                    playerscore=playerscore+twopower(maingrid[row][savedncol]);
                    maingrid[row][col]=0;
                    savedn=-1;
                    savedncol=-1;

                }
                else
                {
                    savedncol=col;
                    savedn=maingrid[row][col];
                }
            }
        }
    }
    else if(input==2)//right
    {
        for(row=0;row<N;row++)
        {
            savedn=-1;savedncol=-1;
            for(col=N-1;col>=0;col--)
            {
                if(maingrid[row][col]==0){continue;}

                else if(maingrid[row][col]==savedn)
                {
                    maingrid[row][savedncol]++;
                    playerscore=playerscore+twopower(maingrid[row][savedncol]);
                    maingrid[row][col]=0;
                    savedn=-1;
                    savedncol=-1;

                }
                else
                {
                    savedncol=col;
                    savedn=maingrid[row][col];
                }
            }
        }
    }


}
void moveElements(int maingrid[N][N],int input)
{
    int row,col,zerorow,zerocol;

    if(input==1)//UP
    {
        for(col=0;col<N;col++)
        {
            for(row=1;row<N;row++)
            {
                if(maingrid[row][col]==0){continue;}
                else
                {
                    for(zerorow=row-1 ; maingrid[zerorow][col]==0 && (zerorow>=0);zerorow--){}
                    zerorow++;
                    if(zerorow==row){continue;}
                    else
                    {
                        maingrid[zerorow][col]=maingrid[row][col];
                        maingrid[row][col]=0;
                    }
                }
            }
        }
    }

    if(input==3)//DOWN
    {
        for(col=0;col<N;col++)
        {
            for(row=N-2;row>=0;row--)
            {
                if(maingrid[row][col]==0){continue;}
                else
                {
                    for(zerorow=row+1 ; maingrid[zerorow][col]==0 && (zerorow<N);zerorow++){}
                    zerorow--;
                    if(zerorow==row){continue;}
                    else
                    {
                        maingrid[zerorow][col]=maingrid[row][col];
                        maingrid[row][col]=0;
                    }
                }
            }
        }
    }

    if(input==4)//LEFT
    {
        for(row=0;row<N;row++)
        {
            for(col=1;col<N;col++)
            {
                if(maingrid[row][col]==0){continue;}
                else
                {
                    for(zerocol=col-1 ; maingrid[row][zerocol]==0 && (zerocol>=0);zerocol--){}
                    zerocol++;
                    if(zerocol==col){continue;}
                    else
                    {
                        maingrid[row][zerocol]=maingrid[row][col];
                        maingrid[row][col]=0;
                    }
                }
            }
        }
    }

    if(input==2)//right
    {
        for(row=0;row<N;row++)
        {
            for(col=N-2;col>=0;col--)
            {
                if(maingrid[row][col]==0){continue;}
                else
                {
                    for(zerocol=col+1 ; maingrid[row][zerocol]==0 && (zerocol<N);zerocol++){}
                    zerocol--;
                    if(zerocol==col){continue;}
                    else
                    {
                        maingrid[row][zerocol]=maingrid[row][col];
                        maingrid[row][col]=0;
                    }
                }
            }
        }
    }
}
int GetRandomNumber(int n)
{
    return (rand() % (n+1));
}
void placeNewNumber(int maingrid[N][N])
{
    int row,col,probfactor;
    do{
        row=GetRandomNumber(3);
        col=GetRandomNumber(3);
    }while(maingrid[row][col]!=0);

    probfactor=GetRandomNumber(4);
    if(probfactor==4)
    {
        maingrid[row][col]=2;
    }
    else
    {
        maingrid[row][col]=1;
    }

}
bool gridchange(int initgrid[N][N],int finalgrid[N][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(initgrid[i][j]!=finalgrid[i][j])
            {
                return true;
            }
        }
    }

    return false;
}
void initGrid(int grid1[N][N],int grid2[N][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            grid1[i][j]=grid2[i][j];
        }
    }

}

long int playGridTillEnd(int maingrid[N][N],long int inscore)
{
    int copygrid[N][N],tempgrid[N][N];
    int movedir,flagchange;
    initGrid(copygrid,maingrid);

    while(!LossCondition(copygrid))
    {
        flagchange=0;
        movedir=GetRandomNumber(3)+1;
        initGrid(tempgrid,copygrid);

        combineElements(copygrid,movedir,inscore);
        moveElements(copygrid,movedir);

        if(gridchange(tempgrid,copygrid)){placeNewNumber(copygrid);}
    }

    return inscore;
}
int bestPlay(int maingrid[N][N],long int inscore)
{
    long int inscoreog=inscore,inscoreafterdir;
    int flagchange,dir=1;
    int copygrid[N][N],tempgrid[N][N];
    long long int totalscore[5]={0};


    for(dir=1;dir<5;dir++)
    {
        inscore=inscoreog;
        initGrid(copygrid,maingrid);
        initGrid(tempgrid,copygrid);

        combineElements(copygrid,dir,inscore);
        moveElements(copygrid,dir);



        if(gridchange(tempgrid,copygrid)){placeNewNumber(copygrid);}
        else{continue;}

        inscoreafterdir=inscore;

        if(LossCondition(copygrid)){continue;}

        for(int i=0;i<200;i++)
        {
            inscore=inscoreafterdir;
            totalscore[dir]=totalscore[dir] +playGridTillEnd(copygrid,inscore);

        }
    }

    long long int bestscore=totalscore[1];
    int bestdir=1;

    for(int i=1; i<5;i++)
    {
        if(totalscore[i]>bestscore)
        {
            bestscore=totalscore[i];
            bestdir=i;
        }
        cout<<totalscore[i]<<endl;
    }

    return bestdir;

}
//up 4
//left 1
//right 3
//down 2
long int playGridTillEndv2(int maingrid[N][N],long int inscore)
{
    int copygrid[N][N],tempgrid[N][N],temp2grid[N][N];
    int movedir,flagchange;
    initGrid(copygrid,maingrid);
    long int inscoreog=inscore;


    while(!LossCondition(copygrid))
    {


        bool flagup=false,flagleft=false,flagright=false;

        //up change
        initGrid(tempgrid,copygrid);

        combineElements(tempgrid,4,inscore);
        moveElements(tempgrid,4);
        if(gridchange(tempgrid,copygrid)){flagup=true;}

        initGrid(tempgrid,copygrid);
        inscore=inscoreog;

        //left change
        combineElements(tempgrid,1,inscore);
        moveElements(tempgrid,1);
        if(gridchange(tempgrid,copygrid)){flagleft=true;}

        initGrid(tempgrid,copygrid);
        inscore=inscoreog;

        //right change
        combineElements(tempgrid,3,inscore);
        moveElements(tempgrid,3);
        if(gridchange(tempgrid,copygrid)){flagright=true;}


        inscore=inscoreog;

        if(flagup==true && flagleft==true)
        {
            int flag=GetRandomNumber(1);
            if(flag==0)
            {
                movedir=1;
            }
            else{movedir=4;}
        }
         else{
         if(flagup==true)
        {
            movedir=4;
        }
        if(flagleft==true)
        {
            movedir=1;
        }

        if(flagup==false && flagleft==false)
        {
            if(flagright==true)
            {
                movedir=3;
            }
            else
            {
                movedir=2;
            }
        }}
        //movedir=GetRandomNumber(3)+1;

        initGrid(temp2grid,copygrid);

        combineElements(copygrid,movedir,inscore);
        moveElements(copygrid,movedir);

        if(gridchange(temp2grid,copygrid)){placeNewNumber(copygrid);}
    }

    return inscore;
}
int bestPlayv2(int maingrid[N][N],long int inscore)
{

    bool flagup=false,flagleft=false,flagright=false;
    int flag4end=0,flag1end=0;
    long int inscoreafterdir;
    int copygrid[N][N],tempgrid[N][N];
    long int inscoreog=inscore;
    long long int totalscore4,totalscore1;

    initGrid(copygrid,maingrid);
    initGrid(tempgrid,copygrid);

    //up change
    combineElements(tempgrid,4,inscore);
    moveElements(tempgrid,4);
    if(gridchange(tempgrid,maingrid)){flagup=true;}

    initGrid(tempgrid,copygrid);
    inscore=inscoreog;

    //left change
    combineElements(tempgrid,1,inscore);
    moveElements(tempgrid,1);
    if(gridchange(tempgrid,maingrid)){flagleft=true;}

    initGrid(tempgrid,copygrid);
    inscore=inscoreog;

    //right change
    combineElements(tempgrid,3,inscore);
    moveElements(tempgrid,3);
    if(gridchange(tempgrid,maingrid)){flagright=true;}

    initGrid(tempgrid,copygrid);
    inscore=inscoreog;

    if(flagup== true &&flagleft==true)
    {

        combineElements(copygrid,4,inscore);
        moveElements(copygrid,4);

        inscoreafterdir=inscore;

        for(int i=0;i<20000;i++)
        {
            inscore=inscoreafterdir;
            totalscore4=totalscore4 +playGridTillEnd(copygrid,inscore);

        }

        inscore=inscoreog;
        initGrid(copygrid,maingrid);
        initGrid(tempgrid,copygrid);

        combineElements(copygrid,1,inscore);
        moveElements(copygrid,1);

        inscoreafterdir=inscore;

        for(int i=0;i<2000;i++)
        {
            inscore=inscoreafterdir;
            totalscore1=totalscore1 +playGridTillEnd(copygrid,inscore);

        }

        if(totalscore1>totalscore4)
        {
            return 1;
        }
        else
        {
            return 4;
        }

    }
    if(flagup==true)
    {
        return 4;
    }
    if(flagleft==true)
    {
        return 1;
    }

    if(flagup==false &&flagleft==false)
    {
        if(flagright==true)
        {
            return 3;
        }
        else
        {
            return 2;
        }
    }

}

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define UNCLICKEDCHAR 35
#define BOMBCHAR 153
#define FLAGCHAR 157
#define CLICKEDBUTZERO 48
#define BOMB 9
#define FLAG 8
#define CORRECT 251
#define WRONG 88
using namespace std;


void SetColor(int value);
void clickPos(int bombgrid[][20],int grid[][20],int N,int x,int y,bool &flaggameover);//main part of the program
int searchValidNeighbours(int bombgrid[][20],int grid[][20],int N,int x,int y); //searches valid neighbors and returns number of bombs
void placeBombs(int bombgrid[][20],int Nbomb,int N);                     //placing Nbomb bombs on the bombgrid
int GetRandomNumber(int n);
void printGrid(int grid[][20],int N);                       //printing the minesweeper grid
bool WinCondition(int bombgrid[][20],int grid[][20],int N); //checking if all unbombed location have been clicked
bool displayBombs(int bombgrid[][20],int grid[][20],int N);


int main()
{
    char unclicked=UNCLICKEDCHAR,bomb=BOMBCHAR,clickzero=CLICKEDBUTZERO,flag=FLAGCHAR,correct=CORRECT,wrong=WRONG;
    int bombgrid[20][20];
    bool flaggameover=false;
    int grid[20][20];                             //grid is the grid seen by the user
    int N,Nbomb,currentstatus,numberofturns=0;
    int i,j,k,x,y,xflag,yflag;
    cout<<"Welcome to MineSweeper! "<<endl<<endl;
    cout<<"Instructions:\nFill in the coordinates in 'xcoordinate *space* ycordinate' \n(without the quote marks)\nUse negative coordinates '-x -y' to flag location(x y).\nUse the same to unflag a flagged location.\n\nSymbols:"<<endl;
    SetColor(2);cout<<unclicked<<"-->Unclicked part of grid"<<endl;
    SetColor(12);cout<<bomb<<"-->Bombs!"<<endl;
    SetColor(6);cout<<clickzero<<"-->Indicates no bombs in surroundings. Same as blank pressed tile."<<endl;
    SetColor(12);cout<<flag<<"-->Flags!"<<endl;
    SetColor(10);cout<<correct<<"-->Correctly flagged bomb"<<endl;
    SetColor(12);cout<<wrong<<"-->Incorrectly flagged tile"<<endl;SetColor(7);

    cout<<"\nEnter N for NxN grid(max 20):";cin>>N;
    if(N>20){cout<<"Invalid N;";return -1;}

    cout<<"No. of bombs?:";cin>>Nbomb;
    if(Nbomb>(N*N)){cout<<"Invalid number of bombs!"; return -1;}   //if bombs> total spaces

     for(i=0;i<N;i++)
        for(j=0;j<N;j++)                                            //intializing all elements in bombgrid to 0
            bombgrid[i][j]=0;                                       //0 represents no bomb, on the grid, 1 represents a bomb

    for(i=0;i<N;i++)
        for(j=0;j<N;j++)                                            //intializing all elements in grid to -1 (meaning unclicked)
            grid[i][j]=-1;


    placeBombs(bombgrid,Nbomb,N);
    printGrid(grid,N);
    while(!WinCondition(bombgrid,grid,N) && !flaggameover)                  //main loop which keeps iterating till user clicks on bomb, or wins
    {
        cout<<"\nEnter coordinates to click (x,y)(x is horizontal):";cin>>y>>x;

        if(x>(N-1) || y>(N-1))
        {
            cout<<"\nInvalid Coordinates";
            continue;
        }
        if((x<0 && (y==0||y<0))||((x==0||x<0) && y<0))
        {
            if(grid[-x][-y]==FLAG){grid[-x][-y]=-1;printGrid(grid,N);}
            else{grid[-x][-y]=FLAG;
                    printGrid(grid,N);}                                      //changing value of that particular location to FLAG
        }
        else
        {
            clickPos(bombgrid,grid,N,x,y,flaggameover);
            numberofturns++;
            printGrid(grid,N);
        }

    }

    if(WinCondition(bombgrid,grid,N))
    {
        cout<<"\n\nYOU WIN!!\n\nYou did it in "<<numberofturns<<" turns!"<<endl;    //the loop ended in two cases, have to check
    }
    system("PAUSE");
    cout<<endl;                                                                             //if he lost or won
    return 0;

}

bool displayBombs(int bombgrid[][20],int grid[][20],int N)
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            if(bombgrid[i][j]==1){if(grid[i][j]==FLAG){grid[i][j]=CORRECT;}else{grid[i][j]=BOMB;}}
        }
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            if(grid[i][j]==FLAG){grid[i][j]=WRONG;}
        }
    return true;
}

void clickPos(int bombgrid[][20],int grid[][20],int N,int x,int y,bool &flaggameover)
{
    int n,x1=x-1,y1=y-1,x2=x+1,y2=y+1;
    n=searchValidNeighbours(bombgrid,grid,N,x,y);

    if(grid[x][y]!=-1){return;}
    else if(bombgrid[x][y]==1)
    {
        flaggameover=displayBombs(bombgrid,grid,N);
        cout<<"\n\nYou clicked on a BOMB! GAME OVER!!\n";
        return;
    }
    else
    {
        if(n!=0){grid[x][y]=n;}
        else //0 bombs in surroundings
        {
            grid[x][y]=0;
            if(y1>=0)           {clickPos(bombgrid,grid,N,x,y1,flaggameover);}               //checking if adjacent cells are valid or not and clicking them
            if(y1>=0 && x2<N)   {clickPos(bombgrid,grid,N,x2,y1,flaggameover);}              //if no bombs are present in any of them
            if(x2<N)            {clickPos(bombgrid,grid,N,x2,y,flaggameover);}
            if(y2<N && x2<N)    {clickPos(bombgrid,grid,N,x2,y2,flaggameover);}
            if(y2<N)            {clickPos(bombgrid,grid,N,x,y2,flaggameover);}
            if(y2<N && x1>=0)   {clickPos(bombgrid,grid,N,x1,y2,flaggameover);}
            if(x1>=0)           {clickPos(bombgrid,grid,N,x1,y,flaggameover);}
            if(x1>=0 && y1>=0)  {clickPos(bombgrid,grid,N,x1,y1,flaggameover);}
        }
        return;
    }

}
int searchValidNeighbours(int bombgrid[][20],int grid[][20],int N,int x,int y)
{
        int countBomb=0,y1=y-1,y2=y+1,x1=x-1,x2=x+1;

        if(y1>=0)           {if(bombgrid[x][y1]==1){countBomb++;}}
        if(y1>=0 && x2<N)   {if(bombgrid[x2][y1]==1){countBomb++;}}
        if(x2<N)            {if(bombgrid[x2][y]==1){countBomb++;}}
        if(y2<N && x2<N)    {if(bombgrid[x2][y2]==1){countBomb++;}}
        if(y2<N)            {if(bombgrid[x][y2]==1){countBomb++;}}
        if(y2<N && x1>=0)   {if(bombgrid[x1][y2]==1){countBomb++;}}
        if(x1>=0)           {if(bombgrid[x1][y]==1){countBomb++;}}
        if(x1>=0 && y1>=0)  {if(bombgrid[x1][y1]==1){countBomb++;}}

        return countBomb;
}
void printGrid(int grid[][20],int N)
{
    char unclicked=UNCLICKEDCHAR,bomb=BOMBCHAR,clickzero=CLICKEDBUTZERO,flag=FLAGCHAR,correct=CORRECT,wrong=WRONG;
    cout<<endl<<"   ";
    for(int i=0;i<N;i++){SetColor(9);cout<<i;SetColor(7);if(i<10){cout<<"  ";}else{cout<<" ";}}

    cout<<endl;
    for(int i=0;i<N;i++)
    {

        SetColor(9);cout<<i;SetColor(7);if(i<10){cout<<"  ";}else{cout<<" ";}
        for(int j=0;j<N;j++)
        {
            if(grid[i][j]==-1){SetColor(2);cout<<unclicked<<"  ";SetColor(7);}
            else if (grid[i][j]==0){SetColor(6);cout<<clickzero<<"  ";SetColor(7);}
            else if (grid[i][j]==BOMB){SetColor(12);cout<<bomb<<"  ";SetColor(7);}
            else if (grid[i][j]==FLAG){SetColor(12);cout<<flag<<"  ";SetColor(7);}
            else if (grid[i][j]==CORRECT){SetColor(10);cout<<correct<<"  ";SetColor(7);}
            else if (grid[i][j]==WRONG){SetColor(12);cout<<wrong<<"  ";SetColor(7);}
            else {SetColor(15);cout<<grid[i][j]<<"  ";SetColor(7);}
        }
        cout<<endl;
    }
}
void SetColor(int value)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}
bool WinCondition(int bombgrid[][20],int grid[][20],int N)
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(bombgrid[i][j]==0)
            {
                if(grid[i][j]==-1){return false;}
            }
    return true;
}

void placeBombs(int bombgrid[][20],int Nbomb,int N)
{
    int x,y;
    srand(time(0));
    for(int i=0;i<Nbomb;)
    {
        x=GetRandomNumber(N-1);
        y=GetRandomNumber(N-1);
        if(bombgrid[x][y]==1){continue;}
        else{bombgrid[x][y]=1;i++;}

    }

}

int GetRandomNumber(int n)
{
    return (rand() % (n + 1));
}