**全排列（Permutation）**：

```c++
Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
```

全排列算是很经典的题目了，网上详细的教程很多。这里我只是简单记录一下主要方法，并不详细。

**方法一**：最经典的方法。采用递归的思想解决，先输出所有以A开头的排列，然后输出以B开头的排列，接着输出…，最后输出以N开头的排列。以A开头的排列中，第一位是A，后面是B~N的排列。以AB开头的排列中，第一位是A，第二位是B，后面是C~N的排列……如此递归，生成的是按照字典序排列的全排列。

![161756_NbzE_2911530](D:\OneDrive - my.swjtu.edu.cn\03-leetcode\Array\assets\161756_NbzE_2911530.gif)

```cpp
private static void core(int[] array) {
    int length = array.length;
    fullArray(array, 0, length - 1);
}
    
private static void fullArray(int[] array, int cursor, int end) {
    if (cursor == end) {
        System.out.println(Arrays.toString(array));
    } else {
        for (int i = cursor; i <= end; i++) {
            ArrayUtils.swap(array, cursor, i);
            fullArray(array, cursor + 1, end);
            ArrayUtils.swap(array, cursor, i);
        }
    }
}
```

**方法二**：字典序方法。

假如一个序列是`[1,2,3,4]`从小到大的顺序，按照字典序最后会变为`[4,3,2,1]`从大到小的序列。因此，只要从后往前查找，找不到前一元素小于后一元素，就说明已经转换完成，否则说明该元素不满足从大到小序列，就要进行下一步转换。例如，现在有`[1,3,4,2]`，此时3小于4，所以需要进行下一步转换。首先在3后面找到3的下一个最大值，即4，然后交换3和4，变为`[1,4,3,2]`。在反转4以后的元素，最后为`[1,4,2,3]`。为什么要反转。因为交换后，此时4后面的元素为逆序，因为从3变为了4，所以4后面的元素需要重新全排列，因此4后面的元素需要恢复到从小到大的顺序，反转恰好能实现这个功能。

```cpp
#include<iostream>
#include<algorithm>
 
using namespace std;
 
int arry[3] = { 1,2,3 };//len==3;
 
void Permutation()
{
	int len = 3;
	int j, k;
 
	while (true)
	{
		printf("%d%d%d\n", arry[0], arry[1], arry[2]);
 
		for (j = len - 2; j >= 0 && arry[j] > arry[j + 1]; j--);//注意此处 j >= 0 判断条件在前
 
		if (j < 0) return;//结束
		
		for (k = len - 1; k > j&&arry[k] < arry[j]; k--);
 
		swap(arry[k], arry[j]);
 
		for (int l = j + 1, r = len - 1; l < r; l++, r--)
			swap(arry[l], arry[r]);
	}
}
 
int main()
{
 
	Permutation();
 
	return 0;
}
```



--------

31. Next Permutation

Implement **next permutation**, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be **in-place** and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

```
1,2,3` → `1,3,2`
`3,2,1` → `1,2,3`
`1,1,5` → `1,5,1
```

**题意**：找到全排列的下一个序列

**我的解法**：8ms,8.5MB ,时间复杂度：$\ O(n)$ ，空间复杂度：$\ O(1)$。使用字典序的方法查找下一个序列

![31_Next_Permutation](D:\OneDrive - my.swjtu.edu.cn\03-leetcode\Array\assets\31_Next_Permutation.gif)

```Cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        
        if(nums.size()==1)return;  //只有一个，直接返回
        auto begin =nums.begin();
        auto last = prev(nums.end());
        auto start = last-1;
        
        //从后向前找到第一个*start<*(next(start))的下标，例如[1,2,4,3],返回的是2.如果序列[4,3,2,1]或[1,1,1],则返回的start是begin的前一个数，即下标-1。可加一个判定，如果所有数相等直接返回。
        for(;start>=begin;start--){
            if(*start<*(next(start))) {
                break;
            }
        }
        
        //如果start不为-1，然后找到大于*start的最小值的索引，即replace，然后交换start和replace
        if(start>=begin){
            auto replace = start+1;
            for(auto i=replace;i<=last;i++){
                if(*i>*start && *i<=*replace) { //注意这里对相等数的处理，如果有相等的则继续向后走。例如[1,3,5,4,4,2],则交换的是3和第二个4，这样反转后便是1,4,2,3,4,5.
                    replace=i;
                }
            }
            swap(*start,*replace);   
        }
		
        //反转start+1 到last 之间的数，如果是start是-1.则是反转整个数组。
        while(start<last) swap(*(++start),*(last--));
           
        
    }
};
```

**论坛解法**：四种算法思想都一样，实现不一样

**解法 1**



Just for info: There's a library function that does the job, even going from totally reverse sorted to sorted:   直接使用库函数就可以实现



```
void nextPermutation(vector<int>& nums) {
    next_permutation(begin(nums), end(nums));
}
```



**解法 2**



Using library functions for all building blocks of the algorithm. Very nice how they all play together, notice the total lack of `+1`/`-1`, it all fits exactly.

同样利用更基础的库函数，而且没有多余的下标`+1/-1`操作

```cpp
void nextPermutation(vector<int>& nums) {
    auto i = is_sorted_until(nums.rbegin(), nums.rend());//is_sorted_until() 来判断一个元素段是否有序。它的参数用来定义要测试的迭代器。这个函数返回第一个破坏序列有序的元素迭代器.如果是[1,2,4,3]则返回元素2的迭代器。如果完全有序，返回结束迭代器 nums.rend()
    if (i != nums.rend())//根据i判断是否有序
        swap(*i, *upper_bound(nums.rbegin(), i, *i));//upper_bound()返回指定迭代器范围内大于指定值的第一个元素的迭代器。该地方从后向前查找大于*i的第一个元素，然后和*i交换
    reverse(nums.rbegin(), i); //翻转指定迭代器的数。
}
```



**解法 3**

Doing it all on my own (except `swap`, let's not be silly):

除了swap，其他都用自带实现。这里就不用注释了，注意下标`+1/-1`的作用就好。

```cpp
void nextPermutation(vector<int>& nums) {
    int i = nums.size() - 1, k = i;
    
    while (i > 0 && nums[i-1] >= nums[i])
        i--;
    
    for (int j=i; j<k; j++, k--)
        swap(nums[j], nums[k]);
    
    if (i > 0) {
        k = i--;
        while (nums[k] <= nums[i])
            k++;
        swap(nums[i], nums[k]);
    }
}
```

---------

33. Search in Rotated Sorted Array

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



