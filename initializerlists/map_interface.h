
template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
          typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
class map
{
public:
    typedef _Key                       key_type;
    typedef _Tp                        mapped_type;
    typedef std::pair<const _Key, _Tp> value_type;

...

    map(initializer_list<value_type> __l, 
        const _Compare& __comp = _Compare(),
        const allocator_type& __a = allocator_type())
    : _M_t(__comp, _Pair_alloc_type(__a))
    {
        _M_t._M_insert_unique(__l.begin(), __l.end()); 
    }

...
};
