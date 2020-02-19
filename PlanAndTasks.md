##  一、系统分析

1. 存储学生信息
2. 存储课程信息
3. 存储成绩信息
4. 存储综合信息
5. 信息排序
6. 奖学金评比

## 二、系统设计

### 1.流程图

```mermaid
graph TD

E[导入数据] --> A
C[数据修改] --> A
A --> C
A[主程序] --> B[信息排序]
A --> F[奖学金评比]
F --> D[输出数据]
B --> D
A --> G[导出txt文件]

```

### 2.功能模块图

```mermaid
graph TD
A[Main] --> B[Menu]
A --> D[Calculate&Sort]
A --> C[IO]
C --> C1[Input]
C --> C2[Output]
A --> F[S/L]
F --> F1[Save]
F --> F2[Load]
A --> G[Change]
```

### 3.数据结构设计

1. 学生数据结构
   + 姓名
   + 学号
   + 宿舍号
   + 性别
   + 年龄
   + 所修课程
     - 课程号
     - 课程得分
     - 重修标记
   + 奖惩信息
     - 奖励/惩罚
     - 奖惩种类
     - 奖惩信息
2. 课程数据结构
   * 课程号
   * 课程名称
   * 课程学期



### 4.菜单结构设计

```mermaid
graph TD
A[主菜单] --> B[1.文件]
A --> C[2.编辑]
A --> D[3.查询]
A --> E[4.计算]
```

```mermaid
graph TB

B[1.文件] --> B1[建立新文件]
B --> B2[导入文件]
B --> B3[导出文件]
B --> B4[导出txt]
```

```mermaid
graph TB
C[2.编辑] --> C1[添加/删除学生]
C --> C2[添加/删除课程]
C --> C3[编辑学生信息]
C --> C4[编辑课程信息]
```





### 5.输入输出设计

### 6.文件结构设计

### 7.代码规范化设计

## 三、测试

## 四、运行界面

## 五、总结

## 六、开发日志及计划

02.19 进行菜单设计，实现方向键选择菜单，空格确认，esc 键退出功能。