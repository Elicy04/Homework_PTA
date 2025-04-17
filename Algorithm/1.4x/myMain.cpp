#include <bits/stdc++.h>
#include <string>



using namespace std;

//输入最大规模
const int MAXN = 30;
//总数字个数
int n;
//用于保存各个数字的字符串数组
string num[MAXN];

bool cmp(string x,string y){
    return stoi(x+y)>=stoi(y+x);
}

void input(){
    cin>> n;
    for(int i=1;i<=n;i++){
        cin>> num[i];
    }
}

void output(){
    for(int i=1;i<=n;i++){
        cout<<num[i];
    }
}

int main(){
    // 输入优化
    cin.sync_with_stdio(0);
    cin.tie(0);
    //输入
    input();
    //处理
    sort(&num[1],&num[n+1],cmp);
    //输出
    output();

    return 0;
}