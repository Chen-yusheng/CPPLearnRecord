### C++ lambda���ʽ  
��������������棺lambda���ʽ  
���������ȱ��:  
&emsp;&emsp;ʹ���ڷ����㷨�������ݹ����У������ڴ��бȽ�����/�Զ����������Ҫ�ȶ���һ�������  
**lambda���ʽ���﷨��  
&emsp;&emsp;\[�����ⲿ����](�β��б�)->����ֵ{��������};**  
�����ⲿ����:  
&emsp;[]��ʾ�������κ��ⲿ����  
&emsp;[=]��ʾ�Դ�ֵ�ķ�ʽ�����ⲿ�����б���  
&emsp;[&]��ʾ�Դ����õķ�ʽ�����ⲿ�����б���  
&emsp;[this]��ʾ�����ⲿ��thisָ��  
&emsp;[=,&a]��ʾ�Դ�ֵ�ķ�ʽ�����ⲿ�����б���������a�����Դ����õķ�ʽ����  
&emsp;[a,b]��ʾ��ֵ���ݵķ�ʽ�����ⲿ����a��b  

���lambda���ʽ�ķ���ֵ����Ҫ����ô"->����ֵ"����ʡ��  
lambda����Ϊ������const�������ڲ������޸ĳ�Ա����������ͨ��mutable���Σ�mutable��const�෴����ʾ�����ڲ������޸ĳ�Ա���������Ը���const������  
#### C++��mutable��volatile
mutableֻ�����������Ա�ϣ�ָʾ���������ǿɱ�ġ����ܺ�constͬʱ����һ����Ա���������ʹ�ã�const���εķ����У�mutable���εĳ�Ա���ݿ��Է����ı䣬����֮�ⲻӦ�ö���/������������á�  
const�����в�����Գ����Ա���б䶯����mutable��Ա���ܴ����� 

volatile�������γ�Ա�������ָʾ�����ζ��������ʱ�仯����������Ҫ�������α��������Ż������棩��ÿ��ȡֵӦ��ֱ�Ӷ�ȡ�ڴ档����volatile�ı仯���������ڣ��������constһ��ʹ�á�  
��volatile�������£�ÿ��ѭ���������ڴ��е�ֵ���ﵽͬ����Ч����  
��Ҫע����ǣ�volatile��ֵ������ʱ��䣬�ڼ�ᵼ�·�Ԥ�ڵĽ����  

**�ܽ�:**  
mutableֻ�������������������constͬʱʹ�ã���const���εķ����У�mutable������ֵ���Է����ı䣻  
volatileֻ�������ڱ�����ֵ��ʱ���ܸı䣬���ָı伴�������������̣߳�Ҳ���������ⲿϵͳ��


```cpp
template <typename T=void>
class TestLambda01
{
public:
    void operator()()const   //��������Ϊ��   ����������Ա���������޸�
    {
        cout << "hello world" << endl;
    }
};
template <typename T=int>
class TestLambda02
{
public:
    T operator()(int a,int b)const   //��������Ϊ��
    {
        return a+b;
    }
};
int main()
{
    auto func1 = []()->void {cout << "hello world" << endl; };
    func1();
    //�����������û�����ͬ
    TestLambda01<> t1;
    t1();
    

    auto func2 = [](int a, int b)->int {return a + b; };
    cout << func2(78, 98) << endl;

    TestLambda02<> t2;
    cout << t2(1, 3) << endl;

    //���lambda���ʽ�ķ���ֵ����Ҫ����ô"->����ֵ"����ʡ��
    auto func3 = []() {cout << "ni hao" << endl; };
    func3();

    
    int a = 3, b = 55;
    auto func4 = [=]()mutable {int temp = a; a = b; b = temp; };
    //lambda����Ϊ������const�������ڲ������޸ĳ�Ա����������ͨ��mutable���Σ�
    //mutable��const�෴����ʾ�����ڲ������޸ĳ�Ա���������Ը���const������
    //mutableֻ�����������Ա�ϣ�ָʾ���������ǿɱ�ġ����ܺ�constͬʱ����һ����Ա��
    //�������ʹ�ã�const���εķ����У�mutable���εĳ�Ա���ݿ��Է����ı䣬
    //����֮�ⲻӦ�ö���/������������á�
    func4();
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    //��ֵ���ݣ���������û���޸�
    //�����ô��ݣ������޸�����ָ����ָ���ֵ
    auto func5 = [&]() {int temp = a; a = b; b = temp; };
    func5();
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;

    return 0;
}
```

```cpp
int main()
{
    vector<int> vec;
    for (int i = 0; i < 20; i++)
    {
        vec.push_back(rand() % 100 + 1);
    }

    sort(vec.begin(), vec.end(), [](int a, int b)->bool {return a > b; });
    for (int val : vec)
        cout << val << " ";
    cout << endl;

    //��65�������vector
    //lambda���þ����Ǽ�Ԫ���������Դ���
    auto it = find_if(vec.begin(), vec.end(), [](int a)->bool {return a < 65; });

    if (it != vec.end())
        vec.insert(it, 65);
    for (int val : vec)
        cout << val << " ";
    cout << endl;
    for_each(vec.begin(), vec.end(), [](int a) {cout << a << " "; });
    cout << endl;
    return 0;
}
```

��Ȼlambda���ʽֻ��ʹ������䵱�У����������ʹ��֮ǰ����õı��ʽ������ô�죿  
lambda���ʽ�Ǻ������󣬿�����function���ͱ����������������
```cpp
int main()
{
    map<int, function<int(int, int)>> caculateMap;
    caculateMap[1] = [](int a, int b)->int {return a + b; };
    caculateMap[2] = [](int a, int b)->int {return a - b; };
    caculateMap[3] = [](int a, int b)->int {return a * b; };
    caculateMap[4] = [](int a, int b)->int {return a / b; };

    cout << "ѡ��:";
    int choice;
    cin >> choice;
    cout << "result=" << caculateMap[choice](1, 14) << endl;

    return 0;
}
```