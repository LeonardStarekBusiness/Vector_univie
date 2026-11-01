#include <cstddef>
#include <iostream>
#include <ostream>
#include <stdexcept>

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
		static constexpr size_type min_capacity = 4;
		size_type sz = 0;
		size_type max_size = min_capacity;
		value_type *values;
	public:
		// Konstruktoren
		Vector()
		{
			sz = 0;
			max_size = min_capacity;
			values = new value_type[max_size];
		};
		Vector(const Vector &other)
		{
			sz = other.sz;
			max_size = other.max_size;
			values = new value_type[max_size];
			for (size_type i = 0; i < sz; i++)
				values[i] = other.values[i];
		};
		// idk if needed!!
		Vector &operator=(const Vector &other)
		{
			Vector *vec = new Vector;
			vec->sz = other.sz;
			vec->max_size = other.max_size;
			vec->values = new value_type[max_size];
			for (size_type i = 0; i < sz; i++)
				vec->values[i] = other.values[i];
			return (*vec);
		};
		Vector(size_type n)
		{
			sz = 0;
			max_size = n;
			values = new value_type[n];
		};
		Vector(std::initializer_list<value_type> list)
		{
			sz = list.size();
			max_size = sz * 2;
			values = new value_type[max_size];
			for (size_type i = 0; i < sz; i++)
				values[i] = *(list.begin() + i);
		};
		~Vector()
		{
			delete[] values;
		};
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
				pointer ptr;
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
		size_type size() const
		{
			return sz;
		};
		bool empty() const
		{
			return (sz == 0);
		};
		void clear()
		{
			delete[] values;
			values = new value_type[min_capacity];
			sz = 0;
			max_size = min_capacity;
		};
		void reserve(size_type n)
		{
			if (max_size >= n)
				return ;
			pointer new_values = new value_type[n];
			for (size_type i = 0; i < sz; i++)
				new_values[i] = values[i];
			delete[] values;
			max_size = n;
			values = new_values;
		};
		void shrink_to_fit()
		{
			if (sz <= max_size)
				return ;
			pointer new_values = new value_type[sz];
			for (size_type i = 0; i < sz; i++)
				new_values[i] = values[i];
			delete[] values;
			values = new_values;
		};
		void push_back(value_type x)
		{
			while (sz >= max_size)
				reserve(max_size * 2);
			values[sz] = x;
			++sz;
			return ;
		};
		void pop_back()
		{
			if (sz <= 0)
				throw std::runtime_error("Vector is already empty bro");
			--sz;
			if ((sz << 1) < max_size)
				shrink_to_fit();
		};
		reference operator[](size_type index)
		{
			if (index > sz || index < 0)
				throw std::runtime_error("Out of range bro");
			return values[index];
		};
		const_reference operator[](size_type index) const
		{
			if (index > sz || index < 0)
				throw std::runtime_error("Out of range bro");
			return values[index];
		};
		size_type capacity() const
		{
			return max_size;
		};
		// Output
		friend std::ostream &operator<<(std::ostream& out, const Vector& vec)
		{
			out << "[";
			for (size_type i = 0; i < vec.size(); i++)
				out << vec[i] << ", ";
			out << "]";
			return out;
		};
		iterator begin()
		{
			//
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
		};
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
		};
		friend Vector::difference_type operator-(const Vector::ConstIterator& lop, const Vector::ConstIterator& rop)
		{
			return lop.ptr - rop.ptr;
		}
};



