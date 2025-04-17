#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

// 对坐标基于横坐标的比较函数
bool cmp(pair<int, int> x, pair<int, int> y)
{
    return x.first > y.first;
}

const int MAXN = 1002;

//总坐标个数
int n;
//坐标数组
pair<int,int> points[MAXN];

//读取函数并排序
void input(){
    cin >> n;
    //一共读n次
    for(int i=1;i<=n;i++){
        int x,y;
        cin >> x >> y;
        points[i].first = x;
        points[i].second = y;
    }
    sort(&points[1],&points[1001],cmp);
}

//输入检查函数
void examine(){
    for(int i=1;i<=n;i++){
        cout << "("<< points[i].first<<","<<points[i].second<<")"<<" ";
    }
}

int main()
{
    //输入优化
    cin.sync_with_stdio(0);
    cin.tie(0);
    //读取
    input();
    examine();

    return 0;
}