#ifndef ANIME_H
#define ANIME_H
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"hz.h"
#include"mouse.h"
#include"SVGA.h"
#include"global.h"
#include"lgfunc.h"
#include"menu.h"
#include"robot.h"
#include"diary.h"
#include "initfund.h"



//����ɨ��������Ϣ�ṹ��
typedef struct {
    int x;
    int y;
    int width;
    int height;
} Brush;


//����ˮ��������Ϣ�ṹ��
typedef struct {
    int x;
    int y;
    int width;
    int height;  
} Kettle;


//������������Ϣ�ṹ��
typedef struct {
    int x;
    int y;
    int width;
    int height;  
} Bottle;


//���廨��������Ϣ�ṹ��
typedef struct {
    int x;
    int y;
    int width;
    int height;  
} Sprinkler;



void winanime(int *page);//ȫ���룬ִ�п��ش�����
void openwin_anime(Robot *Rob);//��������
void closewin_anime(Robot *Rob);//�ش�����

void draw_winbackground(Robot *Rob);//�������ش�ȫ����
void draw_windowbase();//���ƿ����ش���ͬԪ�أ�������
void draw_openwin();//������
void draw_closewin();//���ش�




void brushanime(int *page);//ɨ��ȫ���룬ִ��ɨ�ض���
void cleaning_anime(Robot *Rob, Brush *brush);//����ɨ�ض���

void draw_cleaningbackground(Robot *Rob, Brush *brush);//����ɨ�ؽ��汳���������baseimages
void draw_brush(Brush *brush);//����ɨ��
void draw_cleaningtip();//���ơ�����ɨ�ء�����
void draw_cleanuptip();//���ơ������ɨ������������1����Զ���ʧ
void draw_cleanningroom();//�������ɨ�ؽ��汳��




void teaanime(int *page);//��ˮȫ���룬ִ�е�ˮ����
void boilwater_anime(Robot *Rob, Kettle *kettle, Bottle *bottle);//ִ�л�������ˮ��ˮ����

void draw_livingroom(Robot *Rob, Kettle *kettle, Bottle *bottle);//���Ƶ�ˮ���汳���������baseimages
void draw_wbottle(Bottle *bottle);//��δװˮ��ˮ��
void draw_hbottle(Bottle *bottle);//��װ�뱭ˮ��ˮ��
void draw_mbottle(Bottle *bottle);//��װ��ˮ��ˮ��
void draw_zkettle(Kettle *kettle);//���ŵ�ˮ��
void draw_xkettle(Kettle *kettle);//б�ŵ�ˮ��
void draw_boilingtip();//���ơ�������ˮ���͡���ˮ��ɡ�����
void draw_bottlefulltip();//�汳�������ơ���⵽ˮ����װ����������
void draw_finishboilingtip();//�汳�������ơ������ˮ���͡��͵�ˮ��������




void wateranime(int *page);//����ȫ���룬ִ�н�������
void watering_anime(Robot *Rob, Sprinkler *sprinkler);//ִ�н�������

void draw_wateringbackground(Robot *Rob, Sprinkler *sprinkler);//���ƽ������汳���������baseimages
void draw_flower(int x,int y);//������
void draw_xsprinkler(Sprinkler *sprinkler);//��б�ŵĻ���
void draw_zsprinkler(Sprinkler *sprinkler);//�����ŵĻ���
void draw_water(Sprinkler *sprinkler);//��������ˮ
void draw_fullsprinktip();//���ơ�����װˮ���͡�����ɡ�����
void draw_alreadywatertip();//�汳�������ơ�����ɽ�����������
void draw_finishwatertip();//�汳�������ơ�һ���Խ�̫��ˮ��ֲ�ﲻ��Ŷ��������


#endif