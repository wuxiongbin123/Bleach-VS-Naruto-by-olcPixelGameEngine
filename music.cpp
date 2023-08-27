//
// Created by Poker Joker on 2023/8/23.
//

#include "music.h"
using namespace std;


void play(Sound sd){
    switch (sd) {
        case NarutoHitSound:{
            thread tid(playNarutoHit);
            tid.detach();
        }break;

        case hitSound:{
            thread tid(playHit);
            tid.detach();
        }break;
        case ggSound:{
            thread tid(playGg);
            tid.detach();
        }break;
    }
}

void playHit()
{
    mciSendString(TEXT("open hitHeavely.mp3 alias hit"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play hit wait"), NULL, 0, NULL);
}

void playGg()
{
    std::this_thread::sleep_for(std::chrono::microseconds (500));
    mciSendString(TEXT("open ./gameOver.mp3 alias gameover"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play gameover wait"), NULL, 0, NULL);
}

void playNarutoHit()
{
    mciSendString(TEXT("open NarutoHit.mp3 alias NarutoHit"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play NarutoHit wait"), NULL, 0, NULL);
}