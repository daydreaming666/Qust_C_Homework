#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

struct student{
    char name[20];
    char studentNumber[15];
    double score[20];
    double average;
    double grade;
    double compositeScore;
};

const char elementName[20][50]={"软件技术导论","C语言程序设计","高等数学",
                                "大学体育","大学英语","近现代史","辅导员评分","班级同学评分",
                                "作者\x64\x61\x79\x64\x72\x65\x61\x6D\x69\x6E\x67\n"};

const double courseGrade[20]={2,3.5,5,2,3,2};
const double scholarshipRate[5]={0.03,0.07,0.2};
const int courseNum=8;
const int allNum=35;
const double fullGrade=17.5;
int num;

student stu[50];
student averageScore;


/*void windowSet(int w,int h){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = {w,h};
	SetConsoleScreenBufferSize(hOut,size);
	SMALL_RECT rc = {1,1,w,h};
	SetConsoleWindowInfo(hOut,true,&rc);
	return;
}
*/
void getMainChoice();
void output(int);


inline void clearAll(){
    fflush(stdin);
    system("cls");
}

	inline void successPrompt(){
		printf("操作完成!\n");
		system("pause");
	}

inline int numberError(char *n){
    if (strlen(n)!=10) return 1;
    for (int i=0;i<10;i++) if (!(n[i]>='0'&&n[i]<='9')) return 1;
    return 0;
}

inline int scoreError(double n){
    if (!(n<=100.0&&n>=0.0)) return 1;
    return 0;
}

inline void getGrade(student *s){
    s->grade=0.0;
    if (s->score[0]>=60.0) s->grade+=courseGrade[0];
	if (s->score[1]>=60.0) s->grade+=courseGrade[1];
	if (s->score[2]>=60.0) s->grade+=courseGrade[2];
	if (s->score[3]>=60.0) s->grade+=courseGrade[3];
	if (s->score[4]>=60.0) s->grade+=courseGrade[4];
	if (s->score[5]>=60.0) s->grade+=courseGrade[5];
    return;
}

inline void getAverage(student *s){
    s->average=0.0;
    for (int i=0;i<6;i++) s->average+=s->score[i];
    s->average/=6.0;
    return;
}

void getCourseAverage(student *s){
    for (int i=0;i<num;i++){
        for (int j=0;j<6;j++){
            averageScore.score[j]=0;
        }
        averageScore.average=0;
        averageScore.grade=0;
    }
    strcpy(averageScore.name,"平均分");
    strcpy(averageScore.studentNumber,"          ");
    for (int i=0;i<num;i++){
        for (int j=0;j<6;j++){
            averageScore.score[j]+=s[i].score[j];
        }
        averageScore.average+=s[i].average;
        averageScore.grade+=s[i].grade;
    }
    for (int j=0;j<6;j++){
        averageScore.score[j]/=num;
    }
    averageScore.average/=num;
    averageScore.grade/=num;
}


void swapStudent(student &p,student &q){
    student tmp;
    tmp=q;
    q=p;
    p=tmp;
    return;
}

inline void gradeSort(student *s,int n){
    for (int i=0;i<n-1;i++){
        for (int j=0;j<n-i-1;j++){
            if (s[j].grade<s[j+1].grade){
                swapStudent(s[j],s[j+1]);
            }
        }
    }
    return;
}

inline void averageSort(student *s,int n){
    for (int i=0;i<n-1;i++){
        for (int j=0;j<n-i-1;j++){
            if (s[j].average<s[j+1].average){
                swapStudent(s[j],s[j+1]);
            }
        }
    }
    return ;
}

inline void sortCompositeScore(student *s,int n){
    for (int i=0;i<n-1;i++){
        for (int j=0;j<n-i-1;j++){
            if (s[j].compositeScore<s[j+1].compositeScore){
                swapStudent(s[j],s[j+1]);
            }
        }
    }
    return ;
}

inline void studentNumberSort(student *s,int n){
    for (int i=0;i<n-1;i++) {
        for (int j=0;j<n-i-1;j++) {
            if (strcmp(s[j].studentNumber,s[j+1].studentNumber)>0) {
                swapStudent(s[j],s[j+1]);
            }
        }
    }
    return ;
}

inline void getCompositeScore(student *s){
    s->compositeScore=(s->average*0.7)+((s->score[6]+s->score[7])/2*0.3);
    return;
}

void inputStudent(student *s){
    clearAll();
    if (num!=0){
        printf("已经建立过成绩单了！\n");
        successPrompt();
        return;
    }
    printf("请输入学生人数\n");
    scanf("%d",&num);
    clearAll();
    for (int i=0;i<num;i++){
        printf("----------------------------------------------------------------------------------------------------\n");
        printf("|                                            建立成绩单                                            |\n");
        printf("|                                          --------------                                          |\n");
        printf("请输入学生%d学号\n",i+1);
        scanf("%s",s[i].studentNumber);
        while (numberError(s[i].studentNumber)){
            fflush(stdin);
            printf("输入错误，请重新输入\n");
            scanf("%s",s[i].studentNumber);
        }
        char sign;
        do {
            printf("请输入学生姓名\n");
            scanf("%s",s[i].name);
            printf("姓名为%s,确认(Y),重输(N)\n",s[i].name);
            fflush(stdin);
            sign=getchar();
        }while (sign!='y'&&sign!='Y');
        for (int j=0;j<courseNum;j++){
            printf("请输入%s成绩\n",elementName[j]);
            scanf("%lf",&s[i].score[j]);
            while (scoreError(s[i].score[j])){
                printf("输入错误，请重新输入\n");
                scanf("%lf",&s[i].score[j]);
            }
        }
        getAverage(&s[i]);
        getGrade(&s[i]);
        getCompositeScore(&s[i]);
        clearAll();
    }
    studentNumberSort(stu,num);
    successPrompt();
    return;
}

inline void printName(char *a){
    int slen=strlen(a);
    if (slen>6){
        for (int i=0;i<6;i++){
            putchar(a[i]);
        }
    }
    int putspace=(6-slen)/2;
    for (int i=0;i<putspace;i++){
        putchar(' ');
    }
    printf("%s",a);
    for (int i=0;i<6-slen-putspace;i++){
        putchar(' ');
    }
    putchar('|');
    return;
}

inline void printScore(int spa,double sco){
    int slen;
	if (sco>99.9) slen = 5;
	if (sco<99.9&&sco>10.0) slen=4;
	if (sco<10.0) slen=3;
	int putspace=(spa-slen)/2;
	for (int i=0;i<putspace;i++){
        putchar(' ');
    }
    printf("%.1f",sco);
    for (int i=0;i<spa-slen-putspace;i++){
        putchar(' ');
    }
    putchar('|');
    return ;
}

void printAverage(){
    getCourseAverage(stu);
    printf("|%2d|%s|",num+1,averageScore.studentNumber);
    printName(averageScore.name);
    printScore(8,averageScore.score[0]);
    printScore(8,averageScore.score[1]);
    printScore(6,averageScore.score[2]);
    printScore(6,averageScore.score[3]);
    printScore(6,averageScore.score[4]);
    printScore(6,averageScore.score[5]);
    printScore(4,averageScore.grade);
    printScore(6,averageScore.average);
    printScore(6,averageScore.score[6]);
    printScore(6,averageScore.score[7]);
    printScore(5,averageScore.compositeScore);
    putchar('\n');
	printf("|--------------------------------------------------------------------------------------------------|\n");
}

void outputStudent(){
    printf("|==================================================================================================|\n");
    printf("|                                             学生成绩表                                           |\n");
    printf("|--------------------------------------------------------------------------------------------------|\n");
    printf("|序|          |      | 软件技 | C 语言 | 高等 | 大学 | 大学 | 近现 | 学 | 平均 |辅导员| 同学 | 综合|\n");
    printf("|号|   学号   | 姓名 | 术导论 |程序设计| 数学 | 体育 | 英语 | 代史 | 分 |  分  | 评分 | 评分 |  分 |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    for (int i=0;i<num;i++){
        printf("|%2d|%s|",i+1,stu[i].studentNumber);
        printName(stu[i].name);
        printScore(8,stu[i].score[0]);
        printScore(8,stu[i].score[1]);
        printScore(6,stu[i].score[2]);
        printScore(6,stu[i].score[3]);
        printScore(6,stu[i].score[4]);
        printScore(6,stu[i].score[5]);
        printScore(4,stu[i].grade);
        printScore(6,stu[i].average);
        printScore(6,stu[i].score[6]);
        printScore(6,stu[i].score[7]);
        printScore(5,stu[i].compositeScore);
        putchar('\n');
		printf("|--------------------------------------------------------------------------------------------------|\n");
    }
    printAverage();
    successPrompt();
    return;
}

void outputScholarship(){
    int prize[3];
    for (int i=0;i<3;i++){
        prize[i]=(int)(allNum*scholarshipRate[i]);
    }
    printf("|学生共有%2d人，一等奖学金%2d人，二等奖学金%2d人，三等奖学金%2d人                                      |\n",allNum,prize[0],prize[1],prize[2]);
    printf("|==================================================================================================|\n");
    printf("|                                             学生成绩表                                           |\n");
    printf("|--------------------------------------------------------------------------------------------------|\n");
    printf("|序|          |      | 软件技 | C 语言 | 高等 | 大学 | 大学 | 近现 | 奖 | 平均 |辅导员| 同学 | 综合|\n");
    printf("|号|   学号   | 姓名 | 术导论 |程序设计| 数学 | 体育 | 英语 | 代史 |学金|  分  | 评分 | 评分 |  分 |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    for (int i=0;i<num;i++){
        printf("|%2d|%s|",i+1,stu[i].studentNumber);
        printName(stu[i].name);
        printScore(8,stu[i].score[0]);
        printScore(8,stu[i].score[1]);
        printScore(6,stu[i].score[2]);
        printScore(6,stu[i].score[3]);
        printScore(6,stu[i].score[4]);
        printScore(6,stu[i].score[5]);
        //printScore(4,stu[i].grade);
        if (stu[i].grade<fullGrade) printf("挂科|");
        else {
            if (prize[0]>0){
                prize[0]--;
                printf("一等|");
            }
            else if (prize[1]>0){
                prize[1]--;
                printf("二等|");
                }
                else if (prize[2]>0){
                    prize[2]--;
                    printf("三等|");
                    }
                    else printf(" 无 |");
        }
        printScore(6,stu[i].average);
        printScore(6,stu[i].score[6]);
        printScore(6,stu[i].score[7]);
        printScore(5,stu[i].compositeScore);
        putchar('\n');
		printf("|--------------------------------------------------------------------------------------------------|\n");
    }
//    printAverage();
    successPrompt();
    return;
}

void RoutputStudent(){
    printf("|==================================================================================================|\n");
    printf("|                                             学生成绩表                                           |\n");
    printf("|--------------------------------------------------------------------------------------------------|\n");
    printf("|序|          |      | 软件技 | C 语言 | 高等 | 大学 | 大学 | 近现 | 学 | 平均 |辅导员| 同学 | 综合|\n");
    printf("|号|   学号   | 姓名 | 术导论 |程序设计| 数学 | 体育 | 英语 | 代史 | 分 |  分  | 评分 | 评分 |  分 |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    for (int i=num-1;i>=0;i--){
        printf("|%2d|%s|",num-i,stu[i].studentNumber);
        printName(stu[i].name);
        printScore(8,stu[i].score[0]);
        printScore(8,stu[i].score[1]);
        printScore(6,stu[i].score[2]);
        printScore(6,stu[i].score[3]);
        printScore(6,stu[i].score[4]);
        printScore(6,stu[i].score[5]);
        printScore(4,stu[i].grade);
        printScore(6,stu[i].average);
        printScore(6,stu[i].score[6]);
        printScore(6,stu[i].score[7]);
        printScore(5,stu[i].compositeScore);
        putchar('\n');
		printf("|--------------------------------------------------------------------------------------------------|\n");
    }
    printAverage();
    successPrompt();
    return ;
}

void sortStudent(student*s,int n){
    averageSort(s,n);
    gradeSort(s,n);
    output(2);
    return;
}

void RsortStudent(student*s,int n){
    averageSort(s,n);
    gradeSort(s,n);
    output(0);
    RoutputStudent();
    return;
}


void compositeSort(student *s,int n){
    sortCompositeScore(s,n);
    gradeSort(s,n);
    output(6);
    return;
}



void findGrade(){
    output(0);
    double grade;
    printf("请输入要查询的学分：\n");
    scanf("%lf",&grade);
    printf("|==================================================================================================|\n");
    printf("|                                        学分为");
    printScore(4,grade);
    printf("\b学生成绩                                        |\n");
    printf("|--------------------------------------------------------------------------------------------------|\n");
    printf("|序|          |      | 软件技 | C 语言 | 高等 | 大学 | 大学 | 近现 | 学 | 平均 |辅导员| 同学 | 综合|\n");
    printf("|号|   学号   | 姓名 | 术导论 |程序设计| 数学 | 体育 | 英语 | 代史 | 分 |  分  | 评分 | 评分 |  分 |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    for (int i=0;i<num;i++){
        if (stu[i].grade>grade-0.1 && stu[i].grade<grade+0.1){
            printf("|%2d|%s|",i+1,stu[i].studentNumber);
            printName(stu[i].name);
            printScore(8,stu[i].score[0]);
            printScore(8,stu[i].score[1]);
            printScore(6,stu[i].score[2]);
            printScore(6,stu[i].score[3]);
            printScore(6,stu[i].score[4]);
            printScore(6,stu[i].score[5]);
            printScore(4,stu[i].grade);
            printScore(6,stu[i].average);
            printScore(6,stu[i].score[6]);
            printScore(6,stu[i].score[7]);
            printScore(5,stu[i].compositeScore);
            putchar('\n');
        }
        printf("|--------------------------------------------------------------------------------------------------|\n");
    }
    successPrompt();
    return;
}

void findIndex(){
    output(0);
    int index;
    printf("请输入要查询的编号：\n");
    scanf("%d",&index);
    if (index>num+1){
        printf("查无此人！");
        successPrompt();
        return;
    }
    output(0);
    printf("|==================================================================================================|\n");
    printf("|                                          序号%2d学生成绩                                          |\n",index);
    printf("|--------------------------------------------------------------------------------------------------|\n");
    printf("|序|          |      | 软件技 | C 语言 | 高等 | 大学 | 大学 | 近现 | 学 | 平均 |辅导员| 同学 | 综合|\n");
    printf("|号|   学号   | 姓名 | 术导论 |程序设计| 数学 | 体育 | 英语 | 代史 | 分 |  分  | 评分 | 评分 |  分 |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("|%2d|%s|",index,stu[index-1].studentNumber);
    printName(stu[index-1].name);
    printScore(8,stu[index-1].score[0]);
    printScore(8,stu[index-1].score[1]);
    printScore(6,stu[index-1].score[2]);
    printScore(6,stu[index-1].score[3]);
    printScore(6,stu[index-1].score[4]);
    printScore(6,stu[index-1].score[5]);
    printScore(4,stu[index-1].grade);
    printScore(6,stu[index-1].average);
    printScore(6,stu[index-1].score[6]);
    printScore(6,stu[index-1].score[7]);
    printScore(5,stu[index-1].compositeScore);
    putchar('\n');
    printf("|--------------------------------------------------------------------------------------------------|\n");
    successPrompt();
    return;
}

void insertStudent(){
    output(0);
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("|                                             插入数据                                             |\n");
    printf("|                                          --------------                                          |\n");
    printf("请输入学生学号\n");
    scanf("%s",stu[num].studentNumber);
    while (numberError(stu[num].studentNumber)){
        fflush(stdin);
        printf("输入错误，请重新输入\n");
        scanf("%s",stu[num].studentNumber);
    }
    char sign;
    do {
        printf("请输入学生姓名\n");
        scanf("%s",stu[num].name);
        printf("姓名为%s,确认(Y),重输(N)\n",stu[num].name);
        fflush(stdin);
        sign=getchar();
    }while (sign!='y'&&sign!='Y');
    for (int j=0;j<6;j++){
        printf("请输入%s成绩\n",elementName[j]);
        scanf("%lf",&stu[num].score[j]);
        while (scoreError(stu[num].score[j])){
            printf("输入错误，请重新输入\n");
            scanf("%lf",&stu[num].score[j]);
        }
    }
    getAverage(&stu[num]);
    getGrade(&stu[num]);
    clearAll();
    num++;
    studentNumberSort(stu,num);
    successPrompt();
    return;
}

void deleteStudent(){
    char tmpNumber[15];
    output(0);
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("|                                             删除数据                                             |\n");
    printf("|                                          --------------                                          |\n");
    printf("请输入学生学号\n");
    scanf("%s",tmpNumber);
    while (numberError(tmpNumber)){
        fflush(stdin);
        printf("输入错误，请重新输入\n");
        scanf("%s",tmpNumber);
    }
    int p=0;
    for (int i=0;i<num;i++){
        if (strcmp(stu[i].studentNumber,tmpNumber)==0){
            swapStudent(stu[i],stu[num-1]);
            num--;
            p++;
            break;
        }
    }
    if (!p) {
        printf("查无此人！\n");
    }
    successPrompt();
    return;
}

void editStudent(){
    char tmpNumber[15];
    output(0);
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("|                                             修改数据                                             |\n");
    printf("|                                          --------------                                          |\n");
    printf("请输入学生学号\n");
    scanf("%s",tmpNumber);
    while (numberError(tmpNumber)){
        fflush(stdin);
        printf("输入错误，请重新输入\n");
        scanf("%s",tmpNumber);
    }
    int p=0;
    for (int i=0;i<num;i++){
        if (strcmp(stu[i].studentNumber,tmpNumber)==0){
            char sign;
            do {
                printf("请输入学生姓名\n");
                scanf("%s",stu[i].name);
                printf("姓名为%s,确认(Y),重输(N)\n",stu[i].name);
                fflush(stdin);
                sign=getchar();
            }while (sign!='y'&&sign!='Y');
            for (int j=0;j<courseNum;j++){
                printf("请输入%s成绩\n",elementName[j]);
                scanf("%lf",&stu[i].score[j]);
                while (scoreError(stu[i].score[j])){
                    printf("输入错误，请重新输入\n");
                    scanf("%lf",&stu[i].score[j]);
                }
            }
            getAverage(&stu[i]);
            getGrade(&stu[i]);
            getCompositeScore(&stu[i]);
            clearAll();
            p++;
            break;
        }
    }
    if (!p) {
        printf("查无此人！\n");
    }
    successPrompt();
    return;
}

void exitSystem(){
    clearAll();
    output(0);
    char s[50];
    for (int i=0;i<=0xf;i++){
        Sleep(50);
        sprintf(s,"color %x0",i);
        system(s);
    }
    for (int i=1;i<=5;i++){
        printf("\n");
    }
    printf("感谢使用学生管理系统,%s\n",elementName[8]);
    exit(0);
    return;
}

void mainMenu(){
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("|                                              主菜单                                              |\n");
    printf("|                                          --------------                                          |\n");
    printf("|                                          1.建立成绩单                                            |\n");
    printf("|                                          2.查询数据                                              |\n");
    printf("|                                          3.成绩排序                                              |\n");
    printf("|                                          4.编辑数据                                              |\n");
    printf("|                                          0.退出                                                  |\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    getMainChoice();
    return;
}

void getSortChoice(){
    if (num<=0){
        printf("你还没建立成绩单呢！");
        successPrompt();
        return;
    }
    printf("请选择：\n");
    char p=getchar();
    switch (p)
    {
        case '1': studentNumberSort(stu,num);output(2);break;
        case '2': sortStudent(stu,num);                break;
        case '3': RsortStudent(stu,num);               break;
        case '0':                                      break;
        default: printf("输入错误，请重新输入\n");
    }
    return;
}

void sortStudentMenu(){
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("|                                             成绩排序                                             |\n");
    printf("|                                          --------------                                          |\n");
    printf("|                                          1.按学号排序                                            |\n");
    printf("|                                          2.成绩正序排序                                          |\n");
    printf("|                                          3.成绩倒序排序                                          |\n");
    printf("|                                          0.返回主菜单                                            |\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    getSortChoice();
    return;
}

void getFindChoice(){
    if (num<=0){
        printf("你还没建立成绩单呢！");
        successPrompt();
        return;
    }
    printf("请选择：\n");
    char p=getchar();
    switch (p)
    {
        case '1': output(2);              break;
        case '2': findGrade();            break;
        case '3': findIndex();            break;
        case '4': compositeSort(stu,num); break;
        case '0':                         break;
        default: printf("输入错误，请重新输入\n");
    }
    return;
}

void findStudentMenu(){
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("|                                             查询数据                                             |\n");
    printf("|                                          --------------                                          |\n");
    printf("|                                          1.查询成绩单                                            |\n");
    printf("|                                          2.按成绩查询                                            |\n");
    printf("|                                          3.按序号查询                                            |\n");
    printf("|                                          4.奖学金查询                                            |\n");
    printf("|                                          0.返回主菜单                                            |\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    getFindChoice();
    return;
}

void getEditChoice(){
    printf("请选择：\n");
    char p=getchar();
    switch (p)
    {
        case '1': insertStudent();        break;
        case '2': deleteStudent();        break;
        case '3': editStudent();          break;
        case '0':                         break;
        default: printf("输入错误，请重新输入\n");
    }
    return;
}

void editStudentMenu(){
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("|                                             编辑数据                                             |\n");
    printf("|                                          --------------                                          |\n");
    printf("|                                          1.插入数据                                              |\n");
    printf("|                                          2.删除数据                                              |\n");
    printf("|                                          3.修改数据                                              |\n");
    printf("|                                          0.返回主菜单                                            |\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    getEditChoice();
    return;
}

void output(int typ){
    clearAll();
    printf("****************************************************************************************************\n");
    printf("*                                       欢迎使用学生管理系统                                       *\n");
    printf("****************************************************************************************************\n");
    switch (typ){
        case 1: mainMenu();          break;
        case 2: outputStudent();     break;
        case 3: editStudentMenu();   break;
        case 4: findStudentMenu();   break;
        case 5: sortStudentMenu();   break;
        case 6: outputScholarship(); break;
    }
    return ;
}

void getMainChoice(){
    printf("请选择：\n");
    char p=getchar();
    switch (p)
    {
        case '1': inputStudent(stu);      break;
        case '2': output(4);              break;
        case '3': output(5);              break;
        case '4': output(3);              break;
        case '0': exitSystem();           break;
        default: printf("输入错误，请重新输入\n");
    }
    return;
}

int main(){
//    windowSet(80,80);
    system("color 0f");
    while (1){
        output(1);
    }
    return 0;
}