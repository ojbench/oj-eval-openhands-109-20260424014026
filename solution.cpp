#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 505;

int n;
int adj[MAXN][MAXN];
long long dp[MAXN][MAXN];

// dp[i][j] = number of ways to form a non-crossing tree on nodes from i to j
long long solve(int l, int r) {
    if (l > r) return 1;
    if (l == r) return 1;
    
    if (dp[l][r] != -1) return dp[l][r];
    
    long long result = 0;
    
    // Try each node k in [l+1, r] to connect with l
    for (int k = l + 1; k <= r; k++) {
        if (adj[l][k] == 0) continue;
        
        long long left_ways = solve(l + 1, k - 1);
        long long right_ways = solve(k + 1, r);
        
        result = (result + left_ways * right_ways % MOD) % MOD;
    }
    
    dp[l][r] = result;
    return result;
}

int main() {
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }
    
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    
    memset(dp, -1, sizeof(dp));
    
    // For a circle, we break it by choosing an edge from node 0
    long long ans = 0;
    for (int k = 1; k < n; k++) {
        if (adj[0][k] == 0) continue;
        
        long long left = solve(1, k - 1);
        long long right = solve(k + 1, n - 1);
        
        ans = (ans + left * right % MOD) % MOD;
    }
    
    cout << ans << endl;
    
    return 0;
}
