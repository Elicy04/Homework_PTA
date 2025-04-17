#include <iostream>
#include <algorithm>
#include <utility>
#include <stack>
#include <limits>

using namespace std;

// 对pair<int,int>重命名
typedef pair<int, int> coord;

// 对坐标基于横坐标的比较函数
bool cmp(coord x, coord y)
{
    if (x.first == y.first)
    {
        return x.second > y.second;
    }
    return x.first > y.first;
}

const int MAXN = 11000;

// 总坐标个数
int n;
// 坐标数组
coord points[MAXN];
// 存储极大点下标的栈
stack<int> mystack;
// 读取函数并排序
void input()
{
    cin >> n;
    // 一共读n次
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        points[i].first = x;
        points[i].second = y;
    }
    sort(&points[1], &points[n+1], cmp);
}

// 输入检查函数
void examine()
{
    for (int i = 1; i <= n; i++)
    {
        cout << "(" << points[i].first << "," << points[i].second << ")" << " ";
    }
}

// 从前向后扫描寻找极大点
void find_maxmimal_points()
{
    int temp_max_y = INT32_MIN;
    for (int i = 1; i <= n; i++)
    {
        if (points[i].second > temp_max_y)
        {
            mystack.push(i);
            temp_max_y = points[i].second;
        }
    }
}

// 打印函数
void output()
{
    while (!mystack.empty())
    {
        int tmp;
        tmp = mystack.top();
        cout << "(" << points[tmp].first << "," << points[tmp].second << ")";
        mystack.pop();
    }
    cout << endl;
}

int main()
{
    // 输入优化
    cin.sync_with_stdio(0);
    cin.tie(0);
    // 读取
    input();
    find_maxmimal_points();
    output();
    return 0;
}

// Q1:对于x1>=x2,y1>=y2的支配关系，当x1=x2时，支配关系判断会出问题，当x等于时，前面的元素可能会被后面的元素支配
// S1:针对cmp做出调整，当x1=x2时根据y大小确定优先级(已完成)