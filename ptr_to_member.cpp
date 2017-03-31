
#include <iostream>
#include <conio.h>

using namespace std;

class Base
{
public:
    int i;

    void f() { cout << __FUNCTION__ << endl; }
    virtual void g() { cout << __FUNCTION__ << endl; }
};

class Derived : public Base
{
public:
    int i_in_derived;

    virtual void g() { cout << __FUNCTION__ << endl; }
    void h() { cout << __FUNCTION__ << endl; }
};

static void test()
{
    int Base::*pi = &Base::i;   // can point to any integer in Base
    void (Base::*pf)() = &Base::f;  // can point to any function in Base with type void (*)()

    Base base;
    Base* base_p = &base;

    // Pointer-to-members are not bound to an instance that's why you need to provide
    // an instance every time you want to dereference the pointer-to-member.
    base.*pi = 42;  // pointer-to-member variable is essentially an offset
    base_p->*pi = 42;

    // pointer-to-member function is a function pointer
    (base.*pf)();       // will print Base::f
    (base_p->*pf)();    // will print Base::f

    pf = &Base::g;      // that works with late binding as well
    // pf now points to a compiler generated helper function which calls through vtable[0]

    Derived derived;
    base_p = &derived;
    (base_p->*pf)();    // will print Derived::g
    
    int Base::*base_int = 0;  //  can be null
    //int* i = static_cast<int*>(base_int);   // will not compile of course
}

static void test_contravariance()
{
    int Derived::*pi;
    void (Derived::*pf)();

    pi = &Derived::i_in_derived;    //  nothing interesting
    pf = &Derived::g;

    pi = &Base::i;  //  implicit downcast
    pf = &Base::g;

    Derived derived;
    (derived.*pf)();    // will print Derived::g

    pf = &Derived::h;
    void (Base::*p_base_f)() = static_cast<void (Base::*)()>(pf);   //  explicit upcast
    Base base;
    (base.*p_base_f)(); // will call h() on base!
    // Undefined behaviour but won't cause trouble here because h() does not touch any members.

    //p_base_f = dynamic_cast<void (Base::*)()>(pf); // will not compile
}

int main()
{
    cout << endl << "test()" << endl;
    test();
    cout << endl << "test_contravariance()" << endl;
    test_contravariance();

    _getch();
    return 0;
}

// test()
// Base::f
// Base::f
// Derived::g
// 
// test_contravariance()
// Derived::g
// Derived::h
