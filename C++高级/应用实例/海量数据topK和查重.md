### ����Ҫ�ں��������в���topKԪ�ػ����ʱ����ô�죿
1G = 10 0000 0000 �� 10�ڣ����10���������ݴ�Լռ4G�ڴ�ռ�  
#### һ������
��������**����**�ķ�����  

|����|��ȱ��|
|:-:|:-:|
|��ϣ��|Ч�ʸߣ��ڴ�ռ�ô�|
|���η�|�����Ը�|
|BloomFilter,<br>��¡������|�ŵ��ǿռ�Ч�ʺͲ�ѯʱ�䶼��һ����㷨Ҫ�õĶ�<br>ȱ������һ������ʶ���ʺ�ɾ������|

�����ַ������͵Ĳ��أ��У�KMP���ҡ�TrieTree�ֵ���(ǰ׺��)

�ù�ϣ����صĻ���˼·��
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
	//�ҳ�ar[SIZE]��˭�ظ��ˣ���ͳ���ظ��Ĵ���
	unordered_map<int, int> map;
	for (int val : ar)
	{
		map[val]++;  //��ϣӳ��
	}

	for (auto pair : map)
	{
		if (pair.second > 1)
		{
			cout << "���֣�" << pair.first << " �ظ�������" << pair.second << endl;
		}
	}
}
```

���ص������ʷ���  
�ʷ�һ��  
��һ�����ļ����д��������� 50�ڸ��������ڴ�����400M���ҳ��ظ���Ԫ�ػ����  
���Σ����ļ�����ΪС�ļ���ʹ��ÿһ��С�ļ��ܹ����ص��ڴ浱�У������Ӧ���ظ�Ԫ�أ��ѽ��д�뵽һ���洢�ظ�Ԫ�ص��ļ�����
 
�ʷ�����  
A,B�����ļ����У����涼��10�ڸ�Ԫ�أ��ڴ�����400M�����A,B������Щ�ظ�Ԫ��


#### ������topK
1.�����/С��**ǰK��**Ԫ��  
2.�����/С��**��K��**Ԫ��  

�ⷨ˼·��  
**1.��/С����**  
����ǰ10��Ԫ�ش���һ��С���ѣ�֮�����ʣ�µ���������������ȶѶ�Ԫ�ش���ôɾ���Ѷ�Ԫ�أ����ѣ���Ȼ���ٰ�������ѣ�����������Ԫ�أ�С������ŵľ���ֵ����ǰ10��Ԫ��
```cpp
#include <vector>
#include <queue>    //�������ȶ��У����ȶ��еײ����ö�ʵ�ֵ�
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
	//����ǰ10��Ԫ�ع���һ����
	for (; k < 10; ++k)
		minHeap.push(vec[k]);

	for (; k < vec.size(); ++k)
	{
		if (vec[k] > minHeap.top())  //�������Ԫ�رȶѶ�Ԫ�ش󣬶Ѷ�Ԫ�س��ѣ�����Ԫ�����
		{
			minHeap.pop();
			minHeap.push(vec[k]);
		}
	}

	while (!minHeap.empty())   //���ʣ��Ķ�Ԫ�ؾ���ǰK��Ԫ��
	{
		cout << minHeap.top() << endl;
		minHeap.pop();
	}

	return 0;
}
```

**2.���ŷָ�**  
һ�˿��ŷָ������O(logn)��ʱ���ڰ�С�ڻ�׼����������������ߣ��Ѵ��ڻ�׼���������������ұߣ���׼���Ϳ�����Ϊ�ǵڣ�index+1)С������  

*��������*  
```cpp
//һ�˿��ŷָ�
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

#### �����ۺϿ���
�ʷ�һ���ҳ����ݵ��ظ��������/��С��ǰK��/��K��Ԫ��  
˼·����ϣͳ�ƣ�map�� + ��/���ŷָ�  

�ں��������У��ҳ��ظ���������ǰ10�������쳣��������ظ���������1������û������ظ���ô�죿��  
```cpp
int main()
{
	vector<int> vec;
	for (int i = 0; i < 200000; ++i)
	{
		vec.push_back(rand());
	}

	//ͳ�����������ظ�����  ��ϣͳ��
	unordered_map<int, int> numMap;
	for (int val : vec)
	{
		numMap[val]++;
	}   

	//����һ��С����
	using P = pair<int, int>;
	using FUNC = function<bool(P&, P&)>;
	using MinHeap = priority_queue<P, vector<P>, FUNC>;
	MinHeap minheap([](auto& a, auto& b)->bool {
		return a.second > b.second;
		});

	//�����ѷ�10��Ԫ��
	int k = 0;
	auto it = numMap.begin();

	for (; it != numMap.end() && k < 10; ++it, ++k)
	{
		minheap.push(*it);
	}

	//��K+1��ĩβ��Ԫ�ؽ��б������ͶѶ�Ԫ�رȽ�
	for (; it != numMap.end(); ++it)
	{
		if (it->second > minheap.top().second)
		{
			minheap.pop();
			minheap.push(*it);
		}
	}

	//�Ѷ�ʣ�µľ����ظ���������ǰk��Ԫ��
	while (!minheap.empty())
	{
		auto& pair = minheap.top();
		cout << pair.first << " : " << pair.second << endl;
		minheap.pop();
	}

	return 0;
}
```
�ʷ�������һ�����ļ����ڴ�����200M�����ļ����ظ���������ǰ10��Ԫ��  
˼·���Ѵ��ļ�����ΪС�ļ���С�ļ��е����ݹ�ϣͳ�ƣ��öѻ�����ҳ���С�ļ��е�ǰ10Ԫ��  
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

	//�Ѵ��ļ�����ΪС�ļ�
	const int FILE_NO = 11;   //���軮��Ϊ11��С�ļ�
	FILE* pfile[FILE_NO] = { nullptr };
	for (int i = 0; i < FILE_NO; ++i)
	{
		char filename[20];
		sprintf(filename, "data%d.dat", i + 1);
		pfile[i] = fopen(filename, "wb+");
	}

	//��ϣӳ�䣬�Ѵ��ļ��е�����ӳ�䵽����С�ļ���
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

	//�ֶ����С�ļ���top 10������֣���������ս��
	for (int i = 0; i < FILE_NO; ++i)
	{
		fseek(pfile[i], 0, SEEK_SET);

		//��ϣͳ���ظ�����
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

		//��K+1��ĩβ��Ԫ�ؽ��б������ͶѶ�Ԫ�رȽ�
		for (; it != numMap.end(); ++it)
		{
			if(it->second > minheap.top().second)
			{
				minheap.pop();
				minheap.push(*it);
			}
		}

		//��չ�ϣ��������һ��С�ļ�������ͳ��
		numMap.clear();
	}

	//����ʣ�µľ����ظ���������ǰk��
	while (!minheap.empty())
	{
		auto& pair = minheap.top();
		cout << pair.first << " : " << pair.second << endl;
		minheap.pop();
	}

	return 0;
}
```
