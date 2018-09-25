//Trie with bits! Beautiful implementation.
//Source : 706D Codeforces
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

const ll mod = 1000000007;
const ll inf = (ll)1e17;
const ld eps = 1e-12;
const ll N = (int)1e5+5;
const ll LOGN = 19;
const ld PI = 3.14159265358979323846;
ll mul(ll a, ll b, ll m = mod) { return (ll)(a * b) % m;}
ll add(ll a, ll b, ll m = mod) { a += b; if(a >= m) a -= m; if(a < 0) a += m; return a;}
ll power(ll a, ll b, ll m = mod) { if(b == 0) return 1; if(b == 1) return (a % m); ll x = power(a, b / 2, m); x = mul(x, x, m); if(b % 2) x = mul(x, a, m); return x;}


struct Trie{
#define index(c) ((int)c - (int)'0')
    struct node{
        node* children[2];
        int cnt;
        node(){
            f(i,2)
                children[i] = NULL;
            cnt = 0;
        }
    };

    node* globalRoot;

    Trie(){
        globalRoot = new node;
    }

    void insert(string s)
    {
        node* root = globalRoot;
        f(i, s.length())
        {
            if(root->children[s[i] - '0'] == NULL)
            {
                root->children[s[i] - '0'] = new node;
            }
            root=root->children[s[i] - '0'];
            root->cnt++;
        }
    }

    void remove(string s)
    {
        node* root = globalRoot;
        f(i, s.length())
        {
            root = root->children[index(s[i])];
            root->cnt--;
        }
    }

    ll search(string s)
    {
        ll ret = 0;
        string to;
        node* root = globalRoot;
        f(i, s.length())
        {
            int bit = (index(s[i]) ^ 1);
            if(root->children[bit] != NULL && root->children[bit]->cnt > 0) {
                root = root->children[bit];
                to += '1';
            }
            else if(root->children[(bit ^ 1)] != NULL && root->children[(bit) ^ 1]->cnt > 0){
                root = root->children[(bit ^ 1)];
                to += '0';
            }
            else{
              return stoi(s, nullptr, 2);
            }
        }
        ret = stoi(to, nullptr, 2);
        ret = max(ret, (ll)stoi(s, nullptr, 2));
        return ret;
    }

#undef index
};

int q;
map<int, int> mp;
Trie trie;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    cin>>q;
    while(q--)
    {
        char c;
        int x;
        cin>>c>>x;
        if(c == '+') {
            if(mp.find(x) == mp.end())
            {
                string s = bitset<33>(x).to_string();
                trie.insert(s);
            }
            mp[x]++;
        }
        else if(c == '-') {
            if(mp[x] == 1)
            {
                string s = bitset<33>(x).to_string();
                trie.remove(s);
            }
            mp[x]--;
            if(mp[x] == 0) mp.erase(x);
        }
        else {
            string s = bitset<33>(x).to_string();
            cout<<trie.search(s)<<endl;
        }
    }
    return 0;
}