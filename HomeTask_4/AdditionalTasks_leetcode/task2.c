/* Minimum Subsequence in Non-Increasing Order
https://leetcode.com/problems/minimum-subsequence-in-non-increasing-order/description/ */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minSubsequence(int* nums, int numsSize, int* returnSize) {
    int sum = 0;

    for(int i = 0; i < numsSize; i++){
        sum += nums[i];
        int key = nums[i];
        int j = i - 1;
        while(j >= 0 && nums[j] < key){
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;
    }

    if(nums[0] == nums[numsSize - 1])
        *returnSize = numsSize;
    else
        for(int i = 0, tmpSum = 0; i < numsSize; i++){
            tmpSum += nums[i];
            if(tmpSum > sum - tmpSum){
                nums[i + 1] = '\0';
                *returnSize = i + 1;
                break;
            }
        }

    return nums;
}