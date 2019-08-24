//date:2019-8-22
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include "hacker.h"

#define WAIT_TIME 600
#define WIDTH  50
#define HEIGHT 20
#define MAX_STR 256
#define FILE_NAME "accounts.txt"

using namespace std;

int main(void);

void printInMid(string msg)
{
	int spaceCount = (WIDTH - msg.length()) / 2;
	for (int j = 0; j < spaceCount; j++)
	{
		cout << " ";
	}
	cout << msg;
}

void init(void)
{
	//set window size
	char cmd[128];
	sprintf_s(cmd, sizeof(cmd), "mode con cols=%d lines=%d", WIDTH, HEIGHT);
	system(cmd);
}

void inputPwd(char username[], int size_a, char password[], int size_p)
{
	int i = 0;
	char ret;

	while (1)
	{
		ret = _getch();
		if (ret != '\r' && ret != '\b') //当输入回车符时,getch()返回'\r'
		{
			password[i] = ret;
			cout << "*";
			i++; //密码下标进到下一位
		}
		else if (ret == '\b') //如果是退格符,回到前一位输入
		{
			//清屏后显示原来的输入结果
			system("cls");
			cout << "please input username: " << username << endl;
			cout << "please input password: ";
			for (int j = 0; j < i - 1; j++)
			{
				cout << "*";
			}

			if (i > 0) i--; //密码下标回到前一位
		}
		else //如果是回车,结束输入
		{
			password[i] = '\0';
			cout << endl;
			break;
		}
	}
}

void login(void)
{
	char username[MAX_STR]; //char name;
	char password[MAX_STR]; //char password;
	string nam_tmp;
	string pwd_tmp;

	fstream file;
	file.open(FILE_NAME);
	if (file.fail())
	{
		cout << "Fail to open the file...";
		Sleep(WAIT_TIME);
		exit(1);
	}

	while (1)
	{
		printInMid("---Sign In---");
		cout << endl;

		cout << "please input username: ";
		cin >> username;

		cout << "please input password: ";
		inputPwd(username, sizeof(username), password, sizeof(password));

		while (!file.fail())
		{
			//从account.txt中读取用户名和密码
			file >> nam_tmp >> pwd_tmp;

			//看是否有一致的用户名和密码
			if (!strcmp(username, nam_tmp.c_str()) && !strcmp(password, pwd_tmp.c_str()))
			{
				cout << "Success...";
				Sleep(WAIT_TIME);
				file.close();
				return;
			}
		}
		cout << "Wrong!" << endl;
		Sleep(WAIT_TIME);
		system("cls");
	}
}

void menuShow(void)
{
	string menu[] = {	//定义一个字符串数组保存菜单选项
		"1.Web 404 Attack",
		"2.Web Tamper Attack",
		"3.Web Restore",
		"4.Attack Record",
		"5.Add Account",
		"6.Switch Account",
		"7.Exit"
	};

	//计算空格数
	//字符串数组中每个字符串所占内存相同,用数组总内存除以每个字符串内存,得到字符串的个数
	int menuCount = sizeof(menu) / sizeof(menu[0]);  // 计算字符串个数
	int maxLeng = 0;
	int spaceCount;
	for (int i = 0; i < menuCount; i++)
	{
		if (menu[i].length() > maxLeng)
		{
			maxLeng = menu[i].length();
		}
	}
	spaceCount = (WIDTH - maxLeng) / 2;

	//计算空行数
	int lineCount = (HEIGHT - menuCount - 2) / 3;

	system("cls");

	for (int i = 0; i < lineCount; i++)
	{
		cout << endl;
	}

	//打印菜单
	printInMid("--Hacker Attack System--");
	cout << endl;
	for (int i = 0; i < menuCount; i++)
	{
		for (int j = 0; j < spaceCount; j++)
		{
			cout << " ";
		}
		cout << menu[i] << endl;
	}
}

// 404 Attack
void Attack404(void)
{
	char id[MAX_STR];
	char response[MAXSIZE];

	system("cls");
	printInMid("---404 ATTACK---");

	cout << endl << "input web ID to attack: ";
	scanf_s("%s", id, sizeof(id));

	// attack
	cout << "404 Attacking..." << endl;
	hk_404(id, response);

	string retStr = UTF8ToGBK(response);
	cout << retStr << endl;

	Sleep(WAIT_TIME);
}

void TamperAttack()
{
	char id[MAX_STR];
	string tamperText;
	char response[MAXSIZE];

	system("cls");
	printInMid("---WEB TAMPER ATTACK---");

	cout << endl << "input web ID to attack: ";
	scanf_s("%s", id, sizeof(id));
	cout << "input message to tamper: ";
	cin >> tamperText;

	//attack
	cout << "Tampering Attacking..." << endl;
	GBKToUTF8(tamperText);
	hk_tamper(id, (char*)tamperText.c_str(), response);

	string retStr = UTF8ToGBK(response);
	cout << retStr << endl;

	Sleep(WAIT_TIME);
}

void attackRestore(void)
{
	char id[MAX_STR];
	char response[MAXSIZE];

	system("cls");
	printInMid("---ATTACK RESTORE---");

	cout << endl << "input web ID to restore: ";
	scanf_s("%s", id, sizeof(id));

	cout << "Restoring..." << endl;
	hk_restore(id, response);

	string retStr = UTF8ToGBK(response);
	cout << retStr << endl;

	Sleep(WAIT_TIME);
}

void attackRecord(void)
{
	char id[MAX_STR];
	char response[MAXSIZE];

	system("cls");
	printInMid("---ATTACK RECORD---");

	cout << endl << "input web ID: ";
	scanf_s("%s", id, sizeof(id));

	hk_record(id, response);

	string retStr = UTF8ToGBK(response);
	cout << retStr << endl;

	system("pause");
}

void addAcct()
{
	string username;
	string password;

	fstream out;
	out.open(FILE_NAME, ios::app); //为写而打开文件,起始位置设定为文件尾
	if (out.fail())
	{
		cout << endl << "Fail to open the file...";
		Sleep(WAIT_TIME);
		exit(1);
	}

	system("cls");
	printInMid("---ADD ACCOUNT---");
	cout << endl << "Input username: ";
	cin >> username;
	cout << "Input password: ";
	cin >> password;

	//写入用户名和密码
	out << username << "\t\t\t" << password << endl;
	if (!out.fail())
	{
		cout << "Added successfully.";
		Sleep(WAIT_TIME);
	}
	else cout << "Error.";

	out.close();
}

bool choiceAndWork(void)
{
	//多次选择功能
	int n;
	menuShow();
	printInMid("Please choose: ");
	cin >> n;
	if (cin.fail())
	{
		cin.clear(); // 清除错误标记
		cin.sync();  // 清除输入缓冲区
		cout << "Input failed.";
		Sleep(WAIT_TIME);
	}
	else
	{
		switch (n)
		{
		case 1:
			Attack404();
			break;
		case 2:
			TamperAttack();
			break;
		case 3:
			attackRestore();
			break;
		case 4:
			attackRecord();
			break;
		case 5:
			addAcct();
			break;
		case 6: //switch account
			main();
			break;
		case 7:
			return false; // exit
			break;
		default:
			cout << "Invalid input.";
			Sleep(WAIT_TIME);
			break;
		}
	}
	
	return true;
}

int main(void)
{
	init();
	login();
	while (1)
		if (!choiceAndWork())
			exit(0);

	exit(0);
}