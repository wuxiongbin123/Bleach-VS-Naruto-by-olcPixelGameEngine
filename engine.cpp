#include "engine.h"
using namespace std;

Unit::Unit(){}

Unit::Unit(bool s, unitType u): S(stand), lives(200)
                                , side(s), type(u),
                                stateNum(0), face(!s),
                                acceleration(0), canDoubleJump(true),
                                attackNum(-1), attackFrames(0),
                                hitFrames(0), hitNum(0),
                                farAttackFrames(0),
                                flashFrames(0), chakra(0),
                                skill_1_Frames(0), skill_2_Frames(0),skill_3_Frames(0),
                                fallDownFrames(0),
                                skillHit(0), size(olc::vf2d(63, 97))
                                {
    speed = {250, 0};
    if (side){
        rightKey = olc::Key::D;
        leftKey = olc::Key::A;
        upKey = olc::Key::W;
        downKey = olc::Key::S;
        attackKey = olc::Key::R;
        flashKey = olc::Key::F;
        farAttackKey = olc::Key::G;
        skillKey = olc::Key::T;


        oppoentNum = 1;
    } else {
        rightKey = olc::Key::RIGHT;
        leftKey = olc::Key::LEFT;
        upKey = olc::Key::UP;
        downKey = olc::Key::DOWN;
        attackKey = olc::Key::PGDN;
        flashKey = olc::Key::PGUP;
        farAttackKey = olc::Key::ENTER;
        skillKey = olc::Key::END;

        oppoentNum = 0;
    }
}


bool Example::OnUserCreate() {

    //初始化人物位置
    unitA = Unit(true, Sasuke);
    unitB = Unit(false, Sasuke);
    units.push_back(&unitA);
    units.push_back(&unitB);

    unitA.position = { 1024 * 0.2 - 120, floorPos-blockSize.y + 15};
    unitB.position = {1024 * 0.8 , floorPos - blockSize.y + 15};//170是hard code上去的，是人物的高度。

    //为了简便，规定Sasuke是角色A,Naruto是角色B.

    backgroundPic = std::make_unique<olc::Sprite>("./pic/background.jpg");
    standPicOfA = std::make_unique<olc::Sprite>("./pic/Naruto/stand_A.png");
    standPicOfB = std::make_unique<olc::Sprite>("./pic/Naruto/stand_B.png");
    tilePic = std::make_unique<olc::Sprite>("./pic/tile.png");
    runRightPic = std::make_unique<olc::Sprite>("./pic/Naruto/run_right.png");
    runLeftPic = std::make_unique<olc::Sprite>("./pic/Naruto/run_left.png");
    jumpRightPic = std::make_unique<olc::Sprite>("./pic/Naruto/jump_right.png");
    jumpLeftPic = std::make_unique<olc::Sprite>("./pic/Naruto/jump_left.png");
    attackRightPic_0 = std::make_unique<olc::Sprite>("./pic/Naruto/attack_0_right.png");
    attackRightPic_1 = std::make_unique<olc::Sprite>("./pic/Naruto/attack_1_right.png");
    attackRightPic_2 = std::make_unique<olc::Sprite>("./pic/Naruto/attack_2_right.png");
    attackRightPic_3 = std::make_unique<olc::Sprite>("./pic/Naruto/attack_3_right.png");
    attackLeftPic_0 = std::make_unique<olc::Sprite>("./pic/Naruto/attack_0_left.png");
    attackLeftPic_1 = std::make_unique<olc::Sprite>("./pic/Naruto/attack_1_left.png");
    attackLeftPic_2 = std::make_unique<olc::Sprite>("./pic/Naruto/attack_2_left.png");
    attackLeftPic_3 = std::make_unique<olc::Sprite>("./pic/Naruto/attack_3_left.png");
    hitRightPic = std::make_unique<olc::Sprite>("./pic/Naruto/hit_right.png");
    hitLeftPic = std::make_unique<olc::Sprite>("./pic/Naruto/hit_left.png");
    fallRightPic = std::make_unique<olc::Sprite>("./pic/Naruto/fall_right.png");
    fallLeftPic = std::make_unique<olc::Sprite>("./pic/Naruto/fall_left.png");
    defendRightPic = std::make_unique<olc::Sprite>("./pic/Naruto/defend_right.png");
    defendLeftPic = std::make_unique<olc::Sprite>("./pic/Naruto/defend_left.png");
    gameOverPic = std::make_unique<olc::Sprite>("./pic/gameOver.png");
    playerAPic = std::make_unique<olc::Sprite>("./pic/playerA.png");
    playerBPic = std::make_unique<olc::Sprite>("./pic/playerB.png");
    livesBarA = std::make_unique<olc::Sprite>("./pic/livesBar_A.png");
    livesBarB = std::make_unique<olc::Sprite>("./pic/livesBar_B.png");
    flashRightPic = std::make_unique<olc::Sprite>("./pic/Naruto/flash_right.png");
    flashLeftPic = std::make_unique<olc::Sprite>("./pic/Naruto/flash_left.png");
    farAttackRightPic_0 = std::make_unique<olc::Sprite>("./pic/Naruto/farAttack/0_right.png");
    farAttackRightPic_1 = std::make_unique<olc::Sprite>("./pic/Naruto/farAttack/1_right.png");
    farAttackRightPic_2 = std::make_unique<olc::Sprite>("./pic/Naruto/farAttack/2_right.png");
    farAttackLeftPic_0 = std::make_unique<olc::Sprite>("./pic/Naruto/farAttack/0_left.png");
    farAttackLeftPic_1 = std::make_unique<olc::Sprite>("./pic/Naruto/farAttack/1_left.png");
    farAttackLeftPic_2 = std::make_unique<olc::Sprite>("./pic/Naruto/farAttack/2_left.png");
    shurikenPic = std::make_unique<olc::Sprite>("./pic/Naruto/farAttack/shuriken.png");

    backgroundDecal = std::make_unique<olc::Decal>(backgroundPic.get());
    standDecalOfA = std::make_unique<olc::Decal>(standPicOfA.get());
    standDecalOfB = std::make_unique<olc::Decal>(standPicOfB.get());
    runRightDecal = std::make_unique<olc::Decal>(runRightPic.get());
    runLeftDecal = std::make_unique<olc::Decal>(runLeftPic.get());
    jumpRightDecal = std::make_unique<olc::Decal>(jumpRightPic.get());
    jumpLeftDecal = std::make_unique<olc::Decal>(jumpLeftPic.get());
    attackRightDecal_0 = std::make_unique<olc::Decal>(attackRightPic_0.get());
    attackRightDecal_1 = std::make_unique<olc::Decal>(attackRightPic_1.get());
    attackRightDecal_2 = std::make_unique<olc::Decal>(attackRightPic_2.get());
    attackRightDecal_3 = std::make_unique<olc::Decal>(attackRightPic_3.get());
    attackLeftDecal_0 = std::make_unique<olc::Decal>(attackLeftPic_0.get());
    attackLeftDecal_1 = std::make_unique<olc::Decal>(attackLeftPic_1.get());
    attackLeftDecal_2 = std::make_unique<olc::Decal>(attackLeftPic_2.get());
    attackLeftDecal_3 = std::make_unique<olc::Decal>(attackLeftPic_3.get());
    hitRightDecal = std::make_unique<olc::Decal>(hitRightPic.get());
    hitLeftDecal = std::make_unique<olc::Decal>(hitLeftPic.get());
    fallRightDecal = std::make_unique<olc::Decal>(fallRightPic.get());
    fallLeftDecal = std::make_unique<olc::Decal>(fallLeftPic.get());
    defendRightDecal = std::make_unique<olc::Decal>(defendRightPic.get());
    defendLeftDecal = std::make_unique<olc::Decal>(defendLeftPic.get());
    gameOverDecal = std::make_unique<olc::Decal>(gameOverPic.get());
    playerADecal = std::make_unique<olc::Decal>(playerAPic.get());
    playerBDecal = std::make_unique<olc::Decal>(playerBPic.get());
    livesBarADecal = std::make_unique<olc::Decal>(livesBarA.get());
    livesBarBDecal = std::make_unique<olc::Decal>(livesBarB.get());
    tileDecal = std::make_unique<olc::Decal>(tilePic.get());
    flashRightDecal = std::make_unique<olc::Decal>(flashRightPic.get());
    flashLeftDecal = std::make_unique<olc::Decal>(flashLeftPic.get());
    farAttackRightDecal_0 = std::make_unique<olc::Decal>(farAttackRightPic_0.get());
    farAttackRightDecal_1 = std::make_unique<olc::Decal>(farAttackRightPic_1.get());
    farAttackRightDecal_2 = std::make_unique<olc::Decal>(farAttackRightPic_2.get());
    farAttackLeftDecal_0 = std::make_unique<olc::Decal>(farAttackLeftPic_0.get());
    farAttackLeftDecal_1 = std::make_unique<olc::Decal>(farAttackLeftPic_1.get());
    farAttackLeftDecal_2 = std::make_unique<olc::Decal>(farAttackLeftPic_2.get());
    shurikenDecal = std::make_unique<olc::Decal>(shurikenPic.get());

    //大招的图片
    skill_1_right_0_P = std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/right/0.png");
    skill_1_right_1_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/right/1.png");
    skill_1_right_2_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/right/2.png");
    skill_1_right_3_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/right/3.png");
    skill_1_right_4_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/right/4.png");
    skill_1_right_5_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/right/5.png");
    skill_1_right_6_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/right/6.png");
    skill_1_right_7_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/right/7.png");
    skill_1_right_8_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/right/8.png");
    skill_1_right_9_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/right/9.png");
    skill_1_right_10_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/right/10.png");

    skill_1_left_0_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/left/0.png");
    skill_1_left_1_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/left/1.png");
    skill_1_left_2_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/left/2.png");
    skill_1_left_3_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/left/3.png");
    skill_1_left_4_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/left/4.png");
    skill_1_left_5_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/left/5.png");
    skill_1_left_6_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/left/6.png");
    skill_1_left_7_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/left/7.png");
    skill_1_left_8_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/left/8.png");
    skill_1_left_9_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/left/9.png");
    skill_1_left_10_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_1/left/10.png");

    skill_1_right_0_D = std::make_unique<olc::Decal>(skill_1_right_0_P.get());
    skill_1_right_1_D = std::make_unique<olc::Decal>(skill_1_right_1_P.get());
    skill_1_right_2_D = std::make_unique<olc::Decal>(skill_1_right_2_P.get());
    skill_1_right_3_D = std::make_unique<olc::Decal>(skill_1_right_3_P.get());
    skill_1_right_4_D = std::make_unique<olc::Decal>(skill_1_right_4_P.get());
    skill_1_right_5_D = std::make_unique<olc::Decal>(skill_1_right_5_P.get());
    skill_1_right_6_D = std::make_unique<olc::Decal>(skill_1_right_6_P.get());
    skill_1_right_7_D = std::make_unique<olc::Decal>(skill_1_right_7_P.get());
    skill_1_right_8_D = std::make_unique<olc::Decal>(skill_1_right_8_P.get());
    skill_1_right_9_D = std::make_unique<olc::Decal>(skill_1_right_9_P.get());
    skill_1_right_10_D = std::make_unique<olc::Decal>(skill_1_right_10_P.get());

    skill_1_left_0_D = std::make_unique<olc::Decal>(skill_1_left_0_P.get());
    skill_1_left_1_D = std::make_unique<olc::Decal>(skill_1_left_1_P.get());
    skill_1_left_2_D = std::make_unique<olc::Decal>(skill_1_left_2_P.get());
    skill_1_left_3_D = std::make_unique<olc::Decal>(skill_1_left_3_P.get());
    skill_1_left_4_D = std::make_unique<olc::Decal>(skill_1_left_4_P.get());
    skill_1_left_5_D = std::make_unique<olc::Decal>(skill_1_left_5_P.get());
    skill_1_left_6_D = std::make_unique<olc::Decal>(skill_1_left_6_P.get());
    skill_1_left_7_D = std::make_unique<olc::Decal>(skill_1_left_7_P.get());
    skill_1_left_8_D = std::make_unique<olc::Decal>(skill_1_left_8_P.get());
    skill_1_left_9_D = std::make_unique<olc::Decal>(skill_1_left_9_P.get());
    skill_1_left_10_D = std::make_unique<olc::Decal>(skill_1_left_10_P.get());

    //第二阶段的图片
    skill_2_right_0_P = std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/right/0.png");
    skill_2_right_1_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/right/1.png");
    skill_2_right_2_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/right/2.png");
    skill_2_right_3_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/right/3.png");
    skill_2_right_4_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/right/4.png");
    skill_2_right_5_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/right/5.png");
    skill_2_right_6_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/right/6.png");
    skill_2_right_7_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/right/7.png");


    skill_2_left_0_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/left/0.png");
    skill_2_left_1_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/left/1.png");
    skill_2_left_2_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/left/2.png");
    skill_2_left_3_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/left/3.png");
    skill_2_left_4_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/left/4.png");
    skill_2_left_5_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/left/5.png");
    skill_2_left_6_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/left/6.png");
    skill_2_left_7_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_2/left/7.png");

    skill_2_right_0_D = std::make_unique<olc::Decal>(skill_2_right_0_P.get());
    skill_2_right_1_D = std::make_unique<olc::Decal>(skill_2_right_1_P.get());
    skill_2_right_2_D = std::make_unique<olc::Decal>(skill_2_right_2_P.get());
    skill_2_right_3_D = std::make_unique<olc::Decal>(skill_2_right_3_P.get());
    skill_2_right_4_D = std::make_unique<olc::Decal>(skill_2_right_4_P.get());
    skill_2_right_5_D = std::make_unique<olc::Decal>(skill_2_right_5_P.get());
    skill_2_right_6_D = std::make_unique<olc::Decal>(skill_2_right_6_P.get());
    skill_2_right_7_D = std::make_unique<olc::Decal>(skill_2_right_7_P.get());

    skill_2_left_0_D = std::make_unique<olc::Decal>(skill_2_left_0_P.get());
    skill_2_left_1_D = std::make_unique<olc::Decal>(skill_2_left_1_P.get());
    skill_2_left_2_D = std::make_unique<olc::Decal>(skill_2_left_2_P.get());
    skill_2_left_3_D = std::make_unique<olc::Decal>(skill_2_left_3_P.get());
    skill_2_left_4_D = std::make_unique<olc::Decal>(skill_2_left_4_P.get());
    skill_2_left_5_D = std::make_unique<olc::Decal>(skill_2_left_5_P.get());
    skill_2_left_6_D = std::make_unique<olc::Decal>(skill_2_left_6_P.get());
    skill_2_left_7_D = std::make_unique<olc::Decal>(skill_2_left_7_P.get());


    //第三阶段
    skill_3_right_0_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_3/right/0.png");
    skill_3_right_1_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_3/right/1.png");
    skill_3_right_2_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_3/right/2.png");
    skill_3_right_3_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_3/right/3.png");

    skill_3_left_0_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_3/left/0.png");
    skill_3_left_1_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_3/left/1.png");
    skill_3_left_2_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_3/left/2.png");
    skill_3_left_3_P= std::make_unique<olc::Sprite>("./pic/Naruto/skill_3/left/3.png");

    skill_3_right_0_D = std::make_unique<olc::Decal>(skill_3_right_0_P.get());
    skill_3_right_1_D = std::make_unique<olc::Decal>(skill_3_right_1_P.get());
    skill_3_right_2_D = std::make_unique<olc::Decal>(skill_3_right_2_P.get());
    skill_3_right_3_D = std::make_unique<olc::Decal>(skill_3_right_3_P.get());

    skill_3_left_0_D = std::make_unique<olc::Decal>(skill_3_left_0_P.get());
    skill_3_left_1_D = std::make_unique<olc::Decal>(skill_3_left_1_P.get());
    skill_3_left_2_D = std::make_unique<olc::Decal>(skill_3_left_2_P.get());
    skill_3_left_3_D = std::make_unique<olc::Decal>(skill_3_left_3_P.get());

    //Sasuke的图片
    Sasuke_stand_right_P = std::make_unique<olc::Sprite>("./pic/Sasuke/stand/right.png");
    Sasuke_stand_left_P = std::make_unique<olc::Sprite>("./pic/Sasuke/stand/left.png");
    Sasuke_run_right_P = std::make_unique<olc::Sprite>("./pic/Sasuke/run/right.png");
    Sasuke_run_left_P = std::make_unique<olc::Sprite>("./pic/Sasuke/run/left.png");
    Sasuke_attack_0_right_P = std::make_unique<olc::Sprite>("./pic/Sasuke/attack/0/right.png");
    Sasuke_attack_0_left_P = std::make_unique<olc::Sprite>("./pic/Sasuke/attack/0/left.png");
    Sasuke_attack_1_right_P = std::make_unique<olc::Sprite>("./pic/Sasuke/attack/1/right.png");
    Sasuke_attack_1_left_P = std::make_unique<olc::Sprite>("./pic/Sasuke/attack/1/left.png");
    Sasuke_hit_right_P = std::make_unique<olc::Sprite>("./pic/Sasuke/hit/right.png");
    Sasuke_hit_left_P = std::make_unique<olc::Sprite>("./pic/Sasuke/hit/left.png");

    Sasuke_stand_right_D = std::make_unique<olc::Decal>(Sasuke_stand_right_P.get());
    Sasuke_stand_left_D = std::make_unique<olc::Decal>(Sasuke_stand_left_P.get());
    Sasuke_run_right_D = std::make_unique<olc::Decal>(Sasuke_run_right_P.get());
    Sasuke_run_left_D = std::make_unique<olc::Decal>(Sasuke_run_left_P.get());
    Sasuke_attack_0_right_D = std::make_unique<olc::Decal>(Sasuke_attack_0_right_P.get());
    Sasuke_attack_0_left_D = std::make_unique<olc::Decal>(Sasuke_attack_0_left_P.get());
    Sasuke_attack_1_right_D = std::make_unique<olc::Decal>(Sasuke_attack_1_right_P.get());
    Sasuke_attack_1_left_D = std::make_unique<olc::Decal>(Sasuke_attack_1_left_P.get());
    Sasuke_hit_right_D = std::make_unique<olc::Decal>(Sasuke_hit_right_P.get());
    Sasuke_hit_left_D = std::make_unique<olc::Decal>(Sasuke_hit_left_P.get());
    return true;
}

bool Example::OnUserUpdate(float fElapsedTime) {
    //每回合开始前,记录两个角色的位置,和运动状态,用于物理碰撞.
    unitA.moveFlag = isMoving(unitA);
    unitB.moveFlag = isMoving(unitB);
    unitAreas.push_back(unitArea(unitA.position, blockSize, true, unitA.moveFlag, unitA.face));
    unitAreas.push_back(unitArea(unitB.position, blockSize, false, unitB.moveFlag, unitB.face));

    if (true) {
        //两个角色自动互相面对
        if (unitA.S == stand) {
            if (unitA.position.x > unitB.position.x) unitA.face = false;
            else unitA.face = true;
        }
        if (unitB.S == stand){
            if (unitB.position.x < unitA.position.x ) unitB.face = true;
            else unitB.face = false;
        }

        jumpAction(unitA, fElapsedTime);
        jumpAction(unitB, fElapsedTime);

        //当按住方向键时将状态设定为奔跑。
        runAction(unitA, fElapsedTime);
        runAction(unitB, fElapsedTime);


        //两个角色的攻击
        attackAction(unitA, fElapsedTime);
        attackAction(unitB, fElapsedTime);

        //攻击时进行移动。
        moveUnit(unitA, fElapsedTime);
        moveUnit(unitB, fElapsedTime);

        //防御
        defendAction(unitA, fElapsedTime);
        defendAction(unitB, fElapsedTime);

        //闪现
        flashAction(unitA, fElapsedTime);
        flashAction(unitB, fElapsedTime);

        //远攻
        farAttackAction(unitA, fElapsedTime);
        farAttackAction(unitB, fElapsedTime);

        //释放技能
        skill_1_Action(unitA, fElapsedTime);
        skill_1_Action(unitB, fElapsedTime);
        skill_2_Action(unitA, fElapsedTime);
        skill_2_Action(unitB, fElapsedTime);
        skill_3_Action(unitA, fElapsedTime);
        skill_3_Action(unitB, fElapsedTime);

        //回合结束，结算是否被攻击中。如果被击中则会移动。
        hitAction(unitA, fElapsedTime);
        hitAction(unitB, fElapsedTime);

        fallAction(unitA, fElapsedTime);
        fallAction(unitB, fElapsedTime);

        //道具移动与生效.
        item_moveAndEffect(fElapsedTime);

        collision(fElapsedTime);

        recover(unitA);
        recover(unitB);
        //回合结束后需要删除unitArea
        unitAreas[0].existence = false;
        unitAreas[1].existence = false;
        //删除所有已死的区域
        removeDeadArea();
        gameOver();
    }

    //删除失效道具.
    removeDeadItem();


            //血条逐渐减少。
    if (barRedLenOfA > 330 * unitA.lives / 200){
            barRedLenOfA -= 35 * fElapsedTime ;
        }
    if (barRedLenOfB > 330 * unitB.lives / 200){
            barRedLenOfB -= 35 * fElapsedTime ;
        }
    render(fElapsedTime);
    return true;
}

void Example::render(float fElapsedTime) {
    Clear(olc::WHITE);

    //画背景
    DrawDecal(olc::vf2d(0, 0), backgroundDecal.get());

    //画地板
    for(int i = 0; i < ScreenWidth() / 16; i++){
        floorSite.x = i * 16;
        floorSite.y = floorPos;
        DrawDecal(floorSite, tileDecal.get());
    }
    drawSignal(unitA);
    drawSignal(unitB);

    //画血条和血条架。
    drawLivesBar(fElapsedTime);

    //画查克拉条

    //先画两个角色的查克拉槽.
    FillRectDecal(olc::vf2d(posOfLivesBarA.x, posOfLivesBarA.y + 53), darkBarSize, olc::DARK_RED);
    FillRectDecal(olc::vf2d(ScreenWidth() - 200, posOfLivesBarA.y + 53), darkBarSize, olc::DARK_RED);
    chakraDraw(&unitA);
    chakraDraw(&unitB);

    SetPixelMode(olc::Pixel::ALPHA);

    //画道具
    itemDraw();

    if (true){
        //根据不同的状态画不同的图像。
        switch (unitA.S) {
            case jump:jumpDraw(unitA, 0, 16);break;
            case stand:standDraw(unitA, 0, 3);break;
            case run:runDraw(unitA, 0, 8);break;
            case attack:attackDraw(unitA, -5, 10);break;
            case hit:hitDraw(unitA, 0, 0);break;
            case fall:fallDraw(unitA, 0, 0);break;
            case defend:defendDraw(unitA, 0, 0);break;
            case flash: flashDraw(unitA, 0, 0);break;
            case farAttack:farAttackDraw(unitA, 0, 0);break;
            case skill_1:skill_1_Draw(unitA, 0, 0);break;
            case skill_2:skill_2_Draw(unitA, 0, 0);break;
            case skill_3:skill_3_Draw(unitA, 0, 0);break;
        }
        switch(unitB.S){
            case jump: jumpDraw(unitB, 0, 16);break;
            case stand:standDraw(unitB, 0, 3);break;
            case run:runDraw(unitB, 0, 8);break;
            case attack:attackDraw(unitB, -5, 10);break;
            case hit:hitDraw(unitB, 0, 0);break;
            case fall:fallDraw(unitB, 0, 0);break;
            case defend:defendDraw(unitB, 0, 0);break;
            case flash:flashDraw(unitB, 0, 0);break;
            case farAttack: farAttackDraw(unitB, 0, 0);break;
            case skill_1:skill_1_Draw(unitB, 0, 0);break;
            case skill_2:skill_2_Draw(unitB, 0, 0);break;
            case skill_3:skill_3_Draw(unitB, 0, 0);break;
        }
    }
    if (winner != unsettled){

        //Render game over.
        olc::vf2d posOfGameOver;
        posOfGameOver.x = 152;
        posOfGameOver.y = 150;
        DrawDecal(posOfGameOver, gameOverDecal.get());
    }
}

//画跳跃状态的函数。true代表向右边动时的偏移量，false代表左边
void Example::jumpDraw(Unit& unit, float offset_true, float offset_false) {
    olc::vf2d offset = {0, 0};
    if (unit.face){//往右跳
        offset.x += offset_true;
        olc::vi2d picNum;
        if (unit.speed.y < 0) {//speed.y < 0 代表朝上跳.
            picNum.x = 1;
            DrawPartialDecal(unit.position, jumpRightDecal.get(),
                              picNum * blockSize + offset, blockSize - olc::vf2d(5, 0));
        }
        else{
            picNum.x = 3;
            DrawPartialDecal(unit.position, jumpRightDecal.get(),
                              picNum * blockSize + offset, blockSize);
        }
    }
    else
    {
        offset.x += offset_false;
        olc::vi2d picNum;
        if (unit.speed.y < 0) {//speed.y < 0 代表朝上跳.
            picNum.x = 3;

            DrawPartialDecal(unit.position, jumpLeftDecal.get(),
                              picNum * blockSize + offset , blockSize - olc::vf2d(10, 0));

        }
        else{
            picNum.x = 1;
            DrawPartialDecal(unit.position, jumpLeftDecal.get(),
                              picNum * blockSize + offset, blockSize - olc::vf2d(10, 0));
        }
    }
}

//站立的动画.
void Example::standDraw(Unit& unit, float offset_true, float offset_false) {
    olc::vf2d offset = {0, 0};
    if(unit.type == Naruto)
    {
        if (unit.face){
            offset.x += offset_true;
            olc::vi2d picNum = { int(unit.stateNum) % 6, 0};
            DrawPartialDecal(unit.position, standDecalOfA.get(),
                             picNum * unit.size + offset, blockSize);
            unit.stateNum += 0.02;
        }
        else{
            offset.x += offset_false;
            olc::vi2d picNum = { int(unit.stateNum) % 6, 0};
            DrawPartialDecal(unit.position, standDecalOfB.get(),
                             picNum * unit.size + offset, blockSize);
            unit.stateNum += 0.02;
        }
    }
    if (unit.type == Sasuke)
    {

        if(unit.face)
        {
            offset.x = 5;
            olc::vi2d picNum = {int(unit.stateNum) % 6, 0};
            DrawPartialDecal(unit.position + olc::vf2d(0, -3),
                             Sasuke_stand_right_D.get(),
                             picNum * unit.size + offset,
                             unit.size,
                             {0.9, 0.9});
            unit.stateNum += 0.01;
        }
        else
        {
            offset.x = -3;
            olc::vi2d picNum = {int(unit.stateNum) % 6, 0};
            DrawPartialDecal(unit.position + olc::vf2d(0, -3),
                             Sasuke_stand_left_D.get(),
                             picNum * unit.size + offset,
                             unit.size,
                             {0.9, 0.9});
            unit.stateNum += 0.01;
        }
    }
}

//奔跑的动画
void Example::runDraw(Unit& unit, float offset_true, float offset_false) {
    olc::vf2d offset = {0, 0};
    if (unit.type == Naruto) {
        if (unit.face)//朝右跑，则脸向右，为真。
        {
            offset.x += offset_true ;
            olc::vi2d picNum = {int(unit.stateNum) % 6, 0};
            DrawPartialDecal(unit.position, runRightDecal.get(),
                             picNum * blockSize + offset,
                             blockSize - olc::vf2d(2, 0));
            unit.stateNum += 0.02;
        } else {
            offset.x += offset_false + 2;
            olc::vi2d picNum = {int(unit.stateNum) % 6, 0};
            DrawPartialDecal(unit.position, runLeftDecal.get(),
                             picNum * blockSize + offset,
                             blockSize - olc::vf2d(1, 0));
            unit.stateNum += 0.02;
        }
    }
    if (unit.type == Sasuke)
    {
        if (unit.face)
        {
            offset.x = 5;
            olc::vi2d picNum = {int(unit.stateNum) % 6, 0};
            DrawPartialDecal(unit.position + olc::vf2d(0, -3),
                             Sasuke_run_right_D.get(),
                             picNum * unit.size + offset,
                             unit.size,
                             {0.9, 0.9});
            unit.stateNum += 0.01;
        }
        else
        {
            offset.x = -3;
            olc::vi2d picNum = {int(unit.stateNum) % 6, 0};
            DrawPartialDecal(unit.position + olc::vf2d(0, -3),
                             Sasuke_run_left_D.get(),
                             picNum * unit.size + offset,
                             unit.size,
                             {0.9, 0.9});
            unit.stateNum += 0.01;
        }
    }
}

void Example::attackDraw(Unit &unit, float offset_true, float offset_false) {
    olc::vf2d offset = {0, 0};
    if (unit.type == Naruto)
    {
        if (unit.face)//向右攻击
        {
            offset.x += offset_true;
            switch(unit.attackNum){
                case 0:
                {
                    offset.x -= 5;
                    int num = 3 - (unit.attackFrames) / 196;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position, attackRightDecal_0.get(),
                                     picNum * blockSize + offset,
                                     blockSize);
                }break;
                case 1:
                {
                    int num = 3 - (unit.attackFrames) / 196;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position, attackRightDecal_1.get(),
                                     picNum * blockSize + offset, blockSize);
                }break;
                case 2:
                {
                    offset.x += 3;
                    int num = 3 - (unit.attackFrames) / 196;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position, attackRightDecal_2.get(),
                                     picNum * blockSize + offset, blockSize);
                }break;
                case 3:
                    offset.x += 5;
                    offset.y += 5;
                    int num = 4 - (unit.attackFrames) / 293;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position, attackRightDecal_3.get(),
                                     picNum * blockSize + offset, blockSize);
            }
        }
        else
        {
            offset.x += offset_false;
            switch(unit.attackNum){
                case 0:
                {
                    offset.x += 7;
                    int num = (unit.attackFrames) / 196;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position, attackLeftDecal_0.get(),
                                     picNum * blockSize + offset,
                                     blockSize - olc::vf2d(2, 0));
                }break;
                case 1:
                {
                    int num = (unit.attackFrames) / 196;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position, attackLeftDecal_1.get(),
                                     picNum * blockSize + offset, blockSize);
                }break;
                case 2:
                {
                    offset.x -= 3;
                    int num = (unit.attackFrames) / 196;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position, attackLeftDecal_2.get(),
                                     picNum * blockSize + offset, blockSize);
                }break;
                case 3:
                    offset.x -= 5;
                    offset.y += 5;
                    int num = (unit.attackFrames) / 293;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position, attackLeftDecal_3.get(),
                                     picNum * blockSize + offset, blockSize);
            }
        }
    }
    if (unit.type == Sasuke)
    {
        if (unit.face)
        {
            offset.x += offset_true;
            switch(unit.attackNum){
                case 0:
                {
                    //单次攻击的frames是700, 一共有4张图
                    int num = 3 - (unit.attackFrames) / 176;
                    offset.x = 5;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position,
                                     Sasuke_attack_0_right_D.get(),
                                     picNum * blockSize + offset,
                                     blockSize,
                                     {0.9, 0.9}
                                     );
                }break;
                case 1:
                {
                    int num = 7 - (unit.attackFrames) / 176;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position, Sasuke_attack_0_right_D.get(),
                                     picNum * blockSize + offset, blockSize,
                                     {0.9, 0.9});
                }break;
                case 2:
                {
                    offset.x = 5;
                    offset.y = -8;
                    int num = 12 - (unit.attackFrames) / 141;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position, Sasuke_attack_0_right_D.get(),
                                     picNum * blockSize + offset,
                                     blockSize + olc::vf2d(-4, 0),
                                     {0.9, 0.9});
                }break;
                case 3:
                    offset.x += 16;
                    offset.y += 5;
                    int num = 4 - (unit.attackFrames) / 211;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position,
                                     Sasuke_attack_1_right_D.get(),
                                     picNum * blockSize + offset,
                                     blockSize + olc::vf2d(-2, 0),
                                     {0.9, 0.9});
            }
        }
        else
        {
            offset.x += offset_true;
            switch(unit.attackNum){
                case 0:
                {
                    //单次攻击的frames是700, 一共有4张图
                    int num = (unit.attackFrames) / 176 + 9;
                    offset.x = 5;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position,
                                     Sasuke_attack_0_left_D.get(),
                                     picNum * blockSize + offset,
                                     blockSize,
                                     {0.9, 0.9}
                    );
                }break;
                case 1:
                {
                    offset.x = 12;
                    int num = (unit.attackFrames) / 176 + 4;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position, Sasuke_attack_0_left_D.get(),
                                     picNum * blockSize + offset, blockSize,
                                     {0.9, 0.9});
                }break;
                case 2:
                {
                    offset.x = 12;
                    int num = (unit.attackFrames) / 141;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position, Sasuke_attack_0_left_D.get(),
                                     picNum * blockSize + offset,
                                     blockSize + olc::vf2d(-4, 0),
                                     {0.9, 0.9});
                }break;
                case 3:
                    offset.x += 1;
                    offset.y += 5;
                    int num = (unit.attackFrames) / 211;
                    olc::vi2d picNum = {num, 0};
                    DrawPartialDecal(unit.position,
                                     Sasuke_attack_1_left_D.get(),
                                     picNum * blockSize + offset,
                                     blockSize + olc::vf2d(-2, 0),
                                     {0.9, 0.9});
            }
        }
    }

}

void Example::hitDraw(Unit &unit, float offset_true, float offset_false) {
    olc::vf2d offset;
    if (unit.type == Naruto)
    {
        if (unit.face){//面向右边时被攻击
            offset.x = offset_true;
            olc::vi2d picNum;
            picNum.x = (unit.hitNum + unit.skillHit) % 2;
            picNum.y = 0;
            DrawPartialDecal(unit.position, hitRightDecal.get(),
                             picNum * blockSize + offset, blockSize);
        }
        else{
            offset.x = offset_false;
            olc::vi2d picNum;
            picNum.x = (unit.hitNum + unit.skillHit) % 2;
            picNum.y = 0;
            DrawPartialDecal(unit.position, hitLeftDecal.get(),
                             picNum * blockSize + offset, blockSize);
        }
    }
    if (unit.type == Sasuke)
    {
        if (unit.face)
        {
            olc::vi2d picNum;
            picNum.x = (unit.hitNum + unit.skillHit) % 2;
            picNum.y = 0;
            offset.y = 10;
            DrawPartialDecal(unit.position,
                             Sasuke_hit_right_D.get(),
                             picNum * blockSize + offset,
                             blockSize);
        }
        else
        {
            olc::vi2d picNum;
            picNum.x = (unit.hitNum + unit.skillHit) % 2;
            picNum.y = 0;
            offset.y = 10;
            DrawPartialDecal(unit.position,
                             Sasuke_hit_left_D.get(),
                             picNum * blockSize + offset,
                             blockSize);
        }
    }
}


void Example::fallDraw(Unit &unit, float offset_true, float offset_false) {
    olc::vf2d offset;
    olc::vi2d picNum = {0, 0};
    if (unit.face){
        offset.x = offset_true;
        if (unit.speed.y != 0)// 还在飞行中
        {
            if (winner == unsettled){
                picNum.x = 0;
            }
            DrawPartialDecal(unit.position, fallRightDecal.get(),
                             picNum * blockSize + offset, blockSize);
        }
        else{
            if (winner == unsettled){
                if (1500 - unit.fallDownFrames < 100) picNum.x = 1;
                if (1500 - unit.fallDownFrames >= 100
                    && 1500 - unit.fallDownFrames <= 1400) picNum.x = 2;
                if (1500 - unit.fallDownFrames >1400 ) picNum.x = 3;
            }
            else{
                if (1500 - unit.fallDownFrames < 100) picNum.x = 1;
                if (1500 - unit.fallDownFrames >= 100) picNum.x = 2;
            }
            DrawPartialDecal(unit.position, fallRightDecal.get(),
                              picNum * blockSize + offset, blockSize);
        }
    }
    else
    {
        offset.x = offset_false;
        offset.x = offset_true;
        if (unit.speed.y != 0)// 还在飞行中
        {
            if (winner == unsettled){
                picNum.x = 3;
            }
            DrawPartialDecal(unit.position, fallLeftDecal.get(),
                              picNum * blockSize + offset, blockSize);
        }
        else{
            if (winner == unsettled){
                if (1500 - unit.fallDownFrames < 100) picNum.x = 2;
                if (1500 - unit.fallDownFrames >= 100
                    && 1500 - unit.fallDownFrames <= 1400) picNum.x = 1;
                if (1500 - unit.fallDownFrames >1400 ) picNum.x = 0;
            }
            else{
                if (1500 - unit.fallDownFrames < 100) picNum.x = 2;
                if (1500 - unit.fallDownFrames >= 100) picNum.x = 1;
            }
            DrawPartialDecal(unit.position, fallLeftDecal.get(),
                              picNum * blockSize + offset, blockSize);
        }
    }
}

//recover进行状态转移。
void Example::recover(Unit& unit) {
    switch (unit.S) {
        case farAttack:{}
        case jump:{}//jump也只能在自身函数内恢复
        case flash:{}break;//闪现状态只能在其自身函数内恢复为stand.
        case run:{
            if ((GetKey(unit.rightKey).bReleased || GetKey(unit.leftKey).bReleased))
                unit.S = stand;
        }break;
        case attack:{
            if (unit.attackFrames <= 0)
            {
                //在天上
                if (unit.acceleration != 0)
                {
                    unit.S = jump;
                    unit.speed.y = 0;
                    unit.attackNum = -1;
                }
                else//在地上.
                {
                    unit.S = stand;
                    unit.attackNum = -1;
                }
            }
            else
            {
                unit.attackFrames--;
            }
        }break;
        case hit:{
            if (unit.hitFrames <= 0)
            {
                //在天上
                if (unit.acceleration != 0)
                {
                    unit.S = jump;
                    unit.speed.y = 0;
                }
                else//在地上.
                {
                    unit.S = stand;
                }
            }
            else
            {
                unit.hitFrames--;
            }
        }break;
        case defend:
        {
            if ((GetKey(unit.downKey).bReleased)) unit.S = stand;
        }break;
        default:{

        }
        break;
    }
}

//角色发动攻击技能
void Example::attackAction(Unit &unit, float fElapsedTime) {
    if (GetKey(unit.attackKey).bPressed && winner == unsettled){
        switch(unit.S)
        {
            case jump:{}
            case farAttack:{}
            case skill_1:{}
            case skill_2:{}
            case skill_3:{}
            case hit:{}
            case fall:{}
            case flash:{}break;
            default:
            {
                //跳跃状态下不进行普攻。
                if (unit.attackFrames <= 200) {
                    //第四次攻击后需要更长的cd
                    unit.S = attack;
                    unit.attackNum = (unit.attackNum + 1) % 4;
                    if (unit.attackNum == 3) unit.attackFrames = 1050;
                    else unit.attackFrames = 700;

                    //攻击时创造伤害区域，维持一定时间。
                    //朝右边攻击
                    if (unit.face){
                        olc::vf2d northwest;
                        northwest.x= unit.position.x- 5;
                        northwest.y = unit.position.y - blockSize.y;
                        hitAreas.push_back(hitArea(northwest, blockSize * olc::vf2d(1.3, 1), 500, unit.side));
                    }
                    else{
                        //朝左边攻击
                        olc::vf2d northwest;
                        northwest.x = unit.position.x - blockSize.x * 1.1;
                        northwest.y = unit.position.y - blockSize.y;
                        hitAreas.push_back(hitArea(northwest, blockSize * olc::vf2d(1.3, 1), 500, unit.side));
                    }
                }
            }
        }

    }
}



void Example::hitAction(Unit &unit, float fElapsedTime) {
    //如果角色处于hitArea中，则会收到伤害, 然后这个area自动消亡。
    for(int i = 0; i < hitAreas.size(); i++) {
        if (hitAreas[i].inArea(unit) && unit.side != hitAreas[i].side && unit.S != fall
            && unit.S != defend){
            unit.S = hit;

            unit.hitFrames = 1500;
            unit.lives -= 5;
            unit.hitNum++;
            hitAreas[i].existence = false;
            play(hitSound);

            //被攻击成功后双方都会增加查克拉.
            Unit* oppoent = units[unit.oppoentNum];
            if (unit.chakra < 300) unit.chakra += 5;
            else unit.chakra = 300;
            if (oppoent->chakra < 300) oppoent->chakra += 3;
            else oppoent->chakra = 300;

        }if (unit.S == defend){
            //防御状态下击中同样会增加查克拉,但是更少.而对方仍增加10.
            Unit* oppoent = units[unit.oppoentNum];
            if (unit.chakra < 300) unit.chakra += 5;
            else unit.chakra = 300;
            if (oppoent->chakra < 300) oppoent->chakra += 3;
            else oppoent->chakra = 300;
            hitAreas[i].existence = false;
            unit.lives -= 1;
        }
    }
    if (unit.S == hit){
        //如果3秒之内连续收到四次攻击，则会被击飞。然后firstHitTime和hitNum重置
        unit.skill_1_Frames = 0;
        unit.skill_2_Frames = 0;
        unit.skill_3_Frames = 0;

        Unit* oppoent = units[unit.oppoentNum];
        if (oppoent->attackNum == 3)
        {
            play(NarutoHitSound);
            unit.S = fall;
            unit.hitNum = 0;
            unit.speed.y = -400;
            unit.acceleration = 500;
        }
    }
}

//被动状态,击飞.
void Example::fallAction(Unit &unit, float fElapsedTime) {
    if (unit.S == fall){
        unit.skill_1_Frames = 0;
        unit.skill_2_Frames = 0;
        unit.skill_3_Frames = 0;
        //竖直方向的飞行无关朝向，fall时间等于飞行时间加上躺在地上的时间。飞行的逻辑和jump一样
        if ((unit.position.y + unit.speed.y * fElapsedTime) < floorPos-blockSize.y + 15){
            unit.position.y += unit.speed.y * fElapsedTime;
            unit.speed.y += unit.acceleration * fElapsedTime;
        }
        else
        {
            if (unit.position.y < floorPos-blockSize.y + 15){//不等于地板高度代表着第一次到地面。
                unit.position.y = floorPos - blockSize.y + 15;
                unit.speed.y = 0;
                unit.fallDownFrames = 1500;
            }
            else{
                //落地之后继续躺1.5s, 状态出口。
                if (unit.fallDownFrames <= 0 && winner == unsettled)
                {
                    unit.S = stand;
                }
                else
                {
                    unit.fallDownFrames--;
                }
            }
        }
        //还在空中飞的过程中才会移动。
        if (unit.speed.y != 0){
            if (unit.face)//面向右边，则朝左边飞，X坐标减小
            {
                float futurePos = unit.position.x - unit.speed.x * fElapsedTime;
                if (inBound(!unit.face, futurePos)) unit.position.x = futurePos;
                else unit.position.x = 0;
            }
            else{//面向左边，则朝右飞， X坐标增大
                float futurePos = unit.position.x + unit.speed.x * fElapsedTime;//以4倍的速度飞行
                if (inBound(!unit.face, futurePos)) unit.position.x = futurePos;
                else unit.position.x = ScreenWidth() - blockSize.x;
            }
        }

        //如果被击飞,则将其主动维持的frames清零.
        unit.skill_1_Frames = 0;
        unit.skill_2_Frames = 0;
    }
}

//判断角色是否处于area中
bool Area::inArea(Unit u) {
    float left = northwest.x;
    float right = northwest.x + size.x;
    float upper = northwest.y;
    float floor = northwest.y + size.y;
    return (u.position.x >= left && u.position.x <= right
            && u.position.y >= upper && u.position.y <= floor);
}

//删除经过这个循环后不存在的area
void Example::removeDeadArea() {
    for(int i = 0; i < hitAreas.size(); i++){
        if (clock() - hitAreas[i].startTime > hitAreas[i].duration) hitAreas[i].existence = false;
    }
    hitAreas.erase(
            std::remove_if(hitAreas.begin(), hitAreas.end(), [](const hitArea& hArea) { return !hArea.existence; }),
            hitAreas.end());
    unitAreas.erase(
            std::remove_if(unitAreas.begin(), unitAreas.end(), [](const unitArea& uArea) { return !uArea.existence; }),
            unitAreas.end());
}

bool Example::inBound(bool moveDirection, float positionX) {
    if (moveDirection)
        return positionX <= ScreenWidth() - blockSize.x;
    else
        return positionX >= 0;
}

void Example::gameOver(){
    if (winner == unsettled)
    {
        if (unitA.lives <= 0)
        {
            unitA.speed.y = -100;
            unitA.acceleration = 500;
            unitA.S = fall;
            winner = playerB;
            play(ggSound);
        }
        if (unitB.lives <= 0)
        {
            unitB.speed.y = -100;
            unitB.acceleration = 500;
            unitB.S = fall;
            winner = playerA;
            play(ggSound);
        }
        if (unitA.lives <= 0 && unitB.lives <= 0)
        {
            unitA.speed.y = -100;
            unitA.acceleration = 500;
            unitA.S = fall;
            unitB.speed.y = -100;
            unitB.acceleration = 500;
            unitB.S = fall;
            winner = draw;
            play(ggSound);
        }
    }
}

void Example::drawSignal(Unit& unit) {
    olc::vf2d posOfSignal;
    posOfSignal.x = unit.position.x - blockSize.x;
    posOfSignal.y = unit.position.y + blockSize.y;
    if (unit.side) DrawDecal(posOfSignal, playerADecal.get());
    else DrawDecal(posOfSignal, playerBDecal.get());
}

void Example::drawLivesBar(float fElapsedTime) {
    posOfLivesBarA.x = 0;
    posOfLivesBarA.y = 15;
    posOfLivesBarB.x = ScreenWidth() - 341;
    posOfLivesBarB.y = 15;
    //红色血条会逐渐变短
    livesRedBarSizeA.x = barRedLenOfA;
    livesRedBarSizeB.x = barRedLenOfB;
    //绿色血条瞬间变短
    livesGreenBarSizeA.x = 330 * unitA.lives / 200;
    livesGreenBarSizeB.x = 330 * unitB.lives / 200;

    livesRedBarSizeA.y = 20;
    livesRedBarSizeB.y = 20;
    livesGreenBarSizeA.y = 20;
    livesGreenBarSizeB.y = 20;

    DrawDecal(posOfLivesBarA, livesBarADecal.get());
    DrawDecal(posOfLivesBarB, livesBarBDecal.get());

    FillRectDecal(olc::vf2d(posOfLivesBarA.x, posOfLivesBarA.y + 30) , livesRedBarSizeA, olc::RED);
    FillRectDecal(olc::vf2d(ScreenWidth() - livesRedBarSizeB.x, posOfLivesBarB.y + 30), livesRedBarSizeB, olc::RED);
    FillRectDecal(olc::vf2d(posOfLivesBarA.x, posOfLivesBarA.y + 30) , livesGreenBarSizeA, olc::GREEN);
    FillRectDecal(olc::vf2d(ScreenWidth() - livesGreenBarSizeB.x, posOfLivesBarB.y + 30), livesGreenBarSizeB, olc::GREEN);
}


//根据状态移动角色
void Example::moveUnit(Unit &unit, float fElapsedTime) {
    Unit oppoent;
    if (unit.side) oppoent = unitB;
    else oppoent = unitA;
    switch(unit.S){
        case attack: {
            if (oppoent.S != defend){
                if (unit.face) {
                    if(unit.position.x + unit.speed.x * 0.1 * fElapsedTime <= ScreenWidth() - blockSize.x)
                        unit.position.x += 0.2 * unit.speed.x * fElapsedTime;
                } else {
                    if(unit.position.x - unit.speed.x * 0.1 * fElapsedTime >= 0)
                        unit.position.x -= 0.2 * unit.speed.x * fElapsedTime;
                }
            }

        }break;
        case hit: {
//            if (unit.face){
//                if (unit.position.x - unit.speed.x * 0.2 * fElapsedTime >= 0)
//                    unit.position.x -= unit.speed.x * 0.2 * fElapsedTime;
//            }else{
//                if (unit.position.x + unit.speed.x * 0.2 * fElapsedTime <= ScreenWidth() - blockSize.x)
//                    unit.position.x += unit.speed.x * 0.2 * fElapsedTime;
//            }break;
        }
    }
}

//防御
void Example::defendAction(Unit &unit, float fElapsedTime) {
    if (GetKey(unit.downKey).bHeld && winner == unsettled){
        switch(unit.S){
            //攻击、跳跃、被攻击、击飞时不能通过按键改变状态。
            case skill_1:
            case skill_2:
            case skill_3:
            case flash:{}
            case farAttack:{}
            case attack:{}
            case jump:{}
            case fall:{}
            case hit:{}break;
            default: unit.S = defend;
        }
    }
}

void Example::defendDraw(Unit &unit, float offset_true, float offset_false) {
    olc::vf2d offset(0, 0);
    if (unit.face){//面向右边防御
        offset.x = offset_true;
        DrawDecal(unit.position, defendRightDecal.get(), {1.1, 0.9});
    }
    else
    {
        offset.x = offset_false;
        DrawDecal(unit.position, defendLeftDecal.get(), {1.1, 0.9});
    }
}
//当在跑动或者跳跃,且有方向键按住时,或者在攻击时可以判断在运动.
bool Example::isMoving(Unit &unit) {
    return (unit.S == run || unit.S == jump)
            && (GetKey(unit.rightKey).bHeld ||GetKey(unit.leftKey).bHeld)
            || unit.S == attack;
}

void Example::runAction(Unit &unit, float fElapsedTime) {
    //右跑
    if (GetKey(unit.rightKey).bHeld && winner == unsettled){
        switch (unit.S) {
            case skill_1:
            case skill_2:
            case skill_3:
            case farAttack:
            case flash:
            case defend:
            case fall:
            case hit:
            case attack: break;
            case jump:
            default: {
                if (!GetKey(unit.leftKey).bHeld){
                    if (unit.S != jump) unit.S = run;
                    unit.moveFlag = true;
                    unit.face = true;
                    float futurePos = unit.position.x + unit.speed.x * fElapsedTime;
                    //没有被阻挡
                    if (!isBlocked(unit, futurePos)){
                        if (futurePos <= ScreenWidth() - blockSize.x)
                            //右边不能过右界限
                            unit.position.x = futurePos;
                    }
                    else{//被阻挡
                        //迎面相撞
                        unitArea oppoentArea = unitAreas[unit.oppoentNum];
                        if (oppoentArea.moveFlag && oppoentArea.moveDirection != unit.face){
                            //该角色不动
                        }
                        //该角色撞击对面角色, 对面角色没有走路的意思
                        if (!oppoentArea.moveFlag){
                            //该角色减速, 对面角色被推着.
                            futurePos = unit.position.x + unit.speed.x * fElapsedTime * 0.5;
                            float futurePosOfOppent;

                            if (unit.side){//此时unit为A
                                futurePosOfOppent = unitB.position.x + unit.speed.x * fElapsedTime * 0.5;
                                //该角色运动,但人物图像不能重合
                                unitA.position.x = futurePos;
                                //对手运动,但不能过右边界
                                if (futurePosOfOppent <= ScreenWidth() - blockSize.x)
                                    unitB.position.x = futurePosOfOppent;
                            }
                            else{
                                //此时该角色为B
                                futurePosOfOppent = unitA.position.x + unit.speed.x * fElapsedTime * 0.5;
                                //该角色运动,但人物图像不能重合
                                unitB.position.x = futurePos;
                                //对手运动,但不能过右边界
                                if (futurePosOfOppent <= ScreenWidth() - blockSize.x)
                                    unitA.position.x = futurePosOfOppent;
                            }
                        }
                    }
                }
                else
                {
                    if (unit.acceleration != 0) unit.S = jump;
                    else unit.S = stand;
                }
            }
        }
    }

    //角色左跑
    if (GetKey(unit.leftKey).bHeld && winner == unsettled){
        switch (unit.S) {
            case skill_1:
            case skill_2:
            case skill_3:
            case farAttack:
            case flash:
            case defend:
            case fall:
            case hit:
            case attack: break;
            case jump:
            default:{
                //两个键同时按,则状态出口为stand
                if (!GetKey(unit.rightKey).bHeld){
                    if (unit.S != jump) unit.S = run;
                    unit.moveFlag = true;
                    unit.face = false;
                    float futurePos = unit.position.x - unit.speed.x * fElapsedTime;
                    //没有被阻挡
                    if (!isBlocked(unit, futurePos)){
                        if (futurePos >= 0)
                            //左跑不能过左边界
                            unit.position.x = futurePos;
                    }
                    else{//被阻挡
                        //迎面相撞
                        unitArea oppoentArea = unitAreas[unit.oppoentNum];
                        if (oppoentArea.moveFlag && oppoentArea.moveDirection != unit.face){
                            //该角色不动
                        }
                        //该角色撞击对面角色, 对面角色没有走路的意思
                        if (!oppoentArea.moveFlag){
                            //该角色减速, 对面角色被推着.
                            futurePos = unit.position.x - unit.speed.x * fElapsedTime * 0.5;
                            float futurePosOfOppent;

                            if (unit.side){//此时unit为A
                                futurePosOfOppent = unitB.position.x - unit.speed.x * fElapsedTime * 0.5;
                                //该角色运动,但人物图像不能重合
                                unitA.position.x = futurePos;
                                //对手运动,但不能过右边界
                                if (futurePosOfOppent >= 0)
                                    unitB.position.x = futurePosOfOppent;
                            }
                            else{
                                //此时该角色为B
                                futurePosOfOppent = unitA.position.x - unit.speed.x * fElapsedTime * 0.5;
                                //该角色运动,但人物图像不能重合
                                unitB.position.x = futurePos;
                                //对手运动,但不能过右边界
                                if (futurePosOfOppent >= 0)
                                    unitA.position.x = futurePosOfOppent;
                            }
                        }
                    }
                }
                else
                {
                    if (unit.acceleration != 0) unit.S = jump;
                    else unit.S = stand;
                }
            }break;
        }
    }
}

//判断主动运动过程中是否被对方阻挡.
bool Example::isBlocked(Unit& unit, float futurePos) {
    int oppoentNum;
    switch(unit.side){
        case true: oppoentNum = 1;break;
        case false: oppoentNum = 0;break;
    }

    unitArea oppoentArea = unitAreas[oppoentNum];

    if (unit.face){//向右面主动运动时被阻挡.
        return (unit.position.y - oppoentArea.northwest.y <= blockSize.y * 0.75
            &&  oppoentArea.northwest.y - unit.position.y <= blockSize.y * 0.75
            &&  oppoentArea.northwest.x - futurePos <= blockSize.x * 0.9
            &&  oppoentArea.northwest.x - futurePos >= blockSize.x * 0.8);
    }else{
        return (unit.position.y - oppoentArea.northwest.y <= blockSize.y * 0.75
                &&  oppoentArea.northwest.y - unit.position.y <= blockSize.y * 0.75
                &&  futurePos - oppoentArea.northwest.x <= blockSize.x * 0.9
                &&  futurePos - oppoentArea.northwest.x >= blockSize.x * 0.8);
    }
}

void Example::collision(float fElapsedTime) {

    //当两者相距非常近的时候
    //A在B的右侧时
    if ((unitA.position.x - unitB.position.x) <= blockSize.x
     &&  unitA.position.x >= unitB.position.x
     &&  abs(unitA.position.y - unitB.position.y) <= blockSize.y * 0.75){
        float futurePosOfA = unitA.position.x + unitA.speed.x * 0.5 * fElapsedTime;
        if (futurePosOfA <= ScreenWidth() - blockSize.x){
            //不能碰到边界
            unitA.position.x = futurePosOfA;
        }
        float futurePosOfB = unitB.position.x - unitB.speed.x * 0.5 * fElapsedTime;
        if (futurePosOfB >= 0){
            //不能碰到边界
            unitB.position.x = futurePosOfB;
        }
    }

    //B在A的右侧
    if ((unitB.position.x - unitA.position.x) <= blockSize.x
        &&  unitB.position.x >= unitA.position.x
        &&  abs(unitA.position.y - unitB.position.y) <= blockSize.y * 0.75){
        float futurePosOfA = unitB.position.x + unitB.speed.x * fElapsedTime * 0.5;
        if (futurePosOfA <= ScreenWidth() - blockSize.x){
            //不能碰到边界
            unitB.position.x = futurePosOfA;
        }
        float futurePosOfB = unitA.position.x - unitA.speed.x * fElapsedTime * 0.5;
        if (futurePosOfB >= 0){
            //不能碰到边界
            unitA.position.x = futurePosOfB;
        }
    }
}

void Example::jumpAction(Unit &unit, float fElapsedTime) {
    //静止时的跳跃, 按下K键的瞬间获得一个极大的冲量。
    //A角色起跳用K键控制，跳跃最多可以二段跳。
    if (GetKey(unit.upKey).bPressed && winner == unsettled){
        switch(unit.S){
            case skill_1:
            case skill_2:
            case skill_3:
            case farAttack:
            case flash:
            case hit:
            case fall:break;
            case jump:{
                if(unit.canDoubleJump)
                {
                    unit.speed.y = -400;
                    unit.canDoubleJump = false;
                }
            }break;
            default:{
                unit.S = jump;
                unit.speed.y = -400;
            }
        }
    }

    //落体过程。
    if (unit.S == jump) {
        unit.acceleration = 500;
        if ((unit.position.y + unit.speed.y * fElapsedTime) <= floorPos-blockSize.y + 15){
            unit.position.y += unit.speed.y * fElapsedTime;
            unit.speed.y += unit.acceleration * fElapsedTime;
        }
        else
        {
            unit.position.y = floorPos-blockSize.y + 15;
            unit.speed.y = 0;
            unit.acceleration = 0;
            unit.S = stand;
            unit.canDoubleJump = true;

            //落地之后可以刷新远攻.

        }
    }
}

void Example::flashAction(Unit &unit, float fElapsedTime) {
    if(GetKey(unit.flashKey).bReleased && winner == unsettled){
        switch(unit.S){
            //从这里到default都为空,代表着这些状态都不能直接到flash
            case skill_1:
            case skill_2:
            case skill_3:
            case farAttack:{}
            case hit:{}
            case attack:{}
            case defend:{}
            case fall: {}
            case flash:{}break;
            case jump:
            default:{
                unit.S = flash;
                unit.flashFrames += 300;
                unit.speed.y = 0;
                if (unit.face){
                    float futurePos = unit.position.x + 150;
                    if (futurePos <= ScreenWidth() - blockSize.x){
                        unit.position.x = futurePos;
                    }
                    else{
                        unit.position.x = ScreenWidth() - blockSize.x;
                    }
                }
                else{
                    float futurePos = unit.position.x - 150;
                    if (futurePos >= 0){
                        unit.position.x = futurePos;
                    }
                    else{
                        unit.position.x = 0;
                    }
                }
            }
        }

    }

    //每次刷新扣一, 归零时回到stand.
    if (unit.S == flash){
        unit.flashFrames--;
        if (unit.flashFrames <= 0){
            if (unit.acceleration != 0) {
                unit.S = jump;
            }else{
                unit.S = stand;
            }
        }
    }
}

void Example::flashDraw(Unit &unit, float offset_true, float offset_false) {
    if (unit.face){
        DrawDecal(unit.position, flashRightDecal.get(), {1.1, 0.9});
    }
    else{
        DrawDecal(unit.position, flashLeftDecal.get(), {1.1, 0.9});
    }
}

//远攻,除非击飞和僵直,其余主动状态都可以转位远攻状态且释放手里剑.
//但有cd,在一定时间内不能再放远攻且保持该状态.
void Example::farAttackAction(Unit &unit, float fElapsedTime) {

    if (GetKey(unit.farAttackKey).bPressed && winner == unsettled){
        switch(unit.S)
        {
            //不可进行转移的状态.
            case defend:
            case jump:
            case attack:
            case flash:
            case farAttack:
            case skill_1:
            case skill_2:
            case skill_3:
            case hit:
            case fall:break;

            //可以进行转移的状态.
            case stand:
            case run:
            default:{
                //成功进行攻击
                if (unit.farAttackFrames == 0){
                    olc::vf2d offset(0, 0);
                    if (unit.face) offset.x = blockSize.x;
                    else offset.x = - blockSize.x;
                    unit.S = farAttack;
                    if(unit.chakra < 300) unit.chakra += 5;

                    items.push_back(
                            std::make_shared<shuriken>(unit.position + offset,
                                     unit.side, unit.face,
                                     olc::vf2d(51, 97), true)
                    );
                    unit.farAttackFrames = 600;//cd为600帧

                }
            }
        }
    }
    //自动恢复的过程.只能从这里改变farAttack的状态,其余的不能改变farAttack的状态
    if (unit.S == farAttack){
        unit.farAttackFrames--;
        if (unit.farAttackFrames <= 0){
            unit.farAttackFrames = 0;
            unit.S = stand;
        }
    }
}

//远攻的图像函数
void Example::farAttackDraw(Unit &unit, float offset_true, float offset_false) {
    //根据留存的farAttackFrames决定该画哪张图像.
    int picNum;
    if (unit.farAttackFrames >= 400){
        picNum = 0;
    }
    else{
        if (unit.farAttackFrames >= 200)
            picNum = 1;
        else picNum = 2;
    }

    if (unit.face){
        switch(picNum){
            case 0:
                DrawDecal(unit.position, farAttackRightDecal_0.get(),
                    {1.1, 0.9});break;
            case 1:
                DrawDecal(unit.position, farAttackRightDecal_1.get(),
                          {0.99, 0.9});break;
            case 2:
                DrawDecal(unit.position, farAttackRightDecal_2.get(),
                          {1.1, 0.9});break;
        }
    }
    else{
        switch(picNum) {
            case 0:
                DrawDecal(unit.position, farAttackLeftDecal_0.get(),
                          {1.1, 0.9});
                break;
            case 1:
                DrawDecal(unit.position, farAttackLeftDecal_1.get(),
                          {0.99, 0.9});
                break;
            case 2:
                DrawDecal(unit.position, farAttackLeftDecal_2.get(),
                          {1.1, 0.9});
                break;
        }
    }
}

void Example::itemDraw() {
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->tp == shurikenItem) {
            DrawDecal(items[i]->position, shurikenDecal.get());
        }
    }
}

void Example::removeDeadItem() {
    items.erase(
            std::remove_if(items.begin(), items.end(), [](const std::shared_ptr<Item>& itm) { return !itm->existence; }),
            items.end());
}

void Example::item_moveAndEffect(float fElapsedTime) {
    for (int i = 0; i < items.size(); i++) {
        items[i]->move(fElapsedTime);
        Unit* opponent;
        Unit* unit;
        if (items[i]->side){
            opponent = &unitB;
            unit = &unitA;
        }

        else{
            opponent = &unitA;
            unit = &unitA;
        }

        items[i]->effect(unit, opponent);

    }
}

void Example::chakraDraw(Unit *unit) {
    unit->chakraBarLen = (int(unit->chakra) % 100) / 100.0 * 200;
    unit->chakraColor = unit->chakra / 100;
    olc::vf2d chakraBarSize(unit->chakraBarLen, 7);


    if (unit->side){
        switch(unit->chakraColor){
            case 0:{
                //蓝色
                FillRectDecal(olc::vf2d(posOfLivesBarA.x, posOfLivesBarA.y + 54),
                              chakraBarSize, olc::BLUE);

            }break;
            case 1:
            {
                FillRectDecal(olc::vf2d(posOfLivesBarA.x, posOfLivesBarA.y + 54),
                              {200, 7}, olc::BLUE);
                FillRectDecal(olc::vf2d(posOfLivesBarA.x, posOfLivesBarA.y + 54),
                              chakraBarSize, olc::YELLOW);
            }break;
            //黄色
            case 2:
            {
                FillRectDecal(olc::vf2d(posOfLivesBarA.x, posOfLivesBarA.y + 54),
                              {200, 7}, olc::YELLOW);
                FillRectDecal(olc::vf2d(posOfLivesBarA.x, posOfLivesBarA.y + 54),
                              chakraBarSize, olc::RED);
            }break;
            //红色
            case 3:{
                FillRectDecal(olc::vf2d(posOfLivesBarA.x, posOfLivesBarA.y + 54),
                              {200, 7}, olc::RED);
            }break;//红
        }
    }
    else{
        switch(unit->chakraColor) {
            case 0: {
                //蓝色
                FillRectDecal(olc::vf2d(ScreenWidth() - unit->chakraBarLen, posOfLivesBarB.y + 54),
                              chakraBarSize, olc::BLUE);

            }
                break;
            case 1: {
                FillRectDecal(olc::vf2d(ScreenWidth() - 200, posOfLivesBarB.y + 54),
                              {200, 7}, olc::BLUE);
                FillRectDecal(olc::vf2d(ScreenWidth() - unit->chakraBarLen, posOfLivesBarB.y + 54),
                              chakraBarSize, olc::YELLOW);
            }break;
            //黄色
            case 2: {
                FillRectDecal(olc::vf2d(ScreenWidth() - 200, posOfLivesBarB.y + 54),
                              {200, 7}, olc::YELLOW);
                FillRectDecal(olc::vf2d(ScreenWidth() - unit->chakraBarLen, posOfLivesBarB.y + 54),
                              chakraBarSize, olc::RED);
            }break;
            //红色
            case 3: {
                FillRectDecal(olc::vf2d(ScreenWidth() - 200, posOfLivesBarB.y + 54),
                              {200, 7}, olc::RED);
            }
                break;//红
        }
    }
}

void Example::skill_1_Action(Unit &unit, float fElapsedTime) {
    if (GetKey(unit.skillKey).bPressed && winner == unsettled){
        switch(unit.S)
        {
            case defend:
            case jump:
            case attack:
            case flash:
            case farAttack:
            case skill_1:
            case skill_2:
            case skill_3:
            case hit:
            case fall:break;
            case stand:
            case run:
            default:
            {

                if (unit.chakra >= 100)
                {
                    unit.chakra -= 100;
                    unit.S = skill_1;
                    unit.skill_1_Frames = 1150;
                }
            }
        }
    }

    //技能状态一前0.6s召唤分身搓螺旋丸,后0.6s开始攻击判定.
    if (unit.S == skill_1)
    {
        if (unit.skill_1_Frames <= 700){
            //移动.
            if (unit.face)
            {
                float futurePos = unit.position.x + unit.speed.x * 1.2 * fElapsedTime;
                if (futurePos <= ScreenWidth() - blockSize.x) unit.position.x = futurePos;
                else unit.position.x = ScreenWidth() - blockSize.x;
            }
            else
            {
                float futurePos = unit.position.x - unit.speed.x * 1.2 * fElapsedTime;
                if (futurePos >= 0) unit.position.x = futurePos;
                else unit.position.x = 0;
            }

            Unit* oppoent = units[unit.oppoentNum];
            //如果击中对方,则自身进入状态二,敌方受到伤害.
            if (skillHit(&unit, oppoent))
            {
                unit.skill_1_Frames = 0;
                unit.S = skill_2;
                unit.skill_2_Frames = 1200;
                return;
            }
        }

        //持续时间减一.
        if (unit.skill_1_Frames <= 0)
        {
            unit.S = skill_3;
            unit.skill_3_Frames = 400;
        }
        else unit.skill_1_Frames--;
    }
}

//技能第二阶段,每隔0.25s,检查一次,造成伤害.
void Example::skill_2_Action(Unit &unit, float fElapsedTime) {
    if (unit.S == skill_2)
    {
        Unit* oppoent = units[unit.oppoentNum];
        switch(unit.skill_2_Frames)
        {
            case 1200:
            case 900:
            case 600:
            case 300:{
                //每次造成伤害前检查是否击中角色.
                if (skillHit(&unit, oppoent))
                {
                    if(oppoent->S != defend)
                    {

                        oppoent->S = hit;
                        oppoent->skillHit++;
                        oppoent->lives -= 8;
                        oppoent->hitFrames = 500;
                        play(hitSound);
                    }
                    else
                    {
                        oppoent->lives -= 3;
                        play(hitSound);
                    }
                }
            }break;

            case 0:
            {
                if (skillHit(&unit, oppoent))
                {
                    //被防御住了
                    if(oppoent->S != defend)
                    {
                        oppoent->S = fall;
                        oppoent->speed.y = -400;
                        oppoent->acceleration = 500;
                        play(hitSound);
                        play(NarutoHitSound);
                    }
                    else
                    {
                        oppoent->lives -= 3;
                        play(hitSound);
                    }
                }
            }break;

            default:{}break;
        }

        //自然状态下,帧时间归零时状态恢复stand.
        if (unit.skill_2_Frames <= 0)
        {
            unit.S = skill_3;
            unit.skill_3_Frames = 400;
        }
        else unit.skill_2_Frames--;
    }
}

bool Example::skillHit(Unit* unit, Unit* oppoent) {
    return (oppoent->position.x <= unit->position.x + blockSize.x * 1.05
        &&  oppoent->position.x >= unit->position.x - blockSize.x * 1.05
        &&  abs(oppoent->position.y - unit->position.y) < blockSize.y * 0.5);
}

void Example::skill_1_Draw(Unit &unit, float offset_true, float offset_false) {
    olc::vf2d offset(0, 0);
    if (unit.face)
    {
        offset.x = offset_true;

        if (unit.skill_1_Frames >= 700)
        {
            int picNum = (unit.skill_1_Frames - 700) / 50;
            switch(picNum) {
                case 9: {
                }
                case 8: {
                    offset.x = -blockSize.x;
                    offset.y = 3;
                    DrawDecal(unit.position + offset,
                              skill_1_right_0_D.get(),
                              {0.8, 0.8});
                }
                    break;
                case 7: {
                    offset.x = -blockSize.x - 1;
                    offset.y = 3;
                    DrawDecal(unit.position + offset,
                              skill_1_right_1_D.get(),
                              {0.8, 0.8});
                }
                    break;
                case 6: {
                    offset.x = -blockSize.x - 1;
                    offset.y = -2;
                    DrawDecal(unit.position + offset,
                              skill_1_right_2_D.get(),
                              {0.8, 0.8});
                }
                    break;
                case 5: {
                    offset.x = -blockSize.x;
                    offset.y = -2;
                    DrawDecal(unit.position + offset,
                              skill_1_right_3_D.get(),
                              {0.8, 0.8});
                }
                    break;
                case 4: {
                    offset.x = -blockSize.x;
                    offset.y = -16;
                    DrawDecal(unit.position + offset,
                              skill_1_right_4_D.get(),
                              {0.9, 0.9});
                }
                    break;
                case 3: {
                    offset.x = -blockSize.x + 1;
                    offset.y = 5;
                    DrawDecal(unit.position + offset,
                              skill_1_right_5_D.get(),
                              {0.8, 0.80});
                }
                    break;
                case 2: {
                    offset.x = -blockSize.x + 1;
                    offset.y = 5;
                    DrawDecal(unit.position + offset,
                              skill_1_right_6_D.get(),
                              {0.8, 0.8});
                }
                    break;
                case 1: {
                    offset.x = -blockSize.x + 2;
                    offset.y = 7;
                    DrawDecal(unit.position + offset,
                              skill_1_right_7_D.get(), {0.8, 0.8});
                }
                    break;
                case 0: {
                    offset.x = -blockSize.x + 1;
                    offset.y = 5;
                    DrawDecal(unit.position + offset,
                              skill_1_right_8_D.get(), {0.8, 0.8});
                }
                    break;
            }
        }

        else
        {
            //此时开始移动.
            if ((unit.skill_1_Frames / 50) % 2 == 1)
            {
                offset.x = -blockSize.x * 1.2;
                offset.y = 7;
                DrawDecal(unit.position + offset,
                          skill_1_right_9_D.get(),
                          {0.8, 0.8});
            }
            else
            {
                offset.x = -blockSize.x * 1.2;
                offset.y = 7;
                DrawDecal(unit.position + offset,
                          skill_1_right_10_D.get(),
                          {0.8, 0.8});
            }
        }
    }
    else
    {
        offset.x = offset_false;
        if (unit.skill_1_Frames >= 700)
        {
            int picNum = (unit.skill_1_Frames - 700) / 50;
            switch(picNum) {
                case 9: {
                }
                case 8: {
                    offset.x = -blockSize.x;
                    offset.y = 3;
                    DrawDecal(unit.position + offset,
                              skill_1_left_0_D.get(),
                              {0.8, 0.8});
                }
                    break;
                case 7: {
                    offset.x = -blockSize.x - 1;
                    offset.y = 3;
                    DrawDecal(unit.position + offset,
                              skill_1_left_1_D.get(),
                              {0.8, 0.8});
                }
                    break;
                case 6: {
                    offset.x = -blockSize.x - 1;
                    offset.y = -2;
                    DrawDecal(unit.position + offset,
                              skill_1_left_2_D.get(),
                              {0.8, 0.8});
                }
                    break;
                case 5: {
                    offset.x = -blockSize.x;
                    offset.y = -2;
                    DrawDecal(unit.position + offset,
                              skill_1_left_3_D.get(),
                              {0.8, 0.8});
                }
                    break;
                case 4: {
                    offset.x = -blockSize.x;
                    offset.y = -16;
                    DrawDecal(unit.position + offset,
                              skill_1_left_4_D.get(),
                              {0.9, 0.9});
                }
                    break;
                case 3: {
                    offset.x = -blockSize.x + 1;
                    offset.y = 5;
                    DrawDecal(unit.position + offset,
                              skill_1_left_5_D.get(),
                              {0.8, 0.80});
                }
                    break;
                case 2: {
                    offset.x = -blockSize.x + 1;
                    offset.y = 5;
                    DrawDecal(unit.position + offset,
                              skill_1_left_6_D.get(),
                              {0.8, 0.8});
                }
                    break;
                case 1: {
                    offset.x = -blockSize.x + 2;
                    offset.y = 7;
                    DrawDecal(unit.position + offset,
                              skill_1_left_7_D.get(), {0.8, 0.8});
                }
                    break;
                case 0: {
                    offset.x = -blockSize.x + 1;
                    offset.y = 5;
                    DrawDecal(unit.position + offset,
                              skill_1_left_8_D.get(), {0.8, 0.8});
                }
                    break;
            }
        }

        else
        {
            //此时开始移动.
            //用奇数和偶数逻辑交替render两张图片实现螺旋丸的闪烁.
            if ((unit.skill_1_Frames / 50) % 2 == 1)
            {
                offset.x = -blockSize.x * 1.2;
                offset.y = 7;
                DrawDecal(unit.position + offset,
                          skill_1_left_9_D.get(),
                          {0.8, 0.8});
            }
            else
            {
                offset.x = -blockSize.x * 1.2;
                offset.y = 7;
                DrawDecal(unit.position + offset,
                          skill_1_left_10_D.get(),
                          {0.8, 0.8});
            }
        }
    }
}

void Example::skill_3_Action(Unit &unit, float fElapsedTime) {
    if (unit.S == skill_3)
    {
        //stand即代表自由状态.
        if (unit.skill_3_Frames <= 0) unit.S = stand;
        else unit.skill_3_Frames--;
    }
}

void Example::skill_3_Draw(Unit &unit, float offset_true, float offset_false) {
    olc::vf2d offset(0, 0);
    if (unit.face)
    {
        //总的frames是400.
        int picNum = unit.skill_3_Frames / 100;
        switch(picNum)
        {
            case 4:
            case 3:
            {
                offset.x = -blockSize.x * 0.4;
                offset.y = 8;
                DrawDecal(unit.position + offset,
                          skill_3_right_0_D.get(),
                          {0.8, 0.8});
            }break;
            case 2:
            {
                offset.x = -blockSize.x * 0.4;
                offset.y = 8;
                DrawDecal(unit.position + offset,
                          skill_3_right_1_D.get(),
                          {0.8, 0.8});
            }break;
            case 1:
            {
                offset.x = -blockSize.x * 0.3;
                offset.y = -3;
                DrawDecal(unit.position + offset,
                          skill_3_right_2_D.get(),
                          {0.9, 0.9});
            }break;
            case 0:
            {
                offset.x = -blockSize.x * 0.3;
                offset.y = -3;
                DrawDecal(unit.position + offset,
                          skill_3_right_3_D.get(),
                          {0.9, 0.9});
            }break;
        }
    }
    else
    {
        //总的frames是400.
        int picNum = unit.skill_3_Frames / 100;
        switch(picNum)
        {
            case 4:
            case 3:
            {
                offset.x = blockSize.x * 0.4;
                offset.y = 8;
                DrawDecal(unit.position + offset,
                          skill_3_right_0_D.get(),
                          {0.8, 0.8});
            }break;
            case 2:
            {
                offset.x = blockSize.x * 0.4;
                offset.y = 8;
                DrawDecal(unit.position + offset,
                          skill_3_left_1_D.get(),
                          {0.8, 0.8});
            }break;
            case 1:
            {
                offset.x = blockSize.x * 0.3;
                offset.y = -3;
                DrawDecal(unit.position + offset,
                          skill_3_left_2_D.get(),
                          {0.9, 0.9});
            }break;
            case 0:
            {
                offset.x = blockSize.x * 0.3;
                offset.y = -3;
                DrawDecal(unit.position + offset,
                          skill_3_left_3_D.get(),
                          {0.9, 0.9});
            }break;
        }
    }
}

void Example::skill_2_Draw(Unit &unit, float offset_true, float offset_false) {
    olc::vf2d offset(0, 0);
    if (unit.face)
    {
        int picNum = (unit.skill_2_Frames - 1) / 150;
        switch(picNum)
        {
            case 7:
            {
                offset.x = -blockSize.x * 1;
                offset.y = 4;
                DrawDecal(unit.position + offset,
                          skill_2_right_0_D.get(),
                          {0.8, 0.8});
            }break;
            case 6:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = 8;
                DrawDecal(unit.position + offset,
                          skill_2_right_1_D.get(),
                          {0.85, 0.85});
            }break;
            case 5:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = -7;
                DrawDecal(unit.position + offset,
                          skill_2_right_2_D.get(),
                          {0.8, 0.8});
            }break;
            case 4:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = -8;
                DrawDecal(unit.position + offset,
                          skill_2_right_3_D.get(),
                          {0.8, 0.8});
            }break;
            case 3:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = -8;
                DrawDecal(unit.position + offset,
                          skill_2_right_4_D.get(),
                          {0.8, 0.8});
            }break;
            case 2:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = -8;
                DrawDecal(unit.position + offset,
                          skill_2_right_5_D.get(),
                          {0.8, 0.8});
            }break;
            case 1:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = -8;
                DrawDecal(unit.position + offset,
                          skill_2_right_6_D.get(),
                          {0.8, 0.8});
            }break;
            case 0:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = -8;
                DrawDecal(unit.position + offset,
                          skill_2_right_7_D.get(),
                          {0.8, 0.8});
            }break;

        }

    }
    else
    {
        int picNum = (unit.skill_2_Frames - 1) / 150;
        switch(picNum)
        {
            case 7:
            {
                offset.x = -blockSize.x * 1;
                offset.y = 4;
                DrawDecal(unit.position + offset,
                          skill_2_left_0_D.get(),
                          {0.8, 0.8});
            }break;
            case 6:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = 8;
                DrawDecal(unit.position + offset,
                          skill_2_left_1_D.get(),
                          {0.85, 0.85});
            }break;
            case 5:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = -7;
                DrawDecal(unit.position + offset,
                          skill_2_left_2_D.get(),
                          {0.8, 0.8});
            }break;
            case 4:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = -8;
                DrawDecal(unit.position + offset,
                          skill_2_left_3_D.get(),
                          {0.8, 0.8});
            }break;
            case 3:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = -8;
                DrawDecal(unit.position + offset,
                          skill_2_left_4_D.get(),
                          {0.8, 0.8});
            }break;
            case 2:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = -8;
                DrawDecal(unit.position + offset,
                          skill_2_left_5_D.get(),
                          {0.8, 0.8});
            }break;
            case 1:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = -8;
                DrawDecal(unit.position + offset,
                          skill_2_left_6_D.get(),
                          {0.8, 0.8});
            }break;
            case 0:
            {
                offset.x = -blockSize.x * 0.5;
                offset.y = -8;
                DrawDecal(unit.position + offset,
                          skill_2_left_7_D.get(),
                          {0.8, 0.8});
            }break;
        }
    }
}


//判断角色是否被该道具影响
bool shuriken::isEffected(Unit* unit) {
    //向右运动时,人物若在图像上和shuriken重叠,那么就会判定为true
    return (unit->position.x <= size.x * 0.6 + position.x
    &&  unit->position.x >= position.x -  unit->size.x * 0.6
    &&  abs(unit->position.y - position.y) < 97 * 0.5);
}

void shuriken::effect(Unit* unit, Unit* oppoent) {
    if (isEffected(oppoent)){
        switch(oppoent->S){
            case defend:{
                oppoent->lives -= 1;
                existence = false;
                if(unit->chakra < 300) unit->chakra += 5;
                else unit->chakra = 300;
                if (oppoent->chakra < 300) oppoent->chakra += 5;
                else oppoent->chakra = 300;
            }break;

            case fall:{

            }break;

            default:{
                //和击飞效果类似, 但不会飞那么高, 会扣血,也会攒能量,后期可以用于放技能.
                play(hitSound);
                play(NarutoHitSound);
                oppoent->S = fall;
                oppoent->lives -= 5;
                oppoent->hitNum = 0;
                oppoent->speed.y = -100;
                oppoent->acceleration = 500;

                //对手成功攻击,查克拉增加.
                if (oppoent->chakra < 300) oppoent->chakra += 10;
                else oppoent->chakra = 300;
                //己方受到攻击,查克拉也增加.
                if (unit->chakra < 300) unit->chakra += 5;
                else unit->chakra = 300;

                existence = false;
            }break;
        }
    }
}

//手里剑移动.每过一帧,存在帧数减少,位置移动.
void shuriken::move(float fElapsedTime) {
    if (existFrams >= 0){
        existFrams--;
        if (direction) position.x += speed.x * fElapsedTime;
        else position.x -= speed.x * fElapsedTime;
    }
    else existence = false;
}
