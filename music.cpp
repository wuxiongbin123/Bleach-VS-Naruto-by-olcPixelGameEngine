//
// Created by Poker Joker on 2023/8/23.
//

#include "music.h"
using namespace std;
void play(Sound sd){
    switch (sd) {
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
    mciSendString(TEXT("open hitSound.mp3 alias mysong"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play mysong wait"), NULL, 0, NULL);
}

void playGg()
{
    std::this_thread::sleep_for(std::chrono::microseconds (500));
    mciSendString(TEXT("open gameOver.mp3 alias mysong"),//I also gave up to play it.
                  NULL, 0, NULL);
    mciSendString(TEXT("play mysong wait"), NULL, 0, NULL);
}