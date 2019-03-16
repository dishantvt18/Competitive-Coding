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
inline ll mul(ll a, ll b, ll m = mod) { return (ll)(a * b) % m;}
inline ll add(ll a, ll b, ll m = mod) { a += b; if(a >= m) a -= m; if(a < 0) a += m; return a;}
inline ll power(ll a, ll b, ll m = mod) { if(b == 0) return 1; if(b == 1) return (a % m); ll x = power(a, b / 2, m); x = mul(x, x, m); if(b % 2) x = mul(x, a, m); return x;}

//Not fully tested
//Source : https://cp-algorithms.com/algebra/fft.html#toc-tgt-6
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd>& a, bool invert){
    int n = a.size();
    if(n == 1) return;
    int half = n >> 1;

    vector<cd> even(half), odd(half);
    for(int i = 0; i * 2 < n; i++) {
        even[i] =  a[2 * i];
        odd[i] = a[2 * i + 1];
    }
    fft(even, invert);
    fft(odd, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for(int i = 0; i * 2 < n; i++) {
        a[i] = even[i] + w * odd[i];
        a[i + half] = even[i] - w * odd[i];
        if(invert){
            //Each step of recursion divide by 2 => logn steps will incur division by n.
            a[i] /= 2;
            a[i + half] /= 2;
        }
        w *= wn;
    }
}

//Works only for integer co-efficient polynomials.
//**Remember to change to ll or other data types if needed.**
vector<ll> multiply(vector<ll>& a, vector<ll>& b){
    vector<cd> fa(all(a)), fb(all(b));
    int n = 1;
    while(n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for(int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> res(n);
    //Check this -> it can be written as (int)(fa[i].real + 0.5). Figure out which is better!
    for(int i = 0; i < n; i++)
        res[i] = round(fa[i].real());
    return res;
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