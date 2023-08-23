//
// Created by Poker Joker on 2023/8/21.
//

#ifndef BVN_ENGINE_H
#define BVN_ENGINE_H
#include "olcPixelGameEngine.h"
#include "time.h"

enum state {stand, run, jump, hit, attack};
enum unitType {Naruto, ichigo};
enum areaType {hitArea};

class Unit
{
public:
    Unit();
    Unit(bool s, unitType u);
    state S;
    float stateNum;
    int lives;
    olc::vf2d position;
    olc::vf2d speed;
    float acceleration;
    bool side;
    unitType type;
    bool face;
    bool canDoubleJump;
    int attackNum;
    bool wait;
    float attackTime;
    float hitTime;
    int hitNum;

    //规定：凡是右这个词都是对应true，左都是对应false
};

class Area{
    //members:nw, se, tp, duration.
public:
    Area(){}
    Area(olc::vf2d nw, olc::vf2d sz,
         areaType tp, float Duration, bool Sd):northwest(nw),
                                      size(sz),
                                      type(tp),
                                      startTime(clock()),
                                      duration(Duration),
                                      existence(true),
                                      side(Sd){}
    bool inArea(Unit u);
public:
    olc::vf2d northwest;
    olc::vf2d size;
    areaType type;
    float startTime;
    float duration;
    bool existence;
    bool side;//true代表是A的攻击，false代表是B的攻击。
};

class Example : public olc::PixelGameEngine
{
public:
    Example()
    {
        sAppName = "bvn";
    }

public:
    int mouse;
    float gravity = 100;
    float floorPos = ScreenHeight() + 200;
    olc::vf2d floorSite;
    std::vector<Area> areas;
    friend Unit;
    Unit unitA;
    Unit unitB;
    std::vector<std::string> commands;
    void render();
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

    // 角色图片
    std::unique_ptr<olc::Sprite> standPicOfA;
    std::unique_ptr<olc::Sprite> standPicOfB;
    std::unique_ptr<olc::Sprite> runRightPic;
    std::unique_ptr<olc::Sprite> runLeftPic;
    std::unique_ptr<olc::Sprite> jumpRightPic;
    std::unique_ptr<olc::Sprite> jumpLeftPic;
    std::unique_ptr<olc::Sprite> attackRightPic_0;
    std::unique_ptr<olc::Sprite> attackRightPic_1;
    std::unique_ptr<olc::Sprite> attackRightPic_2;
    std::unique_ptr<olc::Sprite> attackLeftPic_0;
    std::unique_ptr<olc::Sprite> attackLeftPic_1;
    std::unique_ptr<olc::Sprite> attackLeftPic_2;
    std::unique_ptr<olc::Sprite> hitRightPic;
    std::unique_ptr<olc::Sprite> hitLeftPic;
    olc::vf2d blockSize = {63, 97};
    std::unique_ptr<olc::Sprite> tilePic;

    //动作封装
    void attackAction(Unit& unit, float fElapsedTime);
    void hitAction(Unit& unit, float fElapsedTime);

    //动作动画函数封装
    void jumpDraw(Unit& unit, float offset_true, float offset_false);
    void runDraw(Unit& unit, float offset_true, float offset_false);
    void standDraw(Unit& unit, float offset_true, float offset_false);
    void attackDraw(Unit& unit, float offset_true, float offset_false);
    void hitDraw(Unit& unit, float offset_true, float offset_false);


    void recover();
    void removeDeadArea();
};


#endif //BVN_ENGINE_H
