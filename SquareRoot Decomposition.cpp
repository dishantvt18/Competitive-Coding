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
const ll N = (int)5e5 + 5;
const ll LOGN = 19;
const ld PI = 3.14159265358979323846;
inline ll mul(ll a, ll b, ll m = mod) { return (ll)(a * b) % m;}
inline ll add(ll a, ll b, ll m = mod) { a += b; if(a >= m) a -= m; if(a < 0) a += m; return a;}
inline ll power(ll a, ll b, ll m = mod) { if(b == 0) return 1; if(b == 1) return (a % m); ll x = power(a, b / 2, m); x = mul(x, x, m); if(b % 2) x = mul(x, a, m); return x;}
/*
 * SquareRoot Decomposition : Array a[] is the working array.
 * Use scanf and printf for I/O. 
 */
int n, blocksize, q;
vector<int> sortedBlocks[5005];
int a[N];

void update(int num, int start, int end){
    sortedBlocks[num].clear();
    rep(i, start, end){
        sortedBlocks[num].pb(a[i]);
    }
    sort(all(sortedBlocks[num]));
}

/*
 * Returns number less than equal to k in the interval [L,R]
 * Time Complexity : O(sqrt(n)). Use Merge Sort tree instead :p
 */
int query(int L, int R, int k) {
    int from = L/blocksize + 1, to = R/blocksize - 1;
    int ret = 0;
    rep(i, from, to){
        ret += abs(lower_bound(all(sortedBlocks[i]), k) - sortedBlocks[i].end());
    }
    int left_end = (L/blocksize + 1)*blocksize - 1;
    int right_start = (R/blocksize) * blocksize;
    if(L/blocksize == R/blocksize){
        rep(i, L, R) {
            if(a[i] >= k) ret++;
        }
    }
    else{
        rep(i, L, left_end){
            if(a[i] >= k) ret++;
        }
        rep(i, right_start, R){
            if(a[i] >= k) ret++;
        }
    }
    return ret;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    scanf("%d", &n);
    f(i, n) scanf("%d", &a[i]);
    blocksize = static_cast<int>(sqrt(n));
    int blocks = n/blocksize;
    if(n % blocksize) blocks++;
    f(i, blocks) {
        int start = i * blocksize;
        int end = min((i + 1) * blocksize, n) - 1;
        update(i, start, end);
    }
    scanf("%d", &q);
    while(q--){
        int type;
        scanf("%d", &type);
        if(!type){
            int aa, b, c;
            scanf("%d %d %d", &aa, &b, &c);
            aa--, b--;
            printf("%d\n",query(aa, b, c));
        }
        else{
            int aa, b;
            scanf("%d %d", &aa, &b);
            aa--;
            a[aa] = b;
            int num = aa/blocksize;
            int start = num * blocksize;
            int end = min((num + 1) * blocksize, n) - 1;
            update(num, start, end);
        }
    }
    return 0;
}