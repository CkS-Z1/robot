/*initfund
���ܣ�
    1.��ȡTodaydata��������Ӧ"ȫ�ֱ���"�ĸ�ֵ���ļ��洢
    2.��ʼ������״̬��д��<windowstate.dat>;
    3.
�ļ���
    <winstate.dat>:ֻ����һ��bool����windowstate�����ڼ�¼�����Ŀ���״̬
*/

#ifndef INITFUND_H
#define INITFUND_H
#include <stdio.h>
#include <global.h>

//��ʼ����������ȡTodaydata��������Ӧȫ�ֱ����ĸ�ֵ;����todaydata
void read_todaydata(Todaydata *todaydata);
//���ݽ��յ���todaydata��ʼ������״̬��д��<winstate.dat>
void initialize_windowstate(Todaydata *todaydata);
//�ܵĳ�ʼ��fundation data����
void initialize_fundation();







#endif