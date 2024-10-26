#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

#define OD_T(x) ( (const unsigned short*)__OD_T(x))
#define __OD_T(x) L ## x

