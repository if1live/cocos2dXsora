﻿// Ŭnicode please
#pragma once

#include "arch.h"
#if SR_WIN
#include <unordered_map>
#elif SR_IPHONE
#include <unordered_map>
#elif SR_ANDROID
//#include <unordered_map>
#include <unordered_map>
#else
#errror "not support??"
#endif