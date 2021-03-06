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

/* Segtree - range update, range query
 * a - Initializer array. Building is done based on array a[].
 * Check for overflows OR #define int long long!
 * Each function assumes 0-based indexing.
 */
struct node{
    ll val;
    ll lazy;

    node(){
        val = 0;
        lazy = 0;
    }

    void init(int x){
        val = x;
    }

    void merge(node &l, node &r){
        val = l.val + r.val;
    }

    void no_use(){
        /*Fill neutral values that don't affect the answer */
        val = 0;
        lazy = 0;
    }
};

node segtree[N << 2];
ll a[N];

/* Magic happens here! */
void propogate(int num, int start, int end, ll mul){
    segtree[num].val += (end - start + 1) * mul * 1ll;
    if(start != end){
        segtree[num + num + 1].lazy +=  mul;
        segtree[num + num + 2].lazy += mul;
    }
}

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

//Range update. Implemented : add p in range l, r in O(logn).
void update(int num, int start, int end, int l, int r, ll p){
    if(segtree[num].lazy !=0){
        //If current node has updates pending, finish them first and pass on the "laziness" to the children.
        propogate(num, start, end, segtree[num].lazy);
        segtree[num].lazy = 0;
    }
    if(start > end || start > r || end < l) return;
    if(start >= l && end <= r){
        //If current node is fully within range, update it(lazy won't be changed here!!!).
        //Pass the laziness to children.
        propogate(num, start, end, p);
        return;
    }
    int lc = num + num + 1, rc = lc + 1;
    int mid = (start + end) >> 1;
    update(lc, start, mid, l, r, p);
    update(rc, mid + 1, end, l, r, p);
    segtree[num].merge(segtree[lc], segtree[rc]);
}

//Range Query - Returns the answer of query in O(logn) time.
node query(int num, int start, int end, int qs, int qe){
    if(start > qe || end < qs){
        node ret;
        ret.no_use();
        return ret;
    }
    if(segtree[num].lazy != 0){
        //If current node has updates pending, finish them first and pass on the "laziness" to the children.
        propogate(num, start, end, segtree[num].lazy);
        segtree[num].lazy = 0;
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