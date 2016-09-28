#include "fonctions.h"

void collision()
{
    int i;

    for(i = 0; i < Game.nbEnnemiCreated; i++)
    {
        if(Officer[i].y == Player.y)
        {
            if( (Officer[i].x - 70 < Player.x && Officer[i].x - 70 > Player.x - 70)
             || (Officer[i].x > Player.x - 70 && Officer[i].x < Player.x) )
            {
                Game.stade = 2;
            }
        }
    }
}
