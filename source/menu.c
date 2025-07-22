#include <allfunc.h>


void menu_on(int *page)
{
    Incidentcode incidentcode; //事件代码
    struct tm eventtime;
    int bar_width = 60;  // 电量条总宽度
    char battery_level[10];  // 电量字符串
    int random_number;       // 当前电量
    FILE *file;

    // 文件路径
    char *file_path = "Data\\battary.dat";

    // 读取电量值
    file = fopen(file_path, "rb");
    if (file == NULL)  // 如果文件不存在，初始化电量为100
    {
        random_number = 100;
        file = fopen(file_path, "wb");
    }
    if (file == NULL)  // 如果文件不存在，初始化电量为100
    {
        random_number = 100;
        file = fopen(file_path, "wb");
        if (file == NULL)
        {
            printf("无法创建文件！\n");
            exit(1);
        }
        fwrite(&random_number, sizeof(int), 1, file);
        fclose(file);
    }
    else  // 读取文件中的电量值
    {
        fread(&random_number, sizeof(int), 1, file);
        fclose(file);
    }

    // 每次进入界面时，电量减少5（最小为0）
    random_number -= 5;
    if (random_number < 0)
    {
        random_number = 0;
    }

    // 将新的电量值写回文件
    file = fopen(file_path, "wb");
    if (file == NULL)
    {
        printf("无法写入文件！\n");
        exit(1);
    }
    fwrite(&random_number, sizeof(int), 1, file);
    fclose(file);

    // 将电量值转换为字符串
    itoa(random_number, battery_level, 10);
    mouse_off(&mouse);

    // 初始化界面（绘图等）
    bar1(0, 0, 1024, 768, 0x5686BF);
    bar1(35, 32, 989, 744, 0xFFFFFF);
    ThickDiagonalLine(35,32,989,32,2,0x003399);
    ThickDiagonalLine(35,32,35,744,2,0x003399);
    ThickDiagonalLine(35,744,989,744,2,0x003399);
    ThickDiagonalLine(989,32,989,744,2,0x003399); 
    Readbmp64k(67,50,"bmp\\robot.bmp"); 
    bar1(857, 19, 1004, 67, 0x1E90FF);
    prt_hz16_size(865,25, 2,2, "聊天功能", 0xFFFFFF, "HZK\\HZK16s");
    bar2(280,695,340,726,0x4D1F00);  // 机器人充电部分
    prt_hz16_size(62,695, 2, 2, "机器人电量", 0x000000, "HZK\\HZK16s");
    put_asc16_size(442,695,2,2,"%",0x000000);	
    draw_botton(511,690,615,731,0xFF7F50,0x0000FF);
    prt_hz16_size(530,695, 2, 2, "充电", 0xFFFFFF, "HZK\\HZK16s");
    put_asc16_size(390,695,2,2,battery_level,0x000000);

    // 根据电量绘制电量条
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

    // 其他按钮和界面元素
    draw_botton(540,130,840,200,0xFF7F50,0x0000FF);
    prt_hz16_size(605,140, 3, 3, "家庭服务", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(540,260,840,330,0xFF7F50,0x0000FF);
    prt_hz16_size(605,270, 3, 3, "健康监测", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(540,390,840,460,0xFF7F50,0x0000FF);
    prt_hz16_size(585,400, 3, 3, "机器人日志", 0xFFFFFF, "HZK\\HZK16s");
    draw_botton(540,520,840,590,0xFF7F50,0x0000FF);
    prt_hz16_size(620,530, 3, 3, "平面图", 0xFFFFFF, "HZK\\HZK16s");
    // 退出按钮
    draw_botton(840,660,958,717,0xFF7F50,0x000000);
    prt_hz16_size(840,675, 2, 2, "返回登录", 0xFFFFFF, "HZK\\HZK16s");

    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);

        // 电量为0时，只能充电
        if (random_number == 0)
        {
            prt_hz16_size(511,646, 1, 1, "电量已耗尽，请充电！", 0xFAF0E6, "HZK\\HZK16s");
            if(mouse_press(511,690,615,731)==1)  // 充电按钮
            {
                mouse_off(&mouse);
                bar1(510,645,660,680,0xfffffff); // 覆盖掉提示
                while(random_number<100)
                {
                    random_number += 5;
                    if(random_number > 100) random_number = 100;
                    itoa(random_number, battery_level, 10);
                    bar1(280,695,280+bar_width * random_number / 100,726,0x4D1F00);
                    bar1(385,695,425,725,0xffffff);
                    put_asc16_size(390,695,2,2,battery_level,0x000000);

                    // 电量充满后记录事件
                    if (random_number == 100)
                    {
                        incidentcode = battery;
                        fstart_diary(&incidentcode, &eventtime);
                        fend_diary(&incidentcode, &eventtime);
                    }
                    delay(300);
                }
                // 更新文件中的电量值
                file = fopen(file_path, "wb");
                if (file != NULL)
                {
                    fwrite(&random_number, sizeof(int), 1, file);
                    fclose(file);
                }
                mouse_show(&mouse);
            }
            continue; // 阻止其他操作
        }

        // 其他按钮操作逻辑保持不变
        if (mouse_press(540,130,840,200)==1)//家庭服务
        {
            *page = 12;
            break;
        }
        else if (mouse_press(540,260,840,330)==1)//健康监测
        {
            *page = 5;
            break;
        }
        else if (mouse_press(540,390,840,460)==1)//机器人日志
        {
            *page = 13;
            break;
        }
        else if (mouse_press(540,520,840,590)==1)//平面图
        {
            *page = 17;
            break;
        }
        else if(mouse_press(857, 19, 1004, 67)==1)//聊天功能
        {
            *page=15;
            break;
        }
        else if (mouse_press(840,660,958,717)==1)//返回登录
        {
            *page = 2;
            break;
        }
        else  if(mouse_press(511,690,615,731)==1)
        {
            mouse_off(&mouse);//不允许中断

            while(random_number<=100)
            {
                if(random_number==100)
                {
                    prt_hz16_size(640,690, 2, 2, "已充满电！", 0x000000, "HZK\\HZK16s");
                    delay(1000);
                    bar1(635,690,810,723,0xffffff);
                    break;
                }
                else if(random_number<=95)
                {
                    random_number+=5;
                      // 将新的电量值写回文件
                    file = fopen(file_path, "wb");
                    if (file == NULL)
                    {
                         printf("无法写入文件！\n");
                         exit(1);
                    }
                    fwrite(&random_number, sizeof(int), 1, file);
                    fclose(file);
                    if(random_number==100)//充满了，记录
                    {
                        // 记录事件
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


