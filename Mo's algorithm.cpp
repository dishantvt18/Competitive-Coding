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
const ll N = (int)3e4 + 5;
const ll LOGN = 19;
const ld PI = 3.14159265358979323846;
inline ll mul(ll a, ll b, ll m = mod) { return (ll)(a * b) % m;}
inline ll add(ll a, ll b, ll m = mod) { a += b; if(a >= m) a -= m; if(a < 0) a += m; return a;}
inline ll power(ll a, ll b, ll m = mod) { if(b == 0) return 1; if(b == 1) return (a % m); ll x = power(a, b / 2, m); x = mul(x, x, m); if(b % 2) x = mul(x, a, m); return x;}

/*
 * Mo's algorithm. Operations are performed on array a.
 * Credits for sort function : https://discuss.codechef.com/questions/119615/query-regarding-mos-algorithm
 */
const int Q = (int)2e5 + 5; //Maximum number of queries.
int n, q, a[N];
int blocksize; //Usually set around k * sqrt(N) where k ~ 1.
ll cans, ans[Q];

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
inline void remove(int x){
    
}

//Modify as per the need of problem. Be careful with modular addition function!
inline void add(int x){
    
}

void mo(){
    blocksize = q/(int)sqrt(n);
    sort(queries, queries + q);
    int curr_l = 0, curr_r = -1;
    cans = 0;
    f(i, q){
        while(curr_l < queries[i].l){
            remove(a[curr_l++]);
        }
        while(curr_l > queries[i].l){
            add(a[--curr_l]);
        }
        while(curr_r < queries[i].r){
            add(a[++curr_r]);
        }
        while(curr_r > queries[i].r){
            remove(a[curr_r--]);
        }
        ans[queries[i].idx] = cans;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    cin>>n;
    f(i, n) cin>>a[i];
    cin>>q;
    f(i, q) queries[i].read(i);
    //Call after scanning all the input.
    mo();
    f(i, q) cout<<ans[i]<<"\n";
    return 0;
}