/*initfund.c
    <initialize fundation.c>
���ܣ�
    1.��ȡTodaydata��������Ӧ"ȫ�ֱ���"�ĸ�ֵ���ļ��洢
    2.��ʼ������״̬��д��<windowstate.dat>;
    3.
�ļ���
    <winstate.dat>:ֻ����һ��bool����windowstate�����ڼ�¼�����Ŀ���״̬
*/

#include "initfund.h"

void read_todaydata(Todaydata *todaydata);
void initialize_windowstate(Todaydata *todaydata);
void initialize_fundation();

//��ʼ����������ȡTodaydata��������Ӧȫ�ֱ����ĸ�ֵ;����todaydata
void read_todaydata(Todaydata *todaydata)
{
    FILE *fp = NULL;

    // ���ļ��Զ����ƶ�ȡtodaydata
    fp = fopen("Data\\diary.dat", "rb");
    if (fp == NULL) 
    {
        perror("can't open diary.dat file");
        exit(1);
    }

    // ���ļ��ж�ȡ Todaydata ����
    if (fread(todaydata, sizeof(Todaydata), 1, fp) != 1)
    {
        perror("error in read_todaydata reading diary.dat file");
        fclose(fp);
        exit(1);
    } 

    // �ر��ļ�
    fclose(fp);
}

//���ݽ��յ���todaydata��ʼ������״̬��д��<winstate.dat>
void initialize_windowstate(Todaydata *todaydata) 
{
    FILE *fp = NULL;
    Windowstate windowstate;

    // �������������ʼ������״̬
    if (todaydata->weather == Rainy || todaydata->weather == Snowy) 
    {
        windowstate = WindowClose;
    } 
    else 
    {
        windowstate = WindowOpen;
    }

    // ���ļ��Զ����Ƹ���д��winstate.dat
    fp = fopen("Data\\winstate.dat", "wb");
    if (fp == NULL) 
    {
        perror("can't open winstate.dat file");
        exit(1);
    }

    // ������״̬д���ļ�
    if (fwrite(&windowstate, sizeof(Windowstate), 1, fp) != 1) {
        perror("error in writing into winstate.dat file");
        fclose(fp);
        exit(1);
    }

    // �ر��ļ�
    fclose(fp);
}

//�ܵĳ�ʼ��fundation data����
void initialize_fundation() 
{
    Todaydata todaydata;

    // ��ȡTodaydata
    read_todaydata(&todaydata);

    // ��ʼ������״̬��boolֵ����<winstate.dat>
    initialize_windowstate(&todaydata);
}