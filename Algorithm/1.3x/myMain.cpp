#include <bits/stdc++.h>

using namespace std;


//孩子数量
int n;
//糖果数量
int m;
//用于存储孩子需求的优先队列
priority_queue<int, vector<int>,greater<int> > children;
//用于存储糖果重量的优先队列
priority_queue<int, vector<int>,greater<int> > candybox;
//用于存储可满足孩子的最大数量
int maxnum=0;
void input()
{
    cin >> m >> n;
    for(int i =1;i<=m;i++){
        int j=0;
        cin >> j;
        candybox.push(j);
    }
    for(int i =1;i<=n;i++){
        int j=0;
        cin >> j;
        children.push(j);
    }    
}

void get_max(){
    while(!candybox.empty()){
        if(candybox.top()>=children.top()){
            children.pop();
            maxnum++;
        }
        candybox.pop();
    }
}

void output()
{
    cout << maxnum;
}

int main()
{
    // 输入优化
    cin.sync_with_stdio(0);
    cin.tie(0);
    // 输入
    input();
    // 处理
    get_max();
    // 输出
    output();
    return 0;
}

//Q1:为什么调试时后发现优先队列里的元素并不是按下标有序的？
//A1:优先队列只是说逻辑上每次出队的是最小/大元素，而物理结构上不一定有序