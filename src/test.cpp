#include <iostream>
#include <iterator>

#include "../include/vector.h"
int main() {
  /*sc::vector<int> meu;
  meu.push_back( 78 );
  std::cout << meu[0] << std::endl;
  meu = { 1,2,3,4,5};
  std::cout << meu[0] << std::endl;
  meu.push_front( -4 );
  auto ptr = meu.begin();
  while( ptr != meu.end() )
  { 
  	std::cout << "AQUI >> " << *ptr << std::endl;
  	ptr++;
  }
  ptr = meu.begin();
  meu.pop_front();
  while( ptr != meu.end() )
  { 
  	std::cout << "AQUI 2 >> " << *ptr << std::endl;
  	ptr++;
  }
  ptr = meu.begin()+3;
  meu.insert( ptr, 32 );
  meu.shrink_to_fit();
  	std::cout << "AQUI 3 >> " << meu << std::endl;
  //meu.push_back(12);
  	int A[] = {6,7,8,9,10,11,12,13,14};
  	meu.insert( meu.begin()+2, &A[0], &A[8] );
  	std::cout << "assign test>> " << meu << std::endl;
  	std::cout<<meu.back() <<std::endl;

  	sc::vector<int> jooj{1,2,3,4,5};

     /*sc::vector<int> vec { 1, 2, 3, 4, 5 };

    // removing a segment from the beginning.
    auto past_last = vec.erase( vec.begin(), std::next(vec.begin(),3) );
    std::cout << vec << std::endl;*/


    sc::vector<int> vec1 { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
    sc::vector<int> source { 6, 7, 8, 9, 10 };


    vec1 = vec2;
    vec1.insert( std::next( vec1.begin(), 2 ), source.begin(), source.end() );
    auto aau = source.end();
    aau--; 
    std::cout << "end :    " << *aau << std::endl;
    std::cout << vec1 << std::endl;
   	return 0;


}