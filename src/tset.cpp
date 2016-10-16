// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля
/*private:
  int MaxPower;       // максимальная мощность множества
  TBitField BitField; // битовое поле для хранения характеристического вектора*/
#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
	TBitField buf(mp);
	BitField = buf;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if ((Elem >= 0) && (Elem <= MaxPower)){
		BitField.ClrBit(Elem);
	}
	else{
		throw Elem;
	}
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower){
		return 0;
	}
	else{
		if (BitField == s.BitField){
			return 1;
		}
	}
	return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower){
		return 1;
	}
	else{
		if (BitField == s.BitField){
			return 0;
		}
	}
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet buf(BitField|s.BitField);
	return buf;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{

	if ((Elem >= 0) && (Elem <= MaxPower)){

	TSet buf(MaxPower);
	for (int i = 0; i < MaxPower; i++){
		if ((BitField.GetBit(i) == 1) || (i==Elem)){
			buf.InsElem(i);
		}
	}
	return buf;
	
		}
	else{
		throw Elem;
	}


}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet buf(MaxPower);
	for (int i = 0; i < MaxPower; i++){
		if ((BitField.GetBit(i) == 1) || (i != Elem)){
			buf.InsElem(i);
		}
	}
	return buf;
}


TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet buf(BitField&s.BitField);
	
	return buf;
}

TSet TSet::operator~(void) // дополнение
{
	TSet buf(MaxPower);
	for (int i = 0; i < MaxPower; i++){
		if (BitField.GetBit(i) != 1){
			buf.InsElem(i);
		}
	}
	return buf;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int a = 0;
	for (int i = s.GetMaxPower() - 1; i >= 0; i--){
		istr >> a;
		if (a == 1){
			s.InsElem(i);
		}
	}
	cout << endl;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = s.GetMaxPower() - 1; i >= 0; i--){
		ostr << s.IsMember(i) << ' ';
	}
	ostr << endl;
	return ostr;
}
