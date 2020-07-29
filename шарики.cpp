 #include "TXLib.h"
#include <ctime>

struct Ball_t
    {
    int x,y;
    int Vx,Vy ;
    COLORREF color;
    int r;
    };

struct doska_t
    {
    int x,y;
    int h,w;
    COLORREF color;
    };

int N=  100;
int an= 5;
int timer =0;

void drawboll (Ball_t ball);
void dv(Ball_t* ball);
void bu(Ball_t* ball1, Ball_t* ball2,int* c);
void drawdoska (doska_t doska);
void dvdoska( doska_t* doska);
void udoska(doska_t doska,Ball_t* ball);
void shar();
Ball_t createball();
int main()
    {
    // фон
    txTextCursor (false);
    txCreateWindow(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN) + 25);
    txSetFillColor(TX_WHITE);
    txClear();
    srand(time(NULL));
    // переменые
    int c=3;
    int t=2;
    Ball_t ball[N];
    doska_t doska= {400,300,100,200, RGB(255,0,0)};
    for (int i=0 ; i<N; i++)
        {
        ball[i]= createball();
        }
    // рабочая область
    while (!GetAsyncKeyState(VK_SPACE) and !GetAsyncKeyState(VK_ESCAPE))
        {
        shar();
        if (t % 2 == 0)
            {
            txSetFillColor(TX_WHITE);
            txClear();
            }
        // движение шариков
        for (int i=0 ; i<an; i++)
            {
            dv( &ball[i]);
            }
        dvdoska(&doska);
        // физика
        for (int i=0 ; i < an; i++)
            {
            for (int i1=i + 1 ; i1<an ;i1++)
                {
                bu(&ball[i],&ball[i1],&c);
                }
            udoska(doska,&ball[i]);
            }
        // прорисовка шариков
        for (int i=0 ; i<an; i++)
            {
            drawboll(ball[i]);
            }
        drawdoska(doska);
        txSetColor(TX_BLACK,2);
        if (GetAsyncKeyState(VK_CONTROL))
            {
            c++;
            txSleep(100);
            }
        if (GetAsyncKeyState(VK_TAB))
            {
            t++;
            txSleep(100);
            }
        txSleep(10);
        }
    return 0 ;
    }
void shar()
    {
    if ((GetAsyncKeyState(VK_ADD)) && (timer==0)) //  +
        {
        an++;
        timer=10;
        }
    if ((GetAsyncKeyState(VK_SUBTRACT)) && (timer==0)) // -
        {
        an--;
        timer=10;
        }
    if (an > 100) an=100;
    if (an < 0) an= 0;
    timer--;
    if (timer < 0) timer=0;
    }
void drawboll (Ball_t ball)
    {
    txSetFillColor(ball.color);
    txSetColor(ball.color);
    txCircle(ball.x,ball.y,ball.r);
    }
void dv(Ball_t* ball)
    {
    if (ball->x>txGetExtentX () - ball->r)      {ball->Vx= - ball->Vx; ball->x--;}
    if (ball->x<ball->r)                        {ball->Vx= - ball->Vx; ball->x++;}
    if (ball->y>txGetExtentY () - ball->r - 22) {ball->Vy= - ball->Vy; ball->y--;}
    if (ball->y<ball->r)                        {ball->Vy= - ball->Vy; ball->y++;}
    ball->x=ball->x + ball->Vx;
    ball->y=ball->y + ball->Vy;
    }
void bu(Ball_t* ball1, Ball_t* ball2,int* c)
    {
    if  ((sqrt( ((ball1->x - ball2->x) * (ball1->x - ball2->x)) + ((ball1->y - ball2->y) * (ball1->y - ball2->y)))) <= (ball1->r + ball2->r + 2))
        {
            if (ball1-> x <= ball2->x)
                {
                ball1->x--;
                }
            else
                {
                ball2->x--;
                }
        ball1->Vx  = - ball1->Vx;
        ball2->Vx  = - ball2->Vx;
        ball1->Vy  = - ball1->Vy;
        ball2->Vy  = - ball1->Vy;
        }
    if (*c % 2 ==0)
        {
        txSetColor(TX_BLACK,3);
        txLine(ball1->x,ball1->y,ball2->x,ball2->y);
        }
    }
void drawdoska (doska_t doska)
    {
    txSetFillColor (doska.color);
    txSetColor (doska.color);
    txRectangle( doska.x , doska.y ,doska.x + doska.w ,doska.y + doska.h );
    }
void dvdoska( doska_t* doska)
    {
     if (GetAsyncKeyState(VK_LEFT)) doska-> x -= 10;
     if (GetAsyncKeyState(VK_RIGHT)) doska-> x += 10;
     if (GetAsyncKeyState(VK_UP)) doska-> y -= 10;
     if (GetAsyncKeyState(VK_DOWN)) doska-> y += 10;
     if ((GetAsyncKeyState(VK_LBUTTON)) and (txMouseY () >= doska->y) and (txMouseY () <= doska->y + doska->h) and (txMouseX () >= doska->x) and (txMouseX () <= doska->x + doska->w))
        {
        doska->y = txMouseY () - doska->h/2;
        doska->x = txMouseX () - doska->w/2;
        }
    }
void udoska(doska_t doska,Ball_t* ball)
    {
    if ((ball->x >=doska.x - ball->r) and (ball->x <=doska.x + doska.w + ball->r) and (ball->y >=doska.y - ball->r) and (ball->y <=doska.y + doska.h + ball->r))
        {
        // отскакивание
        if (ball->x <= doska.x)
            ball->Vx  = - ball->Vx;
        if (ball->x >= doska.x + doska.w)
            ball->Vx  = - ball->Vx;
        if (ball->y <= doska.y)
            ball->Vy  = - ball->Vy;
        if (ball->y >= doska.y + doska.h)
            ball->Vy  = - ball->Vy;
        // дебаг шарика если застрял
        if (ball->x <= doska.x + ball->r)
            ball->x = doska.x - ball->r;
        if (ball->x >= doska.x + doska.w - ball->r)
            ball->x = doska.x + doska.w + ball->r;
        if (ball->y <= doska.y + ball->r)
            ball->y = doska.y -  ball->r;
        if (ball->y >= doska.y + doska.h - ball->r)
            ball->y = doska.y + doska.h  + ball->r;
        }
    }

Ball_t createball()
    {
    Ball_t ball= {random (txGetExtentX () - 100) + 50, random (txGetExtentY () - 100) + 50, random (21) - 10, random (21) - 10, RGB(random(255),random(255),random(255)), random (50) + 10};
    return ball;
    }
