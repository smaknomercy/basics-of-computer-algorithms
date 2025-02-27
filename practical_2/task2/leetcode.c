/* Solution for leetcode task 1. Two Sum
Link to the answer https://leetcode.com/problems/two-sum/submissions/1557440174
*/

int *twoSum(int *nums, int numsSize, int target, int *returnSize){
    *returnSize = 2;
    int *returnValues = malloc((*returnSize) * sizeof(int));

    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                returnValues[0] = i;
                returnValues[1] = j;
                break;
            }
        }
    }
    
    return returnValues;
}