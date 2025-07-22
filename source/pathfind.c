#include "wasd.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GRID_SIZE 20
#define MAX_PATH_LENGTH 512
#define GRID_WIDTH (1024 / GRID_SIZE)
#define GRID_HEIGHT (768 / GRID_SIZE)

// 结构体用于A*搜索
typedef struct Node {
    int x, y;
    int g, h;
    int parentIndex;
    bool walkable;
} Node;

// 结构体用于openList元素（老编译器不支持C99结构体初始化）
typedef struct {
    int x, y;
    int g, h;
    int parent;
} OpenNode;

// 全局网格地图（用于寻路）
Node grid[GRID_WIDTH][GRID_HEIGHT];

// 全局辅助函数：根据坐标设置当前所在房间（用于自动寻路后的保存）
void updateRoomByPosition(PlayerState *player) {
    RoomID roomid = NONE;
    if (player->sx >= 60 && player->sx <= 404 && player->sy >= 10 && player->sy <= 222) {
        roomid = SECONDBEDROOM;
    } else if (player->sx >= 425 && player->sx <= 690 && player->sy >= 8 && player->sy <= 297) {
        roomid = MASTERBEDROOM;
    } else if (player->sx >= 705 && player->sx <= 947 && player->sy >= 10 && player->sy <= 138) {
        roomid = KITCHEN;
    } else if (player->sx >= 703 && player->sx <= 945 && player->sy >= 150 && player->sy <= 300) {
        roomid = DININGROOM;
    } else if (player->sx >= 404 && player->sx <= 941 && player->sy >= 368 && player->sy <= 677) {
        roomid = LIVINGROOM;
    } else if (player->sx >= 47 && player->sx <= 385 && player->sy >= 396 && player->sy <= 668) {
        roomid = BALCONY;
    }

    if (roomid != NONE) {
        writeRoomIDToFile(&roomid);
    }
}

// 初始化地图
void initGrid() {
    int i, j;
    int px, py;
    for (i = 0; i < GRID_WIDTH; i++) {
        for (j = 0; j < GRID_HEIGHT; j++) {
            px = i * GRID_SIZE + GRID_SIZE / 2;
            py = j * GRID_SIZE + GRID_SIZE / 2;

            // 若坐标接近餐厅文字区域，略向右偏移以避开障碍框
            if (px >= 727 && px <= 820 && py >= 190 && py <= 241) {
                px += 10; // 向右偏移10像素
            }

            if (canMove(&px, &py)) {
                grid[i][j].walkable = true;
            } else {
                grid[i][j].walkable = false;
            }
        }
    }
}

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2); // 曼哈顿距离
}

bool findPath(int startX, int startY, int goalX, int goalY, int path[MAX_PATH_LENGTH][2], int *pathLength) {
    OpenNode openList[GRID_WIDTH * GRID_HEIGHT];
    bool closed[GRID_WIDTH][GRID_HEIGHT] = { false };
    int openCount = 0;
    int parents[GRID_WIDTH][GRID_HEIGHT][2];
    int startGX, startGY, goalGX, goalGY;
    int bestIndex, i, j;
    int f1, f2;
    int cx, cy, px, py;
    int nx, ny;
    const int dirs[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    bool alreadyInOpen;
    OpenNode current, newNode;

    startGX = startX / GRID_SIZE;
    startGY = startY / GRID_SIZE;
    goalGX = goalX / GRID_SIZE;
    goalGY = goalY / GRID_SIZE;

    newNode.x = startGX;
    newNode.y = startGY;
    newNode.g = 0;
    newNode.h = heuristic(startGX, startGY, goalGX, goalGY);
    newNode.parent = -1;
    openList[openCount++] = newNode;

    while (openCount > 0) {
        bestIndex = 0;
        for (i = 1; i < openCount; i++) {
            f1 = openList[i].g + openList[i].h;
            f2 = openList[bestIndex].g + openList[bestIndex].h;
            if (f1 < f2) bestIndex = i;
        }

        current = openList[bestIndex];
        for (i = bestIndex; i < openCount - 1; i++) openList[i] = openList[i + 1];
        openCount--;
        closed[current.x][current.y] = true;

        if (current.x == goalGX && current.y == goalGY) {
            cx = goalGX;
            cy = goalGY;
            *pathLength = 0;
            while (!(cx == startGX && cy == startGY)) {
                path[*pathLength][0] = cx * GRID_SIZE + GRID_SIZE / 2;
                path[*pathLength][1] = cy * GRID_SIZE + GRID_SIZE / 2;
                (*pathLength)++;
                px = parents[cx][cy][0];
                py = parents[cx][cy][1];
                cx = px;
                cy = py;
            }
            return true;
        }

        for (i = 0; i < 4; i++) {
            nx = current.x + dirs[i][0];
            ny = current.y + dirs[i][1];
            if (nx >= 0 && ny >= 0 && nx < GRID_WIDTH && ny < GRID_HEIGHT) {
                if (grid[nx][ny].walkable && !closed[nx][ny]) {
                    alreadyInOpen = false;
                    for (j = 0; j < openCount; j++) {
                        if (openList[j].x == nx && openList[j].y == ny) {
                            alreadyInOpen = true;
                            break;
                        }
                    }
                    if (!alreadyInOpen) {
                        newNode.x = nx;
                        newNode.y = ny;
                        newNode.g = current.g + 1;
                        newNode.h = heuristic(nx, ny, goalGX, goalGY);
                        newNode.parent = 0;
                        openList[openCount++] = newNode;
                        parents[nx][ny][0] = current.x;
                        parents[nx][ny][1] = current.y;
                    }
                }
            }
        }
    }

    return false; // 未找到路径
}

void autoMoveToTarget(int startX, int startY, int targetX, int targetY, PlayerState *player) {
    int path[MAX_PATH_LENGTH][2];
    int pathLength = 0;
    int i;

    initGrid();
    if (!findPath(startX, startY, targetX, targetY, path, &pathLength)) return;

    for (i = pathLength - 1; i >= 0; i--) {
        delay(20);
        clearPreviousPosition(&player->sx, &player->sy);
        player->sx = path[i][0];
        player->sy = path[i][1];
        bar1(player->sx - 10, player->sy - 10, player->sx + 10, player->sy + 10, 0xF5F5F5);
    }

    // 根据新位置保存房间信息
    updateRoomByPosition(player);
}
