#include "TXLib.h"
#include <ctime>
#include <stdlib.h>

using namespace std;

struct ball_t
    {
    int x,y;
    int r;
    COLORREF color;
    };
const int N=10;

void drawball(ball_t ball);
ball_t createball();

int main()
    {
    txTextCursor (false);
    srand(time(NULL));
    txCreateWindow(800,600);
    txSetFillColor(TX_WHITE);
    txClear();
    ball_t ball[N];
    for (int i=0; i < N ; i++)
        {
        ball[i]=createball();
        }
        while (true)
            {
            txSetFillColor(TX_WHITE);
            txClear();
            for (int i=0; i<N; i++)
                {
                drawball(ball[i]);
                ball[i].r=10;
                }
            txSleep(100);
            }
    /*while (!GetAsyncKeyState(VK_SPACE))
        {
        ball[i]=createball();
        drawball(ball[i]);
        for (int i=0; i < N ; i++)
            {
            ball[i]=
            }
        txSleep(1);
        } */
    return 0;
    }

void drawball(ball_t ball)
    {
    txSetColor(ball.color);
    txSetFillColor(ball.color);
    txCircle(ball.x, ball.y , ball.r);
    }
ball_t createball()
    {
    ball_t ball={rand()%800, rand()%600 , rand ()%50 + 50, RGB(rand()%255,rand()%255,rand()%255)}; //{rand()%800, rand()%600 , rand ()%50 + 50, RGB(rand()%255,rand()%255,rand()%255)};
    return ball;
    }
