//Author Rafael Del Lama
 
//-----------------------------------------	TMatriz.h -----------------------------------------//

#pragma once
#include <iostream>
#include <vector>

template <typename T>
class matriz
{
	private:
		std::vector<T> values;
		std::size_t nrow_, ncol_;
		
	public:
		matriz(std::size_t nrow_, std::size_t ncol_, const T& default_value);
		std::size_t ncol();
		std::size_t nrow();
		T getElement(std::size_t i, std::size_t j);
		matriz<T> getLine(std::size_t n);
		matriz<T> getCol(std::size_t n);
		void print();
		
		//Operadores
		T& operator() (std::size_t, std::size_t);	
		T operator() (std::size_t, std::size_t) const;
};// class matrix

//-----------------------------------------	TMatriz.cpp -----------------------------------------//

//Construtor
template <typename T>
matriz<T>::matriz(std::size_t nrow, std::size_t ncol, const T& default_value)
    : values(nrow * ncol, default_value), nrow_(nrow), ncol_(ncol)
  {}

//-----------------	ncol -----------------//
template <typename T>
std::size_t matriz<T>::ncol(){
	return ncol_;	
}

//-----------------	nrow -----------------//
template <typename T>
std::size_t matriz<T>::nrow(){
	return nrow_;	
}

//-----------------	getElement -----------------//
template <typename T>
T matriz<T>::getElement(std::size_t i, std::size_t j){
	if(i < nrow_ && j < ncol_)
		return values[i * ncol_ + j];
	
	std::cout << "Valor invalido!" << std::endl;
	abort();
}

//-----------------	getLine -----------------//
template <typename T>
matriz<T> matriz<T>::getLine(std::size_t n){
	if(n >= nrow_) {
		std::cout << "Valor invalido!" << std::endl;
		abort();
	}
	
	matriz<T> line(1, ncol_, 0);
	std::size_t start = n * ncol_;
	std::size_t stop = (n + 1) * ncol_;
	for(std::size_t i = start; i < stop; i++)
		line(0, i - start) = values[i];
	return line;
}

//-----------------	getCol -----------------//
template <typename T>
matriz<T> matriz<T>::getCol(std::size_t n){
	if(n >= ncol_) {
		std::cout << "Valor invalido!" << std::endl;
		abort();
	}
	matriz<T> col(nrow_, 1, 0);
	std::size_t start = n;
	std::size_t stop = nrow_ * ncol_;
	for(std::size_t i = start; i < stop; i = i + ncol_)
		col(i/ncol_, 0) = values[i];
	return col;
}

//-----------------	print -----------------//
template <typename T>
void matriz<T>::print(){
	std::size_t stop = nrow_ * ncol_;
	for(std::size_t i = 0; i < stop; i++){
		if(i % ncol_ == 0)
			std::cout << std::endl;
		std::cout << "[" << values[i] << "] ";
	}
	std::cout << std::endl;
}

//operadores ()
template <typename T>
T& matriz<T>::operator()(std::size_t i, std::size_t j) { 
	return values[i * ncol_ + j]; 	
}
  
template <typename T>
T matriz<T>::operator()(std::size_t i, std::size_t j) const { 
	return values[i * ncol_ + j]; 
}

//Pag 242
