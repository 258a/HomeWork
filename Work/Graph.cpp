#include <iostream>
#include <queue>
#include <stack>
#include <cstring>

#define Vex_N 100
#define Arc_N 100

using namespace std;

typedef char vextype;

int dis[Vex_N][Vex_N];
int path[Vex_N][Vex_N] = {-1};

struct node
{
    vextype vexs[Vex_N];
    int arcs[Vex_N][Vex_N];
    int vexnum, arcnum;
    int kind; // 0：无向图，1：有向图
};
typedef struct node *MGraph;

int visited[Vex_N + '0'] = {0};
int founded[Vex_N + '0'] = {0};

// 用于定位顶点的位置
int LocateVex(MGraph g, vextype v);

//创建图
MGraph CreateGraph(int v, int a, int kind)
{
    char vi, vj;
    int weight;
    int i, j, k;
    MGraph g = new struct node;
    g->vexnum = v;
    g->arcnum = a;
    g->kind = kind;
    cout << "请输入" << v << "个顶点：" << endl;
    for (int i = 0; i < v; i++)
    {
        cin >> g->vexs[i];
    }
    cout << "初始化邻接矩阵" << endl;
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            g->arcs[i][j] = 0;
            dis[i][j] = 0x3f3f3f3f;
            dis[i][i] = 0;/*顶点自身到自身的距离设为0*/
            dis[j][j] = 0;
        }
    }
    cout << "请输入" << a << "条边和对应权重,（输入格式是vi vj weight）:" << endl;
    for (int k = 0; k < a; k++)
    {
        cin >> vi >> vj >> weight;
        i = LocateVex(g, vi);
        j = LocateVex(g, vj);
        if (g->kind == 0)
        {
            g->arcs[i][j] = weight;
            g->arcs[j][i] = weight;
            dis[i][j] = weight;
            dis[j][i] = weight;
        }
        else if (g->kind == 1)
        {
            g->arcs[i][j] = weight;
            dis[i][j] = weight;
            dis[j][i] = weight;
        }
    }
    return g;
}

// n为图g的顶点个数
void ShowGraph(MGraph g, int n)
{
    int i, j;
    cout << "邻接矩阵为：" << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << g->arcs[i][j] << " ";
        }
        cout << endl;
    }
}

void DFS(MGraph g, vextype v, int *visited)
{
    int i, j;
    i = LocateVex(g, v);
    visited[i] = 1;
    cout << g->vexs[i] << " ";
    for (j = 0; j < g->vexnum; j++)
    {
        if (g->arcs[i][j] == 1 && !visited[j])
        {
            DFS(g, g->vexs[j], visited);
        }
    }
}

void BFS(MGraph g, vextype v, int *visited)
{
    int i, j;
    memset(visited, 0, sizeof(visited));
    memset(founded, 0, sizeof(visited));

    queue<vextype> q;
    i = LocateVex(g, v);
    q.push(g->vexs[i]);
    while (!q.empty())
    {
        i = LocateVex(g, q.front());
        q.pop();
        visited[g->vexs[i]] = 1;
        cout << g->vexs[i] << " ";
        for (j = 0; j < g->vexnum; j++)
        {
            if (g->arcs[i][j] == 1 && !visited[g->vexs[j]] && !founded[g->vexs[j]])
            {
                q.push(g->vexs[j]);
                founded[g->vexs[j]] = 1;
            }
        }
    }
    cout << endl;
}

int LocateVex(MGraph g, vextype v)
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

void floyd(MGraph g, int a, int b)
{
    int i, j, k;
    for (i = 0; i < g->vexnum; i++)
    {
        for (j = 0; j < g->vexnum; j++)
        {
            if (i == j)
            {
                path[i][j] = -1;
            }
            else
            {
                path[i][j] = j;
            }
        }
    }
    for (k = 0; k < g->vexnum; k++)
    {
        for (i = 0; i < g->vexnum; i++)
        {
            for (j = 0; j < g->vexnum; j++)
            {
                if (dis[i][j] > dis[i][k] + dis[k][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }
    a = LocateVex(g, a + '0');
    b = LocateVex(g, b + '0');
    cout << "顶点" << a + 1 << "到顶点" << b + 1 << "的最短路径为：";
    int temp = a;
    while (temp != b)
    {
        cout << g->vexs[temp] << "->";
        temp = path[temp][b];
    }
    cout << g->vexs[temp] << endl;
}

void TopologicalSort(MGraph g)
{
    int indegree[Vex_N] = {0};
    stack<vextype> st;
    for (int i = 0; i < g->vexnum; i++)
    {
        for (int j = 0; j < g->vexnum; j++)
        {
            if (g->arcs[i][j] == 1)
            {
                indegree[j]++;
            }
        }
    }
    for (int i = 0; i < g->vexnum; i++)
    {
        if (indegree[i] == 0)
        {
            st.push(g->vexs[i]);
        }
    }
    while (!st.empty())
    {
        vextype v = st.top();
        st.pop();
        cout << v << " ";
        int i = LocateVex(g, v);
        for (int j = 0; j < g->vexnum; j++)
        {
            if (g->arcs[i][j] == 1)
            {
                indegree[j]--;
                if (indegree[j] == 0)
                {
                    st.push(g->vexs[j]);
                }
            }
        }
    }
    cout << endl;
}

void Prim(MGraph g)
{
    int parent[g->vexnum];
    int key[g->vexnum];
    bool mstSet[g->vexnum];

    for (int i = 0; i < g->vexnum; i++)
    {
        key[i] = 0x3f3f3f3f;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < g->vexnum - 1; count++)
    {
        int u = -1;
        int minKey = 0x3f3f3f3f;
        for (int i = 0; i < g->vexnum; i++)
        {
            if (!mstSet[i] && key[i] < minKey)
            {
                u = i;
                minKey = key[i];
            }
        }
        mstSet[u] = true;

        for (int v = 0; v < g->vexnum; v++)
        {
            if (g->arcs[u][v] && !mstSet[v] && g->arcs[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = g->arcs[u][v];
            }
        }
    }

    for (int i = 1; i < g->vexnum; i++)
    {
        cout << g->vexs[parent[i]] << "-" << g->vexs[i] << " ";
    }
    cout << endl;
}

int main()
{
    int i;
    char vi, vj;
    char v1, v2;
    int v, e;
    int k;

    int cnt = 3;
    while (cnt--)
    {
        cout << "现在是第" << 3 - cnt << "次循环" << endl;
        cout << "请输入图的种类：（0：无向图，1：有向图）" << endl;
        cin >> k;
        cout << "请输入顶点数和边数：" << endl;
        cin >> v >> e;
        MGraph g = CreateGraph(v, e, k);
        ShowGraph(g, v);
        if (g->kind == 0)
        {
            if (cnt == 2)
            {
                cout << "从哪个顶点开始深度优先遍历：" << endl;
                cin >> v1;
                DFS(g, v1, visited);
                cout << endl;
                cout << "从哪个顶点开始广度优先遍历：" << endl;
                cin >> v2;
                BFS(g, v2, visited);
                int a, b;
                cout << "要查询哪两个顶点的最短路径：" << endl;
                cin >> a >> b;
                floyd(g, a, b);
            }
            if (cnt == 0)
            {
                cout << "最小生成树为：" << endl;
                Prim(g);
            }
        }
        else if (k == 1)
        {
            cout << "拓扑排序结果为：" << endl;
            TopologicalSort(g);
        }
    }

    return 0;
}