#include <allfunc.h>
struct HealthData 
{
    int systolic;       // ����ѹ (mmHg)
    int diastolic;      // ����ѹ (mmHg)
    int respiration;    // ����Ƶ�� (��/����)
    int heart_rate;     // ���� (bpm)
};

struct HealthData generate_health_data() 
{
    struct HealthData data;
    srand(time(0)); // �������������[3]
    data.systolic = 90 + rand() % 51;  // 90-140 ��������ѹ��������Χ��90-140mmHg����Ѫѹǰ�ڣ�120-139/80-89 
    data.diastolic = 60 + rand() % 31; //��������ѹ��������Χ��60-90mmHg�� ע�⣺����ѹӦС������ѹ 
    while(data.diastolic >= data.systolic)
 {                
        data.diastolic = 60 + rand() % 31; // ȷ�����������
 }
    data.respiration = 12 + rand() % 9;  // ����Ƶ�ʣ�����������12-20��/���ӣ�
     // ���ʣ�������60-100bpm���˶�Ա���ܵ���40��
    data.heart_rate = 40 + rand() % 61;  // ��չ��Χ��40-100   
    return data;
}
int  healthmonitor(int* page);
int   data_check(int *page);
void write_healthdata(struct HealthData data, const char* person) ;

void write_healthdata(struct HealthData data, const char* person) 
{
    FILE* fp;
    char datetime_str[120];
    time_t rawtime;
    struct tm* timeinfo;
    

    // ��ȡ��ǰʱ��
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(datetime_str, sizeof(datetime_str), "%Y-%m-%d %H:%M:%S", timeinfo);

    // �� CSV �ļ�
    fp = fopen("hecare\\hedata.csv", "a+"); // ��׷�ӷ�ʽ��
    if (fp == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    // ��������ļ���д�������
    fseek(fp, 0, SEEK_END); // �ƶ����ļ�ĩβ
    if (ftell(fp) == 0) { // ����ļ�Ϊ�գ���д�����
        fprintf(fp, "ʱ��,��ɫ,����ѹ(mmHg),����ѹ(mmHg),����Ƶ��(��/����),����(bpm)\n");
    }

    // д�����ݣ�������ɫ��Ϣ
    fprintf(fp, "%s,%s,%d,%d,%d,%d\n", datetime_str, person, data.systolic, data.diastolic, data.respiration, data.heart_rate);

    // �ر��ļ�
    fclose(fp);
}

int healthmonitor(int* page)
{
    struct HealthData current_data;
    char systolic_str[16], diastolic_str[16];
    char respiration_str[16], heart_rate_str[16];
    int j;
    char* file_path = NULL;        // ���ڴ洢��ǰ��ɫ�Ľ�������·��
    const char* person = NULL;     // ���ڱ�ǽ�ɫ��үү�����̣�

    mouse_off(&mouse);
    delay(100);
    bar1(0, 0, 1024, 768, 0x5686BF);
    bar1(35, 32, 989, 744, 0xFFFFFF);
    ThickDiagonalLine(35, 32, 989, 32, 2, 0x003399);
    ThickDiagonalLine(35, 32, 35, 744, 2, 0x003399);
    ThickDiagonalLine(35, 744, 989, 744, 2, 0x003399);
    ThickDiagonalLine(989, 32, 989, 744, 2, 0x003399);
    Readbmp64k(84, 73, "bmp\\yeye.bmp");
    Readbmp64k(715, 73, "bmp\\nainai.bmp");
    bar1(83, 335, 254, 387, 0xFFFFFF);
    bar1(800, 345, 938, 400, 0xFFFFFF);
    bar1(49, 410, 175, 450, 0x24367D); // ����ѹ
    puthz(60, 418, "����ѹ", 24, 24, 0xFFFFFF);
    bar1(49, 505, 175, 545, 0x24367D); // ����ѹ
    puthz(60, 513, "����ѹ", 24, 24, 0xFFFFFF);
    bar1(49, 591, 175, 631, 0x24367D); // ����Ƶ��
    puthz(60, 599, "����Ƶ��", 24, 24, 0xFFFFFF);
    bar1(49, 674, 175, 714, 0x24367D); // ����
    puthz(60, 682, "��������", 24, 24, 0xFFFFFF);
    draw_botton(103, 340, 274, 395, 0xB85798, 0xDDDD);
    prt_hz16_size(145, 355, 2, 2, "үү", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(717, 345, 888, 395, 0xB85798, 0xDDDD);
    prt_hz16_size(769, 355, 2, 2, "����", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(800, 688, 950,722, 0xBC8F8F, 0xFFEFD5);
    prt_hz16_size(830, 690, 2, 2, "����", 0xFFFFFF, "HZK\\HZK16s");
    bar1(800, 660, 957, 685, 0xF5FFFA);
    puthz(800, 660, "��ѯ�������", 24, 24, 0x000000);
    mouse_on(mouse);

    while (1)
    {
        mouse_show(&mouse);
        if (mouse_press(83, 340, 254, 395) == 1) // �ж���үү
        {
            
            mouse_off(&mouse);
            file_path = "bmp\\health2.dat";
            person = "үү";
        }
        else if (mouse_press(737, 345, 908, 395) == 1) // �ж�������
        {
            
            mouse_off(&mouse);
            file_path = "bmp\\health1.dat";
            person = "����";
        }

        if (file_path != NULL)
        {
            FILE* file;

            // ���ɽ�������
            current_data = generate_health_data();

            // д�뽡�����ݵ� CSV �ļ���������ɫ��Ϣ��
            write_healthdata(current_data, person);

            // ���浱ǰ�������ݵ��������ļ�
            file = fopen(file_path, "wb");
            if (file != NULL)
            {
                fwrite(&current_data, sizeof(struct HealthData), 1, file);
                fclose(file);
            }

            // ������ת��Ϊ�ַ�������ʾ�ڽ�����
            itoa(current_data.systolic, systolic_str, 10);
            itoa(current_data.diastolic, diastolic_str, 10);
            itoa(current_data.respiration, respiration_str, 10);
            itoa(current_data.heart_rate, heart_rate_str, 10);

            puthz(297, 136, "����Ϊ�����ɽ����������", 32, 32,0x000000);
            for (j = 0; j < 3; j++)
            {
                puthz(610 + 20 * j, 180, "��", 24, 24, 0x000000);
                delay(1000);
            }
            put_asc16_size(180, 418, 2, 2, systolic_str, 0x000000); // ��ӡ����ѹ
            put_asc16_size(270, 418, 2, 2, "mmHg", 0x000000);
            put_asc16_size(180, 513, 2, 2, diastolic_str, 0x000000); // ��ӡ����ѹ
            put_asc16_size(270, 513, 2, 2, "mmHg", 0x000000);
            put_asc16_size(180, 599, 2, 2, respiration_str, 0x000000); // ��ӡ����Ƶ��
            prt_hz16_size(270, 599, 1, 1, "��", 0x000000, "HZK\\HZK16s");
            put_asc16_size(290, 599, 1, 1, "/", 0x000000);
            prt_hz16_size(305, 599, 1, 1, "����", 0x000000,"HZK\\HZK16s");
            put_asc16_size(180, 682, 2, 2, heart_rate_str, 0x000000); // ��ӡ����
            put_asc16_size(270, 682, 2, 2, "bpm", 0x000000);
            delay(1000); // ��ʱ1��
            if (current_data.systolic > 140 || current_data.diastolic > 90)
            {
                puthz(366, 460, "���˵�Ѫѹ���ߣ��뼰ʱ��ҽ", 24, 24, 0x000000);
            }
                else if (current_data.systolic < 90 || current_data.diastolic < 60)
            {
                puthz(366, 460, "���˵�Ѫѹ���ͣ��뼰ʱ��ҽ", 24, 24, 0x000000);
            }
            else
            {
                puthz(366, 460, "Ѫѹ����", 24, 24, 0x000000);
            }
            
            delay(1000);
            if (current_data.respiration < 12)
            {
                puthz(368, 599, "����Ƶ�ʹ���", 24, 24, 0x000000);
            }
            else if (current_data.respiration > 20)
            {
                puthz(368, 599, "����Ƶ�ʹ���", 24, 24, 0x000000);
            }
            else
            {
                puthz(368, 599, "����Ƶ������", 24, 24, 0x000000);
            }
            
            delay(1000);
            if (current_data.heart_rate < 60)
            {
                puthz(366, 682, "����Ƶ�ʹ�������ע���ҽ", 24, 24, 0x000000);
            }
            else if (current_data.heart_rate > 100)
            {
                puthz(366, 682, "����Ƶ�ʹ��죬��ע���ҽ", 24, 24, 0x000000);
            }
            else
            {
                puthz(366, 682, "����Ƶ������", 24, 24, 0x000000);
            }
            bar1(290, 133, 682, 330, 0xFFFFFF); // �����ʾ����
            puthz(500,547, "��ǰ��", 24, 24, 0x000000);
            puthz(670,547,"�ļ����в鿴�����������ݣ�", 24, 24, 0x000000);
            put_asc16_size(570,544,2,2,"hecare",0xC0C0C0);
            delay(1500);
            bar1(180,415,700,712,0xffffff); // ��ս�����������
            bar1(490,544,970,650,0xffffff); // ����ļ�����ʾ����
            mouse_on(mouse);
            file_path = NULL; // ����·���������ظ�����
        }
        else if (mouse_press(800, 660, 957, 685) == 1)
        {
            data_check(page);
            break;
        }
        else if (mouse_press(800, 688, 950,722) == 1) // ���ذ�ť
        {
            *page = 4;
            break;
        }

    }

    return 0;
}


int data_check(int *page)
{
    struct HealthData loaded_data;
    char systolic_str[16], diastolic_str[16];
    char respiration_str[16], heart_rate_str[16];
    char *file_path = NULL; // ���ڴ洢��ǰ��ɫ�Ľ�������·��

    mouse_off(&mouse);
    delay(100);
    bar1(35, 32, 989, 744, 0xFFFFFF);
    ThickDiagonalLine(35, 32, 989, 32, 2, 0x003399);
    ThickDiagonalLine(35, 32, 35, 744, 2, 0x003399);
    ThickDiagonalLine(35, 744, 989, 744, 2, 0x003399);
    ThickDiagonalLine(989, 32, 989, 744, 2, 0x003399);
    ThickDiagonalLine(989, 32, 989, 744, 2, 0x003399);
    ThickDiagonalLine(144, 200,636,200, 2, 0xFAF0E6);
    ThickDiagonalLine(636,200,636,253,2, 0xFAF0E6);
    ThickDiagonalLine(144,253,636,253,2, 0xFAF0E6);
    ThickDiagonalLine(144,253,144,200,2, 0xFAF0E6);
    bar1(144,200,636,253,0xFFFF99);
    bar1(49, 410, 175, 450, 0x24367D); // ����ѹ
    puthz(60, 418, "����ѹ", 24, 24, 0xFFFFFF);
    bar1(49, 505, 175, 545, 0x24367D); // ����ѹ
    puthz(60, 513, "����ѹ", 24, 24, 0xFFFFFF);
    bar1(49, 591, 175, 631, 0x24367D); // ����Ƶ��
    puthz(60, 599, "����Ƶ��", 24, 24, 0xFFFFFF);
    bar1(49, 674, 175, 714, 0x24367D); // ����
    puthz(60, 682, "��������", 24, 24, 0xFFFFFF);
    draw_botton(103, 340, 274, 395, 0xB85798, 0xDDDD);
    prt_hz16_size(145, 355, 2, 2, "үү", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(717, 345, 888, 395, 0xB85798, 0xDDDD);
    prt_hz16_size(769, 355, 2, 2, "����", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(800, 698, 950, 735, 0xBC8F8F, 0xFFEFD5);
    prt_hz16_size(835, 700, 2, 2, "����", 0xFFFFFF, "HZK\\HZK16s");
    puthz(145,214, "�����ť���ɲ�ѯ����ļ������", 32,32, 0x000000);
    mouse_on(mouse);
    while (1)
    {
        mouse_show(&mouse);
        if (mouse_press(83, 340, 254, 395) == 1) // үү
        {
            file_path = "bmp\\health2.dat";
        }
        else if (mouse_press(737, 345, 908, 395) == 1) // ����
        {
            file_path = "bmp\\health1.dat";
        }

        if (file_path != NULL)
        {
            FILE *file = fopen(file_path, "rb");
            if (file != NULL)
            {
                fread(&loaded_data, sizeof(struct HealthData), 1, file);
                fclose(file);

                // ������ת��Ϊ�ַ���
                itoa(loaded_data.systolic, systolic_str, 10);
                itoa(loaded_data.diastolic, diastolic_str, 10);
                itoa(loaded_data.respiration, respiration_str, 10);
                itoa(loaded_data.heart_rate, heart_rate_str, 10);

                // ��ʾ��������
                bar1(176, 418, 737, 714, 0xFFFFFF);
                put_asc16_size(180, 418, 2, 2, systolic_str, 0x000000); // ����ѹ
                put_asc16_size(270, 418, 2, 2, "mmhg", 0x000000);
                put_asc16_size(180, 513, 2, 2, diastolic_str, 0x000000); // ����ѹ
                put_asc16_size(270, 513, 2, 2, "mmhg", 0x000000);
                put_asc16_size(180, 599, 2, 2, respiration_str, 0x000000); // ����Ƶ��
                put_asc16_size(270, 599, 2, 2, "bpm", 0x000000);
                put_asc16_size(180, 682, 2, 2, heart_rate_str, 0x000000); // ����
                put_asc16_size(270, 682, 2, 2, "HR", 0x000000);
            }
            else
            {
                puthz(366, 460, "��δ�Դ˶�����й��������ݲ���", 24, 24, 0xFF0000);
            }

            file_path = NULL; // ����Ϊ NULL
        }
        else if (mouse_press(800, 700, 950, 735) == 1) // ����
        {
            *page = 5; 
            break;
        }
    }
    return 0;
}
