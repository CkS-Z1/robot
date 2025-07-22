#ifndef WASD_H
#define WASD_H

#include<allfunc.h>

#define UP 0x4800
#define DOWN 0x5000
#define RIGHT 0x4D00
#define LEFT 0x4B00
#define MOVE_STEP 10
#define E_KEY_UPPER 0x45  
#define E_KEY_LOWER 0x65



typedef enum
{
    false,
    true
} bool;



typedef struct{
    int sx; // ��ɫ�ĺ�����
    int sy; // ��ɫ��������
}PlayerState;



void updatePosition(int k, int *sx, int *sy);
void clearPreviousPosition(int *sx, int *sy);
bool canMove(int *new_sx, int *new_sy);
void DrawFloor();                               //���Ƽ�ͥƽ��ͼ
RoomID readRoomIDFromFile();
void setPlayerPosition(RoomID *roomid, PlayerState *player);
void writeRoomIDToFile(RoomID *roomid);
void checkRoom(PlayerState *player);
void gamei(int *page);





#endif

