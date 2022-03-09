#include <iostream>

#if __has_include(<optional>)
#   include <optional>
#endif

using namespace std;

void case1()
{
#if __linux__
#   define HAS_LINUX    1
#endif

    cout << "linux is " << HAS_LINUX << endl;
}

void case2()
{
#define CUBE(a) (a) * (a) * (a)

    cout << CUBE(10) << endl;
    cout << CUBE(15) << endl;

#undef CUBE

#ifdef AUTH_PWD
#   undef AUTH_PWD
#endif
#define AUTH_PWD "XXX"

    cout << AUTH_PWD << endl;

#define MAX_BUF_LEN 65535
#define VERSION "1.0.18"
}

#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE(x) }

BEGIN_NAMESPACE(my_own)

class MyClass final
{
};

void case3()
{
    cout << "working in own namespace" << endl;
}

END_NAMESPACE(my_own)

#ifdef __cplusplus
    extern "C" {
#endif
    void a_c_function(int a);
#ifdef __cplusplus
    }
#endif

void case4()
{
    cout << __cplusplus << endl;

#if __cplusplus >= 202002
    cout << "c++20 or later" << endl;
#elif __cplusplus >= 201703
    cout << "c++17 or later" << endl;
#else
#   error "c++ is too old"
#endif

#if __GNUC__ <= 5
    cout << "gcc is too old" << endl;
#else
    cout << "gcc is good enough" << endl;
#endif

#if defined(__SSE4_2__) && defined(__x86_64)
    cout << "we can do more optimization" << endl;
#endif

#if __linux__
    cout << "running on linux" << endl;
#else
    cout << "running on others" << endl;
#endif

#if defined(__cpp_modules)
    cout << "moudle enable" << endl;
#else
    cout << "moudle disable" << endl;
#endif

#if defined(__cpp_decltype_auto)
    cout << "decltype(auto) enable" << endl;
#else
    cout << "decltype(auto) disable" << endl;
#endif

#ifndef NDEBUG
    cout << "debug mode" << endl;
#endif

}

int main()
{
    case1();
    case2();

    my_own::case3();

    [[maybe_unused]]
    my_own::MyClass obj;

    case4();

    cout << "pre-process demo" << endl;
}


