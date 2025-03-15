#include "easyx.h"	// �ؼ�ͼ�ο�
#include "ctime"
#include "cstdio"

#define TITLE 100
#define GRID_W 100
#define GRID_H 150

// �洢ÿһ�кڿ�ı��
int flag[4] = { 3, 0, 1, 2 };

// ��Ϸ������־
bool isOver = false;

// �÷�
int score = 0;

// ��ʱ
int startTime = 0;

// ��ʼ��
void init() {
	for (int i = 0; i < 4; ++i) {
		flag[i] = rand() % 4;
	}
}

// ��Ϸ����
void draw() {
	settextcolor(BLACK);
	settextstyle(36, 0, "����");
	char tt[100] = "��Ȱ�ɫ��ש";
	
	sprintf(tt, "��Ȱ�ɫ��ש %d %d", score, startTime ? (clock() - startTime) / 1000 : 0);

	// ��ȡ�ַ������ ������ʾ
	int space = (getwidth() - textwidth(tt)) / 2;
	outtextxy(space, 20, tt);

	// ��������
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);

	// ���Ƹ���
	for (int i = 0; i < 5; ++i) {
		line(0, TITLE + i * GRID_H, 400, TITLE + i * GRID_H);
		line(i * GRID_W, 100, i * GRID_W, 700);
	}

	// ���ƺڷ���
	setfillcolor(BLACK);
	for (int i = 0; i < 4; ++i) {
		int x = flag[i] * GRID_W;
		int y = flag[i] * GRID_H + TITLE;

		solidrectangle(x, y, x + GRID_W, y + GRID_H);
	}
}

int main() {
	// ���������
	srand(time(NULL));

	// ������Ϸ����
	initgraph(400, 700);	// ����һ�� 640x480 �Ĵ���

	// ��Ϸ��ʼ��
	setbkcolor(WHITE);
	cleardevice();
	init();
	draw();

	// ����˫�����ͼ���⿨��
	BeginBatchDraw();

	// ��Ϸ��ѭ��
	while (true) {
		// ��Ϸ����

		// �û�����

		// �ж���Ϸ�Ƿ����

		// ��Ϸˢ��
		FlushBatchDraw();
	}

	// �ر�˫�����ͼ
	EndBatchDraw();

	// �ر���Ϸ����
	closegraph();

	return 0;
}