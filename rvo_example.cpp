#include <stdio.h>
#include <conio.h>

class Test
{
public:
    Test() : i_(0) { printf("default ctor\n"); }
    Test(const Test& rhs) : i_(rhs.i_) { printf("copy ctor\n"); }
    Test& operator=(const Test& rhs) { i_ = rhs.i_; return *this; }
    ~Test() { printf("dtor\n"); }

    int i() const { return i_; }

    void set_i(int i) { i_ = i; }

private:
    int i_;
};

static Test GetTest()
{
    Test test;
    test.set_i(1);
    return test;
}

int main()
{
    Test test(GetTest());

    printf("%d\n", test.i());
    _getch();
    return 0;
}

// RESULTS
// =======

// VS2012 - Debug
// default ctor
// copy ctor
// dtor
// 1

// VS2012 - Release
// default ctor
// 1

// MINGW 4.8 - Debug
// default ctor
// 1

// MINGW 4.8 - Release
// default ctor
// 1

// Constructors and destructors should never have side effects or be prepared for porting issues.
