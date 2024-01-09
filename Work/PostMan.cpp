#include <iostream>
#include <string.h>
#include <vector>
#define N 100
using namespace std;

const int inf = 0x3f3f3f3f;
// 存储奇度点
char oddVex[N];
int count = 0;
char reodd[N];
int sign[N][N];

typedef struct node
{
    int vexnum;
    int arcnum;
    char vexs[N];
    int arcs[N][N];
    int rearcs[N][N];
} graph;

int LocateVex(graph *g, char v);

// 初始化图以及邻接矩阵
graph *createGraph(int vnum, int anum)
{
    char vi, vj;
    int weight;
    int i, j;
    graph *G = new graph;
    G->vexnum = vnum;
    G->arcnum = anum;
    cout << "请输入" << vnum << "个顶点：" << endl;
    for (int i = 0; i < vnum; i++)
    {
        cin >> G->vexs[i];
    }
    for (int i = 0; i < vnum; i++)
    {
        for (int j = 0; j < vnum; j++)
        {
            G->arcs[i][j] = 0;
        }
    }
    cout << "请输入" << anum << "条边和权值：" << endl;
    for (int k = 0; k < anum; k++)
    {
        cin >> vi >> vj >> weight;
        i = LocateVex(G, vi);
        j = LocateVex(G, vj);
        G->arcs[i][j] = weight;
        G->arcs[j][i] = weight;
    }
    return G;
}

// 输出邻接矩阵
void ShowGraph(graph *g)
{
    int i, j;
    cout << "邻接矩阵为：" << endl;
    for (i = 0; i < g->vexnum; i++)
    {
        for (j = 0; j < g->vexnum; j++)
        {
            cout << g->arcs[i][j] << " ";
        }
        cout << endl;
    }
}

// 确定每个顶点的下标
int LocateVex(graph *g, char v)
{
    int i;
    for (i = 0; i < g->vexnum; i++)
    {
        if (g->vexs[i] == v)
        {
            return i;
        }
    }
    return -1;
}

// 确定下标对应的顶点
char GetVex(graph *g, int index)
{
    if (index >= 0 && index < g->vexnum)
    {
        return g->vexs[index];
    }
    return '\0';
}

// 计算顶点的度数
void Degree(graph *g)
{
    for (int i = 0; i < g->vexnum; i++)
    {
        int degree = 0;
        for (int j = 0; j < g->vexnum; j++)
        {
            if (g->arcs[i][j] != 0)
                degree++;
        }
        cout << "顶点" << g->vexs[i] << "的度为" << degree << endl;
    }
}

// 寻找度数为奇数的顶点
void Odd(graph *g)
{
    int k = 0;
    for (int i = 0; i < g->vexnum; i++)
    {
        int degree = 0;
        for (int j = 0; j < g->vexnum; j++)
        {
            if (g->arcs[i][j] != 0)
                degree++;
        }
        if (degree % 2 != 0)
        {
            oddVex[k++] = g->vexs[i];
        }
    }
    cout << "度为奇数的顶点为：";
    for (int i = 0; i < k; i++)
    {
        cout << oddVex[i] << " ";
        count++;
    }
    cout << endl;
}

// 求最短路径
int Dijkstra(graph *g, char start, char end)
{
    int i, j;
    int dis[g->vexnum];
    int path[g->vexnum];
    for (int i = 0; i < g->vexnum; i++)
    {
        dis[i] = inf;
        path[i] = 0;
    }
    int startv = LocateVex(g, start);
    dis[startv] = 0;
    for (int i = 0; i < g->vexnum; i++)
    {
        int min = inf, minv;
        for (int j = 0; j < g->vexnum; j++)
        {
            if (dis[j] < min && path[j] == 0)
            {
                min = dis[j];
                minv = j;
            }
        }
        path[minv] = 1;
        for (int j = 0; j < g->vexnum; j++)
        {
            if (g->arcs[minv][j] > 0)
            {
                if (min + g->arcs[minv][j] < dis[j])
                {
                    dis[j] = min + g->arcs[minv][j];
                }
            }
        }
    }
    int endv = LocateVex(g, end);
    return dis[endv];
}

// 求每个奇度点到其他奇度点的距离
void Dijkstra_Odd(graph *g)
{
    int k = 0;
    for (; k < count; k++)
    {
        char start = oddVex[k];
        for (int l = k + 1; l < count; l++)
        {
            char end = oddVex[l];
            int dis = Dijkstra(g, start, end);
            cout << "从" << start << "到" << end << "的最短路径为：" << dis << endl;
        }
    }
}

// 寻找两个奇度点之间的具体路径
void short_way(graph *g, char start, char end)
{
    int dis[g->vexnum];
    int path[g->vexnum];
    int pre[g->vexnum]; // 用于记录前驱节点
    for (int i = 0; i < g->vexnum; i++)
    {
        dis[i] = inf;
        path[i] = 0;
    }
    int startv = LocateVex(g, start);
    dis[startv] = 0;
    pre[startv] = -1; // 起点没有前驱节点

    for (int i = 0; i < g->vexnum; i++)
    {
        int min = inf, minv;
        for (int j = 0; j < g->vexnum; j++)
        {
            if (dis[j] < min && path[j] == 0)
            {
                min = dis[j];
                minv = j;
            }
        }
        path[minv] = 1;
        for (int j = 0; j < g->vexnum; j++)
        {
            if (g->arcs[minv][j] > 0)
            {
                if (min + g->arcs[minv][j] < dis[j])
                {
                    dis[j] = min + g->arcs[minv][j];
                    pre[j] = minv; // 更新前驱节点
                }
            }
        }
    }

    int endv = LocateVex(g, end);
    int current = endv; // 将终点作为当前节点
    cout << "逆序路径为：" << endl;
    cout << GetVex(g, current);
    while (current != startv) // 回溯构造最短路径
    {
        current = pre[current];
        cout << " -> " << GetVex(g, current);
    }
    cout << endl
         << endl;
}

// 距离最短的配对方案及权值
void search_edge(graph *g)
{
    char start, end;
    int sign[count] = {0};
    start = oddVex[0];
    int i = 0, k = 0;
    int tmp;
    int sum = 0;
    cout << "距离最短的添加方案的配对为：" << endl;
    int l = 0;
    for (; i < count; i++)
    {
        if (sign[i] == 0)
        {
            int temp = inf;
            char start = oddVex[i];
            for (int j = i + 1; j < count; j++)
            {
                if (sign[j] == 0)
                {
                    char end = oddVex[j];
                    int dis1 = Dijkstra(g, start, end);
                    if (dis1 < temp)
                    {
                        tmp = j;
                        temp = dis1;
                    }
                }
            }
            sign[i] = 1;
            sign[tmp] = 1;
            cout << oddVex[i] << "-" << oddVex[tmp] << endl;
            int j = 1;
            while (j--)
            {
                reodd[l] = oddVex[i];
                reodd[++l] = oddVex[tmp];
                l++;
            }
            sum += temp;
        }
    }
    cout << "距离最短的添加方案的权值总和为" << sum << endl;
}

// void odd_edge(graph *g){
// 	for(int i=0;i<g->vexnum;i++){
//         reodd[i]='0';
//     }
//     for(int i=0;i<g->vexnum;i++){
//         for(int j=0;j<count;j++){
//             if(g->vexs[i]==oddVex[j]){
//                 reodd[i]=g->vexs[i];
//             }
//         }
//     }
// }

// 添加边
void add_edge(graph *g)
{
    int sign[g->vexnum][g->vexnum];
    memset(g->rearcs, 0, sizeof(sign));
    int flag[g->vexnum];
    memset(flag, 0, sizeof(flag));
    for (int i = 0; i < g->vexnum; i++)
    {
        int c = LocateVex(g, oddVex[i]);
        flag[c] = 1;
    }
    int i, j;
    for (i = 0; i < g->vexnum; i++)
    {
        for (j = 0; j < g->vexnum; j++)
        {
            if (g->arcs[i][j] != 0 && g->arcs[j][i] != 0)
            {
                g->rearcs[i][j] = 1;
                g->rearcs[j][i] = 1;
            }
        }
    }
    int a;
    for (i = 0; i < count; i++)
    {
        int a = LocateVex(g, reodd[i]);
        int b = LocateVex(g, reodd[i + 1]);
        if (flag[i] == 1)
        {
            g->rearcs[a][b]++;
            g->rearcs[b][a]++;
            flag[i] = 0;
            flag[i + 1] = 0;
        }
    }

    // for (i = 0; i < g->vexnum; i++)
    // {
    //     for (j = 0; j < g->vexnum; j++)
    //     {
    //         cout << g->rearcs[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}

// 一笔画输出欧拉回路

// 深度优先搜索遍历欧拉回路
void DFS_Euler(graph *g, int v, vector<int> &path)
{
    for (int i = 0; i < g->vexnum; i++)
    {
        if (g->rearcs[v][i] > 0)
        {
            g->rearcs[v][i]--;
            g->rearcs[i][v]--;
            DFS_Euler(g, i, path);
        }
    }
    path.push_back(v);
}

// 输出欧拉回路
void EulerPath(graph *g)
{
    cout<<"从哪个顶点出发输出欧拉回路:"<<endl;
    char start;
    cin>>start;
    vector<int> path;
    int s= LocateVex(g,start); // 从第一个顶点开始遍历，即A点
    DFS_Euler(g, s, path);
    cout << "欧拉回路为：";
    for (int i = path.size() - 1; i >= 0; i--)
    {
        cout << g->vexs[path[i]] << " ";
    }
    cout << endl;
}

int main()
{
    int vexnum;
    int arcnum;
    cout << "请输入顶点数：" << endl;
    cin >> vexnum;
    cout << "请输入边数：" << endl;
    cin >> arcnum;
    graph *G = createGraph(vexnum, arcnum);
    ShowGraph(G);    // 输出邻接矩阵
    Degree(G);       // 求顶点的度数
    Odd(G);          // 求奇度点
    Dijkstra_Odd(G); // 迪杰斯特拉算法求奇度点之间的最短路径
    search_edge(G);  // 寻找代价最小的奇度点配对方案
    add_edge(G);     // 添加重复边
    EulerPath(G);    // 按顶点输出欧拉回路
    return 0;
}
// 测试用例
//  12
//  16
//  ABCDEFGHIJKL
//  A B 3
//  A L 2
//  L K 3
//  K J 3
//  J I 2
//  I F 3
//  F E 2
//  E D 3
//  D C 4
//  C B 1
//  C G 3
//  A G 1
//  E G 4
//  H L 3
//  F H 2
//  H J 3