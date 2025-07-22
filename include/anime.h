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



//定义扫把坐标信息结构体
typedef struct {
    int x;
    int y;
    int width;
    int height;
} Brush;


//定义水壶坐标信息结构体
typedef struct {
    int x;
    int y;
    int width;
    int height;  
} Kettle;


//定义茶壶坐标信息结构体
typedef struct {
    int x;
    int y;
    int width;
    int height;  
} Bottle;


//定义花洒坐标信息结构体
typedef struct {
    int x;
    int y;
    int width;
    int height;  
} Sprinkler;



void winanime(int *page);//全代码，执行开关窗动画
void openwin_anime(Robot *Rob);//开窗动画
void closewin_anime(Robot *Rob);//关窗动画

void draw_winbackground(Robot *Rob);//画开窗关窗全背景
void draw_windowbase();//绘制开窗关窗共同元素：窗架子
void draw_openwin();//画开窗
void draw_closewin();//画关窗




void brushanime(int *page);//扫地全代码，执行扫地动画
void cleaning_anime(Robot *Rob, Brush *brush);//播放扫地动画

void draw_cleaningbackground(Robot *Rob, Brush *brush);//绘制扫地界面背景，并存好baseimages
void draw_brush(Brush *brush);//绘制扫把
void draw_cleaningtip();//绘制“正在扫地”弹窗
void draw_cleanuptip();//绘制“完成清扫！”弹窗并于1秒后自动消失
void draw_cleanningroom();//绘制完成扫地界面背景




void teaanime(int *page);//倒水全代码，执行倒水动画
void boilwater_anime(Robot *Rob, Kettle *kettle, Bottle *bottle);//执行机器人烧水倒水动画

void draw_livingroom(Robot *Rob, Kettle *kettle, Bottle *bottle);//绘制倒水界面背景，并存好baseimages
void draw_wbottle(Bottle *bottle);//画未装水的水杯
void draw_hbottle(Bottle *bottle);//画装半杯水的水杯
void draw_mbottle(Bottle *bottle);//画装满水的水杯
void draw_zkettle(Kettle *kettle);//正放的水壶
void draw_xkettle(Kettle *kettle);//斜放的水壶
void draw_boilingtip();//绘制“正在烧水”和“烧水完成”弹窗
void draw_bottlefulltip();//存背景，绘制“监测到水杯已装满！”弹窗
void draw_finishboilingtip();//存背景，绘制“完成烧水”和“和倒水！”弹窗




void wateranime(int *page);//浇花全代码，执行浇花动画
void watering_anime(Robot *Rob, Sprinkler *sprinkler);//执行浇花动画

void draw_wateringbackground(Robot *Rob, Sprinkler *sprinkler);//绘制浇花界面背景，并存好baseimages
void draw_flower(int x,int y);//画花盆
void draw_xsprinkler(Sprinkler *sprinkler);//画斜着的花洒
void draw_zsprinkler(Sprinkler *sprinkler);//画正着的花洒
void draw_water(Sprinkler *sprinkler);//画洒出的水
void draw_fullsprinktip();//绘制“正在装水”和“已完成”弹窗
void draw_alreadywatertip();//存背景，绘制“已完成浇花！”弹窗
void draw_finishwatertip();//存背景，绘制“一次性浇太多水对植物不好哦！”弹窗


#endif