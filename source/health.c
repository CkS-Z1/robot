#include <allfunc.h>
struct HealthData 
{
    int systolic;       // 收缩压 (mmHg)
    int diastolic;      // 舒张压 (mmHg)
    int respiration;    // 呼吸频率 (次/分钟)
    int heart_rate;     // 心率 (bpm)
};

struct HealthData generate_health_data() 
{
    struct HealthData data;
    srand(time(0)); // 设置随机数种子[3]
    data.systolic = 90 + rand() % 51;  // 90-140 生成收缩压（正常范围：90-140mmHg）高血压前期：120-139/80-89 
    data.diastolic = 60 + rand() % 31; //生成舒张压（正常范围：60-90mmHg） 注意：舒张压应小于收缩压 
    while(data.diastolic >= data.systolic)
 {                
        data.diastolic = 60 + rand() % 31; // 确保生理合理性
 }
    data.respiration = 12 + rand() % 9;  // 呼吸频率（成人正常：12-20次/分钟）
     // 心率（正常：60-100bpm，运动员可能低至40）
    data.heart_rate = 40 + rand() % 61;  // 扩展范围至40-100   
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
    

    // 获取当前时间
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(datetime_str, sizeof(datetime_str), "%Y-%m-%d %H:%M:%S", timeinfo);

    // 打开 CSV 文件
    fp = fopen("hecare\\hedata.csv", "a+"); // 以追加方式打开
    if (fp == NULL) {
        printf("无法打开文件！\n");
        return;
    }

    // 如果是新文件，写入标题行
    fseek(fp, 0, SEEK_END); // 移动到文件末尾
    if (ftell(fp) == 0) { // 如果文件为空，则写入标题
        fprintf(fp, "时间,角色,收缩压(mmHg),舒张压(mmHg),呼吸频率(次/分钟),心率(bpm)\n");
    }

    // 写入数据，包括角色信息
    fprintf(fp, "%s,%s,%d,%d,%d,%d\n", datetime_str, person, data.systolic, data.diastolic, data.respiration, data.heart_rate);

    // 关闭文件
    fclose(fp);
}

int healthmonitor(int* page)
{
    struct HealthData current_data;
    char systolic_str[16], diastolic_str[16];
    char respiration_str[16], heart_rate_str[16];
    int j;
    char* file_path = NULL;        // 用于存储当前角色的健康数据路径
    const char* person = NULL;     // 用于标记角色（爷爷或奶奶）

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
    bar1(49, 410, 175, 450, 0x24367D); // 收缩压
    puthz(60, 418, "收缩压", 24, 24, 0xFFFFFF);
    bar1(49, 505, 175, 545, 0x24367D); // 舒张压
    puthz(60, 513, "舒张压", 24, 24, 0xFFFFFF);
    bar1(49, 591, 175, 631, 0x24367D); // 呼吸频率
    puthz(60, 599, "呼吸频率", 24, 24, 0xFFFFFF);
    bar1(49, 674, 175, 714, 0x24367D); // 心率
    puthz(60, 682, "心跳次数", 24, 24, 0xFFFFFF);
    draw_botton(103, 340, 274, 395, 0xB85798, 0xDDDD);
    prt_hz16_size(145, 355, 2, 2, "爷爷", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(717, 345, 888, 395, 0xB85798, 0xDDDD);
    prt_hz16_size(769, 355, 2, 2, "奶奶", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(800, 688, 950,722, 0xBC8F8F, 0xFFEFD5);
    prt_hz16_size(830, 690, 2, 2, "返回", 0xFFFFFF, "HZK\\HZK16s");
    bar1(800, 660, 957, 685, 0xF5FFFA);
    puthz(800, 660, "查询监测数据", 24, 24, 0x000000);
    mouse_on(mouse);

    while (1)
    {
        mouse_show(&mouse);
        if (mouse_press(83, 340, 254, 395) == 1) // 判断是爷爷
        {
            
            mouse_off(&mouse);
            file_path = "bmp\\health2.dat";
            person = "爷爷";
        }
        else if (mouse_press(737, 345, 908, 395) == 1) // 判断是奶奶
        {
            
            mouse_off(&mouse);
            file_path = "bmp\\health1.dat";
            person = "奶奶";
        }

        if (file_path != NULL)
        {
            FILE* file;

            // 生成健康数据
            current_data = generate_health_data();

            // 写入健康数据到 CSV 文件（包括角色信息）
            write_healthdata(current_data, person);

            // 保存当前健康数据到二进制文件
            file = fopen(file_path, "wb");
            if (file != NULL)
            {
                fwrite(&current_data, sizeof(struct HealthData), 1, file);
                fclose(file);
            }

            // 将数据转换为字符串并显示在界面上
            itoa(current_data.systolic, systolic_str, 10);
            itoa(current_data.diastolic, diastolic_str, 10);
            itoa(current_data.respiration, respiration_str, 10);
            itoa(current_data.heart_rate, heart_rate_str, 10);

            puthz(297, 136, "正在为您生成健康检测数据", 32, 32,0x000000);
            for (j = 0; j < 3; j++)
            {
                puthz(610 + 20 * j, 180, "·", 24, 24, 0x000000);
                delay(1000);
            }
            put_asc16_size(180, 418, 2, 2, systolic_str, 0x000000); // 打印收缩压
            put_asc16_size(270, 418, 2, 2, "mmHg", 0x000000);
            put_asc16_size(180, 513, 2, 2, diastolic_str, 0x000000); // 打印舒张压
            put_asc16_size(270, 513, 2, 2, "mmHg", 0x000000);
            put_asc16_size(180, 599, 2, 2, respiration_str, 0x000000); // 打印呼吸频率
            prt_hz16_size(270, 599, 1, 1, "次", 0x000000, "HZK\\HZK16s");
            put_asc16_size(290, 599, 1, 1, "/", 0x000000);
            prt_hz16_size(305, 599, 1, 1, "分钟", 0x000000,"HZK\\HZK16s");
            put_asc16_size(180, 682, 2, 2, heart_rate_str, 0x000000); // 打印心率
            put_asc16_size(270, 682, 2, 2, "bpm", 0x000000);
            delay(1000); // 延时1秒
            if (current_data.systolic > 140 || current_data.diastolic > 90)
            {
                puthz(366, 460, "老人的血压过高，请及时就医", 24, 24, 0x000000);
            }
                else if (current_data.systolic < 90 || current_data.diastolic < 60)
            {
                puthz(366, 460, "老人的血压过低，请及时就医", 24, 24, 0x000000);
            }
            else
            {
                puthz(366, 460, "血压正常", 24, 24, 0x000000);
            }
            
            delay(1000);
            if (current_data.respiration < 12)
            {
                puthz(368, 599, "呼吸频率过低", 24, 24, 0x000000);
            }
            else if (current_data.respiration > 20)
            {
                puthz(368, 599, "呼吸频率过高", 24, 24, 0x000000);
            }
            else
            {
                puthz(368, 599, "呼吸频率正常", 24, 24, 0x000000);
            }
            
            delay(1000);
            if (current_data.heart_rate < 60)
            {
                puthz(366, 682, "心跳频率过慢，请注意就医", 24, 24, 0x000000);
            }
            else if (current_data.heart_rate > 100)
            {
                puthz(366, 682, "心跳频率过快，请注意就医", 24, 24, 0x000000);
            }
            else
            {
                puthz(366, 682, "心跳频率正常", 24, 24, 0x000000);
            }
            bar1(290, 133, 682, 330, 0xFFFFFF); // 清空提示区域
            puthz(500,547, "请前往", 24, 24, 0x000000);
            puthz(670,547,"文件夹中查看近期所有数据！", 24, 24, 0x000000);
            put_asc16_size(570,544,2,2,"hecare",0xC0C0C0);
            delay(1500);
            bar1(180,415,700,712,0xffffff); // 清空健康数据区域
            bar1(490,544,970,650,0xffffff); // 清空文件夹提示区域
            mouse_on(mouse);
            file_path = NULL; // 重置路径，避免重复操作
        }
        else if (mouse_press(800, 660, 957, 685) == 1)
        {
            data_check(page);
            break;
        }
        else if (mouse_press(800, 688, 950,722) == 1) // 返回按钮
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
    char *file_path = NULL; // 用于存储当前角色的健康数据路径

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
    bar1(49, 410, 175, 450, 0x24367D); // 收缩压
    puthz(60, 418, "收缩压", 24, 24, 0xFFFFFF);
    bar1(49, 505, 175, 545, 0x24367D); // 舒张压
    puthz(60, 513, "舒张压", 24, 24, 0xFFFFFF);
    bar1(49, 591, 175, 631, 0x24367D); // 呼吸频率
    puthz(60, 599, "呼吸频率", 24, 24, 0xFFFFFF);
    bar1(49, 674, 175, 714, 0x24367D); // 心率
    puthz(60, 682, "心跳次数", 24, 24, 0xFFFFFF);
    draw_botton(103, 340, 274, 395, 0xB85798, 0xDDDD);
    prt_hz16_size(145, 355, 2, 2, "爷爷", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(717, 345, 888, 395, 0xB85798, 0xDDDD);
    prt_hz16_size(769, 355, 2, 2, "奶奶", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(800, 698, 950, 735, 0xBC8F8F, 0xFFEFD5);
    prt_hz16_size(835, 700, 2, 2, "返回", 0xFFFFFF, "HZK\\HZK16s");
    puthz(145,214, "点击按钮即可查询最近的检测数据", 32,32, 0x000000);
    mouse_on(mouse);
    while (1)
    {
        mouse_show(&mouse);
        if (mouse_press(83, 340, 254, 395) == 1) // 爷爷
        {
            file_path = "bmp\\health2.dat";
        }
        else if (mouse_press(737, 345, 908, 395) == 1) // 奶奶
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

                // 将数据转换为字符串
                itoa(loaded_data.systolic, systolic_str, 10);
                itoa(loaded_data.diastolic, diastolic_str, 10);
                itoa(loaded_data.respiration, respiration_str, 10);
                itoa(loaded_data.heart_rate, heart_rate_str, 10);

                // 显示健康数据
                bar1(176, 418, 737, 714, 0xFFFFFF);
                put_asc16_size(180, 418, 2, 2, systolic_str, 0x000000); // 收缩压
                put_asc16_size(270, 418, 2, 2, "mmhg", 0x000000);
                put_asc16_size(180, 513, 2, 2, diastolic_str, 0x000000); // 舒张压
                put_asc16_size(270, 513, 2, 2, "mmhg", 0x000000);
                put_asc16_size(180, 599, 2, 2, respiration_str, 0x000000); // 呼吸频率
                put_asc16_size(270, 599, 2, 2, "bpm", 0x000000);
                put_asc16_size(180, 682, 2, 2, heart_rate_str, 0x000000); // 心率
                put_asc16_size(270, 682, 2, 2, "HR", 0x000000);
            }
            else
            {
                puthz(366, 460, "您未对此对象进行过健康数据测量", 24, 24, 0xFF0000);
            }

            file_path = NULL; // 重置为 NULL
        }
        else if (mouse_press(800, 700, 950, 735) == 1) // 返回
        {
            *page = 5; 
            break;
        }
    }
    return 0;
}
