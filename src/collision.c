#include "fonctions.h"

void collision()
{
    int i;

    for(i = 0; i < Game.nbEnnemiCreated; i++)
    {
        if((Officer[i].y + 30 < Player.y && Officer[i].y + 30 > Player.y + 30)
             || (Officer[i].y > Player.y + 30 && Officer[i].y < Player.y)
             || Player.y == Officer[i].y )
        {
            if( (Officer[i].x - 70 < Player.x && Officer[i].x - 70 > Player.x - 70)
             || (Officer[i].x > Player.x - 70 && Officer[i].x < Player.x) )
            {
                Game.stade = 2;
            }
        }
    }
}
