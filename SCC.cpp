#include<bits/stdc++.h>
using namespace std;
/*#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
/*template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
*/typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll,ll> pl;
typedef pair<int,int> pii;

#define LOCAL 0
#define dbg(x) cout << #x << " is " << x << "\n"
#define gll(x) scanf("%d",&x)
#define gll2(x,y) scanf("%d%d",&x,&y)
#define gll3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define gllarr(arr,n) f(i,n) gll(arr[i]);
#define sz(x) ((int)x.size())
#define s(x) sort(x.begin(),x.end())
#define all(v) v.begin(),v.end()
#define rs(v) { s(v) ; r(v) ; }
#define r(v) {reverse(all(v));}
#define pb push_back
#define f(i,n) for(int i=0;i<n;i++)
#define fr(i,n) for(int i=n-1;i>=0;i--)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define repr(i,a,b) for(int i=a;i>=b;i--)

const ll mod = (ll)1e9 + 7;
const ll inf = (ll)1e16;
const ld eps = 1e-12;
const ll N = (int)1e5 + 5;
const ll LOGN = 19;
const ld PI = 3.14159265358979323846;
inline ll mul(ll a, ll b, ll m = mod) { return (ll)(a * b) % m;}
inline ll add(ll a, ll b, ll m = mod) { a += b; if(a >= m) a -= m; if(a < 0) a += m; return a;}
inline ll power(ll a, ll b, ll m = mod) { if(b == 0) return 1; if(b == 1) return (a % m); ll x = power(a, b / 2, m); x = mul(x, x, m); if(b % 2) x = mul(x, a, m); return x;}

/*
 * adjrev -> reversed adjacency list
 * SCC -> saves number of Strongly Connected Components after the function calls.
 * components -> stores the nodes of all SCCs.
 */
vector<int> adj[N], adjrev[N], components[N];
bool vis[N];
stack<int> S;
int SCC = 0;

/*
 * This method assumes 1-based indexing. For 0-based indexing, change call to dfs and adjacency list in main.
 * It doesn't handle self loops and back edges.
 */
void dfs(int src)
{
    vis[src] = true;
    for(int u : adj[src])
    {
        if(vis[u]) continue;
        dfs(u);
    }
    S.push(src);
}

void dfsrev(int src)
{
    vis[src] = true;
    components[SCC - 1].pb(src);
    for(int u : adjrev[src])
    {
        if(vis[u]) continue;
        dfsrev(u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    int n, m;
    cin>>n>>m;
    f(i, m)
    {
        int u, v;
        cin>>u>>v;
        adj[u].pb(v);
        adjrev[v].pb(u);
    }
    memset(vis, 0, sizeof(vis));
    rep(i,1,n)
    {
        if(!vis[i])
        {
            dfs(i);
        }
    }
    memset(vis, 0, sizeof(vis));
    while(!S.empty())
    {
        int u = S.top();
        S.pop();
        if(vis[u]) {
            continue;
        }
        SCC++;
        dfsrev(u);
    }
    cout<<SCC<<endl;
    f(i, SCC){
        f(j, components[i].size())
            cout<<components[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}