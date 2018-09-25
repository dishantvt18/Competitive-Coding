/*
    Article : http://codeforces.com/blog/entry/58316
    Problem : http://codeforces.com/problemset/problem/923/B
*/
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
#define gll3(x,y,z) scanf("%d%d%d",&x,&y,&y)
#define gllarr(arr,n) f(i,n) gll(arr[i]);
#define sz(x) ((int)x.size())
#define s(x) sort(x.begin(),x.end())
#define all(v) v.begin(),v.end()
#define rs(v) { s(v) ; r(v) ; }
#define r(v) {reverse(all(v));}
#define pb push_back
#define F first
#define S second
#define f(i,n) for(int i=0;i<n;i++)
#define fr(i,n) for(int i=n-1;i>=0;i--)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define repr(i,a,b) for(int i=a;i>=b;i--)

const ll mod = 1000000007;
const ll inf = (ll)1e17;
const ld eps = 1e-12;
const ll N = (int)1e5+5;
const ll LOGN = 19;
const ld PI = 3.14159265358979323846;
ll mul(ll a, ll b, ll m = mod) { return (ll)(a * b) % m;}
ll add(ll a, ll b, ll m = mod) { a += b; if(a >= m) a -= m; if(a < 0) a += m; return a;}
ll power(ll a, ll b, ll m = mod) { if(b == 0) return 1; if(b == 1) return (a % m); ll x = power(a, b / 2, m); x = mul(x, x, m); if(b % 2) x = mul(x, a, m); return x;}

struct VeniceSet{
    multiset<ll> S;
    ll water_level = 0;
    void add(ll val)
    {
        S.insert(val + water_level);
    }
    void remove(ll val)
    {
        S.erase(S.find(val + water_level));
    }
    void updateAll(ll val)
    {
        water_level += val;
    }
    ll getMin()
    {
        return *S.begin() - water_level;
    }
    int size()
    {
        return S.size();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    int n;
    cin>>n;
    ll sz[n];
    ll temp[n];
    f(i,n)
        cin>>sz[i];
    f(i,n)
        cin>>temp[i];
    VeniceSet mySet;
    f(i,n)
    {
        //cout<<i<<" "<<mySet.size()<<endl;
        mySet.add(sz[i]);
        mySet.updateAll(temp[i]);
        ll ans = (ll)temp[i] * (ll)mySet.size();
        while(mySet.getMin() < 0 && mySet.size() > 0)
        {
            ll sub = mySet.getMin();
            ans += sub;
            mySet.remove(sub);
        }
        cout<<ans<<" ";
    }
    return 0;
}