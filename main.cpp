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
			cout << "please input username: " << username << endl;
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
			//��account.txt�ж�ȡ�û���������
			file >> nam_tmp >> pwd_tmp;

			//���Ƿ���һ�µ��û���������
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
	string menu[] = {	//����һ���ַ������鱣��˵�ѡ��
		"1.Web 404 Attack",
		"2.Web Tamper Attack",
		"3.Web Restore",
		"4.Attack Record",
		"5.Add Account",
		"6.Switch Account",
		"7.Exit"
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
	out.open(FILE_NAME, ios::app); //Ϊд�����ļ�,��ʼλ���趨Ϊ�ļ�β
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

	//д���û���������
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