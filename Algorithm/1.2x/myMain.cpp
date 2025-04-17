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
    //查找
    int find(int x){
        if(parent[x]!=x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    //合并
    void unite(int x,int y){
        int rootX = find(x);
        int rootY = find(y);
        //如果在同一集合
        if(rootX == rootY)return; 
        //否则合并
        if(rank[rootX]<rank[rootY]){
            parent[rootX] = rootY;
        }else{
            parent[rootY] = rootX;
            if(rank[rootX] == rank[rootY]){
                rank[rootX]++;
            }
        }
    }
    //判断两个元素是否在同一集合
    bool isConnected(int x,int y){
        return find(x)==find(y);
    }
};

// 学习更为简洁的节点构体写法模式,loc定位符，h为节点高
struct Node
{
    int loc, h;
    Node(int _loc, int _h) : loc(_loc), h(_h) {};
};

//最大输入规模
const int MAXN = 2100;

//矩阵边长
int n;
//存储矩阵的动态数组
vector<Node> NodeList;
//标记节点是否激活的布尔数组
bool isActive[MAXN];
//记录结果
int max_h;




void input()
{
    cin>>n;
    for(int i=1,tmp=0;i<=n*n;i++){
        cin >> tmp;
        NodeList.push_back(Node(i,tmp));
        isActive[i] = false;
    }
    sort(NodeList.begin(),NodeList.end(),[](const Node& a,const Node& b){
        return a.h < b.h;
    }
    );
}

//找到最大中间节点
void get_res(){
    UnionFind uf(n*n);
    for(int i=1,tmploc=0;i<=n*n;i++){
        isActive[i]=true;
        tmploc = NodeList[i].loc;
        //up
        if(tmploc>n&&isActive[tmploc-n]){
            uf.unite(tmploc,tmploc-n);
        }
        //down
        if(tmploc>n*(n-1)&&isActive[tmploc+n]){
            uf.unite(tmploc,tmploc+n);

        }
        //left
        if(tmploc%n!=1&&isActive[tmploc-1]){
            uf.unite(tmploc,tmploc-1);

        }
        //right
        if(tmploc%n!=0&&isActive[tmploc+1]){
            uf.unite(tmploc,tmploc+1);
            
        }
        if(uf.isConnected(1,n*n)){
            max_h = NodeList[i].h;
            return;
        }
    }
}



void output()
{
    cout << max_h<<endl;
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