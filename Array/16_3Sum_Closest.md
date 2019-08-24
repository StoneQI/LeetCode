16.3Sum Closest

Given an array `nums` of *n* integers and an integer `target`, find three integers in `nums` such that the sum is closest to `target`. Return the sum of the three integers. You may assume that each input would have exactly one solution.

**Example:**

```
Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
```

**题意**：找到最靠近target的值

**我的解法**：8ms  8.7MB   时间复杂度：$\ O(n^2)$ ，空间复杂度：$\ O(1)$

解法和上题几乎一样，只是注意用绝对值计算距离最小即可。

```c++
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int result=0;
        int min=INT_MAX;
        int current=0;
        if (nums.size() < 3) return min; //处理边界情况
        sort(nums.begin(),nums.end());
        auto last=nums.end(); 
        
        
        for (auto a=nums.begin(); a<prev(last,2); a++) {
            auto b=next(a);//next 1 postion
            auto c=prev(last);//prev 1 postion
            
            if (a>nums.begin() &&  *a == *prev(a)) continue; //重复的只处理一次
            if(*a>result) break; //当*a大于result时。a和后面的值之和肯定大于a，即不可能小于result，所以直接返回
            
            while(b<c) {
                current=*a+*b+*c-target;//计算差值
                if(min>abs(current)) { //利用绝对值判断sum离target的距离，如果最小，则保存当前的sum，并更新min最小距离。
                    min=abs(current);
                    result =*a+*b+*c;
                    if(current==0) return result; //如果差值为0，则为最closest的值。
                } 
                
                if (current < 0) b++; //差值小于0, 说明sum小于target，要使sum增加才closest target，需要b后移
                
                if (current > 0)  c--; //差值大于0, 说明sum大于target，要使sum减小才closest target，需要c前移
                
                    
            } 
        }    
        return result;
    }
};
```

**论坛解法**：12ms  8.7MB   时间复杂度：$\ O(n^2)$ ，空间复杂度：$\ O(1)$ 。和我逻辑差不多

```C++
class Solution {
public:
        int threeSumClosest(vector<int>& nums, int target) {
        int result=nums[0]+nums[1]+nums[nums.size()-1];
        sort(nums.begin(),nums.end());
        auto last=nums.end(); 
        
        //固定i，然后变动start end
        for (auto i=nums.begin(); i<prev(last,2); i++) {
            auto start=next(i);//next 1 postion
            auto end=prev(last);//prev 1 postion  
            
            while(start<end) {
                int sum=*i+*start+*end;//计算和
                
				if(sum>target) end--; //如何sum大于目标，end减少，总体sum则减少，更靠近target
                else start++;  //如何sum小于目标，start减少，总体sum则减少，更靠近target
                
                if(abs(sum-target)<abs(result-target)) { //利用绝对值判断sum离target的距离，如果最小，则保存当前的sum。
                    result =sum;             
                }                           
            } 
        }    
        return result;
    }
};
```