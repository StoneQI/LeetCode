<!--
 * @Author: stone
 * @Date: 2019-08-23 09:25:21
 * @LastEditTime: 2019-08-23 09:26:43
 * @LastEditors: stone
 * @Description: 
 -->
11. Container With Most Water

    Given *n* non-negative integers *a1*, *a2*, ..., *an* , where each represents a point at coordinate (*i*, *ai*). *n* vertical lines are drawn such that the two endpoints of line *i* is at (*i*, *ai*) and (*i*, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

    **Note:** You may not slant the container and *n* is at least 2.

    ![1566035073852](assets\1566035073852.png)

The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.

 

**Example:**

```visual basic
Input: [1,8,6,2,5,4,8,3,7]
Output: 49
```



**题意**：给定一系列非负数，假设为高度，计算能装最多水的区域。

**我的解法**：

蛮力法，时间复杂度：$\ O(n^2)$ 计算为$\ \frac{n(n-1)}{n}$，空间复杂度：$\ O(1)$

```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        //使用遍历依次计算两个高度之间的area，找到最大值
        int max =0;
        int len = height.size();
        int hei=0;
        int are=0;
        for(int i=0;i<len;i++)
        {
            for(int j=i+1;j<len;j++) //使用j=i+1,避免一般的循环
            {   
                hei = height[i];
                if(height[i]>height[j]) hei = height[j]; //判断高
                are = (j-i)*hei;//计算两者的面积
                if(are>max) max=are;
                    
            }
        }
        return max;
        
    }
};
```

**官方解法**：两指针逼近。时间复杂度：$\ O(n)$ ，空间复杂度：$\ O(1)$

这种方法背后的直觉是，线之间形成的区域总是受短线高度的限制。此外，越远的线，获得的区域就越多。 我们取两个指针，一个在开头，一个在构成行长度的数组的末尾。因此，我们维护一个变量maxarea最大区域，以存储到现在获得的最大区域。在每一步中，我们找出它们之间形成的区域，更新 maxarea，并将指向较短的线的指针向另一端移动一个步骤。

![11_Container_Water](assets\11_Container_Water.gif)





1.  3Sum

Given an array `nums` of *n* integers, are there elements *a*, *b*, *c* in `nums` such that *a* + *b* + *c* = 0? Find all unique triplets in the array which gives the sum of zero.

**Note:**

The solution set must not contain duplicate triplets.

**Example:**

```c++
Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```

**题意**：给定n个数，找出不重复的三个数，相加和为0。

**论坛解法**：时间复杂度：$\ O(n^2)$ ，空间复杂度：$\ O(1)$

首先对vector序列排序，然后设置三个指标，一个指向首元素`i`，一个指向首元素后一个元素`j`，一个指向尾元素`k`,然后固定`i`，移动`j`和`k`，如果sum小于0，则需要增加sum，使其靠近`0`，有由于序列有序，只需找到`j`后一个值，即增加了sum。sum大于0同理。一次遍历完后,增加`i`值，继续遍历。最后对满足的序列去重即可。

```C++
class Solution {
public:
    vector< vector<int> > result;

    vector< vector<int> > threeSum(vector<int>& nums) {

        if(nums.size() < 3) return result;

        map<vector<int>,int> mymap;

        sort(nums.begin(),nums.end());
		//固定i，依次调整j和k
        for(int i = 0;i < nums.size()-2;i++){
            if (i > 0 && (nums[i] == nums[i-1])) { //当出现重复时，只在第一次出现时计算一次
                continue;
            }
            int j = i+1;  //
            int k = nums.size()-1;
            //依次全部遍历
            while(j < k ){
                if(nums[i]+nums[j]+nums[k] < 0){ //如果和小于零，说明需要增大和，数列有序，因此j增加
                    j++;
                }else
                if(nums[i]+nums[j]+nums[k] > 0){ //如果和大于零，说明需要减小和，数列有序，因此k减小
                    k--;
                }
                else{
                    vector<int> temp;
                    temp.push_back(nums[i]);
                    temp.push_back(nums[j]);
                    temp.push_back(nums[k]);
                    mymap[temp] = 1; //map对vector<int>去重，即hash去重
                    j++;
                    k--;
                }
            }
        }
        for(auto t:mymap){
            result.push_back(t.first);
        }
        return result;
    }
};
```



**优化版本1**：108ms 18.3mb, 时间复杂度：$\ O(n^2)$ ，空间复杂度：$\ O(1)$

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        
        vector<vector<int>> result;
        if (nums.size() < 3) return result; //处理边界情况
        sort(nums.begin(),nums.end());
        const int target = 0;
        auto last=nums.end(); 
        //固定a，依次改变b和c
        //重点解释为什么没有去重算法。
        //首先是a，当固定a时，对于后面的值，根据b和c，对于相加为0的重复的值都只计算了一次，所以在固定a的这一次计算产生的多个3个数序列是不会有重复的，其中a和b可能会相同（仅当a为相同元素的第一个时），b和c不可能相同。再来讨论a，a只计算[begin,0],而且对于其中的所有元素，只计算一次，因此a也不会重复，最终得到的序列不会有任何一个重复的序列。
        for (auto a=nums.begin(); a<prev(last,2); a++) {
            auto b=next(a);//next 1 postion
            auto c=prev(last);//prev 1 postion
            
            if (a>nums.begin() &&  *a == *prev(a)) continue; //重复的只处理一次
            
            if (*a>0) return result; //当*a>0时说明，后面相加已经不可能等于0
            
            //注意下面的三个分支，当和不为0时，每个元素都处理了，即使相同元素也进行了。当和为0，这时的a、b、c已经组成一个序列，因此不可能，b、c一个不变，一个变的情况下和还能为0，因此去除a，b重复的现象。也就结下来组成的序列不可能再重复。
            while(b<c) {
                if (*a + *b + *c < target) b++; //小于0 b增加
                else if (*a + *b + *c > target) c--; //大于0 c减少
                else {          
                    result.push_back({*a,*b,*c});
                    while (b<c && *b==*(next(b))) b++;//when break,b != next(b),but b==prev(b). 对b和c去重复判断情况
                    while (b<c && *c==*(prev(c))) c--;
                    b++; //因为b==prev(b)，prev(b)已经判断了，所以++
                    c--;   
                }                     
            } 
        }    
        return result;
        
    }
};
```

**优化版本2**：

```c++
class Solution {
public:
    vector< vector<int> > result;

    vector< vector<int> > threeSum(vector<int>& nums) {

        if(nums.size() < 3) return result;


        sort(nums.begin(),nums.end());
        int i = 0;
        //固定i，一次改变j和k
        while(i < nums.size()-2){
            if (nums[i]>0) break;////当*i>0时说明，后面相加已经不可能等于0

            int j = i+1;
            int k = nums.size()-1;
            
            while(j < k ){
                int sum=nums[i]+nums[j]+nums[k];
                if(sum==0){ //符合条件添加到vector
                    vector<int> temp;
                    temp.push_back(nums[i]);
                    temp.push_back(nums[j]);
                    temp.push_back(nums[k]);
                    result.push_back(temp);
                    
                }
                
                //这里有三种情况，列如[-2,-1,-1,0,1,2,2],如果找到的第一个sum=0的为[-2,0,2]，此时j、k必须同时改变到不等于0、2的数，不然只改一个的话不会满足条件。所以同时满足两个if。当sum小于0，需要找到和j不相等的下一个值，因此只执行第一个条件。大于同理。
                
                //如果小于等于零，向后找到下一个不同的值
                if(sum <= 0){
                    while (  nums[j]==nums[++j]&& j<k) ;//当*j和*(++j)*不相等时，由于++j，所以此时j指向不等于j的后一个值
                }
                //如果大于等于零，向前找到下一个不同的值
                if(sum >= 0){
                     while ( nums[k--]==nums[k]&& j<k) ;//当*(k--)和*(k)*不相等时，由于k--，所以此时k指向不等于k的前一个值。注意这个比教的是 后一个k的值==前一个k的值。
                }
                
            }
            //保证每个i只处理一次
            while(nums[i] == nums[++i] && i < nums.size() - 2);
        }
        return result;
    }
};
```



16. 3Sum Closest

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



18. 4Sum

Given an array `nums` of *n* integers and an integer `target`, are there elements *a*, *b*, *c*, and *d* in `nums` such that *a* + *b*+ *c* + *d* = `target`? Find all unique quadruplets in the array which gives the sum of `target`.

**Note:**

The solution set must not contain duplicate quadruplets.

**Example:**

```
Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
```

**题意**：找到四个数，其和等于target，且序列不重复

**我的解法**：52ms，9MB 。时间复杂度：$\ O(n^3)$ ，空间复杂度：$\ O(1)$

设置是个指标，同时固定第一个和最后一个，变动中间两个指标即可。

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        if (nums.size() < 3) return result; //处理边界情况
        sort(nums.begin(),nums.end());
        auto last = prev(nums.end());
        //先固定a，依次变动其他的指针
        for (auto a=nums.begin(); a<last-2; a++) {
            
            if (a>nums.begin() &&  *a == *prev(a)) {
                    continue; //重复的只处理一次
            }
            //在固定d，即最后一个指针，变动b、c指针
            for (auto d=last; d>a+2; d--) {
                auto b=next(a);//next 1 postion
                auto c=prev(d);//prev 1 postion
                if (d<last &&  *d == *next(d)) {
                    continue; //重复的只处理一次
                }
                while(b<c) {
                    int current = *a + *b + *c+*d;
                    if (current< target) b++; //小于target b增加
                    else if (current > target) c--; //大于target c减少
                    else {          
                        result.push_back({*a,*b,*c,*d});
                        while (b<c && *b==*(next(b))) b++;//when break,b != 
                        while (b<c && *c==*(prev(c))) c--;
                        b++; //因为b==prev(b)，prev(b)已经判断了，所以++
                        c--;   
                    }
                }
            }            
        }    
        return result;
    }
};
```

**论坛解法**：4ms, 43MB。时间复杂度：$\ O(n^3)$ ，空间复杂度：$\ O(1)$

```java
public List<List<Integer>> fourSum(int[] nums, int target) {
		ArrayList<List<Integer>> res = new ArrayList<List<Integer>>();
		int len = nums.length;
		if (nums == null || len < 4)
			return res;

		Arrays.sort(nums);

		int max = nums[len - 1];
    	//判断别介条件
		if (4 * nums[0] > target || 4 * max < target)
			return res;

		int i, z;
		for (i = 0; i < len; i++) {
			z = nums[i];
			if (i > 0 && z == nums[i - 1])// 避免重复计算i
				continue;
			if (z + 3 * max < target) // 保证z不能太小，
				continue;
			if (4 * z > target) // 此时i后面的都不满足条件，直接退出
				break;
			if (4 * z == target) { //如果四个相同的*i和等于target，则后面的也都不满足，直接返回
				if (i + 3 < len && nums[i + 3] == z)
					res.add(Arrays.asList(z, z, z, z));
				break;
			}
			//分解为3Sum的问题，求i+1 到len-1中3个数和为target-z的 序列
			threeSumForFourSum(nums, target - z, i + 1, len - 1, res, z);
		}

		return res;
	}

	/*
	 * Find all possible distinguished three numbers adding up to the target
	 * in sorted array nums[] between indices low and high. If there are,
	 * add all of them into the ArrayList fourSumList, using
	 * fourSumList.add(Arrays.asList(z1, the three numbers))
	 */
	public void threeSumForFourSum(int[] nums, int target, int low, int high, ArrayList<List<Integer>> fourSumList,
			int z1) {
		if (low + 1 >= high)
			return;

		int max = nums[high];
		if (3 * nums[low] > target || 3 * max < target)
			return;

		int i, z;
		for (i = low; i < high - 1; i++) {
			z = nums[i];
			if (i > low && z == nums[i - 1]) // avoid duplicate
				continue;
			if (z + 2 * max < target) // z is too small
				continue;

			if (3 * z > target) // z is too large
				break;

			if (3 * z == target) { // z is the boundary
				if (i + 1 < high && nums[i + 2] == z)
					fourSumList.add(Arrays.asList(z1, z, z, z));
				break;
			}

			twoSumForFourSum(nums, target - z, i + 1, high, fourSumList, z1, z);
		}

	}

	/*
	 * Find all possible distinguished two numbers adding up to the target
	 * in sorted array nums[] between indices low and high. If there are,
	 * add all of them into the ArrayList fourSumList, using
	 * fourSumList.add(Arrays.asList(z1, z2, the two numbers))
	 */
	public void twoSumForFourSum(int[] nums, int target, int low, int high, ArrayList<List<Integer>> fourSumList,
			int z1, int z2) {

		if (low >= high)
			return;

		if (2 * nums[low] > target || 2 * nums[high] < target)
			return;

		int i = low, j = high, sum, x;
		while (i < j) {
			sum = nums[i] + nums[j];
			if (sum == target) {
				fourSumList.add(Arrays.asList(z1, z2, nums[i], nums[j]));

				x = nums[i];
				while (++i < j && x == nums[i]) // avoid duplicate
					;
				x = nums[j];
				while (i < --j && x == nums[j]) // avoid duplicate
					;
			}
			if (sum < target)
				i++;
			if (sum > target)
				j--;
		}
		return;
	}
```

