#include <cassert>

#include <typeinfo>
#include <string>
#include <iostream>
#include <stdexcept>

[[deprecated("deadline:2022-3-9")]]
int old_func()
{
    int value = 0;

    return value;
}

[[gnu::constructor]]
void first_func()
{
    printf("before main()\n");
}

[[gnu::destructor]]
void last_func()
{
    printf("after main()\n");
}

[[using gnu : const, always_inline]] inline
 int get_num()
 {
    return 42;
 }

[[noreturn]]
int case1(bool flag)
{
    throw std::runtime_error("XXX");
}

void case2()
{
    using namespace std;

    [[maybe_unused]]  // [[gun::unused]]
    int nouse;

    cout << "case2" << endl;
}

[[gnu::hot]]
void case3()
{
    using namespace std;

    cout << "case3" << endl;
}

int main()
{
    using namespace std;

    old_func();
    get_num();

    case2();
    case3();

    cout << "attribute demo" << endl;
}
