class Vector
{
	public:
		class ConstIterator;
		class Iterator;
		using value_type = double;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = Vector::Iterator;
		using const_iterator = Vector::ConstIterator;
	private:
		static constexpr size_t min_capacity = 4;
		size_t sz = 0;
		size_t max_size = min_capacity;
		value_type *values;
	public:
		// Konstruktoren
		Vector();
		Vector(const Vector &other);
		Vector &operator=(const Vector &other);
		Vector(size_type n);
		Vector(std::initializer_list<value_type>);
		~Vector();
		// Interne Klassen 
		class Iterator
		{
			public:
				using value_type = Vector::value_type;
				using reference = Vector::reference;
				using pointer = Vector::pointer;
				using difference_type = Vector::difference_type;
				using iterator_category = std::forward_iterator_tag;
			private:
				// Instanzvariablen
			public:
				// Methoden
		};
		class ConstIterator
		{
			public:
				using value_type = Vector::value_type;
				using reference = Vector::const_reference;
				using pointer = Vector::const_pointer;
				using difference_type = Vector::difference_type;
				using iterator_category = std::forward_iterator_tag;
			private:
				// Instanzvariablen
			public:
				// Methoden
		};
		// Member-Funktionen
		size_type size() const;
		bool empty() const;
		void clear();
		void reserver(size_type n);
		void shrink_to_fit();
		void push_back(value_type x);
		void pop_back();
		reference operator[](size_type index);
		const_reference operator[](size_type index) const;
		size_type capacity() const;
};

iterator insert(const_iterator pos, const_reference val)
{
	auto diff = pos - begin();
	if (diff < 0 || static_cast<size_type>(diff) > sz)
		throw std::runtime_error("Iterator out of bounds");
	size_type current{static_cast<size_type>(diff)};
	if (sz >= max_sz)
		reserve(max_sz * 2 + 1); // Achtung Sonderfall, wenn keine Mindestgroesze definiert ist
	for (auto i{sz}; i-- > current;)
	 	values[i + 1] = values[i];
	values[current] = val;
	++sz;
	return iterator{values + current};
}

iterator erase(const_iterator pos)
{
	auto diff = pos - begin();
	if (diff < 0 || static_cast<size_type>(diff) >= sz)
		throw std::runtime_error("Iterator out of bounds");
	size_type current{static_cast<size_type>(diff)};
	for (auto i{current}; i < sz - 1; ++i)
		values[i] = values[i + 1];
	--sz;
	return iterator{values + current};
}

friend Vector::difference_type operator-(const Vector::ConstIterator& lop, const Vector::ConstIterator& rop)
{
	return lop.ptr - rop.ptr;
}

