#include <vector>
#include <algorithm>

class Solution {
public:
    int solveRec(std::vector<int>& coins, int amount) {
        if(amount == 0)
            return 0;
        
        if(amount < 0)
            return std::numeric_limits<int>::max();
        
        int mini = std::numeric_limits<int>::max();
        for(int i=0; i<coins.size(); i++) {
            int ans = solveRec(coins, amount-coins[i]);
            if(ans != std::numeric_limits<int>::max())
                mini = std::min(mini, ans+1);
        }
        return mini;
    }

    int solveMem(std::vector<int>& coins, int amount, std::vector<int>& dp) {
        if(amount == 0)
            return 0;
        
        if(amount < 0)
            return std::numeric_limits<int>::max();

        if(dp[amount] != -1) {
            return dp[amount];
        }
        
        int mini = std::numeric_limits<int>::max();
        for(int i=0; i<coins.size(); i++) {
            int ans = solveMem(coins, amount-coins[i], dp);
            if(ans != std::numeric_limits<int>::max())
                mini = std::min(mini, ans+1);
        }

        dp[amount] = mini;
        return mini;
    }

    int coinChange(std::vector<int>& coins, int amount) {
        std::vector<int> dp(amount+1, -1);

        int ans = solveMem(coins, amount, dp);
        if(ans == std::numeric_limits<int>::max())
            return -1;
        else
            return ans;
    }
};