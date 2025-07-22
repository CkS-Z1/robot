#include "wasd.h"




void updatePosition(int k, int *sx, int *sy);
void clearPreviousPosition(int *sx, int *sy);
bool canMove(int *new_sx, int *new_sy);
void DrawFloor();                               //���Ƽ�ͥƽ��ͼ
RoomID readRoomIDFromFile();
void setPlayerPosition(RoomID *roomid, PlayerState *player);
void writeRoomIDToFile(RoomID *roomid);
void checkRoom(PlayerState *player);
void gamei(int *page);




struct AABB{
    int x1, y1; // ���Ͻ�����
    int x2, y2; // ���½�����
};



bool AABBOverlap(struct AABB a, struct AABB b) 
{
    return (a.x1 < b.x2 && a.x2 > b.x1 && a.y1 < b.y2 && a.y2 > b.y1);
}





// ƽ��ͼ������
void gamei(int *page)
{
    int k = 0;  // ����ֵ
    int new_sx = 0;
    int new_sy = 0; // ��ɫ�������꣬���ڼ����һ���ǲ�����ײ

    RoomID roomid = 0; // ��ɫ���ڷ����

    PlayerState orplayer;
    PlayerState *player = &orplayer; // ����������

    new_sx = player->sx;
    new_sy = player->sy;


    //���ļ��ж�ȡ����ţ���player����ֵ���ļ���id���ʼ��Ϊ30��30
    //ע�⣺ֻ�����µ���gamei()��ʱ��Żᡰ���ݷ���ų�ʼ��player����
    roomid = readRoomIDFromFile();
    setPlayerPosition(&roomid, player);


    // ����ƽ��ͼ�ͻ�����λ��
    mouse_off(&mouse);
    DrawFloor();
    bar1(player->sx - 10, player->sy - 10, player->sx + 10, player->sy + 10, 0xF5F5F5);
    mouse_on(mouse);
    

    //����whileѭ���жϣ���·��ײǽ�����뷿��
    while (1)
    {
        mouse_show(&mouse);


        //���߼�⣬��Ϸ��Լ��
        if (bioskey(1)) 
        {
            k = bioskey(0);
            new_sx = player->sx;
            new_sy = player->sy;

            if (k == DOWN) new_sy += MOVE_STEP;
            else if (k == UP) new_sy -= MOVE_STEP;
            else if (k == RIGHT) new_sx += MOVE_STEP;
            else if (k == LEFT) new_sx -= MOVE_STEP;

            // �����λ���Ƿ���Ч
            if (canMove(&new_sx, &new_sy)) 
            {
                clearPreviousPosition(&player->sx, &player->sy);
                updatePosition(k, &player->sx, &player->sy);

                checkRoom(player);//����Ƿ���뷿�䣬����д��.dat
                bar1(player->sx - 10, player->sy - 10, player->sx + 10, player->sy + 10, 0xF5F5F5);
                watchov(page); // ���ͻ��״��
            }

        }
    

        // ���������
        if (mouse_press(50, 4, 393, 228) == 1 && player->sx > 50 && player->sx < 393 && player->sy > 4 && player->sy < 228) {
            *page = 16; // ����������
            break;
        }
        if (mouse_press(421, 3, 701, 302) == 1 && player->sx> 421 && player->sx < 701 && player->sy > 3 && player->sy < 302) {
            *page = 16;  // �����Ҳ�����
            break;
        }
        if (mouse_press(706, 3, 958, 140) == 1 && player->sx > 706 && player->sx < 958 && player->sy > 3 && player->sy < 140) {
            *page = 11;  // �������
            break;
        }
        if (mouse_press(702, 141, 957, 304) == 1 && player->sx > 702 && player->sx < 957 && player->sy > 141 &&player->sy < 304) {
            *page = 11;  // �������
            break;
        }
        if (mouse_press(44, 392, 383, 670) == 1 &&player->sx > 50 &&player->sx < 380 && player->sy > 395 && player->sy < 660) {
            wateranime(page);//������̨
            *page = 17;  // ��ƽ��ͼ
            break;
        }
        if (mouse_press(410, 370, 935, 675) == 1 && player->sx > 410 && player->sx < 935 && player->sy > 370 && player->sy < 675) {
            teaanime(page);//�������
            *page = 17;  // ��ƽ��ͼ
            break;
        }

        //ѭ��
        // ����
        if (mouse_press(50, 4, 393, 228) == 1) {
            if (!(player->sx > 50 && player->sx < 393 && player->sy > 4 && player->sy < 228)) {
                autoMoveToTarget(player->sx, player->sy, 245, 135, player);
            }
            *page = 16;
            break;
        }
        //����
        if (mouse_press(421, 3, 701, 302) == 1) {
            if (!(player->sx > 421 && player->sx < 701 && player->sy > 3 && player->sy < 302)) {
                autoMoveToTarget(player->sx, player->sy, 510, 162, player);
            }
            *page = 16;
            break;
        }
        //����
        if (mouse_press(706, 3, 958, 140) == 1) {
            if (!(player->sx > 706 && player->sx < 958 && player->sy > 3 && player->sy < 140)) {
                autoMoveToTarget(player->sx, player->sy, 875, 95, player);
            }
            *page = 11;
            break;
        }
        //����
        if (mouse_press(702, 141, 957, 304) == 1) {
            if (!(player->sx > 702 && player->sx < 957 && player->sy > 141 && player->sy < 304)) {
                autoMoveToTarget(player->sx, player->sy, 874, 225, player);
            }
            *page = 11;
            break;
        }
        //��̨
        if (mouse_press(44, 392, 383, 670) == 1) {
            if (!(player->sx > 50 && player->sx < 380 && player->sy > 395 && player->sy < 660)) {
                autoMoveToTarget(player->sx, player->sy, 182, 497, player);
            }
            wateranime(page);
            *page = 17;
            break;
        }
        //����
        if (mouse_press(410, 370, 935, 675) == 1) {
            if (!(player->sx > 410 && player->sx < 935 && player->sy > 370 && player->sy < 675)) {
                autoMoveToTarget(player->sx, player->sy, 628, 388, player);
            }
            teaanime(page);
            *page = 17;
            break;
        }




        if(mouse_press(390,695,580,745)==1)//���ز˵�
        {
            *page=4;
            break;
        }



    }


}



// ���½�ɫλ��
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


// ����֮ǰ��λ��
void clearPreviousPosition(int *sx, int *sy) 
{
    bar1((*sx) - 10, (*sy) - 10, (*sx) + 10, (*sy) + 10, 0xFFFFFF); // �Ա���ɫ���
}


// ����Ƿ����ƶ�����λ��
bool canMove(int *new_sx, int *new_sy) 
{
	int	i;
    
	struct AABB player;
    int numObstacles;
    struct AABB obstacles[] = {
        // ��ֱǽ����չ1���ؿ�ȣ�
        {52, 2, 52, 1022},      // �������ֱǽ (ԭ51,5-51,231)(�߽�)
        {258,231,260,309},     // �м䴹ֱǽ1 (259,231-259,309)
        {258,359,260,387},     // �м䴹ֱǽ2 (259,359-259,387)
        {397,359,399,686},     // �Ҳഹֱǽ (398,359-398,686)
        {419,5,421,305},       // ���Դ�ֱǽ (420,5-420,305)
        {699,5,701,305},       // ������ֱǽ (700,5-700,305)
        {953,1,953,767},       // ���Ҳഹֱǽ (953,0,953,768)(�߽�)
        {763,357,765,387},     // ������ֱǽ (764,357-764,387)
        {881,387,885,637},     // ɳ���Ҳ�ǽ (883,387-883,637)
        {931,357,933,637},     // �Ҳ�߽�ǽ (932,357-932,637)
        {40,392,42,682},       //��̨�����ֱǽ

        // ˮƽǽ����չ1���ظ߶ȣ�
        {51,230,259,232},      // ��ˮƽ����ǽ (51,231-259,231)
        {41,386,259,388},      // ������ˮƽǽ (42,387-259,387)
        {419,304,470,306},     // ����ˮƽ����ǽ (420,305-701,305)
        {539,304,701,306},     //����ˮƽ����ǽ
        {699,141,784,143},     // �����ϲ�ǽ (700,142-954,142)
        {859,141,945,143},     //�����ϲ�ǽ
        {747,304,956,306},     // ��������ǽ (748,305-954,305)
        {763,356,933,358},     // ����װ��ǽ (764,357-932,357)
        {882,636,933,638},     // �����·�ǽ (883,637-932,637)
        {761,390,884,392},     //ɳ���¶�
        {2,680,1022,680},      // ���·�ˮƽǽ(�߽�)
       
        // �����ϰ���
        {415,415,496,618},     // ���ӻ����� (416,415-494,618)
        {752,452,832,598},     // �輸���� (753,452-830,598) 
        {269,619,381,666},     // �������� (270,620,380,665)
        {389,694,579,744},      // �����˰�ť���� (390,695,580,745)

        //������������
        {76,28,167,74},//����
        {64,279,166,322},//������
        {144,625,235,674},//��̨
        {528,446,639,503},//����
        {447,62,531,117},//����
        {735,40,816,90},//����
        {727,190,820,241}//����
    };
    
	player.x1 = (*new_sx) - 10;
	player.y1 = (*new_sy) - 10;
	player.x2 = (*new_sx) + 10;
	player.y2 = (*new_sy) + 10; // ��ɫ��AABB��
    numObstacles = sizeof(obstacles) / sizeof(obstacles[0]);
  
    // �߽��飨����20x20��ɫ�ߴ磩
    if 
    (player.x1 < 10 || player.x2 > 1014 || 
        player.y1 < 10 || player.y2 > 758) {
        return false;
    }

    // ��ײ���
    for (i= 0; i < numObstacles; i++) 
    {
        if (AABBOverlap(player, obstacles[i])) 
        {
            return false; // ���������Щ�����������ƶ�
        }
    }

    return true; // �����ƶ�
}



void DrawFloor()//���Ƽ�ͥƽ��ͼ
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
    puthz(87,29, "����", 32, 27, 0x000000);
    puthz(459,69, "����", 32, 27, 0x000000);
    puthz(743,43, "����", 32, 27, 0x000000);
    puthz(743,199, "����", 32, 27, 0x000000);
    puthz(542,454, "����", 32, 27, 0x000000);
    puthz(890,450, "ɳ", 32, 27, 0x000000);
    puthz(890,501, "��", 32, 27, 0x000000);
    puthz(72,279, "������", 32, 27, 0x000000);
    puthz(162,630, "��̨", 32, 27, 0x000000);
    bar2(416,415,494,618,0x00000);
    puthz(440,450,"��",32,27,0x000000);
    puthz(440,500, "��", 32, 27, 0x000000);
    puthz(440,550, "��", 32, 27, 0x000000);
    bar2(753,452,830,598,0x00000);
    puthz(767,476, "��", 32, 27, 0x000000);
    puthz(767,531, "��", 32, 27, 0x000000);

    bar2(270,620,380,665,0x00000);
    puthz(280,630, "����", 32, 27, 0x000000);

    draw_botton(390,695,580,745,0x00FF,0xDDDD);
    puthz(410,703,"���ز˵�", 32, 35, 0xD8BFD8);

    bar2(76,28,167,74,0xDC143C);//����
    bar2(64,279,164,322,0xDC143C);//������
    bar2(727,190,815,241,0xDC143C);//����
    bar2(144,630,235,674,0xDC143C);//��̨
    bar2(528,446,639,503,0xDC143C);//����
    bar2(447,62,531,117,0xDC143C);//����
    bar2(740,41,816,85,0xDC143C);//����

}
 

//���ļ� Data\\inroom.dat �ж�ȡһ�� RoomID ���͵�ֵ��
//����ļ���û��ֵ�򷵻� NONE
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




//���� roomid ���� player ��λ��
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


//���ļ� Data\\roomid.dat ��д��һ�� RoomID ���͵�ֵ
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


    // //���飺д��.txt���ԣ�
    // file = fopen("Data\\roomid.txt", "w+");
    // if (file == NULL)
    // {
    //     perror("Failed to open roomid file");
    //     return;	
    // }
    // fprintf(file, "%d", *roomid);
    // fclose(file);

}



//���ݻ��������ڵ����꣬�жϻ������Ƿ��ڷ��䣬����д��roomid.dat
void checkRoom(PlayerState *player)
{
    RoomID roomid = 0;


    // �������
    if (player->sx >= 60 && player->sx <= 404 && player->sy >= 10 && player->sy <= 222)
    {
        roomid = SECONDBEDROOM;
        writeRoomIDToFile(&roomid);
    }
    // ��������
    else if (player->sx >= 425 && player->sx <= 690 && player->sy >= 8 && player->sy <= 297)
    {
        roomid = MASTERBEDROOM;
        writeRoomIDToFile(&roomid);
    }
    // �������
    else if (player->sx >= 705 && player->sx <= 947 && player->sy >= 10 && player->sy <= 138)
    {
        roomid = KITCHEN;
        writeRoomIDToFile(&roomid);
    }
    // �������
    else if (player->sx >= 703 && player->sx <= 945 && player->sy >= 150 && player->sy <= 300)
    {
        roomid = DININGROOM;
        writeRoomIDToFile(&roomid);
    }
    // �������
    else if (player->sx >= 404 && player->sx <= 941 && player->sy >= 368 && player->sy <= 677)
    {
        roomid = LIVINGROOM;
        writeRoomIDToFile(&roomid);
    }
    // ������̨
    else if (player->sx >= 47 && player->sx <= 385 && player->sy >= 396 && player->sy <= 668)
    {
        roomid = BALCONY;
        writeRoomIDToFile(&roomid);
    }

    
}