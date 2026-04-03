class Solution {
public:
int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = robots.size();
        
        vector<pair<long long, long long>> rob(n);
        for (int i = 0; i < n; ++i) {
            rob[i] = {robots[i], distance[i]};
        }
        
        sort(rob.begin(), rob.end());
        
        vector<long long> sorted_walls(walls.begin(), walls.end());
        sort(sorted_walls.begin(), sorted_walls.end());
        
        auto count_walls = [&](long long L, long long R) -> int {
            if (L > R) return 0; 
            auto it1 = lower_bound(sorted_walls.begin(), sorted_walls.end(), L);
            auto it2 = upper_bound(sorted_walls.begin(), sorted_walls.end(), R);
            return std::distance(it1, it2);
        };
        
        vector<vector<int>> dp(n, vector<int>(2, 0));
        
        long long P0 = rob[0].first;
        long long D0 = rob[0].second;
        long long R0 = (n > 1) ? min(P0 + D0, rob[1].first) : (P0 + D0);
        
        dp[0][0] = count_walls(P0 - D0, P0);
        dp[0][1] = count_walls(P0, R0);

        for (int i = 1; i < n; ++i) {
            long long Pi = rob[i].first;
            long long Di = rob[i].second;
            
            long long Pi_prev = rob[i-1].first;
            long long Di_prev = rob[i-1].second;
            long long Ri_prev = min(Pi_prev + Di_prev, Pi);
            
            long long Ri = (i < n - 1) ? min(Pi + Di, rob[i+1].first) : (Pi + Di);
            
            int left_optA = dp[i-1][0] + count_walls(max(Pi - Di, Pi_prev + 1), Pi);
            
            int left_optB = dp[i-1][1] + count_walls(max(Pi - Di, Ri_prev + 1), Pi);
            
            dp[i][0] = max(left_optA, left_optB);
            
            int right_optA = dp[i-1][0] + count_walls(Pi, Ri);
            
            int right_optB = dp[i-1][1] + count_walls(max(Pi, Ri_prev + 1), Ri);
            
            dp[i][1] = max(right_optA, right_optB);
        }
        
        return max(dp[n-1][0], dp[n-1][1]);
    }
};