#include "TXLib.h"
#include <ctime>

int N=10;

struct ball_t
    {
    int x,y,vx,vy,h,w;
    };

void drawball(ball_t ball, int r,HDC* boll);
void dvig(ball_t* ball,const int t);

int main()
    {
    srand(time(NULL));
    txTextCursor (false);
    txCreateWindow(800,600);
    txSetFillColor(TX_WHITE);
    txClear();
    ball_t ball[N];
    HDC fon=txLoadImage("pokemon.bmp");
    HDC boll=txLoadImage("far.bmp");
    int r=0;
    int t=1;
        for (int i=0; i <N; i++)
        {
        ball[i]= {.x=random(600) + 100 , .y=random(400) + 100 , .vx=random(20) - 10 , .vy=random(20) - 10 , .h=100 , .w=100 };
        }
    txSetFillColor(TX_BLACK);
    while (!GetAsyncKeyState(VK_SPACE))
        {
        txBitBlt(txDC(),     0,0     , 800,600,              fon,          0,0);
        for (int i=0; i <N; i++)
            {
            dvig(&ball[i], t);
            drawball (ball[i], r,&boll);
            }
        r++;
        if (r==4) r=0;
        txEnd();
        txSleep(15);
        txBegin();
        }
    txDeleteDC(fon);
    txDeleteDC(boll);
    return 0;
    }
void dvig(ball_t* ball,const int t)
    {
    if ((ball->x>800-ball->h/2) or (ball->x<0+ball->h/2)) ball->vx=-ball->vx;
    if ((ball->y>600-ball->w/2) or (ball->y<0+ball->w/2)) ball->vy=-ball->vy;
    ball->x+=ball->vx * t;
    ball->y+=ball->vy * t;
    }

void drawball(ball_t ball, int r,HDC* boll)
    {
    txTransparentBlt  (txDC(),     ball.x - ball.w/2,ball.y-ball.h/2     , 100,100,              *boll,        100 * r,0, RGB(34,177,76) );
    }
