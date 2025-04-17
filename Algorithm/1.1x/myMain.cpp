#include <bits/stdc++.h>

using namespace std;

// 输入规模最大值
const int MAXN = 10000;

// 可容纳质量
int M;
// 总物品数量
int N;
// 用于存储各物品重量列表的数组
int items[MAXN];

// 用于存储解集的栈
queue<int> myqueue;

// 求出应该放入背包的物品
bool getItems(int m,int n)
{
    if(items[n]==m){
        myqueue.push(items[n]);
        return true;
    }
    if(n==1||m<0){
        return false;
    }else{
            //装入背包
            if(getItems(m-items[n],n-1)){
                myqueue.push(items[n]);
                return true;
            }
            //不装入背包
            if(getItems(m,n-1)){
                return true;
            }
    }
    return false;
}
void input()
{
    cin >> M >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> items[i];
    }
}

void output()
{
    while (!myqueue.empty())
    {
        int tmp;
        tmp = myqueue.front();
        cout << tmp;
        myqueue.pop();
        if(!myqueue.empty()){
            cout<<" ";
        }
    }
    cout<<endl;
}

int main()
{
    // 输入优化
    cin.sync_with_stdio(0);
    cin.tie(0);
    // 输入
    input();
    // 处理
    if(!getItems(M,N)){
        cout<<"0"; //无解
    }
    // 输出
    else{
        output();
    }
    return 0;
}

// Q1:可否以贪心算法做这道题？
// A1：显然不能，如mi分别为5,3,3,3,总m=9的情况，则从前向后扫描时不能选取5

// Q2:输出顺序是？
// A2：虽然题目中未明确指出，但由样例1可以猜测是选择结果是遵循输入的初始顺序的