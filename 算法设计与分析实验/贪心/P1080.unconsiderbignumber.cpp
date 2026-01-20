#include<iostream>
#include<vector>
#include<algorithm>
#define MAXN 1005
#define ll long long
using namespace std;
int n;
struct Minister{
	ll lefthand;
	ll righthand;
};
//按左手右手相乘的大小顺序进行排序
bool compare(const Minister& a,const Minister& b){//参数是传递引用，避免调用时候频繁拷贝对象
	return a.lefthand*a.righthand<b.lefthand*b.righthand;//从小到大排序，用<
}
int main(){
	ll kingleft,kingright;
	cin>>n;
	cin>>kingleft>>kingright;
	vector<Minister> ministers(n);
	for(int i=0;i<n;i++){
		cin>>ministers[i].lefthand>>ministers[i].righthand;
	}
	ll max_reward = 0;
	ll product = kingleft;//初始乘积是国王的左手
	//将ministers按照指定的顺序排列
	sort(ministers.begin(),ministers.end(),compare);
	
	for(const auto& m:ministers){
		ll reward = product/m.righthand;
		if(reward>max_reward){
			max_reward = reward;
		}
		product*=m.lefthand;
	}
	cout<<max_reward;
	return 0;
}