class Solution {
public:
int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size();
        int n = coins[0].size();
        
        const int MIN_VAL = -1e9; 
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(3, MIN_VAL)));
        
        dp[0][0][0] = coins[0][0]; 
        if (coins[0][0] < 0) {
            dp[0][0][1] = 0; 
        }
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                
                if (i == 0 && j == 0) continue; 
                
                for (int k = 0; k < 3; ++k) {
                    
                    int best_prev = MIN_VAL;
                    if (i > 0) best_prev = max(best_prev, dp[i-1][j][k]); 
                    if (j > 0) best_prev = max(best_prev, dp[i][j-1][k]);
                    
                    if (best_prev != MIN_VAL) {
                        dp[i][j][k] = max(dp[i][j][k], best_prev + coins[i][j]);
                    }
                    
            
                    if (coins[i][j] < 0 && k > 0) {
                        int best_prev_skip = MIN_VAL;
                        if (i > 0) best_prev_skip = max(best_prev_skip, dp[i-1][j][k-1]);
                        if (j > 0) best_prev_skip = max(best_prev_skip, dp[i][j-1][k-1]);
                        
                        
                        if (best_prev_skip != MIN_VAL) {
                            dp[i][j][k] = max(dp[i][j][k], best_prev_skip); 
                        }
                    }
                }
            }
        }
        
        return max({dp[m-1][n-1][0], dp[m-1][n-1][1], dp[m-1][n-1][2]});
    }
};