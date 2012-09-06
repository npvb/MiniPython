#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

namespace Types
{
	int entero = 0;
	int booleano = 1;
	int charconstant = 2;
}

class Tipo
{
public:

	Tipo(){}

	virtual int getTipo()
	{
		return -1;
	}

	virtual bool esEquivalente(Tipo *t)
	{
		return false;
	}

	exception TypeError(string descripcion)
	{
		stringstream msg;
		msg << "TypeError: "<<descripcion<<endl;
		throw exception(msg.str().c_str());
	}
};

class Tipo_Entero : public Tipo
{
public:

	int getTipo()
	{
		return Types::entero;
	}

	bool EsEquivalente(Tipo *t)
	{
		if(t->getTipo() == Types::entero)
		{
			return true;
		}else
		{
			return false;
		}
	}
};

class Tipo_Booleano : public Tipo
{
public:

	int getTipo()
	{
		return Types::booleano;
	}

	bool EsEquivalente(Tipo *t)
	{
		if(t->getTipo() == Types::booleano)
		{
			return true;
		}else
		{
			return false;
		}
	}
};

class Tipo_CharConstant : public Tipo
{
public:
	int getTipo()
	{
		return Types::charconstant;
	}

	bool EsEquivalente(Tipo *t)
	{
		if(t->getTipo() == Types::charconstant)
		{
			return true;
		}else
		{
			return false;
		}
	}
};