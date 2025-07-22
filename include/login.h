#ifndef __login_H__
#define __login_H__

#include<allfunc.h>

void log_in(int* page,int* unum);//启动登陆界面
void register_in(int*page);//把registerin放这里了
void draw_basic(void);//绘制所有界面共同的基本元素
void draw_botton(int x1 ,int y1,int x2,int y2,int Cowercolor,int Bordercolor);
void draw_commoninput(int x1,int y1,char *s);
void draw_confirmbotton(int x1,int y1,char *s);



#endif