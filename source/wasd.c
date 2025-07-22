#include "wasd.h"




void updatePosition(int k, int *sx, int *sy);
void clearPreviousPosition(int *sx, int *sy);
bool canMove(int *new_sx, int *new_sy);
void DrawFloor();                               //绘制家庭平面图
RoomID readRoomIDFromFile();
void setPlayerPosition(RoomID *roomid, PlayerState *player);
void writeRoomIDToFile(RoomID *roomid);
void checkRoom(PlayerState *player);
void gamei(int *page);




struct AABB{
    int x1, y1; // 左上角坐标
    int x2, y2; // 右下角坐标
};



bool AABBOverlap(struct AABB a, struct AABB b) 
{
    return (a.x1 < b.x2 && a.x2 > b.x1 && a.y1 < b.y2 && a.y2 > b.y1);
}





// 平面图主函数
void gamei(int *page)
{
    int k = 0;  // 按键值
    int new_sx = 0;
    int new_sy = 0; // 角色的新坐标，用于监测下一步是不是碰撞

    RoomID roomid = 0; // 角色所在房间号

    PlayerState orplayer;
    PlayerState *player = &orplayer; // 机器人坐标

    new_sx = player->sx;
    new_sy = player->sy;


    //向文件中读取房间号，赋player坐标值；文件无id则初始化为30，30
    //注意：只有重新调用gamei()的时候才会“根据房间号初始化player”！
    roomid = readRoomIDFromFile();
    setPlayerPosition(&roomid, player);


    // 画出平面图和机器人位置
    mouse_off(&mouse);
    DrawFloor();
    bar1(player->sx - 10, player->sy - 10, player->sx + 10, player->sy + 10, 0xF5F5F5);
    mouse_on(mouse);
    

    //进入while循环判断，走路与撞墙，进入房间
    while (1)
    {
        mouse_show(&mouse);


        //行走检测，与合法性检测
        if (bioskey(1)) 
        {
            k = bioskey(0);
            new_sx = player->sx;
            new_sy = player->sy;

            if (k == DOWN) new_sy += MOVE_STEP;
            else if (k == UP) new_sy -= MOVE_STEP;
            else if (k == RIGHT) new_sx += MOVE_STEP;
            else if (k == LEFT) new_sx -= MOVE_STEP;

            // 检查新位置是否有效
            if (canMove(&new_sx, &new_sy)) 
            {
                clearPreviousPosition(&player->sx, &player->sy);
                updatePosition(k, &player->sx, &player->sy);

                checkRoom(player);//检查是否进入房间，是则写入.dat
                bar1(player->sx - 10, player->sy - 10, player->sx + 10, player->sy + 10, 0xF5F5F5);
                watchov(page); // 检查突发状况
            }

        }
    

        // 检查区域点击
        if (mouse_press(50, 4, 393, 228) == 1 && player->sx > 50 && player->sx < 393 && player->sy > 4 && player->sy < 228) {
            *page = 16; // 到达左侧次卧
            break;
        }
        if (mouse_press(421, 3, 701, 302) == 1 && player->sx> 421 && player->sx < 701 && player->sy > 3 && player->sy < 302) {
            *page = 16;  // 到达右侧主卧
            break;
        }
        if (mouse_press(706, 3, 958, 140) == 1 && player->sx > 706 && player->sx < 958 && player->sy > 3 && player->sy < 140) {
            *page = 11;  // 到达厨房
            break;
        }
        if (mouse_press(702, 141, 957, 304) == 1 && player->sx > 702 && player->sx < 957 && player->sy > 141 &&player->sy < 304) {
            *page = 11;  // 到达餐厅
            break;
        }
        if (mouse_press(44, 392, 383, 670) == 1 &&player->sx > 50 &&player->sx < 380 && player->sy > 395 && player->sy < 660) {
            wateranime(page);//到达阳台
            *page = 17;  // 回平面图
            break;
        }
        if (mouse_press(410, 370, 935, 675) == 1 && player->sx > 410 && player->sx < 935 && player->sy > 370 && player->sy < 675) {
            teaanime(page);//到达客厅
            *page = 17;  // 回平面图
            break;
        }

        //循迹
        // 次卧
        if (mouse_press(50, 4, 393, 228) == 1) {
            if (!(player->sx > 50 && player->sx < 393 && player->sy > 4 && player->sy < 228)) {
                autoMoveToTarget(player->sx, player->sy, 245, 135, player);
            }
            *page = 16;
            break;
        }
        //主卧
        if (mouse_press(421, 3, 701, 302) == 1) {
            if (!(player->sx > 421 && player->sx < 701 && player->sy > 3 && player->sy < 302)) {
                autoMoveToTarget(player->sx, player->sy, 510, 162, player);
            }
            *page = 16;
            break;
        }
        //厨房
        if (mouse_press(706, 3, 958, 140) == 1) {
            if (!(player->sx > 706 && player->sx < 958 && player->sy > 3 && player->sy < 140)) {
                autoMoveToTarget(player->sx, player->sy, 875, 95, player);
            }
            *page = 11;
            break;
        }
        //餐厅
        if (mouse_press(702, 141, 957, 304) == 1) {
            if (!(player->sx > 702 && player->sx < 957 && player->sy > 141 && player->sy < 304)) {
                autoMoveToTarget(player->sx, player->sy, 874, 225, player);
            }
            *page = 11;
            break;
        }
        //阳台
        if (mouse_press(44, 392, 383, 670) == 1) {
            if (!(player->sx > 50 && player->sx < 380 && player->sy > 395 && player->sy < 660)) {
                autoMoveToTarget(player->sx, player->sy, 182, 497, player);
            }
            wateranime(page);
            *page = 17;
            break;
        }
        //客厅
        if (mouse_press(410, 370, 935, 675) == 1) {
            if (!(player->sx > 410 && player->sx < 935 && player->sy > 370 && player->sy < 675)) {
                autoMoveToTarget(player->sx, player->sy, 628, 388, player);
            }
            teaanime(page);
            *page = 17;
            break;
        }




        if(mouse_press(390,695,580,745)==1)//返回菜单
        {
            *page=4;
            break;
        }



    }


}



// 更新角色位置
void updatePosition(int k, int *sx, int *sy)
{
    if (k == DOWN) 
    {
        *sy += MOVE_STEP;
    } 
    else if (k == UP) 
    {
        *sy -= MOVE_STEP;
    } 
    else if (k == RIGHT) 
    {
        *sx += MOVE_STEP;
    } 
    else if (k == LEFT) 
    {
        *sx -= MOVE_STEP;
    }
}


// 擦除之前的位置
void clearPreviousPosition(int *sx, int *sy) 
{
    bar1((*sx) - 10, (*sy) - 10, (*sx) + 10, (*sy) + 10, 0xFFFFFF); // 以背景色清除
}


// 检查是否能移动到新位置
bool canMove(int *new_sx, int *new_sy) 
{
	int	i;
    
	struct AABB player;
    int numObstacles;
    struct AABB obstacles[] = {
        // 垂直墙（扩展1像素宽度）
        {52, 2, 52, 1022},      // 左侧主垂直墙 (原51,5-51,231)(边界)
        {258,231,260,309},     // 中间垂直墙1 (259,231-259,309)
        {258,359,260,387},     // 中间垂直墙2 (259,359-259,387)
        {397,359,399,686},     // 右侧垂直墙 (398,359-398,686)
        {419,5,421,305},       // 次卧垂直墙 (420,5-420,305)
        {699,5,701,305},       // 厨房垂直墙 (700,5-700,305)
        {953,1,953,767},       // 最右侧垂直墙 (953,0,953,768)(边界)
        {763,357,765,387},     // 客厅左垂直墙 (764,357-764,387)
        {881,387,885,637},     // 沙发右侧墙 (883,387-883,637)
        {931,357,933,637},     // 右侧边界墙 (932,357-932,637)
        {40,392,42,682},       //阳台左侧竖直墙

        // 水平墙（扩展1像素高度）
        {51,230,259,232},      // 主水平连接墙 (51,231-259,231)
        {41,386,259,388},      // 卫生间水平墙 (42,387-259,387)
        {419,304,470,306},     // 次卧水平连接墙 (420,305-701,305)
        {539,304,701,306},     //次卧水平连接墙
        {699,141,784,143},     // 厨房上部墙 (700,142-954,142)
        {859,141,945,143},     //厨房上部墙
        {747,304,956,306},     // 餐厅连接墙 (748,305-954,305)
        {763,356,933,358},     // 客厅装饰墙 (764,357-932,357)
        {882,636,933,638},     // 盆栽下方墙 (883,637-932,637)
        {761,390,884,392},     //沙发下端
        {2,680,1022,680},      // 最下方水平墙(边界)
       
        // 特殊障碍物
        {415,415,496,618},     // 电视机区域 (416,415-494,618)
        {752,452,832,598},     // 茶几区域 (753,452-830,598) 
        {269,619,381,666},     // 盆栽区域 (270,620,380,665)
        {389,694,579,744},      // 机器人按钮区域 (390,695,580,745)

        //房间文字区域
        {76,28,167,74},//次卧
        {64,279,166,322},//卫生间
        {144,625,235,674},//阳台
        {528,446,639,503},//客厅
        {447,62,531,117},//主卧
        {735,40,816,90},//厨房
        {727,190,820,241}//餐厅
    };
    
	player.x1 = (*new_sx) - 10;
	player.y1 = (*new_sy) - 10;
	player.x2 = (*new_sx) + 10;
	player.y2 = (*new_sy) + 10; // 角色的AABB框
    numObstacles = sizeof(obstacles) / sizeof(obstacles[0]);
  
    // 边界检查（考虑20x20角色尺寸）
    if 
    (player.x1 < 10 || player.x2 > 1014 || 
        player.y1 < 10 || player.y2 > 758) {
        return false;
    }

    // 碰撞检测
    for (i= 0; i < numObstacles; i++) 
    {
        if (AABBOverlap(player, obstacles[i])) 
        {
            return false; // 如果碰到这些线条，则不能移动
        }
    }

    return true; // 可以移动
}



void DrawFloor()//绘制家庭平面图
{
    bar1(0, 0,1024,768, 0xffffff);
    Line1(51, 5, 51, 231, 0x000000);
    Line1(51, 231,259,231, 0x000000);
    Line1(259,231,259,309, 0x000000);
    Line1(259,359,259,387, 0x000000);
    Line1(398,359,398,686, 0x000000);
    Line1(42,387,259,387, 0x000000);
    Line1(42,387,42,679, 0x000000);
    Line1(420,5,420,305, 0x000000); 
    Line1(420,305,470,305, 0x000000);
    Line1(540,305,700,305, 0x000000);
    Line1(700,5,700,305, 0x000000);
    Line1(700,142,790,142, 0x000000);
    Line1(864,142,954,142, 0x000000);
    Line1(954,5,954,305, 0x000000);
    Line1(748,305,954,305, 0x000000);
    Line1(954,342,954,680, 0x000000);
    Line1(764,357,932,357, 0x000000);
    Line1(932,357,932,637, 0x000000);
    Line1(764,357,764,387, 0x000000);
    Line1(764,387,883,387, 0x000000);
    Line1(883,387,883,637, 0x000000);
    Line1(883,637,932,637,0x000000);
    puthz(87,29, "次卧", 32, 27, 0x000000);
    puthz(459,69, "主卧", 32, 27, 0x000000);
    puthz(743,43, "厨房", 32, 27, 0x000000);
    puthz(743,199, "餐厅", 32, 27, 0x000000);
    puthz(542,454, "客厅", 32, 27, 0x000000);
    puthz(890,450, "沙", 32, 27, 0x000000);
    puthz(890,501, "发", 32, 27, 0x000000);
    puthz(72,279, "卫生间", 32, 27, 0x000000);
    puthz(162,630, "阳台", 32, 27, 0x000000);
    bar2(416,415,494,618,0x00000);
    puthz(440,450,"电",32,27,0x000000);
    puthz(440,500, "视", 32, 27, 0x000000);
    puthz(440,550, "机", 32, 27, 0x000000);
    bar2(753,452,830,598,0x00000);
    puthz(767,476, "茶", 32, 27, 0x000000);
    puthz(767,531, "几", 32, 27, 0x000000);

    bar2(270,620,380,665,0x00000);
    puthz(280,630, "盆栽", 32, 27, 0x000000);

    draw_botton(390,695,580,745,0x00FF,0xDDDD);
    puthz(410,703,"返回菜单", 32, 35, 0xD8BFD8);

    bar2(76,28,167,74,0xDC143C);//次卧
    bar2(64,279,164,322,0xDC143C);//卫生间
    bar2(727,190,815,241,0xDC143C);//餐厅
    bar2(144,630,235,674,0xDC143C);//阳台
    bar2(528,446,639,503,0xDC143C);//客厅
    bar2(447,62,531,117,0xDC143C);//主卧
    bar2(740,41,816,85,0xDC143C);//厨房

}
 

//从文件 Data\\inroom.dat 中读取一个 RoomID 类型的值，
//如果文件中没有值则返回 NONE
RoomID readRoomIDFromFile() 
{
    int roomID = 0;
    FILE *file = NULL;

    file = fopen("Data\\roomid.dat", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NONE;
    }

    if (fread(&roomID, sizeof(int), 1,file) != 1)
    {
        fclose(file);
        return NONE;
    }

    fclose(file);

    if (roomID < NONE || roomID > TOILET) 
    {
        return NONE;
    }

    return (RoomID)roomID;
}




//根据 roomid 设置 player 的位置
void setPlayerPosition(RoomID *roomid, PlayerState *player) 
{
    switch (*roomid) {
        case LIVINGROOM:
            player->sx = 628;
            player->sy = 388;
            break;
        case KITCHEN:
            player->sx = 875;
            player->sy = 95;
            break;
        case MASTERBEDROOM:
            player->sx = 510;
            player->sy = 162;
            break;
        case SECONDBEDROOM:
            player->sx = 245;
            player->sy = 135;
            break;
        case BATHROOM:
            player->sx = 180;
            player->sy = 346;
            break;
        case DININGROOM:
            player->sx = 874;
            player->sy = 225;
            break;
        case BALCONY:
            player->sx = 182;
            player->sy = 497;
            break;
        case NONE:
            player->sx = 360;
            player->sy = 320;
            break;
        default:
            player->sx = 360;
            player->sy = 320;
            break;
    }
}


//向文件 Data\\roomid.dat 中写入一个 RoomID 类型的值
void writeRoomIDToFile(RoomID *roomid) 
{
    FILE *file = NULL;
    file = fopen("Data\\roomid.dat", "wb");
    if (file == NULL) 
    {
        perror("Failed to open roomid file");
        exit(1);
    }

    fwrite(roomid, sizeof(RoomID), 1, file);
    fclose(file);


    // //检验：写入.txt试试？
    // file = fopen("Data\\roomid.txt", "w+");
    // if (file == NULL)
    // {
    //     perror("Failed to open roomid file");
    //     return;	
    // }
    // fprintf(file, "%d", *roomid);
    // fclose(file);

}



//根据机器人现在的坐标，判断机器人是否在房间，是则写入roomid.dat
void checkRoom(PlayerState *player)
{
    RoomID roomid = 0;


    // 进入次卧
    if (player->sx >= 60 && player->sx <= 404 && player->sy >= 10 && player->sy <= 222)
    {
        roomid = SECONDBEDROOM;
        writeRoomIDToFile(&roomid);
    }
    // 进入主卧
    else if (player->sx >= 425 && player->sx <= 690 && player->sy >= 8 && player->sy <= 297)
    {
        roomid = MASTERBEDROOM;
        writeRoomIDToFile(&roomid);
    }
    // 进入厨房
    else if (player->sx >= 705 && player->sx <= 947 && player->sy >= 10 && player->sy <= 138)
    {
        roomid = KITCHEN;
        writeRoomIDToFile(&roomid);
    }
    // 进入餐厅
    else if (player->sx >= 703 && player->sx <= 945 && player->sy >= 150 && player->sy <= 300)
    {
        roomid = DININGROOM;
        writeRoomIDToFile(&roomid);
    }
    // 进入客厅
    else if (player->sx >= 404 && player->sx <= 941 && player->sy >= 368 && player->sy <= 677)
    {
        roomid = LIVINGROOM;
        writeRoomIDToFile(&roomid);
    }
    // 进入阳台
    else if (player->sx >= 47 && player->sx <= 385 && player->sy >= 396 && player->sy <= 668)
    {
        roomid = BALCONY;
        writeRoomIDToFile(&roomid);
    }

    
}