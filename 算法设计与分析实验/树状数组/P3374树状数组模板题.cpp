/*
树状数组和前缀和数组都是求解区间长度的，但两者适用方向不同
树状数组适用于区间的点数值一直在变化，需要动态查询
前缀和数组适用于静态区间
*/
#include<iostream>
#include<vector>
#define ll long long
using namespace std;

class treeArray{
private:
	vector<ll> tree;//tree[i]表示区间内元素和,num[i-l+1]---num[i]之间的元素和，l = i&(-i)
	int n;
	
public:
	treeArray(int size):n(size),tree(size+1,0){}//初始化将tree的长度定为size+1，从1开始
	
	void update(int i,int delta){
		while(i<=n){
			tree[i]+=delta;//更新所有包括i的区间的元素和
			i+= i & (-i);//取的是二进制的最低位1的位序，作为区间长度
		}
	}
	
	int query(int i){
		ll sum = 0;
		while(i>=1){
			sum+=tree[i];
			i-= i & (-i);//查询时候i-=，从树尖到树根遍历
		}
		return sum;
	}
	
	int queryrange(int l,int r){
		return query(r) - query(l-1);
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n,m;
	cin>>n>>m;
	vector<ll> a(n+1);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	treeArray tr(n);
	for(int i=1;i<=n;i++){
		tr.update(i,a[i]);//初始化时候是用当前数组初始化
	}
	int op;
	for(int i=1;i<=m;i++){
		cin>>op;
		if(op == 1){
			int x,k;
			cin>>x>>k;
			tr.update(x,k);
		}else{
			int x,y;
			cin>>x>>y;
			int ans = tr.queryrange(x,y);
			cout<<ans<<endl;
		}
	}
	return 0;
}