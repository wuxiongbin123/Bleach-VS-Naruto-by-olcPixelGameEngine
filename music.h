//
// Created by Poker Joker on 2023/8/23.
//

#ifndef BVN_MUSIC_H
#define BVN_MUSIC_H
#include <thread>
#include <windows.h>
#include "mmsystem.h"
#include <thread>
#include <chrono>
#pragma comment(lib, "winmm.lib")
enum Sound {hitSound, ggSound, NarutoHitSound};
void play(Sound sd);
void playHit();
void playGg();
void playNarutoHit();

#endif //BVN_MUSIC_H
