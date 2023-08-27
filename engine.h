//
// Created by Poker Joker on 2023/8/21.
//

#ifndef BVN_ENGINE_H
#define BVN_ENGINE_H
#include "olcPixelGameEngine.h"
#include "music.h"
#include "time.h"


enum state {stand, run, jump, hit, attack, fall, defend,
            flash, farAttack, skill_1, skill_2};
enum unitType {Naruto, ichigo};
enum itemType {none, shurikenItem};
enum player {playerA, playerB, draw, unsettled};

class Unit
{
public:
    Unit();
    Unit(bool s, unitType u);
    state S;
    float stateNum;
    int lives;
    olc::vf2d position;
    olc::vf2d size = {64, 97};
    olc::vf2d speed;
    float acceleration;
    bool side;
    unitType type;
    bool face;
    bool canDoubleJump;
    int attackNum;
    float attackTime;
    float hitTime;
    int hitNum;
    float firstHitTime;
    float fallDownTime;
    float chakra;//查克拉,用于释放技能.
    int chakraBarLen;
    int chakraColor;


    //抽象出按键,从而可以使得行为单独编入一个函数.
    olc::Key rightKey;
    olc::Key leftKey;
    olc::Key upKey;
    olc::Key downKey;
    olc::Key attackKey;
    olc::Key flashKey;
    olc::Key farAttackKey;
    olc::Key skillKey;
    bool moveFlag;//判断是否跑动、跳跃或者攻击.
    int oppoentNum;
    int flashFrames;//闪现姿势持续的帧数
    int farAttackFrames;//远攻姿势维持的帧数.
    int skill_1_Frames;
    int skill_2_Frames;
    int skillHit;//这个仅仅用来改变被攻击的动画,击飞只取决于最后一击.
    //规定：凡是右这个词都是对应true，左都是对应false
};

class Area{
    //members:nw, se, tp, duration.
public:
    Area(){}
    Area(olc::vf2d nw, olc::vf2d sz,
         bool Sd):northwest(nw),
                  size(sz),
                  existence(true),
                  side(Sd){}
    bool inArea(Unit u);
public:
    friend Unit;
    olc::vf2d northwest;
    olc::vf2d size;

    bool existence;
    bool side;//true代表是A的攻击，false代表是B的攻击。
};

//攻击存在区域
class hitArea: public Area
{
public:
    hitArea(olc::vf2d nw, olc::vf2d sz,
            float Duration, bool Sd
            ): Area(nw, sz, Sd)
            {
                startTime = clock();
                duration = Duration;
            }
    float startTime;
    float duration;
};

//角色存在的区域,用于碰撞检测
class unitArea: public Area
{
public:
    unitArea(olc::vf2d nw,
             olc::vf2d sz,
             bool Sd,
             bool mFlag,
             bool mD):
             Area(nw, sz, Sd)
             {  moveFlag = mFlag;
                moveDirection = mD;}
public:
    bool moveFlag;//指是否主动运动, 如果主动运动,运动方向一定和face一致
    bool moveDirection;//right == true, left == false;
};

class Item
{
public:
    Item(olc::vf2d pos, bool sd):position(pos),
                                side(sd),
                                existence(true),
                                tp(none){}
    virtual void effect(Unit* unit, Unit* oppoent){
        std::cout << "none" << std::endl;
    };
    virtual void move(float fElapsedTime){
        std::cout << "none" << std::endl;
    };

public:
    olc::vf2d position = {0, 0};
    itemType tp;
    bool existence;
    bool side;
};

class shuriken: public Item
{
public:
    shuriken(olc::vf2d pos, bool sd,
             bool Direction, olc::vf2d sz,
             bool isHorizontal):Item(pos, sd){
        //设定水平速度为350, 可以斜向上投射,也可以水平投射.
        speed.x = 350;
        if (isHorizontal){
            speed.y = 0;
        }else{
            speed.y = 400;
        }

        size = sz;
        direction = Direction;
        existFrams = 800;
        tp = shurikenItem;
    }

    bool isEffected(Unit* unit);
    void effect(Unit* unit, Unit* oppoent) override;
    void move(float fElapsedTime) override;


public:
    int existFrams;
    olc::vf2d speed;
    bool direction;
    olc::vf2d size;
};


class Example : public olc::PixelGameEngine
{
public:
    Example()
    {
        sAppName = "bvn";
    }

public:
    player winner = unsettled;
    int mouse;
    float gravity = 100;
    float floorPos = ScreenHeight() + 200;
    olc::vf2d floorSite;
    float barRedLenOfA = 330;
    float barRedLenOfB = 330;
    olc::vf2d posOfLivesBarA;
    olc::vf2d posOfLivesBarB;
    olc::vf2d livesGreenBarSizeA;
    olc::vf2d livesRedBarSizeA;
    olc::vf2d livesRedBarSizeB;
    olc::vf2d livesGreenBarSizeB;
    olc::vf2d darkBarSize = {200, 9};
    std::vector<hitArea> hitAreas;
    std::vector<unitArea> unitAreas;
    std::vector<Unit*> units;
    friend Unit;
    Unit unitA;
    Unit unitB;
    std::vector<std::shared_ptr<Item>> items;
    std::vector<std::string> commands;
    void render(float fElapsedTime);
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

    // Sprites
    std::unique_ptr<olc::Sprite> backgroundPic;
    std::unique_ptr<olc::Sprite> standPicOfA;
    std::unique_ptr<olc::Sprite> standPicOfB;
    std::unique_ptr<olc::Sprite> runRightPic;
    std::unique_ptr<olc::Sprite> runLeftPic;
    std::unique_ptr<olc::Sprite> jumpRightPic;
    std::unique_ptr<olc::Sprite> jumpLeftPic;
    std::unique_ptr<olc::Sprite> attackRightPic_0;
    std::unique_ptr<olc::Sprite> attackRightPic_1;
    std::unique_ptr<olc::Sprite> attackRightPic_2;
    std::unique_ptr<olc::Sprite> attackRightPic_3;
    std::unique_ptr<olc::Sprite> attackLeftPic_0;
    std::unique_ptr<olc::Sprite> attackLeftPic_1;
    std::unique_ptr<olc::Sprite> attackLeftPic_2;
    std::unique_ptr<olc::Sprite> attackLeftPic_3;
    std::unique_ptr<olc::Sprite> hitRightPic;
    std::unique_ptr<olc::Sprite> hitLeftPic;
    std::unique_ptr<olc::Sprite> fallRightPic;
    std::unique_ptr<olc::Sprite> fallLeftPic;
    std::unique_ptr<olc::Sprite> defendRightPic;
    std::unique_ptr<olc::Sprite> defendLeftPic;
    std::unique_ptr<olc::Sprite> gameOverPic;
    std::unique_ptr<olc::Sprite> playerAPic;
    std::unique_ptr<olc::Sprite> playerBPic;
    std::unique_ptr<olc::Sprite> livesBarA;
    std::unique_ptr<olc::Sprite> livesBarB;
    std::unique_ptr<olc::Sprite> flashRightPic;
    std::unique_ptr<olc::Sprite> flashLeftPic;
    std::unique_ptr<olc::Sprite> farAttackRightPic_0;
    std::unique_ptr<olc::Sprite> farAttackRightPic_1;
    std::unique_ptr<olc::Sprite> farAttackRightPic_2;
    std::unique_ptr<olc::Sprite> farAttackLeftPic_0;
    std::unique_ptr<olc::Sprite> farAttackLeftPic_1;
    std::unique_ptr<olc::Sprite> farAttackLeftPic_2;
    std::unique_ptr<olc::Sprite> shurikenPic;

    //Decals
    std::unique_ptr<olc::Decal> backgroundDecal;
    std::unique_ptr<olc::Decal> standDecalOfA;
    std::unique_ptr<olc::Decal> standDecalOfB;
    std::unique_ptr<olc::Decal> runRightDecal;
    std::unique_ptr<olc::Decal> runLeftDecal;
    std::unique_ptr<olc::Decal> jumpRightDecal;
    std::unique_ptr<olc::Decal> jumpLeftDecal;
    std::unique_ptr<olc::Decal> attackRightDecal_0;
    std::unique_ptr<olc::Decal> attackRightDecal_1;
    std::unique_ptr<olc::Decal> attackRightDecal_2;
    std::unique_ptr<olc::Decal> attackRightDecal_3;
    std::unique_ptr<olc::Decal> attackLeftDecal_0;
    std::unique_ptr<olc::Decal> attackLeftDecal_1;
    std::unique_ptr<olc::Decal> attackLeftDecal_2;
    std::unique_ptr<olc::Decal> attackLeftDecal_3;
    std::unique_ptr<olc::Decal> hitRightDecal;
    std::unique_ptr<olc::Decal> hitLeftDecal;
    std::unique_ptr<olc::Decal> fallRightDecal;
    std::unique_ptr<olc::Decal> fallLeftDecal;
    std::unique_ptr<olc::Decal> defendRightDecal;
    std::unique_ptr<olc::Decal> defendLeftDecal;
    std::unique_ptr<olc::Decal> gameOverDecal;
    std::unique_ptr<olc::Decal> playerADecal;
    std::unique_ptr<olc::Decal> playerBDecal;
    std::unique_ptr<olc::Decal> livesBarADecal;
    std::unique_ptr<olc::Decal> livesBarBDecal;
    std::unique_ptr<olc::Decal> flashRightDecal;
    std::unique_ptr<olc::Decal> flashLeftDecal;
    std::unique_ptr<olc::Decal> farAttackRightDecal_0;
    std::unique_ptr<olc::Decal> farAttackRightDecal_1;
    std::unique_ptr<olc::Decal> farAttackRightDecal_2;
    std::unique_ptr<olc::Decal> farAttackLeftDecal_0;
    std::unique_ptr<olc::Decal> farAttackLeftDecal_1;
    std::unique_ptr<olc::Decal> farAttackLeftDecal_2;
    std::unique_ptr<olc::Decal> shurikenDecal;

    //大招的图片
    std::unique_ptr<olc::Sprite> skill_1_right_0_P;
    std::unique_ptr<olc::Sprite> skill_1_right_1_P;
    std::unique_ptr<olc::Sprite> skill_1_right_2_P;
    std::unique_ptr<olc::Sprite> skill_1_right_3_P;
    std::unique_ptr<olc::Sprite> skill_1_right_4_P;
    std::unique_ptr<olc::Sprite> skill_1_right_5_P;
    std::unique_ptr<olc::Sprite> skill_1_right_6_P;
    std::unique_ptr<olc::Sprite> skill_1_right_7_P;
    std::unique_ptr<olc::Sprite> skill_1_right_8_P;
    std::unique_ptr<olc::Sprite> skill_1_right_9_P;
    std::unique_ptr<olc::Sprite> skill_1_right_10_P;

    std::unique_ptr<olc::Sprite> skill_1_left_0_P;
    std::unique_ptr<olc::Sprite> skill_1_left_1_P;
    std::unique_ptr<olc::Sprite> skill_1_left_2_P;
    std::unique_ptr<olc::Sprite> skill_1_left_3_P;
    std::unique_ptr<olc::Sprite> skill_1_left_4_P;
    std::unique_ptr<olc::Sprite> skill_1_left_5_P;
    std::unique_ptr<olc::Sprite> skill_1_left_6_P;
    std::unique_ptr<olc::Sprite> skill_1_left_7_P;
    std::unique_ptr<olc::Sprite> skill_1_left_8_P;
    std::unique_ptr<olc::Sprite> skill_1_left_9_P;
    std::unique_ptr<olc::Sprite> skill_1_left_10_P;

    std::unique_ptr<olc::Decal> skill_1_right_0_D;
    std::unique_ptr<olc::Decal> skill_1_right_1_D;
    std::unique_ptr<olc::Decal> skill_1_right_2_D;
    std::unique_ptr<olc::Decal> skill_1_right_3_D;
    std::unique_ptr<olc::Decal> skill_1_right_4_D;
    std::unique_ptr<olc::Decal> skill_1_right_5_D;
    std::unique_ptr<olc::Decal> skill_1_right_6_D;
    std::unique_ptr<olc::Decal> skill_1_right_7_D;
    std::unique_ptr<olc::Decal> skill_1_right_8_D;
    std::unique_ptr<olc::Decal> skill_1_right_9_D;
    std::unique_ptr<olc::Decal> skill_1_right_10_D;

    std::unique_ptr<olc::Decal> skill_1_left_0_D;
    std::unique_ptr<olc::Decal> skill_1_left_1_D;
    std::unique_ptr<olc::Decal> skill_1_left_2_D;
    std::unique_ptr<olc::Decal> skill_1_left_3_D;
    std::unique_ptr<olc::Decal> skill_1_left_4_D;
    std::unique_ptr<olc::Decal> skill_1_left_5_D;
    std::unique_ptr<olc::Decal> skill_1_left_6_D;
    std::unique_ptr<olc::Decal> skill_1_left_7_D;
    std::unique_ptr<olc::Decal> skill_1_left_8_D;
    std::unique_ptr<olc::Decal> skill_1_left_9_D;
    std::unique_ptr<olc::Decal> skill_1_left_10_D;

    std::unique_ptr<olc::Sprite> skill_2_right_0_P;
    std::unique_ptr<olc::Sprite> skill_2_right_1_P;
    std::unique_ptr<olc::Sprite> skill_2_right_2_P;
    std::unique_ptr<olc::Sprite> skill_2_right_3_P;
    std::unique_ptr<olc::Sprite> skill_2_right_4_P;
    std::unique_ptr<olc::Sprite> skill_2_right_5_P;
    std::unique_ptr<olc::Sprite> skill_2_right_6_P;
    std::unique_ptr<olc::Sprite> skill_2_right_7_P;
    std::unique_ptr<olc::Sprite> skill_2_right_8_P;
    std::unique_ptr<olc::Sprite> skill_2_right_9_P;
    std::unique_ptr<olc::Sprite> skill_2_right_10_P;
    std::unique_ptr<olc::Sprite> skill_2_right_11_P;

    std::unique_ptr<olc::Sprite> skill_2_left_0_P;
    std::unique_ptr<olc::Sprite> skill_2_left_1_P;
    std::unique_ptr<olc::Sprite> skill_2_left_2_P;
    std::unique_ptr<olc::Sprite> skill_2_left_3_P;
    std::unique_ptr<olc::Sprite> skill_2_left_4_P;
    std::unique_ptr<olc::Sprite> skill_2_left_5_P;
    std::unique_ptr<olc::Sprite> skill_2_left_6_P;
    std::unique_ptr<olc::Sprite> skill_2_left_7_P;
    std::unique_ptr<olc::Sprite> skill_2_left_8_P;
    std::unique_ptr<olc::Sprite> skill_2_left_9_P;
    std::unique_ptr<olc::Sprite> skill_2_left_10_P;
    std::unique_ptr<olc::Sprite> skill_2_left_11_P;

    std::unique_ptr<olc::Decal> skill_2_right_0_D;
    std::unique_ptr<olc::Decal> skill_2_right_1_D;
    std::unique_ptr<olc::Decal> skill_2_right_2_D;
    std::unique_ptr<olc::Decal> skill_2_right_3_D;
    std::unique_ptr<olc::Decal> skill_2_right_4_D;
    std::unique_ptr<olc::Decal> skill_2_right_5_D;
    std::unique_ptr<olc::Decal> skill_2_right_6_D;
    std::unique_ptr<olc::Decal> skill_2_right_7_D;
    std::unique_ptr<olc::Decal> skill_2_right_8_D;
    std::unique_ptr<olc::Decal> skill_2_right_9_D;
    std::unique_ptr<olc::Decal> skill_2_right_10_D;
    std::unique_ptr<olc::Decal> skill_2_right_11_D;

    std::unique_ptr<olc::Decal> skill_2_left_0_D;
    std::unique_ptr<olc::Decal> skill_2_left_1_D;
    std::unique_ptr<olc::Decal> skill_2_left_2_D;
    std::unique_ptr<olc::Decal> skill_2_left_3_D;
    std::unique_ptr<olc::Decal> skill_2_left_4_D;
    std::unique_ptr<olc::Decal> skill_2_left_5_D;
    std::unique_ptr<olc::Decal> skill_2_left_6_D;
    std::unique_ptr<olc::Decal> skill_2_left_7_D;
    std::unique_ptr<olc::Decal> skill_2_left_8_D;
    std::unique_ptr<olc::Decal> skill_2_left_9_D;
    std::unique_ptr<olc::Decal> skill_2_left_10_D;
    std::unique_ptr<olc::Decal> skill_2_left_11_D;




    olc::vf2d blockSize = {63, 97};
    std::unique_ptr<olc::Sprite> tilePic;
    std::unique_ptr<olc::Decal> tileDecal;


    //动作封装
    void runAction(Unit& unit, float fElapsedTime);
    void jumpAction(Unit& unit, float fElapsedTime);
    void attackAction(Unit& unit, float fElapsedTime);
    void hitAction(Unit& unit, float fElapsedTime);
    void fallAction(Unit& unit, float fElapsedTime);
    void defendAction(Unit& unit, float fElapsedTime);
    void flashAction(Unit& unit, float fElapsedTime);
    void farAttackAction(Unit& unit, float fElapsedTime);
    void skill_1_Action(Unit& unit, float fElapsedTime);
    void skill_2_Action(Unit& unit, float fElapsedTime);
    void gameOver();
    void moveUnit(Unit& unit, float fElapsedTime);

    //动作动画函数封装
    void jumpDraw(Unit& unit, float offset_true, float offset_false);
    void runDraw(Unit& unit, float offset_true, float offset_false);
    void standDraw(Unit& unit, float offset_true, float offset_false);
    void attackDraw(Unit& unit, float offset_true, float offset_false);
    void hitDraw(Unit& unit, float offset_true, float offset_false);
    void fallDraw(Unit& unit, float offset_true, float offset_false);
    void defendDraw(Unit& unit, float offset_true, float offset_false);
    void flashDraw(Unit& unit, float offset_true, float offset_false);
    void farAttackDraw(Unit& unit, float offset_true, float offset_false);
    void skill_1_Draw(Unit& unit, float offset_true, float offset_false);
    void skill_2_Draw(Unit& unit, float offset_true, float offset_false);
    void itemDraw();
    void chakraDraw(Unit* unit);


    void drawSignal(Unit& unit);
    void drawLivesBar(float fEplasedTime);

    //引擎中的交互函数

    bool skillHit(Unit* unit, Unit* oppoent);
    void item_moveAndEffect(float fElapsedTime);
    void collision(float fElapsedTime);
    bool isBlocked(Unit& unit, float futurePos);
    bool isMoving(Unit& unit);
    bool inBound(bool moveDirection, float positionX);
    void recover(Unit& unit);
    void removeDeadArea();
    void removeDeadItem();
};


#endif //BVN_ENGINE_H
