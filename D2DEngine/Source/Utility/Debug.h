#pragma once
#include <iostream>

#ifdef _DEBUG
#define DEBUG_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define DEBUG_WPRINT(fmt, ...) wprintf(fmt, ##__VA_ARGS__)
#else
/** DEBUG 빌드에서만 작동되는 매크로 입니다.*/
#define DEBUG_PRINT(fmt, ...)
#define DEBUG_WPRINT(fmt, ...)
#endif

