template <class Type>
class InputIterator
{
    virtual InputIterator<Type> operator++() = 0;
    virtual InputIterator<Type> operator++(int) = 0;

    virtual const Type &operator*() const = 0;

    virtual bool operator == (const InputIterator<Type>& it) const = 0;
    virtual bool operator != (const InputIterator<Type>& it) const = 0;
};

template <class Type>
class OutputIterator
{
    virtual InputIterator<Type> operator++() = 0;
    virtual InputIterator<Type> operator++(int) = 0;

    virtual Type &operator*() = 0;
};

template <class Type>
class ForwardIterator
{
    virtual ForwardIterator<Type> operator++() = 0;
    virtual ForwardIterator<Type> operator++(int) = 0;

    virtual const Type &operator*() const = 0;
    virtual Type &operator*() = 0;

    virtual bool operator == (const ForwardIterator<Type>& it) const = 0;
    virtual bool operator != (const ForwardIterator<Type>& it) const = 0;
};

template <class Type>
class BidirectionalIterator
{
    virtual BidirectionalIterator<Type> operator++() = 0;
    virtual BidirectionalIterator<Type> operator++(int) = 0;
    virtual BidirectionalIterator<Type> operator--() = 0;
    virtual BidirectionalIterator<Type> operator--(int) = 0;

    virtual const Type &operator*() const = 0;
    virtual Type &operator*() = 0;

    virtual bool operator == (const BidirectionalIterator<Type>& it) const = 0;
    virtual bool operator != (const BidirectionalIterator<Type>& it) const = 0;
};

template <class Type>
class RandomAccessIterator
{
    virtual RandomAccessIterator<Type> operator++() = 0;
    virtual RandomAccessIterator<Type> operator++(int) = 0;
    virtual RandomAccessIterator<Type> operator--() = 0;
    virtual RandomAccessIterator<Type> operator--(int) = 0;

    virtual const Type &operator*() const = 0;
    virtual Type &operator*() = 0;

    virtual bool operator == (const RandomAccessIterator<Type>& it) const = 0;
    virtual bool operator != (const RandomAccessIterator<Type>& it) const = 0;

    virtual void operator +=(int a) = 0;
    virtual void operator -=(int a) = 0;
};

template <class Type>
RandomAccessIterator<Type> operator +(const RandomAccessIterator<Type>& it, int n);
template <class Type>
RandomAccessIterator<Type> operator +(int n, const RandomAccessIterator<Type>& it);
template <class Type>
RandomAccessIterator<Type> operator -(const RandomAccessIterator<Type>& it, int n);
template <class Type>
RandomAccessIterator<Type> operator -(int n, const RandomAccessIterator<Type>& it);

template <class Type>
size_t count(InputIterator<Type> begin, InputIterator<Type> end, Type value)
{
    size_t result = 0;
    while (begin != end)
    {
        if (*begin == value)
        {
            ++result;
        }
        ++begin;
    }
    return result;
}

struct Container {
    int a;
    int b;
    std::string sample;
};

struct Collection {
    int arr[3];
};

template <typename FIRST_TYPE, typename SECOND_TYPE>
struct pair {
    FIRST_TYPE first;
    SECOND_TYPE second;
};

template <typename FIRST_TYPE, typename SECOND_TYPE>
pair<FIRST_TYPE, SECOND_TYPE> make_pair(FIRST_TYPE f, SECOND_TYPE s) {
    pair<FIRST_TYPE, SECOND_TYPE> p = {f, s};
    return p;
}

auto p = make_pair(10, 3.2);