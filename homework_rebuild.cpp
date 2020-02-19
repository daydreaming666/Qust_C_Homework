#include<cstdio>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
#include<cstring>

const int SCREENWIDTH = 105, SCREENHEIGHT = 300;

char screenBuffer[SCREENHEIGHT][SCREENWIDTH]; // ��������������ڶ��θ�����ʾ����

void putScreenBuffer(int page);
void createMainMenu(void);
int selectMenu(int menuLength ,void (*createMenu)(void));
void putHint(int page);
void exitSystem(void);
void welcomePage(void);
void createFileMenu(void);
void mainMenu(void);
void fileMenu(void);
void keyTest(void);

// �˺������ڲ��԰���
void keyTest(void) {
	while (1){
		int c = getch();
		printf("%d\n",c);
	}
	return ;
}

// �ļ��˵�����
void fileMenu(void) {
	int p = selectMenu(5, createFileMenu);
	switch (p){
		case 0: mainMenu();break;
	}
	return;
}

// ���˵�����
void mainMenu(void) {
	int p = selectMenu(5, createMainMenu);
	switch (p) {
		case 1: fileMenu(); break;
	}
	return;
}

// ���ļ��˵����ݷ����������
void createFileMenu(void) {
	strcpy(screenBuffer[0] ,"-----------------------------------------------------------------------------------------------\n");
	strcpy(screenBuffer[1] ,"|                                          �ļ��˵�                                           |\n");
	strcpy(screenBuffer[2] ,"|                                       --------------                                        |\n");
	strcpy(screenBuffer[3] ,"|                                        1. �������ļ�                                        |\n");
	strcpy(screenBuffer[4] ,"|                                        2. ��������                                          |\n");
	strcpy(screenBuffer[5] ,"|                                        3. ��������                                          |\n");
	strcpy(screenBuffer[6] ,"|                                        4. ����txt                                           |\n");
	strcpy(screenBuffer[7] ,"|                                        0. �������˵�                                        |\n");
	strcpy(screenBuffer[8] ,"|                                                                                             |\n");
	strcpy(screenBuffer[9] ,"|                                                                                             |\n");
	strcpy(screenBuffer[10],"-----------------------------------------------------------------------------------------------\n");
}

// ���뻶ӭҳ��
void welcomePage(void) {
	printf("�����������...");
	getch();
	mainMenu();
}

// �˳�ϵͳ
void exitSystem(void) {
	exit(0);
}

// ��������ʾ�������뻺��ҳ������һ��
void putHint(int page) {
	strcpy(screenBuffer[page * 30 - 1],"                   �� �� ��ѡ�񣬿ո�ȷ�ϣ�esc���˳�����(���ݽ���ʧ)");
}


// �����˵����ݷ����������
void createMainMenu(void) { // ���Ϊ 95
	strcpy(screenBuffer[0] ,"-----------------------------------------------------------------------------------------------\n");
	strcpy(screenBuffer[1] ,"|                                           ���˵�                                            |\n");
	strcpy(screenBuffer[2] ,"|                                       --------------                                        |\n");
	strcpy(screenBuffer[3] ,"|                                          1. �ļ�                                            |\n");
	strcpy(screenBuffer[4] ,"|                                          2. �༭                                            |\n");
	strcpy(screenBuffer[5] ,"|                                          3. ��ѯ                                            |\n");
	strcpy(screenBuffer[6] ,"|                                          4. ����                                            |\n");
	strcpy(screenBuffer[7] ,"|                                          0. �˳�                                            |\n");
	strcpy(screenBuffer[8] ,"|                                                                                             |\n");
	strcpy(screenBuffer[9] ,"|                                                                                             |\n");
	strcpy(screenBuffer[10],"-----------------------------------------------------------------------------------------------\n");
	return;
};



// ���� page ҳ���������
void putScreenBuffer(int page) {
	system("cls");
	putHint(page);
	for (int i = (page - 1) * 30; i < page + 30; i++) {
		printf(screenBuffer[i]);
	}
	return;
}

// �˵�����ѡ�� (�˵�����,�����˵�����)
int selectMenu(int menuLength,void (*createMenu)(void)) {
	createMenu();
	int p = 3;
	screenBuffer[p][40] = '>';
	putScreenBuffer(1);
	while (1) {
		int c1 = getch();
		switch (c1){
			case '1':
			case '2':
			case '3':
			case '4': p = c1 - 48; return p;
		}
		if (c1 == 224) {
			int c2 = getch();
			if (c2 == 72) { // �� ��������
				if (p > 3) {
					screenBuffer[p][40] = ' ';
					p--;
					screenBuffer[p][40] = '>';
					putScreenBuffer(1);
				}
			}
			if (c2 == 80) { // �� ��������
				if (p < 3 + menuLength - 1) {
					screenBuffer[p][40] = ' ';
					p++;
					screenBuffer[p][40] = '>';
					putScreenBuffer(1);
				}
			}
		}
		if (c1 == ' ') break;
		if (c1 == 27) exitSystem();
	}
	return p - 2;
}

int main(void) {
	system("color 0f");
	welcomePage();
//	keyTest();
	return 0;
}
