// 2022.04.09
// 实质是求：是否能够取出数组中的一些数，使得他们的和为sum//2
// 可转换为0-1背包问题：
//     假设我们有一个最大承重为sum//2的背包，一组重量和价值都为nums的商品。
// 求解这个背包能装载的商品的最大价值。
//     因为所有的商品价值和重量相等，所以理论上背包所承载商品的最大价值不会超过最大承重sum//2。
// 如果nums里存在一组数的和为sum//2，那么背包一定能被塞满，并且最后背包里商品价值和为sum//2。
// 反之，背包能承载的商品最大价值不为sum//2。
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        vector<int> dp(10001, 0);
        for(int i = 0; i < nums.size(); i++){
            sum += nums[i];
        }
        if(sum % 2 == 1){
            return false;
        }
        int target = sum / 2;
        for(int i = 0; i < nums.size(); i++){
            for(int j = target; j >= nums[i]; j--){
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }
        if(dp[target] == target){
            return true;
        }
        return false;
    }
};