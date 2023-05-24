
//2:32:00

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class BigInt
{
public:
	BigInt(string str) :strDigit(str)
	{

	}

private:
	string strDigit;   //使用字符串存储大整数

	friend ostream& operator<<(ostream& out, const BigInt& src);
	friend BigInt operator+(const BigInt & lhs, const BigInt & rhs);
	friend BigInt operator-(const BigInt & lhs, const BigInt & rhs);
};

//打印函数
ostream& operator<<(ostream& out, const BigInt& src)
{
	out << src.strDigit;
	return out;
}

//大数加法
BigInt operator+(const BigInt& lhs, const BigInt& rhs)
{
	string result;
	bool flag = false;   //考虑进位
	int size1 = lhs.strDigit.length() - 1;
	int size2 = rhs.strDigit.length() - 1;
	int i = size1, j = size2;

	for (; i >= 0 && j >= 0; --i, --j)
	{
		int ret = lhs.strDigit[i] - '0' + rhs.strDigit[j] - '0';
		if (flag)
		{
			ret += 1;
			flag = false;
		}
		if (ret >= 10)
		{
			ret %= 10;
			flag = true;
		}
		result.push_back(ret + '0');
	}

	//其中某个先完了
	if (i >= 0)
	{
		while (i >= 0)
		{
			int ret = lhs.strDigit[i] - '0';
			if (flag)
			{
				ret += 1;
				flag = false;
			}

			if (ret >= 10)
			{
				ret %= 10;
				flag = true;
			}

			result.push_back(ret + '0');
			i--;
		}
	}
	else if(j >= 0)
	{
		while (j >= 0)
		{
			int ret = rhs.strDigit[j] - '0';
			if (flag)
			{
				ret += 1;
				flag = false;
			}

			if (ret >= 10)
			{
				ret %= 10;
				flag = true;
			}

			result.push_back(ret + '0');
			j--;
		}
	}

	if (flag)
	{
		result.push_back('1');
	}

	reverse(result.begin(), result.end());
	return result;   //return BigInt(string)
}

//大数减法
BigInt operator-(const BigInt& lhs, const BigInt& rhs)
{
	string result;
	bool  flag = false;
	bool minor = false;

	string maxStr = lhs.strDigit;
	string minStr = rhs.strDigit;
	if (maxStr.length() < minStr.length())
	{
		maxStr = rhs.strDigit;
		minStr = lhs.strDigit;
		minor = true;
	}
	else if (maxStr.length() == minStr.length())
	{
		if (maxStr < minStr)
		{
			maxStr = rhs.strDigit;
			minStr = lhs.strDigit;
			minor = true;
		}
		else if (maxStr == minStr)
		{
			return string("0");
		}
	}
	
	int size1 = maxStr.length() - 1;
	int size2 = minStr.length() - 1;
	int i = size1, j = size2;
	for (; i >= 0 && j >= 0; --i, --j)
	{
		int ret = maxStr[i] - minStr[j];
		if (flag)
		{
			ret -= 1;
			flag = false;
		}

		if (ret < 0)
		{
			ret += 10;
			flag = true;
		}
		result.push_back(ret + '0');
	}

	while (i>= 0)
	{
		int ret = maxStr[i] - '0';
		if (flag)
		{
			ret -= 1;
			flag = false;
		}
		if (ret < 0)
		{
			ret += 10;
			flag = true;
		}
		
		result.push_back(ret + '0');
		i--;
	}
	string retStr;
	auto it = result.rbegin();
	for (; it != result.rend(); ++it)
	{
		if (*it != '0')
		{
			break;
		}
	}

	for (; it != result.rend(); ++it)
	{
		retStr.push_back(*it);
	}

	if (minor)
	{
		retStr.insert(retStr.begin(), '-');
	}

	return retStr;
}


#if 0
int main()
{
	BigInt int1("334654767822");
	BigInt int2("71142343254765876");
	BigInt int3("382957392592580257");

	cout << int1 + int2 << endl;
	cout << int1 - int3 << endl;

	BigInt int4("999");
	BigInt int5("998");
	cout << int4 - int5 << endl;
	cout << int5 - int4 << endl;




	return 0;
}
#endif