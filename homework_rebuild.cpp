#include<cstdio>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
#include<cstring>

const int SCREENWIDTH = 105, SCREENHEIGHT = 300;

char screenBuffer[SCREENHEIGHT][SCREENWIDTH]; // 输出缓存区，用于二次更改显示内容

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

// 此函数用于测试按键
void keyTest(void) {
	while (1){
		int c = getch();
		printf("%d\n",c);
	}
	return ;
}

// 文件菜单操作
void fileMenu(void) {
	int p = selectMenu(5, createFileMenu);
	switch (p){
		case 0: mainMenu();break;
	}
	return;
}

// 主菜单操作
void mainMenu(void) {
	int p = selectMenu(5, createMainMenu);
	switch (p) {
		case 1: fileMenu(); break;
	}
	return;
}

// 将文件菜单内容放入输出缓存
void createFileMenu(void) {
	strcpy(screenBuffer[0] ,"-----------------------------------------------------------------------------------------------\n");
	strcpy(screenBuffer[1] ,"|                                          文件菜单                                           |\n");
	strcpy(screenBuffer[2] ,"|                                       --------------                                        |\n");
	strcpy(screenBuffer[3] ,"|                                        1. 建立新文件                                        |\n");
	strcpy(screenBuffer[4] ,"|                                        2. 导入数据                                          |\n");
	strcpy(screenBuffer[5] ,"|                                        3. 导出数据                                          |\n");
	strcpy(screenBuffer[6] ,"|                                        4. 导出txt                                           |\n");
	strcpy(screenBuffer[7] ,"|                                        0. 返回主菜单                                        |\n");
	strcpy(screenBuffer[8] ,"|                                                                                             |\n");
	strcpy(screenBuffer[9] ,"|                                                                                             |\n");
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
	}
	return;
}

// 菜单内容选择 (菜单长度,创建菜单函数)
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
			if (c2 == 72) { // ↑ 按键操作
				if (p > 3) {
					screenBuffer[p][40] = ' ';
					p--;
					screenBuffer[p][40] = '>';
					putScreenBuffer(1);
				}
			}
			if (c2 == 80) { // ↓ 按键操作
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
