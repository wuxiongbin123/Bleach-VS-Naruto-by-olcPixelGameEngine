#include "engine.h"
using namespace std;

Unit::Unit(){}

Unit::Unit(bool s, unitType u): S(stand), lives(10)
                                , side(s), type(u),
                                stateNum(0), face(!s),
                                acceleration(500), canDoubleJump(true),
                                attackNum(3), attackTime(clock() - 500),
                                hitTime(clock() - 500), hitNum(0)
                                {
    speed = {250, 0};
    if (side){
        rightKey = olc::Key::D;
        leftKey = olc::Key::A;
    } else {
        rightKey = olc::Key::RIGHT;
        leftKey = olc::Key::LEFT;
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
    gameOverPic = std::make_unique<olc::Sprite>("./pic/gameOver.png");
    return true;
}

bool Example::OnUserUpdate(float fElapsedTime) {
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
        //静止时的跳跃, 按下K键的瞬间获得一个极大的冲量。
        //A角色起跳用K键控制，跳跃最多可以二段跳。
        if (GetKey(olc::Key::K).bPressed){
            if (unitA.S != jump)
            {
                unitA.S = jump;
                unitA.speed.y = -400;
            }
            else
            {
                if(unitA.canDoubleJump)
                {
                    unitA.speed.y = -400;
                    unitA.canDoubleJump = false;
                }
            }
        }
        //B角色的起跳用鼠标右键控制
        if (GetMouse(1).bPressed ){
            if (unitB.S != jump)
            {
                unitB.S = jump;
                unitB.speed.y = -400;
            }
            else
            {
                if (unitB.canDoubleJump)
                {
                    unitB.speed.y = -400;
                    unitB.canDoubleJump = false;
                }
            }
        }

        //落体过程。
        if (unitA.S == jump) {
            if ((unitA.position.y + unitA.speed.y * fElapsedTime) <= floorPos-blockSize.y + 15){
                unitA.position.y += unitA.speed.y * fElapsedTime;
                unitA.speed.y += unitB.acceleration * fElapsedTime;
            }
            else
            {
                unitA.position.y = floorPos-blockSize.y + 15;
                unitA.speed.y = 0;
                unitA.S = stand;
                unitA.canDoubleJump = true;
            }
        }

        if (unitB.S == jump) {
            if ((unitB.position.y + unitB.speed.y * fElapsedTime) <= floorPos-blockSize.y + 15){
                unitB.position.y += unitB.speed.y * fElapsedTime;
                unitB.speed.y += unitB.acceleration * fElapsedTime;
            }
            else
            {
                unitB.position.y = floorPos-blockSize.y + 15;
                unitB.speed.y = 0;
                unitB.S = stand;
                unitB.canDoubleJump = true;
            }
        }


        //当按住方向键时将状态设定为奔跑。
        //A角色右跑
        if (GetKey(olc::Key::D).bHeld){
            switch (unitA.S) {
                case hit:{}
                case attack: break;
                case jump:{
                    unitA.face = true;
                    if (unitA.position.x + unitA.speed.x * fElapsedTime <= ScreenWidth() - blockSize.x)
                        unitA.position.x += unitA.speed.x * fElapsedTime;
                }break;
                default:{
                    unitA.S = run;
                    unitA.face = true;
                    //右边不能过右界限
                    if (unitA.position.x + unitA.speed.x * fElapsedTime <= ScreenWidth() - blockSize.x)
                        unitA.position.x += unitA.speed.x * fElapsedTime;
                }break;
            }
        }

        //A角色左跑
        if (GetKey(olc::Key::A).bHeld){
            switch (unitA.S) {
                case hit:{}
                case attack: break;
                case jump:{
                    unitA.face = false;
                    //左边不能过左界限
                    if (unitA.position.x + unitA.speed.x * fElapsedTime >=0)
                        unitA.position.x -= unitA.speed.x * fElapsedTime;
                }break;
                default:{
                    unitA.S = run;
                    unitA.face = false;
                    //左边不能过左界限
                    if (unitA.position.x + unitA.speed.x * fElapsedTime >=0)
                        unitA.position.x -= unitA.speed.x * fElapsedTime;
                }break;
            }
        }

        //B角色右跑
        if (GetKey(olc::Key::RIGHT).bHeld){
            switch (unitB.S) {
                case hit:{}
                case attack: break;
                case jump:{
                    unitB.face = true;
                    float futurePos = unitB.position.x += unitB.speed.x * fElapsedTime;
                    if (inBound(unitB.face, futurePos))
                        unitB.position.x = futurePos;
                }break;
                default:{
                    unitB.S = run;
                    unitB.face = true;
                    //右边不能过右界限
                    float futurePos = unitB.position.x + unitB.speed.x * fElapsedTime;
                    if (inBound(unitB.face, futurePos))
                        unitB.position.x = futurePos;
                }break;
            }
        }
        //B角色左跑
        if (GetKey(olc::Key::LEFT).bHeld){
            switch (unitB.S) {
                case hit:{}
                case attack: break;
                case jump:{
                    unitB.face = false;
                    //左边不能过左界限
                    if (unitB.position.x + unitB.speed.x * fElapsedTime >=0)
                        unitB.position.x -= unitB.speed.x * fElapsedTime;
                }break;
                default:{
                    unitB.S = run;
                    unitB.face = false;
                    //左边不能过左界限
                    if (unitB.position.x + unitB.speed.x * fElapsedTime >=0)
                        unitB.position.x -= unitB.speed.x * fElapsedTime;
                }break;
            }
        }
        //两个角色的攻击
        if(GetKey(olc::Key::J).bPressed){
            attackAction(unitA, fElapsedTime);
        }
        if(GetMouse(0).bPressed){
            attackAction(unitB, fElapsedTime);
        }

        //回合结束，结算是否被攻击中。如果被击中则会移动。
        hitAction(unitA, fElapsedTime);
        hitAction(unitB, fElapsedTime);
        fallAction(unitA, fElapsedTime);
        fallAction(unitB, fElapsedTime);

        recover(unitA);
        recover(unitB);
        removeDeadArea();
        gameOver();
    }

    render();
    return true;
}

void Example::render() {
    Clear(olc::WHITE);
    //画地板
    for(int i = 0; i < ScreenWidth() / 16; i++){
        floorSite.x = i * 16;
        floorSite.y = floorPos;
        DrawSprite(floorSite, tilePic.get());
    }
    if (winner == unsettled){
        //根据不同的状态画不同的图像。
        SetPixelMode(olc::Pixel::ALPHA);
        switch (unitA.S) {
            case jump:jumpDraw(unitA, 0, 16);break;
            case stand:standDraw(unitA, 0, 3);break;
            case run:runDraw(unitA, 0, 8);break;
            case attack:attackDraw(unitA, -5, 10);break;
            case hit:hitDraw(unitA, 0, 0);break;
            case fall:fallDraw(unitA, 0, 0);break;
        }
        switch(unitB.S){
            case jump: jumpDraw(unitB, 0, 16);break;
            case stand:standDraw(unitB, 0, 3);break;
            case run:runDraw(unitB, 0, 8);break;
            case attack:attackDraw(unitB, -5, 10);break;
            case hit:hitDraw(unitB, 0, 0);break;
            case fall:fallDraw(unitB, 0, 0);break;
        }
    }
    if (winner != unsettled){

        //Render game over.
        olc::vf2d posOfGameOver;
        posOfGameOver.x = 152;
        posOfGameOver.y = 150;
        DrawSprite(posOfGameOver, gameOverPic.get());

        switch(winner)
        {
            case playerA:{

                standDraw(unitA, 0, 3);
                fallDraw(unitB, 0, 0);
            }break;
            case playerB:{

                standDraw(unitB, 0, 3);
                fallDraw(unitA, 0, 0);
            }
                break;
            case draw: {
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
            DrawPartialSprite(unit.position, jumpRightPic.get(),
                              picNum * blockSize + offset, blockSize - olc::vf2d(5, 0));
        }
        else{
            picNum.x = 3;
            DrawPartialSprite(unit.position, jumpRightPic.get(),
                              picNum * blockSize + offset, blockSize);
        }
    }
    else
    {
        offset.x += offset_false;
        olc::vi2d picNum;
        if (unit.speed.y < 0) {//speed.y < 0 代表朝上跳.
            picNum.x = 3;

            DrawPartialSprite(unit.position, jumpLeftPic.get(),
                              picNum * blockSize + offset , blockSize - olc::vf2d(10, 0));

        }
        else{
            picNum.x = 1;
            DrawPartialSprite(unit.position, jumpLeftPic.get(),
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
        DrawPartialSprite(unit.position, standPicOfA.get(),
                          picNum * blockSize + offset, blockSize);
        unit.stateNum += 0.02;
    }
    else{
        offset.x += offset_false;
        olc::vi2d picNum = { int(unit.stateNum) % 6, 0};
        DrawPartialSprite(unit.position, standPicOfB.get(),
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
        DrawPartialSprite(unit.position, runRightPic.get(),
                          picNum * blockSize + offset, blockSize);
        unit.stateNum += 0.02;
    }
    else
    {
        offset.x += offset_false;
        olc::vi2d picNum = {int(unit.stateNum)  % 6, 0};
        DrawPartialSprite(unit.position,runLeftPic.get(),
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
                int num = (clock() - unit.attackTime) / 125;
                olc::vi2d picNum = {num, 0};
                DrawPartialSprite(unit.position, attackRightPic_0.get(),
                                  picNum * blockSize + offset, blockSize);
            }break;
            case 1:
            {
                int num = (clock() - unit.attackTime) / 125;
                olc::vi2d picNum = {num, 0};
                DrawPartialSprite(unit.position, attackRightPic_1.get(),
                                  picNum * blockSize + offset, blockSize);
            }break;
            case 2:
            {
                int num = (clock() - unit.attackTime) / 125;
                olc::vi2d picNum = {num, 0};
                DrawPartialSprite(unit.position, attackRightPic_2.get(),
                                  picNum * blockSize + offset, blockSize);
            }break;
            case 3:
                offset.x += 5;
                offset.y += 5;
                int num = (clock() - unit.attackTime) / 125;
                olc::vi2d picNum = {num, 0};
                DrawPartialSprite(unit.position, attackRightPic_3.get(),
                                  picNum * blockSize + offset, blockSize);
        }
    }
    else
    {
        offset.x += offset_false;
        switch(unit.attackNum){
            case 0:
            {
                int num = (clock() - unit.attackTime) / 125;
                olc::vi2d picNum = {num, 0};
                DrawPartialSprite(unit.position, attackLeftPic_0.get(),
                                  picNum * blockSize + offset, blockSize);
            }break;
            case 1:
            {
                int num = (clock() - unit.attackTime) / 125;
                olc::vi2d picNum = {num, 0};
                DrawPartialSprite(unit.position, attackLeftPic_1.get(),
                                  picNum * blockSize + offset, blockSize);
            }break;
            case 2:
            {
                int num = (clock() - unit.attackTime) / 125;
                olc::vi2d picNum = {num, 0};
                DrawPartialSprite(unit.position, attackLeftPic_2.get(),
                                  picNum * blockSize + offset, blockSize);
            }break;
            case 3:
                offset.x -= 5;
                offset.y += 5;
                int num = (clock() - unit.attackTime) / 125;
                olc::vi2d picNum = {num, 0};
                DrawPartialSprite(unit.position, attackLeftPic_3.get(),
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
        DrawPartialSprite(unit.position, hitRightPic.get(),
                          picNum * blockSize + offset, blockSize);
    }
    else{
        offset.x = offset_false;
        olc::vi2d picNum;
        picNum.x = unit.hitNum % 2;
        picNum.y = 0;
        DrawPartialSprite(unit.position, hitLeftPic.get(),
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
            picNum.x = 0;
            DrawPartialSprite(unit.position, fallRightPic.get(),
                              picNum * blockSize + offset, blockSize);
        }
        else{
            if (winner == unsettled){
                if (clock() - unit.fallDownTime < 100) picNum.x = 0;
                if (clock() - unit.fallDownTime >= 100
                    && clock() - unit.fallDownTime <= 1400) picNum.x = 1;
                if (clock() - unit.fallDownTime >1400 ) picNum.x = 2;
            }
            else{
                if (clock() - unit.fallDownTime < 100) picNum.x = 0;
                if (clock() - unit.fallDownTime >= 100) picNum.x = 1;
            }
            DrawPartialSprite(unit.position, fallRightPic.get(),
                              picNum * blockSize + offset, blockSize);
        }
    }
    else
    {
        offset.x = offset_false;
        offset.x = offset_true;
        if (unit.speed.y != 0)// 还在飞行中
        {
            picNum.x = 3;
            DrawPartialSprite(unit.position, fallLeftPic.get(),
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
            DrawPartialSprite(unit.position, fallLeftPic.get(),
                              picNum * blockSize + offset, blockSize);
        }
    }
}

//recover进行状态转移。
void Example::recover(Unit& unit) {
    switch (unit.S) {
        case run:{
            if ((GetKey(unit.rightKey).bReleased || GetKey(unit.leftKey).bReleased))
                unit.S = stand;
        }break;
        case attack:{
            if( (clock() - unit.attackTime) > 500) unit.S = stand;
        }break;
        case hit:{
            if( (clock() - unit.hitTime) > 1000) unit.S = stand;
        }break;
        default:{}
        break;
    }
}

//角色发动攻击技能
void Example::attackAction(Unit &unit, float fElapsedTime) {
    //跳跃状态下不进行普攻。
    if (unit.S != jump && (clock() - unit.attackTime) > 500) {
        unit.S = attack;
        unit.attackNum = (unit.attackNum + 1) % 4;
        //更新攻击时间
        unit.attackTime = clock();
        //攻击时进行移动。
        if (unit.face) {
            unit.position.x += unit.speed.x * 20 * fElapsedTime;
        } else {
            unit.position.x -= unit.speed.x * 20 * fElapsedTime;
        }
        //攻击时创造伤害区域，维持一定时间。
        //朝右边攻击
        if (unit.face){
            olc::vf2d northwest;
            northwest.x= unit.position.x- 5;
            northwest.y = unit.position.y - blockSize.y;
            areas.push_back(Area(northwest, blockSize * olc::vf2d(1.3, 1), hitArea, 500, unit.side));
        }
        else{
            //朝左边攻击
            olc::vf2d northwest;
            northwest.x = unit.position.x - blockSize.x * 1.1;
            northwest.y = unit.position.y - blockSize.y;
            areas.push_back(Area(northwest, blockSize * olc::vf2d(1.3, 1), hitArea, 500, unit.side));
        }
    }
}



void Example::hitAction(Unit &unit, float fElapsedTime) {
    //如果角色处于hitArea中，则会收到伤害, 然后这个area自动消亡。
    for(int i = 0; i < areas.size(); i++) {
        if (areas[i].inArea(unit) && areas[i].type == hitArea && unit.side != areas[i].side){
            unit.S = hit;
            unit.hitTime = clock();
            if (unit.hitNum == 0) unit.firstHitTime = clock();
            unit.lives -= 10;
            unit.hitNum++;
            areas[i].existence = false;
        }
    }
    if (unit.S == hit){
        if (unit.face){
            if (unit.position.x - unit.speed.x * 0.3 * fElapsedTime >= 0)
            unit.position.x -= unit.speed.x * 0.3 * fElapsedTime;
        }else{
            if (unit.position.x + unit.speed.x * 0.3 * fElapsedTime <= ScreenWidth() - blockSize.x)
            unit.position.x += unit.speed.x * 0.3 * fElapsedTime;
        }
        //如果3秒之内连续收到四次攻击，则会被击飞。然后firstHitTime和hitNum重置
        if (clock() - unit.firstHitTime < 5000 && unit.hitNum == 4){
            unit.S = fall;
            unit.hitNum = 0;
            unit.speed.y = -400;
        }
    }
}

void Example::fallAction(Unit &unit, float fElapsedTime) {
    if (unit.S == fall){

        //竖直方向的飞行无关朝向，fall时间等于飞行时间加上躺在地上的时间。飞行的逻辑和jump一样
        if ((unit.position.y + unit.speed.y * fElapsedTime) < floorPos-blockSize.y + 15){
            unit.position.y += unit.speed.y * fElapsedTime;
            unit.speed.y += unitB.acceleration * fElapsedTime;
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
    for(int i = 0; i < areas.size(); i++){
        if (clock() - areas[i].startTime > areas[i].duration) areas[i].existence = false;
    }
    areas.erase(
            std::remove_if(areas.begin(), areas.end(), [](const Area& area) { return !area.existence; }),
            areas.end());
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
    }
    if (unitB.lives <= 0)
    {
        unitB.fallDownTime = clock();
        winner = playerA;
    }
    if (unitA.lives == 0 && unitB.lives == 0)
    {
        winner = draw;
    }
}



