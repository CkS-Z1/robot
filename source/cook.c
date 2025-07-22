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
        printf("无法打开文件进行写入.\n");
    }
}

void load_food_selection(const char *filename, Food *food_selection) {
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        fread(food_selection, sizeof(Food), 1, file);
        fclose(file);
    } else {
        printf("无法打开文件进行读取.\n");
        // 初始化为 0，避免未加载到数据时出错
        memset(food_selection, 0, sizeof(Food));
    }
}


int cook_meal(int *page)
{
    int i; 
    Food food_selection; 
    load_food_selection("bmp\\food.dat", &food_selection); // 从文件加载状态
    

    mouse_off(&mouse);
    cook_design();//画出厨房的基本元素 
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
        save_food_selection("bmp\\food.dat", &food_selection); // 保存状态
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
    prt_hz16_size(123,325,2,2,"汤类",0x000000,"HZK\\HZK16s");
    prt_hz16_size(473,325,2,2,"主食",0x000000,"HZK\\HZK16s");
    prt_hz16_size(803,325,2,2,"菜肴",0x000000,"HZK\\HZK16s");
    prt_hz16_size(34,666,2,2,"请选择你的午饭菜品",0x000000,"HZK\\HZK16s");
    ThickDiagonalLine(977,21,1006,53,2,0xE6E6FA);
    ThickDiagonalLine(977,53,1006,21,2,0xE6E6FA);
    bar1(525,664,780,700,0xFF7F50);
    prt_hz16_size(529,666,2,2,"查看今日已选菜品",0x000000,"HZK\\HZK16s");
    mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);
        if(mouse_press(977,21,1006,53)==1)
        {
            *page=11;
            break;
        }
        if(mouse_press(71,314,266,366)==1)//汤类
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
    int y1 = 100, y2 = 100, y3 = 100; // Y坐标起始位置
    int has_selected = 0;             // 标志是否有已勾选的菜品
    int i;

    // 从文件加载数据
    load_food_selection("bmp\\food.dat", food_selection);

    mouse_off(&mouse);
    bar1(0, 0, 1024, 768, 0xffffff); // 清屏
    prt_hz16_size(100, 50, 2, 2, "已勾选的菜品如下", 0x000000, "HZK\\HZK16s");
    put_asc16_size(360, 50, 2, 2, ":", 0x000000);

    // 检查汤类
    for (i = 0; i < 3; i++) {
        if (food_selection->soup_selected[i] == 1) {
            has_selected = 1;
            switch (i) {
                case 0:
                    prt_hz16_size(30, y1, 2, 2, "藕汤", 0x000000, "HZK\\HZK16s");
                    y1 += 30;
                    break;
                case 1:
                    prt_hz16_size(30, y1, 2, 2, "西红柿鸡蛋汤", 0x000000, "HZK\\HZK16s");
                    y1 += 30;
                    break;
                case 2:
                    prt_hz16_size(30, y1, 2, 2, "紫菜汤", 0x000000, "HZK\\HZK16s");
                    y1 += 30;
                    break;
            }
        }
    }

    // 检查主食
    for (i = 0; i < 4; i++) {
        if (food_selection->staple_selected[i] == 1) {
            has_selected = 1;
            switch (i) {
                case 0:
                    prt_hz16_size(250, y2, 2, 2, "米饭", 0x000000, "HZK\\HZK16s");
                    y2 += 30;
                    break;
                case 1:
                    prt_hz16_size(250, y2, 2, 2, "面条", 0x000000, "HZK\\HZK16s");
                    y2 += 30;
                    break;
                case 2:
                    prt_hz16_size(250, y2, 2, 2, "烙饼", 0x000000, "HZK\\HZK16s");
                    y2 += 30;
                    break;
                case 3:
                    prt_hz16_size(250, y2, 2, 2, "馒头", 0x000000, "HZK\\HZK16s");
                    y2 += 30;
                    break;
            }
        }
    }

    // 检查菜肴
    for (i = 0; i < 9; i++) {
        if (food_selection->fry_selected[i] == 1) {
            has_selected = 1;
            switch (i) {
                case 0:
                    prt_hz16_size(400, y3, 2, 2, "酸辣土豆丝", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 1:
                    prt_hz16_size(400, y3, 2, 2, "鱼香肉丝", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 2:
                    prt_hz16_size(400, y3, 2, 2, "番茄炒蛋", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 3:
                    prt_hz16_size(400, y3, 2, 2, "麻婆豆腐", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 4:
                    prt_hz16_size(400, y3, 2, 2, "红烧茄子", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 5:
                    prt_hz16_size(400, y3, 2, 2, "清炒时蔬", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 6:
                    prt_hz16_size(400, y3, 2, 2, "宫保鸡丁", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 7:
                    prt_hz16_size(400, y3, 2, 2, "白灼虾", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
                case 8:
                    prt_hz16_size(400, y3, 2, 2, "地三鲜", 0x000000, "HZK\\HZK16s");
                    y3 += 30;
                    break;
            }
        }
    }

    // 如果没有勾选任何菜品
    if (!has_selected) {
        prt_hz16_size(100, y1, 2, 2, "您未选择任何菜品", 0xFF0000, "HZK\\HZK16s");
    }

    // “点击开始烹饪”按钮
    if (has_selected) {
        bar1(800, 600, 1008, 650, 0xFF7F50); // 激活状态
        prt_hz16_size(810, 610, 2, 2, "点击开始烹饪", 0x000000, "HZK\\HZK16s");
    } else {
        bar1(800, 600, 1008, 650, 0xF5FFFA); // 禁用状态
        prt_hz16_size(810, 610, 2, 2, "无菜品可烹饪", 0xB0E0E6, "HZK\\HZK16s");
    }

    // 返回按钮
    draw_botton(884, 712, 1011, 755, 0xBC8F8F, 0xffffff);
    prt_hz16_size(915, 715, 2, 2, "返回", 0x000000, "HZK\\HZK16s");

    mouse_on(mouse);
    while (1) {
        mouse_show(&mouse);

        // 返回按钮事件
        if (mouse_press(884, 712, 1011, 755) == 1) {
            orderfood(page, food_selection); // 返回页面
            break;
        }

        // “点击开始烹饪”按钮事件
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
    // 清空内存中的 food_selection 数据为未勾选
    for (i = 0; i < 3; i++) { // 汤类（3种）
        food_selection->soup_selected[i] = 0;
    }
    for (i = 0; i < 4; i++) { // 主食（4种）
        food_selection->staple_selected[i] = 0;
    }
    for (i = 0; i < 9; i++) { // 菜肴（9种）
        food_selection->fry_selected[i] = 0;
    }

    // 将修改后的数据保存到文件中
    save_food_selection("bmp\\food.dat", food_selection);

    // 记录日志开始
    incidentcode = cook;
    fstart_diary(&incidentcode, &eventtime);
    
    // 显示制作食物的提示
    bar1(0, 0, 1024, 768, 0xffffff); // 清屏
    puthz(360, 350, "正在为您制作食物", 32, 32, 0x000000);

    // 模拟制作食物的延迟
    delay(2000); // 假设制作食物需要2秒

    // 提示食物制作完成
    puthz(360, 400, "食物制作完成！请尽快食用", 32, 32, 0x000000);
    delay(2000); // 显示完成提示

    // 返回到 check_food 页面
    check_food(page, food_selection);

    //记录日志结束
    incidentcode = cook;
    fend_diary(&incidentcode, &eventtime);

    return 0; // 成功返回
}

int cook_soup(int *page, Food *food_selection) {
    // 加载上一次的勾选状态
    load_food_selection("bmp\\food.dat", food_selection);

    mouse_off(&mouse);
    Readbmp64k(0, 0, "bmp\\tang.bmp");
    prt_hz16_size(429, 714, 2, 2, "请勾选你需要的汤类", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(426, 88, 3, 3, "藕汤", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(426, 323, 3, 3, "西红柿鸡蛋汤", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(426, 563, 3, 3, "紫菜汤", 0x000000, "HZK\\HZK16s");
    
    // 根据上一次的状态绘制勾选框
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
    prt_hz16_size(895, 715, 2, 2, "确定", 0x000000, "HZK\\HZK16s");
    ThickDiagonalLine(977, 21, 1006, 53, 2, 0xE6E6FA);
    ThickDiagonalLine(977, 53, 1006, 21, 2, 0xE6E6FA);

    mouse_on(mouse);
    while (1) {
        int mouse_clicked = 0; // 记录是否已处理鼠标点击的标志

        mouse_show(&mouse);
       
        // 检测点击区域
        if (mouse_press(730, 103, 762, 129) == 1 && food_selection->soup_selected[0] == 0) { // 勾选藕汤
            mouse_off(&mouse);
            ThickDiagonalLine(732, 113, 749, 127, 2, 0x000000);
            ThickDiagonalLine(749, 127, 762, 105, 2, 0x000000);
            food_selection->soup_selected[0] = 1;
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(730, 332, 762, 358) == 1 && food_selection->soup_selected[1] == 0) { // 勾选西红柿鸡蛋汤
            mouse_off(&mouse);
            ThickDiagonalLine(732, 342, 749, 356, 2, 0x000000);
            ThickDiagonalLine(749, 356, 762, 334, 2, 0x000000);
            food_selection->soup_selected[1] = 1;
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(730, 578, 762, 604) == 1 && food_selection->soup_selected[2] == 0) { // 勾选紫菜汤
            mouse_off(&mouse);
            ThickDiagonalLine(732, 588, 749, 602, 2, 0x000000);
            ThickDiagonalLine(749, 602, 760, 580, 2, 0x000000);
            food_selection->soup_selected[2] = 1;
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(730, 103, 762, 129) == 1 && food_selection->soup_selected[0] == 1) { // 取消勾选藕汤
            mouse_off(&mouse);
            bar1(730, 103, 765, 128, 0xffffff);
            bar2(730, 103, 762, 129, 0x000000);
            food_selection->soup_selected[0] = 0; // 改为 0 以表示未勾选
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(730, 332, 762, 358) == 1 && food_selection->soup_selected[1] == 1) { // 取消勾选西红柿鸡蛋汤
            mouse_off(&mouse);
            bar1(730, 332, 765, 357, 0xffffff);
            bar2(730, 332, 762, 358, 0x000000);
            food_selection->soup_selected[1] = 0; // 改为 0 以表示未勾选
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(730, 578, 762, 604) == 1 && food_selection->soup_selected[2] == 1) { // 取消勾选紫菜汤
            mouse_off(&mouse);
            bar1(730, 575, 765, 603, 0xffffff);
            bar2(730, 578, 762, 604, 0x000000);
            food_selection->soup_selected[2] = 0; // 改为 0 以表示未勾选
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(884, 712, 1011, 755) == 1 && (food_selection->soup_selected[0] == 1 || food_selection->soup_selected[1] == 1 || food_selection->soup_selected[2] == 1)) { // 完成选菜
            save_food_selection("bmp\\food.dat", food_selection); // 保存状态
            prt_hz16_size(540, 680, 1, 1, "已为您添加勾选菜品至列表中", 0x000000, "HZK\\HZK16s");
            delay(1000);
            orderfood(page, food_selection);
            break;
        }
        else if (mouse_press(884, 712, 1011, 755) == 1 && !(food_selection->soup_selected[0] == 1 || food_selection->soup_selected[1] == 1 || food_selection->soup_selected[2] == 1)) { // 不能完成选菜
            prt_hz16_size(540, 680, 1, 1, "您未选择任何菜品", 0x000000, "HZK\\HZK16s");
            delay(1000);
            bar1(518, 679, 680, 700, 0xffffff);
        }
        else if (mouse_press(977, 21, 1006, 53) == 1) {
            save_food_selection("bmp\\food.dat", food_selection); // 保存状态
            orderfood(page, food_selection);
            break;
        }

        // 如果已经点击并处理过一次，等待下一次点击
        if (mouse_clicked) {
            delay(200);
        }
    }

    return 0;
}
int cook_staplefood(int *page, Food *food_selection) {
    // 加载上一次的勾选状态
    load_food_selection("bmp\\food.dat", food_selection);

    mouse_off(&mouse);
    Readbmp64k(0, 0, "bmp\\staple.bmp");
    prt_hz16_size(301, 722, 2, 2, "请勾选你需要的主食", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(325, 70, 3, 3, "米饭", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(325, 262, 3, 3, "面条", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(325, 440, 3, 3, "烙饼", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(325, 640, 3, 3, "馒头", 0x000000, "HZK\\HZK16s");
    bar2(478, 81, 512, 112, 0x000000);
    bar2(478, 261, 512, 292, 0x000000);
    bar2(478, 441, 512, 472, 0x000000);
    bar2(478, 651, 512, 682, 0x000000);

    // 根据上一次的勾选状态绘制勾选框
    if (food_selection->staple_selected[0] == 1) { // 米饭已被选中
        ThickDiagonalLine(480, 95, 495, 110, 2, 0x000000);
        ThickDiagonalLine(495, 110, 512, 81, 2, 0x000000);
    }
    if (food_selection->staple_selected[1] == 1) { // 面条已被选中
        ThickDiagonalLine(480, 275, 495, 290, 2, 0x000000);
        ThickDiagonalLine(495, 290, 512, 261, 2, 0x000000);
    }
    if (food_selection->staple_selected[2] == 1) { // 烙饼已被选中
        ThickDiagonalLine(480, 455, 495, 470, 2, 0x000000);
        ThickDiagonalLine(495, 470, 512, 441, 2, 0x000000);
    }
    if (food_selection->staple_selected[3] == 1) { // 馒头已被选中
        ThickDiagonalLine(480, 664, 495, 680, 2, 0x000000);
        ThickDiagonalLine(495, 680, 512, 651, 2, 0x000000);
    }

    draw_botton(884, 712, 1011, 755, 0xBC8F8F, 0xffffff);
    prt_hz16_size(895, 715, 2, 2, "确定", 0x000000, "HZK\\HZK16s");
    ThickDiagonalLine(977, 21, 1006, 53, 2, 0xE6E6FA);
    ThickDiagonalLine(977, 53, 1006, 21, 2, 0xE6E6FA);
    mouse_on(mouse);

    while (1) {
        int mouse_clicked = 0; // 记录是否已处理鼠标点击的标志
        mouse_show(&mouse);

        // 检测点击区域
        if (mouse_press(478, 81, 512, 112) == 1 && food_selection->staple_selected[0] == 0) { // 勾选米饭
            mouse_off(&mouse);
            ThickDiagonalLine(480, 95, 495, 110, 2, 0x000000);
            ThickDiagonalLine(495, 110, 512, 81, 2, 0x000000);
            food_selection->staple_selected[0] = 1;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 261, 512, 292) == 1 && food_selection->staple_selected[1] == 0) { // 勾选面条
            mouse_off(&mouse);
            ThickDiagonalLine(480, 275, 495, 290, 2, 0x000000);
            ThickDiagonalLine(495, 290, 512, 261, 2, 0x000000);
            food_selection->staple_selected[1] = 1;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 441, 512, 472) == 1 && food_selection->staple_selected[2] == 0) { // 勾选烙饼
            mouse_off(&mouse);
            ThickDiagonalLine(480, 455, 495, 470, 2, 0x000000);
            ThickDiagonalLine(495, 470, 512, 441, 2, 0x000000);
            food_selection->staple_selected[2] = 1;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 651, 512, 682) == 1 && food_selection->staple_selected[3] == 0) { // 勾选馒头
            mouse_off(&mouse);
            ThickDiagonalLine(480, 664, 495, 680, 2, 0x000000);
            ThickDiagonalLine(495, 680, 512, 651, 2, 0x000000);
            food_selection->staple_selected[3] = 1;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 81, 512, 112) == 1 && food_selection->staple_selected[0] == 1) { // 取消勾选米饭
            mouse_off(&mouse);
            bar1(478, 79, 515, 113, 0xffffff);
            bar2(478, 81, 512, 112, 0x000000);
            food_selection->staple_selected[0] = 0;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 261, 512, 292) == 1 && food_selection->staple_selected[1] == 1) { // 取消勾选面条
            mouse_off(&mouse);
            bar1(478, 259, 515, 293, 0xffffff);
            bar2(478, 261, 512, 292, 0x000000);
            food_selection->staple_selected[1] = 0;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 441, 512, 472) == 1 && food_selection->staple_selected[2] == 1) { // 取消勾选烙饼
            mouse_off(&mouse);
            bar1(478, 439, 515, 473, 0xffffff);
            bar2(478, 441, 512, 472, 0x000000);
            food_selection->staple_selected[2] = 0;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(478, 651, 512, 682) == 1 && food_selection->staple_selected[3] == 1) { // 取消勾选馒头
            mouse_off(&mouse);
            bar1(478, 649, 515, 683, 0xffffff);
            bar2(478, 651, 512, 682, 0x000000);
            food_selection->staple_selected[3] = 0;
            mouse_clicked = 1;
            mouse_on(mouse);
        } else if (mouse_press(884, 712, 1011, 755) == 1) { // 完成选菜
            if (food_selection->staple_selected[0] || food_selection->staple_selected[1] || food_selection->staple_selected[2] || food_selection->staple_selected[3]) {
                save_food_selection("bmp\\food.dat", food_selection); // 保存状态
                prt_hz16_size(440, 685, 1, 1, "已为您添加勾选菜品至列表中", 0x000000, "HZK\\HZK16s");
                delay(1000);
                *page = 14;
                break;
            } else {
                prt_hz16_size(540, 680, 1, 1, "您未选择任何菜品", 0x000000, "HZK\\HZK16s");
                delay(1000);
                bar1(518, 679, 680, 700, 0xffffff);
            }
        } else if (mouse_press(977, 21, 1006, 53) == 1) { // 返回
            save_food_selection("bmp\\food.dat", food_selection); // 保存状态
            orderfood(page, food_selection);
            break;
        }

        if (mouse_clicked) delay(200);
    }
    return 0;
}





int cook_fry(int *page, Food *food_selection) {
    // 加载上一次的勾选状态
    load_food_selection("bmp\\food.dat", food_selection);

    mouse_off(&mouse);
    Readbmp64k(0, 0, "bmp\\fry.bmp");
    prt_hz16_size(72, 729, 2, 2, "请勾选你需要的主食", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(70, 181, 1, 1, "酸辣土豆丝", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(404, 181, 1, 1, "鱼香肉丝", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(704, 181, 1, 1, "番茄炒蛋", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(75, 439, 1, 1, "麻婆豆腐", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(404, 439, 1, 1, "红烧茄子", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(704, 439, 1, 1, "清炒时蔬", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(75, 700, 1, 1, "宫保鸡丁", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(404, 700, 1, 1, "白灼虾", 0x000000, "HZK\\HZK16s");
    prt_hz16_size(704, 700, 1, 1, "地三鲜", 0x000000, "HZK\\HZK16s");

    // 绘制选择框的边框 
    bar2(152, 175, 177, 199, 0x000000);
    bar2(472, 175, 498, 196, 0x000000);
    bar2(772, 175, 798, 196, 0x000000);
    bar2(149, 436, 177, 457, 0x000000);
    bar2(472, 436, 498, 457, 0x000000);
    bar2(772, 436, 798, 457, 0x000000);
    bar2(149, 698, 177, 719, 0x000000);
    bar2(472, 698, 498, 719, 0x000000);
    bar2(772, 698, 798, 719, 0x000000);

    // 根据上一次的勾选状态绘制勾选框
    if (food_selection->fry_selected[0] == 1) { // 酸辣土豆丝已被选中
        ThickDiagonalLine(157, 185, 166, 197, 2, 0x000000);
        ThickDiagonalLine(166, 197, 177, 177, 2, 0x000000);
    }
    if (food_selection->fry_selected[1] == 1) { // 鱼香肉丝已被选中
        ThickDiagonalLine(477, 185, 488, 194, 2, 0x000000);
        ThickDiagonalLine(488, 194, 498, 177, 2, 0x000000);
    }
    if (food_selection->fry_selected[2] == 1) { // 番茄炒蛋已被选中
        ThickDiagonalLine(777, 185, 788, 194, 2, 0x000000);
        ThickDiagonalLine(788, 194, 798, 177, 2, 0x000000);
    }
    if (food_selection->fry_selected[3] == 1) { // 麻婆豆腐已被选中
        ThickDiagonalLine(154, 446, 167, 455, 2, 0x000000);
        ThickDiagonalLine(167, 455, 177, 438, 2, 0x000000);
    }
    if (food_selection->fry_selected[4] == 1) { // 红烧茄子已被选中
        ThickDiagonalLine(477, 446, 488, 455, 2, 0x000000);
        ThickDiagonalLine(488, 455, 498, 438, 2, 0x000000);
    }
    if (food_selection->fry_selected[5] == 1) { // 清炒时蔬已被选中
        ThickDiagonalLine(777, 446, 788, 455, 2, 0x000000);
        ThickDiagonalLine(788, 455, 798, 438, 2, 0x000000);
    }
    if (food_selection->fry_selected[6] == 1) { // 宫保鸡丁已被选中
        ThickDiagonalLine(154, 708, 167, 717, 2, 0x000000);
        ThickDiagonalLine(167, 717, 177, 700, 2, 0x000000);
    }
    if (food_selection->fry_selected[7] == 1) { // 白灼虾已被选中
        ThickDiagonalLine(477, 708, 488, 717, 2, 0x000000);
        ThickDiagonalLine(488, 717, 498, 700, 2, 0x000000);
    }
    if (food_selection->fry_selected[8] == 1) { // 地三鲜已被选中
        ThickDiagonalLine(777, 708, 788, 717, 2, 0x000000);
        ThickDiagonalLine(788, 717, 798, 700, 2, 0x000000);
    }

    // 绘制确认按钮和返回按钮
    ThickDiagonalLine(977, 21, 1006, 53, 2, 0xE6E6FA);
    ThickDiagonalLine(977, 53, 1006, 21, 2, 0xE6E6FA);
    draw_botton(884, 712, 1011, 755, 0xBC8F8F, 0xffffff);
    prt_hz16_size(895, 715, 2, 2, "确定", 0x000000, "HZK\\HZK16s");
    mouse_on(mouse);

    while (1) {
        int mouse_clicked = 0; // 记录是否已处理鼠标点击的标志
        mouse_show(&mouse);

        // 检测鼠标点击区域（点击逻辑保持不变，省略部分重复代码）
        if (mouse_press(152, 175, 177, 199) == 1 && food_selection->fry_selected[0] == 0) { 
            mouse_off(&mouse);
            ThickDiagonalLine(157, 185, 166, 197, 2, 0x000000);
            ThickDiagonalLine(166, 197, 177, 177, 2, 0x000000);
            food_selection->fry_selected[0] = 1;
            mouse_clicked = 1;
            mouse_on(mouse);
        }
        else if (mouse_press(472,175,498,196) == 1 &&food_selection->fry_selected[1]  == 0) // 勾选鱼香肉丝
        {
            mouse_off(&mouse);
            ThickDiagonalLine(477,185,488,194, 2, 0x000000);
            ThickDiagonalLine(488,194,498,177, 2, 0x000000);
            food_selection->fry_selected[1] = 1;
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(772,175,798,196) == 1 && food_selection->fry_selected[2]== 0) // 勾选番茄炒蛋
        {
            mouse_off(&mouse);
            ThickDiagonalLine(777,185,788,194, 2, 0x000000);
            ThickDiagonalLine(788,194,798,177, 2, 0x000000);
            food_selection->fry_selected[2] = 1;
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(149,436,177,457) == 1 &&  food_selection->fry_selected[3] == 0) // 勾选麻婆豆腐
        {
            mouse_off(&mouse);
            ThickDiagonalLine(154,446,167,455, 2, 0x000000);
            ThickDiagonalLine(167,455,177,438, 2, 0x000000);
            food_selection->fry_selected[3] = 1;
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(472,436,498,457) == 1 &&   food_selection->fry_selected[4] == 0) // 勾选红烧茄子
        {
            mouse_off(&mouse);
            ThickDiagonalLine(477,446,488,455, 2, 0x000000);
            ThickDiagonalLine(488,455,498,438, 2, 0x000000);
            food_selection->fry_selected[4] = 1;
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(772,436,798,457) == 1 &&   food_selection->fry_selected[5] == 0) // 勾选清炒时蔬
        {
            mouse_off(&mouse);
            ThickDiagonalLine(777,446,788,455, 2, 0x000000);
            ThickDiagonalLine(788,455,798,438, 2, 0x000000);
            food_selection->fry_selected[5] = 1;
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(149,698,177,719) == 1 && food_selection->fry_selected[6] == 0) // 勾选宫保鸡丁
        {
            mouse_off(&mouse);
            ThickDiagonalLine(154,708,167,717, 2, 0x000000);
            ThickDiagonalLine(167,717,177,700, 2, 0x000000);
            food_selection->fry_selected[6] = 1;
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(472,698,498,719) == 1 && food_selection->fry_selected[7] == 0) // 勾选白灼虾
        {
            mouse_off(&mouse);
            ThickDiagonalLine(477,708,488,717, 2, 0x000000);
            ThickDiagonalLine(488,717,498,700, 2, 0x000000);
            food_selection->fry_selected[7] = 1;
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(772,698,798,719) == 1 && food_selection->fry_selected[8] == 0) // 勾选地三鲜
        {
            mouse_off(&mouse);
            ThickDiagonalLine(777,708,788,717, 2, 0x000000);
            ThickDiagonalLine(788,717,798,700, 2, 0x000000);
            food_selection->fry_selected[8]  = 1;
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(152,175,177,199) == 1 &&  food_selection->fry_selected[0] == 1) // 取消勾选酸辣土豆丝
          {
            mouse_off(&mouse);
            bar1(152,175,179,199, 0xffffff);
            bar2(152,175,177,199, 0x000000);
            food_selection->fry_selected[0]= 0; // 改为 0 以表示未勾选
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
          }
        else if (mouse_press(472,175,498,196) == 1 && food_selection->fry_selected[1] == 1) //取消勾选鱼香肉丝
        {
            mouse_off(&mouse);
            bar1(472,175,500,196, 0xffffff);
            bar2(472,175,498,196, 0x000000);
            food_selection->fry_selected[1]= 0; // 改为 0 以表示未勾选
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(772,175,798,196) == 1 &&  food_selection->fry_selected[2]== 1) //取消勾选番茄炒蛋
        {
            mouse_off(&mouse);
            bar1(772,175,800,196, 0xffffff);
            bar2(772,175,798,196, 0x000000);
            food_selection->fry_selected[2]= 0; // 改为 0 以表示未勾选
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(149,436,177,457) == 1 &&  food_selection->fry_selected[3] == 1) //取消勾选麻婆豆腐
        {
            mouse_off(&mouse);
            bar1(149,436,179,457, 0xffffff);
            bar2(149,436,177,457, 0x000000);
            food_selection->fry_selected[3]= 0; // 改为 0 以表示未勾选
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(472,436,498,457) == 1 && food_selection->fry_selected[4] == 1) //取消勾选红烧茄子
        {
            mouse_off(&mouse);
            bar1(472,436,500,457, 0xffffff);
            bar2(472,436,498,457, 0x000000);
            food_selection->fry_selected[4]= 0; // 改为 0 以表示未勾选
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(772,436,798,457) == 1 &&  food_selection->fry_selected[5] == 1) //取消勾选清炒时蔬
        {
            mouse_off(&mouse);
            bar1(772,436,800,457, 0xffffff);
            bar2(772,436,798,457,0x000000);
            food_selection->fry_selected[5]= 0; // 改为 0 以表示未勾选
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(149,698,177,719) == 1 &&  food_selection->fry_selected[6] == 1) //取消勾选宫保鸡丁
        {
            mouse_off(&mouse);
            bar1(149,698,181,719, 0xffffff);
            bar2(149,698,179,719, 0x000000);
            food_selection->fry_selected[6]= 0; // 改为 0 以表示未勾选
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(472,698,498,719) == 1 &&  food_selection->fry_selected[7] == 1) //取消勾选白灼虾
        {
            mouse_off(&mouse);
            bar1(472,698,500,719, 0xffffff);
            bar2(472,698,498,719, 0x000000);
            food_selection->fry_selected[7]= 0; // 改为 0 以表示未勾选
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }
        else if (mouse_press(772,698,798,719) == 1 &&  food_selection->fry_selected[8] == 1) //取消勾选地三鲜
        {
            mouse_off(&mouse);
            bar1(772,698,800,719, 0xffffff);
            bar2(772,698,798,719, 0x000000);
            food_selection->fry_selected[8]= 0; // 改为 0 以表示未勾选
            mouse_clicked = 1; // 处理这个点击
            mouse_on(mouse);
        }

        else if(mouse_press(977,21,1006,53)==1)
        {
            save_food_selection("bmp\\food.dat", food_selection); // 保存状态
            orderfood(page,food_selection);
            break;
        }
        else if (mouse_press(884, 712, 1011, 755) == 1) 
        {
            int has_selected = 0;  // 是否有勾选标志
            int i;
            for ( i = 0; i < 9; i++)
            {
                    if (food_selection->fry_selected[i] == 1) {
                        has_selected = 1;
                        break;  // 找到勾选立即退出循环
                    }
            }
            if (has_selected) 
            {
                save_food_selection("bmp\\food.dat", food_selection); // 保存状态
                prt_hz16_size(465,740, 1, 1, "已为您添加勾选菜品至列表中", 0x000000, "HZK\\HZK16s");
                delay(1000);
                *page = 14;
                break;
            } 
            else 
            {
                prt_hz16_size(465, 740, 1, 1, "您未选择任何菜品", 0x000000, "HZK\\HZK16s");
                delay(1000);
                bar1(460,738,650,758,0xffffff);
            }
        }
        if (mouse_clicked) 
        {
             // 通过短暂停顿，避免过快的点击处理
             delay(200); 
        }
    }
}

void  cook_design()
{
    bar1(0,0,1024,768,0xF5FFFA);
    puthz(209,42,"欢迎来到厨房，请点餐哦！", 32, 32,0x000000);
    //画冰箱
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

    //画橱柜
    Line3(159,365,364,365,2,0x32CD32);
    Line3(364,365,364,589,2,0x32CD32);
    Line3(364,589,159,589,2,0x32CD32);
    Line3(258,365,258,589,2,0x32CD32);
    Line3(159,365,159,589,2,0x32CD32);
    bar1(241,451,250,483,0x9ACD32);
    bar1(269,451,278,483,0x9ACD32);

    //画微波炉
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

    //画灶台
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

    //画锅
    Line1(562,266,612,367,0x6A5ACD);
    Line2(612,267,621,281,0x6A5ACD);
    Circle(589,261,4,0x556B2F);
    Line2(564,341,574,336,0x6A5ACD);
    Line2(599,336,609,341,0x6A5ACD);

    //画平底锅
    Line1(633,318,704,318,0x6A5ACD);
    Line2(633,318,639,337,0x6A5ACD);
    Line1(639,337,698,337,0x6A5ACD);
    Line2(698,337,704,318,0x6A5ACD);
    Line2(654,337,647,342,0x6A5ACD);
    Line2(683,337,686,342,0x6A5ACD);
    Line1(701,330,715,330,0x6A5ACD);
    bar2(715,325,748,335,0x6A5ACD);

    //画抽烟机
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

    //画炊具
    bar2(408,232,532,249,0x6A5ACD);
    Circle(434,240,4,0x6A5ACD);
    Circle(471,240,4,0x6A5ACD);
    Circle(506,240,4,0x6A5ACD);
    Line1(434,240,434,261,0x6A5ACD);
    Line1(471,240,470,261,0x6A5ACD);
    Line1(506,240,506,261,0x6A5ACD);
    //画铲子1
    bar2(427,261,441,305,0x6A5ACD);
    Circle(434,325,20,0x6A5ACD);
    //画铲子2
    bar2(465,261,477,312,0x6A5ACD);
    Line2(465,312,459,322,0x6A5ACD);
    Line2(477,312,483,322,0x6A5ACD);
    Line1(459,322,459,343,0x6A5ACD);
    Line1(483,322,483,343,0x6A5ACD);
    Line1(459,343,483,343,0x6A5ACD);    
    //画搅拌铲
    bar2(500,260,512,309,0x6A5ACD);
    DrawEllipse(506,329,15,20,0x6A5ACD);
    Line1(498,315,498,344,0x6A5ACD);
    Line1(514,315,514,344,0x6A5ACD);
    Line1(506,309,506,349,0x6A5ACD);
  
    //画桌子
    FillEllipse(866,563,132,47,0x66FF59);
    FillEllipse(866,714,50,23,0x66FF59);
    Line3(834,611,834,699,3,0x66FF59);
    Line3(899,611,899,699,3,0x66FF59);
    draw_botton(925,727,1013,756,0x4D1F00,0xffffff);
    prt_hz16_size(945,735,1,1,"返回",0x000000,"HZK\\HZK16s");
    draw_botton(42,25,175,66,0xCD5C5C,0xffffff);
    prt_hz16_size(70,30,2,2,"点餐",0x000000,"HZK\\HZK16s");
    }


