#include "fonctions.h"

void initOfficer(int n, int lane)
{
		Officer[n].sprite = getSprite(OFFICER_SPRITE);
		Officer[n].x =SCREEN_WIDTH;
		Officer[n].y =lane*GRID_STEP+PATH_TOP_Y;
		Officer[n].speed = REGULAR_O_SPEED ;
		Officer[n].alive =1;
		Officer[n].passed =0;
		Officer[n].lane = lane;
		printf("Officer %d at: %d,%d\n", n, Officer[n].x, Officer[n].y);
}



void createOfficers(){
	int i, lane;

    lane = rand()%4;

    for(i = 0; i <= Game.nbEnnemiCreated; i++){
        if(Officer[i].y == (lane*GRID_STEP+PATH_TOP_Y) && Officer[i].x > SCREEN_WIDTH - 200 ){
            lane = -1;
        }
    }

    if(lane != -1){
        initOfficer(Game.nbEnnemiCreated, lane);
        Game.nbEnnemiCreated++;
    }
}

void drawOfficer()
{
	int i;
	for(i=0; i<=Game.nbEnnemiCreated; i++){
		if(Officer[i].alive == 1){
		drawImage(Officer[i].sprite, Officer[i].x, Officer[i].y);
		}
	}
}

void moveOfficers() {
	int i,j;

	for(i=0; i<=Game.nbEnnemiCreated;i++){
		if(Officer[i].alive == 1){

			Officer[i].x += (Officer[i].speed - Player.speed);

            if(Officer[i].x < Player.x && Officer[i].passed == 0){
            Game.score += (Player.speed - Officer[i].speed);
            Officer[i].passed = 1;
            }
		}
	}
}

void doEnnemi(){
	int tick = Game.timer % 20;
	if(tick ==0 && Player.x > Officer[Game.nbEnnemiCreated - 1].x - SCREEN_WIDTH){
		createOfficers();
	}
	moveOfficers();
}
