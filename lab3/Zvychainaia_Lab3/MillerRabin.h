#pragma once

#include "RandomBBS.h"
#include <string>

std::string to_string(byte* key, size_t lenght);  // �������������� ������� ���� � hex ������
bool miller_rabin(Integer p, int iteration = 15);
