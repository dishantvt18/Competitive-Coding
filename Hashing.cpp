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
 * String Hashing - b1 and b2 are base. They should be prime and greater than range of characters in input string.
 * Implementation details - https://codeforces.com/contest/182/submission/48936522
 */
const int b1 = 31, b2 = 53;
const ll mod1 = (ll)1e9 + 7, mod2 = (ll)1e9 + 9;

struct shash{
    vector<ll> h1, h2, inv1, inv2;

    void init(int n) {
        h1.resize(n, 0);
        h2.resize(n, 0);
        inv1.resize(n, 0);
        inv2.resize(n, 0);
    }

    shash(string &s) {
        int n = s.length();
        init(n);
        ll bp1 = 1, bp2 = 1;
        f(i, n){
            h1[i] = mul((s[i] - 'a' + 1), bp1, mod1);
            h2[i] = mul((s[i] - 'a' + 1), bp2, mod2);
            if(i != 0) {
                h1[i] = add(h1[i], h1[i - 1], mod1);
                h2[i] = add(h2[i], h2[i - 1], mod2);
            }
            inv1[i] = power(bp1, mod1 - 2, mod1);
            inv2[i] = power(bp2, mod2 - 2, mod2);
            bp1 = mul(bp1, b1, mod1);
            bp2 = mul(bp2, b2, mod2);
        }
    }

    pair<ll, ll> get_hash(int l, int r){
        ll ff = h1[r], ss = h2[r];
        if(l != 0){
            ff = add(ff, -h1[l - 1], mod1);
            ff = mul(ff, inv1[l], mod1);
            ss = add(ss, -h2[l - 1], mod2);
            ss = mul(ss, inv2[l], mod2);
        }
        return {ff, ss};
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }

    return 0;
}