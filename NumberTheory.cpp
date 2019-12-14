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

struct NumberTheory{
    /*  Input parameters  */
    ll mod = (ll)1e9 + 7;                   //The keyyyy xD
    ll n = (int)1e5;                        //Size of isPrime Array.

    /*  Output Parameters  */
    ll x;                                   //Stores the co-efficient of A in Extended Euclidean Algo.
    ll y;                                   //Stores the co-efficient of B in Extended Euclidean Algo.
    ll gcd;                                 //Stores the gcd obtained by Extended Euclidean Algo.
    vector<bool> isPrime;                   //Marks true if i is prime number.
    vector<int> primes;                     //Can be used to store primes upto n.
    vector<int> minprime;                   //Stores the value of minimum prime factor of index
    vector<ll> SegmentedPrimes;             //Stores the prime in range L to R.

    /*  Basic methods  */
    //Modular Addition of a and b.
    ll add(ll a, ll b)
    {
        a += b;
        if(a >= mod)
            a -= mod;
        if(a < 0)
            a += mod;
        return a;
    }

    //Modular multiplication of a and b.
    ll mul(ll a, ll b)
    {
        return ((a%mod * b%mod)%mod);
    }

    /*
     *  What if power is large? Take power and all involving calculations with respect to (mod - 1).
     *   Why? By Fermat's Li'l theorem : a ^ (m - 1) ~ 1 (mod m). What if m = mod, result doesn't hold if we take exponent % mod. Interesting :)
     */
    //Computes (Base^power)%mod in O(log(power)) time.
    ll ModularExpo(ll base, ll power)
    {
        ll ans = 1;
        while(power){
            if(power & 1)
                ans = ans%mod * base%mod;
            base = base%mod * base%mod;
            power /= 2;
        }
        return ans % mod;
    }

    /*  Methods to compute GCD  */
    //Calculates gcd of A and B in O(log(max(A,B)) time.
    ll Euclid(ll A, ll B)
    {
        if(B == 0)
            return A;
        
        return Euclid(B,A%B);
    }

    //Calcuates co-efficients x,y and gcd of equation : Ax + By = gcd in O(log(max(A,B)) time.
    //Be mindful : It doesn't return anything. Just stores value in appropriate variables.
    void ExtendedEuclid(ll A, ll B)
    {
        if(B == 0) {
            gcd = A;
            x = 1;
            y = 0;
        }
        else {
            ExtendedEuclid(B, A % B);
            ll temp = x;
            x = y;
            y = temp - (A / B) * y;
        }
    }

    /*  Methods to compute Modular Inverse of a number  */
    //Calculates the modular inverse of A in O(log(max(A,mod)) time.
    //A and mod needs to be coprime. If mod is prime, use Fermat approach instead!
    ll ModInverseByExtended(ll A)
    {
        ExtendedEuclid(A,mod);
        return (x%mod + mod)%mod;
    }

    //Calculates the modular inverse of A in O(log(mod)) time.
    //mod needs to be prime for applying this method.
    ll ModInverseByFermat(ll A)
    {
        return ModularExpo(A,mod-2);
    }

    /*  Sieves  */
    //Calculates all prime number upto n and is marked as true in isPrime array if it is prime.
    //Time Complexity : O(nloglogN)
    void SieveOfEratosthenes()
    {
        isPrime.resize(n + 2, true);
        isPrime[0] = false;
        isPrime[1] = false;
        for(ll i = 2; i * i <= n; i++)
        {
            if(isPrime[i])
            {
                for(ll j = i * i; j <= n; j += i)
                    isPrime[j] = false;
            }
        }
        /* Uncomment this lines for storing the primes upto n in primes array */
        f(i,n+1)
        {
            if(isPrime[i])
                primes.pb(i);
        }
    }

    //Calculates primes from L to R and stores them in Segmented Primes array.
    //Beware of data type. Numbers can be large enough to generate overflow.
    void SegmentedSieve(ll L, ll R)
    {
        //Call this in main if multiple queries exist. ** Be cautious to clear the SegmentedPrimes vector after each query. **
        //Uncomment the pushing of primes in Sieve.
        n = (ll)sqrt(R);
        SieveOfEratosthenes();
        ll sz = R - L + 1;
        bool check[sz];
        memset(check,true,sizeof(check));
        for(ll i : primes)
        {
            ll start = L/i * i;
            if(i > (ll)sqrt(R))
                break;
            if(start < L)
                start += i;
            ll end = R;
            for(ll j = start; j <= end; j += i)
            {
                check[j - L] = false;
            }
            if(start == i)
                check[i - L] = true;
        }
        if(L == 1)
            check[0] = false;
        for(ll i = 0; i < sz; i++)
        {
            if(check[i])
                SegmentedPrimes.pb(i + L);
        }
    }

    /*  Factorization methods   */
    //Returns vector of Prime factors of n in O(sqrt(n)) time.
    //Beware : It won't contain 1! Overflow may occur.
    vector<ll> PrimeFactorize(ll n)
    {
        vector<ll> ret;
        for(ll i = 2; i * i <= n; i++)
        {
            while(n % i == 0)
            {
                ret.pb(i);
                n /= i;
            }
        }
        if(n != 1)
            ret.pb(n);
        return ret;
    }

    //Calculates the minimum prime factor for each number and stores it in minprime array.
    void CalculateMinPrime(int n)
    {
        minprime.resize(n+2,0);
        for(int i = 2; i * i <= n; i++)
        {
            if(minprime[i] == 0)
            {
                for(int j = i * i; j <= n; j += i)
                {
                    if(minprime[j] == 0)
                        minprime[j] = i;
                }
            }
        }               
        rep(i,2,n)
        {
            if(minprime[i] == 0)
                minprime[i] = i;
        }
    }

    //Returns Prime Factors of n in O(log(n)) time.
    //Useful only if n is around 1e6. We need to make array of size n.
    vector<int> PrimeFactorizeinlogn(int n)
    {
        //Call this in main if multiple queries exist.
        CalculateMinPrime(n);
        vector<int> ret;
        while(n != 1)   
        {
            ret.pb(minprime[n]);
            n /= minprime[n];
        }
        return ret;
    }

    //Euler's Totient Function : Returns number of co-prime numbers of n.
    ll phi(int val)
    {
        //Call this function in main if multiple queries exist.
        n = (int)1e5 + 2;           //Assign n as 1 more than maximum n
        SieveOfEratosthenes();
        ll num = val;
        for(ll i = 0; primes[i] * primes[i] <= val; i++)
        {
            if(val % primes[i] == 0)
            {
                num -= (num/primes[i]);
                while(val % primes[i] == 0)
                    val /= primes[i];
            }
        }
        if(val > 1)
            num -= (num/val);
        return num;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (LOCAL) {
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\input.txt", "r", stdin);
        freopen("C:\\Users\\Dishant\\Desktop\\Collection-DEV c++\\output.txt", "w", stdout);
    }
    NumberTheory solve;
    
    return 0;
}