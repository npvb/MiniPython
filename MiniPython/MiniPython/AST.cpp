#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

#include "AST.h"

using namespace std;
extern int fila;
EntornoTipos* environment;

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

 #pragma region Expresiones

Expr::Expr()
{
	actTypeEnvironment = environment;
}

Tipo* Expr::validarSemantica() 
{
	throw ASTError("validarSemantica","Error Semantica");
}

 #pragma region OpBinario

OpBinExpr::OpBinExpr(Expr *e1, Expr *e2)
{
	expr_izq = e1;
	expr_der = e2;
}

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

	}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
	{
		return new Booleano();

	}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
	{
		return new Booleano();

	}else

	throw ASTError("MayorExpr","Tipos de la Expresion MAYOR (>) deben ser: booleano, flotante o caracter");
}


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
	}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
	{
		return new Booleano();

	}else
		throw ASTError("MenorExpr","Tipos de la Expresion MENOR (<) deben ser: booleano, flotante o caracter");
}

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
	}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
	{
		return new Booleano();
	}else
		throw ASTError("MayorIgualExpr","Tipos de la Expresion MAYOR IGUAL (>=) deben ser: booleano, flotante o caracter");
}


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
	}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
	{
		return new Booleano();
	}else
	throw ASTError("MenorExpr","Tipos de la Expresion MENOR (<) deben ser: booleano, flotante o caracter");
}


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
	}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
	{
		return new Booleano();
	}else
		throw ASTError("DistintoExpr","Tipos de la Expresion -DISTINTO DE (!=) deben ser: booleano, flotante o caracter");
}


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
	}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
	{
		return new Booleano();
	}else
		throw ASTError("IgualExpr","Tipos de la Expresion IGUAL (=) deben ser: booleano, flotante o caracter");
}


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
		return new Booleano();
	}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
	{
		return new Booleano();
	}else
		throw ASTError("MayorExpr","Tipos de la Expresion MAYOR deben ser: booleano, flotante o caracter");
}


AndExpr::AndExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}
string AndExpr::ToString()
{
	return expr_izq->ToString() + " and " + expr_der->ToString();
}

Tipo* AndExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
	Tipo *t_der = expr_der->validarSemantica();
		
	if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
	{
		return new Booleano();
	}else
		throw ASTError("ANDExpr","Tipos de la Expresion AND deben ser: booleano, flotante o caracter");
}

OrExpr::OrExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string OrExpr::ToString()
{
	return expr_izq->ToString() + " or " + expr_der->ToString();
}

Tipo* OrExpr::validarSemantica()
{
	Tipo *t_izq = expr_izq->validarSemantica();
	Tipo *t_der = expr_der->validarSemantica();
		
	if(t_izq->getTipo() == Types::entero && t_der->getTipo() == Types::entero)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::booleano && t_der->getTipo() == Types::booleano)
	{
		return new Booleano();
	}else if(t_izq->getTipo() == Types::charconstant && t_der->getTipo() == Types::charconstant)
	{
		return new Booleano();
	}else
		throw ASTError("ORExpr","Tipos de la Expresion OR deben ser: booleano, flotante o caracter");
}


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
	}else if (t_izq->getTipo()==Types::charconstant && t_der->getTipo()==Types::charconstant)
	{
		return t_der;
	}else
		throw ASTError("SumaExpr","Tipos Invalidos");

}



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
	}else if (t_izq->getTipo()==Types::charconstant && t_der->getTipo()==Types::charconstant)
	{
		return t_der;
	}else
		throw ASTError("RestaExpr","Tipos Invalidos");
}


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
		return t_der;
	}else if (t_izq->getTipo()==Types::charconstant && t_der->getTipo()==Types::charconstant)
	{
		return t_der;
	}else
		throw ASTError("DivisionExpr","Tipos Invalidos");
}



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
	}else if (t_izq->getTipo()==Types::charconstant && t_der->getTipo()==Types::charconstant)
	{
		return t_der;
	}else

	throw ASTError("MultiplicacionExpr","Tipos Invalidos");
}


ShiftLeftExpr::ShiftLeftExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string ShiftLeftExpr::ToString()
{
	return expr_izq->ToString() + " << " + expr_der->ToString();
}



ShiftRightExpr::ShiftRightExpr(Expr *e1, Expr *e2):OpBinExpr(e1,e2){}

string ShiftRightExpr::ToString()
{
	return expr_izq->ToString() + " >> " + expr_der->ToString();
}

#pragma endregion

 #pragma region UnaryOp

UnaryExpr::UnaryExpr(Expr *e)
{
	expresion = e;
}

NegateExpr::NegateExpr(Expr *e):UnaryExpr(e){}

string NegateExpr::ToString()
{
	return " (-) " + expresion->ToString();
}


InvertExpr::InvertExpr(Expr *e):UnaryExpr(e){}

string InvertExpr::ToString()
{
	return " ~ " + expresion->ToString();
}

#pragma endregion

 #pragma region Constant

string NumExpr::ToString()
{
	return " NUM ";
}



string CharExpr::ToString()
{
	return " CHAR ";
}


string BooleanExpr::ToString()
{
	return " BOOLEAN ";
}

#pragma endregion

 #pragma region LValueExpr

LValueExpr::LValueExpr(string nombre)
{
	varname = nombre;
}


IDExpr::IDExpr(string nom):LValueExpr(nom){}

string IDExpr::ToString()
{
	return " "+varname+" ";
}



ArrayExpr::ArrayExpr(string nom,Expr *idx):LValueExpr(nom)
{
	index = idx;
}

string ArrayExpr::ToString()
{
	return " "+varname+" ["+index->ToString()+"] ";
}


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
	Tipo *t = this->actTypeEnvironment->get(nombre_funcion);
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

				if(!t1->esEquivalente(t2))
				{
					throw ASTError("MethodCallExpr::validarSemantica","Tipo de Parametro Incorrecto "+(*it).first);
				}
			}
			return f1->retorno;
		}else
			throw ASTError("MethodCallExpr::validarSemantica","Cantidad Erronea de Parametros");
	}
}
#pragma endregion

#pragma endregion

 #pragma region Statements

string BlockStatement::ToString()
{
	string retorno = "";

	for (int x = 0; x < statements.size(); x++)
	{
		retorno.append(statements[x]->ToString() + "\n");
	}

	return retorno;
}

AssignStatement::AssignStatement(Expr *lvalue, Expr *rvalue)
{
	leftValue = lvalue;
	rightValue = rvalue;
}

string AssignStatement::ToString()
{
	return leftValue->ToString() + " = " + rightValue->ToString();
}




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


ElseIfBlockStatement::ElseIfBlockStatement(Expr *cond, BlockStatement *blck)
{
	condition = cond;
	block = blck;
}

string ElseIfBlockStatement::ToString()
{
	string retorno = "else if (" + condition->ToString() + "):\n";
	retorno += block->ToString();
	return retorno;
}



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



#pragma region Iteration



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


#pragma endregion


ReturnStatement::ReturnStatement(Expr *e)
{
	expr = e;
}

string ReturnStatement::ToString()
{
	return "return " + expr->ToString();
}


BreakStatement::BreakStatement() { }

string BreakStatement::ToString()
{
	return "break";
}


ContinueStatement::ContinueStatement() { }

string ContinueStatement::ToString()
{
	return "continue";
}



ReadStatement::ReadStatement(Expr *val)
{
	value = val;
}

string ReadStatement::ToString()
{
	return "read " + value->ToString();
}


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


#pragma endregion

 #pragma region Program

FieldDeclNode::FieldDeclNode(AssignStatement *decl)
{
	decl_stmnt = decl;
}

string FieldDeclNode::ToString()
{
	return decl_stmnt->ToString();
}


MethodDeclNode::MethodDeclNode(string name)
{
	methodName = name;

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

#pragma endregion

 #pragma region Tipos

int Tipo::getTipo()
{
	throw exception("Tipo::getTipo() error. No implementado!");
}

bool Tipo::esEquivalente(Tipo *t)
{
	throw exception("Tipo::esEquivalent(Tipo *t) error. No implementado!");
}

exception Tipo::TypeError(string descripcion)
{
	stringstream msg;
	msg << "TypeError: "<<descripcion<<endl;
	throw exception(msg.str().c_str());
}

int Entero::getTipo()
{
	return Types::entero;
}

bool Entero::EsEquivalente(Tipo *t)
{
	if(t->getTipo() == Types::entero)
	{
		return true;
	}else
	{
		return false;
	}
}


int Booleano::getTipo()
{
	return Types::booleano;
}

bool Booleano::EsEquivalente(Tipo *t)
{
	if(t->getTipo() == Types::booleano)
	{
		return true;
	}else
	{
		return false;
	}
}



int CharConstant::getTipo()
{
	return Types::charconstant;
}

bool CharConstant::EsEquivalente(Tipo *t)
{
	if(t->getTipo() == Types::charconstant)
	{
		return true;
	}else
	{
		return false;
	}
}


int Void::getTipo()
{
	return Types::Void;
}

bool Void::EsEquivalente(Tipo *t)
{
	if(t->getTipo() == Types::Void)
	{
		return true;
	}else
	{
		return false;
	}
}


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
			if(arr->arraytype->esEquivalente(this->arraytype))
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

int Funcion::getTipo()
{
	return Types::funcion;
}

bool Funcion::EsEquivalente(Tipo *t)
{
	if(t->getTipo() == Types::funcion)
	{
		Funcion* func = dynamic_cast<Funcion*>(t);
		if(func->retorno->esEquivalente(this->retorno))
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
#pragma endregion