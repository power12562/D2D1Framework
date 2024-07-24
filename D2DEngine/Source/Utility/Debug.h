#pragma once
#include <iostream>

#ifdef _DEBUG
#define DEBUG_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define DEBUG_WPRINT(fmt, ...) wprintf(fmt, ##__VA_ARGS__)
#else
/** DEBUG ���忡���� �۵��Ǵ� ��ũ�� �Դϴ�.*/
#define DEBUG_PRINT(fmt, ...)
#define DEBUG_WPRINT(fmt, ...)
#endif

