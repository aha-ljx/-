#include<iostream>
#include<algorithm>
using namespace std;
int X,N;
int coin[11];
//二分查找小于等于x的值
int find(int x){
	int l=1,r=N,mid;
	while(l<r){
		mid = (l+r+1)/2;
		if(coin[mid]<=x) l = mid;
		else r = mid-1;
	}
	return l;
}
int main(){
	cin>>X>>N;
	for(int i=1;i<=N;i++){
		cin>>coin[i];
	}
	sort(coin+1,coin+N+1);
	int current_max = 0;
	int ans = 0;
	if(coin[1]!=1) return -1;
	while(current_max < X){
		//寻找小于等于current_max+1的值，如果大于current_max+1,无法覆盖current_max+1。
		int i = find(current_max+1);
		ans++;current_max+=coin[i];
	}
	cout<<ans;
	return 0;
}