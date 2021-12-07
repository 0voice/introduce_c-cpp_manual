#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>

int map[8][8] =
{
	{0,0,1,1,1,0,0,0},
	{0,0,1,4,1,0,0,0},
	{0,0,1,0,1,1,1,1},
	{1,1,1,3,0,3,4,1},
	{1,4,0,3,2,1,1,1},
	{1,1,1,1,3,1,0,0},
	{0,0,0,1,4,1,0,0},
	{0,0,0,1,1,1,0,0},
};


IMAGE personImg;
IMAGE personDestImg;
IMAGE boxImg;
IMAGE boxDestImg;
IMAGE destImg;
IMAGE wallImg;
IMAGE blankImg;

#define MAP_BLANK 0
#define MAP_WALL 1
#define MAP_PERSON 2
#define MAP_BOX 3
#define MAP_DEST 4
#define MAP_PERSON_DEST 6
#define MAP_BOX_DEST 7


#define DIRE_TOP 1
#define DIRE_LEFT 2
#define DIRE_RIGHT 3
#define DIRE_BOTTOM 4

struct Point {
	int x;
	int y;
};

IMAGE* mapload(int type)
{
	IMAGE* img = NULL;
	switch (type)
	{
	case MAP_BLANK:
		img = &blankImg;
		break;
	case MAP_WALL:
		img = &wallImg;
		break;
	case MAP_PERSON:
		img = &personImg;
		break;
	case MAP_BOX:
		img = &boxImg;
		break;
	case MAP_DEST:
		img = &destImg;
		break;
	case MAP_PERSON_DEST:
		img = &personDestImg;
		break;
	case MAP_BOX_DEST:
		img = &boxDestImg;
		break;
	default:
		break;
	}
	return img;
}

//���ص�ͼ
void drawMap()
{
	BeginBatchDraw();
	loadimage(&personImg, L"images/person.png", 64,64);
	loadimage(&personDestImg, L"images/person.png", 64, 64);
	loadimage(&boxImg, L"images/box.png", 64, 64);
	loadimage(&boxDestImg, L"images/box_dest.png", 64, 64);
	loadimage(&destImg, L"images/dest.png", 64, 64);
	loadimage(&wallImg, L"images/wall.png", 64, 64);
	loadimage(&blankImg, L"images/blank.png", 64, 64);

	for (int i = 0; i < 8;i++) {
		for (int j = 0; j < 8;j++) {
			putimage(64*j, 64*i, mapload(map[i][j]));
		}
	}
	FlushBatchDraw();
	EndBatchDraw();
}



//�ж��Ƿ�����ƶ�
void direction(int i, int j, int direction)
{
	struct Point point1;
	struct Point point2;
	struct Point point3;

	point1.x = i;
	point1.y = j;

	switch (direction) {
	case DIRE_TOP:
		point2.x = i - 1;
		point2.y = j;
		point3.x = i - 2;
		point3.y = j;
		//map[i - 1][j] = MAP_PERSON;
		//map[i][j] -= MAP_PERSON;
		break;
	case DIRE_BOTTOM:
		point2.x = i + 1;
		point2.y = j;
		point3.x = i + 2;
		point3.y = j;
		break;
	case DIRE_LEFT:
		point2.x = i;
		point2.y = j - 1;
		point3.x = i;
		point3.y = j - 2;
		break;
	case DIRE_RIGHT:
		point2.x = i;
		point2.y = j + 1;
		point3.x = i;
		point3.y = j + 2;
		break;
	}

	if (map[point2.x][point2.y] == MAP_BLANK || 
		map[point2.x][point2.y] == MAP_DEST || 
		map[point2.x][point2.y] == MAP_PERSON) {

		//ֱ���ƶ�������Ҫ�жϵ������������

		map[point2.x][point2.y] += MAP_PERSON;
		map[point1.x][point1.y] -= MAP_PERSON;

	}
	else if (map[point2.x][point2.y] == MAP_BOX || map[point2.x][point2.y] == MAP_BOX_DEST) {
		//�����ƶ������
		if (map[point3.x][point3.y] == MAP_BOX || 
			map[point3.x][point3.y] == MAP_BOX_DEST || 
			map[point3.x][point3.y] == MAP_WALL) {
			//�Ʋ���
		}
		else {

			if (map[point2.x][point2.y] == MAP_BOX_DEST) { //��2������Ŀ�ĵ�

				//�ƶ�����
				if (map[point3.x][point3.y] == MAP_DEST) {  //��3������Ŀ��
					map[point1.x][point1.y] -= MAP_PERSON;
					map[point2.x][point2.y] = MAP_PERSON_DEST;
					map[point3.x][point3.y] = MAP_BOX_DEST;
				}
				else if (map[point3.x][point3.y] == MAP_BLANK) {  //��3�����ǿհ�
					map[point1.x][point1.y] -= MAP_PERSON;
					map[point2.x][point2.y] = MAP_PERSON_DEST;
					map[point3.x][point3.y] = MAP_BOX;
				}
			}
			else if (map[point2.x][point2.y] == MAP_BOX) {
				map[point1.x][point1.y] -= MAP_PERSON;
				map[point2.x][point2.y] = MAP_PERSON;
				map[point3.x][point3.y] += MAP_BOX;
			}
		}

	}
	

}

void move()
{
	//�ı������е�����
	////i��j��ʾ�˵�λ��
	int i = 0;
	int j = 0;

	while (1) {
		drawMap();
		char ch = _getch();

		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (MAP_PERSON == map[i][j]) {
					break;
				}
			}
			if (MAP_PERSON == map[i][j]) {
				break;
			}
		}

		if (ch == 'W' || ch == 'w') {
			//������
			direction(i, j, DIRE_TOP);
		} else if (ch == 'S' || ch == 's') {
			direction(i, j, DIRE_BOTTOM);
			//������
			//map[i + 1][j] = MAP_PERSON;
			//map[i][j] -= MAP_PERSON;
		}
		else if (ch == 'A' || ch == 'a') {
			direction(i, j, DIRE_LEFT);
			//������
			//map[i][j-1] = MAP_PERSON;
			//map[i][j] -= MAP_PERSON;
		}
		else if (ch == 'D' || ch == 'd') {
			direction(i, j, DIRE_RIGHT);
			//������
			//map[i][j + 1] = MAP_PERSON;
			//map[i][j] -= MAP_PERSON;
		}
	}

}

int main()
{
	//easyX ��ʼ����ͼ����
	initgraph(64 * 8, 64 * 8);

	move();

	getchar(); //�������룬��Ҫ���س��������
	closegraph();

	return 0;
}