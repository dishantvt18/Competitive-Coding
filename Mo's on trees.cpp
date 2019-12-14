#include<bits/stdc++.h>
using namespace std;
/*#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
*/typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll,ll> pl;
typedef pair<int,int> pii;

//#define int ll
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

/*  CF Frank Sintara.
 * Mo's algorithm. Operations are performed on array a.
 * Credits for sort function : https://discuss.codechef.com/questions/119615/query-regarding-mos-algorithm
 */
const int Q = (int)1e5 + 5; //Maximum number of queries.
int n, q, val[N];
int blocksize; //Usually set around k * sqrt(N) where k ~ 1.
int cans, ans[Q], vis[N];
ordered_set<pair<int, int> > S;
int mp[N];
vector< pair<int, int> > adj[N];
int timer, st[N], ft[N], a[N << 1]; //a stores the reverse mapping and queries are performed on the array a.
int depth[N], pa[LOGN][N];

void dfs(int src = 0, int par = -1, int dep = 0) {
    a[timer] = src;
    st[src] = timer++;
    pa[0][src] = par;
    depth[src] = dep;
    for(auto &it: adj[src]) {
        int u = it.first, w = it.second;
        if(u == par) continue;
        val[u] = w;
        dfs(u, src, dep + 1);
    }
    a[timer] = src;
    ft[src] = timer++;
}

/* Use zero based indexing on trees to use LCA function */
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

struct Query{
    int l, r, idx;

    inline void read(int i){
        cin>>l>>r;
        l--, r--;
        idx = i;
    }

    bool operator < (const Query& q1) const {   //Works better than normal sorting.
        int b1 = l/blocksize, b2 = q1.l/blocksize;
        if(b1 != b2) return b1 < b2;
        return b1 & 1 ? r < q1.r : q1.r < r;
    }
} queries[Q];

//Modify as per the need of problem.
inline void go(int x){
    if(val[x] > N - 1) return;
    if(vis[x]) {
        mp[val[x]]--;
        if(mp[val[x]] == 0) {
            S.erase(S.find({val[x], 1}));
        }
    }
    else {
        mp[val[x]]++;
        S.insert({val[x], 1});
    }
    vis[x] ^= 1;
}

int findans() {
    //auto it = *S.begin();
    //if(it.first != 0) return 0;
    int ans = -1;
    int low = 0, high = N;
    while(low <= high) {
        int mid = (low + high) >> 1;
        if(S.order_of_key({mid, -1}) != mid) {
            ans = mid;
            high = mid - 1;
        }
        else low = mid + 1;
    }
    return ans;
}

void mo(){
    blocksize = (int)sqrt(timer);
    sort(queries, queries + q);
    int curr_l = 0, curr_r = -1;
    cans = INT_MAX;
    f(i, q){
        while(curr_l < queries[i].l){
            go(a[curr_l++]);
        }
        while(curr_l > queries[i].l){
            go(a[--curr_l]);
        }
        while(curr_r < queries[i].r){
            go(a[++curr_r]);
        }
        while(curr_r > queries[i].r){
            go(a[curr_r--]);
        }
        ans[queries[i].idx] = findans()-1;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    cin>>n>>q;
    f(i, n - 1) {
        int u, v, w;
        cin>>u>>v>>w;
        u--, v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    val[0] = INT_MAX;
    memset(pa, -1, sizeof(pa));
    dfs();
    for(int i=1; i<LOGN; i++) {
        for(int j=0; j<n; j++) {
            if(pa[i-1][j] != -1) pa[i][j] = pa[i-1][pa[i-1][j]];
        }
    }
    f(i, q) {
        int u, v;
        cin>>u>>v;
        u--, v--;
        if(st[u] > st[v]) swap(u, v);
        int lca = LCA(u, v);
        queries[i].idx = i;
        if(lca == u) {
            queries[i].l = st[u] + 1, queries[i].r = st[v];
            if(u == 0) queries[i].l = st[u];
        }
        else queries[i].l = ft[u], queries[i].r = st[v];
    }
    //Call after scanning all the input.
    mo();
    f(i, q) cout<<ans[i]<<"\n";
    return 0;
}