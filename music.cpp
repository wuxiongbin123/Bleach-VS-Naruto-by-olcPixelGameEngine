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
        case rasenganSound:
        {
            thread tid(playRasengan);
            tid.detach();
        }break;
        case shidoiSound:
        {
            thread tid(playShidoi);
            tid.detach();
        }break;
        case SasukeHitSound: {
            thread tid(playSasukeHit);
            tid.detach();
        }break;
        case selectSound:
        {
            thread tid(playSelect);
            tid.detach();
        }break;
        case readySound:
            {
                thread tid(playReady);
                tid.detach();
            }break;
    }
}

void playHit()
{
    mciSendString(TEXT("open ./audio/hitHeavely.mp3 alias hit"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play hit wait"), NULL, 0, NULL);
}

void playGg()
{
    std::this_thread::sleep_for(std::chrono::microseconds (500));
    mciSendString(TEXT("open ./audio/gameOver.mp3 alias gameover"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play gameover wait"), NULL, 0, NULL);
}

void playNarutoHit()
{
    mciSendString(TEXT("open ./audio/NarutoHit.mp3 alias NarutoHit"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play NarutoHit wait"), NULL, 0, NULL);
}

void playSasukeHit()
{
    mciSendString(TEXT("open ./audio/SasukeHit.mp3 alias NarutoHit"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play NarutoHit wait"), NULL, 0, NULL);
}

void playRasengan()
{
    mciSendString(TEXT("open ./audio/rasengan.mp3 alias NarutoHit"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play NarutoHit wait"), NULL, 0,NULL);
}

void playShidoi()
{
    mciSendString(TEXT("open ./audio/shidoi.mp3 alias NarutoHit"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play NarutoHit wait"), NULL, 0,NULL);
}

void playSelect()
{
    mciSendString(TEXT("open ./audio/select_1.mp3 alias select"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play select wait"), NULL, 0,NULL);
}

void playReady()
{
    mciSendString(TEXT("open ./audio/ready.mp3 alias ready"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play ready wait"), NULL, 0,NULL);
}
