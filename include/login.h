#ifndef __login_H__
#define __login_H__

#include<allfunc.h>

void log_in(int* page,int* unum);//������½����
void register_in(int*page);//��registerin��������
void draw_basic(void);//�������н��湲ͬ�Ļ���Ԫ��
void draw_botton(int x1 ,int y1,int x2,int y2,int Cowercolor,int Bordercolor);
void draw_commoninput(int x1,int y1,char *s);
void draw_confirmbotton(int x1,int y1,char *s);



#endif