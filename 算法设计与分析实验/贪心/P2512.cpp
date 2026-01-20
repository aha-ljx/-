/*
令Xi表示第i人向左传递的糖果总数，令Ai表示第i人手中的糖果数
Ai - Xi + Xi+1 = average
令Ci = A1+A2+A3+...+Ai - i*average
A1 - X1 + X2 = average      X2 = X1 - C1     
A2 - X2 + X3 = average      X3 = X1 - C2
An-1 - Xn-1 + Xn = average   Xn = X1 - Cn-1
如果求|X1|+|X2|+...|Xn|最小值，即求n*X1 - (C0+C1+C2+C3+...+Cn-1)
即求到C0,C1,C2...Cn-1距离最近的点，数学上是中位点到各个点距离最短。
*/

#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
int n;
const int MAXN = 1e6+5;
ll candy[MAXN];
ll sum[MAXN];//前缀和数组
ll C[MAXN];//由数学关系推导出来的数组，C[i] = sum[i] - i*average
int main(){
	cin>>n;
	ll averagecandy=0;
	for(int i=1;i<=n;i++){
		cin>>candy[i];
		averagecandy+=candy[i];
	}
	averagecandy/=n;
	ll count = 0;
	//构建前缀和数组sum
	sum[1] = candy[1];
	for(int i=2;i<=n;i++){
		sum[i] = sum[i-1]+candy[i];
	}
	//根据C[i] = sum[i] - i*average构建数组C
	for(int i=1;i<=(n-1);i++){
		C[i] = sum[i] - i*averagecandy;
	}
	//将数组C进行排序
	sort(C,C+n);
	//求出中位点到各个点的距离
	int mid = C[n/2];
	for(int i=0;i<n;i++){
		count+=abs(mid-C[i]);
	}
	cout<<count;
	return 0;
}