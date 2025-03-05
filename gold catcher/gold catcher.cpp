#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>  
#include <graphics.h>
#include <process.h>
#include "gold catcher.h"
#include <string>
#include <functional>
#include <vector>
#include <iostream>


typedef struct {
	char name[10];
	int point;
	char password[10];
}player;
player account[10];

void setTextStyle(int x, int y) {
	LOGFONT f;          //这个结构体定义了字体的属性
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = x;						// 设置字体高度
	f.lfWeight = y;
	_tcscpy_s(f.lfFaceName, _T("微软黑体"));		// 设置字体
	settextstyle(&f);						// 设置字体样式
	setbkmode(TRANSPARENT);// 去掉文字背景
}


bool inArea(int mx, int my, int x, int y, int w, int h)
{
	if (mx > x && mx<x + w && my>y && my < y + h)
	{
		return true;
	}return false;
}

void button(int x, int y, int w, int h, const char* text)
{
	fillroundrect(x, y, x + w, y + h, 5, 5);
	int hSpace = (w - textwidth(text)) / 2;
	int vSpace = (h - textheight(text)) / 2;
	settextcolor(BLACK);
	outtextxy(x + hSpace, y + vSpace, text);
}


int reading1(player account[])
{
	FILE* fp;
	if ((fp = fopen("../player account.txt", "r")) == NULL) {
		printf("不能打开文件");
		return -1;
	}
	int numplayer = 0;
	int i = 0;
	while (!feof(fp) && numplayer < 10)
	{
		
		fscanf(fp, "%s\n%s\n", account[i].name,&account[i].password);
		numplayer++;
		i++;
	}
	fclose(fp);
	return numplayer;
}

void writeUser(const player* player) {
	FILE* fp;
	if ((fp = fopen("../player account.txt", "a")) == NULL) {
		printf("不能打开文件");
		return;
	}
	fprintf(fp, "%s\n%s\n", player->name, player->password);
	fclose(fp);
}

int isPlayerNmaeExists(player account[], char name[]) {
	int numplayer = reading1(account);
	for (int i = 0; i < numplayer; i++)
	{
		if (strcmp(name, account[i].name) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int validateLogin(player account[], const char* name, const char* password) {
	int numplayer = reading1(account);
	for (int i = 0; i < numplayer; i++) {
		if (strcmp(account[i].name, name) == 0 && strcmp(account[i].password, password) == 0)
			return 1;
	}
	return 0;
}

void Register()
{
	cleardevice();
	MOUSEMSG msg = GetMouseMsg();
	IMAGE picture;
	loadimage(&picture, "../images/menu.jpg", 1024, 640);
	putimage(0, 0, &picture);
	FILE* fp;
	char tempChar;
	char username[10] = { 0 };
	char password[10] = { 0 };
	int activeInput = 0;
	int counter = 0;
	settextcolor(WHITE);
	setfillcolor(BROWN);
	button(200, 50, 600, 400, "");
	setfillcolor(WHITE);
	button(380, 293, 200, 50, "");
	button(380, 193, 200, 50, ""); 
	button(700, 300, 150, 50, "确定");
	outtextxy(300, 200, "账号：");
	outtextxy(300, 300, "密码：");
	int loggedIn = 0;
	int ifNameExisted = 0;
	int error = 0;
	int userCount = reading1(account);
	while (true)
	{
		if (MouseHit()) {
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (msg.x > 380 && msg.x < 580 && msg.y > 193 && msg.y < 243) {
					activeInput = 1;
				}
				else if (msg.x > 380 && msg.x < 580 && msg.y > 293 && msg.y < 343)
					activeInput = 2;
				else if (msg.x > 700 && msg.x < 850 && msg.y > 300 && msg.y < 350)
				{
					if (strlen(username) == 0 || strlen(password) == 0) {
						outtextxy(600, 50, "用户名和密码不能为空");
					}
					else if (isPlayerNmaeExists(account, username)) {
						outtextxy(600, 50, "用户名已存在");
						ifNameExisted = 1;
					}
					else if(ifNameExisted == 0){
						player newcount;
						strcpy(newcount.name, username);
						strcpy(newcount.password, password);
						writeUser(&newcount);
						account[userCount] = newcount;
						userCount++;
						outtextxy(600, 50, "注册成功！");
						Sleep(100);
						system("pause");
					}

				}
				else
					activeInput = 0;
			}
		}

		if (_kbhit())
		{
			tempChar = _getch();

			if (activeInput != 0) {
				if (tempChar == 8)   // 退格键处理
				{
					if (activeInput == 1 && strlen(username) > 0) {
						username[strlen(username) - 1] = '\0';
						setfillcolor(WHITE);
						fillrectangle(380, 193, 580, 243);
						settextcolor(BLACK);
						outtextxy(400, 200, username);
					}
					else if (activeInput == 2 && strlen(password) > 0) {
						password[strlen(password) - 1] = '\0';
						setfillcolor(WHITE);
						fillrectangle(380, 293, 580, 343);
						settextcolor(BLACK);
						char asterisks[10] = { 0 };
						for (int i = 0; i < strlen(password); i++)
							asterisks[i] = '*';
						outtextxy(400, 300, asterisks);
					}
				}
				if ((tempChar >= '0' && tempChar <= '9') || (tempChar >= 'A' && tempChar <= 'Z') || (tempChar >= 'a' && tempChar <= 'z'))
				{
					if (activeInput == 1 && strlen(username) < 9) {
						username[strlen(username)] = tempChar;
						setfillcolor(WHITE);
						fillrectangle(380, 193, 580, 243);
						settextcolor(BLACK);
						outtextxy(400, 200, username);
					}

					else if (activeInput == 2 && strlen(password) < 9) {
						password[strlen(password)] = tempChar;
						setfillcolor(WHITE);
						fillrectangle(380, 293, 580, 343);
						char asterisks[10] = { 0 };
						for (int i = 0; i < strlen(password); i++)
							asterisks[i] = '*';
						outtextxy(400, 300, asterisks);
					}

				}
			}
			
		}
		Sleep(10);
	}
		
	}
	void login() {
		cleardevice();
		MOUSEMSG msg = GetMouseMsg();
		IMAGE picture;
		loadimage(&picture, "../images/menu.jpg", 1024, 640);
		putimage(0, 0, &picture);
		char tempChar;
		char username[10] = { 0 };
		char password[10] = { 0 };
		int activeInput = 0; 
		int counter = 0;
		settextcolor(WHITE);
		setfillcolor(BROWN);
		button(200, 50, 600, 400, "");
		setfillcolor(WHITE);
		button(380, 293, 200, 50, "");
		button(380, 193, 200, 50, "");
		button(700, 300, 150, 50, "确定");
		outtextxy(300, 200, "账号：");
		outtextxy(300, 300, "密码：");
		int loggedIn = 0;
		int userCount = reading1(account);

		while (true) {
			if (MouseHit()) {
				msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN) {
					if (msg.x > 380 && msg.x < 580 && msg.y > 193 && msg.y < 243) {
						activeInput = 1; // 用户名输入框
					}
					else if (msg.x > 380 && msg.x < 580 && msg.y > 293 && msg.y < 343) {
						activeInput = 2; // 密码输入框
					}
					else if (msg.x > 700 && msg.x < 850 && msg.y > 300 && msg.y < 350) {
						// 登录按钮
						if (validateLogin(account, username, password)) {
							outtextxy(600, 50, "登录成功！");
							Sleep(1000);
							system("pause");
						}
						else {
							outtextxy(600, 50, "用户名或密码错误！");
						}
					}
					else
						activeInput = 0;
				}
			}
			if (_kbhit()) {
				tempChar = _getch();
				if (tempChar == 8) { 
					if (activeInput == 1 && strlen(username) > 0) {
						username[strlen(username) - 1] = '\0';
						setfillcolor(WHITE);
						fillroundrect(380, 193, 580, 243,5,5);
						settextcolor(BLACK);
						outtextxy(400, 200, username);
					}
					else if (activeInput == 2 && strlen(password) > 0) {
						password[strlen(password) - 1] = '\0';
						setfillcolor(WHITE);
						fillroundrect(380, 293, 580, 343,5,5);
						settextcolor(BLACK);
						char asterisks[10] = { 0 };
						for (int i = 0; i < strlen(password); i++)
							asterisks[i] = '*';
						outtextxy(400, 300, asterisks);
					}
				}
				else if ((tempChar >= '0' && tempChar <= '9') || (tempChar >= 'A' && tempChar <= 'Z') || (tempChar >= 'a' && tempChar <= 'z')) { // 可打印字符
					if (activeInput == 1 && strlen(username) < 9) {
						username[strlen(username)] = tempChar;
						setfillcolor(WHITE);
						fillroundrect(380, 193, 580, 243,5,5);
						settextcolor(BLACK);
						outtextxy(400, 200, username);
					}
					else if (activeInput == 2 && strlen(password) < 9) {
						password[strlen(password)] = tempChar;
						setfillcolor(WHITE);
						fillroundrect(380, 293, 580, 343,5,5);
						char asterisks[10] = { 0 };
						for (int i = 0; i < strlen(password); i++)
							asterisks[i] = '*';
						outtextxy(400, 300, asterisks);
					}
					}
				}
			}

			Sleep(10);
		}
	
	

void menu() {
	int page = 0;
	MOUSEMSG m = GetMouseMsg();
	button(400, 300, 200, 50, "登录");
	button(400, 200, 200, 50, "注册");

	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && inArea(m.x, m.y, 400, 200, 200, 50)) {
			page = 1;
			break;
		}
		else if (m.uMsg == WM_LBUTTONDOWN && inArea(m.x, m.y, 400, 300, 200, 50)) {
			page = 2;
			break;
		}
	
	}
	if (page == 1)
		Register();
	if (page == 2)
		login();
	

}
 
int _tmain(int argc, _TCHAR* argv[]) {
	initgraph(1024, 640);
	setbkcolor(WHITE);
	FILE* fp;
	IMAGE picture;
	loadimage(&picture, "../images/menu.jpg", 1024, 640);
	putimage(0, 0 ,& picture);
	setTextStyle(30, 0);
	int count = reading1(account);

	menu();
	
}


