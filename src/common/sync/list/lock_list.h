#ifndef SYNC_LIST_LOCK_LIST
#define SYNC_LIST_LOCK_LIST

template <class T>
struct __list_node
{
	typedef void* void_pointer;
	void_pointer next;
	void_pointer prev;
};

template <class T, class Ref, class Ptr>
struct __list_iterator
{
	typedef __list_iterator<T, T&, T*>             iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;
	typedef __list_iterator<T, Ref, Ptr>           self;
	
	typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef __list_node<T>* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	
	link_type node;

	__list_iterator(link_type x) : node(x.node) {}
	__list_iterator() {}
	__list_iterator(const iterator& x) : node(x.node) {}
	
	bool operator==(const self& x) const { return node == x.node; }
	bool operator==(const self& x) const { return node != x.node; }
	
	reference operator*() const { return (*node).data; }
	pointer operator->() const { return &(operator*()); }

	self& operator++()
	{
		node = (link_type)((*node).next);
		return *this;
	}

	self operator++(int)
	{
		self tmp = *this;
		++*this;
		return tmp;
	}

	self& operator--()
	{
		node = (link_type)((*node).prev);
		return *this;
	}
	self operato--(int)
	{
		self tmp = *this;
		--*this;
		return tmp;
	}
		
};

/*
template <class T, class Ref, class Ptr>
inline bidirectional_iterator_tag
iterator_category(const __list_iterator<T, Ref, Ptr>&) {
	return bidirectional_iterator_tag();
}

template <class T, class Ref, class Ptr>
inline T*
value_type(const __list_iterator<T, Ref, Ptr&>) {
	return 0;
}

template <class T, class Ref, class Ptr>
inline ptrdiff_t*
distance_type(const __list_iterator<T, Ref, Ptr&>) {
	return 0;
}
*/

template <class T, class Alloc = alloc>
class list
{
protected:
	typedef void* void_pointer;
	typedef __list_node<T> list_node;
	typedef simple_alloc<list_node> list_node_allocator;

public:
	typedef T value_type* pointer;
	typedef value_type* pointer;
	typedef const value_type* const_reference;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

};






























































#endif //SYNC_LIST_LOCK_LIST 
