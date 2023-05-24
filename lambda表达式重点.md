### C++ lambda表达式  
函数对象的升级版：lambda表达式  
函数对象的缺点:  
&emsp;&emsp;使用在泛型算法参数传递过程中，或用在带有比较性质/自定义操作，需要先定义一个类出来  
**lambda表达式的语法：  
&emsp;&emsp;\[捕获外部变量](形参列表)->返回值{操作代码};**  
捕获外部变量:  
&emsp;[]表示不捕获任何外部变量  
&emsp;[=]表示以传值的方式捕获外部的所有变量  
&emsp;[&]表示以传引用的方式捕获外部的所有变量  
&emsp;[this]表示捕获外部的this指针  
&emsp;[=,&a]表示以传值的方式捕获外部的所有变量，但是a变量以传引用的方式捕获  
&emsp;[a,b]表示以值传递的方式捕获外部变量a和b  

如果lambda表达式的返回值不需要，那么"->返回值"可以省略  
lambda函数为常方法const，函数内部不能修改成员变量，可以通过mutable修饰，mutable与const相反，表示函数内部可以修改成员变量，可以覆盖const的限制  
#### C++的mutable和volatile
mutable只能作用在类成员上，指示其数据总是可变的。不能和const同时修饰一个成员，但能配合使用：const修饰的方法中，mutable修饰的成员数据可以发生改变，除此之外不应该对类/对象带来副作用。  
const方法中不允许对常规成员进行变动，但mutable成员不受此限制 

volatile用于修饰成员或变量，指示其修饰对象可能随时变化，编译器不要对所修饰变量进行优化（缓存），每次取值应该直接读取内存。由于volatile的变化来自运行期，其可以与const一起使用。  
在volatile的修饰下，每次循环都会检查内存中的值，达到同步的效果。  
需要注意的是，volatile的值可能随时会变，期间会导致非预期的结果。  

**总结:**  
mutable只能用与类变量，不能与const同时使用；在const修饰的方法中，mutable变量数值可以发生改变；  
volatile只是运行期变量的值随时可能改变，这种改变即可能来自其他线程，也可能来自外部系统。


```cpp
template <typename T=void>
class TestLambda01
{
public:
    void operator()()const   //参数个数为空   常方法，成员变量不能修改
    {
        cout << "hello world" << endl;
    }
};
template <typename T=int>
class TestLambda02
{
public:
    T operator()(int a,int b)const   //参数个数为空
    {
        return a+b;
    }
};
int main()
{
    auto func1 = []()->void {cout << "hello world" << endl; };
    func1();
    //上下两条作用机理相同
    TestLambda01<> t1;
    t1();
    

    auto func2 = [](int a, int b)->int {return a + b; };
    cout << func2(78, 98) << endl;

    TestLambda02<> t2;
    cout << t2(1, 3) << endl;

    //如果lambda表达式的返回值不需要，那么"->返回值"可以省略
    auto func3 = []() {cout << "ni hao" << endl; };
    func3();

    
    int a = 3, b = 55;
    auto func4 = [=]()mutable {int temp = a; a = b; b = temp; };
    //lambda函数为常方法const，函数内部不能修改成员变量，可以通过mutable修饰，
    //mutable与const相反，表示函数内部可以修改成员变量，可以覆盖const的限制
    //mutable只能作用在类成员上，指示其数据总是可变的。不能和const同时修饰一个成员，
    //但能配合使用：const修饰的方法中，mutable修饰的成员数据可以发生改变，
    //除此之外不应该对类/对象带来副作用。
    func4();
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    //按值传递，变量本体没有修改
    //按引用传递，可以修改引用指针所指向的值
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

    //把65按序插入vector
    //lambda不用纠结是几元函数都可以处理
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

既然lambda表达式只能使用在语句当中，如果想跨语句使用之前定义好的表达式，该怎么办？  
lambda表达式是函数对象，可以用function类型保留函数对象的类型
```cpp
int main()
{
    map<int, function<int(int, int)>> caculateMap;
    caculateMap[1] = [](int a, int b)->int {return a + b; };
    caculateMap[2] = [](int a, int b)->int {return a - b; };
    caculateMap[3] = [](int a, int b)->int {return a * b; };
    caculateMap[4] = [](int a, int b)->int {return a / b; };

    cout << "选择:";
    int choice;
    cin >> choice;
    cout << "result=" << caculateMap[choice](1, 14) << endl;

    return 0;
}
```