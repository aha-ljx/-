/*
#include<iostream>
#include<vector>
using namespace std;
//判断填入的数字是否合法
bool isValid(vector<vector<int>>& grid,int row,int col,int num){
	for(int i=0;i<9;i++){
		if(grid[i][col] == num) return false;
	}
	for(int j=0;j<9;j++){
		if(grid[row][j] == num) return false;
	}
	//检查3*3网格是否合法
	int startrow = row-row%3;
	int startcol = col-col%3;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(grid[startrow+i][startcol+j] == num) return false;
		}
	}
	return true;
}
//递归回溯求解数独
bool solveSudu(vector<vector<int>>& grid){
	//寻找格子为0的
	for(int row = 0;row<9;row++){
		for(int col=0;col<9;col++){
			if(grid[row][col] == 0){
				//填入9个数字
				for(int num=1;num<=9;num++){
					if(isValid(grid,row,col,num)){
						grid[row][col] = num;
						if(solveSudu(grid)){
							return true;
						}
						grid[row][col] = 0;
					}
				}
				return false;
			}
		}
	}
	return true;
}
//打印数独
void printSudu(vector<vector<int>>&grid){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout<<grid[i][j]<<' ';
		}
		cout<<endl;
	}
}
int main(){
	vector<vector<int>> grid(9,vector<int>(9,0));
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cin>>grid[i][j];
		}
	}
	solveSudu(grid);
	printSudu(grid);
	return 0;
}
*/
#include <iostream>
#include <vector>
using namespace std;

// 全局辅助数组，用于快速判断合法性
bool rowUsed[9][10];   // rowUsed[i][num]: 第i行是否用了num
bool colUsed[9][10];   // colUsed[j][num]: 第j列是否用了num
bool boxUsed[9][10];   // boxUsed[b][num]: 第b个3x3宫格是否用了num

// 计算3x3宫格编号
inline int getBoxIndex(int row, int col) {
    return (row / 3) * 3 + (col / 3);
}

// 初始化辅助数组
void initUsed(vector<vector<int>>& grid) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int num = grid[i][j];
            if (num != 0) {
                rowUsed[i][num] = true;
                colUsed[j][num] = true;
                boxUsed[getBoxIndex(i, j)][num] = true;
            }
        }
    }
}

// 回溯求解数独
bool solveSudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (grid[row][col] == 0) {
                int boxIdx = getBoxIndex(row, col);
                for (int num = 1; num <= 9; ++num) {  // 注意：num 从 1 开始！
                    if (!rowUsed[row][num] && !colUsed[col][num] && !boxUsed[boxIdx][num]) {
                        // 填入数字
                        grid[row][col] = num;
                        rowUsed[row][num] = colUsed[col][num] = boxUsed[boxIdx][num] = true;

                        if (solveSudoku(grid)) {
                            return true;
                        }

                        // 回溯
                        grid[row][col] = 0;
                        rowUsed[row][num] = colUsed[col][num] = boxUsed[boxIdx][num] = false;
                    }
                }
                return false; // 无合法数字可填
            }
        }
    }
    return true; // 所有格子已填满
}

// 打印数独
void printSudoku(const vector<vector<int>>& grid) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    vector<vector<int>> grid(9, vector<int>(9));
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cin >> grid[i][j];
        }
    }

    // 初始化辅助数组
    initUsed(grid);

    // 求解
    solveSudoku(grid);

    // 输出结果
    printSudoku(grid);

    return 0;
}