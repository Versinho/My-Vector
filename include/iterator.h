#ifndef ITERATOR_H
#define ITERATOR_H
#include <iterator>

namespace sc{
	template < typename T >
	class iterator{	
		public:
			typedef T* pointer;
 			typedef T value_type; //!< Value type the iterator points to. 
			typedef T& reference; //!< Alias para uma referência.
	      	typedef std::ptrdiff_t difference_type;
	      	/// Identificar a categoria do iterador para algoritmos do STL.
	  	   	typedef std::bidirectional_iterator_tag iterator_category;
	  	private:
	  		T* ptr;
	  	public:
			/**
			 *default constructor.
 			*/
	  		iterator( T* pt = nullptr ): ptr{ pt }
	  		{ /* empty */ }

			/**
			 * advances iterator to the next location within the vector. 
 			*/
	  		iterator operator++( void )
	  		{
	  			++ptr;
	  			return *this;
	  		}

			/**
			 * advances iterator to the next location within the vector. 
 			*/
	  		iterator operator++( int )
	  		{
	  			iterator temp( ptr );
	  			ptr++;
	  			return temp; 
	  		}

			/**
			 * retreat iterator to the previous location within the vector. 
 			*/
	  		iterator operator--( void )
	  		{
	  			--ptr;
	  			return *this;
	  		}

			/**
			 *retreat iterator to the previous location within the vector. 
 			*/
	  		iterator operator--( int )
	  		{
	  			iterator temp( ptr );
	  			ptr--;
	  			return temp;
	  		}

			/**
			 * as in it1 == it2 : returns true if both iterators refer to the same location within the vector, and false otherwise. 
 			*/
	  		bool operator==( const iterator &it )const
	  		{ return this->ptr == it.ptr; }

			/**
			 * as in it1 != it2 : returns true if both iterators refer to a diﬀerent location within the vector, and false otherwise.
 			*/
	  		bool operator!=( const iterator &it )const
	  		{ return this->ptr != it.ptr; }

			/**
			 * as in it1-it2 : return the diﬀerence between two iterators. 
 			*/
	  		difference_type operator-( const iterator &rhs )
	  		{ return ptr - rhs.ptr; }

			/**
			 * as in *it : return a reference to the object located at the position pointed by the iterator.The reference may be modiﬁable
 			*/
	  		reference operator*(void)
	  		{ return *ptr;}

			/**
			 *as in *it : return a reference to the object located at the position pointed by the iterator.The reference may be modiﬁable
 			*/
	  		const T& operator*( void )const
	  		{ return *ptr; }

			/**
			 * as in it->field : return a pointer to the location in the vector the it points to. 
 			*/
 			T* operator->( void ) const
 			{ return ptr; }

			/**
			 * as in 2+it : return a iterator pointing to the n -th successor in the vector from it . 
 			*/
	  		friend sc::iterator<T> operator+( int n, sc::iterator<T> it )
	  		{ 
	  			it.ptr += n;
	  			return it;
	  		}

			/**
			 *as in it+2 : return a iterator pointing to the n -th successor in the vector from it . 
 			*/
	  		friend sc::iterator<T> operator+( sc::iterator<T> it, int n )
	  		{ return n + it; }

			/**
			 *as in 2-it : return a iterator pointing to the n -th predecessor in the vector from it . 
 			*/
	  		friend sc::iterator<T> operator-( int n, sc::iterator<T> it )
	  		{ 
	  			it.ptr -= n;
	  			return it;
	  		}

			/**
			 * as in it-2 : return a iterator pointing to the n -th predecessor in the vector from it .
 			*/
	  		friend sc::iterator<T> operator-( sc::iterator<T> it, int n )
	  		{ return n - it; }
	};
}// namespace
#endif