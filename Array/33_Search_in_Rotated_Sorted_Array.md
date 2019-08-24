33.Search in Rotated Sorted Array

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., `[0,1,2,4,5,6,7]` might become `[4,5,6,7,0,1,2]`).

You are given a target value to search. If found in the array return its index, otherwise return `-1`.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of *O*(log *n*).

**Example 1:**

```cpp
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
```

**Example 2:**

```cpp
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
```

**题意**：一个旋转的有序序列，查找target，查找成功返回对应索引，查找失败返回-1。要求时间复杂度$\ O(log{n})$

**我的解法**：4ms,8.6MB ,时间复杂度：$\ O(log{n})$ ，空间复杂度：$\ O(1)$。

要求时间复杂度$\ O(log{n})$，所以必然是二分查找。关键是判断target在哪一部分。例如`[4,5,6,7,0,1,2]`，如果对半分，则必然有一部分是有序的，然后在判断target是否在有序的这部分。如果在，则选择该部分为下一次折半查找的部分。否则选择另一部分。

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int length = nums.size();
        int start = 0;
        int end =length-1;
        //依次折半，
        while(start<=end){
            int half = (start+end)/2;
            if(nums[half] == target) return half;
            
            bool flag=false;//flag标记下一次折半在哪一部分。true是前半部分，false是后半部分。
            if(nums[start]<=nums[half] )//判断前半部分是否有序。如果相等，说明前半部分只有一个数，默认是有序的。
                flag=true;
            
            if(flag){
                //当前半部分有序的条件下，判断target是否在其中，如在，flag==true，折半前半部分；如不在，flag==false，折半后半部分。
                if(nums[start]> target || nums[half]< target)
                    flag = false;
            }else{
                //当后半部分有序的条件下，判断target是否在其中，如在，flag==false，折半后半部分；如不在，flag==true，折半前半部分。
                if(nums[half]> target || nums[end]<target )
                    flag = true;
            }
            
            //根据falg的值判断对哪部分折半。
            if(flag)
                end = half-1;
            else
                start =half+1;
            
        }
        return -1;
        
    }
};
```

**论坛解法1**：4ms,8.6MB ,时间复杂度：$\ O(log{n})$ ，空间复杂度：$\ O(1)$

该解法的思路是二分法是重新将索引映射到正确的值。例如`[4,5,6,7,0,1,2]`，这里索引0对应的是4,1对应的是5。如果找到一个函数`f`，使`0=f(0)，1=f(1)`。那么直接对这个进行二分就行了。而这里的序列是作了旋转的，类似与时钟，因此能找到这个规律映射到原来的值。这里先用二分找到最小值的索引。然后在计算时，引入这个索引便可以将旋转的序列给恢复原样。例如`[4,5,6,7,0,1,2]`，找到最小值的索引是4，那么只需向前旋转5次就行了。在公式里，`mid=(lo+hi)/2`这里的mid是旋转过后的值。要恢复到真实的mid为`realmid=(mid+rot)%n`可用时钟的原理去理解。



```cpp
class Solution {
public:
    int search(vector<int>& A, int target) {
        int n=A.size();
        int lo=0,hi=n-1;
        // find the index of the smallest value using binary search.
        // Loop will terminate since mid < hi, and lo or hi will shrink by at least 1.
        // Proof by contradiction that mid < hi: if mid==hi, then lo==hi and loop would have been terminated.
        while(lo<hi){ //找到最小值的索引，不清楚的可以推一下。实际这里找到最小值时，最小值的前后两部分都是有序的，可以直接判断target在那一部分，然后对那部分进行折半查找就行。不过作者的方法更有数学技巧。
            int mid=(lo+hi)/2;
            if(A[mid]>A[hi]) lo=mid+1;
            else hi=mid;
        }
        // lo==hi is the index of the smallest value and also the number of places rotated.
        int rot=lo;
        lo=0;hi=n-1;
        // The usual binary search and accounting for rotation.
        while(lo<=hi){
            int mid=(lo+hi)/2;
            int realmid=(mid+rot)%n;//利用最小值的索引，能映射该索引对应的正确值。
            if(A[realmid]==target)return realmid;
            if(A[realmid]<target)lo=mid+1;
            else hi=mid-1;
        }
        return -1;
    
        
    }
};
```

**论坛解法2**：4ms,8.6MB ,时间复杂度：$\ O(log{n})$ ，空间复杂度：$\ O(1)$

这种解法更复杂。这里面涉及到三个值`nums[lo],nums[mid],target`。这里主要判断`nums[mid],target`是否在`nums[lo]`的同一边。如果`nums[mid],target`同时大于或小于`nums[lo]`，则说明`nums[mid],target`在`nums[lo]`的同一边。否则，`nums[mid],target`分别在`nums[lo]`的两侧。例如`[4,5,6,7,0,1,2]`，`target=5，nums[lo]=4，nums[mid]=7`,则说明`nums[mid],target`在`nums[lo]`的右侧，此时只需判断`nums[mid]`和`target`的大小关系即可。 如果`nums[mid]`和`target`不在`nums[lo]`的同一边，则判断`target`和`nums[lo]`的大小关系即可。

```cpp
int search(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size();
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        
        //判断是否在同一边。如果在同一边，nums[mid]<target,对后半部分折半；nums[mid]>target,对前半部分折半。如果不在同一边。target < nums[lo] ，对后半部分折半；target > nums[lo],对前半部分折半。相等则直接返回。
        double num = (nums[mid] < nums[lo]) == (target < nums[lo])
                   ? nums[mid]
                   : target < nums[lo] ? -INFINITY : INFINITY;
                   
        if (num < target)
            lo = mid + 1;
        else if (num > target)
            hi = mid;
        else
            return mid;
    }
    return -1;
}

//根据理解我做了如下修改，更简洁，快速。
int search(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size();
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (nums[mid] == target)
            return mid;
        double num = (nums[mid] < nums[lo]) == (target < nums[lo])
            ? nums[mid] < target ? lo = mid + 1 : hi = mid
            : target < nums[lo] ? lo = mid + 1 : hi = mid;
    }
    return -1;  
}
```
