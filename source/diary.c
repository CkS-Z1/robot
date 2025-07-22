/**
 * @name:diary.c
 * @description: 
 *  logic:
 *  1.open project->            finitialize
 *  2.things happen->           record
 *  3.if want to get this time->timedata.dat
 *  4.things finish->           solve
 *  5.close project->           fclose
 * @file:
 * 1.diary.dat(C:\\cks\\Data\\diary.dat)
 * >>datas' input type:
 * a.finitialize_diary: <Todaydata>
 * b.fstart_diary:      <struct tm>,<Incidentcode>
 * c.fend_diary:        <Incidentcode>,<struct tm>
 * (b and c constitute a whole incident-recording)
 * 
 * 2.diary.txt(C:\\cks\\Data\\diary.txt)
 * 3.timedata.dat(C:\\cks\\Data\\timedata.dat)
 * @author:wty
 * @finishtime:4.6
*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "diary.h"
#include "global.h"



void finitialize_diary();
void fstart_diary(Incidentcode *incidentcode, struct tm *starttime);
void fend_diary(Incidentcode *incidentcode, struct tm *endtime);
void fget_time();
void fsave_time();



/**
 * @name:finitialize_diary
 * @description: ��ʼ����־��
 *               ������־�����ļ�diary.dat����־�ļ�diary.txt��
 *               ���뱾�ճ�ʼ��Ϣ�����ڡ��������¶ȣ�
 *               ����Ӧ��Ϣ��ӡ��txt����struct Todaydata��dat
 * @file:��־����C:\\cks\\Data\\diary.dat��
 *       ��־�ĵ�C:\\cks\\Data\\diary.txt��
*/
void finitialize_diary() {

    char *weekday_str[] = {"������", "����һ", "���ڶ�", "������", "������", "������", "������"};
    char *weather_str[] = {"����", "����", "����", "ѩ��"};

    FILE *txt_file, *dat_file;
    Todaydata entry;

    time_t current_time = 0;
    struct tm *local_time;

    int year = 0;
    int temperature = 0;
    int month = 0;
    int day = 0;
    Weekday weekday = 0;
    Weather weather = 0;


    // ��ʼ�����������
    srand(time(NULL));

    // ��ȡ��ǰʱ��
    current_time = time(NULL);
    local_time = localtime(&current_time);

    // ��ȡ�ꡢ�¡��ա����ڼ�
    year = local_time->tm_year + 1900;
    month = local_time->tm_mon + 1;
    day = local_time->tm_mday;
    weekday = (Weekday)local_time->tm_wday;

    // �����������
    weather = (Weather)(rand() % 4);
    // ���� 10 �� 30 ֮�������¶ȣ�ѩ���¶�Ϊ 0 �� 5
    if(weather == Snowy)
    {
        temperature = rand() % 6;
    }
    else
    {
        temperature = rand() % 21 + 10; 
    }

    // �����ṹ������洢��Ϣ
    entry.year = year;
    entry.month = month;
    entry.day = day;
    entry.weekday = weekday;
    entry.weather = weather;
    entry.temperature = temperature;

    // �� diary.txt �ļ���д����Ϣ
    txt_file = fopen("Data\\diary.txt", "a+");
    if (txt_file == NULL) {
        perror("�޷��� diary.txt �ļ�");
        return;
    }

    // ����Ϣд�� diary.txt �ļ�
    fprintf(txt_file, "%d/", year);
    fprintf(txt_file, "%d/", month);
    fprintf(txt_file, "%d  ", day);
    fprintf(txt_file, "%s  ", weekday_str[weekday]);
    fprintf(txt_file, "%s  ", weather_str[weather]);
    fprintf(txt_file, "%d��\n\n", temperature);

    // �ر� diary.txt �ļ�
    fclose(txt_file);

    // �� diary.dat �ļ��Զ�����д����Ϣ
    dat_file = fopen("Data\\diary.dat", "wb+");
    if (dat_file == NULL) {
        perror("�޷��� diary.dat �ļ�");
        return;
    }

    // ���ṹ�����д�� diary.dat �ļ�
    fwrite(&entry, sizeof(Todaydata), 1, dat_file);

    // �ر� diary.dat �ļ�
    fclose(dat_file);
}






/**
 * @name:fstart_diary
 * @description: ���¼�����ʱ�ⲿ���ã�Ҫ����Incidentcode *incidentcode, struct tm *starttime��
 *               ����������¼����ͣ���¼�¼��Ŀ�ʼ��
 *               ��"ʱ��"��"ʲô�¼����ڷ���"��"���ڴ���"д��diary.dat��diary.txt��
 *               ͨ��ָ�뷵��struct tm *starttimeҲ���ǿ�ʼʱ��ֵ
 *       ##���룺returnһ��intֵ�����ⲿcount++������¼���������¼����Թ���־���ڶ�ȡdiary.dat�ĵڼ����¼���##
 * @file:��־����C:\\cks\\Data\\diary.dat��
 *       ��־�ĵ�C:\\cks\\Data\\diary.txt��
 *       ʱ���ݴ����ݿ�C:\\cks\\Data\\timedata.dat
*/
void fstart_diary(Incidentcode *incidentcode, struct tm *starttime)
{

    FILE *fp_timedata, *txt_file, *dat_file;
    char tc = 0;
    // �����¼������Ӧ��������������
    char *incident_descriptions[] = {
        "",        // ռλ����Ϊö�ٴ� 1 ��ʼ
        "���ڿ���...",
        "���ڹص�...",
        "���ڿ���...",
        "���ڹش�...",
        "���ڹ���...",
        "��������...",
        "���ڴ�ɨ...",
        "������ˮ��ˮ...",
        "���ڽ���...",
        "���ڳ��...",
        //emergency
        "�������֣����ڴ�������...",
        "���ڴ����Դ����...",
        "���ڴ�����үү���岻��...",
        "���ڴ������������岻��...",
        "���ڴ������쳣��...",
        "���ڴ������쳣��..."
        "���ڴ�����泱ʪ..."
        "���ڴ����Ա����..."
        "���ڴ���ú��й©..."
    };



    //record start time
    fget_time();
    fsave_time();
    //return start time
    fp_timedata = fopen("Data\\timedata.dat", "rb");
    if (fp_timedata == NULL) {
        perror("�޷��� timedata.dat �ļ����ж�ȡ");
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }

    if (fread(starttime, sizeof(struct tm), 1, fp_timedata) != 1) {
        perror("��ȡ timedata.dat �ļ�ʱ����");
        fclose(fp_timedata);
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }
    fclose(fp_timedata);




    //record incident start

    // �� diary.dat �ļ��Զ�����׷��ģʽд����Ϣ
    dat_file = fopen("Data\\diary.dat", "ab");
    if (dat_file == NULL) {
        perror("�޷��� diary.dat �ļ�");
        return;
    }

    // ���¼�����д�� diary.dat �ļ�
    fwrite(incidentcode, sizeof(Incidentcode), 1, dat_file);
    fclose(dat_file);

    // �� diary.txt �ļ���׷��ģʽд����Ϣ
    txt_file = fopen("Data\\diary.txt", "a");
    if (txt_file == NULL) {
        perror("�޷��� diary.txt �ļ�");
        return;
    }

    // �����¼������ȡ��Ӧ������������д�� diary.txt �ļ�
    if (*incidentcode >= 1 && *incidentcode < sizeof(incident_descriptions) / sizeof(incident_descriptions[0])) {
        fprintf(txt_file, "%s\n", incident_descriptions[*incidentcode]);
    }

    fclose(txt_file);


}








/**
 * @name:fend_diary
 * @description: ���¼�����ʱ�ⲿ���ã�Ҫ����Incidentcode *incidentcode, struct tm *endtime��
 *               ����������¼����ͣ���¼�¼��Ľ�����
 *               ��"ʲô�¼��������"��"ʱ��"д��diary.dat��diary.txt��
 *               ͨ��ָ�뷵��struct tm *endtimeҲ���ǽ���ʱ��ֵ
 * @file:��־����C:\\cks\\Data\\diary.dat��
 *       ��־�ĵ�C:\\cks\\Data\\diary.txt��
 *       ʱ���ݴ����ݿ�C:\\cks\\Data\\timedata.dat
*/
void fend_diary(Incidentcode *incidentcode, struct tm *endtime)
{

    FILE *fp_timedata, *txt_file, *dat_file;
    char tc = 0;
    // �����¼������Ӧ��������������
    const char *incident_descriptions[] = {
        "",        // ռλ����Ϊö�ٴ� 1 ��ʼ
        "����ɿ���",
        "����ɹص�",
        "����ɿ���",
        "����ɹش�",
        "����ɹ���",
        "���������",
        "����ɴ�ɨ",
        "�������ˮ��ˮ",
        "����ɽ���",
        "����ɳ��",
        //emergency
        "����ɻ��ִ���",
        "����ɵ�Դ���ϴ���",
        "�������үү���岻�ʴ���",
        "��������������岻�ʴ���",
        "����ɴ��������쳣����",
        "������ſ����쳣����",
        "���泱ʪ������ɴ���",
        "��Ա����������ɴ���",
        "ú��й©������ɴ���"
    };



    //get end time
    fget_time();
    //return end time
    fp_timedata = fopen("Data\\timedata.dat", "rb");
    if (fp_timedata == NULL) {
        perror("�޷��� timedata.dat �ļ����ж�ȡ");
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }

    if (fread(endtime, sizeof(struct tm), 1, fp_timedata) != 1) {
        perror("��ȡ timedata.dat �ļ�ʱ����");
        fclose(fp_timedata);
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }
    fclose(fp_timedata);




    //record incident end

    // �� diary.dat �ļ��Զ�����׷��ģʽд����Ϣ
    dat_file = fopen("Data\\diary.dat", "ab");
    if (dat_file == NULL) {
        perror("�޷��� diary.dat �ļ�");
        return;
    }

    // ���¼�����д�� diary.dat �ļ�
    fwrite(incidentcode, sizeof(Incidentcode), 1, dat_file);
    fclose(dat_file);

    // �� diary.txt �ļ���׷��ģʽд����Ϣ
    txt_file = fopen("Data\\diary.txt", "a");
    if (txt_file == NULL) {
        perror("�޷��� diary.txt �ļ�");
        return;
    }

    // �����¼������ȡ��Ӧ������������д�� diary.txt �ļ�
    if (*incidentcode >= 1 && *incidentcode < sizeof(incident_descriptions) / sizeof(incident_descriptions[0])) {
        fprintf(txt_file, "%s\n���", incident_descriptions[*incidentcode]);
    }

    fclose(txt_file);




    //record endtime
    fsave_time();


}











/**
 * @name:fget_time
 * @description: ��ȡ��ǰ����ʱ�䲢�� tm ���ʹ��� timedata.dat �ļ�
 * @file:ʱ���ݴ����ݿ�C:\\cks\\Data\\timedata.dat
*/
void fget_time() {
    time_t current_time;
    struct tm localtimeori;
    struct tm *local_time = &localtimeori;
    char tc = 0;
    FILE *fp;

    // ��ȡ��ǰʱ���
    current_time = time(NULL);
    // ��ʱ���ת��Ϊ����ʱ��
    local_time = localtime(&current_time);

    // �� timedata.dat �ļ��Զ�����д��ģʽ
    fp = fopen("Data\\timedata.dat", "wb");
    if (fp == NULL) {
        perror("�޷��� timedata.dat �ļ�����д��");
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }

    // ������ʱ����Ϣ�Զ�������ʽд���ļ�
    fwrite(local_time, sizeof(struct tm), 1, fp);

    // �ر��ļ�
    fclose(fp);
}


/**
 * @name:fsave_time
 * @description:�� timedata.dat �ļ��ж�ȡ tm ����ʱ��
 *              ��ת�浽 diary.txt��diary.dat �ļ�
 * @file:��־����C:\\cks\\Data\\diary.dat��
 *       ��־�ĵ�C:\\cks\\Data\\diary.txt
 */
void fsave_time() {
    char time_str[100];
    struct tm read_time;
    char tc = 0;
    FILE *fp_dat, *fp_txt, *fp_diarydat;

    // �� timedata.dat �ļ��Զ����ƶ�ȡģʽ
    fp_dat = fopen("Data\\timedata.dat", "rb");
    if (fp_dat == NULL) {
        perror("�޷��� timedata.dat �ļ����ж�ȡ");
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }

    // �� timedata.dat �ļ��ж�ȡʱ����Ϣ
    if (fread(&read_time, sizeof(struct tm), 1, fp_dat) != 1) {
        perror("��ȡ timedata.dat �ļ�ʱ����");
        fclose(fp_dat);
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }
    fclose(fp_dat);

    // �� diary.dat �ļ���д��ʱ��
    fp_diarydat = fopen("Data\\diary.dat", "ab");
    if (fp_diarydat == NULL) {
        perror("�޷��� diary.dat �ļ�����д��");
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }

    // �� timedata.dat�� ʱ����Ϣд�� diary.dat �ļ�
    fwrite(&read_time, sizeof(struct tm), 1, fp_diarydat);

    // �ر��ļ�
    fclose(fp_diarydat);

    // �� diary.txt �ļ���д��ʱ��
    fp_txt = fopen("Data\\diary.txt", "a");
    if (fp_txt == NULL) {
        perror("�޷��� diary.txt �ļ�����д��");
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }

    // ����ȡ����ʱ����Ϣ��ʽ��Ϊ�ַ���
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &read_time);

    // ����ʽ�����ʱ����Ϣд�� diary.txt �ļ�
    fprintf(fp_txt, "ʱ��: %s\n", time_str);

    // �ر��ļ�
    fclose(fp_txt);
}