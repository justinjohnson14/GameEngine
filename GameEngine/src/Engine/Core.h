#pragma once

#include <iostream>

#ifdef _DEBUG
#define ENGINE_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { ENGINE_LOG_ERROR("Assertion Failed"); __debugbreak(); } }
#define ENGINE_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { ENGINE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#define HZ_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
#define HZ_GET_ASSERT_MACRO(...) HZ_EXPAND_VARGS(HZ_ASSERT_RESOLVE(__VA_ARGS__, HZ_ASSERT_MESSAGE, HZ_ASSERT_NO_MESSAGE))

#define HZ_ASSERT(...) HZ_EXPAND_VARGS( HZ_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#define HZ_CORE_ASSERT(...) HZ_EXPAND_VARGS( HZ_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
#define HZ_ASSERT(...)
#define HZ_CORE_ASSERT(...)

#define ENGINE_ASSERT_NO_MESSAGE(...)
#define ENGINE_ASSERT_MESSAGE(...)
#endif
