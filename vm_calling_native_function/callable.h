#ifndef _CALLABLE_H_
#define _CALLABLE_H_

#include <memory>

#include "process_tuple.h"
#include "tuple_indices.h"

// The runtime stack of our VM. This class may contain pop_value
// overloads for all supported function parameter types.

class RuntimeStack
{
public:
    void pop_value(int& value)
    {
        value = 42;
    }

    void pop_value(const char*& value)
    {
        value = "wow!";
    }
};

class Callable
{
public:
    virtual ~Callable() {}
    virtual void Call(RuntimeStack& stack) = 0;
};

template<class _R, class... _Args>
class CallableFunction : public Callable
{
public:
    explicit CallableFunction(_R (*f)(_Args...));
    virtual void Call(RuntimeStack& stack);
private:
    _R (*m_f)(_Args...);

    template<size_t... _Indices>
    void Call(std::tuple<_Args...>& args, tuple_indices<_Indices...>);

    class PopFromStack
    {
    public:
        explicit PopFromStack(RuntimeStack& stack): m_stack(stack) {}

        template<class T>
        void operator()(size_t index, T& value)
        {
            m_stack.pop_value(value);
        }

    private:
        RuntimeStack& m_stack;
    };
};

template<class _R, class... _Args>
CallableFunction<_R, _Args...>::CallableFunction(_R (*f)(_Args...)): m_f(f) {}

template<class _R, class... _Args>
void CallableFunction<_R, _Args...>::Call(RuntimeStack& stack)
{
    std::tuple<_Args...> args;

    PopFromStack popFromStack(stack);   // create the PopFromStack operation
    process_tuple(args, popFromStack);  // pop each function parameter from the stack

    Call(args, typename make_tuple_indices<sizeof...(_Args)>::type());
}

template<class _R, class... _Args>
template<size_t... _Indices>
void CallableFunction<_R, _Args...>::Call(std::tuple<_Args...>& args, tuple_indices<_Indices...>)
{
    (*m_f)(std::get<_Indices>(args)...);  // This is the actual call of the native function
}

// Helper to create the Callable function object from the given function.

template<class _R, class... _Args>
std::unique_ptr<Callable> NewCallableFunction(_R (*f)(_Args...))
{
    return std::unique_ptr<Callable>(new CallableFunction<_R, _Args...>(f));
}


#endif // _CALLABLE_H_
