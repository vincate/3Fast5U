#include "fonctions.h"

void initPlayer()
{
	Player.sprite = getSprite(PLAYER_SPRITE);
    Player.lane = 3;
    Player.dir = 1;
    Player.acc = 0;
    Player.ia = 0;
	Player.x = PLAYER_X;
	Player.speed = REGULAR_P_SPEED;
	Player.y = Player.lane*GRID_STEP+PATH_TOP_Y;
}

void drawPlayer()
{
	drawImage(Player.sprite, Player.x, Player.y);
	sprintf(string,"%d", Player.ia );
	drawMenu(string,0,0,Font);
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
        if(Player.x < PLAYER_X + 35){
            Player.x += 5;
        }
    }else if(Player.acc == -1){
        Player.speed -= 0.1;
        if(Player.x > PLAYER_X - 35){
            Player.x -= 5;
        }
    }else{
        if(Player.x < PLAYER_X){
            Player.x += 5;
        }else if(Player.x > PLAYER_X){
            Player.x -= 5;
        }
    }
}

void IA(){

    int j;
    int i = 0;

     while( i < Game.nbEnnemiCreated && (Officer[i].lane != Player.lane || Officer[i].x - Player.x > 150 || Officer[i].x - Player.x <0) ){
    i++;
    }

   if(i < Game.nbEnnemiCreated && Player.y == Player.lane*GRID_STEP+PATH_TOP_Y){
        if(calcDisH() > calcDisB()){
           if(Player.lane != 0){
            Player.lane--;
            Player.dir=0;
           }else{
            Player.lane++;
            Player.dir=2;
            }
        }else{
            if(Player.lane != 3){
            Player.lane++;
            Player.dir=2;
            }else{
            Player.lane--;
            Player.dir=0;
            }
        }
    }
}


double calcDisH()
{
    int i;
    double dis = SCREEN_WIDTH;

    if(Player.lane == 0){return -1;}

    for(i = 0; i < Game.nbEnnemiCreated; i++){

        if(Officer[i].lane == Player.lane - 1 && Officer[i].x < dis && Officer[i].x > Player.x - 50){
            dis = Officer[i].x;
        }

    }
    return dis;
}

double calcDisB()
{
    int i;
    double dis = SCREEN_WIDTH;

    if(Player.lane == 3){return -1;}

    for(i = 0; i < Game.nbEnnemiCreated; i++){

        if(Officer[i].lane == Player.lane + 1 && Officer[i].x < dis && Officer[i].x > Player.x - 50){
            dis = Officer[i].x;
        }

    }
    return dis;
}
