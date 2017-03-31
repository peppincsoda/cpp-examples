#ifndef _STATIC_LIST_H_
#define _STATIC_LIST_H_

// The _Name parameter is just an extension to the type name
// so that multiple static lists can coexists for different factories.

template< class _Name >
class StaticList
{
public:
    static StaticList*  first()  { return first_; }

    StaticList*  next()  { return next_; }

protected:
    StaticList()
    {
        next_ = first_;
        first_ = this;
    }

    ~StaticList() {}

private:
    StaticList* next_;

    static StaticList* first_;
};

template< class _Name >
StaticList<_Name>* StaticList<_Name>::first_ = nullptr;

#endif // _STATIC_LIST_H_
