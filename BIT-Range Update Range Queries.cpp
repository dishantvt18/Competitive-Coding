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
const ll N = (int)2e5 + 5;
const ll LOGN = 19;
const ld PI = 3.14159265358979323846;
inline ll mul(ll a, ll b, ll m = mod) { return (ll)(a * b) % m;}
inline ll add(ll a, ll b, ll m = mod) { a += b; if(a >= m) a -= m; if(a < 0) a += m; return a;}
inline ll power(ll a, ll b, ll m = mod) { if(b == 0) return 1; if(b == 1) return (a % m); ll x = power(a, b / 2, m); x = mul(x, x, m); if(b % 2) x = mul(x, a, m); return x;}

/*
 * BIT : Range Update and Range Queries
 * Source : https://kartikkukreja.wordpress.com/2013/12/02/range-updates-with-bit-fenwick-tree/
 * Video : https://www.youtube.com/watch?v=kPaJfAUwViY&t=796s
 * bit1[] - stores the sum as usual partial sums.
 */

ll bit1[N], bit2[N];

void init(){
    f(i, N) bit1[i] = bit2[i] = 0;
}

void update(ll bit[], ll idx, ll val){
    while(idx < N){
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

ll query(const ll bit[], ll idx){
    ll ret = 0;
    while(idx){
        ret += bit[idx];
        idx -= (idx & -idx);
    }
    return ret;
}

void range_update(ll L, ll R, ll val){
    update(bit1, L, val);
    update(bit1, R + 1, -val);
    update(bit2, L, val * (L - 1));
    update(bit2, R + 1, -val * R);
}

ll query(ll b){
    return query(bit1, b) * b - query(bit2, b);
}

ll range_query(ll a, ll b){
    return query(b) - query(a - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    int t;
    cin>>t;
    while(t--){
        int n,q;
        cin>>n>>q;
        init();
        while(q--){
            int ty;
            cin>>ty;
            if(!ty){
                ll l, r, v;
                cin>>l>>r>>v;
                range_update(l, r, v);
            }
            else{
                ll l, r;
                cin>>l>>r;
                cout<<range_query(l, r)<<endl;
            }
        }
    }
    return 0;
}