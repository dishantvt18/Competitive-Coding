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

vector< pair<int, pair<int,int> > > edges;
int par[N], sz[N];

struct DSU{
    void init()
    {
        f(i, N) {
            par[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x){
        while(par[x] != x)
            x = par[x];
        return x;
    }

    void merge(int x, int y) {
        int u = find(x);
        int v = find(y);
        if (sz[u] <= sz[v])
        {
            par[u] = par[v];
            sz[v] += sz[u];
        }
        else
        {
            par[v] = par[u];
            sz[u] += sz[v];
        }
    }
};

ll kruskal()
{
    ll ret = 0ll;
    DSU dsu;
    dsu.init();
    for(auto it : edges)
    {
        int w = it.first, u = it.second.first, v = it.second.second;
        int par_u = dsu.find(u), par_v = dsu.find(v);
        if(par_u == par_v) continue;
        ret += w;
        dsu.merge(u,v);
    }
    return ret;
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
        int u, v, w;
        cin>>u>>v>>w;
        edges.pb({w,{u,v}});
    }
    sort(all(edges));
    cout<<kruskal()<<endl;
    return 0;
}