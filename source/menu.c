#include <allfunc.h>


void menu_on(int *page)
{
    Incidentcode incidentcode; //�¼�����
    struct tm eventtime;
    int bar_width = 60;  // �������ܿ��
    char battery_level[10];  // �����ַ���
    int random_number;       // ��ǰ����
    FILE *file;

    // �ļ�·��
    char *file_path = "Data\\battary.dat";

    // ��ȡ����ֵ
    file = fopen(file_path, "rb");
    if (file == NULL)  // ����ļ������ڣ���ʼ������Ϊ100
    {
        random_number = 100;
        file = fopen(file_path, "wb");
    }
    if (file == NULL)  // ����ļ������ڣ���ʼ������Ϊ100
    {
        random_number = 100;
        file = fopen(file_path, "wb");
        if (file == NULL)
        {
            printf("�޷������ļ���\n");
            exit(1);
        }
        fwrite(&random_number, sizeof(int), 1, file);
        fclose(file);
    }
    else  // ��ȡ�ļ��еĵ���ֵ
    {
        fread(&random_number, sizeof(int), 1, file);
        fclose(file);
    }

    // ÿ�ν������ʱ����������5����СΪ0��
    random_number -= 5;
    if (random_number < 0)
    {
        random_number = 0;
    }

    // ���µĵ���ֵд���ļ�
    file = fopen(file_path, "wb");
    if (file == NULL)
    {
        printf("�޷�д���ļ���\n");
        exit(1);
    }
    fwrite(&random_number, sizeof(int), 1, file);
    fclose(file);

    // ������ֵת��Ϊ�ַ���
    itoa(random_number, battery_level, 10);
    mouse_off(&mouse);

    // ��ʼ�����棨��ͼ�ȣ�
    bar1(0, 0, 1024, 768, 0x5686BF);
    bar1(35, 32, 989, 744, 0xFFFFFF);
    ThickDiagonalLine(35,32,989,32,2,0x003399);
    ThickDiagonalLine(35,32,35,744,2,0x003399);
    ThickDiagonalLine(35,744,989,744,2,0x003399);
    ThickDiagonalLine(989,32,989,744,2,0x003399); 
    Readbmp64k(67,50,"bmp\\robot.bmp"); 
    bar1(857, 19, 1004, 67, 0x1E90FF);
    prt_hz16_size(865,25, 2,2, "���칦��", 0xFFFFFF, "HZK\\HZK16s");
    bar2(280,695,340,726,0x4D1F00);  // �����˳�粿��
    prt_hz16_size(62,695, 2, 2, "�����˵���", 0x000000, "HZK\\HZK16s");
    put_asc16_size(442,695,2,2,"%",0x000000);	
    draw_botton(511,690,615,731,0xFF7F50,0x0000FF);
    prt_hz16_size(530,695, 2, 2, "���", 0xFFFFFF, "HZK\\HZK16s");
    put_asc16_size(390,695,2,2,battery_level,0x000000);

    // ���ݵ������Ƶ�����
    if (random_number <= 20)
    {
        bar1(280, 695, 280 + (bar_width * random_number / 100), 726, 0xFAF0E6);
    }
    else if (random_number > 20 && random_number <= 50)
    {
        bar1(280, 695, 280 + (bar_width * random_number / 100), 726, 0x07CFC00);
    }
    else if (random_number > 50 && random_number <= 100)
    {
        bar1(280, 695, 280 + (bar_width * random_number / 100), 726, 0x4D1F00);
    }

    // ������ť�ͽ���Ԫ��
    draw_botton(540,130,840,200,0xFF7F50,0x0000FF);
    prt_hz16_size(605,140, 3, 3, "��ͥ����", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(540,260,840,330,0xFF7F50,0x0000FF);
    prt_hz16_size(605,270, 3, 3, "�������", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(540,390,840,460,0xFF7F50,0x0000FF);
    prt_hz16_size(585,400, 3, 3, "��������־", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(540,520,840,590,0xFF7F50,0x0000FF);
    prt_hz16_size(620,530, 3, 3, "ƽ��ͼ", 0xFFFFFF, "HZK\\HZK16s");
    // �˳���ť
    draw_botton(840,660,958,717,0xFF7F50,0x000000);
    prt_hz16_size(840,675, 2, 2, "���ص�¼", 0xFFFFFF, "HZK\\HZK16s");

    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);

        // ����Ϊ0ʱ��ֻ�ܳ��
        if (random_number == 0)
        {
            prt_hz16_size(511,646, 1, 1, "�����Ѻľ������磡", 0xFAF0E6, "HZK\\HZK16s");
            if(mouse_press(511,690,615,731)==1)  // ��簴ť
            {
                mouse_off(&mouse);
                bar1(510,645,660,680,0xfffffff); // ���ǵ���ʾ
                while(random_number<100)
                {
                    random_number += 5;
                    if(random_number > 100) random_number = 100;
                    itoa(random_number, battery_level, 10);
                    bar1(280,695,280+bar_width * random_number / 100,726,0x4D1F00);
                    bar1(385,695,425,725,0xffffff);
                    put_asc16_size(390,695,2,2,battery_level,0x000000);

                    // �����������¼�¼�
                    if (random_number == 100)
                    {
                        incidentcode = battery;
                        fstart_diary(&incidentcode, &eventtime);
                        fend_diary(&incidentcode, &eventtime);
                    }
                    delay(300);
                }
                // �����ļ��еĵ���ֵ
                file = fopen(file_path, "wb");
                if (file != NULL)
                {
                    fwrite(&random_number, sizeof(int), 1, file);
                    fclose(file);
                }
                mouse_show(&mouse);
            }
            continue; // ��ֹ��������
        }

        // ������ť�����߼����ֲ���
        if (mouse_press(540,130,840,200)==1)//��ͥ����
        {
            *page = 12;
            break;
        }
        else if (mouse_press(540,260,840,330)==1)//�������
        {
            *page = 5;
            break;
        }
        else if (mouse_press(540,390,840,460)==1)//��������־
        {
            *page = 13;
            break;
        }
        else if (mouse_press(540,520,840,590)==1)//ƽ��ͼ
        {
            *page = 17;
            break;
        }
        else if(mouse_press(857, 19, 1004, 67)==1)//���칦��
        {
            *page=15;
            break;
        }
        else if (mouse_press(840,660,958,717)==1)//���ص�¼
        {
            *page = 2;
            break;
        }
        else  if(mouse_press(511,690,615,731)==1)
        {
            mouse_off(&mouse);//�������ж�

            while(random_number<=100)
            {
                if(random_number==100)
                {
                    prt_hz16_size(640,690, 2, 2, "�ѳ����磡", 0x000000, "HZK\\HZK16s");
                    delay(1000);
                    bar1(635,690,810,723,0xffffff);
                    break;
                }
                else if(random_number<=95)
                {
                    random_number+=5;
                      // ���µĵ���ֵд���ļ�
                    file = fopen(file_path, "wb");
                    if (file == NULL)
                    {
                         printf("�޷�д���ļ���\n");
                         exit(1);
                    }
                    fwrite(&random_number, sizeof(int), 1, file);
                    fclose(file);
                    if(random_number==100)//�����ˣ���¼
                    {
                        // ��¼�¼�
                        incidentcode = battery;
                        fstart_diary(&incidentcode, &eventtime);
                        fend_diary(&incidentcode, &eventtime);
                    }
                    delay(500);
                }
                itoa(random_number, battery_level, 10);
                bar1(385,695,425,725,0xffffff);
                put_asc16_size( 390,695,2,2,battery_level,0x000000);
                if(random_number<=20)
                {
                    bar1(280,695,280+bar_width * random_number / 100,726,0xFAF0E6);
                }
                else if(random_number>20&&random_number<=50)
                {
                    bar1(280,695,280+bar_width * random_number / 100,726,0x07CFC00);
                }
                else if(random_number>50&&random_number<=100)
                {
                bar1(280,695,280+bar_width * random_number / 100,726,0x4D1F00);
                }

            }

            mouse_show(&mouse);

        }
    }
}


