#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include "Tipos.h"

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
		msg << "Error de: " << nombre_funcion << "-> " << descripcion << "\nFila # "<<linea<<endl;
		throw exception(msg.str().c_str());
	}
};

#pragma region Expresiones
class Expr: public ASTNode
{
public:
	
	virtual Tipo* validarSemantica() 
	{
		throw ASTError("validarSemantica","Error Semantica");
	}

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

	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
		Tipo *t_der = expr_der->validarSemantica();
		
		if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
		{
			return new Tipo_Booleano();

		}else

		throw ASTError("MayorExpr","Tipos de la Expresion MAYOR (>) deben ser: booleano, flotante o caracter");
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

	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
		Tipo *t_der = expr_der->validarSemantica();
		
		if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
		{
			return new Tipo_Booleano();

		}else

		throw ASTError("MenorExpr","Tipos de la Expresion MENOR (<) deben ser: booleano, flotante o caracter");
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

	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
		Tipo *t_der = expr_der->validarSemantica();
		
		if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
		{
			return new Tipo_Booleano();

		}else

		throw ASTError("MayorIgualExpr","Tipos de la Expresion MAYOR IGUAL (>=) deben ser: booleano, flotante o caracter");
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

	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
		Tipo *t_der = expr_der->validarSemantica();
		
		if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
		{
			return new Tipo_Booleano();

		}else

		throw ASTError("MenorExpr","Tipos de la Expresion MENOR (<) deben ser: booleano, flotante o caracter");
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
	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
		Tipo *t_der = expr_der->validarSemantica();
		
		if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
		{
			return new Tipo_Booleano();

		}else

		throw ASTError("DistintoExpr","Tipos de la Expresion -DISTINTO DE (!=) deben ser: booleano, flotante o caracter");
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

	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
		Tipo *t_der = expr_der->validarSemantica();
		
		if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
		{
			return new Tipo_Booleano();

		}else

		throw ASTError("IgualExpr","Tipos de la Expresion IGUAL (=) deben ser: booleano, flotante o caracter");
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
	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
		Tipo *t_der = expr_der->validarSemantica();
		
		if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
		{
			return new Tipo_Booleano();

		}else

		throw ASTError("MayorExpr","Tipos de la Expresion MAYOR deben ser: booleano, flotante o caracter");
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

	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
		Tipo *t_der = expr_der->validarSemantica();
		
		if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
		{
			return new Tipo_Booleano();

		}else

		throw ASTError("ANDExpr","Tipos de la Expresion AND deben ser: booleano, flotante o caracter");
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

	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
		Tipo *t_der = expr_der->validarSemantica();
		
		if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
		{
			return new Tipo_Booleano();

		}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
		{
			return new Tipo_Booleano();

		}else

		throw ASTError("ORExpr","Tipos de la Expresion OR deben ser: booleano, flotante o caracter");
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

	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
        Tipo *t_der = expr_der->validarSemantica();

		if (t_izq->getTipo()==Types::entero && t_der->getTipo()==Types::entero)
		{
           return t_der;

		}else if (t_izq->getTipo()==Types::charconstant && t_der->getTipo()==Types::charconstant)
		{
			return t_der;
		}else

		throw ASTError("SumaExpr","Tipos Invalidos");

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

	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
        Tipo *t_der = expr_der->validarSemantica();

		if (t_izq->getTipo()==Types::entero && t_der->getTipo()==Types::entero)
		{
           return t_der;

		}else if (t_izq->getTipo()==Types::charconstant && t_der->getTipo()==Types::charconstant)
		{
			return t_der;
		}else

		throw ASTError("RestaExpr","Tipos Invalidos");

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

	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
        Tipo *t_der = expr_der->validarSemantica();

		if (t_izq->getTipo()==Types::entero && t_der->getTipo()==Types::entero)
		{
           return t_der;

		}else if (t_izq->getTipo()==Types::charconstant && t_der->getTipo()==Types::charconstant)
		{
			return t_der;
		}else

		throw ASTError("DivisionExpr","Tipos Invalidos");

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

	virtual Tipo* validarSemantica()
	{
		Tipo *t_izq = expr_izq->validarSemantica();
        Tipo *t_der = expr_der->validarSemantica();

		if (t_izq->getTipo()==Types::entero && t_der->getTipo()==Types::entero)
		{
           return t_der;

		}else if (t_izq->getTipo()==Types::charconstant && t_der->getTipo()==Types::charconstant)
		{
			return t_der;
		}else

		throw ASTError("MultiplicacionExpr","Tipos Invalidos");

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

 #pragma region Statements

class Statement : public ASTNode
{
};

class BlockStatement : public Statement
{
public:
	vector<Statement *> statements;

	virtual string ToString()
	{
		string retorno = "";

		for (int x = 0; x < statements.size(); x++)
		{
			retorno.append(statements[x]->ToString() + "\n");
		}

		return retorno;
	}
};

class AssignStatement : public Statement
{
public:
	Expr *leftValue;
	Expr *rightValue;

	AssignStatement(Expr *lvalue, Expr *rvalue)
	{
		leftValue = lvalue;
		rightValue = rvalue;
	}

	virtual string ToString()
	{
		return leftValue->ToString() + " = " + rightValue->ToString();
	}
};

class MethodCallStatement : public Statement
{
public:
	MethodCallExpr *methodCall;

	MethodCallStatement(MethodCallExpr *mtc)
	{
		methodCall = mtc;
	}

	virtual string ToString()
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
};

class ElseIfBlockStatement : public Statement
{
public:
	Expr *condition;
	BlockStatement *block;

	ElseIfBlockStatement(Expr *cond, BlockStatement *blck)
	{
		condition = cond;
		block = blck;
	}

	virtual string ToString()
	{
		string retorno = "else if (" + condition->ToString() + "):\n";
		retorno += block->ToString();
		return retorno;
	}
};

class IfStatement : public Statement
{
public:
	Expr *condition;
	BlockStatement *ifBlock;
	vector<ElseIfBlockStatement*> elifBlock_list;
	BlockStatement *elseBlock;

	IfStatement(Expr *cond, BlockStatement *ifBlck)
	{
		condition = cond;
		ifBlock = ifBlck;

		elseBlock = NULL;
	}

	virtual string ToString()
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
};


#pragma region Iteration

class IterationStatement : public Statement
{
};

class WhileStatement : public IterationStatement
{
public:
	Expr *condition;
	BlockStatement *block;

	WhileStatement(Expr *cond, BlockStatement *blck)
	{
		condition = cond;
		block = blck;
	}

	virtual string ToString()
	{
		string retorno = "while (" + condition->ToString() + "):\n";
		retorno += block->ToString();

		return retorno;
	}
};

class ForStatement : public IterationStatement
{
public:
	string varname;
	Expr *exprInicial;
	Expr *exprFinal;
	BlockStatement *block;

	ForStatement(string vName)
	{
		varname = vName;
		
		exprInicial = exprFinal = NULL;
		block = NULL;
	}

	virtual string ToString()
	{
		string retorno = "for (" + varname + " in " + exprInicial->ToString() + " .. " + exprFinal->ToString() + "):\n";
		retorno += block->ToString();

		return retorno;
	}
};

#pragma endregion

class ReturnStatement : public Statement
{
public:
	Expr *expr;

	ReturnStatement(Expr *e)
	{
		expr = e;
	}

	virtual string ToString()
	{
		return "return " + expr->ToString();
	}
};

class BreakStatement : public Statement
{
public:
	BreakStatement() { }

	virtual string ToString()
	{
		return "break";
	}
};

class ContinueStatement : public Statement
{
public:
	ContinueStatement() { }

	virtual string ToString()
	{
		return "continue";
	}
};

class ReadStatement : public Statement
{
public:
	Expr *value;

	ReadStatement(Expr *val)
	{
		value = val;
	}

	virtual string ToString()
	{
		return "read " + value->ToString();
	}
};

class PrintStatement : public Statement
{
public:
	vector<Expr *> printlist;

	virtual string ToString()
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
};

#pragma endregion

 #pragma region Program

class FieldDeclNode : public ASTNode
{
public:
	AssignStatement *decl_stmnt;

	FieldDeclNode(AssignStatement *decl)
	{
		decl_stmnt = decl;
	}

	virtual string ToString()
	{
		return decl_stmnt->ToString();
	}
};

class MethodDeclNode : public ASTNode
{
public:
	string methodName;
	vector<string> methodArguments;
	BlockStatement *block;

	MethodDeclNode(string name)
	{
		methodName = name;

		block = NULL;
	}

	virtual string ToString()
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
};

class ProgramNode : public ASTNode
{
public:
	string name;
	vector<FieldDeclNode *> field_decl_list;
	vector<MethodDeclNode *> method_decl_list;

	ProgramNode(string nombre)
	{
		name = nombre;
	}

	virtual string ToString()
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
};

#pragma endregion