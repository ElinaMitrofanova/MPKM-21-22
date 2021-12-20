#pragma once

#include "RandomBBS.h"

Integer modulo(Integer base, Integer exponent, Integer mod)
{
	Integer x = 1;
	Integer y = base;
	while (exponent > 0)
	{
		if (exponent % 2 == 1)
			x = (x * y) % mod;
		y = (y * y) % mod;
		exponent = exponent / 2;
	}
	return x % mod;
}

Integer n = Integer("D5BBB96D30086EC484EBA3D7F9CAEB07") * Integer("425D2B9BFDB25B9CF6C416CC6E37B59C1F");  // ��������� ������� n ��� BBS
Integer r = Integer("675215CC3E227D321097E1DB049F1");  // ��������� ������� r ��� BBS

unsigned char rand_bbs()  // ��������� ���� �� ��������� BBS
{
	r = modulo(r, 2, n);  // ��������� � ������� �� ������ n
	return r.GetByte(0);  // ��������� ������� 8 ���
}
