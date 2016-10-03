#include "fonctions.h"


void drawInterface()
{
    drawText("score: ", 100, SCREEN_HEIGHT - 50,textFont);
    sprintf(string,"%d",Game.score);
    drawText(string, 150, SCREEN_HEIGHT - 50, textFont);
    drawText("speed: ", 200, SCREEN_HEIGHT - 50,textFont);
    sprintf(string,"%.0f",Player.speed);
    drawText(string, 250, SCREEN_HEIGHT - 50, textFont);
}
