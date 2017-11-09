//Author Rafael Del Lama
 
//-----------------------------------------	TMatriz.h -----------------------------------------//

#pragma once
#include <iostream>
#include <vector>
#include <cmath>

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
		matriz<T> getRow(std::size_t n);
		matriz<T> getCol(std::size_t n);
		matriz<T> subMatriz(std::size_t rMin, std::size_t rMax, std::size_t cMin, std::size_t cMax);
		matriz<T> removeRow(std::size_t n);
		matriz<T> removeCol(std::size_t n);
		matriz<T> concRow(matriz<T> a, matriz<T> b);
		matriz<T> concCol(matriz<T> a, matriz<T> b);
		matriz<T> transpose();
		T determinant();	
		T detRecursive(matriz<T> a);
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

//-----------------	getRow -----------------//
template <typename T>
matriz<T> matriz<T>::getRow(std::size_t n){
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

//-----------------	subMatriz -----------------//
template <typename T>
matriz<T> matriz<T>::subMatriz(std::size_t rMin, std::size_t rMax, std::size_t cMin, std::size_t cMax){
	if(rMin < 0 || rMax >= nrow_ || cMin < 0 || cMax >= ncol_) {
		std::cout << "Valores incorretos de linha ou coluna!" << std::endl;
		exit(1);
	}
	matriz<T> M(rMax - rMin + 1, cMax - cMin + 1, 0);
	
	for(std::size_t i = rMin; i <= rMax; i++)
		for(std::size_t j = cMin; j <= cMax; j++)
			M(i - rMin,j - cMin) = getElement(i,j);
	
	return M;
}

//-----------------	removeRow -----------------//
template <typename T>
matriz<T> matriz<T>::removeRow(std::size_t n){
	if(n < 0 || n >= nrow_) {
		std::cout << "Linha invalida!" << std::endl;
		exit(1);
	}
	matriz<T> M(nrow_ -1, ncol_, 0);
	for(std::size_t i = 0; i < nrow_ - 1; i++)
		for(std::size_t j = 0; j < ncol_; j++){
			if(i < n)
				M(i,j) = getElement(i,j);
			else
				M(i,j) = getElement(i + 1,j);
		}
	return M;
}
//-----------------	removeCol -----------------//
template <typename T>
matriz<T> matriz<T>::removeCol(std::size_t n){
	if(n < 0 || n >= ncol_) {
		std::cout << "Coluna invalida!" << std::endl;
		exit(1);
	}
	matriz<T> M(nrow_, ncol_ -1, 0);
	for(std::size_t i = 0; i < nrow_; i++)
		for(std::size_t j = 0; j < ncol_ -1; j++){
			if(j < n)
				M(i,j) = getElement(i,j);
			else
				M(i,j) = getElement(i,j + 1);
		}
	return M;
	
}
//-----------------	concRow -----------------//
template <typename T>
matriz<T> matriz<T>::concRow(matriz<T> a, matriz<T> b){
	if(a.ncol() != b.ncol()) {
		std::cout << "Matrizes com ncol diferentes!" << std::endl;
		exit(1);
	}
	matriz<T> M(a.nrow() + b.nrow(), a.ncol(), 0);
	for(std::size_t i = 0; i < M.nrow(); i++)
		for(std::size_t j = 0; j < M.ncol() -1; j++){
			if(i < a.nrow())
				M(i,j) = a.getElement(i,j);
			else
				M(i,j) = b.getElement(i - a.nrow(),j);
		}
	return M;
}
//-----------------	concCol -----------------//
template <typename T>
matriz<T> matriz<T>::concCol(matriz<T> a, matriz<T> b){
	if(a.nrow() != b.nrow()) {
		std::cout << "Matrizes com nrow diferentes!" << std::endl;
		exit(1);
	}
	matriz<T> M(a.nrow(), a.ncol() + b.ncol(), 0);
	for(std::size_t i = 0; i < M.nrow(); i++)
		for(std::size_t j = 0; j < M.ncol() -1; j++){
			if(j < a.ncol())
				M(i,j) = a.getElement(i,j);
			else
				M(i,j) = b.getElement(i,j - a.ncol());
		}
	return M;	
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
	//Caso matriz 1x1
	if(ncol_ == 1)
		return getElement(0,0);
	
	//Caso matriz 2x2
	if(ncol_ == 2)
		return getElement(0,0) * getElement(1,1) - getElement(1,0) * getElement(0,1);
	
	//Caso matriz nxn, com n > 2
	T det = 0;
	for(std::size_t i = 0; i < ncol_; i++)
		det = det + getElement(0, i) * pow(-1, i) * detRecursive(removeRow(0).removeCol(i));

	return det;	
}

template <typename T>
T matriz<T>::detRecursive(matriz<T> a){
	//Caso matriz 2x2
	if(a.ncol() == 2)
		return a.getElement(0,0) * a.getElement(1,1) - a.getElement(1,0) * a.getElement(0,1);

	//Caso matriz nxn, com n > 2
	T det = 0;		
	for(std::size_t i = 0; i < a.ncol(); i++)
		det = det + a.getElement(0, i) * pow(-1, i) * detRecursive(a.removeRow(0).removeCol(i));

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
