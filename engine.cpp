#include "engine.h"
using namespace std;

Unit::Unit(){}

Unit::Unit(bool s, unitType u): S(stand), lives(100)
                                , side(s), type(u),
                                stateNum(0), face(!s),
                                acceleration(0), canDoubleJump(true),
                                attackNum(3), attackTime(clock() - 1000),
                                hitTime(clock() - 500), hitNum(0),
                                farAttackFrames(0),
                                flashFrames(0)
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
    unitA = Unit(true, Naruto);
    unitB = Unit(false, Naruto);
    unitA.position = { 1024 * 0.2 - 120, floorPos-blockSize.y + 15};
    unitB.position = {1024 * 0.8 , floorPos - blockSize.y + 15};//170是hard code上去的，是人物的高度。

    //为了简便，规定两个都是Naruto。

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

    return true;
}

bool Example::OnUserUpdate(float fElapsedTime) {
    //每回合开始前,记录两个角色的位置,和运动状态,用于物理碰撞.
    unitA.moveFlag = isMoving(unitA);
    unitB.moveFlag = isMoving(unitB);
    unitAreas.push_back(unitArea(unitA.position, blockSize, true, unitA.moveFlag, unitA.face));
    unitAreas.push_back(unitArea(unitB.position, blockSize, false, unitB.moveFlag, unitB.face));

    if (winner == unsettled) {
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
        //删除失效道具.
        removeDeadItem();
        gameOver();
    }
            //血条逐渐减少。
    if (barRedLenOfA > 330 * unitA.lives / 100){
            barRedLenOfA -= 35 * fElapsedTime ;
        }
    if (barRedLenOfB > 330 * unitB.lives / 100){
            barRedLenOfB -= 35 * fElapsedTime ;
        }
    render(fElapsedTime);
    return true;
}

void Example::render(float fElapsedTime) {
    Clear(olc::WHITE);
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
    SetPixelMode(olc::Pixel::ALPHA);

    //画道具
    itemDraw();

    if (winner == unsettled){
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
        }
    }
    if (winner != unsettled){

        //Render game over.
        olc::vf2d posOfGameOver;
        posOfGameOver.x = 152;
        posOfGameOver.y = 150;
        DrawDecal(posOfGameOver, gameOverDecal.get());

        switch(winner)
        {
            case playerA:{
                fallAction(unitB, fElapsedTime);
                standDraw(unitA, 0, 3);
                fallDraw(unitB, 0, 0);
            }break;
            case playerB:{
                fallAction(unitA, fElapsedTime);
                standDraw(unitB, 0, 3);
                fallDraw(unitA, 0, 0);
            }
                break;
            case draw: {
                fallAction(unitB, fElapsedTime);
                fallAction(unitA, fElapsedTime);
                standDraw(unitA, 0, 3);
                standDraw(unitB, 0, 3);
            }break;
        }
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
    if (unit.face){
        offset.x += offset_true;
        olc::vi2d picNum = { int(unit.stateNum) % 6, 0};
        DrawPartialDecal(unit.position, standDecalOfA.get(),
                          picNum * blockSize + offset, blockSize);
        unit.stateNum += 0.02;
    }
    else{
        offset.x += offset_false;
        olc::vi2d picNum = { int(unit.stateNum) % 6, 0};
        DrawPartialDecal(unit.position, standDecalOfB.get(),
                          picNum * blockSize + offset, blockSize);
        unit.stateNum += 0.02;
    }
}

//奔跑的动画
void Example::runDraw(Unit& unit, float offset_true, float offset_false) {
    olc::vf2d offset = {0, 0};
    if (unit.face)//朝右跑，则脸向右，为真。
    {
        offset.x += offset_true;
        olc::vi2d picNum = {int(unit.stateNum)% 6, 0};
        DrawPartialDecal(unit.position, runRightDecal.get(),
                          picNum * blockSize + offset, blockSize);
        unit.stateNum += 0.02;
    }
    else
    {
        offset.x += offset_false;
        olc::vi2d picNum = {int(unit.stateNum)  % 6, 0};
        DrawPartialDecal(unit.position,runLeftDecal.get(),
                          picNum * blockSize + offset, blockSize);
        unit.stateNum += 0.02;
    }
}

void Example::attackDraw(Unit &unit, float offset_true, float offset_false) {
    olc::vf2d offset = {0, 0};
    if (unit.face)//向右攻击
    {
        offset.x += offset_true;
        switch(unit.attackNum){
            case 0:
            {
                int num = (clock() - unit.attackTime) / 200;
                olc::vi2d picNum = {num, 0};
                DrawPartialDecal(unit.position, attackRightDecal_0.get(),
                                  picNum * blockSize + offset, blockSize);
            }break;
            case 1:
            {
                int num = (clock() - unit.attackTime) / 200;
                olc::vi2d picNum = {num, 0};
                DrawPartialDecal(unit.position, attackRightDecal_1.get(),
                                  picNum * blockSize + offset, blockSize);
            }break;
            case 2:
            {
                int num = (clock() - unit.attackTime) / 200;
                olc::vi2d picNum = {num, 0};
                DrawPartialDecal(unit.position, attackRightDecal_2.get(),
                                  picNum * blockSize + offset, blockSize);
            }break;
            case 3:
                offset.x += 5;
                offset.y += 5;
                int num = (clock() - unit.attackTime) / 200;
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
                int num = (clock() - unit.attackTime) / 200;
                olc::vi2d picNum = {num, 0};
                DrawPartialDecal(unit.position, attackLeftDecal_0.get(),
                                  picNum * blockSize + offset, blockSize);
            }break;
            case 1:
            {
                int num = (clock() - unit.attackTime) / 200;
                olc::vi2d picNum = {num, 0};
                DrawPartialDecal(unit.position, attackLeftDecal_1.get(),
                                  picNum * blockSize + offset, blockSize);
            }break;
            case 2:
            {
                int num = (clock() - unit.attackTime) / 200;
                olc::vi2d picNum = {num, 0};
                DrawPartialDecal(unit.position, attackLeftDecal_2.get(),
                                  picNum * blockSize + offset, blockSize);
            }break;
            case 3:
                offset.x -= 5;
                offset.y += 5;
                int num = (clock() - unit.attackTime) / 200;
                olc::vi2d picNum = {num, 0};
                DrawPartialDecal(unit.position, attackLeftDecal_3.get(),
                                  picNum * blockSize + offset, blockSize);
        }
    }
}

void Example::hitDraw(Unit &unit, float offset_true, float offset_false) {
    olc::vf2d offset;
    if (unit.face){//面向右边时被攻击
        offset.x = offset_true;
        olc::vi2d picNum;
        picNum.x = unit.hitNum % 2;
        picNum.y = 0;
        DrawPartialDecal(unit.position, hitRightDecal.get(),
                          picNum * blockSize + offset, blockSize);
    }
    else{
        offset.x = offset_false;
        olc::vi2d picNum;
        picNum.x = unit.hitNum % 2;
        picNum.y = 0;
        DrawPartialDecal(unit.position, hitLeftDecal.get(),
                          picNum * blockSize + offset, blockSize);
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
            }else{
                if (clock() - unit.fallDownTime < 100) picNum.x = 1;
                if (clock() - unit.fallDownTime >= 100) picNum.x = 2;
            }
            DrawPartialDecal(unit.position, fallRightDecal.get(),
                             picNum * blockSize + offset, blockSize);
        }
        else{
            if (winner == unsettled){
                if (clock() - unit.fallDownTime < 100) picNum.x = 1;
                if (clock() - unit.fallDownTime >= 100
                    && clock() - unit.fallDownTime <= 1400) picNum.x = 2;
                if (clock() - unit.fallDownTime >1400 ) picNum.x = 3;
            }
            else{
                if (clock() - unit.fallDownTime < 100) picNum.x = 1;
                if (clock() - unit.fallDownTime >= 100) picNum.x = 2;
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
            }else{
                if (clock() - unit.fallDownTime < 100) picNum.x = 2;
                if (clock() - unit.fallDownTime >= 100) picNum.x = 1;
            }
            DrawPartialDecal(unit.position, fallLeftDecal.get(),
                              picNum * blockSize + offset, blockSize);
        }
        else{
            if (winner == unsettled){
                if (clock() - unit.fallDownTime < 100) picNum.x = 2;
                if (clock() - unit.fallDownTime >= 100
                    && clock() - unit.fallDownTime <= 1400) picNum.x = 1;
                if (clock() - unit.fallDownTime >1400 ) picNum.x = 0;
            }
            else{
                if (clock() - unit.fallDownTime < 100) picNum.x = 2;
                if (clock() - unit.fallDownTime >= 100) picNum.x = 1;
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
            if( (clock() - unit.attackTime) > 800){
                unit.S = stand;
                unit.attackNum = 3;
            }
        }break;
        case hit:{
            if( (clock() - unit.hitTime) > 1000) unit.S = stand;
        }break;
        case defend:
        {
            if ((GetKey(unit.downKey).bReleased)) unit.S = stand;
        }break;
        default:{
            if ((clock() - unit.attackTime) > 500) {
                unit.attackNum = 3;
            }
        }
        break;
    }
}

//角色发动攻击技能
void Example::attackAction(Unit &unit, float fElapsedTime) {
    if (GetKey(unit.attackKey).bPressed){
        //跳跃状态下不进行普攻。
        if (unit.S != farAttack && unit.S != jump && (clock() - unit.attackTime) > 500) {
            //第四次攻击后需要更长的cd
            if (unit.attackNum == 3){
                if(clock() - unit.attackTime >= 1000)
                {
                    unit.S = attack;
                    unit.attackNum = (unit.attackNum + 1) % 4;
                    //更新攻击时间
                    unit.attackTime = clock();
                }
            }
            else{
                unit.S = attack;
                unit.attackNum = (unit.attackNum + 1) % 4;
                //更新攻击时间
                unit.attackTime = clock();
            }


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



void Example::hitAction(Unit &unit, float fElapsedTime) {
    //如果角色处于hitArea中，则会收到伤害, 然后这个area自动消亡。
    for(int i = 0; i < hitAreas.size(); i++) {
        if (hitAreas[i].inArea(unit) && unit.side != hitAreas[i].side && unit.S != fall
            && unit.S != defend){
            unit.S = hit;
            unit.hitTime = clock();
            if (unit.hitNum == 0) unit.firstHitTime = clock();
            unit.lives -= 5;
            unit.hitNum++;
            hitAreas[i].existence = false;
            play(hitSound);
        }if (unit.S == defend){
            hitAreas[i].existence = false;
            unit.lives -= 1;
        }
    }
    if (unit.S == hit){
        //如果3秒之内连续收到四次攻击，则会被击飞。然后firstHitTime和hitNum重置
        if (clock() - unit.firstHitTime < 5000 && unit.hitNum == 4){
            unit.S = fall;
            unit.hitNum = 0;
            unit.speed.y = -400;
            unit.acceleration = 500;
        }
    }
}

void Example::fallAction(Unit &unit, float fElapsedTime) {
    if (unit.S == fall){

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
                unit.fallDownTime = clock();
            }
            else{
                //落地之后继续躺1.5s, 状态出口。
                if (clock() - unit.fallDownTime > 1500) unit.S = stand;
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
    if (unitA.lives <= 0 )
    {
        unitA.fallDownTime = clock();
        winner = playerB;
        play(ggSound);
    }
    if (unitB.lives <= 0)
    {
        unitB.fallDownTime = clock();
        winner = playerA;
        play(ggSound);
    }
    if (unitA.lives <= 0 && unitB.lives <= 0)
    {
        winner = draw;
        play(ggSound);
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
    livesGreenBarSizeA.x = 330 * unitA.lives / 100;
    livesGreenBarSizeB.x = 330 * unitB.lives / 100;

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
    if (GetKey(unit.downKey).bHeld){
        switch(unit.S){
            //攻击、跳跃、被攻击、击飞时不能通过按键改变状态。
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
    if (GetKey(unit.rightKey).bHeld){
        switch (unit.S) {
            case farAttack:{}
            case flash:{}
            case defend:{}
            case fall:{}
            case hit:{}
            case attack:{} break;
            case jump:{}
            default: {
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
        }
    }

    //角色左跑
    if (GetKey(unit.leftKey).bHeld){
        switch (unit.S) {
            case farAttack: {}
            case flash:{}
            case defend:{}
            case fall:{}
            case hit:{}
            case attack:{}break;
            case jump:{}
            default:{
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
    if (GetKey(unit.upKey).bPressed){
        switch(unit.S){
            case farAttack:{}
            case flash:{}
            case hit:{}
            case fall:{}break;
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
    if(GetKey(unit.flashKey).bReleased){
        switch(unit.S){
            //从这里到default都为空,代表着这些状态都不能直接到flash
            case farAttack:{}
            case hit:{}
            case attack:{}
            case defend:{}
            case fall: {}
            case flash:{}break;
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

    if (GetKey(unit.farAttackKey).bPressed){
        switch(unit.S)
        {
            case jump:{}
            case attack:{}
            case fall:{}
            case hit:{}
            case farAttack:{}break;
            default:{
                //成功进行攻击
                if (unit.farAttackFrames == 0){
                    olc::vf2d offset(0, 0);
                    if (unit.face) offset.x = blockSize.x;
                    else offset.x = - blockSize.x;
                    unit.S = farAttack;

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
        if (items[i]->side) opponent = &unitB;
        else opponent = &unitA;
        items[i]->effect(opponent);
    }
}


//判断角色是否被该道具影响
bool shuriken::isEffected(Unit* unit) {
    //向右运动时,人物若在图像上和shuriken重叠,那么就会判定为true
    return (unit->position.x <= size.x + position.x
    &&  unit->position.x >= position.x -  unit->size.x);
}

void shuriken::effect(Unit* unit) {
    if (isEffected(unit)){
        switch(unit->S){
            case defend:{
                unit->lives --;
            }break;
            case fall:{}break;
            default:{
                //和击飞效果类似, 但不会飞那么高, 会扣血,也会攒能量,后期可以用于放技能.
                unit->S = fall;
                unit->lives -= 5;
                unit->hitNum = 0;
                unit->speed.y = -100;
                unit->acceleration = 500;
            }
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
