#pragma once

#include <cryptopp/integer.h>

using namespace CryptoPP;

Integer modulo(Integer base, Integer exponent, Integer mod);  // ������� �� ������
unsigned char rand_bbs();  // ��������� ���� �� ��������� BBS
