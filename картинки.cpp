#include "TXLib.h"
#include <ctime>

HDC CreateImage (char name[100]);

int main ()
    {
    txTextCursor (false);
    txCreateWindow(800,600);
    txSetFillColor(TX_WHITE);
    txClear();
    srand(time(NULL));
    HDC fon=CreateImage("fon.bmp");
    HDC kol=CreateImage("2.bmp");
    int t=0;
    int i=0;
    double i1=0;
    while (!GetAsyncKeyState(VK_SPACE) and (i1 <= 100))
        {
        txBitBlt         (txDC(),    0,0,       i1*8,i*8,              fon,           0,0   );
        i1+=1.3333333333;
        i++;
        txSleep(1);
        }
    //        чтото координаты     размер картинки    HDC картинки                         смещение картинки
    while (!GetAsyncKeyState(VK_SPACE))
        {
        txBitBlt         (txDC(),    0,0,       800,600,              fon,           0,0   );
        if  (GetAsyncKeyState(VK_LBUTTON))          { txTransparentBlt (txDC(),     t%600,200     , 200,200,              kol,          0,0, RGB(34,177,76)); }
            else if  (GetAsyncKeyState(VK_RBUTTON)) { txTransparentBlt (txDC(),     t%600,200     , 200,200,              kol,        200,0, RGB(34,177,76)); }
                else                                { txTransparentBlt (txDC(),     t%600,200     , 200,200,              kol,        400,0, RGB(34,177,76)); }
        txSleep(1);
        t+=1;
        }
    txDeleteDC(fon);
    txDeleteDC(kol);
    return 0;
    }

HDC CreateImage (char name[100])
    {
    HDC image=txLoadImage(name);
    if (!image) { txMessageBox ("не могу найти файл (он в имени окна)",name); return 0; }
    else return image;
    }
