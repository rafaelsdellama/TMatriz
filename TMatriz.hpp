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
		matriz<T> transpose();
		T determinant();	
		void print();
		
		//Operadores
		T& operator() (std::size_t, std::size_t);	//adicionar elemento na matriz
		T operator() (std::size_t, std::size_t) const; // ler elemento da matriz
		matriz<T> operator+ (matriz<T>); // adição de matriz
		matriz<T> operator- (matriz<T>); // subtração de matriz
		matriz<T> operator* (matriz<T>); // multiplicação de matriz
		matriz<T> operator* (int); // multiplicar matriz por escalar
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
	exit(1);
}

//-----------------	getLine -----------------//
template <typename T>
matriz<T> matriz<T>::getLine(std::size_t n){
	if(n >= nrow_) {
		std::cout << "Valor invalido!" << std::endl;
		exit(1);
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
		exit(1);
	}
	matriz<T> col(nrow_, 1, 0);
	std::size_t start = n;
	std::size_t stop = nrow_ * ncol_;
	for(std::size_t i = start; i < stop; i = i + ncol_)
		col(i/ncol_, 0) = values[i];
	return col;
}

//-----------------	transpose -----------------//
template <typename T>
matriz<T> matriz<T>::transpose(){
	matriz<T> Mt(ncol_,nrow_ ,0);
		for(std::size_t i = 0; i < ncol_; i++)
			for(std::size_t j = 0; j < nrow_; j++)
				Mt(i,j) = getElement(j,i);
	
	return Mt;	
}

//-----------------	determinant -----------------//
template <typename T>
T matriz<T>::determinant(){
	if(ncol_ != nrow_){
		std::cout << "Erro ao calcular determinante!\nMatrizes não é quadrada!" << std::endl;
		exit(1);
	}

	T det = 0;
	
	std::cout << "Terminar implementação!" << std::endl;

	return det;	
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

//-----------------	operator () -----------------//
template <typename T>
T& matriz<T>::operator()(std::size_t i, std::size_t j) { 
	return values[i * ncol_ + j]; 	
}
  
template <typename T>
T matriz<T>::operator()(std::size_t i, std::size_t j) const { 
	return values[i * ncol_ + j]; 
}

//-----------------	operator + -----------------//
template <typename T>
matriz<T> matriz<T>::operator+(matriz<T> a) {
	if(a.ncol() != ncol_ || a.nrow() != nrow_){
		std::cout << "Erro ao somar!\nMatrizes com dimensões diferentes!" << std::endl;
		exit(1);
	}
	matriz<T> sum(nrow_,ncol_ ,0);
	for(std::size_t i = 0; i < nrow_; i++)
		for(std::size_t j = 0; j < ncol_; j++)
			sum(i,j) = a(i,j) + getElement(i,j);
	return sum;
}	

//-----------------	operator - -----------------//
template <typename T>
matriz<T> matriz<T>::operator-(matriz<T> a) {
	if(a.ncol() != ncol_ || a.nrow() != nrow_){
		std::cout << "Erro ao subtrair!\nMatrizes com dimensões diferentes!" << std::endl;
		exit(1);
	}
	matriz<T> dif(nrow_, ncol_,0);
	for(std::size_t i = 0; i < nrow_; i++)
		for(std::size_t j = 0; j < ncol_; j++)
			dif(i,j) = getElement(i,j) - a(i,j);
	return dif;
}

//-----------------	operator * -----------------//
template <typename T>
matriz<T> matriz<T>::operator* (matriz<T> a){
	if(a.ncol() != nrow_){
		std::cout << "Erro ao multiplicar!\nMatrizes com dimensões diferentes!" << std::endl;
		exit(1);
	}
	matriz<T> prod(nrow_, a.ncol(),0);
	for(std::size_t i = 0; i < nrow_; i++)
		for(std::size_t j = 0; j < a.ncol(); j++)
			for(std::size_t k = 0; k < ncol_; k++)
				prod(i,j) = prod(i,j) + getElement(i,k) * a(k,j) ;
	return prod;
} 
//-----------------	operator * -----------------//
template <typename T>
matriz<T> matriz<T>::operator* (int a){
	matriz<T> prod(nrow_, ncol_,0);
	for(std::size_t i = 0; i < nrow_; i++)
		for(std::size_t j = 0; j < ncol_; j++)
			prod(i,j) = getElement(i,j) * a;
	return prod;	
}
