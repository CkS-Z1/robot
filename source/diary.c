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
 * @description: 初始化日志：
 *               创建日志数据文件diary.dat、日志文件diary.txt；
 *               输入本日初始信息：日期、天气、温度；
 *               把相应信息打印进txt，存struct Todaydata进dat
 * @file:日志数据C:\\cks\\Data\\diary.dat；
 *       日志文档C:\\cks\\Data\\diary.txt；
*/
void finitialize_diary() {

    char *weekday_str[] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};
    char *weather_str[] = {"晴天", "多云", "雨天", "雪天"};

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


    // 初始化随机数种子
    srand(time(NULL));

    // 获取当前时间
    current_time = time(NULL);
    local_time = localtime(&current_time);

    // 提取年、月、日、星期几
    year = local_time->tm_year + 1900;
    month = local_time->tm_mon + 1;
    day = local_time->tm_mday;
    weekday = (Weekday)local_time->tm_wday;

    // 随机生成天气
    weather = (Weather)(rand() % 4);
    // 生成 10 到 30 之间的随机温度，雪天温度为 0 到 5
    if(weather == Snowy)
    {
        temperature = rand() % 6;
    }
    else
    {
        temperature = rand() % 21 + 10; 
    }

    // 创建结构体变量存储信息
    entry.year = year;
    entry.month = month;
    entry.day = day;
    entry.weekday = weekday;
    entry.weather = weather;
    entry.temperature = temperature;

    // 打开 diary.txt 文件以写入信息
    txt_file = fopen("Data\\diary.txt", "a+");
    if (txt_file == NULL) {
        perror("无法打开 diary.txt 文件");
        return;
    }

    // 将信息写入 diary.txt 文件
    fprintf(txt_file, "%d/", year);
    fprintf(txt_file, "%d/", month);
    fprintf(txt_file, "%d  ", day);
    fprintf(txt_file, "%s  ", weekday_str[weekday]);
    fprintf(txt_file, "%s  ", weather_str[weather]);
    fprintf(txt_file, "%d度\n\n", temperature);

    // 关闭 diary.txt 文件
    fclose(txt_file);

    // 打开 diary.dat 文件以二进制写入信息
    dat_file = fopen("Data\\diary.dat", "wb+");
    if (dat_file == NULL) {
        perror("无法打开 diary.dat 文件");
        return;
    }

    // 将结构体变量写入 diary.dat 文件
    fwrite(&entry, sizeof(Todaydata), 1, dat_file);

    // 关闭 diary.dat 文件
    fclose(dat_file);
}






/**
 * @name:fstart_diary
 * @description: 在事件发生时外部调用，要求传入Incidentcode *incidentcode, struct tm *starttime；
 *               根据输入的事件类型，记录事件的开始：
 *               把"时间"、"什么事件正在发生"、"正在处理"写入diary.dat、diary.txt；
 *               通过指针返回struct tm *starttime也就是开始时间值
 *       ##假想：return一个int值，让外部count++用作记录发生多少事件，以供日志窗口读取diary.dat的第几个事件？##
 * @file:日志数据C:\\cks\\Data\\diary.dat；
 *       日志文档C:\\cks\\Data\\diary.txt；
 *       时间暂存数据库C:\\cks\\Data\\timedata.dat
*/
void fstart_diary(Incidentcode *incidentcode, struct tm *starttime)
{

    FILE *fp_timedata, *txt_file, *dat_file;
    char tc = 0;
    // 定义事件代码对应的中文描述数组
    char *incident_descriptions[] = {
        "",        // 占位，因为枚举从 1 开始
        "正在开灯...",
        "正在关灯...",
        "正在开窗...",
        "正在关窗...",
        "正在关门...",
        "正在做饭...",
        "正在打扫...",
        "正在烧水倒水...",
        "正在浇花...",
        "正在充电...",
        //emergency
        "发生火灾，正在处理并报警...",
        "正在处理电源故障...",
        "正在处理老爷爷身体不适...",
        "正在处理老奶奶身体不适...",
        "正在处理窗户异常开...",
        "正在处理门异常开..."
        "正在处理地面潮湿..."
        "正在处理成员跌倒..."
        "正在处理煤气泄漏..."
    };



    //record start time
    fget_time();
    fsave_time();
    //return start time
    fp_timedata = fopen("Data\\timedata.dat", "rb");
    if (fp_timedata == NULL) {
        perror("无法打开 timedata.dat 文件进行读取");
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }

    if (fread(starttime, sizeof(struct tm), 1, fp_timedata) != 1) {
        perror("读取 timedata.dat 文件时出错");
        fclose(fp_timedata);
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }
    fclose(fp_timedata);




    //record incident start

    // 打开 diary.dat 文件以二进制追加模式写入信息
    dat_file = fopen("Data\\diary.dat", "ab");
    if (dat_file == NULL) {
        perror("无法打开 diary.dat 文件");
        return;
    }

    // 将事件代码写入 diary.dat 文件
    fwrite(incidentcode, sizeof(Incidentcode), 1, dat_file);
    fclose(dat_file);

    // 打开 diary.txt 文件以追加模式写入信息
    txt_file = fopen("Data\\diary.txt", "a");
    if (txt_file == NULL) {
        perror("无法打开 diary.txt 文件");
        return;
    }

    // 根据事件代码获取对应的中文描述并写入 diary.txt 文件
    if (*incidentcode >= 1 && *incidentcode < sizeof(incident_descriptions) / sizeof(incident_descriptions[0])) {
        fprintf(txt_file, "%s\n", incident_descriptions[*incidentcode]);
    }

    fclose(txt_file);


}








/**
 * @name:fend_diary
 * @description: 在事件结束时外部调用，要求传入Incidentcode *incidentcode, struct tm *endtime；
 *               根据输入的事件类型，记录事件的结束：
 *               把"什么事件处理完毕"、"时间"写入diary.dat、diary.txt；
 *               通过指针返回struct tm *endtime也就是结束时间值
 * @file:日志数据C:\\cks\\Data\\diary.dat；
 *       日志文档C:\\cks\\Data\\diary.txt；
 *       时间暂存数据库C:\\cks\\Data\\timedata.dat
*/
void fend_diary(Incidentcode *incidentcode, struct tm *endtime)
{

    FILE *fp_timedata, *txt_file, *dat_file;
    char tc = 0;
    // 定义事件代码对应的中文描述数组
    const char *incident_descriptions[] = {
        "",        // 占位，因为枚举从 1 开始
        "已完成开灯",
        "已完成关灯",
        "已完成开窗",
        "已完成关窗",
        "已完成关门",
        "已完成做饭",
        "已完成打扫",
        "已完成烧水倒水",
        "已完成浇花",
        "已完成充电",
        //emergency
        "已完成火灾处理",
        "已完成电源故障处理",
        "已完成老爷爷身体不适处理",
        "已完成老奶奶身体不适处理",
        "已完成窗户开关异常处理",
        "已完成门开关异常处理",
        "地面潮湿，已完成处理",
        "成员跌倒，已完成处理",
        "煤气泄漏，已完成处理"
    };



    //get end time
    fget_time();
    //return end time
    fp_timedata = fopen("Data\\timedata.dat", "rb");
    if (fp_timedata == NULL) {
        perror("无法打开 timedata.dat 文件进行读取");
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }

    if (fread(endtime, sizeof(struct tm), 1, fp_timedata) != 1) {
        perror("读取 timedata.dat 文件时出错");
        fclose(fp_timedata);
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }
    fclose(fp_timedata);




    //record incident end

    // 打开 diary.dat 文件以二进制追加模式写入信息
    dat_file = fopen("Data\\diary.dat", "ab");
    if (dat_file == NULL) {
        perror("无法打开 diary.dat 文件");
        return;
    }

    // 将事件代码写入 diary.dat 文件
    fwrite(incidentcode, sizeof(Incidentcode), 1, dat_file);
    fclose(dat_file);

    // 打开 diary.txt 文件以追加模式写入信息
    txt_file = fopen("Data\\diary.txt", "a");
    if (txt_file == NULL) {
        perror("无法打开 diary.txt 文件");
        return;
    }

    // 根据事件代码获取对应的中文描述并写入 diary.txt 文件
    if (*incidentcode >= 1 && *incidentcode < sizeof(incident_descriptions) / sizeof(incident_descriptions[0])) {
        fprintf(txt_file, "%s\n完成", incident_descriptions[*incidentcode]);
    }

    fclose(txt_file);




    //record endtime
    fsave_time();


}











/**
 * @name:fget_time
 * @description: 获取当前本地时间并以 tm 类型存入 timedata.dat 文件
 * @file:时间暂存数据库C:\\cks\\Data\\timedata.dat
*/
void fget_time() {
    time_t current_time;
    struct tm localtimeori;
    struct tm *local_time = &localtimeori;
    char tc = 0;
    FILE *fp;

    // 获取当前时间戳
    current_time = time(NULL);
    // 将时间戳转换为本地时间
    local_time = localtime(&current_time);

    // 打开 timedata.dat 文件以二进制写入模式
    fp = fopen("Data\\timedata.dat", "wb");
    if (fp == NULL) {
        perror("无法打开 timedata.dat 文件进行写入");
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }

    // 将本地时间信息以二进制形式写入文件
    fwrite(local_time, sizeof(struct tm), 1, fp);

    // 关闭文件
    fclose(fp);
}


/**
 * @name:fsave_time
 * @description:从 timedata.dat 文件中读取 tm 类型时间
 *              并转存到 diary.txt、diary.dat 文件
 * @file:日志数据C:\\cks\\Data\\diary.dat；
 *       日志文档C:\\cks\\Data\\diary.txt
 */
void fsave_time() {
    char time_str[100];
    struct tm read_time;
    char tc = 0;
    FILE *fp_dat, *fp_txt, *fp_diarydat;

    // 打开 timedata.dat 文件以二进制读取模式
    fp_dat = fopen("Data\\timedata.dat", "rb");
    if (fp_dat == NULL) {
        perror("无法打开 timedata.dat 文件进行读取");
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }

    // 从 timedata.dat 文件中读取时间信息
    if (fread(&read_time, sizeof(struct tm), 1, fp_dat) != 1) {
        perror("读取 timedata.dat 文件时出错");
        fclose(fp_dat);
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }
    fclose(fp_dat);

    // 打开 diary.dat 文件以写入时间
    fp_diarydat = fopen("Data\\diary.dat", "ab");
    if (fp_diarydat == NULL) {
        perror("无法打开 diary.dat 文件进行写入");
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }

    // 将 timedata.dat里 时间信息写入 diary.dat 文件
    fwrite(&read_time, sizeof(struct tm), 1, fp_diarydat);

    // 关闭文件
    fclose(fp_diarydat);

    // 打开 diary.txt 文件以写入时间
    fp_txt = fopen("Data\\diary.txt", "a");
    if (fp_txt == NULL) {
        perror("无法打开 diary.txt 文件进行写入");
        printf("Press any button to exit...");
        tc = getchar();
        exit(1);
    }

    // 将读取到的时间信息格式化为字符串
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &read_time);

    // 将格式化后的时间信息写入 diary.txt 文件
    fprintf(fp_txt, "时间: %s\n", time_str);

    // 关闭文件
    fclose(fp_txt);
}