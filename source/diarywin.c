/*
每次点击按钮打开diarywin函数，都视为重新运行一遍diarywin，
每次都把当前完整的diary.dat数据完整画出，因此选择不封闭file
*/

#include <allfunc.h>
void set_dwin();
int read_dwindata(Todaydata *todaydata, struct tm *times, Incidentcode *codes);
char* incidentToString(Incidentcode code);
char* weekdayToString(Weekday weekday);
char* weatherToString(Weather weather);
void draw_dwin(Todaydata todaydata, Incidentcode *codes, struct tm *times, int n, int remainder);
void diarywin(int* page);


// 绘制日志矩形的函数
void set_dwin() 
{
    char diarybg[8] = "diarybg";

    // 绘制矩形背景
    bar1(0, 0, 1024, 768, 0xD3D3D3);    //大背景
    bar1(250, 0, 750, 768, 0xDB7093);  // 矩形背景

    // 绘制矩形边框
    Line1(250, 0, 750, 0, 0xFFFFFF);  // 上边框
    Line1(750, 0, 750, 768, 0xFFFFFF);  // 右边框
    Line1(250, 768, 750, 768, 0xFFFFFF);  // 下边框
    Line1(250, 0, 250, 768, 0xFFFFFF);  // 左边框

    //绘制矩形关闭按钮
    bar1(720, 0, 750, 30, 0xFF9900);
    bar1(723, 3, 747, 27, 0xFAF0E6);
    Line2(725, 5, 745, 25, 0xFFFFFF);
    Line2(745, 5, 725, 25, 0xFFFFFF);

    //绘制翻页按钮
    bar1(770, 700, 885, 740, 0xFFFAFA);//上一页
    bar1(775, 705, 880, 735, 0xFFDAB9);
    prt_hz16_size(776, 705, 2, 2, "上一页", 0xFF66CC, "HZK\\HZK16s");

    bar1(895, 700, 1010, 740, 0xFFFAFA);//下一页
    bar1(900, 705, 1005, 735, 0xFFDAB9);
    prt_hz16_size(901, 705, 2, 2, "下一页", 0xFF66CC, "HZK\\HZK16s");


    //存好日志区域的背景为diarbg
    Save_image(250, 0, 750, 762, diarybg);
}


//读取diary.dat数据,返回目前一共有多少事件
int read_dwindata(Todaydata *todaydata, struct tm *times, Incidentcode *codes)
{
    int count = 0;
    size_t result = 0;
    FILE *file = fopen("Data\\diary.dat", "rb");

    //1. 阅读todaydata数据
    if (file == NULL) {
        perror("无法打开文件");
        exit(1);
    }

    // 从文件中读取结构体数据
    result = fread(todaydata, sizeof(Todaydata), 1, file);
    if (result != 1) {
        perror("读取文件内容时出错");
        fclose(file);
        exit(1);
    }


    //2. 循环阅读所有事件数据：<struct tm>,<Incidentcode>

    while (1)
    {
        struct tm tm1, tm2;
        Incidentcode code1, code2;

        // 读取一组数据
        if (fread(&tm1, sizeof(struct tm), 1, file) != 1 ||
            fread(&code1, sizeof(int), 1, file) != 1 ||
            fread(&code2, sizeof(int), 1, file) != 1 ||
            fread(&tm2, sizeof(struct tm), 1, file) != 1) {
            break; // 读取失败或到达文件末尾
        }

        // 存储数据
        times[count] = tm1;
        codes[count] = code1;

        count++;
    }
    fclose(file);
    
    return count;
}


//画出一条todaydata+10条日志

// 将Incidentcode转换为对应的中文描述
char* incidentToString(Incidentcode code) {
    switch (code) {
        case light_on: return "已完成开灯";
        case light_off: return "已完成关灯";
        case window_on: return "已完成开窗";
        case window_off: return "已完成关窗";
        case door_off: return "已完成关门";
        case cook: return "已完成做饭";
        case cleanup: return "已完成卫生打扫";
        case boilwater: return "已完成烧水倒水";
        case plants: return "已完成浇花";
        case battery: return "正在充电。已完成充电！";
        // 以下为emergency事件
        case firealarm: return "突发着火，已报警并采取对应措施";
        case electricity: return "突发电源跳闸，已排查并处理";
        case grandfather: return "老爷爷感到身体不适，已检查并采取对应措施";
        case grandmother: return "老奶奶感到身体不适，已检查并采取对应措施";
        case windowstrange: return "窗户异常开，已检查并处理";
        case doorstrange: return "门异常开，已检查并处理";
        case floorwet: return "检测到地面潮湿易滑倒，已干燥处理";
        case falldown: return "有成员跌倒，已检查并采取对应措施";
        case gasleak: return "煤气泄漏，已检查并采取对应措施";

        default: return "";
    }
}

// 将Weekday转换为对应的中文描述
char* weekdayToString(Weekday weekday) {
    switch (weekday) {
        case Monday: return "星期一";
        case Tuesday: return "星期二";
        case Wednesday: return "星期三";
        case Thursday: return "星期四";
        case Friday: return "星期五";
        case Saturday: return "星期六";
        case Sunday: return "星期日";
        default: return "";
    }
}

// 将Weather转换为对应的中文描述
char* weatherToString(Weather weather) {
    switch (weather) {
        case Sunny: return "晴天";
        case Cloudy: return "多云";
        case Rainy: return "雨天";
        case Snowy: return "雪天";
        default: return "";
    }
}

// 绘制函数
void draw_dwin(Todaydata todaydata, Incidentcode *codes, struct tm *times, int n, int remainder) {
    char info1[20];
    char info2[20];
    char lastbmpname[8] = {0};
    char diarybg[8] = "diarybg";
    int i = 0;
    int j = 0;
    int x = 305;
    int y = 20;
    int flag = 16; // 假设使用16x16的字体
    int part = 16;
    int color = 0xFFFFE0; // 假设使用黄色

    // 初始化绘制日志矩形
    set_dwin();

    //在旁边写出loading
    put_asc16_size(770, 600, 2, 2, "LOADING...", 0xFFFFE0);



    /*绘制整页*/

    for (j=0;j<n;j++)
    {
        char bmpname[8] = {0};

        // 绘制todaydata标题信息
        x = 295;
        y = 30;
        puthz(x, y, "今日日期：", flag, part, color);
        x += 16*5;
        sprintf(info1, "%d-%d-%d ", todaydata.year, todaydata.month, todaydata.day);
        prt_asc16(x, y, info1, 0xFFFFE0);
        x += 16*7;
        puthz(x, y, weekdayToString(todaydata.weekday), flag, part, color);
        x += 16*3;

        y += flag + 10;
        x = 295;

        puthz(x, y, "天气：", flag, part, color);
        x += 16*3;
        puthz(x, y, weatherToString(todaydata.weather), flag, part, color);
        x += 16*2;
        puthz(x, y, "，气温：", flag, part, color);
        x += 16*4;
        sprintf(info2, "%d ", todaydata.temperature);
        prt_asc16(x, y, info2, 0xFFFFE0);
        x += 16*2;
        puthz(x, y, "摄氏度", flag, part, color);
        x = 305;

        y += flag + 50;

        // 绘制10条事件信息
        for (i = 0; i < 10; i++) 
        {
            char eventInfo[50];
        
            /*sprintf(eventInfo, "%04d-%02d-%02d %02d:%02d:%02d, 发生了:%s", 
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

        //保存第j页为diarypj
        sprintf(bmpname,"diaryp%d",j);
        Save_image(250, 0, 750, 762, bmpname);
        

        //清空页面，重新绘制
        Load_image(250, 0, 750, 762, diarybg);

    }




    /*绘制最后一页*/

    // 绘制todaydata标题信息
    x = 295;
    y = 30;
    puthz(x, y, "今日日期：", flag, part, color);
    x += 16*5;
    sprintf(info1, "%d-%d-%d ", todaydata.year, todaydata.month, todaydata.day);
    prt_asc16(x, y, info1, 0xFFFFE0);
    x += 16*7;
    puthz(x, y, weekdayToString(todaydata.weekday), flag, part, color);
    x += 16*3;

    y += flag + 10;
    x = 295;

    puthz(x, y, "天气：", flag, part, color);
    x += 16*3;
    puthz(x, y, weatherToString(todaydata.weather), flag, part, color);
    x += 16*2;
    puthz(x, y, "，气温：", flag, part, color);
    x += 16*4;
    sprintf(info2, "%d ", todaydata.temperature);
    prt_asc16(x, y, info2, 0xFFFFE0);
    x += 16*2;
    puthz(x, y, "摄氏度", flag, part, color);
    x = 305;

    y += flag + 50;

    // 绘制remainder条事件信息
    for (i = 0; i < remainder; i++) 
    {
        char eventInfo[50];
    
        /*sprintf(eventInfo, "%04d-%02d-%02d %02d:%02d:%02d, 发生了:%s", 
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

    //保存第n页为diarypn
    sprintf(lastbmpname,"diaryp%d",n);
    Save_image(250, 0, 750, 762, lastbmpname);

    //清空页面，重新加载
    set_dwin();


}



//总函数diarywin，注意上限是100件事，不然会出bug
void diarywin(int* page)
{
    int p = 0;//页面数
    char bmpname[8] = {0};

    Todaydata todaydata;
    struct tm times[100];
    Incidentcode codes[200];

    int count = 0;
    int n = 0;//整页数
    int remainder = 0;//事件余数


    //读取diary.dat数据
    count = read_dwindata(&todaydata, times, codes);

    //处理页面数
    n = count / 10;
    remainder = count % 10;

    // 绘制日志各页
    draw_dwin(todaydata, codes, times, n, remainder);

    

    /*页面更换与退出：鼠标操作*/

    //开始的时候，展示第一页
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
        else if(mouse_press(770, 700, 885, 740)==1 && p != 0 )//上一页,而且有上一页可翻
        {
            p--;
            sprintf(bmpname,"diaryp%d",p);
            Load_image(250, 0, 750, 762, bmpname);
        }
        else if(mouse_press(895, 700, 1010, 740)==1 && p != n )//下一页,而且有下一页可翻
        {
            p++;
            sprintf(bmpname,"diaryp%d",p);
            Load_image(250, 0, 750, 762, bmpname);
        }

    }
}
