#ifndef _PROCESS_TUPLE_H_
#define _PROCESS_TUPLE_H_

#include <tuple>

template<size_t _Ep, class _TupleType, size_t _Sp, class _Func>
struct process_tuple_impl
{
    static void fn(_TupleType& args, _Func func)
    {
        func(_Sp, std::get<_Sp>(args));
        process_tuple_impl<_Ep, _TupleType, _Sp + 1, _Func>::fn(args, func);
    }
};

template<size_t _Ep, class _TupleType, class _Func>
struct process_tuple_impl<_Ep, _TupleType, _Ep, _Func>
{
    static void fn(_TupleType& args, _Func func)
    {
    }
};

// Executes the given function on all elements of a tuple.

template<class _Func, class... _Args>
inline static void process_tuple(std::tuple<_Args...>& args, _Func func)
{
    process_tuple_impl<sizeof...(_Args), std::tuple<_Args...>, 0, _Func>::fn(args, func);
}


#endif // _PROCESS_TUPLE_H_
