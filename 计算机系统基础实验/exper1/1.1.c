#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#define N 5
#define N1 2
#define N2 3
#define Student_Pack_Size 214
typedef struct{
	char name[8];
	short age;
	float score;
	char remark[200];
}student;

void input(student*s){
	for(int i=0;i<N;i++){
		printf("请输入第%d个同学信息：\n",i+1);
		printf("姓名：\n");
		scanf("%s",s[i].name);
		printf("年龄：\n");
		scanf("%hd",&s[i].age);
		printf("成绩：\n");
		scanf("%f",&s[i].score);
		printf("备注：\n");
		scanf("%s",s[i].remark);
	}
}

int pack_student_bytebybyte(student*s,int sno,char*buf){
	int cnts = 0;
	int cntname, cntage, cntscore, cntremark, cntbuf = 0;
	char* p = (char*)s;
	char* pp = buf;
	while (cnts < sno)
	{
		// 读取名字
		cntname = 0;
		while (cntname < 8) {
			if (*p) {  // 遇到\0
				*pp = *p;
				cntname++, cntbuf++;
				p++, pp++;
			}
			else {
				*pp = '\0';
				cntbuf++;
				p += (8 - cntname);                                   
				pp++;
				break;
			}
		}

		// 读取年龄
		cntage = 0;
		while (cntage < 2)
		{
			*pp = *p;
			cntbuf++, cntage++, p++, pp++;
		}

		p += 2;
		// 读入float,占 4 个字节
		cntscore = 0;
		while (cntscore < 4)
		{
			*pp = *p;
			cntbuf++, cntscore++, p++, pp++;
		}

		// 读取remark数组
		cntremark = 0;
		while (cntremark < 200)
		{
			if (*p) {
				*pp = *p;
				cntbuf++, cntremark++, p++, pp++;
			}
			else {
				*pp = 0;
				cntbuf++, pp++;
				p += (200 - cntremark);
				break;
			}
		}
		cnts++;
	}
	return cntbuf;
}

int pack_student_whole(student *s,int sno,char *buf){
	int cnts = 0;
	char* p = (char*)s;
	char* pp = buf;
	student* ppp = s;
	while (cnts < sno)
	{
		// 拷贝名字
		strcpy(pp, ppp[cnts].name);
		pp += strlen(ppp[cnts].name) + 1;
		// 拷贝age
		*((short*)pp) = ppp[cnts].age;
		pp += 2;
		// 拷贝score
		*((float*)pp) = ppp[cnts].score;
		pp += 4;
		// 拷贝备注
		strcpy(pp, ppp[cnts].remark);
		pp += strlen(ppp[cnts].remark) + 1;
		cnts++;

	}
	return pp - buf;
}

int restore_student(char *buf,int len,student *s){
	int cnt = 0; // 记录解压的人数
	char* p = buf;
	student* pp = s;
	int record = 0;
	while ((p - buf) < len)
	{
		// 解压名字
		strcpy(pp[cnt].name, p);
		p += strlen(pp[cnt].name) + 1;
		// 解压年龄
		pp[cnt].age = *((short*)p);
		p += 2;
		// 解压分数
		pp[cnt].score = *((float*)p);
		p += 4;
		// 解压备注
		strcpy(pp[cnt].remark, p);
		int lens = strlen(pp[cnt].remark);
		for(int i = lens;i<200;i++){
			pp[cnt].remark[i] = 0;
		}
		p += lens + 1;
		// 条数加一
		cnt++;
	}
	return cnt;
}

void output(student *s,int count){
	for(int i=0;i<count;i++){
		printf("第%d个学生信息：",i+1);
		printf("姓名：%s",s[i].name);
		printf("年龄：%hd",s[i].age);
		printf("成绩：%f",s[i].score);
		printf("备注：%s",s[i].remark);
	}
}

void print_message(char *buf,int len){
	printf("message中前40个字节：\n");
	for(int i=0;i<len&&i<40;i++){
		printf("%02X ",(unsigned char)buf[i]);
	}
	printf("\n");
}

int main(){
	student new_s[N];
	char message[2000];
	int packed_len = 0;
	int packed_len1 = 0,packed_len2 = 0;
	//input(old_s);
	// 初始化
	student old_s[N] = {
		{"ljx",19,45,"呵呵"},
		{"张三",2,98,"哈哈"},
		{"李四",3,96,"啦啦"},
		{"王五",4,94,"噗噗"},
		{"柳七",5,92,"啧啧"}
	};
	system("cls");
	packed_len1 = pack_student_bytebybyte(old_s,N1,message);
	packed_len2 = pack_student_whole(&old_s[N1],N2,message+packed_len1);
	printf("按字节压缩后message长度：%d\n",packed_len1);
	printf("整体压缩后message长度：%d\n",packed_len2);
	packed_len = packed_len1 + packed_len2;
	printf("------------------------------\n");
	print_message(message,packed_len);
	int num = restore_student(message,packed_len,new_s);
	printf("------------------------------\n");
	printf("原来学生信息：\n");
	output(old_s,N);
	printf("\n");
	printf("修复后的学生信息：\n");
	output(new_s,num);
	
	return 0;
}
