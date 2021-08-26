#include <iostream>
#include <cmath>
#include <conio.h>
#include <string>
#include <vector>
#include <bitset>
#include <math.h>
#include <fstream>

using namespace std;
struct QInt
{
	unsigned data[4];

};
template <class T>
void swap(T& x, T& y)
{
	T temp;
	temp = x;
	x = y;
	y = temp;
}

//string divBy2(string t)
//{
//	string number = t;
//	int next = 0;
//	int cur;
//	for (int i = 0; i < number.size(); i++)
//	{
//		cur = next;
//		if ((number[i] - '0') % 2 != 0)
//		{
//			next = 5;
//		}
//		else
//		{
//			next = 0;
//		}
//		number[i] = (number[i] - '0') / 2 + cur + '0';
//	}
//	while (number[0] == '0'&&number.size() != 1)
//	{
//		number.erase(number.begin());
//	}
//	return number;
//}
string Nhan2(string number)
{
	string result(number.size() + 1, '0');
	int nho = 0;
	for (int i = number.size() - 1; i >= 0; i--)
	{
		int tich = 2 * (number[i] - '0') + nho;
		if (tich > 9)
		{
			result[i + 1] = tich - 10 + '0';
			nho = 1;
		}
		else
		{
			result[i + 1] = tich + '0';
			nho = 0;
		}
		if (i == 0)
		{
			if (nho == 1)
			{
				result[0] = '1';
			}
			else
			{
				result.erase(result.begin());
			}
		}
	}
	return result;
}
string Hai_Mu_N(int N)
{
	string result = "1";
	for (int i = 0; i < N; i++)
	{
		result = Nhan2(result);
	}
	return result;
}

string strCongStr(string a, string b)
{
	// chắc chắn rằng size a lớn hơn size b 
	if (a.size() < b.size())
	{
		swap(a, b);
	}
	string result(a.size(), '0');
	int n1 = a.size();
	int n2 = b.size();
	// n1 > n2
	int nho = 0;
	for (int i = 0; i < n2; i++)
	{
		result[result.size() - 1 - i] = (a[n1 - 1 - i] - '0') + (b[n2 - 1 - i] - '0') + nho;
		if (result[result.size() - 1 - i] > 9)
		{
			result[result.size() - 1 - i] = result[result.size() - 1 - i] - 10 + '0';
			nho = 1;
		}
		else
		{
			result[result.size() - 1 - i] = result[result.size() - 1 - i] + '0';
			nho = 0;
		}
	}
	for (int i = result.size() - n2 - 1; i >= 0; i--)
	{
		result[i] = (a[i] - '0') + nho;
		if (result[i] > 9)
		{
			result[i] = result[i] - 10 + '0';
			nho = 1;
		}
		else
		{
			result[i] = result[i] + '0';
			nho = 0;
		}
	}

	if (nho == 1)
	{
		result.insert(result.begin(), '1');
	}
	while (result[0] == '0'&&result.size() != 1)
	{
		result.erase(result.begin());
	}
	return result;
}

// trả về *bool ( 128 phần tử )
bool * DecToBin(QInt x)
{
	bool *a = new bool[128];
	for (int k = 0; k <128; k++)
	{
		a[k] = (x.data[k / 32] >> (32 - 1 - k % 32)) & 1;
	}
	return a;
}
// trả về QInt , tham số : mảng bool "128 PHẦN TỬ"
QInt BinToDec(bool *bit)
{
	QInt x = { 0 };
	for (int k = 0; k < 128; k++)
	{
		if (bit[k] == 1)
		{
			x.data[k / 32] = (1 << (32 - 1 - (k % 32))) | x.data[k / 32];
		}
	}
	return x;
}
// trả về chuỗi HEXA , tham số : mảng bool "128 phần tử"
char *BinToHex(bool *bit)
{

	// gom 32 đoạn 4 bit
	int startIndex = 127;
	for (int i = 0; i < 128; i++)
	{
		// tìm đoạn bit bắt đầu có giá trị ( có bit 1 )
		if (bit[i] == 1)
		{
			startIndex = (i / 4) * 4;
			break;
		}
	}
	int size = (128 - startIndex) / 4;
	// chứa thêm NULL cuối chuỗi
	char *result = new char[size + 1];
	result[size] = NULL;
	int resultIndex = 0;
	string numberArray[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16" };
	char characterArray[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	string temp;
	// có được cụm 4 bit đầu tiên có giá trị

	for (int i = startIndex; i <= 124; i += 4)
	{

		temp = "0";
		for (int j = i + 3; j >= i; j--)
		{
			if (bit[j] == 1)
				temp = strCongStr(temp, Hai_Mu_N(i + 3 - j));
		}
		for (int k = 0; k < 16; k++)
		{
			if (temp == numberArray[k])
			{
				result[resultIndex++] = characterArray[k];
				break;
			}
		}
	}
	return result;
}
// trả về chuỗi HEXA, tham số : QInt
char *DecToHex(QInt x)
{
	bool *a = DecToBin(x);
	char *result = BinToHex(a);
	delete a;
	return result;
}
//QInt operator+(const QInt &n1, const QInt &n2)
//{
//	bool *a = DecToBin(n1);
//	bool *b = DecToBin(n2);
//	bool c[128] = { 0 };
//	unsigned int nho1 = 0;
//	for (int i = 127; i >= 0; i--)
//	{
//		if (a[i] + b[i] + nho1 > 1)
//		{
//			c[i] = a[i] + b[i] + nho1 - 2;
//			nho1 = 1;
//		}
//		else
//		{
//			c[i] = a[i] + b[i] + nho1;
//			nho1 = 0;
//		}
//	}
//	QInt result = BinToDec(c);
//	return result;
//}
QInt shiftLeft1(QInt x)
{
	//shift left
	QInt result;
	for (int i = 0; i < 4; i++)
	{
		result.data[i] = x.data[i] << 1;
	}
	for (int j = 1; j < 4; j++)
	{
		if (((x.data[j] >> 31) & 1) == 1)
		{
			result.data[j - 1] = 1 | result.data[j - 1];
		}
	}
	return result;
}

// các phép dịch luận lý
QInt shiftRight1(QInt x)
{
	//shift right
	QInt result;
	for (int i = 0; i < 4; i++)
	{
		result.data[i] = x.data[i] >> 1;
	}
	for (int j = 0; j < 3; j++)
	{
		if (((x.data[j]) & 1) == 1)
		{
			result.data[j + 1] = (1 << 31) | result.data[j + 1];
		}
	}
	/*if ((x.data[1] >> 31) & 1 == 1)
	{
	result.data[0] = result.data[0] | (1 << 31);
	}*/
	return result;

}
// trả về x << k ( shift left ) hoặc x >> k ( shift right ) --- type : "left" hoặc "right
QInt shift(QInt x, unsigned int k, string type)
{
	QInt result;
	if (type == "left")
	{
		for (int i = 0; i < k; i++)
		{
			result = shiftLeft1(x);
			x = shiftLeft1(x);
		}
	}
	else if (type == "right")
	{
		for (int i = 0; i < k; i++)
		{
			result = shiftRight1(x);
			x = shiftRight1(x);
		}
	}
	else
	{
		return x;
	}

	return result;
}
// rotate left hoặc right k lần , type: "left" hoặc "right"
QInt operator <<(const QInt &x, unsigned k)
{
	QInt result;
	result = shift(x, k, "left");
	return result;
}
QInt operator >>(const QInt &x, unsigned k)
{
	QInt result;
	result = shift(x, k, "right");
	return result;
}

//-------
QInt operator &(const QInt &x, const QInt &y)
{
	QInt result;
	for (int i = 0; i < 4; i++)
	{
		result.data[i] = x.data[i] & y.data[i];
	}
	return result;
}
QInt operator |(const QInt &x, const QInt &y)
{
	QInt result;
	for (int i = 0; i < 4; i++)
	{
		result.data[i] = x.data[i] | y.data[i];
	}
	return result;
}
QInt operator ^(const QInt &x, const QInt &y)
{
	QInt result;
	for (int i = 0; i < 4; i++)
	{
		result.data[i] = (x.data[i] ^ y.data[i]);
	}
	return result;
}
QInt operator ~(const QInt &x)
{
	QInt result = { 0 };
	for (int i = 0; i < 4; i++)
	{
		result.data[i] = ~(x.data[i]);
	}
	return result;
}
bool operator ==(QInt &x1, QInt &x2)
{
	for (int i = 0; i < 4; i++)
	{
		if (x1.data[i] != x2.data[i])
			return false;
	}
	return true;
}
bool operator <(QInt &x1, QInt &x2)
{
	bool a[128];
	for (int i = 0; i < 128; i++)
	{
		bool k = x1.data[i / 32] & (1 << 31 - i % 32);
		a[i] = k;
	}
	bool b[128];
	for (int i = 0; i < 128; i++)
	{
		bool k = x2.data[i / 32] & (1 << 31 - i % 32);
		b[i] = k;
	}
	if (a[0] == false && b[0] == true)
		return false;
	else if (a[0] == true && b[0] == false)
		return true;
	else
	{
		for (int i = 0; i < 128; i++)
		{
			if (a[i] < b[i])
				return true;
			else if (a[i]>b[i])
				return false;
		}
		return false;
	}
}
bool operator<=(QInt x1, QInt x2)
{
	bool a[128];
	for (int i = 0; i < 128; i++)
	{
		bool k = x1.data[i / 32] & (1 << 31 - i % 32);
		a[i] = k;
	}
	bool b[128];
	for (int i = 0; i < 128; i++)
	{
		bool k = x2.data[i / 32] & (1 << 31 - i % 32);
		b[i] = k;
	}
	if (a[0] == false && b[0] == true)
		return false;
	else if (a[0] == true && b[0] == false)
		return true;
	else
	{
		for (int i = 0; i < 128; i++)
		{
			if (a[i] < b[i])
				return true;
			else if (a[i] > b[i])
				return false;
		}
		return true;
	}
}
bool operator>(QInt x1, QInt x2)
{
	bool a[128];
	for (int i = 0; i < 128; i++)
	{
		bool k = x1.data[i / 32] & (1 << 31 - i % 32);
		a[i] = k;
	}
	bool b[128];
	for (int i = 0; i < 128; i++)
	{
		bool k = x2.data[i / 32] & (1 << 31 - i % 32);
		b[i] = k;
	}
	if (a[0] == false && b[0] == true)
		return true;
	else if (a[0] == true && b[0] == false)
		return false;
	else
	{
		for (int i = 0; i < 128; i++)
		{
			if (a[i] > b[i])
				return true;
			else if (a[i] < b[i])
				return false;
		}
		return false;
	}
}
bool operator >= (QInt x1, QInt x2)
{
	bool a[128];
	for (int i = 0; i < 128; i++)
	{
		bool k = x1.data[i / 32] & (1 << 31 - i % 32);
		a[i] = k;
	}
	bool b[128];
	for (int i = 0; i < 128; i++)
	{
		bool k = x2.data[i / 32] & (1 << 31 - i % 32);
		b[i] = k;
	}
	if (a[0] == false && b[0] == true)
		return true;
	else if (a[0] == true && b[0] == false)
		return false;
	else
	{
		for (int i = 0; i < 128; i++)
		{
			if (a[i] > b[i])
				return true;
			else if (a[i] < b[i])
				return false;
		}
		return true;
	}
}
QInt rol(const QInt &x, unsigned int k)
{
	return (x << k) | (x >> (128 - k));
}
QInt ror(const QInt &x, unsigned int k)
{
	return (x >> k) | (x << (128 - k));
}
//type :
//1: toan tu hai ngoi:"+","-","*","/",">>","<<","&","^","rol","ror",“<”, “>”, “==”, “<=”, “>=”
//2:toan tu mot ngoi: ~
//3: covert   
void getInput(string input, char &type_get, string &operator_get, string &base1, string &base2, string &operand1, string &operand2)
{
	// toan tu 2 ngoi
	for (int i = 0; i < input.size(); i++)
	{
		if (((input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^' || input[i] == '|' || input[i] == '&' || input[i] == '<' || input[i] == '>') && (input[i + 1] == ' '))
			|| ((input[i] == '='&&input[i + 1] == '=') || (input[i] == '>'&&input[i + 1] == '=') || (input[i] == '<'&&input[i + 1] == '=') || (input[i] == '>'&&input[i + 1] == '>') || (input[i] == '<'&&input[i + 1] == '<'))
			|| (input[i] == 'r')
			)
		{
			type_get = '1';
			// luu base 1
			if (input[0] == '1')
			{
				string temp = input.substr(0, 2);
				if (temp == "16")
				{
					base1 = "16";
				}
				else if (temp == "10")
				{
					base1 = "10";
				}
			}
			else
			{
				base1 = "2";
			}
			// luu operand
			for (int k = 0;; k++)
			{
				if (input[k] == ' ')
				{
					for (k = k + 1; input[k] != ' '; k++)
					{
						operand1.push_back(input[k]);
					}
					for (k = k + 3; k<input.size(); k++)
					{
						if (input[k] != ' '&&input[k] != 'l' && input[k] != 'r')
							operand2.push_back(input[k]);
					}
					break;
				}
			}
			for (int j = i; input[j] != ' '; j++)
			{
				operator_get.push_back(input[j]);
			}
			return;
		}
	}
	// toan tu mot ngoi : "~"
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '~')
		{
			type_get = '2';
			operator_get = "~";
			// luu base 1
			if (input[0] == '1')
			{
				string temp = input.substr(0, 2);
				if (temp == "16")
				{
					base1 = "16";
				}
				else if (temp == "10")
				{
					base1 = "10";
				}
			}
			else
			{
				base1 = "2";
			}
			for (int k = 0;; k++)
			{
				if (input[k] == ' ')
				{
					for (k = k + 1; input[k] != ' '; k++)
					{
						operand1.push_back(input[k]);
					}
					break;
				}
			}
			return;
		}
	}

	//nếu không phải 2 trường hợp trên thì là convert giữa 2 hệ cơ số
	type_get = '3';
	// luu base 1 va base 2
	for (int i = 0;; i++)
	{
		if (input[i] != ' ')
			base1.push_back(input[i]);
		else
		{
			for (i = i + 1; input[i] != ' '; i++)
			{
				base2.push_back(input[i]);
			}
			// lưu số cần convert vào operand1
			for (i = i + 1; i<input.size(); i++)
			{
				operand1.push_back(input[i]);
			}
			break;
		}
	}

}
/// cau 1 
string findSum(string str1, string str2)
{
	// Truoc khi cong, chac chan chuoi 2 dai hon 
	if (str1.length() > str2.length())
		swap(str1, str2);

	// Chuoi ket qua
	string str = "";

	// Lay do dai 2 chuoi
	int n1 = str1.length(), n2 = str2.length();

	// Dao nguoc hai chuoi
	reverse(str1.begin(), str1.end());
	reverse(str2.begin(), str2.end());

	// bien de luu nho
	int carry = 0;
	for (int i = 0; i < n1; i++)
	{
		int sum = ((str1[i] - '0') + (str2[i] - '0') + carry);
		str.push_back(sum % 10 + '0');
		carry = sum / 10;
	}

	// Them cac chu so con lai cua so lon hon
	for (int i = n1; i < n2; i++)
	{
		int sum = ((str2[i] - '0') + carry);
		str.push_back(sum % 10 + '0');
		carry = sum / 10;
	}

	// Them phan nho
	if (carry)
		str.push_back(carry + '0');

	// Dao nguoc chuoi ket qua
	reverse(str.begin(), str.end());

	return str;
}
string strdiv2(string scr)
{
	// Ket qua tra ve luu trong chuoi rt
	string rt;
	// Tim phan dau lon hon 2 trong chuoi can chia (Vd: 123:2, 1 chia 2 ko duoc, lay 12 chia 2)
	int idx = 0;
	int temp = scr[idx] - '0';
	while (temp < 2)
		temp = temp * 10 + (scr[++idx] - '0');
	// Chia temp cho 2, lien tuc cap nhat lai temp sau moi lan chia
	while (scr.size() > idx)
	{
		// Lay ket qua
		rt += (temp / 2) + '0';

		// Lay chu so tiep theo 
		temp = (temp % 2) * 10 + scr[++idx] - '0';
	}
	if (rt.length() == 0)
		return "0";
	return rt;
}
void ScanQInt10(QInt &x, string s)
{
	bool a[128] = { 0 };
	int sign = 0; //Khoi tao la so duong
	if (s == "0")
	{
		return;
	}

	if (s[0] == '-')
	{
		sign = 1;
		s = s.substr(1);
	}

	for (int i = 127; i >= 0 && s.size() > 0; i--)
	{
		int l = s.length();
		if (s == "1")
		{
			a[i] = 1;
			break;
		}
		a[i] = (s[l - 1] - '0') % 2;
		s = strdiv2(s);
	}
	for (int i = 0; i < 128; i++)
	{
		if (a[i] == 1)
			x.data[i / 32] = x.data[i / 32] | (1 << (32 - 1 - i % 32));
	}
	//Neu la so am
	if (sign == 1)
	{
		// Dao bit chuyen sang bu 1
		for (int i = 0; i < 128; i++)
		{
			//x.data[i / 32] = ~x.data[i / 32];
			x.data[i / 32] = x.data[i / 32] ^ (1 << 32 - 1 - i % 32);
		}

		int m = 1;
		for (int i = 127; i >= 0; i--)
		{
			m = 1 << (32 - 1 - i % 32);
			if (x.data[i / 32] & m)
			{
				x.data[i / 32] = x.data[i / 32] ^ m;
			}
			else
			{
				x.data[i / 32] = x.data[i / 32] ^ m;
				break;
			}
		}
	}

}
void ScanQInt2(QInt &x, string s)
{
	bool a[128] = { 0 };
	// Chuyen tu chuoi vao mang a[128]
	for (int i = s.size() - 1; i >= 0; i--)
	{
		a[i + 127 - s.size() + 1] = s[i] - '0';
	}
	// Chuyen vao QInt
	for (int i = 0; i < 128; i++)
	{
		if (a[i] == 1)
			x.data[i / 32] = x.data[i / 32] | (1 << (32 - 1 - i));
	}
}
void ScanQInt16(QInt &x, string s)
{
	bool a[128] = { 0 };
	int l = s.size();
	// Do dai so luu duoc khong qua 32
	if (l > 32)
		s = s.substr(l - 32);
	else if (l < 32)
	{
		for (int i = 0; i < 32 - l; i++)
		{
			s = '0' + s;
		}
	}
	for (int i = 32; i >= 1; i--)
	{
		if (s[i - 1] == '0')
		{
			a[i * 4 - 1] = 0; a[i * 4 - 2] = 0; a[i * 4 - 3] = 0; a[i * 4 - 4] = 0;
		}
		else if (s[i - 1] == '1')
		{
			a[i * 4 - 1] = 1; a[i * 4 - 2] = 0; a[i * 4 - 3] = 0; a[i * 4 - 4] = 0;
		}
		else if (s[i - 1] == '2')
		{
			a[i * 4 - 1] = 0; a[i * 4 - 2] = 1; a[i * 4 - 3] = 0; a[i * 4 - 4] = 0;
		}
		else if (s[i - 1] == '3')
		{
			a[i * 4 - 1] = 1; a[i * 4 - 2] = 1; a[i * 4 - 3] = 0; a[i * 4 - 4] = 0;
		}
		else if (s[i - 1] == '4')
		{
			a[i * 4 - 1] = 0; a[i * 4 - 2] = 0; a[i * 4 - 3] = 1; a[i * 4 - 4] = 0;
		}
		else if (s[i - 1] == '5')
		{
			a[i * 4 - 1] = 1; a[i * 4 - 2] = 0; a[i * 4 - 3] = 1; a[i * 4 - 4] = 0;
		}
		else if (s[i - 1] == '6')
		{
			a[i * 4 - 1] = 0; a[i * 4 - 2] = 1; a[i * 4 - 3] = 1; a[i * 4 - 4] = 0;
		}
		else if (s[i - 1] == '7')
		{
			a[i * 4 - 1] = 1; a[i * 4 - 2] = 1; a[i * 4 - 3] = 1; a[i * 4 - 4] = 0;
		}
		else if (s[i - 1] == '8')
		{
			a[i * 4 - 1] = 0; a[i * 4 - 2] = 0; a[i * 4 - 3] = 0; a[i * 4 - 4] = 1;
		}
		else if (s[i - 1] == '9')
		{
			a[i * 4 - 1] = 1; a[i * 4 - 2] = 0; a[i * 4 - 3] = 0; a[i * 4 - 4] = 1;
		}
		else if (s[i - 1] == 'A')
		{
			a[i * 4 - 1] = 0; a[i * 4 - 2] = 1; a[i * 4 - 3] = 0; a[i * 4 - 4] = 1;
		}
		else if (s[i - 1] == 'B')
		{
			a[i * 4 - 1] = 1; a[i * 4 - 2] = 1; a[i * 4 - 3] = 0; a[i * 4 - 4] = 1;
		}
		else if (s[i - 1] == 'C')
		{
			a[i * 4 - 1] = 0; a[i * 4 - 2] = 0; a[i * 4 - 3] = 1; a[i * 4 - 4] = 1;
		}
		else if (s[i - 1] == 'D')
		{
			a[i * 4 - 1] = 1; a[i * 4 - 2] = 0; a[i * 4 - 3] = 1; a[i * 4 - 4] = 1;
		}
		else if (s[i - 1] == 'E')
		{
			a[i * 4 - 1] = 0; a[i * 4 - 2] = 1; a[i * 4 - 3] = 1; a[i * 4 - 4] = 1;
		}
		else if (s[i - 1] == 'F')
		{
			a[i * 4 - 1] = 1; a[i * 4 - 2] = 1; a[i * 4 - 3] = 1; a[i * 4 - 4] = 1;
		}
	}
	// Chuyen vao QInt
	for (int i = 0; i < 128; i++)
	{
		if (a[i] == 1)
			x.data[i / 32] = x.data[i / 32] | (1 << (32 - 1 - i % 32));
	}
}
void PrintQInt2(QInt x)
{
	ofstream out;
	out.open("OUTPUT.txt", ios_base::app);
	for (int i = 0; i < 4; i++)
	{
		out << bitset<32>(x.data[i]);
	}
	out << endl;
	out.close();
}
void PrintQInt16(QInt x)
{
	ofstream out;
	out.open("OUTPUT.txt", ios_base::app);
	char *result = DecToHex(x);
	out << result << endl;
	out.close();
}
void PrintQInt10(QInt x)
{
	bool a[128] = {};
	int sign = 0;
	string s = "0";

	// Chuyen QInt vao mang

	if (x.data[0] >> (32 - 1) & 1)
	{
		sign = 1;
		int m = 1, k = 0;
		for (int i = 127; i >= 0; i--)
		{
			m = m << 32 - 1 - i % 32;
			bool k = x.data[i / 32] & m;// kiem tra tai sao xor khong dc
			if (k == 0)
			{
				x.data[i / 32] = x.data[i / 32] ^ m;
			}
			else
			{
				x.data[i / 32] = x.data[i / 32] ^ m;
				break;
			}
			m = 1;
		}
		// Dao bit
		for (int i = 0; i < 128; i++)
		{
			//x.data[i / 32] = ~x.data[i / 32];
			x.data[i / 32] = x.data[i / 32] ^ (1 << 32 - 1 - i % 32);
		}
	}
	for (int i = 0; i < 128; i++)
	{
		a[i] = (x.data[i / 32] >> 32 - 1 - i % 32) & 1;
	}
	// Chuyen mang thanh chuoi

	for (int i = 127; i >= 0; i--)
	{
		if (a[i] != 0)
		{
			s = findSum(s, Hai_Mu_N(127 - i));
		}
	}
	if (sign == 1)
		s = '-' + s;
	ofstream out;
	out.open("OUTPUT.txt", ios_base::app);
	out << s << endl;
	out.close();
}
void PrintBool(bool x)
{
	ofstream out;
	out.open("OUTPUT.txt", ios_base::app);
	out << x << endl;
	out.close();

}
QInt operator+(QInt a, QInt b)
{
	QInt tong = { 0 };
	bool x, y, nho = 0;
	int temp;
	for (int i = 127; i >= 0; i--)
	{
		x = a.data[i / 32] & 1 << 32 - 1 - i % 32;
		y = b.data[i / 32] & 1 << 32 - 1 - i % 32;
		temp = x + y + nho;
		if (temp == 1)
		{
			tong.data[i / 32] = tong.data[i / 32] | 1 << 32 - 1 - i % 32;
			nho = 0;
		}
		else if (temp == 2)
		{
			nho = 1;
		}
		else if (temp == 3)
		{
			tong.data[i / 32] = tong.data[i / 32] | 1 << 32 - 1 - i % 32;
			nho = 1;
		}
	}
	return tong;
}
QInt operator-(QInt a, QInt b)
{
	QInt hieu = { 0 };
	bool x, y, nho = 0;
	int temp;
	for (int i = 127; i >= 0; i--)
	{
		x = a.data[i / 32] & 1 << 32 - 1 - i % 32;
		y = b.data[i / 32] & 1 << 32 - 1 - i % 32;
		if (nho == 0)
		{
			temp = x - y;
		}
		else
		{
			temp = x - y - 1;
			nho = 0;
		}
		//temp <0;
		if (temp < 0)
		{
			temp = 2 + temp;
			nho = 1;
		}
		if (temp == 1)
		{
			hieu.data[i / 32] = hieu.data[i / 32] | 1 << 32 - 1 - i % 32;
		}
	}
	return hieu;
}
QInt operator*(QInt x, QInt y)
{
	QInt kq = { 0 };
	for (int i = 0; i < 128; i++)
	{
		bool k = y.data[3] & 1;
		if (k && 1)
		{
			kq = kq + x;
		}
		x = x << 1;
		y = y >> 1;
	}
	return kq;
}
QInt amSangDuong(QInt x)
{
	int m = 1, k = 0;
	//- cho 1
	for (int i = 127; i >= 0; i--)
	{
		m = m << 32 - 1 - i % 32;
		bool k = x.data[i / 32] & m;// kiem tra tai sao xor khong dc
		if (k == 0)
		{
			x.data[i / 32] = x.data[i / 32] ^ m;
		}
		else
		{
			x.data[i / 32] = x.data[i / 32] ^ m;
			break;
		}
		m = 1;
	}
	//dao data
	for (int i = 0; i < 128; i++)
		x.data[i / 32] = x.data[i / 32] ^ (1 << 32 - 1 - i % 32);
	return x;
}
QInt duongSangAm(QInt x)
{
	//dao bit
	for (int i = 0; i < 128; i++)
		x.data[i / 32] = x.data[i / 32] ^ (1 << 32 - 1 - i % 32);
	// phep cong cho 1
	int m = 1;
	for (int i = 127; i >= 0; i--)
	{
		m = 1 << 32 - 1 - i % 32;
		if (x.data[i / 32] & m)
		{
			x.data[i / 32] = x.data[i / 32] ^ m;
		}
		else
		{
			x.data[i / 32] = x.data[i / 32] ^ m;
			break;
		}
	}
	return x;
}
QInt operator/(QInt x, QInt y)
{
	int a = 0, b = 0;
	//cho x y deu duong
	if (x.data[0] >> 31 && 1)
	{
		x = amSangDuong(x);
		a = 1;
	}
	if (y.data[0] >> 31 && 1)
	{
		y = amSangDuong(y);
		b = 1;
	}
	QInt A;
	bool bitDau = x.data[0] >> 31 & 1;
	if (bitDau == 1)
		for (int i = 0; i < 128; i++)//gan A toan bit 1
		{
			A.data[i / 32] = A.data[i / 32] | 1 << 32 - 1 - i % 32;
		}
	for (int i = 127; i >= 0; i--)
	{
		A = A << 1;
		bool k = x.data[0] >> 31 & 1;
		if (k == 1)
		{
			A.data[3] = A.data[3] | 1;
		}
		x = x << 1;
		A = A - y;
		bitDau = A.data[0] >> 31 & 1;
		if (bitDau == 1)
		{
			A = A + y;
		}
		else
		{
			x.data[3] = x.data[3] | 1;
		}
	}
	if (a == 0 && b == 1)//x duong y am
	{
		x = duongSangAm(x);
	}
	else if (a == 1 && b == 0)//x am y duong
	{
		QInt temp;
		temp.data[3] = temp.data[3] | 1;
		x = duongSangAm(x + temp);
		A = y - A;//so chia - so du khi duong
	}
	else if (a == 1 && b == 1)// x am y am
	{
		QInt temp;
		temp.data[3] = temp.data[3] | 1;
		x = x + temp;
		A = y - A;//so chia - so du khi duong
	}
	return x;
}

//---------------------------------------------------
// cau 2

char ChangeIntToChar(int n)
{
	if (n < 10)
		return '0' + n;
	return n - 10 + 'A';
}
int ChangeCharToInt(char c)
{
	if (c <= '9' && c >= '0')
		return c - '0';
	return c - 'A' + 10;
}
string DevideString(string a)
{
	string temp;
	int bu = 0;
	for (int i = 0; i < a.length(); i++)
	{
		int temp1 = ChangeCharToInt(a[i]);
		temp1 += bu * 10;
		if (temp1 == 1 && i != 0)
		{
			bu = 1;
			temp.push_back('0');
			continue;
		}
		if (temp1 == 1 && i != a.length() - 1)
		{
			bu = 1;
			continue;
		}
		int temp2 = temp1 / 2;
		temp.push_back(ChangeIntToChar(temp2));
		bu = temp1 % 2;
	}
	return temp;
}

// Hàm nhân chuổi cho 2
string DoubleString(string a)
{
	int bu = 0;
	string KQ;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		int temp = ChangeCharToInt(a[i]);
		int kq = temp * 2;
		kq += bu;
		if (kq >= 10)
		{
			bu = kq / 10;
			kq = kq - 10;
			if (i == 0)
			{
				KQ.insert(KQ.begin(), ChangeIntToChar(kq));
				KQ.insert(KQ.begin(), ChangeIntToChar(bu));
				return KQ;
			}
		}
		else
			bu = 0;
		KQ.insert(KQ.begin(), ChangeIntToChar(kq));
	}
	return KQ;
}
bool CheckString(string a)
{
	for (int i = 1; i < a.length(); i++)
	{
		if (a[i] != '0')
			return false;
	}
	return true;
}
bool check2(string a)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != '0')
			return false;
	}
	return true;
}
struct Qfloat
{
	unsigned int data[4];
};
Qfloat BinToDecFloat(bool *data)
{
	Qfloat x;
	for (int i = 0; i < 128; i++)
	{
		if (data[i] == 1)
		{
			x.data[i / 32] = x.data[i / 32] | 1 << 32 - 1 - i % 32;
		}
	}
	return x;
}
//bài 2 hàm nhập số thực có độ chính xác cao
void PrintQfloat(Qfloat x);
void ScanQfloat(Qfloat &x)
{
	remove("OUTPUT.txt");
	fstream infile;
	infile.open("INPUT.txt", ios::in);

	while (!infile.eof())
	{
		string  a;
		int ts1, ts2;
		infile >> ts1;
		infile >> ts2;
		getline(infile, a, '\n');
		if (a == "")
			break;
		a.erase(a.begin());
		string b, c;
		vector<int>temp1;
		for (int i = 0; i < 4; i++)
			x.data[i] = 0;
		if (ts1 == 2 && ts2 == 10)
		{
			for (int i = 0; i < a.length(); i++)
			{
				temp1.push_back(ChangeCharToInt(a[i]));
			}
			if (temp1.size() < 128)
			{
				for (int i = temp1.size(); i < 128; i++)
					temp1.push_back(0);
			}
			for (int i = 127; i >= 0; i--)
			{
				if (temp1[i] == 1)
				{
					x.data[i / 32] = x.data[i / 32] | 1 << 31 - i % 32;
				}
			}

			PrintQfloat(x);
			continue;
		}
		else
		{
			if (a == "0")
			{
				for (int i = 0; i < 128; i++)
					temp1.push_back(0);
			}
			else
			{
				bool  SoAm = false;
				if (a[0] == '-')
					SoAm = true;
				int dem = 0;

				// Tách phần thực và phần ảo thành 2 chuỗi riêng biệt
				if (SoAm == true)
				{
					for (int i = 1; i < a.length(); i++)
					{
						if (a[i] == '.')
						{
							dem = i;
							break;
						}
						b.push_back(a[i]);
					}
				}
				else
				{
					for (int i = 0; i < a.length(); i++)
					{
						if (a[i] == '.')
						{
							dem = i;
							break;
						}
						b.push_back(a[i]);
					}
				}
				// tach phần ảo vào chuỗi c
				if (dem > 0)
				{
					for (int i = ++dem; i < a.length(); i++)
						c.push_back(a[i]);
				}
				int mu;
				if (c == "" || check2(c) == true)// th số nhập vào là số nguyên
				{
					while (b != "")
					{
						if (b == "1")
						{
							temp1.insert(temp1.begin(), 1);
							break;
						}
						int temp = ChangeCharToInt(b[b.length() - 1]);
						temp1.insert(temp1.begin(), temp % 2);
						b = DevideString(b);
					}
					for (int i = 0; i < temp1.size(); i++)
					{
						if (temp1[i] == 1)
						{
							temp1.erase(temp1.begin() + i);
							mu = temp1.size() - i;
							i--;
							break;
						}
					}
					int n = 112 - temp1.size();
					for (int i = 0; i < n; i++)
					{
						temp1.push_back(0);
					}
				}
				//else if (b == "0" && check2(c) == true)// TH nhập số 0.0
				//{
				//	for (int i = 0; i < 128; i++)
				//		temp1.push_back(0);
				//}
				else
				{
					int count = 0;
					// nếu phan nguyen bằng 0
					// Tách phần nguyên thành nhị phân và đưa vào mảng temp1
					if (b == "0")// Nếu phần nguyên là số 0
					{
						c.insert(c.begin(), '0');
						while (true)
						{
							c = DoubleString(c);
							if (c[0] == '1'&&CheckString(c) == true)
							{
								temp1.push_back(1);
								c[0] = '0';
								break;
							}
							else if (c[0] == '1'&&CheckString(c) != true)
							{
								temp1.push_back(1);
								c[0] = '0';
							}
							else
							{
								temp1.push_back(0);
							}
							if (temp1.size() == 112)
							{
								break;
							}
						}
						while (true)
						{
							if (temp1[0] == 1)
							{
								mu = -(count + 1);
								temp1.erase(temp1.begin());
								break;
							}
							temp1.erase(temp1.begin());
							count++;
						}
						b = "1";
						if (temp1.size() < 112)
						{
							while (true)
							{
								c = DoubleString(c);
								if (c[0] == '1'&&CheckString(c) == true)
								{
									temp1.push_back(1);
									break;
								}
								else if (c[0] == '1'&&CheckString(c) != true)
								{
									temp1.push_back(1);
									c[0] = '0';
								}
								else
								{
									temp1.push_back(0);
								}
								bool k = check2(c);
								if (temp1.size() == 112)
								{
									if (k == false)
									{
										temp1[111] = 1;
									}
									break;
								}
							}
						}
					}
					else
					{
						c.insert(c.begin(), '0');
						while (b != "")
						{
							if (b == "1")
							{
								temp1.insert(temp1.begin(), 1);
								break;
							}
							int temp = ChangeCharToInt(b[b.length() - 1]);
							temp1.insert(temp1.begin(), temp % 2);
							b = DevideString(b);
						}
						for (int i = 0; i < temp1.size(); i++)
						{
							if (temp1[i] == 1)
							{
								temp1.erase(temp1.begin() + i);
								mu = temp1.size() - i;
								i--;
								break;
							}
						}
						// chuyển phần thực thành nhị phân
						while (true)
						{
							c = DoubleString(c);
							if (c[0] == '1'&&CheckString(c) == true)
							{
								temp1.push_back(1);
								break;
							}
							else if (c[0] == '1'&&CheckString(c) != true)
							{
								temp1.push_back(1);
								c[0] = '0';
							}
							else
							{
								temp1.push_back(0);
							}
							if (temp1.size() == 112)
							{
								temp1[111] = 1;
								break;
							}
						}
					}
					if (temp1.size() < 112)
					{
						for (int i = temp1.size(); i < 112; i++)
						{
							temp1.push_back(0);
						}
					}
				}
				//chuyển phần mủ thành nhị phân
				int exponent = mu + pow(double(2), 14) - 1;
				int d[15], k = 0;
				while (k < 15)
				{
					d[k] = exponent % 2;
					exponent /= 2;
					k++;
				}

				for (int j = 0; j <= k - 1; j++)
				{
					temp1.insert(temp1.begin(), d[j]);
				}
				if (SoAm == true)
					temp1.insert(temp1.begin(), 1);
				else
					temp1.insert(temp1.begin(), 0);
			}
			for (int i = 0; i < 4; i++)
				x.data[i] = 0;
			for (int i = 127; i >= 0; i--)
			{
				if (temp1[i] == 1)
				{
					x.data[i / 32] = x.data[i / 32] | 1 << 31 - i % 32;
				}
			}
			fstream outfile;
			outfile.open("OUTPUT.txt", ios::app);
			for (int i = 0; i < 128; i++)
			{
				outfile << temp1[i];
			}
			outfile << endl;
			outfile.close();
		}

	}
	infile.close();
}
// hàm chuyển số thực thập phân thành nhị phân
bool *DecToBin(Qfloat x)
{
	bool *s = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		s[i] = x.data[i / 32] & 1 << 31 - i % 32;
	}
	return s;
}
void LuuTongVao(vector<char> a, int tong)
{
	while (tong != 0)
	{
		a.push_back(tong % 10);
		tong /= 10;
	}
}
vector<char> Divide(vector<char> a, int b)//b=2
{
	int tong = 0;
	vector<char> kq;
	for (int i = a.size() - 1; i >= 0 | tong != 0; i--)
	{
		if (i < 0)
			tong = tong * 10;
		else
			tong = tong * 10 + a[i];
		if (tong == 0)
			kq.push_back(0);
		else if (tong < b)
		{
			//if (i == a.size() - 1)
			kq.push_back(0);
			continue;
		}
		else
		{
			kq.push_back(tong / b);
			tong = tong % b;
		}
	}
	reverse(kq.begin(), kq.end());
	return kq;
}

vector<char> Cong(vector<char> a, vector<char> b)
{

	vector<char> tong;
	int temp = 0, nho = 0, i = 0;
	for (i; i < b.size() && i < a.size(); i++)
	{
		temp = a[i] + b[i] + nho;
		tong.push_back(temp % 10);
		nho = temp / 10;
	}
	for (i; i < b.size(); i++)
	{
		temp = b[i] + nho;
		tong.push_back(temp % 10);
		nho /= 10;
	}
	for (i; i < a.size(); i++)
	{
		temp = a[i] + nho;
		tong.push_back(temp % 10);
		nho /= 10;
	}
	if (nho > 0)
		tong.push_back(1);
	return tong;
}
int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}
int min(int a, int b)
{
	if (a > b)
		return b;
	return a;
}
vector<char> Congsau(vector<char> a, vector<char> b)//b luon nho hon hoac bang a
{
	vector<char> tong;
	int temp = 0, nho = 0, i = 0;
	int csab = max(a.size(), b.size()) - min(a.size(), b.size());
	if (a.size() <= b.size())
	{
		for (int i = 0; i < csab; i++)
			tong.push_back(b[i]);
		for (i = csab; i < b.size() && i < a.size() + csab; i++)
		{
			temp = a[i - csab] + b[i] + nho;
			tong.push_back(temp % 10);
			nho = temp / 10;
		}
	}
	else
	{
		for (int i = 0; i < csab; i++)
			tong.push_back(a[i]);
		for (i = csab; i < b.size() + csab && i < a.size(); i++)
		{
			temp = a[i] + b[i - csab] + nho;
			tong.push_back(temp % 10);
			nho = temp / 10;
		}
	}
	/*if (nho > 0)//vi tong luon nho hon 1
	tong.push_back(1);*/
	return tong;
}
void Set(vector<char> &a) {
	while (a.size() > 1 && a.back() == 0) a.pop_back();
}
vector<char> Phepnhan(vector<char> a, vector<char> b)
{
	Set(a);
	Set(b);
	vector<char> ans;
	ans.assign(a.size() + b.size(), 0);
	for (int i = 0; i <= a.size() - 1; i++) {
		long carry = 0ll;
		for (int j = 0; j < b.size() || carry > 0; j++) {
			long s = ans[i + j] + carry + (long)a[i] * (j < b.size() ? (long)b[j] : 0ll);
			ans[i + j] = s % 10;
			carry = s / 10;
		}
	}
	Set(ans);
	return ans;
}

int KiemTraSoDacBiet(vector<char> a)
{
	int mu = 0, so = 0;
	//kiem tra mu
	for (int i = 1; i < 16; i++)
	{
		if (a[i] == 1)
		{
			mu = 1;
			break;
		}
	}
	for (int i = 1; i < 16; i++)
	{
		if (a[i] == 0 && mu == 1)
		{
			mu = 2;
		}
	}
	for (int i = 16; i < 128; i++)
	{
		if (a[i] == 1)
		{
			so = 1;
			break;
		}
	}
	if (mu == 0 && so == 0)//so 0
		return 0;
	else if (mu == 0 && so != 0)//denormalized
		return 1;
	else if (mu == 1 && so == 0)//infinity
		return 2;
	else if (mu == 1 && so != 0)//NaN
		return 3;
	return 4;
}
void PrintQfloat(Qfloat x)
{

	vector<char> a, tong = { 0 }, temp = { 1 };
	vector<char> tongsau = { 0 };
	int mu = 0, nhanMu = 1;
	a.assign(128, 0);
	unsigned k = 16383;
	for (int i = 0; i < 128; i++)//chua co ham chuyen Qfloat sang bool*
	{
		bool kiemtra = x.data[i / 32] & (1 << 32 - 1 - i % 32);
		a[i] = kiemtra;
	}
	// kiem tra so dac biet
	int soDB;
	soDB = KiemTraSoDacBiet(a);
	if (soDB == 0)
	{
		fstream f;
		f.open("OUTPUT.txt", ios::out | ios::app);
		f << 0 << endl;
		f.close();
		return;
	}
	else if (soDB == 1)
	{
		fstream f;
		f.open("OUTPUT.txt", ios::out | ios::app);
		f << "denormalized" << endl;
		f.close();
		return;
	}
	else if (soDB == 2)
	{
		fstream f;
		f.open("OUTPUT.txt", ios::out | ios::app);
		f << "infinity" << endl;
		f.close();
		return;
	}
	else if (soDB == 3)
	{
		fstream f;
		f.open("OUTPUT.txt", ios::out | ios::app);
		f << "NaN" << endl;
		f.close();
		return;
	}
	//xu ly mu
	for (int i = 15; i > 0; i--)
	{
		if (a[i] == 1)
			mu += nhanMu;
		nhanMu = nhanMu * 2;
	}
	// mu thuc te
	mu -= k;
	vector<char> b = { 2 };
	if (mu > 0)
	{
		// phan nguyen
		for (int i = 15 + mu; i > 15; i--)
		{
			if (a[i] == 1)//nen data cuoi la 1 thi cong vao luon nen dua temp xuong cuoi
			{// luu dung chieu cua so
				tong = Cong(tong, temp);
			}
			temp = Phepnhan(temp, b);
		}
		// cong cho so 1 dau tien
		//temp = Phepnhan(temp, b);
		tong = Cong(tong, temp);
		//phan thuc
		temp = { 5 };//phan thap phan ban dau la 5
		for (int i = 15 + mu + 1; i < 128; i++)
		{
			if (a[i] == 1)//nen data cuoi la 1 thi cong vao luon nen dua temp xuong cuoi
			{
				tongsau = Congsau(tongsau, temp);
			}
			temp = Divide(temp, 2);
		}
	}
	else// khi mu am
	{
		mu = -mu;
		temp = { 5 };
		for (int i = 0; i < mu - 1; i++)// nhung gia tri 0 nen khong cong
		{
			temp = Divide(temp, 2);
		}
		if (mu == 0)
		{
			tong = { 1 };
		}
		else // vi gia tri tiep thu mu la 1;	
		{
			tongsau = Congsau(tongsau, temp);
			temp = Divide(temp, 2);//chia tiep
		}
		// bat dua cac phan tu trong mang
		for (int i = 16; i < 128; i++)
		{
			if (a[i] == 1)
				tongsau = Congsau(tongsau, temp);
			temp = Divide(temp, 2);//chia tiep
		}
	}
	string s = "";
	if (a[0] == 1)
	{
		s += '-';
	}
	for (int i = tong.size() - 1; i >= 0; i--)
	{
		s += tong[i] + '0';
	}
	s += '.';
	for (int i = tongsau.size() - 1; i >= 0; i--)
	{
		s += tongsau[i] + '0';
	}
	fstream f;
	f.open("OUTPUT.txt", ios::out | ios::app);
	f << s << endl;
	f.close();
}

int main(int a, char *av[])
{

	unsigned int select = atoi(av[3]);
	if (a != 4)
	{
		cout << "THAM SO KHONG HOP LE";
		return 0;
	}
	if (select == 1)
	{
		ifstream in;
		remove("OUTPUT.txt");
		in.open("INPUT.txt", ios::in);
		while (!in.eof())
		{
			string oneLineInput;
			getline(in, oneLineInput, '\n');
			char type;
			string getOperator;
			string base1 = "";
			string base2 = "";
			string operand1 = "";
			string operand2 = "";
			getInput(oneLineInput, type, getOperator, base1, base2, operand1, operand2);
			QInt operand1_QInt = { 0 };
			QInt operand2_QInt = { 0 };
			QInt result = { 0 };

			// toan tu 2 ngoi
			if (type == '1')
			{
				if (base1 == "10")
				{
					ScanQInt10(operand1_QInt, operand1);
					if (getOperator == ">>")
					{
						unsigned k = stoi(operand2);
						result = operand1_QInt >> k;
					}
					else if (getOperator == "<<")
					{
						unsigned k = stoi(operand2);
						result = operand1_QInt << k;
					}
					else if (getOperator == "+")
					{
						ScanQInt10(operand2_QInt, operand2);
						result = operand1_QInt + operand2_QInt;
					}
					else if (getOperator == "-")
					{
						ScanQInt10(operand2_QInt, operand2);
						result = operand1_QInt - operand2_QInt;
					}
					else if (getOperator == "*")
					{
						ScanQInt10(operand2_QInt, operand2);
						result = operand1_QInt * operand2_QInt;
					}
					else if (getOperator == "/")
					{
						ScanQInt10(operand2_QInt, operand2);
						result = operand1_QInt / operand2_QInt;
					}
					else if (getOperator == "|")
					{
						ScanQInt10(operand2_QInt, operand2);
						result = operand1_QInt | operand2_QInt;
					}
					else if (getOperator == "&")
					{
						ScanQInt10(operand2_QInt, operand2);
						result = operand1_QInt & operand2_QInt;
					}
					else if (getOperator == "^")
					{
						ScanQInt10(operand2_QInt, operand2);
						result = operand1_QInt ^ operand2_QInt;
					}
					else if (getOperator == ">=")
					{
						ScanQInt10(operand2_QInt, operand2);
						bool boolResult = operand1_QInt >= operand2_QInt;
						PrintBool(boolResult);
						continue;

					}
					else if (getOperator == "<=")
					{
						ScanQInt10(operand2_QInt, operand2);
						bool boolResult = operand1_QInt <= operand2_QInt;
						PrintBool(boolResult);
						continue;

					}
					else if (getOperator == ">")
					{
						ScanQInt10(operand2_QInt, operand2);
						bool boolResult = operand1_QInt > operand2_QInt;
						PrintBool(boolResult);
						continue;

					}
					else if (getOperator == "<")
					{
						ScanQInt10(operand2_QInt, operand2);
						bool boolResult = operand1_QInt < operand2_QInt;
						PrintBool(boolResult);
						continue;
					}

					else if (getOperator == "rol")
					{
						unsigned k = stoi(operand2);
						result = rol(operand1_QInt, k);

					}
					else if (getOperator == "ror")
					{
						unsigned k = stoi(operand2);
						result = ror(operand1_QInt, k);
					}
					PrintQInt10(result);
				}
				else if (base1 == "2")
				{
					ScanQInt2(operand1_QInt, operand1);
					if (getOperator == ">>")
					{
						unsigned k = stoi(operand2);
						result = operand1_QInt >> k;
					}
					else if (getOperator == "<<")
					{
						unsigned k = stoi(operand2);
						result = operand1_QInt << k;
					}
					else if (getOperator == "+")
					{
						ScanQInt2(operand2_QInt, operand2);
						result = operand1_QInt + operand2_QInt;
					}
					else if (getOperator == "-")
					{
						ScanQInt2(operand2_QInt, operand2);
						result = operand1_QInt - operand2_QInt;
					}
					else if (getOperator == "*")
					{
						ScanQInt2(operand2_QInt, operand2);
						result = operand1_QInt * operand2_QInt;
					}
					else if (getOperator == "/")
					{
						ScanQInt2(operand2_QInt, operand2);
						result = operand1_QInt / operand2_QInt;
					}
					PrintQInt2(result);
				}
				//base1=="16"
				else
				{
					ScanQInt16(operand1_QInt, operand1);
					if (getOperator == ">>")
					{
						unsigned k = stoi(operand2);
						result = operand1_QInt >> k;
					}
					else if (getOperator == "<<")
					{
						unsigned k = stoi(operand2);
						result = operand1_QInt << k;
					}
					else if (getOperator == "+")
					{
						ScanQInt16(operand2_QInt, operand2);
						result = operand1_QInt + operand2_QInt;
					}
					else if (getOperator == "-")
					{
						ScanQInt16(operand2_QInt, operand2);
						result = operand1_QInt - operand2_QInt;
					}
					else if (getOperator == "*")
					{
						ScanQInt10(operand2_QInt, operand2);
						result = operand1_QInt * operand2_QInt;
					}
					else if (getOperator == "/")
					{
						ScanQInt16(operand2_QInt, operand2);
						result = operand1_QInt / operand2_QInt;
					}
					PrintQInt16(result);
				}
			}
			else if (type == '2')
			{
				result = ~operand1_QInt;
				if (base1 == "10")
				{
					ScanQInt10(operand1_QInt, operand1);
					result = ~operand1_QInt;
					PrintQInt10(result);
				}
				else if (base1 == "2")
				{
					ScanQInt2(operand1_QInt, operand1);
					result = ~operand1_QInt;
					PrintQInt2(result);
				}
				else
				{
					ScanQInt16(operand1_QInt, operand1);
					result = ~operand1_QInt;
					PrintQInt16(result);
				}
			}
			// covert ( type='3')
			else
			{
				if (base1 == "2")
				{
					ScanQInt2(result, operand1);
					if (base2 == "10")
					{
						PrintQInt10(result);
					}
					else
					{
						PrintQInt16(result);
					}
				}
				else if (base1 == "10")
				{
					ScanQInt10(result, operand1);
					if (base2 == "2")
					{
						PrintQInt2(result);
					}
					else
					{
						PrintQInt16(result);
					}
				}
				else
				{
					ScanQInt16(result, operand1);
					if (base2 == "2")
					{
						PrintQInt2(result);
					}
					else
					{
						PrintQInt10(result);
					}
				}
			}
			if (in.eof())
			{
				break;
			}
		}
		in.close();
	}
	else if (select == 2)
	{
		Qfloat x;
		ScanQfloat(x);
	}
	else
	{
		cout << "THAM SO KHONG HOP LE";
		return 0;
	}

}