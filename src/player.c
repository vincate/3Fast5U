#include "fonctions.h"

void initPlayer()
{
	Player.sprite = getSprite(PLAYER_SPRITE);
    Player.lane = 3;
    Player.dir = 1;
    Player.acc = 0;
	Player.x = 150;
	Player.speed = 120;
	Player.y = Player.lane*GRID_STEP+PATH_TOP_Y;
}

void drawPlayer()
{
	drawImage(Player.sprite, Player.x, Player.y);
}


void movePlayer()
{
    if(Player.dir == 0 ){
            if( Player.y - 8 > Player.lane*GRID_STEP+PATH_TOP_Y ){
               Player.y -= 8;
            }else{
                Player.y = Player.lane*GRID_STEP+PATH_TOP_Y;
                Player.dir = 1;
            }
    }else if (Player.dir == 2 ){
            if(Player.y + 8 < Player.lane*GRID_STEP+PATH_TOP_Y ){
                Player.y += 8;
            }else{
                Player.dir = 1;
                Player.y = Player.lane*GRID_STEP+PATH_TOP_Y;
            }

    }

    if(Player.acc == 1){
        Player.speed += 0.1;
    }else if(Player.acc == -1){
        Player.speed -= 0.1;
    }
}
