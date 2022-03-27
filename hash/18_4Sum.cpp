class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if(nums.size() == 0){
            return res;
        }
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size(); i++){
            if(i > 0 && nums[i] == nums[i - 1]){
                continue;
            }
            for(int j = i + 1; j < nums.size(); j++){
                if(j > i + 1 && nums[j] == nums[j - 1]){
                    continue;
                }
                int temp = target - nums[i] - nums[j];
                int left = j + 1;
                int right = nums.size() - 1;
                while(left < right){
                    if(nums[left] + nums[right] > temp){
                        right--;
                        while(left < right && nums[right] == nums[right + 1]){
                            right--;
                        }
                    }
                    else if(nums[left] + nums[right] < temp){
                        left++;
                        while(left < right && nums[left] == nums[left - 1]){
                            left++;
                        }
                    }
                    else{
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while(left < right && nums[right] == nums[right - 1]){
                            right--;
                        }
                        while(left < right && nums[left] == nums[left + 1]){
                            left++;
                        }
                        right--;
                        left++;
                    }
                }
            }
        }
        return res;
    }
};