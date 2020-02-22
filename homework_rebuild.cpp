#include<cstdio>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
#include<cstring>

const int SCREENWIDTH = 105, SCREENHEIGHT = 300;
const int COURSEIDLENGTH = 10; // �γ̺ų���

struct Course {				// �洢�γ���Ϣ
	char courseID[10];		// �γ̺�
	char courseName[32];	// �γ�����
	int semester;			// �γ�ѧ��
	double fullCredit;		// �ÿγ���ѧ��
};

struct Reward {		// ��¼������Ϣ
    bool type;		// ���� ������true �ͷ���false
	char info[64];	// ������Ϣ���ݣ����32�����ַ�
	int score;		// �ӷ�/����

	Reward(bool type, char* info, int score) { //���캯����c++���룩
	    this->type = type;
	    strcpy(this->info, info);
	    this->score = score;
    }
};

struct Student {
	char name[10];					// ����
	char studentID[10]; 			// ѧ��
	char dormitoryID[10];			// �����
	char sex; 						// �Ա� �У�'m' Ů��'f' δ֪��'n'
	int age;						// ����
	Course (*course)[20]; 			// �γ�
	int courseNum;					// �γ�����
	double grade[20];				// �γ̵÷�
	double credit[20];				// �γ�ѧ��
	bool isMakeup;					// ���ޱ��
	Reward (*reward)[20]; 			// ������Ϣ
	int rewardNum;					// ��������
};

int courseNumber; //��¼������γ�����
char screenBuffer[SCREENHEIGHT][SCREENWIDTH]; // ������������������ǰ������ʾ����
Student stu[200];
Course cou[30];

void putScreenBuffer(int page);
void createMainMenu(void);
int selectMenu(int menuLength ,void (*createMenu)(void));
void putHint(int page);
void exitSystem(void);
void welcomePage(void);
void createFileMenu(void);
void createEditMenu(void);
void mainMenu(void);
void fileMenu(void);
void editMenu(void);
void keyTest(void);
int inputCourse(void);
int numberError(char*, int);
void clearAll();
void successPrompt();

// ���������ɲ��ȴ���������
inline void successPrompt(){
    printf("�������!\n");
    system("pause");
}

// ������뻺����������׼������
inline void clearAll(){
    fflush(stdin);
    system("cls");
}

// ����ַ����е�����
inline int numberError(char *n, int len) {
    if (strlen(n) != len) return 1;
    for (int i = 0; i < 10; i++) if (!(n[i] >= '0' && n[i] <= '9')) return 1;
    return 0;
}

// ����γ���Ϣ
int inputCourse(void) {
	clearAll();
	printf("��������ӿγ̵�����\n");
	int num;
	scanf("%d",&num);
	clearAll();
	for (int i = courseNumber; i <= num + courseNumber; i++) {
		printf("-----------------------------------------------------------------------------------------------\n");
        printf("|                                         �����ɼ���                                          |\n");
        printf("|                                       --------------                                        |\n");
		printf("������γ�%d�Ŀγ̺�\n",i + 1);
		scanf("%s",cou[i].courseID);
        while (numberError(cou[i].courseID, COURSEIDLENGTH)){
            fflush(stdin);
            printf("�����������������\n");
            scanf("%s",cou[i].courseID);
        }
		char sign;
		do {
			printf("������γ�����");
            scanf("%s",cou[i].courseName);
            printf("����Ϊ %s ,ȷ��(Y),����(N)\n",cou[i].courseName);
            fflush(stdin);
            sign=getchar();
        }while (sign!='y'&&sign!='Y');
		printf("������γ�ѧ��\n");
		scanf("%d",&cou[i].semester);
		clearAll();
	}
}

// �˺������ڲ��԰���
void keyTest(void) {
	while (1) {
		int c = getch();
		printf("%d\n",c);
	}
	return;
}

// �ļ��˵�����
void fileMenu(void) {
	int p = selectMenu(5, createFileMenu);
	switch (p){
		case 0: mainMenu();break;
	}
	return;
}

// �༭�˵�����
void editMenu(void) {
	int p = selectMenu(7, createEditMenu);
	switch (p){
		case 0: mainMenu();		break;
		case 2: inputCourse();	break;
	}
	return;
}

// ���˵�����
void mainMenu(void) {
	int p = selectMenu(5, createMainMenu);
	switch (p) {
		case 1: fileMenu(); break;
		case 2: editMenu(); break;
		case 0: exitSystem();
	}
	return;
}

// ���ļ��˵����ݷ����������
void createFileMenu(void) {
	strcpy(screenBuffer[0] ,"-----------------------------------------------------------------------------------------------\n");
	strcpy(screenBuffer[1] ,"|                                          �ļ��˵�                                           |\n");
	strcpy(screenBuffer[2] ,"|                                       --------------                                        |\n");
	strcpy(screenBuffer[3] ,"|                                       1. �������ļ�                                         |\n");
	strcpy(screenBuffer[4] ,"|                                       2. ��������                                           |\n");
	strcpy(screenBuffer[5] ,"|                                       3. ��������                                           |\n");
	strcpy(screenBuffer[6] ,"|                                       4. ����txt                                            |\n");
	strcpy(screenBuffer[7] ,"|                                       0. �������˵�                                         |\n");
	strcpy(screenBuffer[8] ,"|                                                                                             |\n");
	strcpy(screenBuffer[9] ,"|                                                                                             |\n");
	strcpy(screenBuffer[10],"-----------------------------------------------------------------------------------------------\n");
}

// ���༭�˵����ݷ����������
void createEditMenu(void) {
	strcpy(screenBuffer[0] ,"-----------------------------------------------------------------------------------------------\n");
	strcpy(screenBuffer[1] ,"|                                          �༭�˵�                                           |\n");
	strcpy(screenBuffer[2] ,"|                                    --------------------                                     |\n");
	strcpy(screenBuffer[3] ,"|                                     1. ���ѧ����Ϣ                                         |\n");
	strcpy(screenBuffer[4] ,"|                                     2. ��ӿγ���Ϣ                                         |\n");
	strcpy(screenBuffer[5] ,"|                                     3. ɾ��ѧ����Ϣ                                         |\n");
	strcpy(screenBuffer[6] ,"|                                     4. ɾ���γ���Ϣ                                         |\n");
	strcpy(screenBuffer[7] ,"|                                     5. �༭ѧ����Ϣ                                         |\n");
	strcpy(screenBuffer[8] ,"|                                     6. �༭�γ���Ϣ                                         |\n");
	strcpy(screenBuffer[9] ,"|                                     0. �������˵�                                           |\n");
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
/*		for (int j = 0; j <= SCREENWIDTH; j++) {
			putchar(screenBuffer[i][j]);
		}*/
	}
	return;
}

// �˵�����ѡ�� (�˵�����,�����˵�����)
int selectMenu(int menuLength,void (*createMenu)(void)) {
	createMenu();
	int p = 3;
	screenBuffer[p][35] = '>';
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
					screenBuffer[p][35] = ' ';
					p--;
					screenBuffer[p][35] = '>';
					putScreenBuffer(1);
				}
			}
			if (c2 == 80) { // �� ��������
				if (p < 3 + menuLength - 1) {
					screenBuffer[p][35] = ' ';
					p++;
					screenBuffer[p][35] = '>';
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
