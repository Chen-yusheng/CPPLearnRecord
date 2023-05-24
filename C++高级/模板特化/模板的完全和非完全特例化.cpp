#include <iostream>
#include <string>
using namespace std;

#define USE 1
#define N_USE 0

//ģ�����ȫ������
#if N_USE
template <typename T>
bool compare(T a, T b)
{
	cout << "template compare" << endl;
	return a > b;
}

template <>   //��ȫ������������������ȫ��֪   ��ԭģ������ṩ������
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


//ģ��ķ���ȫ������
#if N_USE
template <typename T>
class Vector
{
public:
	Vector() { cout << "call Vecotr template init" << endl; }
};

template <>   //��ȫ������
class Vector<char *>
{
public:
	Vector() { cout << "call Vecotr<char *> template init" << endl; }
};

template <typename Ty>   //���ָ�������ṩ�Ĳ����������汾
class Vector<Ty*>
{
public:
	Vector() { cout << "call Vecotr<Ty *> template init" << endl; }
};

template <typename R,typename A1,typename A2>
class Vector<R(*)(A1, A2)>   //��Ժ���ָ���ṩ�Ĳ���������
{
public:
	Vector() { cout << "call Vecotr<R(*)(A1,A2)> template init" << endl; }
};
template <typename R,typename A1,typename A2>
class Vector<R(A1, A2)>   //��Ժ��������ṩ�Ĳ���������
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

//ģ���ʵ������
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
	func(sum);   //�Զ����ݳ�sum�Ǻ���ָ������
	func2(sum);

	return 0;
}
#endif