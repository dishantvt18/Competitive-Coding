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
 * Persistent Segment Tree - Built on array a.
 * Here, range sum is implemented of different versions and it supports point updates.
 * Root node of different versions are stored in versions array.
 * Implementation credits : https://www.geeksforgeeks.org/persistent-segment-tree-set-1-introduction/
 * Check Anudeep's blog for more understanding.
 * Sample solution : https://www.spoj.com/status/PSEGTREE,dishant_18/
 */

struct node{
    node *left, *right;
    ll val;
    //Constructors. Fill neutral value to "val" that doesn't affect the answer.
    node() : left(NULL), right(NULL), val(0) {}
    node(node* left, node* right, ll val) : left(left), right(right), val(val) {}
};

int n, q;
ll a[N];
node* version[N];

void build(node* root, int start, int end){
    if(start == end){
        root->val = a[start];
        return;
    }
    int mid = (start + end) >> 1;
    root->left = new node();
    root->right = new node();
    build(root->left, start, mid);
    build(root->right, mid + 1, end);
    root->val = root->left->val + root->right->val;
}

//This function upgrades to new version. Supports point updates.
//Here, a[idx] = val is done.
//Call this by creating new node(curr). Save version root after the call to this function.
void upgrade(node* prev, node* curr, int start, int end, int idx, ll val){
    if(idx > end || idx < start || start > end) return;
    if(start == end){
        //Check this part
        a[idx] = val;
        curr->val = val;
        return;
    }
    int mid = (start + end) >> 1;
    if(idx <= mid){
        //Only left child and its descendents needs to be updated.
        curr->right = prev->right;
        curr->left = new node();
        upgrade(prev->left, curr->left, start, mid, idx, val);
    }
    else{
        //Only right child and its descendents needs to be updated.
        curr->left = prev->left;
        curr->right = new node();
        upgrade(prev->right, curr->right, mid + 1, end, idx, val);
    }
    curr->val = curr->left->val + curr->right->val;
}

ll query(node* root, int start, int end, int qs, int qe){
    if(qs > qe || qe < start || qs > end) {
        //No overlap
        return 0;
    }
    if(start >= qs && end <= qe){
        //Total overlap
        return root->val;
    }
    int mid = (start + end) >> 1;
    return query(root->left, start, mid, qs, qe) + query(root->right, mid + 1, end, qs, qe);
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
    version[0] = new node();
    //Similar thing for upgrade.
    build(version[0], 0, n - 1);
    cin>>q;
    while(q--){
        
    }
    return 0;
}