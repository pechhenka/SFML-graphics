#include "TXLib.h"
#include <ctime>

struct char_t
    {
    int x,y;
    int v;
    int zoom;
    COLORREF color;
    int zna;
    int xb;
    };

int N=200;
int HXB=0;
int IHB=0;

COLORREF c=TX_BLACK;

void drawzna(char_t* zna);
void drawxb(char_t zna, int HXB, int IHB);

char_t createzna();

int main ()
    {
    // фон
    txTextCursor (false);
    txCreateWindow(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN) + 25);
    txSetFillColor(c);
    txClear();
    srand(time(NULL));
    //
    char_t zna[N];
    for (int i=0; i < N; i++)
        {
        zna[i]=   createzna();
        }
    while (!GetAsyncKeyState(VK_SPACE) and !GetAsyncKeyState(VK_ESCAPE))
        {
        txSetFillColor(c);
        txClear();
        for (int i=0; i < N; i++)
            {
            drawxb(zna[i],HXB,IHB);
            drawzna(&zna[i]);
            }
        txSleep(5);
        }
    return 0;
    }
void drawxb(char_t zna, int HXB, int IHB)
        {
        txSetColor (zna.color,2);
        for (int i=0; i<=HXB; i++)
            {
            if (zna.zna == 1 ) { txTextOut (zna.x , zna.y - (IHB * i) , "1");}
            if (zna.zna == 0 ) { txTextOut (zna.x , zna.y - (IHB * i) , "0");}
            }
        }
void drawzna(char_t* zna)
    {
    txSetColor (zna->color,2);
    if (zna->zna == 1 ) { txTextOut (zna->x , zna->y , "1");}
    if (zna->zna == 0 ) { txTextOut (zna->x , zna->y , "0");}
    zna->y+=zna->v;
    if (zna->y > txGetExtentY () + 10) {zna->y= -10;}
    }
char_t createzna()
    {
    char_t zna = {random(txGetExtentX () + 8) - 4,random(txGetExtentY ()),random(29) + 2,random(11) + 10,RGB ( random(101), 255, random(101)),random(2),0};
    return zna;
    }
