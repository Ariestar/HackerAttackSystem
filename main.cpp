//date:2019-8-22
//todo: ���ر���
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "hacker.h"

#define WAIT_TIME 600
#define WIDTH  50
#define HEIGHT 20
#define MAX_STR 256

using namespace std;

void init(void)
{
	//set window size
	char cmd[128];
	sprintf_s(cmd, sizeof(cmd), "mode con cols=%d lines=%d", WIDTH, HEIGHT);
	system(cmd);
}

void printInMid(string msg)
{
	int spaceCount = (WIDTH - msg.length()) / 2;
	for (int j = 0; j < spaceCount; j++)
	{
		cout << " ";
	}
	cout << msg;
}

void inputPwd(char account[], int size_a, char password[], int size_p)
{
	int i = 0;
	char ret;

	while (1)
	{
		ret = _getch();
		if (ret != '\r' && ret != '\b') //������س���ʱ,getch()����'\r'
		{
			password[i] = ret;
			cout << "*";
			i++; //�����±������һλ
		}
		else if (ret == '\b') //������˸��,�ص�ǰһλ����
		{
			//��������ʾԭ����������
			system("cls");
			cout << "please input account: " << account << endl;
			cout << "please input password: ";
			for (int j = 0; j < i - 1; j++)
			{
				cout << "*";
			}

			if (i > 0) i--; //�����±�ص�ǰһλ
		}
		else //����ǻس�,��������
		{
			password[i] = '\0';
			cout << endl;
			break;
		}
	}
}

void login(void)
{
	char account[MAX_STR]; //char name;
	char password[MAX_STR]; //char password;

	while (1)
	{
		cout << "please input account: ";
		cin >> account;

		cout << "please input password: ";
		inputPwd(account, sizeof(account), password, sizeof(password));

		//Authority Judgment
		if (!strcmp(account, "54hk") && !strcmp(password, "123456"))
		{
			cout << "Success...";
			Sleep(WAIT_TIME);
			break;
		}
		else
		{
			cout << "Wrong!" << endl;
			Sleep(WAIT_TIME);
			system("cls");
			continue;
		}
	}
}

void menuShow(void)
{
	string menu[] = {	//����һ���ַ������鱣��˵�ѡ��
		"1.Web 404 Attack",
		"2.Web Tamper Attack",
		"3.Web Restore",
		"4.Attack Record",
		"5.Exit",
	};

	//����ո���
	//�ַ���������ÿ���ַ�����ռ�ڴ���ͬ,���������ڴ����ÿ���ַ����ڴ�,�õ��ַ����ĸ���
	int menuCount = sizeof(menu) / sizeof(menu[0]);  // �����ַ�������
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

	//���������
	int lineCount = (HEIGHT - menuCount - 2) / 3;

	system("cls");

	for (int i = 0; i < lineCount; i++)
	{
		cout << endl;
	}

	//��ӡ�˵�
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
	printInMid("---Web Tamper Attack---");

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
	printInMid("---Attack Restore---");

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
	printInMid("---Attack Record---");

	cout << endl << "input web ID: ";
	scanf_s("%s", id, sizeof(id));

	hk_record(id, response);

	string retStr = UTF8ToGBK(response);
	cout << retStr << endl;

	system("pause");
}

bool choiceAndWork(void)
{
	//���ѡ����
	int n;
	menuShow();
	printInMid("Please choose: ");
	cin >> n;
	if (cin.fail())
	{
		cin.clear(); // ���������
		cin.sync();  // ������뻺����
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
			return 0;

	return 0;
}