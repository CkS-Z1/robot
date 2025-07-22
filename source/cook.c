#include <allfunc.h>
typedef struct
{
    int soup_selected[3];
    int staple_selected[4];
    int fry_selected[9];
} Food;
int cook_meal(int *page);
void cook_design(void);
int orderfood(int *page,Food* food_selection);
int  cook_staplefood(int *page,Food* food_selection);
int  cook_fry(int *page,Food* food_selection);
int check_food(int *page,Food* food_selection);
int cook_soup(int *page,Food* food_selection);
void save_food_selection(const char *filename, Food *food_selection);
void load_food_selection(const char *filename, Food *food_selection);
int cook_make(int *page,Food *food_selection) ;

void save_food_selection(const char *filename, Food *food_selection) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(food_selection, sizeof(Food), 1, file);
        fclose(file);
    } else {
        printf("�޷����ļ�����д��.\n");
    }
}

void load_food_selection(const char *filename, Food *food_selection) {
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        fread(food_selection, sizeof(Food), 1, file);
        fclose(file);
    } else {
        printf("�޷����ļ����ж�ȡ.\n");
        // ��ʼ��Ϊ 0������δ���ص�����ʱ����
        memset(food_selection, 0, sizeof(Food));
    }
}


int cook_meal(int *page)
{
    int i; 
    Food food_selection; 
    load_food_selection("bmp\\food.dat", &food_selection); // ���ļ�����״̬
    

    mouse_off(&mouse);
    cook_design();//���������Ļ���Ԫ�� 
    mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(925,727,1013,756)==1)
        {
            *page=12;
            break;
        }
        else if(mouse_press(42,25,175,66)==1)
        {
            orderfood(page,&food_selection);
            break;
        }
        save_food_selection("bmp\\food.dat", &food_selection); // ����״̬
    }
}




int orderfood(int *page,Food* food_selection)
{
    
    mouse_off(&mouse);
    bar1(0,0,1024,768,0xfffffff);
    Readbmp64k(0,0,"bmp\\dishes.bmp");  
    bar1(71,314,266,366,0xFF7F50);
    bar1(417,314,614,366,0xFF7F50);
    bar1(744,314,744+195,366,0xFF7F50);
    prt_hz16_size(123,325,2,2,"����",0x000000,"HZK\\HZK16s");
    prt_hz16_size(473,325,2,2,"��ʳ",0x000000,"HZK\\HZK16s");
    prt_hz16_size(803,325,2,2,"����",0x000000,"HZK\\HZK16s");
    prt_hz16_size(34,666,2,2,"��ѡ������緹��Ʒ",0x000000,"HZK\\HZK16s");
    ThickDiagonalLine(977,21,1006,53,2,0xE6E6FA);
    ThickDiagonalLine(977,53,1006,21,2,0xE6E6FA);
    bar1(525,664,780,700,0xFF7F50);
    prt_hz16_size(529,666,2,2,"�鿴������ѡ��Ʒ",0x000000,"HZK\\HZK16s");
    mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(977,21,1006,53)==1)
        {
            *page=11;
            break;
        }
        if(mouse_press(71,314,266,366)==1)//����
        {
            cook_soup(page,food_selection);
            break;
        }
        if(mouse_press(417,314,614,366)==1)
        {
            cook_staplefood(page,food_selection);
            break;
        }
        if(mouse_press(744,314,744+195,366)==1)
        {
            cook_fry(page,food_selection);
            break;
        }
        if(mouse_press(525,664,780,700)==1)
        {
            check_food(page,food_selection);
            break;
        }
    }
}

int check_food(int *page, Food *food_selection) {
    int y1 = 100, y2 = 100, y3 = 100; // Y������ʼλ��
    int has_selected = 0;             // ��־�Ƿ����ѹ�ѡ�Ĳ�Ʒ
    int i;

    // ���ļ���������
    load_food_selection("bmp\\food.dat", food_selection);

    mouse_off(&mouse);
    bar1(0, 0, 1024, 768, 0xffffff); // ����
    prt_hz16_size(100, 50, 2, 2, "�ѹ�ѡ�Ĳ�Ʒ����", 0x000000, "HZK\\HZK16s");
    put_asc16_size(360, 50, 2, 2, ":", 0x000000);

    // �������
    for (i = 0; i < 3; i++) {
        if (food_selection->soup_selected[i] == 1) {
            has_selected = 1;
            switch (i) {
                case 0:
                    prt_hz16_size(30, y1, 2, 2, "ź��", 0x000000, "HZK\\HZK16s");
                    y1 += 30;
                    break;
                case 1:
                    prt_hz16_size(30, y1, 2, 2, "������������", 0x000000, "HZK\\HZK16s");
                    y1 += 30;
                    break;
                case 2:
                    prt_hz16_size(30, y1, 2, 2, "�ϲ���", 0x000000, "HZK\\HZK16s");
                    y1 += 30;
                    break;
            }
        }
    }

    // �����ʳ
    for (i = 0; i < 4; i++) {
        if (food_selection->staple_selected[i] == 1) {
            has_selected = 1;
            switch (i) {
                case 0:
                    prt_hz16_size(250, y2, 2, 2, "�׷�", 0x000000, "HZK\\HZK16s");
                    y2 += 30;
                    break;
                case 1:
                    prt_hz16_size(250, y2, 2, 2, "����", 0x000000, "HZK\\HZK16s");
                    y2 += 30;
                    break;
                case 2:
                    prt_hz16_size(250, y2, 2, 2, "�ӱ�", 0x000000, "HZK\\HZK16s");
                    y2 += 30;
                    break;
                case 3:
                    prt_hz16_size(250, y2, 2, 2, "��ͷ", 0x000000, "HZK\\HZK16s");
                    y2 += 30;
                    break;
            }
        }
    }

    // ������
    for (i = 0; i < 9; i++) {
        if (food_selection->fry_selected[i] == 1) {
            has_selected = 1;
            switch (i) {
                case 0:
                    prt_hz16_size(400, y3, 2, 2, "��������˿", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 1:
                    prt_hz16_size(400, y3, 2, 2, "������˿", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 2:
                    prt_hz16_size(400, y3, 2, 2, "���ѳ���", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 3:
                    prt_hz16_size(400, y3, 2, 2, "���Ŷ���", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 4:
                    prt_hz16_size(400, y3, 2, 2, "��������", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 5:
                    prt_hz16_size(400, y3, 2, 2, "�峴ʱ��", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 6:
                    prt_hz16_size(400, y3, 2, 2, "��������", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 7:
                    prt_hz16_size(400, y3, 2, 2, "����Ϻ", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 8:
                    prt_hz16_size(400, y3, 2, 2, "������", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
            }
        }
    }

    // ���û�й�ѡ�κβ�Ʒ
    if (!has_selected) {
        prt_hz16_size(100, y1, 2, 2, "��δѡ���κβ�Ʒ", 0xFF0000, "HZK\\HZK16s");
    }

    // �������ʼ��⿡���ť
    if (has_selected) {
        bar1(800, 600, 1008, 650, 0xFF7F50); // ����״̬
        prt_hz16_size(810, 610, 2, 2, "�����ʼ���", 0x000000, "HZK\\HZK16s");
    } else {
        bar1(800, 600, 1008, 650, 0xF5FFFA); // ����״̬
        prt_hz16_size(810, 610, 2, 2, "�޲�Ʒ�����", 0xB0E0E6, "HZK\\HZK16s");
    }

    // ���ذ�ť
    draw_botton(884, 712, 1011, 755, 0xBC8F8F, 0xffffff);
    prt_hz16_size(915, 715, 2, 2, "����", 0x000000, "HZK\\HZK16s");

    mouse_on(mouse);
    while (1) {
        mouse_show(&mouse);

        // ���ذ�ť�¼�
        if (mouse_press(884, 712, 1011, 755) == 1) {
            orderfood(page, food_selection); // ����ҳ��
            break;
        }

        // �������ʼ��⿡���ť�¼�
        if (has_selected && mouse_press(800, 600, 1008, 650) == 1) {
            cook_make(page, food_selection);
            break;
        }
    }

    return 0;
}

int cook_make(int *page, Food *food_selection) 
{
    struct tm eventtime;
    Incidentcode incidentcode;
    int i;
    // ����ڴ��е� food_selection ����Ϊδ��ѡ
    for (i = 0; i < 3; i++) { // ���ࣨ3�֣�
        food_selection->soup_selected[i] = 0;
    }
    for (i = 0; i < 4; i++) { // ��ʳ��4�֣�
        food_selection->staple_selected[i] = 0;
    }
    for (i = 0; i < 9; i++) { // ���ȣ�9�֣�
        food_selection->fry_selected[i] = 0;
    }

    // ���޸ĺ�����ݱ��浽�ļ���
    save_food_selection("bmp\\food.dat", food_selection);

    // ��¼��־��ʼ
    incidentcode = cook;
    fstart_diary(&incidentcode, &eventtime);
    
    // ��ʾ����ʳ�����ʾ
    bar1(0, 0, 1024, 768, 0xffffff); // ����
    puthz(360, 350, "����Ϊ������ʳ��", 32, 32, 0x000000);

    // ģ������ʳ����ӳ�
    delay(2000); // ��������ʳ����Ҫ2��

    // ��ʾʳ���������
    puthz(360, 400, "ʳ��������ɣ��뾡��ʳ��", 32, 32, 0x000000);
    delay(2000); // ��ʾ�����ʾ

    // ���ص� check_food ҳ��
    check_food(page, food_selection);

    //��¼��־����
    incidentcode = cook;
    fend_diary(&incidentcode, &eventtime);

    return 0; // �ɹ�����
}

int cook_soup(int *page, Food *food_selection) {
    // ������һ�εĹ�ѡ״̬
    load_food_selection("bmp\\food.dat", food_selection);

    mouse_off(&mouse);
    Readbmp64k(0, 0, "bmp\\tang.bmp");
    prt_hz16_size(429, 714, 2, 2, "�빴ѡ����Ҫ������", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(426, 88, 3, 3, "ź��", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(426, 323, 3, 3, "������������", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(426, 563, 3, 3, "�ϲ���", 0x000000, "HZK\\HZK16s");
    
    // ������һ�ε�״̬���ƹ�ѡ��
    if (food_selection->soup_selected[0] == 1) {
        ThickDiagonalLine(732, 113, 749, 127, 2, 0x000000);
        ThickDiagonalLine(749, 127, 762, 105, 2, 0x000000);
    }
    if (food_selection->soup_selected[1] == 1) {
        ThickDiagonalLine(732, 342, 749, 356, 2, 0x000000);
        ThickDiagonalLine(749, 356, 762, 334, 2, 0x000000);
    }
    if (food_selection->soup_selected[2] == 1) {
        ThickDiagonalLine(732, 588, 749, 602, 2, 0x000000);
        ThickDiagonalLine(749, 602, 760, 580, 2, 0x000000);
    }

    bar2(730, 103, 762, 129, 0x000000);
    bar2(730, 332, 762, 358, 0x000000);
    bar2(730, 578, 762, 604, 0x000000);
    draw_botton(884, 712, 1011, 755, 0xBC8F8F, 0xffffff);
    prt_hz16_size(895, 715, 2, 2, "ȷ��", 0x000000, "HZK\\HZK16s");
    ThickDiagonalLine(977, 21, 1006, 53, 2, 0xE6E6FA);
    ThickDiagonalLine(977, 53, 1006, 21, 2, 0xE6E6FA);

    mouse_on(mouse);
    while (1) {
        int mouse_clicked = 0; // ��¼�Ƿ��Ѵ���������ı�־

        mouse_show(&mouse);
       
        // ���������
        if (mouse_press(730, 103, 762, 129) == 1 && food_selection->soup_selected[0] == 0) { // ��ѡź��
            mouse_off(&mouse);
            ThickDiagonalLine(732, 113, 749, 127, 2, 0x000000);
            ThickDiagonalLine(749, 127, 762, 105, 2, 0x000000);
            food_selection->soup_selected[0] = 1;
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(730, 332, 762, 358) == 1 && food_selection->soup_selected[1] == 0) { // ��ѡ������������
            mouse_off(&mouse);
            ThickDiagonalLine(732, 342, 749, 356, 2, 0x000000);
            ThickDiagonalLine(749, 356, 762, 334, 2, 0x000000);
            food_selection->soup_selected[1] = 1;
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(730, 578, 762, 604) == 1 && food_selection->soup_selected[2] == 0) { // ��ѡ�ϲ���
            mouse_off(&mouse);
            ThickDiagonalLine(732, 588, 749, 602, 2, 0x000000);
            ThickDiagonalLine(749, 602, 760, 580, 2, 0x000000);
            food_selection->soup_selected[2] = 1;
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(730, 103, 762, 129) == 1 && food_selection->soup_selected[0] == 1) { // ȡ����ѡź��
            mouse_off(&mouse);
            bar1(730, 103, 765, 128, 0xffffff);
            bar2(730, 103, 762, 129, 0x000000);
            food_selection->soup_selected[0] = 0; // ��Ϊ 0 �Ա�ʾδ��ѡ
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(730, 332, 762, 358) == 1 && food_selection->soup_selected[1] == 1) { // ȡ����ѡ������������
            mouse_off(&mouse);
            bar1(730, 332, 765, 357, 0xffffff);
            bar2(730, 332, 762, 358, 0x000000);
            food_selection->soup_selected[1] = 0; // ��Ϊ 0 �Ա�ʾδ��ѡ
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(730, 578, 762, 604) == 1 && food_selection->soup_selected[2] == 1) { // ȡ����ѡ�ϲ���
            mouse_off(&mouse);
            bar1(730, 575, 765, 603, 0xffffff);
            bar2(730, 578, 762, 604, 0x000000);
            food_selection->soup_selected[2] = 0; // ��Ϊ 0 �Ա�ʾδ��ѡ
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(884, 712, 1011, 755) == 1 && (food_selection->soup_selected[0] == 1 || food_selection->soup_selected[1] == 1 || food_selection->soup_selected[2] == 1)) { // ���ѡ��
            save_food_selection("bmp\\food.dat", food_selection); // ����״̬
            prt_hz16_size(540, 680, 1, 1, "��Ϊ����ӹ�ѡ��Ʒ���б���", 0x000000, "HZK\\HZK16s");
            delay(1000);
            orderfood(page, food_selection);
            break;
        }
        else if (mouse_press(884, 712, 1011, 755) == 1 && !(food_selection->soup_selected[0] == 1 || food_selection->soup_selected[1] == 1 || food_selection->soup_selected[2] == 1)) { // �������ѡ��
            prt_hz16_size(540, 680, 1, 1, "��δѡ���κβ�Ʒ", 0x000000, "HZK\\HZK16s");
            delay(1000);
            bar1(518, 679, 680, 700, 0xffffff);
        }
        else if (mouse_press(977, 21, 1006, 53) == 1) {
            save_food_selection("bmp\\food.dat", food_selection); // ����״̬
            orderfood(page, food_selection);
            break;
        }

        // ����Ѿ�����������һ�Σ��ȴ���һ�ε��
        if (mouse_clicked) {
            delay(200);
        }
    }

    return 0;
}
int cook_staplefood(int *page, Food *food_selection) {
    // ������һ�εĹ�ѡ״̬
    load_food_selection("bmp\\food.dat", food_selection);

    mouse_off(&mouse);
    Readbmp64k(0, 0, "bmp\\staple.bmp");
    prt_hz16_size(301, 722, 2, 2, "�빴ѡ����Ҫ����ʳ", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(325, 70, 3, 3, "�׷�", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(325, 262, 3, 3, "����", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(325, 440, 3, 3, "�ӱ�", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(325, 640, 3, 3, "��ͷ", 0x000000, "HZK\\HZK16s");
    bar2(478, 81, 512, 112, 0x000000);
    bar2(478, 261, 512, 292, 0x000000);
    bar2(478, 441, 512, 472, 0x000000);
    bar2(478, 651, 512, 682, 0x000000);

    // ������һ�εĹ�ѡ״̬���ƹ�ѡ��
    if (food_selection->staple_selected[0] == 1) { // �׷��ѱ�ѡ��
        ThickDiagonalLine(480, 95, 495, 110, 2, 0x000000);
        ThickDiagonalLine(495, 110, 512, 81, 2, 0x000000);
    }
    if (food_selection->staple_selected[1] == 1) { // �����ѱ�ѡ��
        ThickDiagonalLine(480, 275, 495, 290, 2, 0x000000);
        ThickDiagonalLine(495, 290, 512, 261, 2, 0x000000);
    }
    if (food_selection->staple_selected[2] == 1) { // �ӱ��ѱ�ѡ��
        ThickDiagonalLine(480, 455, 495, 470, 2, 0x000000);
        ThickDiagonalLine(495, 470, 512, 441, 2, 0x000000);
    }
    if (food_selection->staple_selected[3] == 1) { // ��ͷ�ѱ�ѡ��
        ThickDiagonalLine(480, 664, 495, 680, 2, 0x000000);
        ThickDiagonalLine(495, 680, 512, 651, 2, 0x000000);
    }

    draw_botton(884, 712, 1011, 755, 0xBC8F8F, 0xffffff);
    prt_hz16_size(895, 715, 2, 2, "ȷ��", 0x000000, "HZK\\HZK16s");
    ThickDiagonalLine(977, 21, 1006, 53, 2, 0xE6E6FA);
    ThickDiagonalLine(977, 53, 1006, 21, 2, 0xE6E6FA);
    mouse_on(mouse);

    while (1) {
        int mouse_clicked = 0; // ��¼�Ƿ��Ѵ���������ı�־
        mouse_show(&mouse);

        // ���������
        if (mouse_press(478, 81, 512, 112) == 1 && food_selection->staple_selected[0] == 0) { // ��ѡ�׷�
            mouse_off(&mouse);
            ThickDiagonalLine(480, 95, 495, 110, 2, 0x000000);
            ThickDiagonalLine(495, 110, 512, 81, 2, 0x000000);
            food_selection->staple_selected[0] = 1;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 261, 512, 292) == 1 && food_selection->staple_selected[1] == 0) { // ��ѡ����
            mouse_off(&mouse);
            ThickDiagonalLine(480, 275, 495, 290, 2, 0x000000);
            ThickDiagonalLine(495, 290, 512, 261, 2, 0x000000);
            food_selection->staple_selected[1] = 1;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 441, 512, 472) == 1 && food_selection->staple_selected[2] == 0) { // ��ѡ�ӱ�
            mouse_off(&mouse);
            ThickDiagonalLine(480, 455, 495, 470, 2, 0x000000);
            ThickDiagonalLine(495, 470, 512, 441, 2, 0x000000);
            food_selection->staple_selected[2] = 1;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 651, 512, 682) == 1 && food_selection->staple_selected[3] == 0) { // ��ѡ��ͷ
            mouse_off(&mouse);
            ThickDiagonalLine(480, 664, 495, 680, 2, 0x000000);
            ThickDiagonalLine(495, 680, 512, 651, 2, 0x000000);
            food_selection->staple_selected[3] = 1;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 81, 512, 112) == 1 && food_selection->staple_selected[0] == 1) { // ȡ����ѡ�׷�
            mouse_off(&mouse);
            bar1(478, 79, 515, 113, 0xffffff);
            bar2(478, 81, 512, 112, 0x000000);
            food_selection->staple_selected[0] = 0;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 261, 512, 292) == 1 && food_selection->staple_selected[1] == 1) { // ȡ����ѡ����
            mouse_off(&mouse);
            bar1(478, 259, 515, 293, 0xffffff);
            bar2(478, 261, 512, 292, 0x000000);
            food_selection->staple_selected[1] = 0;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 441, 512, 472) == 1 && food_selection->staple_selected[2] == 1) { // ȡ����ѡ�ӱ�
            mouse_off(&mouse);
            bar1(478, 439, 515, 473, 0xffffff);
            bar2(478, 441, 512, 472, 0x000000);
            food_selection->staple_selected[2] = 0;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 651, 512, 682) == 1 && food_selection->staple_selected[3] == 1) { // ȡ����ѡ��ͷ
            mouse_off(&mouse);
            bar1(478, 649, 515, 683, 0xffffff);
            bar2(478, 651, 512, 682, 0x000000);
            food_selection->staple_selected[3] = 0;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(884, 712, 1011, 755) == 1) { // ���ѡ��
            if (food_selection->staple_selected[0] || food_selection->staple_selected[1] || food_selection->staple_selected[2] || food_selection->staple_selected[3]) {
                save_food_selection("bmp\\food.dat", food_selection); // ����״̬
                prt_hz16_size(440, 685, 1, 1, "��Ϊ����ӹ�ѡ��Ʒ���б���", 0x000000, "HZK\\HZK16s");
                delay(1000);
                *page = 14;
                break;
            } else {
                prt_hz16_size(540, 680, 1, 1, "��δѡ���κβ�Ʒ", 0x000000, "HZK\\HZK16s");
                delay(1000);
                bar1(518, 679, 680, 700, 0xffffff);
            }
        } else if (mouse_press(977, 21, 1006, 53) == 1) { // ����
            save_food_selection("bmp\\food.dat", food_selection); // ����״̬
            orderfood(page, food_selection);
            break;
        }

        if (mouse_clicked) delay(200);
    }
    return 0;
}





int cook_fry(int *page, Food *food_selection) {
    // ������һ�εĹ�ѡ״̬
    load_food_selection("bmp\\food.dat", food_selection);

    mouse_off(&mouse);
    Readbmp64k(0, 0, "bmp\\fry.bmp");
    prt_hz16_size(72, 729, 2, 2, "�빴ѡ����Ҫ����ʳ", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(70, 181, 1, 1, "��������˿", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(404, 181, 1, 1, "������˿", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(704, 181, 1, 1, "���ѳ���", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(75, 439, 1, 1, "���Ŷ���", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(404, 439, 1, 1, "��������", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(704, 439, 1, 1, "�峴ʱ��", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(75, 700, 1, 1, "��������", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(404, 700, 1, 1, "����Ϻ", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(704, 700, 1, 1, "������", 0x000000, "HZK\\HZK16s");

    // ����ѡ���ı߿� 
    bar2(152, 175, 177, 199, 0x000000);
    bar2(472, 175, 498, 196, 0x000000);
    bar2(772, 175, 798, 196, 0x000000);
    bar2(149, 436, 177, 457, 0x000000);
    bar2(472, 436, 498, 457, 0x000000);
    bar2(772, 436, 798, 457, 0x000000);
    bar2(149, 698, 177, 719, 0x000000);
    bar2(472, 698, 498, 719, 0x000000);
    bar2(772, 698, 798, 719, 0x000000);

    // ������һ�εĹ�ѡ״̬���ƹ�ѡ��
    if (food_selection->fry_selected[0] == 1) { // ��������˿�ѱ�ѡ��
        ThickDiagonalLine(157, 185, 166, 197, 2, 0x000000);
        ThickDiagonalLine(166, 197, 177, 177, 2, 0x000000);
    }
    if (food_selection->fry_selected[1] == 1) { // ������˿�ѱ�ѡ��
        ThickDiagonalLine(477, 185, 488, 194, 2, 0x000000);
        ThickDiagonalLine(488, 194, 498, 177, 2, 0x000000);
    }
    if (food_selection->fry_selected[2] == 1) { // ���ѳ����ѱ�ѡ��
        ThickDiagonalLine(777, 185, 788, 194, 2, 0x000000);
        ThickDiagonalLine(788, 194, 798, 177, 2, 0x000000);
    }
    if (food_selection->fry_selected[3] == 1) { // ���Ŷ����ѱ�ѡ��
        ThickDiagonalLine(154, 446, 167, 455, 2, 0x000000);
        ThickDiagonalLine(167, 455, 177, 438, 2, 0x000000);
    }
    if (food_selection->fry_selected[4] == 1) { // ���������ѱ�ѡ��
        ThickDiagonalLine(477, 446, 488, 455, 2, 0x000000);
        ThickDiagonalLine(488, 455, 498, 438, 2, 0x000000);
    }
    if (food_selection->fry_selected[5] == 1) { // �峴ʱ���ѱ�ѡ��
        ThickDiagonalLine(777, 446, 788, 455, 2, 0x000000);
        ThickDiagonalLine(788, 455, 798, 438, 2, 0x000000);
    }
    if (food_selection->fry_selected[6] == 1) { // ���������ѱ�ѡ��
        ThickDiagonalLine(154, 708, 167, 717, 2, 0x000000);
        ThickDiagonalLine(167, 717, 177, 700, 2, 0x000000);
    }
    if (food_selection->fry_selected[7] == 1) { // ����Ϻ�ѱ�ѡ��
        ThickDiagonalLine(477, 708, 488, 717, 2, 0x000000);
        ThickDiagonalLine(488, 717, 498, 700, 2, 0x000000);
    }
    if (food_selection->fry_selected[8] == 1) { // �������ѱ�ѡ��
        ThickDiagonalLine(777, 708, 788, 717, 2, 0x000000);
        ThickDiagonalLine(788, 717, 798, 700, 2, 0x000000);
    }

    // ����ȷ�ϰ�ť�ͷ��ذ�ť
    ThickDiagonalLine(977, 21, 1006, 53, 2, 0xE6E6FA);
    ThickDiagonalLine(977, 53, 1006, 21, 2, 0xE6E6FA);
    draw_botton(884, 712, 1011, 755, 0xBC8F8F, 0xffffff);
    prt_hz16_size(895, 715, 2, 2, "ȷ��", 0x000000, "HZK\\HZK16s");
    mouse_on(mouse);

    while (1) {
        int mouse_clicked = 0; // ��¼�Ƿ��Ѵ���������ı�־
        mouse_show(&mouse);

        // �����������򣨵���߼����ֲ��䣬ʡ�Բ����ظ����룩
        if (mouse_press(152, 175, 177, 199) == 1 && food_selection->fry_selected[0] == 0) { 
            mouse_off(&mouse);
            ThickDiagonalLine(157, 185, 166, 197, 2, 0x000000);
            ThickDiagonalLine(166, 197, 177, 177, 2, 0x000000);
            food_selection->fry_selected[0] = 1;
            mouse_clicked = 1;
            mouse_on(mouse);
        }
        else if (mouse_press(472,175,498,196) == 1 &&food_selection->fry_selected[1]  == 0) // ��ѡ������˿
        {
            mouse_off(&mouse);
            ThickDiagonalLine(477,185,488,194, 2, 0x000000);
            ThickDiagonalLine(488,194,498,177, 2, 0x000000);
            food_selection->fry_selected[1] = 1;
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(772,175,798,196) == 1 && food_selection->fry_selected[2]== 0) // ��ѡ���ѳ���
        {
            mouse_off(&mouse);
            ThickDiagonalLine(777,185,788,194, 2, 0x000000);
            ThickDiagonalLine(788,194,798,177, 2, 0x000000);
            food_selection->fry_selected[2] = 1;
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(149,436,177,457) == 1 &&  food_selection->fry_selected[3] == 0) // ��ѡ���Ŷ���
        {
            mouse_off(&mouse);
            ThickDiagonalLine(154,446,167,455, 2, 0x000000);
            ThickDiagonalLine(167,455,177,438, 2, 0x000000);
            food_selection->fry_selected[3] = 1;
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(472,436,498,457) == 1 &&   food_selection->fry_selected[4] == 0) // ��ѡ��������
        {
            mouse_off(&mouse);
            ThickDiagonalLine(477,446,488,455, 2, 0x000000);
            ThickDiagonalLine(488,455,498,438, 2, 0x000000);
            food_selection->fry_selected[4] = 1;
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(772,436,798,457) == 1 &&   food_selection->fry_selected[5] == 0) // ��ѡ�峴ʱ��
        {
            mouse_off(&mouse);
            ThickDiagonalLine(777,446,788,455, 2, 0x000000);
            ThickDiagonalLine(788,455,798,438, 2, 0x000000);
            food_selection->fry_selected[5] = 1;
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(149,698,177,719) == 1 && food_selection->fry_selected[6] == 0) // ��ѡ��������
        {
            mouse_off(&mouse);
            ThickDiagonalLine(154,708,167,717, 2, 0x000000);
            ThickDiagonalLine(167,717,177,700, 2, 0x000000);
            food_selection->fry_selected[6] = 1;
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(472,698,498,719) == 1 && food_selection->fry_selected[7] == 0) // ��ѡ����Ϻ
        {
            mouse_off(&mouse);
            ThickDiagonalLine(477,708,488,717, 2, 0x000000);
            ThickDiagonalLine(488,717,498,700, 2, 0x000000);
            food_selection->fry_selected[7] = 1;
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(772,698,798,719) == 1 && food_selection->fry_selected[8] == 0) // ��ѡ������
        {
            mouse_off(&mouse);
            ThickDiagonalLine(777,708,788,717, 2, 0x000000);
            ThickDiagonalLine(788,717,798,700, 2, 0x000000);
            food_selection->fry_selected[8]  = 1;
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(152,175,177,199) == 1 &&  food_selection->fry_selected[0] == 1) // ȡ����ѡ��������˿
          {
            mouse_off(&mouse);
            bar1(152,175,179,199, 0xffffff);
            bar2(152,175,177,199, 0x000000);
            food_selection->fry_selected[0]= 0; // ��Ϊ 0 �Ա�ʾδ��ѡ
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
          }
        else if (mouse_press(472,175,498,196) == 1 && food_selection->fry_selected[1] == 1) //ȡ����ѡ������˿
        {
            mouse_off(&mouse);
            bar1(472,175,500,196, 0xffffff);
            bar2(472,175,498,196, 0x000000);
            food_selection->fry_selected[1]= 0; // ��Ϊ 0 �Ա�ʾδ��ѡ
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(772,175,798,196) == 1 &&  food_selection->fry_selected[2]== 1) //ȡ����ѡ���ѳ���
        {
            mouse_off(&mouse);
            bar1(772,175,800,196, 0xffffff);
            bar2(772,175,798,196, 0x000000);
            food_selection->fry_selected[2]= 0; // ��Ϊ 0 �Ա�ʾδ��ѡ
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(149,436,177,457) == 1 &&  food_selection->fry_selected[3] == 1) //ȡ����ѡ���Ŷ���
        {
            mouse_off(&mouse);
            bar1(149,436,179,457, 0xffffff);
            bar2(149,436,177,457, 0x000000);
            food_selection->fry_selected[3]= 0; // ��Ϊ 0 �Ա�ʾδ��ѡ
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(472,436,498,457) == 1 && food_selection->fry_selected[4] == 1) //ȡ����ѡ��������
        {
            mouse_off(&mouse);
            bar1(472,436,500,457, 0xffffff);
            bar2(472,436,498,457, 0x000000);
            food_selection->fry_selected[4]= 0; // ��Ϊ 0 �Ա�ʾδ��ѡ
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(772,436,798,457) == 1 &&  food_selection->fry_selected[5] == 1) //ȡ����ѡ�峴ʱ��
        {
            mouse_off(&mouse);
            bar1(772,436,800,457, 0xffffff);
            bar2(772,436,798,457,0x000000);
            food_selection->fry_selected[5]= 0; // ��Ϊ 0 �Ա�ʾδ��ѡ
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(149,698,177,719) == 1 &&  food_selection->fry_selected[6] == 1) //ȡ����ѡ��������
        {
            mouse_off(&mouse);
            bar1(149,698,181,719, 0xffffff);
            bar2(149,698,179,719, 0x000000);
            food_selection->fry_selected[6]= 0; // ��Ϊ 0 �Ա�ʾδ��ѡ
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(472,698,498,719) == 1 &&  food_selection->fry_selected[7] == 1) //ȡ����ѡ����Ϻ
        {
            mouse_off(&mouse);
            bar1(472,698,500,719, 0xffffff);
            bar2(472,698,498,719, 0x000000);
            food_selection->fry_selected[7]= 0; // ��Ϊ 0 �Ա�ʾδ��ѡ
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }
        else if (mouse_press(772,698,798,719) == 1 &&  food_selection->fry_selected[8] == 1) //ȡ����ѡ������
        {
            mouse_off(&mouse);
            bar1(772,698,800,719, 0xffffff);
            bar2(772,698,798,719, 0x000000);
            food_selection->fry_selected[8]= 0; // ��Ϊ 0 �Ա�ʾδ��ѡ
            mouse_clicked = 1; // ����������
            mouse_on(mouse);
        }

        else if(mouse_press(977,21,1006,53)==1)
        {
            save_food_selection("bmp\\food.dat", food_selection); // ����״̬
            orderfood(page,food_selection);
            break;
        }
        else if (mouse_press(884, 712, 1011, 755) == 1) 
        {
            int has_selected = 0;  // �Ƿ��й�ѡ��־
            int i;
            for ( i = 0; i < 9; i++)
            {
                    if (food_selection->fry_selected[i] == 1) {
                        has_selected = 1;
                        break;  // �ҵ���ѡ�����˳�ѭ��
                    }
            }
            if (has_selected) 
            {
                save_food_selection("bmp\\food.dat", food_selection); // ����״̬
                prt_hz16_size(465,740, 1, 1, "��Ϊ����ӹ�ѡ��Ʒ���б���", 0x000000, "HZK\\HZK16s");
                delay(1000);
                *page = 14;
                break;
            } 
            else 
            {
                prt_hz16_size(465, 740, 1, 1, "��δѡ���κβ�Ʒ", 0x000000, "HZK\\HZK16s");
                delay(1000);
                bar1(460,738,650,758,0xffffff);
            }
        }
        if (mouse_clicked) 
        {
             // ͨ������ͣ�٣��������ĵ������
             delay(200); 
        }
    }
}

void  cook_design()
{
    bar1(0,0,1024,768,0xF5FFFA);
    puthz(209,42,"��ӭ��������������Ŷ��", 32, 32,0x000000);
    //������
    Line3(8,164,8,588,2,0x007FFF);
    Line3(8,164,156,164,2,0x007FFF);
    Line3(156,164,156,588,2,0x007FFF);
    Line3(8,588,156,588,2,0x007FFF);
    Line3(76,171,76,350,2,0x007FFF);
    Line3(76,350,8,350,2,0x007FFF);
    Line3(68,245,68,280,2,0x007FFF);
    Line3(95,245,95,280,2,0x007FFF);
    Line3(76,350,8,350,2,0x007FFF);
    Line3(85,171,85,350,2,0x007FFF);
    Line3(85,350,156,350,2,0x007FFF);
    Line3(66,368,66,377,2,0x007FFF);
    Line3(66,377,98,377,2,0x007FFF);
    Line3(98,377,98,368,2,0x007FFF);
    Line3(66,368,98,368,2,0x007FFF);
    Line3(8,459,156,459,2,0x007FFF);

    //������
    Line3(159,365,364,365,2,0x32CD32);
    Line3(364,365,364,589,2,0x32CD32);
    Line3(364,589,159,589,2,0x32CD32);
    Line3(258,365,258,589,2,0x32CD32);
    Line3(159,365,159,589,2,0x32CD32);
    bar1(241,451,250,483,0x9ACD32);
    bar1(269,451,278,483,0x9ACD32);

    //��΢��¯
    Line3(166,287,270,287,2,0x556B2F);
    Line3(270,287,270,358,2,0x556B2F);
    Line3(270,358,166,358,2,0x556B2F);
    Line3(166,358,166,287,2,0x556B2F);
    bar1(177,298,236,347,0x556B2F);
    bar1(250,339,261,346,0x556B2F);
    Circle(257,302,4,0x556B2F);
    Circle(257,323,4,0x556B2F);
    Circle(257,302,3,0x556B2F);
    Circle(257,323,3,0x556B2F);

    //����̨
    Line3(369,357,720,357,2,0x0D33FF);
    Line3(720,357,720,586,2,0x0D33FF);
    Line3(720,586,369,586,2,0x0D33FF);
    Line3(369,586,369,357,2,0x0D33FF);
    Line3(369,467,525,467,2,0x556B2F);
    bar2(425,369,463,382,0x556B2F);
    bar2(425,485,463,496,0x556B2F);
    Line3(525,357,525,586,2,0x556B2F);
    Line3(531,412,711,414,2,0x556B2F);
    Line3(711,414,711,568,2,0x556B2F);
    Line3(711,568,531,568,2,0x556B2F);
    Line3(531,568,531,412,2,0x556B2F);
    bar2(589,372,654,394,0x556B2F);
    bar2(666,379,676,387,0x556B2F);
    bar2(685,379,697,387,0x556B2F);
    bar2(660,375,680,394,0x556B2F);
    bar2(682,375,702,394,0x556B2F);
    Line2(533,356,541,341,0x6A5ACD);
    Line2(541,341,705,341,0x6A5ACD);
    Line2(705,341,713,356,0x6A5ACD);
    Line2(705,356,533,356,0x6A5ACD);
    Line1(554,301,554,336,0x6A5ACD);
    Line1(554,336,618,336,0x6A5ACD);
    Line1(618,301,618,336,0x6A5ACD);
    bar2(546,280,626,300,0x6A5ACD);
    Line2(553,280,562,266,0x6A5ACD);

    //����
    Line1(562,266,612,367,0x6A5ACD);
    Line2(612,267,621,281,0x6A5ACD);
    Circle(589,261,4,0x556B2F);
    Line2(564,341,574,336,0x6A5ACD);
    Line2(599,336,609,341,0x6A5ACD);

    //��ƽ�׹�
    Line1(633,318,704,318,0x6A5ACD);
    Line2(633,318,639,337,0x6A5ACD);
    Line1(639,337,698,337,0x6A5ACD);
    Line2(698,337,704,318,0x6A5ACD);
    Line2(654,337,647,342,0x6A5ACD);
    Line2(683,337,686,342,0x6A5ACD);
    Line1(701,330,715,330,0x6A5ACD);
    bar2(715,325,748,335,0x6A5ACD);

    //�����̻�
    Line1(631,0,631,68,0x6A5ACD);
    Line1(689,0,689,68,0x6A5ACD);
    Line1(631,68,689,68,0x6A5ACD);
    Line2(631,68,558,142,0x6A5ACD);
    Line2(689,68,762,142,0x6A5ACD);
    Line1(558,142,558,162,0x6A5ACD);
    Line1(762,142,762,162,0x6A5ACD);
    Line1(558,162,762,162,0x6A5ACD);
    Line2(638,68,577,143,0x6A5ACD);
    Line1(577,143,737,143,0x6A5ACD);
    Line2(680,68,737,143,0x6A5ACD);

    //������
    bar2(408,232,532,249,0x6A5ACD);
    Circle(434,240,4,0x6A5ACD);
    Circle(471,240,4,0x6A5ACD);
    Circle(506,240,4,0x6A5ACD);
    Line1(434,240,434,261,0x6A5ACD);
    Line1(471,240,470,261,0x6A5ACD);
    Line1(506,240,506,261,0x6A5ACD);
    //������1
    bar2(427,261,441,305,0x6A5ACD);
    Circle(434,325,20,0x6A5ACD);
    //������2
    bar2(465,261,477,312,0x6A5ACD);
    Line2(465,312,459,322,0x6A5ACD);
    Line2(477,312,483,322,0x6A5ACD);
    Line1(459,322,459,343,0x6A5ACD);
    Line1(483,322,483,343,0x6A5ACD);
    Line1(459,343,483,343,0x6A5ACD);    
    //�������
    bar2(500,260,512,309,0x6A5ACD);
    DrawEllipse(506,329,15,20,0x6A5ACD);
    Line1(498,315,498,344,0x6A5ACD);
    Line1(514,315,514,344,0x6A5ACD);
    Line1(506,309,506,349,0x6A5ACD);
  
    //������
    FillEllipse(866,563,132,47,0x66FF59);
    FillEllipse(866,714,50,23,0x66FF59);
    Line3(834,611,834,699,3,0x66FF59);
    Line3(899,611,899,699,3,0x66FF59);
    draw_botton(925,727,1013,756,0x4D1F00,0xffffff);
    prt_hz16_size(945,735,1,1,"����",0x000000,"HZK\\HZK16s");
    draw_botton(42,25,175,66,0xCD5C5C,0xffffff);
    prt_hz16_size(70,30,2,2,"���",0x000000,"HZK\\HZK16s");
    }


