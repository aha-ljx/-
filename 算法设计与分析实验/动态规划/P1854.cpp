#include <iostream>
#include <algorithm>
#include <climits>
#define MAXN 105
using namespace std;

int F, V;
int a[MAXN][MAXN];          // a[i][j]：第i束花放在第j个花瓶的美学值
int dp[MAXN][MAXN];         // dp[i][j]：前i束花，第i束放在j号花瓶的最大美学值
int path[MAXN][MAXN];       // path[i][j]：记录最优路径，前i束花第i束放j时，前i-1束的花瓶编号
int res[MAXN];              // 存储最终结果：res[i]是第i束花的花瓶编号

int main() {
    cin >> F >> V;
    // 输入美学值矩阵（花束1~F，花瓶1~V）
    for (int i = 1; i <= F; ++i) {
        for (int j = 1; j <= V; ++j) {
            cin >> a[i][j];
        }
    }

    // 1. 初始化边界：第1束花（i=1）放在任意j号花瓶的情况
    for (int j = 1; j <= V; ++j) {
        dp[1][j] = a[1][j];  // 只有1束花，美学值就是当前花在该花瓶的值
        path[1][j] = 0;      // 第1束花没有前一束，path记为0
    }

    // 2. 填充dp数组（按花束数量i从小到大计算）
    for (int i = 2; i <= F; ++i) {  // i从2到F（前i束花）
        for (int j = i; j <= V; ++j) {  // j从i到V（第i束花至少放i号花瓶，满足顺序约束）
            dp[i][j] = INT_MIN;  // 初始化为极小值，避免未更新的垃圾值
            int max_prev = INT_MIN;  // 存储前i-1束花在k<j时的最大dp[i-1][k]
            int best_k = 0;        // 记录前i-1束花的最优花瓶编号

            // 找前i-1束花在k<j的最大dp[i-1][k]（k至少为i-1，因为前i-1束花需要i-1个花瓶）
            for (int k = i-1; k < j; ++k) {
                if (dp[i-1][k] > max_prev) {
                    max_prev = dp[i-1][k];
                    best_k = k;
                }
            }

            // 转移方程：第i束花放j，加上前i-1束花的最大美学值
            dp[i][j] = a[i][j] + max_prev;
            path[i][j] = best_k;  // 记录最优路径的前一个花瓶编号
        }
    }

    // 3. 找到最后一束花（F）的最优花瓶（j从F到V）
    int max_total = INT_MIN;
    int last_j = 0;
    for (int j = F; j <= V; ++j) {
        if (dp[F][j] > max_total) {
            max_total = dp[F][j];
            last_j = j;
        }
    }

    // 4. 回溯路径：从最后一束花倒推到第一束
    res[F] = last_j;  // 第F束花的花瓶编号
    for (int i = F-1; i >= 1; --i) {
        res[i] = path[i+1][res[i+1]];  // 前一束花的编号 = path[当前束][当前花瓶]
    }

    // 5. 输出结果
    cout << max_total << endl;
    for (int i = 1; i <= F; ++i) {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}