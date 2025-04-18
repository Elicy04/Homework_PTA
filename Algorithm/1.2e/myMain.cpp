#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> work;

// 总收益
long long sum = 0; // 经过mingjia3同学提醒

// 任务数量
int n = 0;

// 存储任务的动态数组
vector<work> worklist;

// 比较函数
bool cmp(const work &a, const work &b)
{
    return a.second > b.second;
}

// 实现并查集
class UnionFind
{
public:
    vector<int> parent; // 父节点标识符
    // vector<int> rank;   // 树高度
public:
    // 构造函数
    UnionFind(int size)
    {
        parent.resize(size + 1);
        // rank.resize(size + 1, 0);
        for (int i = 0; i <= size; i++)
        {
            parent[i] = i;
        }
    }
    // // 查找
    // int find(int x)
    // {
    //     if (parent[x] != x)
    //     {
    //         parent[x] = find(parent[x]);
    //     }
    //     return parent[x];
    // }
    // 查找（非递归）
    int find(int x){
        while(parent[x]!=x){
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
    // // 合并,此题不打算用
    // void unite(int x, int y)
    // {
    //     int rootX = find(x);
    //     int rootY = find(y);
    //     // 如果在同一集合
    //     if (rootX == rootY)
    //         return;
    //     // 否则合并
    //     if (rank[rootX] < rank[rootY])
    //     {
    //         parent[rootX] = rootY;
    //     }
    //     else
    //     {
    //         parent[rootY] = rootX;
    //         if (rank[rootX] == rank[rootY])
    //         {
    //             rank[rootX]++;
    //         }
    //     }
    // }
    // // 判断两个元素是否在同一集合，此题无用
    // bool isConnected(int x, int y)
    // {
    //     return find(x) == find(y);
    // }
};

void input()
{
    cin >> n;
    worklist.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> worklist[i].first >> worklist[i].second;
    }
}

void get_sum()
{
    UnionFind uf(n);
    sort(worklist.begin() + 1, worklist.end(), cmp);
    for (int i = 1, j = 0; i <= n; i++)
    {
        j = uf.find(min(worklist[i].first,n));
        if (j != 0)
        {
            sum += worklist[i].second;
            uf.parent[j] = uf.find(j-1);
        }
    }
}

void output()
{
    cout << sum <<endl;
}

int main()
{
    // 输入优化
    cin.sync_with_stdio(0);
    cin.tie(0);
    // 输入
    input();
    // 处理
    get_sum();
    // 输出
    output();
    return 0;
}

//Q*1:极大问题：对于代码逻辑完全无误，而最后一个样例点始终报段错误的原因
//A*1:已查明：来源：cmp函数中的比较使用了 ">="而不是">"
//这道题无排序稳定性要求，由https://blog.csdn.net/Strengthennn/article/details/107738011指出
//当用sort给大量数据排序时若使用自定义的cmp比较函数， 则必须注意弱序规则，即尽可能使用">"/"<"而不是">="/"<="