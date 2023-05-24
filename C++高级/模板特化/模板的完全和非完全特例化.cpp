#include <iostream>
#include <string>
using namespace std;

#define USE 1
#define N_USE 0

//模板的完全特例化
#if N_USE
template <typename T>
bool compare(T a, T b)
{
	cout << "template compare" << endl;
	return a > b;
}

template <>   //完全特例化，参数类型完全已知   有原模板才能提供特例化
bool compare<const char*>(const char* a, const char* b)
{
	cout << "compare <const char*>" << endl;
	return strcmp(a, b) > 0;
}
int main()
{
	compare(10, 20);
	compare("aaa", "bbb");

	return 0;
}
#endif


//模板的非完全特例化
#if N_USE
template <typename T>
class Vector
{
public:
	Vector() { cout << "call Vecotr template init" << endl; }
};

template <>   //完全特例化
class Vector<char *>
{
public:
	Vector() { cout << "call Vecotr<char *> template init" << endl; }
};

template <typename Ty>   //针对指针类型提供的部分特例化版本
class Vector<Ty*>
{
public:
	Vector() { cout << "call Vecotr<Ty *> template init" << endl; }
};

template <typename R,typename A1,typename A2>
class Vector<R(*)(A1, A2)>   //针对函数指针提供的部分特例化
{
public:
	Vector() { cout << "call Vecotr<R(*)(A1,A2)> template init" << endl; }
};
template <typename R,typename A1,typename A2>
class Vector<R(A1, A2)>   //针对函数类型提供的部分特例化
{
public:
	Vector() { cout << "call Vecotr<R(A1,A2)> template init" << endl; }
};

int main()
{
	Vector<int> vec;
	Vector<char*> vec2;
	Vector<int*> vec3;
	Vector<int(*)(int, int)> vec4;
	Vector<int(int, int)> vec5;


	return 0;
}
#endif

//模板的实参推演
#if N_USE
template <typename T>
void func(T a)
{
	cout << typeid(T).name() << endl;
}
template <typename R,typename A1,typename A2>
void func2(R(*a)(A1,A2))
{
	cout << typeid(R).name() << endl;
	cout << typeid(A1).name() << endl;
	cout << typeid(A2).name() << endl;
}
int sum(int a, int b)
{
	return a + b;
}
int main()
{
	func(10);
	func("aaa");
	func(sum);   //自动推演出sum是函数指针类型
	func2(sum);

	return 0;
}
#endif