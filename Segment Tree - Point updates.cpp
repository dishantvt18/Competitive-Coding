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
ll a[N];

void build(int num, int start, int end){
    if(start == end){
        segtree[num].init(a[start]);
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
        a[idx] = val;
        segtree[num].init(a[idx]);
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    
    return 0;
}