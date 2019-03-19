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
 * DSU on trees. Alternate approach: https://codeforces.com/contest/208/submission/51425361
 * Assumes 0-based indexing.
 */
int n;
int depth[N], sz[N], cnt[N];
vector<int> adj[N];
bool big[N];

//Finds the depth of each node from the root(here 0) and subtree size. 
//Call this before starting with DFS.
void dfs0(int src = 0, int par = -1){
    sz[src] = 1;
    for(int u : adj[src]){
        if(u == par) continue;
        depth[u] = depth[src] + 1;
        dfs0(u, src);
        sz[src] += sz[u];
    }
}

//Perform the addition functionality here.
void add(int src, int par, int x){
    cnt[depth[src]] += x;
    for(int u : adj[src]){
        if(u == par || big[u]) continue;
        add(u, src, x);
    }
}

void dfs(int src, int par, bool keep){
    int mx = -1, bigChild = -1;
    for(int u : adj[src]){
        if(u == par) continue;
        if(sz[u] > mx){
            mx = sz[u];
            bigChild = u;
        }
    }
    for(int u : adj[src]){
        if(u == par || u == bigChild) continue;
        dfs(u, src, false); //Calculate ans for smaller children and clear them.
    }
    if(bigChild != -1){
        big[bigChild] = true;
        dfs(bigChild, src, true); //Calculate the ans for bigChild and save it.
    }
    add(src, par, 1);
    //We now have answer for the subtree of src. Perform the desired operation here.

    if(bigChild != -1) big[bigChild] = false;
    if(!keep) add(src, par, -1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    cin>>n;
    f(i, n - 1){
        int u, v;
        cin>>u>>v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs0();
    return 0;
}