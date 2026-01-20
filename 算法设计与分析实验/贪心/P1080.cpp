#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#define ll long long
#define MANN 1005
using namespace std;
struct Minister{
	ll lefthand;
	ll righthand;
};
//排序用比较算法
bool compare(const Minister& a,const Minister& b){
	return a.lefthand*a.righthand<b.lefthand*b.righthand;
}
//计算当前最大奖赏，高精度整数除法
vector<int> bigIntDivide(const vector<int>& num,ll divisor){
	vector<int> res;
	ll remainder = 0;//余数
	//逆序遍历，从高位开始进行
	for(int i=num.size()-1;i>=0;i--){
		remainder = remainder*10+num[i];
		int q = remainder/divisor;
		res.push_back(q);
		remainder%=divisor;
	}
	//移除前导零
	while(res.size() > 1 && res[0] ==0){
		res.erase(res.begin());//erase是删除指定位置的元素
	}
	//翻转结果，由于存储时候是高位存在低位，所以需要翻转
	reverse(res.begin(),res.end());
	return res;
}
//高精度整数比较（a>b返回true）
bool bigIntCompare(const vector<int>& a,const vector<int>& b){
	if(a.size()!=b.size()){
		return a.size()>b.size(); //位数更多的大
	}
	//从高位开始比较
	for(int i=a.size()-1;i>=0;i--){
		if(a[i]!=b[i]){
			return a[i]>b[i];
		}
	}
	return false;
}
//高精度整数乘法
vector<int> bigIntMultiply(const vector<int>& num,ll x){
	vector<int> res;
	ll carry = 0;//进位
	//模拟人在做乘法时的过程,从低位开始遍历
	for(int digit:num){
		ll temp = digit*x+carry;
		res.push_back(temp%10);//数组最低位存储结果最低位
		carry = temp/10;
	}
	//处理剩余进位
	while(carry>0){
		res.push_back(carry%10);
		carry/=10;
	}
	//移除前导零
	while(res.size()>1 && res.back() == 0){
		res.pop_back();
	}
	return res;
}
//高精度整数转化为字符串
string bigIntToString(const vector<int>& num){
	string s;
	for(int i=num.size()-1;i>=0;i--){
		s+=to_string(num[i]);
	}
	return s.empty()?"0":s;
}
int main(){
	int n;
	cin>>n;
	ll kingleft,kingright;
	cin>>kingleft>>kingright;
	
	vector<Minister> ministers(n);
	for(int i=0;i<n;i++){
		cin>>ministers[i].lefthand>>ministers[i].righthand;
	}
	sort(ministers.begin(),ministers.end(),compare);
	
	//使用数组存储product和最大奖赏max_reward
	vector<int> product;vector<int> max_reward;
	int temp = kingleft;
	if(temp == 0){
		product.push_back(0);
	}else{
		while(temp>0){
			product.push_back(temp%10);//product是低位存数字的低位，高位存数字高位
			temp/=10;
		}
	}
	
	for(const auto& m:ministers){
		//计算当前最大奖赏
		vector<int> current_reward = bigIntDivide(product,m.righthand);
		//更新最大奖赏
		if(bigIntCompare(current_reward,max_reward)){
			max_reward = current_reward;
		}
		//更新product
		product = bigIntMultiply(product,m.lefthand);
	}
	cout << bigIntToString(max_reward);
	return 0;
}