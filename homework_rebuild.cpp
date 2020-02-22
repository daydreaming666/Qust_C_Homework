#include<cstdio>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
#include<cstring>

const int SCREENWIDTH = 105, SCREENHEIGHT = 300;
const int COURSEIDLENGTH = 10; // 课程号长度

struct Course {				// 存储课程信息
	char courseID[10];		// 课程号
	char courseName[32];	// 课程名称
	int semester;			// 课程学期
	double fullCredit;		// 该课程满学分
};

struct Reward {		// 记录奖惩信息
    bool type;		// 类型 奖励：true 惩罚：false
	char info[64];	// 奖惩信息内容，最多32中文字符
	int score;		// 加分/减分

	Reward(bool type, char* info, int score) { //构造函数（c++乱入）
	    this->type = type;
	    strcpy(this->info, info);
	    this->score = score;
    }
};

struct Student {
	char name[10];					// 姓名
	char studentID[10]; 			// 学号
	char dormitoryID[10];			// 宿舍号
	char sex; 						// 性别 男：'m' 女：'f' 未知：'n'
	int age;						// 年龄
	Course (*course)[20]; 			// 课程
	int courseNum;					// 课程数量
	double grade[20];				// 课程得分
	double credit[20];				// 课程学分
	bool isMakeup;					// 重修标记
	Reward (*reward)[20]; 			// 奖惩信息
	int rewardNum;					// 奖惩数量
};

int courseNumber; //记录已输入课程数量
char screenBuffer[SCREENHEIGHT][SCREENWIDTH]; // 输出缓存区，用于输出前更改显示内容
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

// 输出操作完成并等待按键操作
inline void successPrompt(){
    printf("操作完成!\n");
    system("pause");
}

// 清空输入缓冲区并清屏准备输入
inline void clearAll(){
    fflush(stdin);
    system("cls");
}

// 检查字符串中的数字
inline int numberError(char *n, int len) {
    if (strlen(n) != len) return 1;
    for (int i = 0; i < 10; i++) if (!(n[i] >= '0' && n[i] <= '9')) return 1;
    return 0;
}

// 输入课程信息
int inputCourse(void) {
	clearAll();
	printf("请输入添加课程的数量\n");
	int num;
	scanf("%d",&num);
	clearAll();
	for (int i = courseNumber; i <= num + courseNumber; i++) {
		printf("-----------------------------------------------------------------------------------------------\n");
        printf("|                                         建立成绩单                                          |\n");
        printf("|                                       --------------                                        |\n");
		printf("请输入课程%d的课程号\n",i + 1);
		scanf("%s",cou[i].courseID);
        while (numberError(cou[i].courseID, COURSEIDLENGTH)){
            fflush(stdin);
            printf("输入错误，请重新输入\n");
            scanf("%s",cou[i].courseID);
        }
		char sign;
		do {
			printf("请输入课程名称");
            scanf("%s",cou[i].courseName);
            printf("名称为 %s ,确认(Y),重输(N)\n",cou[i].courseName);
            fflush(stdin);
            sign=getchar();
        }while (sign!='y'&&sign!='Y');
		printf("请输入课程学期\n");
		scanf("%d",&cou[i].semester);
		clearAll();
	}
}

// 此函数用于测试按键
void keyTest(void) {
	while (1) {
		int c = getch();
		printf("%d\n",c);
	}
	return;
}

// 文件菜单操作
void fileMenu(void) {
	int p = selectMenu(5, createFileMenu);
	switch (p){
		case 0: mainMenu();break;
	}
	return;
}

// 编辑菜单操作
void editMenu(void) {
	int p = selectMenu(7, createEditMenu);
	switch (p){
		case 0: mainMenu();		break;
		case 2: inputCourse();	break;
	}
	return;
}

// 主菜单操作
void mainMenu(void) {
	int p = selectMenu(5, createMainMenu);
	switch (p) {
		case 1: fileMenu(); break;
		case 2: editMenu(); break;
		case 0: exitSystem();
	}
	return;
}

// 将文件菜单内容放入输出缓存
void createFileMenu(void) {
	strcpy(screenBuffer[0] ,"-----------------------------------------------------------------------------------------------\n");
	strcpy(screenBuffer[1] ,"|                                          文件菜单                                           |\n");
	strcpy(screenBuffer[2] ,"|                                       --------------                                        |\n");
	strcpy(screenBuffer[3] ,"|                                       1. 建立新文件                                         |\n");
	strcpy(screenBuffer[4] ,"|                                       2. 导入数据                                           |\n");
	strcpy(screenBuffer[5] ,"|                                       3. 导出数据                                           |\n");
	strcpy(screenBuffer[6] ,"|                                       4. 导出txt                                            |\n");
	strcpy(screenBuffer[7] ,"|                                       0. 返回主菜单                                         |\n");
	strcpy(screenBuffer[8] ,"|                                                                                             |\n");
	strcpy(screenBuffer[9] ,"|                                                                                             |\n");
	strcpy(screenBuffer[10],"-----------------------------------------------------------------------------------------------\n");
}

// 将编辑菜单内容放入输出缓存
void createEditMenu(void) {
	strcpy(screenBuffer[0] ,"-----------------------------------------------------------------------------------------------\n");
	strcpy(screenBuffer[1] ,"|                                          编辑菜单                                           |\n");
	strcpy(screenBuffer[2] ,"|                                    --------------------                                     |\n");
	strcpy(screenBuffer[3] ,"|                                     1. 添加学生信息                                         |\n");
	strcpy(screenBuffer[4] ,"|                                     2. 添加课程信息                                         |\n");
	strcpy(screenBuffer[5] ,"|                                     3. 删除学生信息                                         |\n");
	strcpy(screenBuffer[6] ,"|                                     4. 删除课程信息                                         |\n");
	strcpy(screenBuffer[7] ,"|                                     5. 编辑学生信息                                         |\n");
	strcpy(screenBuffer[8] ,"|                                     6. 编辑课程信息                                         |\n");
	strcpy(screenBuffer[9] ,"|                                     0. 返回主菜单                                           |\n");
	strcpy(screenBuffer[10],"-----------------------------------------------------------------------------------------------\n");
}

// 进入欢迎页面
void welcomePage(void) {
	printf("按任意键继续...");
	getch();
	mainMenu();
}

// 退出系统
void exitSystem(void) {
	exit(0);
}

// 把输入提示放入输入缓存页面的最后一行
void putHint(int page) {
	strcpy(screenBuffer[page * 30 - 1],"                   ↑ ↓ 键选择，空格确认，esc键退出程序(数据将丢失)");
}


// 将主菜单内容放入输出缓存
void createMainMenu(void) { // 宽度为 95
	strcpy(screenBuffer[0] ,"-----------------------------------------------------------------------------------------------\n");
	strcpy(screenBuffer[1] ,"|                                           主菜单                                            |\n");
	strcpy(screenBuffer[2] ,"|                                       --------------                                        |\n");
	strcpy(screenBuffer[3] ,"|                                          1. 文件                                            |\n");
	strcpy(screenBuffer[4] ,"|                                          2. 编辑                                            |\n");
	strcpy(screenBuffer[5] ,"|                                          3. 查询                                            |\n");
	strcpy(screenBuffer[6] ,"|                                          4. 计算                                            |\n");
	strcpy(screenBuffer[7] ,"|                                          0. 退出                                            |\n");
	strcpy(screenBuffer[8] ,"|                                                                                             |\n");
	strcpy(screenBuffer[9] ,"|                                                                                             |\n");
	strcpy(screenBuffer[10],"-----------------------------------------------------------------------------------------------\n");
	return;
};



// 将第 page 页的内容输出
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

// 菜单内容选择 (菜单长度,创建菜单函数)
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
			if (c2 == 72) { // ↑ 按键操作
				if (p > 3) {
					screenBuffer[p][35] = ' ';
					p--;
					screenBuffer[p][35] = '>';
					putScreenBuffer(1);
				}
			}
			if (c2 == 80) { // ↓ 按键操作
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
