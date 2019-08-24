34.Find First and Last Position of Element in Sorted Array

Given an array of integers `nums` sorted in ascending order, find the starting and ending position of a given `target`value.

Your algorithm's runtime complexity must be in the order of *O*(log *n*).

If the target is not found in the array, return `[-1, -1]`.

**Example 1:**

```
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
```

**Example 2:**

```
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
```



**题意**：找到给定序列，target值的起始值和终止值。

**我的解法**：8ms , 10.2MB .时间复杂度：$\ O(log{n})$ ，空间复杂度：$\ O(1)$

直接利用折半查找到target值的位置。然后向前向后查找到与target值相同的索引。

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result ={-1,-1};
        int start = 0;
        int end = nums.size()-1;
        int flag = -1;
        //二分法查找到target值的索引
        while(start<=end){
            int half=(start+end)/2;
            if(nums[half] == target) {
                flag = half;   
                break;
            } 
            if(nums[half]<target){
                start = half+1;
            }else{
                end = half -1;
            }
        }
        if(flag == -1) return result; //未找到target直接返回。
        //以target为中心向前向后查找到与target值相同的索引
        start = flag;
        end = flag;
        while((start-1) >=0 && nums[start]==nums[start-1]) start-- ;
        while((end+1)< nums.size() && nums[end] ==nums[end+1]) end++;
        result[0]=start;
        result[1]=end;
        return result;
    }
};
```

**官方解法**：时间复杂度：$\ O(log_{10}{(n)})$ ，空间复杂度：$\ O(1)$

用二分查找到左边5的索引。再用二分查找到右边5的索引。

```java
class Solution {
    // returns leftmost (or rightmost) index at which `target` should be
    // inserted in sorted array `nums` via binary search.
    private int extremeInsertionIndex(int[] nums, int target, boolean left) {
        int lo = 0;
        int hi = nums.length;
		
       	
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            //首先不管(left && target == nums[mid])的值。nums[mid] > target 这个条件肯定会保证最后查找到5。当left=true时，且target == nums[mid]为true。hi=mid,mid会向左移，找到target的starting position。当left=false时，且target == nums[mid]为true。lo=mid+1，mid会向右移，找到target的ending position。
            if (nums[mid] > target || (left && target == nums[mid])) {
                hi = mid;
            }
            else {
                lo = mid+1;
            }
        }

        return lo;
    }

    public int[] searchRange(int[] nums, int target) {
        int[] targetRange = {-1, -1};
		
        //找到target的starting position。
        int leftIdx = extremeInsertionIndex(nums, target, true);

        // assert that `leftIdx` is within the array bounds and that `target`
        // is actually in `nums`.
        //判断是否存在target
        if (leftIdx == nums.length || nums[leftIdx] != target) {
            return targetRange;
        }

        targetRange[0] = leftIdx;
        ////找到target的ending position。
        targetRange[1] = extremeInsertionIndex(nums, target, false)-1;

        return targetRange;
    }
}
```

**论坛解法**：8ms , 11.2MB .时间复杂度：$\ O(log{n})$ ，空间复杂度：$\ O(log{n})$

该方法的思路是使用折半递归，判断每个折半的部分最小值和最大值是否等于target。例如`[1,2,3,5,5,5,6,7]`，`l=0，r=7`，`nums[l]!=nums[r]`,所以对其折半，在判断`nums[l]==nums[mid]`和`nums[mid]==nums[r]`。满足条件时，折半的两部分会依次返回`left:[l,r];right:[l,r]`。然后选取`left[0], right[1]`。组成最小值和最大值。其中出现`-1`时，直接取另一个。

这里的时间复杂度之所以计算为$\ O(log{n})$ ，是因为当`nums[l] <= target && target <= nums[r]`不满足时，会直接返回，不会再折半这部分。

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        if(n<1) return {-1, -1};
        return search(nums, 0, n - 1, target);
    }
private: 
    vector<int> search(vector<int>& nums, int l, int r, int target) {
        if (nums[l] == target && nums[r] == target) return {l, r};
        if (nums[l] <= target && target <= nums[r]) {
            int mid = l + ((r - l) >> 1);
            vector<int> left = search(nums, l, mid, target); //对左边折半搜索
            vector<int> right = search(nums, mid  +1, r, target);//对右边折半搜索
            if (left[0] == -1) return right;//-1的时候说明另一边不满足条件，直接返回这一边的。
            if (right[0] == -1) return left;
            return {left[0], right[1]};//返回左边最小值，右边最大值
        }
        return {-1, -1};
    }
};
```

