/*       Tarjan缩点
将有向图中的所有强连通分量缩成一个点
缩完点之后原图就变成了一个DAG图（有向无环图）
模板例题
    给定一个n个点m条边有向图，每个点有一个权值，求一条路径，使路径经过的点权值之和最大。你只需要求出这个权值和。
允许多次经过一条边或者一个点，但是，重复经过的点，权值只计算一次。
解法：对整个图缩完点之后跑拓扑排序DP一下即可
*/
const int maxn = 1e4 + 10;
const int maxm = 1e5 + 10;
int val[maxn];
int Low[maxn],dfn[maxn],Stack[maxn],Belong[maxn],num[maxn];
int Index,top,scc;
bool Instack[maxn];
void Tarjan(int u){
    int v;
    Low[u] = dfn[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u]; ~i; i = edge[i].next){
        v = edge[i].to;
        if(!dfn[v]){
            Tarjan(v);
            if(Low[u] > Low[v]) Low[u] = Low[v];
        }else if(Instack[v] && Low[u] > dfn[v]) Low[u] = dfn[v];
    }
    if(Low[u] == dfn[u]){
        scc++;
        do{
            v = Stack[--top];
            Instack[v] = false;
            Belong[v] = scc;
            num[scc]++;
        }while(v != u);
    }
}
int VAL[maxn],ind[maxn];
int dp[maxn];
vector<int>P[maxn];
void solve(){
    for(int i = 1; i <= N ; i ++) dfn[i] = Instack[i] = num[i] = 0;
    Index = scc = top = 0;
    for(int i = 1; i <= N ; i ++) if(!dfn[i]) Tarjan(i);   //将原图缩点为DAG图
    for(int i = 1; i <= N ; i ++){                         //建DAG图
        VAL[Belong[i]] += val[i];
        for(int j = head[i]; ~j; j = edge[j].next){
            int v = edge[j].to;
            if(Belong[v] != Belong[i]){
                P[Belong[i]].pb(Belong[v]);
                ind[Belong[v]]++;
            }
        }
    }
    queue<int>Q;
    for(int i = 1; i <= scc;i ++){
        if(!ind[i]) Q.push(i);
        dp[i] = VAL[i];
    } 
    int ans = 0; 
    while(!Q.empty()){            //拓扑排序
        int u = Q.front(); Q.pop();
        ans = max(ans,dp[u]);
        for(int i = 0 ; i < P[u].size(); i ++){
            int v = P[u][i];
            ind[v]--;
            dp[v] = max(dp[v],dp[u] + VAL[v]);
            if(!ind[v]) Q.push(v);
        }
    }
    Pri(ans);
    
}
int main(){
    N = read(); M = read(); init();
    for(int i = 1; i <= N ; i ++) val[i] = read();
    for(int i = 1; i <= M ; i ++){
        int u = read(),v = read();
        add(u,v);
    }
    solve();
    return 0;
}