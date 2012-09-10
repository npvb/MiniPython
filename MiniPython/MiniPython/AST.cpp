#include "AST.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

extern int fila;
extern EntornoTipos* environment;
extern MethodDeclNode* funcionActual;
extern IterationStatement* cicloActual;

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

Expr::Expr()
{
	actTypeEnvironment = environment;
}

Tipo* Expr::validarSemantica() 
{
	throw ASTError("validarSemantica","Error Semantica");
}

int Expr::getTipoExpr()
{
	return -1;
}

 #pragma region OpBinario

OpBinExpr::OpBinExpr(Expr *e1, Expr *e2)
{
	expr_izq = e1;
	expr_der = e2;
}

int OpBinExpr::getTipoExpr()
{
	return ExprType::opBin;
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		return new Booleano();
	}else
		throw ASTError("ModExpr","Tipos de la Expresion MAYOR deben ser: booleano, flotante o caracter");
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		return new Booleano();
	}else
		throw ASTError("AndExpr","Tipos de la Expresion AND deben ser: booleano, flotante o caracter");
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		return new Booleano();
	}else
		throw ASTError("OrExpr","Tipos de la Expresion OR deben ser: booleano, flotante o caracter");
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		return new Entero();
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		return new Booleano();
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		return new Entero();
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
	}else if(t_izq->getTipo() == Types::generico || t_der->getTipo() == Types::generico)
	{
		return new Entero();
	}else
		throw ASTError("MultiplicacionExpr","Tipos Invalidos");
}


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
		return new Entero();
	}else
		throw ASTError("ShiftLeftExpr","Tipos Invalidos");
}


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
		return new Entero();
	}else
		throw ASTError("ShiftRightExpr","Tipos Invalidos");
}
#pragma endregion

 #pragma region UnaryOp

UnaryExpr::UnaryExpr(Expr *e)
{
	expresion = e;
}

int UnaryExpr::getTipoExpr()
{
	return ExprType::opUn;
}

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
		return new Entero();
	}else
		throw ASTError("NegateExpr","Tipo Invalido");
}

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
		return new Entero();
	}else
		throw ASTError("InvertExpr","Tipo Invalido");
}

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

Tipo* NumExpr::validarSemantica()
{
	return new Entero();
}


string CharExpr::ToString()
{
	return " CHAR ";
}

Tipo* CharExpr::validarSemantica()
{
	return new CharConstant();
}

string BooleanExpr::ToString()
{
	return " BOOLEAN ";
}

Tipo* BooleanExpr::validarSemantica()
{
	return new Booleano();
}
#pragma endregion

 #pragma region LValueExpr

LValueExpr::LValueExpr(string nombre)
{
	varname = nombre;
}

int LValueExpr::getTipoExpr()
{
	return ExprType::lValue;
}

IDExpr::IDExpr(string nom):LValueExpr(nom){}

string IDExpr::ToString()
{
	return " "+varname+" ";
}

Tipo* IDExpr::validarSemantica()
{
	Tipo* t = this->actTypeEnvironment->get(varname);
	return t;
}

ArrayExpr::ArrayExpr(string nom,Expr *idx):LValueExpr(nom)
{
	index = idx;
}

Tipo* ArrayExpr::validarSemantica()
{
	Tipo* t = this->actTypeEnvironment->get(varname);
	
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
	entornoTipoActual = environment;
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

		if(lv->actTypeEnvironment->Exists(lv->varname))
		{
			Tipo* t_izq = lv->actTypeEnvironment->get(lv->varname);
			Tipo* t_der = rightValue->validarSemantica();

			if(!(t_izq->EsEquivalente(t_der)))
			{
				throw ASTError("AssignStatement","El Tipo del Lado Derecho debe ser el Mismo que el Lado Izq en una asignacion");
			}
		}else{
			Tipo* t_der = rightValue->validarSemantica();
			lv->actTypeEnvironment->Put(lv->varname,t_der);
		}	
	}else
		throw ASTError("AssignStatement","El Lado Izquierdo debe ser Un arreglo o una variable");
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

#pragma endregion

#pragma region ElseIfBlockStatement

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

void ElseIfBlockStatement::validarSemantica()
{
	Tipo* t_cond = condition->validarSemantica();
	if(t_cond->EsEquivalente(new Booleano()))
	{
		block->validarSemantica();
	}else
		throw ASTError("ElseIfBlockStatement","La condicion del elif debe ser de tipo Booleano");
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
	}else
		throw ASTError("IfStatement","La condicion del if debe ser de tipo Booleano");
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
	}else
		throw ASTError("WhileStatement","La condicion del while debe ser de tipo Booleano");
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
	if(block->entornoTipoActual->Exists(varname))
	{
		Tipo* t = block->entornoTipoActual->get(varname);
		
		if(!t->EsEquivalente(new Entero()))
		{
			throw ASTError("ForStatement","El Tipo de la Variable "+varname+" del For debe ser Entera");
		}

		Tipo *rango_init = exprInicial->validarSemantica();
		Tipo *rango_end = exprFinal->validarSemantica();

		if(!(rango_init->EsEquivalente(new Entero()) && rango_end->EsEquivalente(new Entero)))
		{
			throw ASTError("ForStatement","El Tipo del Rango Inicial y el Rango Final deben ser Enteros");
		}
	}else{
		block->entornoTipoActual->Put(varname,new Entero());
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
		Tipo* t = enclosingMethod->block->entornoTipoActual->get(enclosingMethod->methodName);
		Funcion* func = dynamic_cast<Funcion*>(t);

		if(func->retorno != NULL)
		{
			if(!t_return->EsEquivalente(func->retorno))
			{
				throw ASTError("ReturnStatement","Tipo de Retorno Incorrecto");
			}
		} else {
			func->retorno = t_return;
			enclosingMethod->block->entornoTipoActual->Set(enclosingMethod->methodName,func);
		}
	} else
		throw ASTError("ReturnStatement","Return inalcanzable o fuera de una funcion");
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

#pragma endregion

#pragma endregion

#pragma region Program

#pragma region Sentence

Sentence::Sentence()
{
	entornoTiposActual = environment;
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

#pragma endregion

#pragma region MethodDeclNode

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
			this->block->entornoTipoActual->Put(methodArguments[x], new Generico());
		}
	}

	this->entornoTiposActual->Put(this->methodName,funcion);
	block->validarSemantica();
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
	for(int x=0;x<field_decl_list.size();x++)
	{
		field_decl_list.at(x)->validarSemantica();
	}

	for(int x=0;x<method_decl_list.size();x++)
	{
		method_decl_list.at(x)->validarSemantica();
	}
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