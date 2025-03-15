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
		int y = i * GRID_H + TITLE;

		solidrectangle(x, y, x + GRID_W, y + GRID_H);
	}
}

// ���������
void mouseMsg(ExMessage* msg) {
	if (startTime == 0) {
		startTime = clock();
	}

	// �жϷ���
	int x = flag[3] * GRID_W;
	int y = 3 * GRID_H + TITLE;

	// ���������һ���ڷ���
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
	// ���������
	srand(time(NULL));

	// ������Ϸ����
	initgraph(400, 700);	// ����һ�� 640x480 �Ĵ���

	// ��Ϸ��ʼ��
	setbkcolor(WHITE);
	cleardevice();
	init();

	// ����˫�����ͼ���⿨��
	BeginBatchDraw();

	// �����Ϣ
	ExMessage em;

	// ��Ϸ��ѭ��
	while (true) {
		// ����
		cleardevice();

		// ��Ϸ����
		draw();

		// ��Ϸˢ��
		FlushBatchDraw();
		
		// �û�����
		if (peekmessage(&em, EX_MOUSE)) {
			// ���������
			if (em.message == WM_LBUTTONDOWN) {
				mouseMsg(&em);
			}
		}

		// �ж���Ϸ�Ƿ����
		if (isOver) {
			MessageBox(GetHWnd(), "��Ϸ����", "��ʾ", MB_OK);
			break;
		}
	}

	// �ر�˫�����ͼ
	EndBatchDraw();

	// �ر���Ϸ����
	closegraph();

	return 0;
}