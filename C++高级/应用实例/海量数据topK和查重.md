### 当需要在海量数据中查找topK元素或查重时该怎么办？
1G = 10 0000 0000 ≈ 10亿，因此10亿整数数据大约占4G内存空间  
#### 一、查重
海量数据**查重**的方法：  

|方法|优缺点|
|:-:|:-:|
|哈希表|效率高，内存占用大|
|分治法|普适性高|
|BloomFilter,<br>布隆过滤器|优点是空间效率和查询时间都比一般的算法要好的多<br>缺点是有一定的误识别率和删除困难|

对于字符串类型的查重，有：KMP查找、TrieTree字典树(前缀树)

用哈希表查重的基本思路：
```cpp
#include <unordered_map>
int main()
{
	const int SIZE = 100;
	int ar[SIZE] = { 0 };
	for (int i = 0; i < SIZE; ++i)
	{
		ar[i] = rand();

	}
	//找出ar[SIZE]中谁重复了，并统计重复的次数
	unordered_map<int, int> map;
	for (int val : ar)
	{
		map[val]++;  //哈希映射
	}

	for (auto pair : map)
	{
		if (pair.second > 1)
		{
			cout << "数字：" << pair.first << " 重复次数：" << pair.second << endl;
		}
	}
}
```

查重的其他问法：  
问法一：  
有一个大文件，有大量的整数 50亿个整数，内存限制400M，找出重复的元素或次数  
分治：大文件划分为小文件，使得每一个小文件能够加载到内存当中，求出对应的重复元素，把结果写入到一个存储重复元素的文件当中
 
问法二：  
A,B两个文件当中，里面都有10亿个元素，内存限制400M，求出A,B中有哪些重复元素


#### 二、求topK
1.求最大/小的**前K个**元素  
2.求最大/小的**第K个**元素  

解法思路：  
**1.大/小根堆**  
先用前10个元素创建一个小根堆，之后遍历剩下的整数，如果整数比堆顶元素大，那么删除堆顶元素（出堆），然后再把整数入堆，遍历完所有元素，小根堆里放的就是值最大的前10个元素
```cpp
#include <vector>
#include <queue>    //包含优先队列，优先队列底层是用堆实现的
using namespace std;
int main()
{

	vector<int> vec;
	for (int i = 0; i < 100000; ++i)
	{
		vec.push_back(rand() + i);
	}
	priority_queue<int, vector<int>, greater<int>> minHeap;
	int k = 0;
	//先用前10个元素构建一个堆
	for (; k < 10; ++k)
		minHeap.push(vec[k]);

	for (; k < vec.size(); ++k)
	{
		if (vec[k] > minHeap.top())  //如果遍历元素比堆顶元素大，堆顶元素出堆，遍历元素入堆
		{
			minHeap.pop();
			minHeap.push(vec[k]);
		}
	}

	while (!minHeap.empty())   //最后剩余的堆元素就是前K大元素
	{
		cout << minHeap.top() << endl;
		minHeap.pop();
	}

	return 0;
}
```

**2.快排分割**  
一趟快排分割就能在O(logn)的时间内把小于基准数的整数调整到左边，把大于基准数的整数调整到右边，基准数就可以认为是第（index+1)小的整数  

*快速排序*  
```cpp
//一趟快排分割
int partation(vector<int>& arr, int i, int j)
{
	int k = arr[i];
	while (i < j)
	{
		while (i < j && arr[j] >= k)
			j--;
		if (i < j)
			arr[i++] = arr[j];
		while (i < j && arr[i] < k)
			i++;
		if (i < j)
			arr[j--] = arr[i];
	}
	arr[i] = k;
	return i;
}

int selectNoK(vector<int>& arr, int i, int j, int k)
{
	int pos = partation(arr, i, j);
	if (pos == k - 1)
		return arr[pos];
	else if (pos < k - 1)
		return selectNoK(arr, pos + 1, j, k);
	else
	{
		return selectNoK(arr, i, pos, k);
	}
}
```
```cpp
int main()
{
	vector<int> vec;
	for (int i = 0; i < 100000; ++i)
	{
		vec.push_back(rand() + i);
	}
	cout << selectNoK(vec, 0, vec.size() - 1, 10) << endl;

	return 0;
}
```

#### 三、综合考察
问法一：找出数据的重复次数最大/最小的前K个/第K个元素  
思路：哈希统计（map） + 堆/快排分割  

在海量数据中，找出重复次数最多的前10个。（异常处理，如果重复次数都是1，根本没有最大重复怎么办？）  
```cpp
int main()
{
	vector<int> vec;
	for (int i = 0; i < 200000; ++i)
	{
		vec.push_back(rand());
	}

	//统计所有数字重复次数  哈希统计
	unordered_map<int, int> numMap;
	for (int val : vec)
	{
		numMap[val]++;
	}   

	//定义一个小根堆
	using P = pair<int, int>;
	using FUNC = function<bool(P&, P&)>;
	using MinHeap = priority_queue<P, vector<P>, FUNC>;
	MinHeap minheap([](auto& a, auto& b)->bool {
		return a.second > b.second;
		});

	//先往堆放10个元素
	int k = 0;
	auto it = numMap.begin();

	for (; it != numMap.end() && k < 10; ++it, ++k)
	{
		minheap.push(*it);
	}

	//把K+1到末尾的元素进行遍历，和堆顶元素比较
	for (; it != numMap.end(); ++it)
	{
		if (it->second > minheap.top().second)
		{
			minheap.pop();
			minheap.push(*it);
		}
	}

	//堆顶剩下的就是重复次数最大的前k个元素
	while (!minheap.empty())
	{
		auto& pair = minheap.top();
		cout << pair.first << " : " << pair.second << endl;
		minheap.pop();
	}

	return 0;
}
```
问法二：有一个大文件，内存限制200M，求文件中重复次数最多的前10个元素  
思路：把大文件划分为小文件，小文件中的数据哈希统计，用堆或快排找出该小文件中的前10元素  
```cpp
int main()
{
	FILE* pf1 = fopen("data.dat", "wb");
	for (int i = 0; i < 20000; ++i)
	{
		int data = rand();
		fwrite(&data, 4, 1, pf1);
	}
	fclose(pf1);

	FILE* pf = fopen("data.dat", "rb");
	if (pf == nullptr)
	{
		cout << "file_path error!" << endl;
		return 0;
	}

	//把大文件划分为小文件
	const int FILE_NO = 11;   //假设划分为11个小文件
	FILE* pfile[FILE_NO] = { nullptr };
	for (int i = 0; i < FILE_NO; ++i)
	{
		char filename[20];
		sprintf(filename, "data%d.dat", i + 1);
		pfile[i] = fopen(filename, "wb+");
	}

	//哈希映射，把大文件中的数据映射到各个小文件中
	int data;
	while (fread(&data, 4, 1, pf) > 0)
	{
		int findex = data % FILE_NO;
		fwrite(&data, 4, 1, pfile[findex]);
	}

	unordered_map<int, int> numMap;
	using P = pair<int, int>;
	using FUNC = function<bool(P&, P&)>;
	using MinHeap = priority_queue<P, vector<P>, FUNC>;
	MinHeap minheap([](auto& a, auto& b)->bool {
		return a.second > b.second;
		});

	//分段求解小文件的top 10大的数字，并求出最终结果
	for (int i = 0; i < FILE_NO; ++i)
	{
		fseek(pfile[i], 0, SEEK_SET);

		//哈希统计重复次数
		while (fread(&data, 4, 1, pfile[i]) > 0)
		{
			numMap[data]++;
		}

		int k = 0;
		auto it = numMap.begin();

		if (minheap.empty())
		{
			for (; it != numMap.end() && k < 10; ++it, ++k)
			{
				minheap.push(*it);
			}
		}

		//把K+1到末尾的元素进行遍历，和堆顶元素比较
		for (; it != numMap.end(); ++it)
		{
			if(it->second > minheap.top().second)
			{
				minheap.pop();
				minheap.push(*it);
			}
		}

		//清空哈希表，进行下一个小文件的数据统计
		numMap.clear();
	}

	//堆中剩下的就是重复次数最大的前k个
	while (!minheap.empty())
	{
		auto& pair = minheap.top();
		cout << pair.first << " : " << pair.second << endl;
		minheap.pop();
	}

	return 0;
}
```
