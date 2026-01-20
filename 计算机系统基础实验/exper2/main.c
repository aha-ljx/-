#include <stdio.h>
#include <string.h>
#include <sys/time.h>   // gettimeofday
#include <stddef.h> 
#define STUDENTS_NUM 24

typedef struct temp {
	char  sname[8];
	char  sid[11];    //  如U202315123
	short  scores[8]; //  8门课的分数
	short  average;   //  平均分
}student;

extern void computeAverageScore(student* s,int num);

void display(student* s, int num){
	for(int i=0;i<num;i++){
		printf("%s ",s[i].sname);
		printf("%s ",s[i].sid);
		for(int j=0;j<8;j++){
			printf("%hd ",s[i].scores[j]);
		}
		printf("%hd",s[i].average);
		printf("\n");
	}
}

void initStudents(student* s, int num)
{
	strcpy(s[0].sname, "ljx");
	strcpy(s[0].sid, "U202414845");
	s[0].scores[0] = 99;
	s[0].scores[1] = 99;
	s[0].scores[2] = 99;
	for (int i=3;i<8;i++){
		s[0].scores[i] = 99;
	}
	s[0].average = 0;
	printf("请顺次输入几个人的信息\n");
	for(int i=1;i<=num;i++){
		scanf("%7s",s[i].sname);
		scanf("%10s",s[i].sid);
		for(int j=0;j<8;j++){
			scanf("%hd",&s[i].scores[j]);
		}
		s[i].average = 0;
	}
}

/*void computeAverageScore(student* s,int num)
{
	for(int i=0;i<num;i++){
		short re=0;
		for(int j=0;j<8;j++){
			re += s[i].scores[j];
		}
		s[i].average = re/8;
	}
}
*/
void sortbyaverage1(student *s,student *new,int num){
	int d[num];
	int temp;
	for(int i=0;i<num;i++){
		d[i] = i;
	}
	for(int i=0;i<num-1;i++){
		for(int j = 0;j<num-1-i;j++){
			if(s[j].average>s[j+1].average){
				temp = d[j];
				d[j] = d[j+1];
				d[j+1] = temp;
			}	
		}
	}
	for(int i=0;i<num;i++){
		new[i] = s[d[i]];
	}
}

void sortbyaverage2(student *s,student *new,int num){
    for (int i = 0; i < num; i++) {
        new[i] = s[i];
    }
    
    // 2. 优化的冒泡排序（针对小型数据，常数项极低）
    for (int i = 0; i < num - 1; i++) {
        int flag = 0;
        int last_swap = num - 1;
        for (int j = 0; j < last_swap; j++) {
            if (new[j].average > new[j + 1].average) {
                // 3. 直接交换结构体（避免中间索引数组）
                student temp = new[j];
                new[j] = new[j + 1];
                new[j + 1] = temp;
                flag = 1;
                last_swap = j; // 更新最后交换位置
            }
        }
        
        if (!flag) break; // 无交换则提前退出
    }
}

// 交换两个学生结构体
void swap(student *a, student *b) {
    student temp = *a;
    *a = *b;
    *b = temp;
}

// 快速排序分区函数
int partition(student *s, int low, int high) {
    // 选择最右边的元素作为基准
    short pivot = s[high].average;
    int i = (low - 1);  // 小于基准的元素索引

    for (int j = low; j <= high - 1; j++) {
        // 如果当前元素小于或等于基准
        if (s[j].average <= pivot) {
            i++;  // 增加小于基准区域的索引
            swap(&s[i], &s[j]);
        }
    }
    swap(&s[i + 1], &s[high]);
    return (i + 1);
}

// 快速排序实现
void quickSort(student *s, int low, int high) {
    if (low < high) {
        // pi是分区索引，s[pi]现在在正确的位置
        int pi = partition(s, low, high);

        // 分别对基准前后的元素进行排序
        quickSort(s, low, pi - 1);
        quickSort(s, pi + 1, high);
    }
}

// 优化后的排序函数
void sortbyaverage3(student *s, student *new, int num) {
    // 先复制原数组，避免修改原数组
    memcpy(new, s, num * sizeof(student));
    
    // 对新数组进行快速排序
    if (num > 1) {
        quickSort(new, 0, num - 1);
    }
}

// 获取当前时间（毫秒）
long long current_millis()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main() {
    student s[STUDENTS_NUM], new[STUDENTS_NUM];
    long long t, start, end;
    int iterations = 10000; // 循环次数，放大时间
	printf("scores offset: %zu\n", offsetof(student, scores));
    printf("average offset: %zu\n", offsetof(student, average));
    printf("%zu\n", sizeof(student));
    initStudents(s, STUDENTS_NUM);

    /* ---- 计算平均分（循环多次） ---- */
    t = 0;
    for (int i = 0; i < 10*iterations; i++) {
        start = current_millis();
        computeAverageScore(s, STUDENTS_NUM);
        end = current_millis();
        t += (end - start);
    }
    printf("计算平均成绩（%d次）用时：%lld 毫秒\n", 10*iterations, t);

    /* ---- 排序（循环多次） ---- */
    t = 0;
    for (int i = 0; i < 10*iterations; i++) {
        start = current_millis();
        sortbyaverage1(s, new, STUDENTS_NUM);
        end = current_millis();
        t += (end - start);
    }
    printf("排序成绩（%d次）用时：%lld 毫秒\n", 10*iterations, t);

	/* ---- 排序（循环多次） ---- */
    t = 0;
    for (int i = 0; i < 10*iterations; i++) {
        start = current_millis();
        sortbyaverage2(s, new, STUDENTS_NUM);
        end = current_millis();
        t += (end - start);
    }
    printf("(2优化后)排序成绩（%d次）用时：%lld 毫秒\n", 10*iterations, t);

    /* ---- 排序（循环多次） ---- */
    t = 0;
    for (int i = 0; i < 10*iterations; i++) {
        start = current_millis();
        sortbyaverage3(s, new, STUDENTS_NUM);
        end = current_millis();
        t += (end - start);
    }
    printf("(3优化后)排序成绩（%d次）用时：%lld 毫秒\n", 10*iterations, t);

    /* ---- 打印最终结果（只需要一次） ---- */
    computeAverageScore(s, STUDENTS_NUM); // 重新计算一次（因为循环中修改了s）
    printf("排序前学生信息：\n");
    display(s, STUDENTS_NUM);
    printf("排序后学生信息：\n");
    display(new, STUDENTS_NUM);

    return 0;
}
