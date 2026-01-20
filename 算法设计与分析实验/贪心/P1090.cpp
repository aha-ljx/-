//哈夫曼编码--没有使用小顶堆，时间复杂度是O(n2logn)
#include<iostream>
#include<algorithm>
#include<vector>
#define MAXN 10005
using namespace std;
int n;
vector<int> a(MAXN);
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	sort(a.begin(),a.begin()+n);
	int ans = 0;
	for(int i=1;i<=n-1;i++){
		ans += a[0]+a[1];
		int temp = a[0]+a[1];
		a[1] = temp;
		a.erase(a.begin());
		sort(a.begin(),a.begin()+n-i);
	}
	cout<<ans;
	return 0;
}

//哈夫曼编码--使用小顶堆，时间复杂度是O(nlogn)
#include<iostream>
#include<queue>
using namespace std;
int n,ans;
priority_queue<int,vector<int>,greater<int>> q;//greater<int>是小于比较，构造小顶堆；less<int>是大顶堆
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		q.push(x);
	}
	while(q.size()>1){
		int a = q.top();q.pop();
		int b = q.top();q.pop();
		ans += a+b;
		q.push(a+b);
	}
	cout<<ans;
	return 0;
}