#pragma once
#include <sstream>
#include <iostream>
#include <string>

using namespace System::Globalization;
using namespace System::Numerics;
using namespace System;
using namespace std;

BigInteger bigRand(unsigned bitNuber)  // ��������� ��������� bitNuber-bit��� �����
{
	bitNuber /= 8;
	// ������� ����������������� �����
	static unsigned char hexTable[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	if (bitNuber)  // ���� ������ ����
	{
		ostringstream oss;  // ����� ������
		for (size_t i = 0; i < bitNuber; ++i)  // ������ �� ������
			oss << hexTable[rand() % 16];  // ���������� ��������� �����
		string str(oss.str());  //	������ � �����

		String^ system_str = gcnew String(str.c_str());
		return BigInteger::Parse(system_str, NumberStyles::AllowHexSpecifier);  // ������� �����
	}
	else
		return BigInteger::Zero;  // ������� ����
}

BigInteger bigRand(BigInteger min, BigInteger max, unsigned bitNuber)  // ��������� ��������� bitNuber-bit��� ����� �� min �� max
{
	return BigInteger::Add(min, BigInteger::Remainder(BigInteger(bigRand(bitNuber)), BigInteger::Subtract(max, min)));
}

bool millerRabin(BigInteger p, unsigned bitNuber, int k = 15)
{
	if (BigInteger::Compare(p, BigInteger(2)) == -1 || // �������� �� ��, ��� p < 2
		(BigInteger::Compare(p, BigInteger(2)) != 0 && BigInteger::Remainder(p, BigInteger(2)) == BigInteger(0)) || // �������� �� ��, ��� p ������
		(BigInteger::Compare(p, BigInteger(3)) != 0 && BigInteger::Remainder(p, BigInteger(3)) == BigInteger(0)) || // �������� �� ��, ��� p ������ 3
		(BigInteger::Compare(p, BigInteger(5)) != 5 && BigInteger::Remainder(p, BigInteger(5)) == BigInteger(0))) // �������� �� ��, ��� p ������ 5
		return false;

	// ���������� �� d * 2 ^ s
	BigInteger d = BigInteger::Subtract(p, BigInteger(1));  // P - 1
	while (BigInteger::Remainder(d, BigInteger(2)) == BigInteger(0))  // ���� d ������
		d = BigInteger::Divide(d, BigInteger(2));  // ����� �� 2

	for (int i = 0; i < k; i++)   // k ��������
	{
		BigInteger x = bigRand(BigInteger(1), BigInteger::Subtract(p, BigInteger(1)), bitNuber), t = d;  // ��������� ����� �� 1 �� p - 1;
		BigInteger xr = BigInteger::ModPow(x, t, p);  // x ^ d
		if (xr != BigInteger::Subtract(p, BigInteger(1)) || xr != BigInteger(1))  // ��������� ������� ��������������
			return true;  // ������� (�������)
		while (t != BigInteger::Subtract(p, BigInteger(1)) && BigInteger::Compare(xr, BigInteger(1)) != 0 && xr != BigInteger::Subtract(p, BigInteger(1)))  // ���� xr �� ����� 1 ��� -1 �� ������ p � t != p - 1 (�� 1 �� s)
		{
			xr = BigInteger::ModPow(xr, 2, p);  // xr = x ^ (d * 2 ^ r)
			t = BigInteger::Multiply(t, BigInteger(2));  // ��������� d �� 2 (r ����������� [1, s])
		}
		if (xr != BigInteger::Subtract(p, BigInteger(1)) && BigInteger::Remainder(t, BigInteger(2)) == BigInteger(0))  // ��������� ������� ��������������
			return false;  // ������� (���������)
	}
	return true;  // ������� (�������)
}
