#include <bits/stdc++.h>
#include <algorithm>
#include <vector>

using namespace std;

// 实现并查集
class UnionFind
{
private:
    vector<int> parent; // 父节点标识符
    vector<int> rank;   // 树高度
public:
    // 构造函数
    UnionFind(int size)
    {
        parent.resize(size + 1);
        rank.resize(size + 1, 0);
        for (int i = 1; i <= size; i++)
        {
            parent[i] = i;
        }
    }
    // 查找
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    // 合并
    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        // 如果在同一集合
        if (rootX == rootY)
            return;
        // 否则合并
        if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else
        {
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY])
            {
                rank[rootX]++;
            }
        }
    }
    // 判断两个元素是否在同一集合
    bool isConnected(int x, int y)
    {
        return find(x) == find(y);
    }
};

// 借助更为简洁的节点构造体写法模式,loc定位符，h为节点高
struct Node
{
public:
    int loc, h;
    Node():loc(0),h(0){};
    Node(int _loc, int _h) : loc(_loc), h(_h) {};
    Node(const Node &s) : loc(s.loc), h(s.h) {};
};

// 最大输入规模
const int MAXN = 1200000;
// const int MAXN = 81;//调试用规模，请勿忘记改回

// 矩阵边长
int n;
// 存储矩阵的动态数组
vector<Node> NodeList;
// 标记节点是否激活的布尔数组
bool isActive[MAXN];
// 记录结果
int max_h;




void input()
{
    cin >> n;
    NodeList.resize(n * n + 1);
    for (int i = 1, tmp = 0; i <= n * n; i++)
    {
        cin >> tmp;
        NodeList[i] = Node(i, tmp);
        isActive[i] = false;
    }
    sort(NodeList.begin()+1, NodeList.end(), [](const Node &a, const Node &b)
         { return a.h < b.h; }
        );

}

// 找到最大中间节点
void get_res()
{
    UnionFind uf(n * n);
    for (int i = 1, tmploc = 0; i <= n * n; i++)
    {
        // 激活新的节点
        tmploc = NodeList[i].loc;
        isActive[tmploc] = true;
        // up
        if (tmploc > n && isActive[tmploc - n])
        {
            uf.unite(tmploc, tmploc - n);
        }
        // down
        if (tmploc <= n * (n - 1) && isActive[tmploc + n])
        {
            uf.unite(tmploc, tmploc + n);
        }
        // left
        if (tmploc % n != 1 && isActive[tmploc - 1])
        {
            uf.unite(tmploc, tmploc - 1);
        }
        // right
        if (tmploc % n != 0 && isActive[tmploc + 1])
        {
            uf.unite(tmploc, tmploc + 1);
        }
        // 检验起点和终点是否连通
        if (uf.isConnected(1, n * n))
        {
            max_h = NodeList[i].h;
            return;
        }
    }
}

void output()
{
    cout << max_h << endl;
}

int main()
{
    // 输入优化
    cin.sync_with_stdio(0);
    cin.tie(0);
    // 输入
    input();
    // 处理
    get_res();
    // 输出
    output();
    return 0;
}

// Q1:这种类似Kruskal的思路是否能够求得经过的最大值节点最小的路线，并重点在于找到这个值，这件事的正确性有待考究

// TD1:
//  1 5 7
//  4 2 3
//  8 9 4
// 理论分析：依次选中长 1，2，3，4，4,此处结果无误
// 测试输入：3 1 5 7 4 2 3 8 9 4

// 第一次测试：发生数组越界（来源：isActive[tmploc]-> tmploc = -213453546 )
    // 发现问题：对于NoteList中的元素输入,采用的是pushback方法，导致第一个元素下标从0开始，而我们调用时认为是从1开始，导致读取元素始终发生错位
    // p.s.此bug预测在NodeList读取到最高点的时候于isActive[n*n+C]处发生段错误，但由于本题设置的isActive规模过大，
    // 导致原来在NoteList[n*n]的垃圾值取正时有可能不发生,但由于无论如何对最低元素发生漏读，导致逻辑bug
    // 解决办法：对NoteList进行resize扩容，再针对NoteList[i]指定赋值，这样认为可直接明确将元素存入指定数组下标，符合强迫症.
    //检验：问题解决

//第二次测试：发生报错，来源（stl_construct.h):no matching function for call to 'Node::Node()'
    //发现问题：创建vector:NoteList进行resize等操作，使得vector：NoteList试图创建空元素，但缺乏无参构造函数，调用失败导致错误
    //解决办法：对Node类加上无参构造函数
    //检验：问题解决