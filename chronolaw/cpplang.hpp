// copyright by chrono

#ifndef _CPP_LANG_HPP
#define _CPP_LANG_HPP

#include <cassert>

#include <iostream>

#include <string>
#include <string_view>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <regex>

#include <atomic>
#include <future>
#include <thread>


// must be C++17 or later
#if __cplusplus < 201703
#   error "C++ is too old"
#endif  

#if __cplusplus >= 201402
#   define CPP_DEPRECATED [[deprecated]]
#else
#   define CPP_DEPRECATED [[gnu::deprecated]]
#endif

#if __cpp_static_assert >= 201411
#   define STATIC_ASSERT(x) static_assert(x)
#else
#   define STATIC_ASSERT(x) static_assert(x, #x)
#endif

#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE(x) }
#define USING_NAMESPACE(x) using namespace x

#endif  //_CPP_LANG_HPP

