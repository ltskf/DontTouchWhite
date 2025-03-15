#include "easyx.h"	// 关键图形库
#include "ctime"
#include "cstdio"

#define TITLE 100
#define GRID_W 100
#define GRID_H 150

// 存储每一行黑块的编号
int flag[4] = { 3, 0, 1, 2 };

// 游戏结束标志
bool isOver = false;

// 得分
int score = 0;

// 计时
int startTime = 0;

// 初始化
void init() {
	for (int i = 0; i < 4; ++i) {
		flag[i] = rand() % 4;
	}
}

// 游戏绘制
void draw() {
	settextcolor(BLACK);
	settextstyle(36, 0, "楷体");
	char tt[100] = "别踩白色地砖";
	
	sprintf(tt, "别踩白色地砖 %d %d", score, startTime ? (clock() - startTime) / 1000 : 0);

	// 获取字符串宽度 居中显示
	int space = (getwidth() - textwidth(tt)) / 2;
	outtextxy(space, 20, tt);

	// 绘制线条
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);

	// 绘制格子
	for (int i = 0; i < 5; ++i) {
		line(0, TITLE + i * GRID_H, 400, TITLE + i * GRID_H);
		line(i * GRID_W, 100, i * GRID_W, 700);
	}

	// 绘制黑方块
	setfillcolor(BLACK);
	for (int i = 0; i < 4; ++i) {
		int x = flag[i] * GRID_W;
		int y = i * GRID_H + TITLE;

		solidrectangle(x, y, x + GRID_W, y + GRID_H);
	}
}

// 处理鼠标点击
void mouseMsg(ExMessage* msg) {
	if (startTime == 0) {
		startTime = clock();
	}

	// 判断方块
	int x = flag[3] * GRID_W;
	int y = 3 * GRID_H + TITLE;

	// 点中了最后一个黑方块
	if (msg->x >= x && msg->x <= x + GRID_W &&
		msg->y >= y && msg->y <= y + GRID_H) {
		for (int i = 3; i > 0; --i) {
			flag[i] = flag[i - 1];
		}
		flag[0] = rand() % 4;
		score++;
	}
	else {
		isOver = true;
	}
}

int main() {
	// 随机数种子
	srand(time(NULL));

	// 创建游戏窗口
	initgraph(400, 700);	// 创建一个 640x480 的窗口

	// 游戏初始化
	setbkcolor(WHITE);
	cleardevice();
	init();

	// 开启双缓冲绘图避免卡顿
	BeginBatchDraw();

	// 鼠标信息
	ExMessage em;

	// 游戏主循环
	while (true) {
		// 清屏
		cleardevice();

		// 游戏绘制
		draw();

		// 游戏刷新
		FlushBatchDraw();
		
		// 用户输入
		if (peekmessage(&em, EX_MOUSE)) {
			// 鼠标左键点击
			if (em.message == WM_LBUTTONDOWN) {
				mouseMsg(&em);
			}
		}

		// 判断游戏是否结束
		if (isOver) {
			MessageBox(GetHWnd(), "游戏结束", "提示", MB_OK);
			break;
		}
	}

	// 关闭双缓冲绘图
	EndBatchDraw();

	// 关闭游戏窗口
	closegraph();

	return 0;
}