// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = BitLen / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete []pMem;
}

int TBitField::GetMemIndex(int const n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int tmp = n % (sizeof(TELEM) * 8);
	TELEM mask = 1;
	mask = mask << tmp;
	return(mask);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const  // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int i = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[i] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int i = GetMemIndex(n);
	TELEM mask = ~GetMemMask(n);
	pMem[i] &= mask;
}
	

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n>-1)&&(n<BitLen))
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		if (pMem != NULL)
			delete pMem;
		pMem = new TELEM[MemLen];
	}
	if (pMem !=NULL)
		for (int i=0;i<MemLen;i++) pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
int flag = 1;
if (BitLen != bf.BitLen) flag=0;
else
{
	for (int i=0; i<MemLen; i++)
		if (pMem[i] != bf.pMem[i]) {
			flag=0;
			break;
		}
}
return flag;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
int flag = 0;
if (BitLen != bf.BitLen) flag=1;
else
{
	for (int i=0; i<MemLen; i++)
		if (pMem[i] != bf.pMem[i]) {
			flag=1;
			break;
		}
}
return flag;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int i, len = BitLen;
    if (bf.BitLen > len) len = bf.BitLen;
    TBitField tmp(len);
    for (i=0;i<MemLen;i++)
	    tmp.pMem[i] = pMem[i];
    for (i=0;i<bf.MemLen;i++)
        tmp.pMem[i] |= bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i, len = BitLen;
    if (bf.BitLen > len) len = bf.BitLen;
    TBitField tmp(len);
    for (i=0;i<MemLen;i++)
	    tmp.pMem[i] = pMem[i];
    for (i=0;i<bf.MemLen;i++)
        tmp.pMem[i] &= bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int i,len = BitLen;
	TBitField tmp(len);
	for (i=0;i<MemLen;i++)
		tmp.pMem[i] = ~pMem[i];
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i,len = bf.BitLen;
	char ch;
	for (i=0; i<len; i++){	
			istr>>ch;
			if (ch == '0') bf.ClrBit(i);
			else if (ch == '1') bf.SetBit(i);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int i,len = bf.BitLen;
	for (i=0; i<len; i++) {
		ostr<<bf.GetBit(i);
	}
	return ostr;
}
