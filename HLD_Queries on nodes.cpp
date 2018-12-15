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

/* HLD when queries are related to nodes.
 ***0-based indexing** for input is must.
 * Code for question : https://www.spoj.com/problems/QTREE3/
 */
int n, q, ptr;
vector<int> adj[N];
int chainNo, chainInd[N], chainHead[N], posInBase[N], base[N], c[N], revmap[N];
int depth[N], pa[LOGN][N], sz[N];


/* Segtree - point update, range query
 * a - Initializer array. Building is done based on array a[].
 * Each function assumes 0-based indexing.
 */
struct node{
    ll val;
    ll pos;

    node(){
        val = -1;
        pos = INT_MAX;
    }

    void init(ll x) {
        if(base[x] == 1) {
            val = revmap[x];
            pos = x;
        }
        else{
            val = -1;
            pos = INT_MAX;
        }
    }

    void merge(node &l, node &r){
        if(l.pos > r.pos){
            val = r.val;
            pos = r.pos;
        }
        else{
            val = l.val;
            pos = l.pos;
        }
    }

    void no_use() {
        val = -1;
        pos = INT_MAX;
    }
};

node segtree[N << 2];

void build(int num, int start, int end){
    if(start == end){
        segtree[num].init(start);
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
        segtree[num].init(idx);
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

void HLD(int src = 0, int par = -1){
    if(chainHead[chainNo] == -1) chainHead[chainNo] = src;
    chainInd[src] = chainNo;
    posInBase[src] = ptr;
    base[ptr++] = c[src];

    int sc = -1, curr = -1;
    for(int i : adj[src]){
        curr++;
        if(i == par) continue;
        if(sc == -1 || sz[sc] < sz[i]){
            sc = i;
        }
    }
    if(sc != -1) HLD(sc, src);
    curr = -1;
    for(int i : adj[src]){
        curr++;
        if(i == par) continue;
        if(sc == i) continue;
        chainNo++;
        HLD(i, src);
    }
}

//Here, v must be ancestor of u.
int query_up(int u, int v){
    if(u == v) {
        if(c[u] == 1) return u;
        return -1;
    }
    int uchain, vchain = chainInd[v], ret = -1, dist = INT_MAX;
    while(1){
        uchain = chainInd[u];
        if(uchain == vchain){
            if(u == v){
                if(c[u] == 1) return u;
                return ret;
            }
            node qq = query(0, 0, ptr, posInBase[v], posInBase[u]);
            ll ret_node = qq.val;
            ll ret_dist = qq.pos;
            if(ret_dist < dist) {
                dist = (int)ret_dist;
                ret = (int)ret_node;
            }
            return ret;
        }
        node qq = query(0, 0, ptr, posInBase[chainHead[uchain]], posInBase[u]);
        ll ret_node = qq.val;
        ll ret_dist = qq.pos;
        if(ret_dist < dist) {
            dist = (int)ret_dist;
            ret = (int)ret_node;
        }
        u = chainHead[uchain];
        u = pa[0][u];
    }
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
    t = 1;
    while(t--){
        init();
        cin>>n>>q;
        f(i, n - 1){
            int u, v;
            cin>>u>>v;
            u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs();
        HLD();
        f(i, n){
            revmap[posInBase[i]] = i;
        }
        build(0, 0, ptr);
        for(int i=1; i<LOGN; i++) {
            for (int j = 0; j < n; j++)
                if (pa[i - 1][j] != -1)
                    pa[i][j] = pa[i - 1][pa[i - 1][j]];
        }
        while(q--) {
            int type, u;
            cin>>type>>u;
            u--;
            if(type == 0){
                c[u] ^= 1;
                update(0, 0, ptr, posInBase[u], c[u]);
            }
            else{
                int v = query_up(u, 0);
                if(v != -1) v++;
                cout<<v<<"\n";
            }
        }
    }
    return 0;
}