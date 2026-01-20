#include<iostream>
#include<string>
#include<vector>
using namespace std;
//如果是单纯寻找最大数字并删除，就会导致低位数字没有删除，如2134
//维护一个递增的单调栈，当前数字小于栈顶数字时候，弹出栈顶元素，并把当前数字入栈
int main(){
	string in_put;
	int k;
	cin>>in_put>>k;
	vector<char> stack;//单调栈
	for(char c:in_put){
		while(!stack.empty() && c<stack.back() && k>0){
			stack.pop_back();
			k--;
		}
		stack.push_back(c);
	}
	//当k还有剩余时候，去掉末尾的数字
	while(k>0 && !stack.empty()){
		stack.pop_back();
		k--;
	}
	string result;
	bool leading_zero = true;
	for(char c:stack){
		//跳过前导零
		if(leading_zero && c=='0'){
			continue;
		}
		leading_zero = false;
		result += c;
	}
	if(result.empty()){
		cout<<0;
	}else{
		cout<<result;
	}
	return 0;
}