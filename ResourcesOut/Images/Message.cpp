#include "stdint.h"

#if defined ( __ICCARM__ )
#pragma location = ".qspi"
#else
__attribute__((section(".qspi")))
#endif
extern const uint8_t Message[334848] = {