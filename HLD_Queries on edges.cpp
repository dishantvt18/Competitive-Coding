//Source : https://github.com/anudeep2011/programming/blob/master/qtree.cpp
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

/* HLD - Queries are based on edges. 
 ***0-based indexing** for input is must.
 * Code for question : https://www.spoj.com/problems/QTREE/
 * Easy way : Can also be solved by assigning values of each edge to the child node on rooting.
 */
int n, ptr;
vector<int> adj[N], costs[N], idx[N];
int chainNo, chainInd[N], chainHead[N], posInBase[N], base[N], otherEnd[N];
int depth[N], pa[LOGN][N], sz[N];


/* Segtree - point update, range query
 * a - Initializer array. Building is done based on array a[].
 * Each function assumes 0-based indexing.
 */
struct node{
    ll val;

    node(){
        val = 0;
    }

    void init(ll x) {
        val = x;
    }

    void merge(node &l, node &r){
        val = max(l.val, r.val);
    }

    void no_use() {
        val = LLONG_MIN;
    }
};

node segtree[N << 2];

void build(int num, int start, int end){
    if(start == end){
        segtree[num].init(base[start]);
        return;
    }
    int lc = num + num + 1, rc = lc + 1;
    int mid = (start + end) >> 1;
    build(lc, start, mid);
    build(rc, mid + 1, end);
    segtree[num].merge(segtree[lc], segtree[rc]);
}

//Point update - Here : change value at index = idx to val -> a[idx] = val.
//In case of tight TL, create idx and val as global variables.
void update(int num, int start, int end, int idx, int val){
    if(start == end){
        base[idx] = val;
        segtree[num].init(base[idx]);
        return;
    }
    int lc = num + num + 1, rc = lc + 1;
    int mid = (start + end) >> 1;
    if(start <= idx && idx <= mid) update(lc, start, mid, idx, val);
    else update(rc, mid + 1, end, idx, val);
    segtree[num].merge(segtree[lc], segtree[rc]);
}

//Range Query - Returns the answer of query in O(logn) time.
node query(int num, int start, int end, int qs, int qe){
    if(start > qe || end < qs){
        node junk;
        junk.no_use();
        return junk;
    }
    if(start >= qs && end <= qe){
        return segtree[num];
    }
    int lc = num + num + 1, rc = lc + 1;
    int mid = (start + end) >> 1;
    node lf = query(lc, start, mid, qs, qe);
    node rg = query(rc, mid + 1, end, qs, qe);
    node ret;
    ret.merge(lf, rg);
    return ret;
}

void init(){
    chainNo = 0;
    f(i, N){
        adj[i].clear();
        costs[i].clear();
        idx[i].clear();
        chainHead[i] = -1;
        f(j, LOGN) pa[j][i] = -1;
    }
}

void dfs(int src = 0, int par = -1, int _depth = 0){
    pa[0][src] = par;
    depth[src] = _depth;
    sz[src] = 1;
    int curr = -1;
    for(int u : adj[src]){
        curr++;
        if(u == par) continue;
        otherEnd[idx[src][curr]] = u;
        dfs(u, src, _depth + 1);
        sz[src] += sz[u];
    }
}

int LCA(int u, int v) {
    if(depth[u] < depth[v]) swap(u,v);
    int diff = depth[u] - depth[v];
    for(int i=0; i<LOGN; i++) if( (diff>>i)&1 ) u = pa[i][u];
    if(u == v) return u;
    for(int i=LOGN-1; i>=0; i--) if(pa[i][u] != pa[i][v]) {
            u = pa[i][u];
            v = pa[i][v];
        }
    return pa[0][u];
}

void HLD(int src = 0, int cost = -1, int par = -1){
    if(chainHead[chainNo] == -1) chainHead[chainNo] = src;
    chainInd[src] = chainNo;
    posInBase[src] = ptr;
    base[ptr++] = cost;

    int sc = -1, ncost = 0, curr = -1;
    for(int i : adj[src]){
        curr++;
        if(i == par) continue;
        if(sc == -1 || sz[sc] < sz[i]){
            sc = i;
            ncost = costs[src][curr];
        }
    }
    if(sc != -1) HLD(sc, ncost, src);
    curr = -1;
    for(int i : adj[src]){
        curr++;
        if(i == par) continue;
        if(sc == i) continue;
        chainNo++;
        HLD(i, costs[src][curr], src);
    }
}

//Here, v must be ancestor of u.
int query_up(int u, int v){
    if(u == v) return 0;
    int uchain, vchain = chainInd[v], ret = -1;
    while(1){
        uchain = chainInd[u];
        if(uchain == vchain){
            if(u == v) break;
            ret = max(ret, (int)query(0, 0, ptr, posInBase[v] + 1, posInBase[u]).val);
            break;
        }
        ret = max(ret, (int)query(0, 0, ptr, posInBase[chainHead[uchain]], posInBase[u]).val);
        u = chainHead[uchain];
        u = pa[0][u];
    }
    return ret;
}

void change(int id, int val){
    int u = otherEnd[id];
    update(0, 0, ptr, posInBase[u], val);
}

int query_HLD(int u, int v){
    int lca = LCA(u, v);
    return max(query_up(u, lca), query_up(v, lca));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    int t;
    cin>>t;
    while(t--){
        init();
        cin>>n;
        f(i, n - 1){
            int u, v, w;
            cin>>u>>v>>w;
            u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
            costs[u].pb(w);
            costs[v].pb(w);
            idx[u].pb(i);
            idx[v].pb(i);
        }
        dfs();
        HLD();
        build(0, 0, ptr);
        for(int i=1; i<LOGN; i++) {
            for (int j = 0; j < n; j++)
                if (pa[i - 1][j] != -1)
                    pa[i][j] = pa[i - 1][pa[i - 1][j]];
        }
        while(1){
            string s;
            cin>>s;
            if(s[0] == 'D') break;
            if(s[0] == 'C'){
                int a, b;
                cin>>a>>b;
                a--;
                change(a, b);
            }
            else{
                int a, b;
                cin>>a>>b;
                a--, b--;
                cout<<query_HLD(a, b)<<"\n";
            }
        }
    }
    return 0;
}