#include "../include/sc.h"
// construtor padrão, cria uma lista de tamanho solicitado, com o dobro de capacidade, ou um vector vazio caso tamanho nao seja especificado.
sc::vector::vector( size_t count=0 ):
	data{ new T[2*count] },
	size{ count },
	capacity{ 2*count } 
{ /*empty*/ }
//destrutor, libera a memória da lista 
sc::vector::~vector()
{
 delete[] data;
}
//construtor cópia
sc::vector::vector( const sc::vector& other ):
	size{ other.size },
	capacity{ other.capacity }
{
	 // [1] Alocar o espaço de dados.
   	data = new T[capacity];
  	// [2] Copiar os elementos do source para o atual (this).
   	std::copy( &source.data[0], &source.data[size], data );
}

template< typename InputIt >
sc::vector::vector( InputIt first, InputIt last ):
	size{ std::distance( first, last ) },
	capacity{ size*2 }
{
	data = new T[capacity];
	std::copy( first, last, data);
}

sc::vector::vector( std::initializer_list<T> ilist )
{

}

sc::vector& operator=( const sc::vector& other )
{
	size = other.size;
	capacity = other.capacity;
	std::copy( other.data, other.data+size, data );
	return *this;
}

sc::vector& operator=( std::initializer_list<T> ilist )
{

	return *this;
}

