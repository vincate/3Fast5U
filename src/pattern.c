#include "fonctions.h"

void initPattern(){
Pattern.x = 0;
Pattern.y = 0;
Pattern.sprite = getSprite(BACKGROUND_SPRITE);
}
void drawBackground(){
drawImage(Pattern.sprite, Pattern.x, Pattern.y);
}
