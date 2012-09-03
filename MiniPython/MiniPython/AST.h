#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
extern int fila;

class ASTNode
{
public:
	int linea;
	virtual string ToString() = 0;

	ASTNode()
	{
		linea = fila;
	}

	exception ASTError(string nombre_funcion,string descripcion)
	{
		stringstream msg;
		msg << "Error de: "<<nombre_funcion<<"-> "<<descripcion<<"\nFila # "<<linea<<endl;
		throw exception(msg.str().c_str());
	}
};

class Expr: public ASTNode
{
};

 #pragma region OpBinario
class OpBinExpr : public Expr
{
public:
	Expr *expr_izq;
	Expr *expr_der;

	OpBinExpr(Expr *e1, Expr *e2)
	{
		expr_izq = e1;
		expr_der = e2;
	}
};

class MayorExpr : public OpBinExpr
{
public:
	MayorExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

	virtual string ToString()
	{
		return expr_izq->ToString() + " > " + expr_der->ToString();
	}
};

class MenorExpr : public OpBinExpr
{
public:
	MenorExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

	virtual string ToString()
	{
		return expr_izq->ToString() + " < " + expr_der->ToString();
	}
};

class MayorIgualExpr : public OpBinExpr
{
public:
	MayorIgualExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	virtual string ToString()
	{
		return expr_izq->ToString() + " >= " + expr_der->ToString();
	}
};

class MenorIgualExpr : public OpBinExpr
{
public:
	MenorIgualExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

	virtual string ToString()
	{
		return expr_izq->ToString() + " <= " + expr_der->ToString();
	}
};

class DistintoExpr : public OpBinExpr
{
public:
	DistintoExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	virtual string ToString()
	{
		return expr_izq->ToString() + " != " + expr_der->ToString();
	}
};

class IgualExpr : public OpBinExpr
{
public:
	IgualExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	virtual string ToString()
	{
		return expr_izq->ToString() + " == " + expr_der->ToString();
	}
};

class ModExpr : public OpBinExpr
{
public:
	ModExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	virtual string ToString()
	{
		return expr_izq->ToString() + " % " + expr_der->ToString();
	}
};

class AndExpr : public OpBinExpr
{
public:
	AndExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	virtual string ToString()
	{
		return expr_izq->ToString() + " and " + expr_der->ToString();
	}
};

class OrExpr : public OpBinExpr
{
public:
	OrExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	virtual string ToString()
	{
		return expr_izq->ToString() + " or " + expr_der->ToString();
	}
};

class SumaExpr : public OpBinExpr
{
public:
	SumaExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	virtual string ToString()
	{
		return expr_izq->ToString() + " + " + expr_der->ToString();
	}
};

class RestaExpr : public OpBinExpr
{
public:
	RestaExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	virtual string ToString()
	{
		return expr_izq->ToString() + " - " + expr_der->ToString();
	}
};

class DivisionExpr : public OpBinExpr
{
public:
	DivisionExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	virtual string ToString()
	{
		return expr_izq->ToString() + " / " + expr_der->ToString();
	}
};

class MultiplicacionExpr : public OpBinExpr
{
public:
	MultiplicacionExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	virtual string ToString()
	{
		return expr_izq->ToString() + " * " + expr_der->ToString();
	}
};

class ShiftLeftExpr : public OpBinExpr
{
public:
	ShiftLeftExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	virtual string ToString()
	{
		return expr_izq->ToString() + " << " + expr_der->ToString();
	}
};

class ShiftRightExpr : public OpBinExpr
{
public:
	ShiftRightExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	virtual string ToString()
	{
		return expr_izq->ToString() + " >> " + expr_der->ToString();
	}
};
#pragma endregion

 #pragma region UnaryOp
class UnaryExpr : public Expr
{
public:
	Expr *expresion;

	UnaryExpr(Expr *e)
	{
		expresion = e;
	}
	
};

class NegateExpr : public UnaryExpr
{
public:
	NegateExpr(Expr *e):UnaryExpr(e){}

	virtual string ToString()
	{
		return " (-) " + expresion->ToString();
	}
};

class InvertExpr : public UnaryExpr
{
public:
	InvertExpr(Expr *e):UnaryExpr(e){}

	virtual string ToString()
	{
		return " ~ " + expresion->ToString();
	}
};

#pragma endregion

 #pragma region Constant
class ConstantExpr : public Expr
{
};

class NumExpr : public ConstantExpr
{
public:

	virtual string ToString()
	{
		return " NUM ";
	}
};

class CharExpr : public ConstantExpr
{
public:

	virtual string ToString()
	{
		return " CHAR ";
	}
};

class BooleanExpr : public ConstantExpr
{
public:

	virtual string ToString()
	{
		return " BOOLEAN ";
	}
};
#pragma endregion

 #pragma region LValueExpr
class LValueExpr : public Expr
{
public:
	string varname;

	LValueExpr(string nombre)
	{
		varname = nombre;
	}
	
};

class IDExpr : public LValueExpr
{
public:
	IDExpr(string nom):LValueExpr(nom){}

	virtual string ToString()
	{
		return " "+varname+" ";
	}
};

class ArrayExpr : public LValueExpr
{
public:
	Expr *index;
	ArrayExpr(string nom,Expr *idx):LValueExpr(nom)
	{
		index = idx;
	}

	virtual string ToString()
	{
		return " "+varname+" ["+index->ToString()+"] ";
	}
};

class MethodCallExpr : public Expr
{
public:
	vector<Expr*> Parametros;
	string nombre_funcion;

	MethodCallExpr(string nombre_func)
	{
		nombre_funcion = nombre_func;
	}

	virtual string ToString()
	{
		string retorno;
		retorno = " "+nombre_funcion+" ";

		if(!Parametros.empty())
		{
			retorno.append("(");

			for(int x = 0; x<Parametros.size();x++)
			{
				retorno.append(Parametros[x]->ToString());

				if(x != Parametros.size()-1)
				{
					retorno.append(",");
				}
			}

			retorno.append(") ");
		}else
			retorno.append("() ");

		return retorno;
	}
};
#pragma endregion

