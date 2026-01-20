#include<iostream>
#include<cmath>
using namespace std;
//分治思想：MID结构体记录中间位置
struct MID{
	int x;
	int y;
};
//GONGZHU结构体保存当前公主位置
struct GONGZHU{
	int x;
	int y;
};
//更新新的公主位置
GONGZHU refind(GONGZHU gongzhu,int rowbegin,int rowend,int colbegin,int colend,int **p){
	GONGZHU newgongzhu;
	if(gongzhu.x>rowend || gongzhu.y>colend || gongzhu.x<rowbegin || gongzhu.y<colbegin){//如果当前公主位置不在区域内
		for(int i=rowbegin;i<=rowend;i++){
			for(int j=colbegin;j<=colend;j++){
				if(p[i][j] !=0){
					newgongzhu.x = i;
					newgongzhu.y = j;
					return newgongzhu;
				}
			}
		}
	}
	return gongzhu;
}
//递归填充函数
void fill(GONGZHU gongzhu,int rowbegin,int rowend,int colbegin,int colend,int **p){
	// 递归终止条件：区域大小为1x1时无需填充
    if (rowbegin == rowend && colbegin == colend) {
        return;
    }
	MID mid;
	mid.x =(rowbegin+rowend)/2;
	mid.y =(colbegin+colend)/2;
	GONGZHU newgongzhu;
	newgongzhu = refind(gongzhu,rowbegin,rowend,colbegin,colend,p);
	if(newgongzhu.x<=mid.x && newgongzhu.y<=mid.y){
		p[mid.x+1][mid.y+1] = 1;
		p[mid.x][mid.y+1] = 1;
		p[mid.x+1][mid.y] = 1;
		cout<<mid.x+1<<' '<<mid.y+1<<' '<<1<<endl;
	}
	else if(newgongzhu.x<=mid.x && newgongzhu.y>=mid.y){
		p[mid.x+1][mid.y] = 2;
		p[mid.x][mid.y] = 2;
		p[mid.x+1][mid.y+1] = 2;
		cout<<mid.x+1<<' '<<mid.y<<' '<<2<<endl;
	}
	else if(newgongzhu.x>=mid.x && newgongzhu.y<=mid.y){
		p[mid.x][mid.y+1] = 3;
		p[mid.x][mid.y] = 3;
		p[mid.x+1][mid.y+1] = 3;
		cout<<mid.x<<' '<<mid.y+1<<' '<<3<<endl;
	}
	else if(newgongzhu.x>=mid.x && newgongzhu.y>=mid.y){
		p[mid.x][mid.y] = 4;
		p[mid.x][mid.y+1] = 4;
		p[mid.x+1][mid.y] = 4;
		cout<<mid.x<<' '<<mid.y<<' '<<4<<endl;
	}
	// 递归处理四个子区域
    fill(gongzhu, rowbegin, mid.x, colbegin, mid.y, p);           // 左上
    fill(gongzhu, rowbegin, mid.x, mid.y + 1, colend, p);         // 右上
    fill(gongzhu, mid.x + 1, rowend, colbegin, mid.y, p);         // 左下
    fill(gongzhu, mid.x + 1, rowend, mid.y + 1, colend, p);       // 右下
}
int main(){
	int k;
	cin>>k;
	int row,col;
	row = pow(2,k);
	col = pow(2,k);
	int** A = new int*[row + 1];
    for (int i = 0; i <= row; ++i) {
        A[i] = new int[col + 1]();  // 初始化所有元素为0
    }
	int **p = &A[0];
	GONGZHU gongzhu;
	cin>>gongzhu.x>>gongzhu.y;
	fill(gongzhu,1,row,1,col,p);
	for (int i = 0; i <= row; ++i) {
        delete[] A[i];
    }
    delete[] A;
	return 0;
}

