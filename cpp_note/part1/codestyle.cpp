#include <iostream>
#include <string>

using std::string;

#define MAX_PATH_LEN 256

int g_sys_flag;

namespace linux_sys {
    void get_rlimit_core();
}

class FilePath final
{
public:
    void set_path(const string& str);
private:
    string m_path;
    int m_level;
};

template<typename T>
int get_value(const T& v);

int main()
{
    using namespace std;

    cout << "show your code style." << endl;
}
