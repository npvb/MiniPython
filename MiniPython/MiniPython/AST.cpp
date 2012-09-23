#include "AST.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>;

using namespace std;

extern int fila;
extern EntornoTipos* entornoTiposActual;
extern MethodDeclNode* funcionActual;
extern IterationStatement* cicloActual;
map<string,Procedure*> Procedimientos;


PilaEntornos pilaEntornoActual;

#pragma region ASTNode

ASTNode::ASTNode()
{
	linea = fila;
}

exception ASTNode::ASTError(string nombre_funcion,string descripcion)
{
		stringstream msg;
		msg << "Error de: " << nombre_funcion << "-> " << descripcion << "\nFila # "<<linea<<endl;
		throw exception(msg.str().c_str());
}

#pragma endregion

#pragma region Expresiones

#pragma region Expr

Expr::Expr()
{
	actualTypeEnvironment = entornoTiposActual;
}

Tipo* Expr::validarSemantica() 
{
	throw ASTError("validarSemantica","Error Semantica");
}

Result* Expr::Evaluate()
{
	throw ASTError("Evaluate","Error Interpretación");
}

int Expr::getTipoExpr()
{
	throw ASTError("validarSemantica","Error Semantica");
}

#pragma endregion

#pragma region OpBinario

#pragma region OpBinExpr

OpBinExpr::OpBinExpr(Expr *e1, Expr *e2)
{
	expr_izq = e1;
	expr_der = e2;
}

int OpBinExpr::getTipoExpr()
{
	return ExprType::opBin;
}

#pragma endregion

#pragma region MayorExpr

MayorExpr::MayorExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	
string MayorExpr::ToString()
{
	return expr_izq->ToString() + " > " + expr_der->ToString();
}

Tipo* MayorExpr:: validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
	Tipo *t_der = expr_der->validarSemantica();
	
	if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
	{
		return new Booleano();
	}
	else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("MayorExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("MayorExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Booleano();
	}else
		throw ASTError("MayorExpr","Tipos de la Expresion MAYOR (>) deben ser: entero.");
}

Result* MayorExpr::Evaluate()
{	
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());	

	return new BoolResult(r_izq->value > r_der->value);
}
#pragma endregion

#pragma region MenorExpr

MenorExpr::MenorExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string MenorExpr::ToString()
{
	return expr_izq->ToString() + " < " + expr_der->ToString();
}

Tipo* MenorExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
	Tipo *t_der = expr_der->validarSemantica();
		
	if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("MenorExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("MenorExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Booleano();
	}else
		throw ASTError("MenorExpr","Tipos de la Expresion MENOR (<) deben ser: entero.");
}

Result* MenorExpr::Evaluate()
{
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());	

	return new BoolResult(r_izq->value < r_der->value);
}
#pragma endregion

#pragma region MayorIgualExpr

MayorIgualExpr::MayorIgualExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string MayorIgualExpr::ToString()
{
	return expr_izq->ToString() + " >= " + expr_der->ToString();
}

Tipo* MayorIgualExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
	Tipo *t_der = expr_der->validarSemantica();

	if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("MayorIgualExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("MayorIgualExpr","Imposible inferir tipo para expresion generica.");
		}
		return new Booleano();
	}else
		throw ASTError("MayorIgualExpr","Tipos de la Expresion MAYOR IGUAL (>=) deben ser: entero.");
}

Result* MayorIgualExpr::Evaluate()
{
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());
	

	return new BoolResult(r_izq->value >= r_der->value);
}

#pragma endregion

#pragma region MenorIgualExpr

MenorIgualExpr::MenorIgualExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string MenorIgualExpr::ToString()
{
	return expr_izq->ToString() + " <= " + expr_der->ToString();
}

Tipo* MenorIgualExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
	Tipo *t_der = expr_der->validarSemantica();
		
	if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("MenorIgualExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("MenorIgualExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Booleano();
	}else
		throw ASTError("MenorIgualExpr","Tipos de la Expresion MENOR (<) deben ser: entero.");
}

Result* MenorIgualExpr::Evaluate()
{
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());	

	return new BoolResult(r_izq->value <= r_der->value);
}

#pragma endregion

#pragma region DistintoExpr

DistintoExpr::DistintoExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string DistintoExpr::ToString()
{
	return expr_izq->ToString() + " != " + expr_der->ToString();
}

Tipo* DistintoExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
	Tipo *t_der = expr_der->validarSemantica();
		
	if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("DistintoExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("DistintoExpr","Imposible inferir tipo para expresion generica.");
		}
		return new Booleano();
	}else
		throw ASTError("DistintoExpr","Tipos de la Expresion -DISTINTO DE (!=) deben ser: entero.");
}

Result* DistintoExpr::Evaluate()
{
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());
	

	return new BoolResult(r_der->value != r_izq->value);
}
#pragma endregion

#pragma region IgualExpr

IgualExpr::IgualExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
	
string IgualExpr::ToString()
{
	return expr_izq->ToString() + " == " + expr_der->ToString();
}

Tipo* IgualExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
	Tipo *t_der = expr_der->validarSemantica();
		
	if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("IgualExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("IgualExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Booleano();
	}else
		throw ASTError("IgualExpr","Tipos de la Expresion IGUAL (=) deben ser: entero.");
}

Result* IgualExpr::Evaluate()
{
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());	

	return new BoolResult(r_izq->value == r_der->value);
}
#pragma endregion

#pragma region ModExpr

ModExpr::ModExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string ModExpr::ToString()
{
	return expr_izq->ToString() + " % " + expr_der->ToString();
}

Tipo* ModExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
	Tipo *t_der = expr_der->validarSemantica();
		
	if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
	{
		return t_der;
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("ModExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("ModExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Entero();
	}else
		throw ASTError("ModExpr","Tipos de la Expresion MOD deben ser: entero.");
}

Result* ModExpr::Evaluate()
{
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());	

	return new IntResult(r_izq->value % r_der->value);
}

#pragma endregion

#pragma region AndExpr

AndExpr::AndExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string AndExpr::ToString()
{
	return expr_izq->ToString() + " and " + expr_der->ToString();
}

Tipo* AndExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
	Tipo *t_der = expr_der->validarSemantica();
		
	/*if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
	{
		return new Booleano();
	}else */
	if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
	{
		return t_der;
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Booleano());
			} else
				throw ASTError("AndExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Booleano());
			} else
				throw ASTError("AndExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Booleano();
	}else
		throw ASTError("AndExpr","Tipos de la Expresion AND deben ser: booleano.");
}

Result* AndExpr::Evaluate()
{
	BoolResult* r_izq = dynamic_cast<BoolResult*>(expr_izq->Evaluate());
	BoolResult* r_der = dynamic_cast<BoolResult*>(expr_der->Evaluate());	

	return new BoolResult(r_izq->value && r_der->value);
}
#pragma endregion

#pragma region OrExpr

OrExpr::OrExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string OrExpr::ToString()
{
	return expr_izq->ToString() + " or " + expr_der->ToString();
}

Tipo* OrExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
	Tipo *t_der = expr_der->validarSemantica();
		
	/*if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
	{
		return new Booleano();
	}else */
	if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
	{
		return t_der;
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Booleano());
			} else
				throw ASTError("OrExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Booleano());
			} else
				throw ASTError("OrExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Booleano();
	}else
		throw ASTError("OrExpr","Tipos de la Expresion OR deben ser: booleano.");
}

Result* OrExpr::Evaluate()
{
	BoolResult* r_izq = dynamic_cast<BoolResult*>(expr_izq->Evaluate());
	BoolResult* r_der = dynamic_cast<BoolResult*>(expr_der->Evaluate());
	

	return new BoolResult(r_izq->value || r_der->value);
}

#pragma endregion

#pragma region SumaExpr

SumaExpr::SumaExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string SumaExpr::ToString()
{
	return expr_izq->ToString() + " + " + expr_der->ToString();
}

Tipo* SumaExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
    Tipo *t_der = expr_der->validarSemantica();

	if (t_izq->getTipo()==Types::entero && t_der->getTipo()==Types::entero)
	{
		return t_der;
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("SumaExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("SumaExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Entero();
	}else
		throw ASTError("SumaExpr","Tipos de la Expresion SUMA deben ser: entero.");

}

Result* SumaExpr::Evaluate()
{
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());

	return new IntResult(r_izq->value + r_der->value);
}
#pragma endregion

#pragma region RestaExpr

RestaExpr::RestaExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string RestaExpr::ToString()
{
	return expr_izq->ToString() + " - " + expr_der->ToString();
}

Tipo* RestaExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
    Tipo *t_der = expr_der->validarSemantica();

	if (t_izq->getTipo()==Types::entero && t_der->getTipo()==Types::entero)
	{
		return t_der;
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("RestaExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("RestaExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Entero();
	}else
		throw ASTError("RestaExpr","Tipos de la Expresion RESTA deben ser: entero.");
}

Result* RestaExpr::Evaluate()
{
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());
	

	return new IntResult(r_izq->value - r_der->value);
}
#pragma endregion

#pragma region DivisionExpr

DivisionExpr::DivisionExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string DivisionExpr::ToString()
{
	return expr_izq->ToString() + " / " + expr_der->ToString();
}

Tipo* DivisionExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
    Tipo *t_der = expr_der->validarSemantica();

	if (t_izq->getTipo()==Types::entero && t_der->getTipo()==Types::entero)
	{
		return new Entero();
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("DivisionExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("DivisionExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Entero();
	}else
		throw ASTError("DivisionExpr","Tipos de la Expresion DIVISION deben ser: entero.");
}

Result* DivisionExpr::Evaluate()
{
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());
	
	if(r_izq->value == 0)
	{
		throw ASTError("DivisionExpr","No se Puede Dividir entre 0");
	}else
		return new IntResult(r_izq->value / r_der->value);
}
#pragma endregion

#pragma region MultiplicacionExpr

MultiplicacionExpr::MultiplicacionExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string MultiplicacionExpr::ToString()
{
	return expr_izq->ToString() + " * " + expr_der->ToString();
}

Tipo* MultiplicacionExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
    Tipo *t_der = expr_der->validarSemantica();

	if (t_izq->getTipo()==Types::entero && t_der->getTipo()==Types::entero)
	{
		return t_der;
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("MultiplicacionExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("MultiplicacionExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Entero();
	}else
		throw ASTError("MultiplicacionExpr","Tipos de la Expresion MULTIPLICACION deben ser: entero.");
}

Result* MultiplicacionExpr::Evaluate()
{
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());	

	return new IntResult(r_izq->value * r_der->value);
}
#pragma endregion

#pragma region ShiftLeftExpr

ShiftLeftExpr::ShiftLeftExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string ShiftLeftExpr::ToString()
{
	return expr_izq->ToString() + " << " + expr_der->ToString();
}

Tipo* ShiftLeftExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
    Tipo *t_der = expr_der->validarSemantica();

	if (t_izq->getTipo()==Types::entero && t_der->getTipo()==Types::entero)
	{
		return t_der;
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("ShiftLeftExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("ShiftLeftExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Entero();
	}else
		throw ASTError("ShiftLeftExpr","Tipos de la Expresion SHIFTLEFT deben ser: entero.");
}

Result* ShiftLeftExpr::Evaluate()
{
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());
	

	return new IntResult(r_izq->value << r_der->value);
}

#pragma endregion

#pragma region ShiftRightExpr

ShiftRightExpr::ShiftRightExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string ShiftRightExpr::ToString()
{
	return expr_izq->ToString() + " >> " + expr_der->ToString();
}

Tipo* ShiftRightExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
    Tipo *t_der = expr_der->validarSemantica();

	if (t_izq->getTipo()==Types::entero && t_der->getTipo()==Types::entero)
	{
		return t_der;
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		if (t_izq->getTipo() == Types::generico)
		{
			if (expr_izq->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_izq = dynamic_cast<LValueExpr *>(expr_izq);

				lv_izq->SetTipo(new Entero());
			} else
				throw ASTError("ShiftRightExpr","Imposible inferir tipo para expresion generica.");
		}
		else if (t_der->getTipo() == Types::generico)
		{
			if (expr_der->getTipoExpr() == ExprType::lValue)
			{
				LValueExpr *lv_der = dynamic_cast<LValueExpr *>(expr_der);

				lv_der->SetTipo(new Entero());
			} else
				throw ASTError("ShiftRightExpr","Imposible inferir tipo para expresion generica.");
		}

		return new Entero();
	}else
		throw ASTError("ShiftRightExpr","Tipos de la Expresion SHIFTRIGHT deben ser: entero.");
}

Result* ShiftRightExpr::Evaluate()
{
	IntResult* r_izq = dynamic_cast<IntResult*>(expr_izq->Evaluate());
	IntResult* r_der = dynamic_cast<IntResult*>(expr_der->Evaluate());
	

	return new IntResult(r_izq->value >> r_der->value);
}
#pragma endregion

#pragma endregion

#pragma region UnaryOp

#pragma region UnaryExpr

UnaryExpr::UnaryExpr(Expr *e)
{
	expresion = e;
}

int UnaryExpr::getTipoExpr()
{
	return ExprType::opUn;
}

#pragma endregion

#pragma region NegateExpr

NegateExpr::NegateExpr(Expr *e):UnaryExpr(e){}

string NegateExpr::ToString()
{
	return " (-) " + expresion->ToString();
}

Tipo* NegateExpr::validarSemantica()
{
	Tipo* t = expresion->validarSemantica();
	
	if(t->getTipo() == Types::entero)
	{
		return t;
	}else if(t->getTipo() == Types::generico){
		if (expresion->getTipoExpr() == ExprType::lValue)
		{
			LValueExpr *lv = dynamic_cast<LValueExpr *>(expresion);

			lv->SetTipo(new Entero());
		} else
			throw ASTError("NegateExpr","Imposible inferir tipo para expresion generica.");

		return new Entero();
	}else
		throw ASTError("NegateExpr","Tipos de la Expresion NEGATE (-) deben ser: entero.");
}

Result* NegateExpr::Evaluate()
{
	IntResult* r = dynamic_cast<IntResult*>(expresion->Evaluate());

	return new IntResult(-1*r->value);
}

#pragma endregion

#pragma region InvertExpr

InvertExpr::InvertExpr(Expr *e):UnaryExpr(e){}

string InvertExpr::ToString()
{
	return " ~ " + expresion->ToString();
}

Tipo* InvertExpr::validarSemantica()
{
	Tipo* t = expresion->validarSemantica();
	
	if(t->getTipo() == Types::entero)
	{
		return t;
	}else if(t->getTipo() == Types::generico){
		if (expresion->getTipoExpr() == ExprType::lValue)
		{
			LValueExpr *lv = dynamic_cast<LValueExpr *>(expresion);

			lv->SetTipo(new Entero());
		} else
			throw ASTError("InvertExpr","Imposible inferir tipo para expresion generica.");

		return new Entero();
	}else
		throw ASTError("InvertExpr","Tipos de la Expresion INVERT (~) deben ser: entero.");
}

Result* InvertExpr::Evaluate()
{
	IntResult* r = dynamic_cast<IntResult*>(expresion->Evaluate());

	return new IntResult( ~r->value);
}

#pragma endregion

#pragma endregion

#pragma region Constant

int ConstantExpr::getTipoExpr()
{
	return ExprType::constant;
}

string NumExpr::ToString()
{
	return " NUM ";
}

NumExpr::NumExpr(int val)
{
	value = val;
}

Tipo* NumExpr::validarSemantica()
{
	return new Entero();
}

Result* NumExpr::Evaluate()
{
	return new IntResult(this->value);
}

CharExpr::CharExpr(string val)
{
	value = val;
}

string CharExpr::ToString()
{
	return " CHAR ";
}

Tipo* CharExpr::validarSemantica()
{
	return new CharConstant();
}

Result* CharExpr::Evaluate()
{
	return new CharResult(this->value);
}

BooleanExpr::BooleanExpr(bool val)
{
	value = val;
}
string BooleanExpr::ToString()
{
	return " BOOLEAN ";
}

Tipo* BooleanExpr::validarSemantica()
{
	return new Booleano();
}

Result* BooleanExpr::Evaluate()
{
	return new BoolResult(this->value);
}

#pragma endregion

#pragma region LValue

#pragma region LValueExpr

LValueExpr::LValueExpr(string nombre)
{
	varname = nombre;

	enclosingMethod = funcionActual;
}

int LValueExpr::getTipoExpr()
{
	return ExprType::lValue;
}

#pragma endregion

#pragma region IDExpr

IDExpr::IDExpr(string nom):LValueExpr(nom){}

string IDExpr::ToString()
{
	return " "+varname+" ";
}

Tipo* IDExpr::validarSemantica()
{
	Tipo* t = this->actualTypeEnvironment->get(varname);
	return t;
}

void IDExpr::SetTipo(Tipo *t)
{
	if (this->enclosingMethod != NULL)
	{
		Tipo *t_func = this->actualTypeEnvironment->get(this->enclosingMethod->methodName);

		Funcion *func = dynamic_cast<Funcion *>(t_func);
	
		if (func->Parametros.count(varname) > 0)
		{
			func->Parametros[varname] = t;
		}
	}

	if (this->actualTypeEnvironment->Exists(varname))
	{
		this->actualTypeEnvironment->Set(varname, t);
	}
	else
	{
		this->actualTypeEnvironment->Put(varname, t);
	}
}

Result* IDExpr::Evaluate()
{
	Result* r = pilaEntornoActual.get(varname)->value;
	
	return r;	
}

void IDExpr::setResult(Result* r)
{
	if (pilaEntornoActual.Exists(this->varname))
	{
		Variable* var = pilaEntornoActual.get(this->varname);
		var->value = r;
	}else
	{
		Variable* var = new Variable(this->varname,r);
		pilaEntornoActual.put(this->varname,var);
	}
}
#pragma endregion

#pragma region ArrayExpr

ArrayExpr::ArrayExpr(string nom,Expr *idx):LValueExpr(nom)
{
	index = idx;
}

Tipo* ArrayExpr::validarSemantica()
{
	Tipo* t = this->actualTypeEnvironment->get(varname);
	
	if(t->getTipo()==Types::arreglo)
	{
		Arreglo* arr = dynamic_cast<Arreglo*>(t);

		if(this->index->validarSemantica()->EsEquivalente(new Entero))
		{
			return arr->arraytype;
		}else
			throw ASTError("ArrayExpr","El indice debe ser un entero");
	}else
		throw ASTError("ArrayExpr",varname+" no es de Tipo Arreglo");
}

string ArrayExpr::ToString()
{
	return " "+varname+" ["+index->ToString()+"] ";
}

void ArrayExpr::SetTipo(Tipo *t)
{
	Tipo* tl = this->actualTypeEnvironment->get(varname);
	
	if(tl->getTipo()==Types::arreglo)
	{
		Arreglo* arr = dynamic_cast<Arreglo*>(tl);

		arr->arraytype = t;
	}else
		throw ASTError("ArrayExpr",varname+" no es de Tipo Arreglo");
}

Result* ArrayExpr::Evaluate()
{
	throw ASTError("ArrayExpr","NO IMPLEMENTADO");
}

void ArrayExpr::setResult(Result* r)
{
	throw ASTError("ArrayExpr","NO IMPLEMENTADO");
}
#pragma endregion

#pragma endregion

#pragma region MethodCallExpr

MethodCallExpr::MethodCallExpr(string nombre_func)
{
	nombre_funcion = nombre_func;
}

string MethodCallExpr::ToString()
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

Tipo* MethodCallExpr::validarSemantica()
{
	Tipo *t = this->actualTypeEnvironment->get(nombre_funcion);

	if(t->getTipo() == Types::funcion)
	{
		Funcion* f1 = dynamic_cast<Funcion*>(t);

		if(this->Parametros.size() == f1->Parametros.size())
		{
			map<string, Tipo*>::iterator it;
			int index = 0;
			for(it=f1->Parametros.begin();it!=f1->Parametros.end();it++)
			{
				Tipo *t1 = this->Parametros.at(index)->validarSemantica();
				Tipo *t2 = (*it).second;

				if(t2->getTipo() == Types::generico)
				{
					t2 = t1;
					f1->Parametros[(*it).first] = t1;//revisar si es neceserario reescribirlo en la tabla de simbolos, ya que tome en cuenta que es *
				}

				if(!t1->EsEquivalente(t2))
				{
					throw ASTError("MethodCallExpr::validarSemantica","Tipo de Parametro Incorrecto "+(*it).first);
				}
				index++;
			}
			return f1->retorno;
		}else
			throw ASTError("MethodCallExpr::validarSemantica","Cantidad Erronea de Parametros");
	}
}

Result* MethodCallExpr::Evaluate()
{
	Procedure* p = Procedimientos[this->nombre_funcion];
	EntornoVariables* regact =new EntornoVariables();

	for(int x=0;x<Parametros.size();x++)
	{
		Result* resultado = Parametros.at(x)->Evaluate();
		Variable* var = new Variable(p->metodo->methodArguments.at(x),resultado);
		regact->tablaVariables[p->metodo->methodArguments.at(x)] = var;
	}

	pilaEntornoActual.push(regact);
	p->metodo->block->Exec();
	pilaEntornoActual.pop();

	Result* ret = p->metodo->retorno;
	p->metodo->retorno = NULL;
	return ret;
}
#pragma endregion

#pragma endregion

#pragma region Statements

#pragma region Statement 

Statement::Statement()
{
	this->enclosingMethod = funcionActual;
}

#pragma endregion

#pragma region BlockStatement

BlockStatement::BlockStatement()
{
	actualTypeEnvironment = entornoTiposActual;
	brekio = false;
	continuar = false;
}

string BlockStatement::ToString()
{
	string retorno = "";

	for (int x = 0; x < statements.size(); x++)
	{
		retorno.append(statements[x]->ToString() + "\n");
	}

	return retorno;
}

void BlockStatement::validarSemantica()
{
	for(int x = 0;x<statements.size();x++)
	{
		statements.at(x)->validarSemantica();
	}
}

void BlockStatement::Exec()
{
	for(int x =0;x<statements.size();x++)
	{
		if(enclosingMethod->retorno!=NULL)
		{
			break;
		}

		statements.at(x)->Exec();
		
		if(brekio == true)
		{
			break;
		}else if(continuar == true)
		{
			continuar = false;
			continue;
		}
	}
}
#pragma endregion

#pragma region AssignStatement

AssignStatement::AssignStatement(Expr *lvalue, Expr *rvalue)
{
	leftValue = lvalue;
	rightValue = rvalue;
}

string AssignStatement::ToString()
{
	return leftValue->ToString() + " = " + rightValue->ToString();
}

void AssignStatement::validarSemantica()
{
	if(leftValue->getTipoExpr() == ExprType::lValue)
	{
		LValueExpr* lv = dynamic_cast<LValueExpr*>(leftValue);

		if(lv->actualTypeEnvironment->Exists(lv->varname))
		{
			Tipo* t_izq = lv->actualTypeEnvironment->get(lv->varname);
			Tipo* t_der = rightValue->validarSemantica();

			if (t_izq->getTipo() == Types::generico)
			{
				lv->SetTipo(t_der);
			}

			if(!(t_izq->EsEquivalente(t_der)))
			{
				throw ASTError("AssignStatement","El Tipo del Lado Derecho debe ser el Mismo que el Lado Izq en una asignacion");
			}
		}else{
			Tipo* t_der = rightValue->validarSemantica();
			lv->SetTipo(t_der);
		}	
	}else
		throw ASTError("AssignStatement","El Lado Izquierdo debe ser Un arreglo o una variable");
}

void AssignStatement::Exec()
{
	LValueExpr* lv = dynamic_cast<LValueExpr*>(this->leftValue);
	Result* r_der = this->rightValue->Evaluate();

	lv->setResult(r_der);
	

}

#pragma endregion

#pragma region MethodCallStatement

MethodCallStatement::MethodCallStatement(MethodCallExpr *mtc)
{
	methodCall = mtc;
}

string MethodCallStatement::ToString()
{
	string retorno = methodCall->nombre_funcion + "(";

	for (int x = 0; x < methodCall->Parametros.size(); x++)
	{
		retorno.append(methodCall->Parametros[x]->ToString());

		if (x != methodCall->Parametros.size() - 1)
			retorno.append(", ");
	}

	retorno.append(")");

	return retorno;
}

void MethodCallStatement::validarSemantica()
{
	this->methodCall->validarSemantica();
}

void MethodCallStatement::Exec()
{
	methodCall->Evaluate();
}

#pragma endregion

#pragma region ElseIfBlockStatement

ElseIfBlockStatement::ElseIfBlockStatement(Expr *cond, BlockStatement *blck)
{
	condition = cond;
	block = blck;
	ejecutado = false;
}

string ElseIfBlockStatement::ToString()
{
	string retorno = "else if (" + condition->ToString() + "):\n";
	retorno += block->ToString();
	return retorno;
}

void ElseIfBlockStatement::validarSemantica()
{
	Tipo* t_cond = condition->validarSemantica();
	if(t_cond->EsEquivalente(new Booleano()))
	{
		block->validarSemantica();
	} else if (t_cond->getTipo() == Types::generico)
	{
		if (condition->getTipoExpr() == ExprType::lValue)
		{
			LValueExpr *lv = dynamic_cast<LValueExpr *>(condition);

			lv->SetTipo(new Booleano());
		} else
			throw ASTError("ElseIfBlockStatement","Imposible inferir tipo para expresion generica.");
	}
	else
		throw ASTError("ElseIfBlockStatement","La condicion del elif debe ser de tipo Booleano");
}

void ElseIfBlockStatement::Exec()
{
	BoolResult* conditionElif = dynamic_cast<BoolResult*>(condition->Evaluate());

	if(conditionElif->value)
	{
		block->Exec();
		ejecutado = true;
	}
}
#pragma endregion

#pragma region IfStatement

IfStatement::IfStatement(Expr *cond, BlockStatement *ifBlck)
{
	condition = cond;
	ifBlock = ifBlck;

	elseBlock = NULL;
}

string IfStatement::ToString()
{
	string retorno;
	retorno = "if (" + condition->ToString() + "):\n";
	retorno += ifBlock->ToString();

	for (int x = 0; x < elifBlock_list.size(); x++)
	{
		retorno += elifBlock_list[x]->ToString();
	}

	if (elseBlock != NULL)
	{
		retorno += "else \n";
		retorno += elseBlock->ToString();
	}

	return retorno;
}

void IfStatement::validarSemantica()
{
	Tipo* t_cond = condition->validarSemantica();

	if(t_cond->EsEquivalente(new Booleano()))
	{
		this->ifBlock->validarSemantica();

		for(int x=0;x<elifBlock_list.size();x++)
		{
			elifBlock_list.at(x)->validarSemantica();
		}
		
		if(elseBlock!=NULL)
		{
			elseBlock->validarSemantica();
		}
	}else if (t_cond->getTipo() == Types::generico)
	{
		if (condition->getTipoExpr() == ExprType::lValue)
		{
			LValueExpr *lv = dynamic_cast<LValueExpr *>(condition);

			lv->SetTipo(new Booleano());
		} else
			throw ASTError("IfStatement","Imposible inferir tipo para expresion generica.");
	}
	else
		throw ASTError("IfStatement","La condicion del if debe ser de tipo Booleano");
}

void IfStatement::Exec()
{
	BoolResult* condicionIf = dynamic_cast<BoolResult*>(condition->Evaluate());

	if(condicionIf->value)
	{
		ifBlock->Exec();

	}else
	{
		bool flag = false;
		for(int x=0;x<elifBlock_list.size();x++)
		{
			elifBlock_list.at(x)->Exec();

			if(elifBlock_list.at(x)->ejecutado)
			{
				flag = true;
				break;
			}
		}
		if(flag == false)
		{
			if(elseBlock!=NULL)
			{
				elseBlock->Exec();
			}
		}
	}

}
#pragma endregion

#pragma region IterationStatement

#pragma region WhileStatement

WhileStatement::WhileStatement(Expr *cond, BlockStatement *blck)
{
	condition = cond;
	block = blck;
}

string WhileStatement::ToString()
{
	string retorno = "while (" + condition->ToString() + "):\n";
	retorno += block->ToString();

	return retorno;
}

void WhileStatement::validarSemantica()
{
	Tipo* t_cond = condition->validarSemantica();
	if(t_cond->EsEquivalente(new Booleano()))
	{
		block->validarSemantica();
	}
	else if (t_cond->getTipo() == Types::generico)
	{
		if (condition->getTipoExpr() == ExprType::lValue)
		{
			LValueExpr *lv = dynamic_cast<LValueExpr *>(condition);

			lv->SetTipo(new Booleano());
		} else
			throw ASTError("WhileStatement","Imposible inferir tipo para expresion generica.");
	}else
		throw ASTError("WhileStatement","La condicion del while debe ser de tipo Booleano");
}

void WhileStatement::Exec()
{
	while(true/*wCondition->value*/)
	{
		BoolResult* wCondition = dynamic_cast<BoolResult*>(condition->Evaluate());
		if(wCondition->value)
		{
			block->Exec();
		}else
			break;
	}

}
#pragma endregion

#pragma region ForStatement

ForStatement::ForStatement(string vName)
{
	varname = vName;
		
	exprInicial = exprFinal = NULL;
	block = NULL;
}

string ForStatement::ToString()
{
	string retorno = "for (" + varname + " in " + exprInicial->ToString() + " .. " + exprFinal->ToString() + "):\n";
	retorno += block->ToString();

	return retorno;
}

void ForStatement::validarSemantica()
{
	if(block->actualTypeEnvironment->Exists(varname))
	{
		Tipo* t = block->actualTypeEnvironment->get(varname);
		
		if(!t->EsEquivalente(new Entero()))
		{
			if (t->getTipo() == Types::generico)
			{
				block->actualTypeEnvironment->Set(varname, new Entero());
			} else
				throw ASTError("ForStatement","El Tipo de la Variable "+varname+" del For debe ser Entera");
		}

		Tipo *rango_init = exprInicial->validarSemantica();
		Tipo *rango_end = exprFinal->validarSemantica();

		if(!(rango_init->EsEquivalente(new Entero()) && rango_end->EsEquivalente(new Entero)))
		{
			if (rango_init->getTipo() == Types::generico)
			{
				if (exprInicial->getTipoExpr() == ExprType::lValue)
				{
					LValueExpr *lv = dynamic_cast<LValueExpr *>(exprInicial);

					lv->SetTipo(new Entero());
				} else
					throw ASTError("ForStatement","Imposible inferir tipo para expresion de rango inicial generica.");
			}
			else if (rango_end->getTipo() == Types::generico)
			{
				if (exprFinal->getTipoExpr() == ExprType::lValue)
				{
					LValueExpr *lv = dynamic_cast<LValueExpr *>(exprFinal);

					lv->SetTipo(new Entero());
				} else
					throw ASTError("ForStatement","Imposible inferir tipo para expresion de rango final generica.");
			} 
			else
				throw ASTError("ForStatement","El Tipo del Rango Inicial y el Rango Final deben ser Enteros");
		}
	}else{
		block->actualTypeEnvironment->Put(varname,new Entero());
	}
}

void ForStatement::Exec()
{
	IDExpr* variable = new IDExpr(varname);
	IntResult* valorExpInicial = dynamic_cast<IntResult*>(exprInicial->Evaluate());
	IntResult* valorExpFinal = dynamic_cast<IntResult*>(exprFinal->Evaluate());

	if(pilaEntornoActual.Exists(varname))
	{
		Variable* variabl = pilaEntornoActual.get(varname);
		variable->setResult(valorExpInicial);	

	}else
	{
		Variable* var = new Variable(varname, valorExpInicial);
		pilaEntornoActual.put(varname,var);
	}
	
	IntResult* valorVariable = dynamic_cast<IntResult*>(variable->Evaluate());
	
	if(valorExpInicial->value < valorExpFinal->value)
	{
		while(valorVariable->value < valorExpFinal->value )
		{
			block->Exec();
			valorVariable->value++;
		}
	}else
	{
		while(valorVariable->value > valorExpFinal->value )
		{
			block->Exec();
			valorVariable->value--;
		}
	}
}

#pragma endregion

#pragma endregion

#pragma region ReturnStatement

ReturnStatement::ReturnStatement(Expr *e)
{
	expr = e;
}

string ReturnStatement::ToString()
{
	return "return " + expr->ToString();
}
 
void ReturnStatement::validarSemantica()
{
	Tipo* t_return = new VoidF();
	
	if(expr!=NULL)
	{
		t_return = expr->validarSemantica();
	}

	if(enclosingMethod!=NULL)
	{
		Tipo* t = enclosingMethod->block->actualTypeEnvironment->get(enclosingMethod->methodName);
		Funcion* func = dynamic_cast<Funcion*>(t);

		if(func->retorno->getTipo() != Types::generico)
		{
			if(!t_return->EsEquivalente(func->retorno))
			{
				throw ASTError("ReturnStatement","Tipo de Retorno Incorrecto");
			}
		} else {
			func->retorno = t_return;
			//enclosingMethod->block->actualTypeEnvironment->Set(enclosingMethod->methodName,func);
		}
	} else
		throw ASTError("ReturnStatement","Return inalcanzable o fuera de una funcion");
}

void ReturnStatement::Exec()
{
	Result* res = dynamic_cast<Result*>(expr->Evaluate());
	enclosingMethod->retorno = res;

}
#pragma endregion

#pragma region BreakStatement

BreakStatement::BreakStatement() { }

string BreakStatement::ToString()
{
	return "break";
}

void BreakStatement::validarSemantica()
{
	if(enclosingCycle==NULL)
	{
		throw ASTError("BreakStatement","No puede existir un break fuera de un ciclo");
	}
}

void BreakStatement::Exec()
{
	enclosingMethod->block->brekio = true;
	
}
#pragma endregion

#pragma region ContinueStatement

ContinueStatement::ContinueStatement() { }

string ContinueStatement::ToString()
{
	return "continue";
}

void ContinueStatement::validarSemantica()
{
	if(enclosingCycle==NULL)
	{
		throw ASTError("ContinueStatement","No puede existit un Continue fuera de un ciclo");
	}
}

void ContinueStatement::Exec()
{
	enclosingMethod->block->continuar = true;
}
#pragma endregion

#pragma region ReadStatement

ReadStatement::ReadStatement(Expr *val)
{
	value = val;
}

string ReadStatement::ToString()
{
	return "read " + value->ToString();
}

void ReadStatement::validarSemantica()
{
	if(value->getTipoExpr() != ExprType::lValue)
	{
		throw ASTError("ReadStatement","Expresion del Read debe ser de tipo Id o Arreglo");
	}
}

void ReadStatement::Exec()
{
	LValueExpr* valor = dynamic_cast<LValueExpr*>(value);
	Tipo* t = value->validarSemantica();

	if(t->getTipo() == Types::entero)
	{
		int intres = 0;
		cin>>intres;
		IntResult* intresul = new IntResult (intres);
		valor->setResult(intresul);

	}else if (t->getTipo() == Types::booleano)
	{
		bool booleanRes = false;
		cin>>booleanRes;
		BoolResult* boolresul = new BoolResult (booleanRes);
		valor->setResult(boolresul);	

	}else 
	{
		string strRes = "";
		cin>>strRes;
		CharResult* charresul = new CharResult (strRes);
		valor->setResult(charresul);		
	}
}
#pragma endregion

#pragma region PrintStatement

string PrintStatement::ToString()
{
	string retorno = "print ";

	for (int x = 0; x < printlist.size(); x++)
	{
		retorno += printlist[x]->ToString();

		if (x != printlist.size() - 1)
			retorno.append(", ");
	}

	return retorno;
}

void PrintStatement::validarSemantica()
{
	if(printlist.size()>0){
		for(int x=0;x<printlist.size();x++)
		{
			printlist.at(x)->validarSemantica();
		}
	}else
		throw ASTError("PrintStatement","No Hay Valores a Imprimir");
}

void PrintStatement::Exec()
{
	for(int x=0;x<printlist.size();x++)
	{
		printlist.at(x)->Evaluate()->Print();
	}
}
#pragma endregion

#pragma endregion

#pragma region Program

#pragma region Sentence

Sentence::Sentence()
{
	actualTypeEnvironment = entornoTiposActual;
}

#pragma endregion

#pragma region FieldDeclNode

FieldDeclNode::FieldDeclNode(AssignStatement *decl)
{
	decl_stmnt = decl;
}

string FieldDeclNode::ToString()
{
	return decl_stmnt->ToString();
}

void FieldDeclNode::validarSemantica()
{
	decl_stmnt->validarSemantica();
}

void FieldDeclNode::Interpretar()
{
	decl_stmnt->Exec();
}

#pragma endregion

#pragma region MethodDeclNode

MethodDeclNode::MethodDeclNode(string name)
{
	methodName = name;
	retorno = NULL;
	block = NULL;
}

string MethodDeclNode::ToString()
{
	string retorno = "def " + methodName + " (";

	if (methodArguments.size() > 0) {
		for (int x = 0; x < methodArguments.size(); x++)
		{
			retorno += methodArguments[x];
			if (x != methodArguments.size() - 1)
				retorno += ", ";
		}
	}
		
	retorno += "):\n";
	retorno += block->ToString();

	return retorno;
}

void MethodDeclNode::validarSemantica()
{
	Funcion* funcion = new Funcion();
	funcion->retorno = new Generico();

	for(int x=0;x<methodArguments.size();x++)
	{
		if (funcion->Parametros.count(methodArguments[x]) > 0)
		{
			throw ASTError("MethodDeclNode", "Ya existe un argumento con el nombre " + methodArguments[x]);
		} else {
			funcion->Parametros[methodArguments[x]] = new Generico();
			this->block->actualTypeEnvironment->Put(methodArguments[x], new Generico());
		}
	}

	this->actualTypeEnvironment->Put(this->methodName,funcion);
	block->validarSemantica();

	Procedure* procs = new Procedure(this);
	Procedimientos[this->methodName] = procs; //acumular procedimientos en mapa global fuuu!!!
}

void MethodDeclNode::Interpretar()
{
	this->block->Exec();
}
#pragma endregion

#pragma region ProgramNode

ProgramNode::ProgramNode(string nombre)
{
	name = nombre;
}

string ProgramNode::ToString()
{
	string retorno = "class " + name +  " :\n";
		
	for (int x = 0; x < field_decl_list.size(); x++)
	{
		retorno += field_decl_list[x]->ToString() + "\n";
	}

	for (int x = 0; x < method_decl_list.size(); x++)
	{
		retorno += method_decl_list[x]->ToString() + "\n";
	}

	return retorno;
}

void ProgramNode::validarSemantica()
{
	bool hasMain = false;

	for(int x=0;x<field_decl_list.size();x++)
	{
		field_decl_list.at(x)->validarSemantica();
	}

	for(int x=0;x<method_decl_list.size();x++)
	{
		method_decl_list.at(x)->validarSemantica();

		if (method_decl_list[x]->methodName == "main")
			hasMain = true;
	}

	if (hasMain == false)
		ASTError("ProgramNode", "No existe metodo main");
}

void ProgramNode::Interpretar()
{
	pilaEntornoActual.push(new EntornoVariables);
	for(int x=0;x<field_decl_list.size();x++)
	{
		field_decl_list.at(x)->Interpretar();
	}

	MethodDeclNode* Main=NULL;
	for(int x=0;x<method_decl_list.size();x++)
	{
		if (method_decl_list[x]->methodName == "main"){
			Main = method_decl_list[x];
			break;
		}
	}

	Main->Interpretar();

	pilaEntornoActual.pop();
}

#pragma endregion

#pragma endregion

#pragma region Tipos

#pragma region Tipo

int Tipo::getTipo()
{
	throw exception("Tipo::getTipo() error. No implementado!");
}

bool Tipo::EsEquivalente(Tipo *t)
{
	throw exception("Tipo::esEquivalent(Tipo *t) error. No implementado!");
}

exception Tipo::TypeError(string descripcion)
{
	stringstream msg;
	msg << "TypeError: "<<descripcion<<endl;
	throw exception(msg.str().c_str());
}

#pragma endregion

#pragma region Generico

int Generico::getTipo()
{
	return Types::generico;
}

bool Generico::EsEquivalente(Tipo *t)
{
	return true;
}

#pragma endregion

#pragma region Entero

int Entero::getTipo()
{
	return Types::entero;
}

bool Entero::EsEquivalente(Tipo *t)
{
	if(t->getTipo() == Types::entero || t->getTipo() == Types::generico)
	{
		return true;
	}else
	{
		return false;
	}
}

#pragma endregion

#pragma region Booleano

int Booleano::getTipo()
{
	return Types::booleano;
}

bool Booleano::EsEquivalente(Tipo *t)
{
	if(t->getTipo() == Types::booleano || t->getTipo() == Types::generico)
	{
		return true;
	}else
	{
		return false;
	}
}

#pragma endregion

#pragma region CharConstant

int CharConstant::getTipo()
{
	return Types::charconstant;
}

bool CharConstant::EsEquivalente(Tipo *t)
{
	if(t->getTipo() == Types::charconstant || t->getTipo() == Types::generico)
	{
		return true;
	}else
	{
		return false;
	}
}

#pragma endregion

#pragma region VoidF

int VoidF::getTipo()
{
	return Types::Void;
}

bool VoidF::EsEquivalente(Tipo *t)
{
	if(t->getTipo() == Types::Void || t->getTipo() == Types::generico)
	{
		return true;
	}else
	{
		return false;
	}
}

#pragma endregion

#pragma region Arreglo

int Arreglo::getTipo()
{
	return Types::arreglo;
}

bool Arreglo::EsEquivalente(Tipo *t)
{
	if(t->getTipo() == Types::arreglo)
	{
		Arreglo *arr = dynamic_cast<Arreglo*>(t);
		if(arr->tamaño == this->tamaño)
		{
			if(arr->arraytype->EsEquivalente(this->arraytype))
			{
				return true;
			}else
				return false;
		}else
			return false;
	}else
	{
		return false;
	}
}

#pragma endregion

#pragma region Funcion

int Funcion::getTipo()
{
	return Types::funcion;
}

bool Funcion::EsEquivalente(Tipo *t)
{
	if(t->getTipo() == Types::funcion)
	{
		Funcion* func = dynamic_cast<Funcion*>(t);
		if(func->retorno->EsEquivalente(this->retorno))
		{
			return true;
		}else
			return false;
	}else
	{
		return false;
	}
}

#pragma endregion

#pragma endregion

#pragma region EntornoTipos

EntornoTipos::EntornoTipos(EntornoTipos* anterior)
{	
	entornoAnterior = anterior;
}

void EntornoTipos::Put(string key,Tipo *type)
{
	if(tablaSimbolosEntorno.count(key) > 0)
	{
		string msg;
		msg="Variable "+key+" ya fue Declarada \n";
		throw exception(msg.c_str());
	}else
		tablaSimbolosEntorno[key] = type;
}

Tipo* EntornoTipos:: get(string key)
{
	for(EntornoTipos *e = this;e!=NULL;e = e->entornoAnterior)
	{
		if(e->tablaSimbolosEntorno.count(key)>0)
		{
			return e->tablaSimbolosEntorno[key];
		}
	}
 	string msg;
	msg="Variable "+key+" No Existe \n";
	throw exception(msg.c_str());
} 

void EntornoTipos::Set(string key, Tipo* type)
{
	for(EntornoTipos *e = this;e!=NULL;e = e->entornoAnterior)
	{
		if(e->tablaSimbolosEntorno.count(key)>0)
		{
			 e->tablaSimbolosEntorno[key] = type;
		}
	}
}

bool EntornoTipos::Exists(string key)
{
	for(EntornoTipos *e = this;e!=NULL;e = e->entornoAnterior)
	{
		if(e->tablaSimbolosEntorno.count(key)>0)
		{
			return true;
		}
	}
 	return false;
}

#pragma endregion

#pragma region Variable/Result
Variable::Variable(string nombre,Result* val)
{
	name = nombre;
	value = val;
}

IntResult::IntResult(int val)
{
	value = val;
}

void IntResult::Print()
{
	cout<<this->value<<endl;
}

Result* IntResult::getValue()
{
	return new IntResult(value);
}

int IntResult::getTipo()
{
	return TipoResult::ResultEntero;
}

BoolResult::BoolResult(bool val)
{
	value = val;
}

Result* BoolResult::getValue()
{
	return new BoolResult(value);
}

int BoolResult::getTipo()
{
	return TipoResult::ResultBoolean;
}
void BoolResult::Print()
{
	cout<<this->value<<endl;
}
/*int IntResult::getTipo()
{
	return TipoResult::ResultBoolean;
}*/

CharResult::CharResult(string val)
{
	value = val;
}

Result* CharResult::getValue()
{
	return new CharResult(value);
}

int CharResult::getTipo()
{
	return TipoResult::ResultCharacter;
}

void CharResult::Print()
{
	cout<<this->value<<endl;
}

void PilaEntornos::push(EntornoVariables* entvar)
{
	PilaEntornoVariablesActual.push_back(entvar);
}

void PilaEntornos::pop()
{
	PilaEntornoVariablesActual.pop_back();
}

void PilaEntornos::put(string key, Variable* var)
{
	PilaEntornoVariablesActual.back()->tablaVariables[key] = var;
}

Variable* PilaEntornos::get(string key)
{
	for(int x=PilaEntornoVariablesActual.size()-1;x>=0;x--)
	{
		if(PilaEntornoVariablesActual.at(x)->tablaVariables.count(key)>0)
		{
			return PilaEntornoVariablesActual.at(x)->tablaVariables[key];
		}
	}

	string msg;
	msg="Variable "+key+" No Existe! \n";
	throw exception(msg.c_str());
}

bool PilaEntornos::Exists(string key)
{
	for(int x=PilaEntornoVariablesActual.size()-1;x>=0;x--)
	{
		if(PilaEntornoVariablesActual.at(x)->tablaVariables.count(key)>0)
		{
			return true;
		}
	}
 	return false;
}
#pragma endregion

#pragma region Procedure

Procedure::Procedure(MethodDeclNode* metodo)
{
	this->metodo = metodo;
}

/*EntornoVariables* Procedure::getEnvironment()
{
	EntornoVariables* retorno = new EntornoVariables();

	for(int x=0;this->metodo->methodArguments.size();x++)
	{
		this->metodo->methodArguments.at(x) = NULL;
		retorno->tablaVariables.at(x) = NULL;
	}

	return retorno;
}*/

#pragma endregion