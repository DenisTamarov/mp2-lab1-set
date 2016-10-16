// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
/*private:
int  BitLen; // длина битового поля - макс. к-во битов
TELEM *pMem; // память для представления битового поля
int  MemLen; // к-во эл-тов Мем для представления бит.поля*/
#include "tbitfield.h"
//+делает на один больше
TBitField::TBitField(int len)
{
	if (len <= 0){
		throw(len);
	}
	else{




		BitLen = len;
		MemLen = len / sizeof(TELEM) * 8 + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++){
			pMem[i] = 0;
		}


	}
}
//+
TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++){
		pMem[i] = bf.pMem[i];
	}
}
//+
TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int a = sizeof(TELEM) * 8;

	if (n % a == 0){
		return n / a;
	}
	else{
		return n / a + 1;
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	//нужные переменные
	int a = sizeof(TELEM) * 8;//кол-во битов в одном эл-те массива
	int numel = n / a;//номер элемента массива в котором содержится данный бит
	int numbit = n%a;//номер бита в элементе, который нам нужен



	//умножение на маску
	int mask = 1;
	mask = mask << numbit;
	mask = mask&pMem[numel];
	return mask;

}

// доступ к битам битового поля
//+
int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}
//+
void TBitField::SetBit(const int n) // установить бит
{
	//нужные переменные
	int a = sizeof(TELEM) * 8;
	int numel = n / a;
	int numbit = n%a;
	
	if ((n >= 0) && (n<=BitLen)){
		//узнаем значение бита в данный момент
		int buf = pMem[numel];
		buf = buf >> numbit;
		buf = buf & 1;


		//если бит 0, то меняем его на 1
		if (buf == 0){
			buf = 1;
			buf <<= numbit;
			pMem[numel] |= buf;
		}
	}
	else{
		throw n;
	}
}
//+
void TBitField::ClrBit(const int n) // очистить бит
{

	//нужные переменные
	int a = sizeof(TELEM) * 8;
	int numel = n / a;
	int numbit = n%a;
	
	
	if ((n >= 0) && (n <= BitLen)){
	//узнаем значение бита в данный момент
	int buf = pMem[numel];
	buf = buf >> numbit;
	buf = buf & 1;

	//если бит 1, то меняем его на 0
	if (buf == 1){
		buf <<= numbit;

		pMem[numel] &= ~buf;
		}
	}
	else{
		throw n;
	}
}
//+
int TBitField::GetBit(const int n) const // получить значение бита
{	

	if ((n >= 0) && (n <= BitLen)){
	//нужные переменные
	int a = sizeof(TELEM) * 8;
	int numel = n / a;
	int numbit = n%a;
	//сдвиг вправо до нужного бита и умножение на 1;
	int mask = 1;
	int buf = pMem[numel];
	buf = buf >> numbit;
	buf = buf & mask;
	//возвращение значения
	return(buf);
	}
	else{
		throw n;
	}
}

// битовые операции
//+
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++){
		pMem[i] = bf.pMem[i];
	}
	return *this;
}
//+
int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen){
		return 0;
	}
	else{
		for (int i = 0; i < MemLen; i++){
			if (pMem[i] != bf.pMem[i]){
				return 0;
			}
		}
	}
	return 1;
}
//+
int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen){
		return 1;
	}
	else{
		for (int i = 0; i < MemLen; i++){
			if (pMem[i] != bf.pMem[i]){
				return 1;
			}
		}
	}
	return 0;
}
//+
TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int bu;

	if (BitLen > bf.BitLen){
		bu = BitLen;

	}
	else{
		bu = bf.BitLen;
	}
	TBitField buf(bu);
	for (int i = 0; i < BitLen; i++){
		if (GetBit(i) == 1){
			buf.SetBit(i);
		}
	}
	for (int i = 0; i < bf.BitLen; i++){
		if (bf.GetBit(i) == 1){
			buf.SetBit(i);
		}
	}
	return buf;
}
//+
TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int bu,minbu;

	if (BitLen > bf.BitLen){
		bu = BitLen;
		minbu = bf.BitLen;
	}
	else{
		bu = bf.BitLen;
		minbu = BitLen;
	}
	TBitField buf(bu);
	for (int i = 0; i < minbu; i++){
		if ((GetBit(i) == 1) && (bf.GetBit(i) == 1)){
			buf.SetBit(i);
		}
	}


	return buf;
}
//+
TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < BitLen; i++){
		if (GetBit(i) == 1){
			ClrBit(i);
		}
		else{
			SetBit(i);
		}
	}
	return *this;
}

// ввод/вывод
//+
istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int a = 0;
	for (int i = bf.BitLen - 1; i >= 0; i--){
		istr >> a;
		if (a == 1){
			bf.SetBit(i);
		}
	}
	cout << endl;
	return istr;
}
//+
ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = bf.BitLen - 1; i >= 0; i--){
		ostr << bf.GetBit(i) << ' ';
	}
	ostr << endl;
	return ostr;
}
