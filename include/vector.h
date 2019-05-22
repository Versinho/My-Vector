#ifndef VECTOR_H
#define VECTOR_H

#include "iterator.h"
#include <iterator>
#include <algorithm> //std::min, std::copy
#include <initializer_list> // std::initializer_list
#include <stdexcept>//std::out_of_range

namespace sc {

template< typename T>
class vector{
	private:
        T * data; //!<  Data storage area for the dynamic array.
        size_t m_size; //!< Current list size (or index past-last valid element). 
        size_t m_capacity; //!< List’s storage capacity. 

   	public:
   		 //=== [I] SPECIAL MEMBERS 

   		/**
		 * Constructs the list with count default-inserted instances of T .
		 *  @param count  the size of the list. 
 		*/
   		vector( size_t count=0 ):
   			data{ new T[count*2] },
			   m_size{ 0 },
			   m_capacity{ count*2 } 
		    { /*empty*/ }

		/**
		 * Constructs the list with the contents of the range [first, last) .
		 *  @param first first element of the range to copy the elements from.
		 *  @param last  the position just after the last element of the range. 
 		*/
   		template< typename InputIt >
   		vector( InputIt first, InputIt last ):
   			m_size{ std::distance( first, last ) },
   			m_capacity{ m_size*2 }
   		{
   			data = new T[m_capacity];
   			std::copy( first, last, data);
   		}

		/**
		 *Copy constructor. Constructs the list with the deep copy of the contents of other . 
		 *  @param other  another list to be used as source to initialize the elements of the list with.
 		*/
      	vector( const vector& other ):
      			m_size{ other.m_size },
   			   m_capacity{ other.m_capacity }
   		{
   	 		// [1] Alocar o espaço de dados.
      			data = new T[m_capacity];
     			// [2] Copiar os elementos do source para o atual (this).
      			std::copy( &other.data[0], &other.data[m_size], data );
   		}

		/**
		 * Constructs the list with the contents of the initializer list init .
		 *  @param ilist initializer list to initialize the elements of the list with.
 		*/
   		vector( std::initializer_list<T> ilist ):
   			m_size{ ilist.size() },
   			m_capacity{ 2*m_size }
   		{
   			data = new T[m_capacity];
   			std::copy( ilist.begin(), ilist.end(), data );
   		}

		/**
		 * Destructs the list. The destructors of the elements are called and the used storage is deallocated.
		 *Note, that if the elements are pointers, the pointed-to objects are not destroyed.
 		*/
   		~vector()
   		{
 			delete[] data;
         }

		/**
		 *Copy assignment operator. Replaces the contents with a copy of the contents of other. 
		 *(i.e. the data in other is moved from other into this container).
		 *other is in a valid but unspeciﬁed state afterwards. 
		 *  @param other another list to be used as source to initialize the elements of the list with.
 		*/
   		vector& operator=( const vector& other )
   		{
   			m_size = other.m_size;
   			m_capacity = other.m_capacity;
   			delete[] data;
      		data = new T[m_capacity];
   			std::copy( other.data, other.data+m_size, data );
   			return *this;
   		}

		/**
		 *Replaces the contents with those identiﬁed by initializer list ilist .
		 *  @param ilist initializer list to initialize the elements of the list with.
 		*/
   		vector& operator=( std::initializer_list<T> ilist )
   		{
   			m_size = ilist.size();
   			m_capacity = m_size*2;
   			delete[] data;
   			data = new T[m_capacity];
   			std::copy( ilist.begin(), ilist.end(), data );
   			return *this;
   		} 

   		//=== [II] ITERATORS
		/**
		 *returns an iterator pointing to the ﬁrst item in the list.
 		*/
   		sc::iterator<T> begin( void )
   		{ return sc::iterator<T>( &data[0] ); }

		/**
		 * returns an iterator pointing to the end mark in the list,
		 *i.e. the position just after the last element of the list. 
 		*/
   		sc::iterator<T> end( void )
   		{ return sc::iterator<T>( &data[m_size] ); }

		/**
		 * returns a constant iterator pointing to the ﬁrst item in the list.
 		*/
   		const sc::iterator<T> cbegin( void )const
   		{ return sc::iterator<T>( &data[0] ); }

		/**
		 * returns a constant iterator pointing to the end mark in the list, 
		 i.e. the position just after the last element of the list.
 		*/
   		const sc::iterator<T> cend( void )const
   		{ return sc::iterator<T>( &data[m_size] ); }

   		//=== [III] Capacity 

		/**
		 *return the number of elements in the container.
 		*/
   		size_t size( void )const
   		{ return m_size; }

		/**
		 * return the internal storage capacity of the array. 
 		*/
   		size_t capacity( void )const
   		{ return m_capacity; }

		/**
		 * returns true if the container contains no elements, and false otherwise. 
 		*/
   		bool empty( void )const
   		{ return m_size == 0; }

		//=== [IV] Modifiers 
		/**
		 *remove (either logically or physically) all elements from the container. 
 		*/
		void clear( void )
		{ m_size = 0; }

		/**
		 * adds value to the front of the list.
		 * @param value  the value to append to the list. 
 		*/
		void push_front( const T& value )
		{
			if( m_size == m_capacity )
   				reserve( ( m_capacity == 0 ) ? 1 : (2 * m_capacity) );
   			
   			for( int i = m_size; i > -1 ; i-- )
   			{
   				data[i+1] = data[i];
   			}
			data[0] = value;
			m_size++;
		}

		/**
		 * adds value to the end of the list.
		 * @param value  the value to append to the list.
 		*/
   		void push_back( const T& value )
   		{
   			if( m_size == m_capacity )
   				 reserve( ( m_capacity == 0 ) ? 1 : (2 * m_capacity) );
   			data[m_size++] = value;
   		}

		/**
		 * removes the object at the end of the list. 
 		*/
   		void pop_back( void )
   		{ 
   			if( empty() ) return;
   			m_size--; 
   		}

		/**
		 * removes the object at the front of the list. 
 		*/
   		void pop_front( void )
   		{
   			if( empty() ) return;
   			for( size_t i = 0; i < m_size ; i++ )
   			{
   				data[i] = data[i+1];
   			}
   			m_size--;
   		}

		/**
		 *increase the storage capacity of the array to a value that’s is greater or equal to new_cap .
		  If new_cap is greater than the current capacity() , new storage is allocated, otherwise the method does nothing. 
		  If new_cap is greater than the current capacity, all iterators and references, including the past-the-end iterator/index, are invalidated.
		   Otherwise, no iterators or references are invalidated. This function also preserve the data elements already stored in the list, as well as their original order. 
		 * @param new_cap new capacity for the vector.
 		*/
   		void reserve( size_t new_cap )
   		{
   			// Se a capacidade nova < capacidade atual, não faço nada.
            if ( new_cap <= m_capacity ) return;

            // Passo 1: alocar nova memória com tamanho solicitado.
            T *temp = new T[ new_cap ];

            // Passo 2: copiar os dados da memória antiga para a nova.
            std::copy( &data[0], &data[m_size],  temp );
            //std::copy( begin(), end(), temp );

            // Passo 3: Liberar a memória antiga.
            delete[] data;

            // Passo 4: Redirecionar ponteiro para a nova (maior) memória.
            data = temp;

            // Passo 5: Atualizações internas.
            m_capacity = new_cap;
   		}

		/**
		 * adds value into the list before the position given by the iterator pos . The method returns an iterator to the position of the inserted item.
		 *  @param value the object to insert. 
 		*/
   		sc::iterator<T> insert( sc::iterator<T> pos, const T& value )
   		{
   			if( m_size == m_capacity )
   			{
   				int pos_correct =  pos-begin();
   				reserve( ( m_capacity == 0 ) ? 1 : (2 * m_capacity) );
   				pos = begin()+pos_correct;
   			}

   			auto aux = end();
   			while( aux != pos )
   			{
   				*aux = *(aux-1);
   				aux--;
   			}
   			*pos = value;
   			m_size++;
   			return pos;
   		}

		/**
		 * inserts elements from the range [first; last) before pos . 
 		*/
   		template < typename InItr> 
   		sc::iterator<T> insert( sc::iterator<T> pos, InItr first, InItr last )
   		{
            if( pos-end() > 0 ) 
            {
               return pos;
            }
   			auto range = std::distance(first,last);
   			if( m_size+range >= m_capacity ) 
   			{
   				int pos_correct =  pos-begin();
   				reserve( ( m_capacity == 0 ) ? range : ( (2*m_capacity)+range ));
   				pos = begin()+pos_correct;
   			}

   			m_size += range;
   			auto aux = end();
   			while( aux != pos )
   			{
               aux--;
   				*aux = *(aux-range);
   			}
   			auto aux2 = first;
   			aux = pos;
   			while( aux2 != last )
   			{
   				*aux = *aux2;
   				aux++;
   				aux2++;

   			}
   			return pos;
   		}

		/**
		 *inserts elements from the initializer list ilist before pos .
		  Initializer list supports the user of insert as in myList.insert( pos, {1, 2, 3, 4} ) , 
		  which would insert the elements 1, 2, 3, and 4 in the list before pos , assuming that myList is a list of int . 
		*  @param ilist the list with the objects to insert. 
 		*/
   		sc::iterator<T> insert( sc::iterator<T> pos, std::initializer_list<T> ilist )
   		{
            if( pos-end() > 0 ) 
            {
               return pos;
            }
   			if( (m_size+ilist.size()) >= m_capacity ) 
   			{
   				int pos_correct =  pos-begin();
   				reserve( ( m_capacity == 0 ) ? ilist.size() : ( (2*m_capacity)+ilist.size() ));
   				pos = begin()+pos_correct;
   			}
   			m_size += ilist.size();
   			auto aux = end();
   			while( aux != pos+(ilist.size())-1 )
   			{
   				*aux = *(aux-(ilist.size()));
   				aux--;
   			}
   			auto aux2 = ilist.begin();
   			aux = pos;
   			while( aux2 != ilist.end() )
   			{
   				*aux = *aux2;
   				aux++;
   				aux2++;
   			}
   			return pos;
   		}

		/**
		 * Requests the removal of unused capacity. It is a non-binding request to reduce capacity() to size() . It depends on the implementation if the request is fulﬁlled. 
 		*/
   		void shrink_to_fit( void )
   		{
   			if( m_size == m_capacity ) return;

   			T *temp = new T[m_size];
   			std::copy( &data[0], &data[m_size], temp );
   			delete[] data;
   			data = temp;
   			m_capacity = m_size;
   		}

		/**
		 *Replaces the contents with count copies of value value . 
 		*/
   		void assign( size_t count, const T& value )
   		{
   			if( count >= m_capacity )
   				reserve( ( m_capacity == 0 ) ? count : (2*count) );
   			m_size = count;
   			for( size_t i = 0; i < m_size; i++ )
   				data[i] = value;
   		}

		/**
		 * replaces the contents of the list with copies of the elements in the range [first; last) . 
 		*/
   		template < typename InItr> 
   		void assign( InItr first, InItr last )
   		{
   			auto range = last-first;
   			if( range >= m_capacity )
   				reserve( ( m_capacity == 0 ) ? range : (2*range) );
   			m_size = range;
   			std::copy( first, last, data);
   		}
		/**
		 * replaces the contents of the list with the elements from the initializer list ilist . 
 		*/
   		void assign( std::initializer_list<T> ilist ) 
   		{
   			m_size = ilist.size();
   			if( m_size >= m_capacity )
   				reserve( ( m_capacity == 0 ) ? m_size : (2*m_size) );
   			std::copy( ilist.begin(), ilist.end(), data );
   		}

		/**
		 *removes the object at position pos . The method returns an iterator to the element that follows pos before the call. 
		 This operation invalidates pos , since the item it pointed to was removed from the list. 
 		*/
   		 sc::iterator<T> erase( sc::iterator<T> pos )
   		 {
   		 	auto aux = pos;
   		 	m_size--;
   			while( aux != end() )
   			{
   				*(aux) = *(aux+1);
   				aux++;
   			}
   			return pos;
   		 }

		/**
		 * removes elements in the range [first; last) .
		  The entire list may be erased by calling a.erase(a.begin(), a.end()); 
 		*/
   		 sc::iterator<T> erase( sc::iterator<T> first, sc::iterator<T> last )
   		 {
   		 	auto aux = first;
   		 	m_size -= (last-first);
   			while( aux != last )
   			{
   				*(aux) = *(aux+(last-first));
   				aux++;
   			}
   			return first;
   		 } 

   		 // [V] Element access

		/**
		 * returns the object at the end of the list. 
 		*/
   		const T& back( void ) const
   		{ return data[m_size-1]; }

      /**
       * returns the object at the end of the list. 
      */
         T& back( void ) 
         { return data[m_size-1]; }


		/**
		 *returns the object at the beginning of the list. 
 		*/
   		const T& front( void ) const
   		{ return data[0]; } 

      /**
       *returns the object at the beginning of the list. 
      */
         T& front( void ) 
         { return data[0]; }

		/**
		 *returns the object at the index pos in the array, with no bounds-checking. 
 		*/
   		T& operator[]( size_t pos )const{ return data[pos]; }

		/**
		 *returns the object at the index pos in the array, with bounds-checking. If pos is not within the range of the list, an exception of type std::out_of_range is thrown. 
 		*/
   		T at( size_t pos )const
   		{
   			if ( pos >= m_size )
            	throw std::out_of_range( "[vector::at() const] out of range error" );

          	return data[ pos ];
   		}
		/**
		 **returns the object at the index pos in the array, with bounds-checking. If pos is not within the range of the list, an exception of type std::out_of_range is thrown.
 		*/
   		T& at( size_t pos )
   		{
   			if ( pos >= m_size )
          		throw std::out_of_range( "[vector::at()] out of range error" );

          	return data[ pos ];
   		}

   		//=== [VII] Friend functions. 

		/**
		 * extraction operator overload
 		*/
   		friend std::ostream& operator<<( std::ostream& os, const vector& v )
        {
            os << "[ ";
            std::copy( &v.data[0], &v.data[v.m_size], std::ostream_iterator<T>( os, " " ));
            os << "| ";
            std::copy( &v.data[v.m_size], &v.data[v.m_capacity], std::ostream_iterator<T>( os, " " ));
            os << "]";

            return os;
        }

       	/*friend void swap( vector<T>& A, vector<T>& B )
       	{
       		for( int i = 0; i < std::min( A.m_size, B.m_size ); i++ )
           		std::swap( A.data[i], B.data[i]);
       	}*/
};

      /**
       * Checks if the contents of lhs and rhs are equal, that is, whether lhs.size() == rhs.size() and each element in lhs compares equal with the element in rhs at the same position. 
      */
      template< typename T>
      bool operator==( const sc::vector<T>& lhs, const sc::vector<T>& rhs )
      {
         if( lhs.size() != rhs.size() )
            return false;
         auto l_it = lhs.cbegin();
         auto r_it = rhs.cbegin();
         while( l_it != lhs.cend() )
         {
            if( *l_it != *r_it )
               return false;
            l_it++;
            r_it++;
         }
         return true;
      }

      /**
       * Similar to the previous operator, but the opposite result.
      */
      template< typename T>
      bool operator!=( const sc::vector<T>& lhs, const sc::vector<T>& rhs )
      {
         if( lhs.size() != rhs.size() )
            return true;
         auto l_it = lhs.cbegin();
         auto r_it = rhs.cbegin();
         while( l_it != lhs.cend() )
         {
            if( *l_it != *r_it )
               return true;
            l_it++;
            r_it++;
         }
         return false;
      }
}//namespace

#endif