//Source : https://www.codechef.com/JUNE18B/problems/SHKSTR/
//Easy and better implementation : http://codeforces.com/contest/514/submission/9959117
//Brilliant article : https://threads-iiith.quora.com/Tutorial-on-Trie-and-example-problems
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


//Implemented the functions on my own. May need some optimizations. 
//Contains only insertion and prefix searching atm.
struct Trie{
#define index(c) ((int)c - (int)'a')
    struct node{
        node* children[26];
        bool isEnd;
        node(){
            f(i,26)
                children[i] = NULL;
            isEnd = false;
        }
    };

    node* globalRoot;

    Trie(){
        globalRoot = new node;
    }

    void insert(string s)
    {
        node* root = globalRoot;
        f(i,s.length())
        {
            if(root->children[index(s[i])] == NULL)
            {
                root->children[index(s[i])] = new node;
                root = root->children[index(s[i])];
            }
            else
            {
                root = root->children[index(s[i])];
            }
            if(i == s.length() - 1)
                root->isEnd = true;
        }
    }

    string search(string s)
    {
        string ret;
        node* root = globalRoot;
        f(i,s.length())
        {
            if(root->children[index(s[i])] == NULL)
                break;
            else
            {
                root = root->children[index(s[i])];
                ret += s[i];
            }
        }
        //cout<<"INSIDE "<<ret<<endl;
        while(!root->isEnd)
        {
            //cout<<"DEB: "<<ret<<endl;
            bool brk = true;
            f(i,26)
            {
                if(root->children[i] != NULL)
                {
                    brk = false;
                    ret += (i + 'a');
                    root=  root->children[i];
                    break;
                }
            }
            if(brk)
                break;
        }
        return ret;
    }

#undef index
};

int n,q;
string s[N];
string min_upto[N];
vector< pair< int, pair<string,int> > > sorted_queries;
string ans[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    cin>>n;
    f(i,n)
    {
        cin>>s[i];
        if(i == 0)
            min_upto[i] = s[i];
        else
            min_upto[i] = min(min_upto[i - 1], s[i]);
    }
    cin>>q;
    f(i,q)
    {
        int u;
        string p;
        cin>>u>>p;
        sorted_queries.pb(make_pair(u,make_pair(p,i)));
    }
    sort(all(sorted_queries));
    int prev = 0;
    Trie trie;
    f(tt,q) {
        int upto = sorted_queries[tt].first;
        string find = sorted_queries[tt].second.first;
        int at = sorted_queries[tt].second.second;
        //cout<<upto<<" ";
        //sort(s, s + upto);
        rep(i, prev, upto - 1) {
            trie.insert(s[i]);
        }
        string ret = trie.search(find);
        if (ret.empty())
        {
            ans[at] = min_upto[upto - 1];
        }
        else
            ans[at] = ret;
        prev = upto;
    }
    f(i,q)
        cout<<ans[i]<<endl;
    return 0;
}