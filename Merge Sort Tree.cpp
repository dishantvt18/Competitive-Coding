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

vector<ll> segtree[N << 2];
ll a[N], junk[N];

void build(int node, int start, int end)
{
    if(start == end)
    {
        segtree[node].pb(a[start]);
        return;
    }
    int mid = (start + end) >> 1;
    int lc = (node << 1) + 1, rc = lc + 1;
    build(lc,start, mid);
    build(rc, mid + 1, end);
    merge(all(segtree[lc]), all(segtree[rc]), back_inserter(segtree[node]));
}

ll query(int node, int start, int end, int qs, int qe, ll val)
{
    if(end < qs || start > qe || start > end)
        return 0;
    else if(start >= qs && end <= qe)
        return abs(segtree[node].end() - upper_bound(all(segtree[node]), val));
    int mid = (start + end) >> 1;
    int lc = (node << 1) + 1, rc = lc + 1;
    return query(lc, start, mid, qs, qe, val) + query(rc, mid + 1, end, qs, qe, val);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    ll n, t;
    cin>>n>>t;
    /* Here junk is the actual array and a is the presum array */
    f(i, n) cin>>junk[i];
    a[0] = junk[0];
    rep(i, 1, n - 1) a[i] = a[i - 1] + junk[i];
    build(0, 0, n - 1);
    ll ans = 0ll;
    f(i, n){
        if(a[i] < t) ans++;
        ans += query(0, 0, n - 1, 0, i - 1, a[i] - t);
    }
    cout<<ans<<endl;
    return 0;
}