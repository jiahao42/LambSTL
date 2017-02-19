#ifndef RB_TREE_H_
#define RB_TREE_H_

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

struct __rb_tree_node_base {
	typedef __rb_tree_color_type color_type;
	typedef __rb_tree_node_base* base_ptr;
	
	color_type color;
	base_ptr parent;
	base_ptr left;
	base_ptr right;
	
	static base_ptr minimum(base_ptr x) {
		while (x -> left != 0) x = x -> left;
		return x;
	}
	static base_ptr maximum(base_ptr x) {
		while (x -> right != 0)	x = x -> right;
		return x;
	}
};

template <class Value>
struct __rb_tree_node : public __rb_tree_node_base {
	typedef __rb_tree_node<Value>* link_type;
	Value value_field;
};


struct __rb_tree_base_iterator {
	typedef __rb_tree_node_base::base_ptr base_ptr;
	typedef bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	
	base_ptr node;
	
	void increment() {
		if (node -> right != 0) {
			node = node -> right;
			while (node -> left != 0)
				node = node -> left;
		}else {
			base_ptr y = node -> parent;
			while (node == y -> right) {
				node = y;
				y = y -> parent;
			}
			if (node -> right != y)
				node = y;
		}
	}
	
	void decrement() {
		if (node -> color == __rb_tree_red && node -> parent -> parent == node)
			node = node -> right;
		else if (node -> left != 0) {
			base_ptr y = node -> left;
			while (y -> right != 0)
				y = y -> right;
			node = y;
		}else {
			base_ptr y = node -> parent;
			while (node == y -> left) {
				node = y;
				y = y -> parent;
			}
			node = y;
		}
	}
};

template <class Value, class Ref, class Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator {
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef __rb_tree_iterator<Value, Value&, Value*> iterator;
	typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
	typedef __rb_tree_iterator<Value, Ref, Ptr> self;
	typedef __rb_tree_node<Value>* link_type;
	
	__rb_tree_iterator() {}
	__rb_tree_iterator(link_type x) { node = x; }
	__rb_tree_iterator(const iterator& it) { node = it.node; }
	
	reference operator*() const { return link_type(node) -> value_field; }
	#ifndef __SGI_STL_NO_ARROW_OPERATOR
		pointer operator-> () const { return &(operator*()); }
	#endif
	
	self& operator++() { increment(); return *this; }
	self operator++(int) {
		self tmp = *this;
		increment();
		return tmp;
	}
	self& operator--() { decrement(); return *this; }
	self operator(int) {
		self tmp = *this;
		decrement();
		return tmp;
	}
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc = alloc>
class rb_tree {
protected:
	typedef void* void_pointer;
	typedef __rb_tree_node_base* base_ptr;
	typedef __rb_tree_node<Value> rb_tree_node;
	typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
	typedef __rb_tree_color_type color_type;
	
public:
	typedef Key key_value;
	typedef Value value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef rb_tree_node* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

protected:
	link_type get_node() { return rb_tree_node_allocator::allocate(); }
	void put_node(link_type p) { rb_tree_node_allocator::deallocate(p); }
	
	link_type create_node(const value_type& x) {
		link_type tmp = get_node();
		__STL_TRY {
			construct(&tmp -> value_field, x);
		}
		__STL_UNWIND(put_node(tmp));
		return tmp;
	}
	
	link_type clone_node(link_type x) {
		link_type tmp = create_node(x -> value_field);
		tmp -> color = x -> color;
		tmp -> left = 0;
		tmp -> right = 0;
		return tmp;
	}
	
	void destroy_node(link_type p) {
		destroy(&p -> value_field);
		put_node(p);
	}
protected:
	size_type node_count;
	link_type header;
	Compare key_compare;
	
	link_type& root() const { return (link_type&)header -> parent; }
	link_type& leftmost() const { return (link_type&)header -> left; }
	link_type& rightmost() const { return (link_type&)header -> right; }
	
	static link_type& left(link_type x) { return (link_type&)x -> left; }
	static link_type& right(link_type x) { return (link_type&)x -> right; }
	static link_type& parent(link_type x) { return (link_type&)x -> parent; }
	static reference value(link_type x) { return x -> value_field; }
	static const Key& key(link_type x) { return KeyOfValue()(value(x)); }
	static color_type& color(link_type x) { return (color_type&)x -> color; }
	
	static link_type& left(base_ptr x) { return (link_type&)x -> left; }
	static link_type& right(base_ptr x) { return (link_type&)x -> right; }
	static link_type& parent(base_ptr x) { return (link_type&)x -> parent; }
	static reference value(link_type x) { return (link_type)x -> value_field; }
	static const Key& key(link_type x) { return KeyOfValue()(value(link_type(x))); }
	static color_type& color(link_type x) { return (color_type&)link_type(x) -> color; }
	
	
	static link_type minimum(link_type x) {
		return (link_type) __rb_tree_node_base::minimum(x);
	}
	static link_type maximum(link_type x) {
		return (link_type) __rb_tree_node_base::maximum(x);
	}

public:
	typedef __rb_tree_iterator<value_type, reference, pointer> iterator;

private:
	inline void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root) {
		//TODO
	}
	iterator __insert(base_ptr x_, base_ptr y_, const value_type& v) {
		link_type x = (link_type) x_;
		link_type y = (link_type) y_;
		link_type z;
		if (y == header || x != 0 || key_compare(KeyOfValue()(v), key(y))) {
			z = create_node(v);
			left(y) = z;
			if (y == header) {
				root() = z;
				rightmost() = z;
			}else if (y == leftmost())
				leftmost() = z;
		}else {
			z = create_node(v);
			right(y) = z;
			if (y == rightmost())
				rightmost() = z;
		}
		parent(z) = y;
		left(z) = 0;
		right(z) = 0;
		
		__rb_tree_rebalance(z, header -> parent);
		++node_count;
		return iterator(z);
	}
	link_type __copy(link_type x, link_type p);
	void __erase(link_type x);
	void init() {
		header = get_node();
		color(header) = __rb_tree_red;
		
		root() = 0;
		leftmost = header;
		rightmost = header;
	}
public:
	rb_tree(const Compare& comp = Compare()) : node_count(0), key_compare(comp) { init(); }
	~rb_tree() {
		clear();
		put_node(header);
	}
	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& operator= (const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x);
public:
	Compare key_comp() const { return key_compare; }
	iterator begin() { return leftmost(); }
	iterator end() { return header; }
	bool empty() const { return node_count == 0};
	size_type size() const { return node_count; }
	size_type max_size() const { return size_type(-1); }
public:
	pair<iterator, bool> insert_unique(const value_type& v) {
		link_type y = header;
		link_type x = root();
		bool comp = true;
		while (x != 0) {
			y = x;
			comp = key_compare(KeyOfValue()(v), key(x));
			x = comp ? left(x) : right(x);
		}
		iterator j = iterator(y);
		if (comp)
			if (j == begin())
				return pair<iterator,bool>(__insert(x,y,v), true);
			else
				--j;
		if (key_compare(key(j.node), KeyOfValue()(v)))
			return pair<iterator, bool>(__insert(x,y,v), true);
		return pair<iterator, bool>(j, false);
	}
	iterator insert_equal(const value_type& x) {
		link_type y = header;
		link_type x = root();
		while (x != 0) {
			y = x;
			x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right (x);
		}
		return __insert(x, y, v);
	}
	//...
};

















#endif