/*
ÿ�ε����ť��diarywin����������Ϊ��������һ��diarywin��
ÿ�ζ��ѵ�ǰ������diary.dat�����������������ѡ�񲻷��file
*/

#include <allfunc.h>
void set_dwin();
int read_dwindata(Todaydata *todaydata, struct tm *times, Incidentcode *codes);
char* incidentToString(Incidentcode code);
char* weekdayToString(Weekday weekday);
char* weatherToString(Weather weather);
void draw_dwin(Todaydata todaydata, Incidentcode *codes, struct tm *times, int n, int remainder);
void diarywin(int* page);


// ������־���εĺ���
void set_dwin() 
{
    char diarybg[8] = "diarybg";

    // ���ƾ��α���
    bar1(0, 0, 1024, 768, 0xD3D3D3);    //�󱳾�
    bar1(250, 0, 750, 768, 0xDB7093);  // ���α���

    // ���ƾ��α߿�
    Line1(250, 0, 750, 0, 0xFFFFFF);  // �ϱ߿�
    Line1(750, 0, 750, 768, 0xFFFFFF);  // �ұ߿�
    Line1(250, 768, 750, 768, 0xFFFFFF);  // �±߿�
    Line1(250, 0, 250, 768, 0xFFFFFF);  // ��߿�

    //���ƾ��ιرհ�ť
    bar1(720, 0, 750, 30, 0xFF9900);
    bar1(723, 3, 747, 27, 0xFAF0E6);
    Line2(725, 5, 745, 25, 0xFFFFFF);
    Line2(745, 5, 725, 25, 0xFFFFFF);

    //���Ʒ�ҳ��ť
    bar1(770, 700, 885, 740, 0xFFFAFA);//��һҳ
    bar1(775, 705, 880, 735, 0xFFDAB9);
    prt_hz16_size(776, 705, 2, 2, "��һҳ", 0xFF66CC, "HZK\\HZK16s");

    bar1(895, 700, 1010, 740, 0xFFFAFA);//��һҳ
    bar1(900, 705, 1005, 735, 0xFFDAB9);
    prt_hz16_size(901, 705, 2, 2, "��һҳ", 0xFF66CC, "HZK\\HZK16s");


    //�����־����ı���Ϊdiarbg
    Save_image(250, 0, 750, 762, diarybg);
}


//��ȡdiary.dat����,����Ŀǰһ���ж����¼�
int read_dwindata(Todaydata *todaydata, struct tm *times, Incidentcode *codes)
{
    int count = 0;
    size_t result = 0;
    FILE *file = fopen("Data\\diary.dat", "rb");

    //1. �Ķ�todaydata����
    if (file == NULL) {
        perror("�޷����ļ�");
        exit(1);
    }

    // ���ļ��ж�ȡ�ṹ������
    result = fread(todaydata, sizeof(Todaydata), 1, file);
    if (result != 1) {
        perror("��ȡ�ļ�����ʱ����");
        fclose(file);
        exit(1);
    }


    //2. ѭ���Ķ������¼����ݣ�<struct tm>,<Incidentcode>

    while (1)
    {
        struct tm tm1, tm2;
        Incidentcode code1, code2;

        // ��ȡһ������
        if (fread(&tm1, sizeof(struct tm), 1, file) != 1 ||
            fread(&code1, sizeof(int), 1, file) != 1 ||
            fread(&code2, sizeof(int), 1, file) != 1 ||
            fread(&tm2, sizeof(struct tm), 1, file) != 1) {
            break; // ��ȡʧ�ܻ򵽴��ļ�ĩβ
        }

        // �洢����
        times[count] = tm1;
        codes[count] = code1;

        count++;
    }
    fclose(file);
    
    return count;
}


//����һ��todaydata+10����־

// ��Incidentcodeת��Ϊ��Ӧ����������
char* incidentToString(Incidentcode code) {
    switch (code) {
        case light_on: return "����ɿ���";
        case light_off: return "����ɹص�";
        case window_on: return "����ɿ���";
        case window_off: return "����ɹش�";
        case door_off: return "����ɹ���";
        case cook: return "���������";
        case cleanup: return "�����������ɨ";
        case boilwater: return "�������ˮ��ˮ";
        case plants: return "����ɽ���";
        case battery: return "���ڳ�硣����ɳ�磡";
        // ����Ϊemergency�¼�
        case firealarm: return "ͻ���Ż��ѱ�������ȡ��Ӧ��ʩ";
        case electricity: return "ͻ����Դ��բ�����Ų鲢����";
        case grandfather: return "��үү�е����岻�ʣ��Ѽ�鲢��ȡ��Ӧ��ʩ";
        case grandmother: return "�����̸е����岻�ʣ��Ѽ�鲢��ȡ��Ӧ��ʩ";
        case windowstrange: return "�����쳣�����Ѽ�鲢����";
        case doorstrange: return "���쳣�����Ѽ�鲢����";
        case floorwet: return "��⵽���泱ʪ�׻������Ѹ��ﴦ��";
        case falldown: return "�г�Ա�������Ѽ�鲢��ȡ��Ӧ��ʩ";
        case gasleak: return "ú��й©���Ѽ�鲢��ȡ��Ӧ��ʩ";

        default: return "";
    }
}

// ��Weekdayת��Ϊ��Ӧ����������
char* weekdayToString(Weekday weekday) {
    switch (weekday) {
        case Monday: return "����һ";
        case Tuesday: return "���ڶ�";
        case Wednesday: return "������";
        case Thursday: return "������";
        case Friday: return "������";
        case Saturday: return "������";
        case Sunday: return "������";
        default: return "";
    }
}

// ��Weatherת��Ϊ��Ӧ����������
char* weatherToString(Weather weather) {
    switch (weather) {
        case Sunny: return "����";
        case Cloudy: return "����";
        case Rainy: return "����";
        case Snowy: return "ѩ��";
        default: return "";
    }
}

// ���ƺ���
void draw_dwin(Todaydata todaydata, Incidentcode *codes, struct tm *times, int n, int remainder) {
    char info1[20];
    char info2[20];
    char lastbmpname[8] = {0};
    char diarybg[8] = "diarybg";
    int i = 0;
    int j = 0;
    int x = 305;
    int y = 20;
    int flag = 16; // ����ʹ��16x16������
    int part = 16;
    int color = 0xFFFFE0; // ����ʹ�û�ɫ

    // ��ʼ��������־����
    set_dwin();

    //���Ա�д��loading
    put_asc16_size(770, 600, 2, 2, "LOADING...", 0xFFFFE0);



    /*������ҳ*/

    for (j=0;j<n;j++)
    {
        char bmpname[8] = {0};

        // ����todaydata������Ϣ
        x = 295;
        y = 30;
        puthz(x, y, "�������ڣ�", flag, part, color);
        x += 16*5;
        sprintf(info1, "%d-%d-%d ", todaydata.year, todaydata.month, todaydata.day);
        prt_asc16(x, y, info1, 0xFFFFE0);
        x += 16*7;
        puthz(x, y, weekdayToString(todaydata.weekday), flag, part, color);
        x += 16*3;

        y += flag + 10;
        x = 295;

        puthz(x, y, "������", flag, part, color);
        x += 16*3;
        puthz(x, y, weatherToString(todaydata.weather), flag, part, color);
        x += 16*2;
        puthz(x, y, "�����£�", flag, part, color);
        x += 16*4;
        sprintf(info2, "%d ", todaydata.temperature);
        prt_asc16(x, y, info2, 0xFFFFE0);
        x += 16*2;
        puthz(x, y, "���϶�", flag, part, color);
        x = 305;

        y += flag + 50;

        // ����10���¼���Ϣ
        for (i = 0; i < 10; i++) 
        {
            char eventInfo[50];
        
            /*sprintf(eventInfo, "%04d-%02d-%02d %02d:%02d:%02d, ������:%s", 
                times[i].tm_year + 1900, times[i].tm_mon + 1, times[i].tm_mday, 
                times[i].tm_hour, times[i].tm_min, times[i].tm_sec, 
                incidentToString(codes[i]));
            prt_hz16_size(x, y, 1, 1, eventInfo, color, "HZK\\HZK16s");*/

            sprintf(eventInfo, "%04d-%02d-%02d %02d:%02d:%02d", 
                times[10*j+i].tm_year + 1900, times[10*j+i].tm_mon + 1, times[10*j+i].tm_mday, 
                times[10*j+i].tm_hour, times[10*j+i].tm_min, times[10*j+i].tm_sec);
            prt_asc16(x, y, eventInfo, 0xFFFFFF);
            y += flag + 10;
            puthz(x, y, incidentToString(codes[10*j+i]), flag, part, color);

            x = 305;
            y += flag + 20;
        }

        //�����jҳΪdiarypj
        sprintf(bmpname,"diaryp%d",j);
        Save_image(250, 0, 750, 762, bmpname);
        

        //���ҳ�棬���»���
        Load_image(250, 0, 750, 762, diarybg);

    }




    /*�������һҳ*/

    // ����todaydata������Ϣ
    x = 295;
    y = 30;
    puthz(x, y, "�������ڣ�", flag, part, color);
    x += 16*5;
    sprintf(info1, "%d-%d-%d ", todaydata.year, todaydata.month, todaydata.day);
    prt_asc16(x, y, info1, 0xFFFFE0);
    x += 16*7;
    puthz(x, y, weekdayToString(todaydata.weekday), flag, part, color);
    x += 16*3;

    y += flag + 10;
    x = 295;

    puthz(x, y, "������", flag, part, color);
    x += 16*3;
    puthz(x, y, weatherToString(todaydata.weather), flag, part, color);
    x += 16*2;
    puthz(x, y, "�����£�", flag, part, color);
    x += 16*4;
    sprintf(info2, "%d ", todaydata.temperature);
    prt_asc16(x, y, info2, 0xFFFFE0);
    x += 16*2;
    puthz(x, y, "���϶�", flag, part, color);
    x = 305;

    y += flag + 50;

    // ����remainder���¼���Ϣ
    for (i = 0; i < remainder; i++) 
    {
        char eventInfo[50];
    
        /*sprintf(eventInfo, "%04d-%02d-%02d %02d:%02d:%02d, ������:%s", 
            times[i].tm_year + 1900, times[i].tm_mon + 1, times[i].tm_mday, 
            times[i].tm_hour, times[i].tm_min, times[i].tm_sec, 
            incidentToString(codes[i]));
        prt_hz16_size(x, y, 1, 1, eventInfo, color, "HZK\\HZK16s");*/

        sprintf(eventInfo, "%04d-%02d-%02d %02d:%02d:%02d", 
            times[10*n+i].tm_year + 1900, times[10*n+i].tm_mon + 1, times[10*n+i].tm_mday, 
            times[10*n+i].tm_hour, times[10*n+i].tm_min, times[10*n+i].tm_sec);
        prt_asc16(x, y, eventInfo, 0xFFFFFF);
        y += flag + 10;
        puthz(x, y, incidentToString(codes[10*n+i]), flag, part, color);

        x = 305;
        y += flag + 20;
    }

    //�����nҳΪdiarypn
    sprintf(lastbmpname,"diaryp%d",n);
    Save_image(250, 0, 750, 762, lastbmpname);

    //���ҳ�棬���¼���
    set_dwin();


}



//�ܺ���diarywin��ע��������100���£���Ȼ���bug
void diarywin(int* page)
{
    int p = 0;//ҳ����
    char bmpname[8] = {0};

    Todaydata todaydata;
    struct tm times[100];
    Incidentcode codes[200];

    int count = 0;
    int n = 0;//��ҳ��
    int remainder = 0;//�¼�����


    //��ȡdiary.dat����
    count = read_dwindata(&todaydata, times, codes);

    //����ҳ����
    n = count / 10;
    remainder = count % 10;

    // ������־��ҳ
    draw_dwin(todaydata, codes, times, n, remainder);

    

    /*ҳ��������˳���������*/

    //��ʼ��ʱ��չʾ��һҳ
    sprintf(bmpname,"diaryp0");
    Load_image(250, 0, 750, 762, bmpname);

    mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);

        if(mouse_press(720, 0, 750, 30)==1)
        {
            mouse_off(&mouse);
            *page = 4;
            break;
        }
        else if(mouse_press(770, 700, 885, 740)==1 && p != 0 )//��һҳ,��������һҳ�ɷ�
        {
            p--;
            sprintf(bmpname,"diaryp%d",p);
            Load_image(250, 0, 750, 762, bmpname);
        }
        else if(mouse_press(895, 700, 1010, 740)==1 && p != n )//��һҳ,��������һҳ�ɷ�
        {
            p++;
            sprintf(bmpname,"diaryp%d",p);
            Load_image(250, 0, 750, 762, bmpname);
        }

    }
}
