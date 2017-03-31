#ifndef _TUPLE_INDICES_H_
#define _TUPLE_INDICES_H_


template<size_t... _Indices>
struct tuple_indices {};

template<size_t _Ep, class _TupleType, size_t _Sp>
struct make_tuple_indices_imp {};

template<size_t _Ep, size_t... _Indices, size_t _Sp>
struct make_tuple_indices_imp<_Ep, tuple_indices<_Indices...>, _Sp>
{
    typedef typename make_tuple_indices_imp<_Ep, tuple_indices<_Indices..., _Sp>, _Sp + 1>::type type;
};

template<size_t _Ep, size_t... _Indices>
struct make_tuple_indices_imp<_Ep, tuple_indices<_Indices...>, _Ep>
{
    typedef tuple_indices<_Indices...> type;
};

// Returns: tuple_indices< _Sp, _Sp + 1, _Sp + 2, ..., _Ep >

template<size_t _Ep, size_t _Sp = 0>
struct make_tuple_indices
{
    static_assert(_Sp <= _Ep, "");
    typedef typename make_tuple_indices_imp<_Ep, tuple_indices<>, _Sp>::type type;
};


#endif // _TUPLE_INDICES_H_
