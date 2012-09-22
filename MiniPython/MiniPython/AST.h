#ifndef AST_H
#define AST_H
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Tipo;

class ASTNode
{
public:
	int linea;
	virtual string ToString() = 0;

	ASTNode();
	exception ASTError(string nombre_funcion,string descripcion);
};

class EntornoTipos;

#pragma region Expresiones

enum ExprType
{
	opBin,
	opUn,
	constant,
	lValue
};

class Result;

class Expr: public ASTNode
{
public:
	Expr();
	virtual Tipo* validarSemantica();
	EntornoTipos* actualTypeEnvironment;
	virtual int getTipoExpr();
	virtual Result* Evaluate();
};

 #pragma region OpBinario

class OpBinExpr : public Expr
{
public:
	Expr *expr_izq;
	Expr *expr_der;

	OpBinExpr(Expr *e1, Expr *e2);
	int getTipoExpr();
};

class MayorExpr : public OpBinExpr
{
public:
	MayorExpr(Expr *e1, Expr *e2);
	
	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class MenorExpr : public OpBinExpr
{
public:
	MenorExpr(Expr *e1, Expr *e2);

	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class MayorIgualExpr : public OpBinExpr
{
public:
	MayorIgualExpr(Expr *e1, Expr *e2);

	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class MenorIgualExpr : public OpBinExpr
{
public:
	MenorIgualExpr(Expr *e1, Expr *e2);

	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class DistintoExpr : public OpBinExpr
{
public:
	DistintoExpr(Expr *e1, Expr *e2);
	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class IgualExpr : public OpBinExpr
{
public:
	IgualExpr(Expr *e1, Expr *e2);
	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class ModExpr : public OpBinExpr
{
public:
	ModExpr(Expr *e1, Expr *e2);

	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class AndExpr : public OpBinExpr
{
public:
	AndExpr(Expr *e1, Expr *e2);

	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class OrExpr : public OpBinExpr
{
public:
	OrExpr(Expr *e1, Expr *e2);

	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class SumaExpr : public OpBinExpr
{
public:
	SumaExpr(Expr *e1, Expr *e2);

	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class RestaExpr : public OpBinExpr
{
public:
	RestaExpr(Expr *e1, Expr *e2);

	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class DivisionExpr : public OpBinExpr
{
public:
	DivisionExpr(Expr *e1, Expr *e2);

	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class MultiplicacionExpr : public OpBinExpr
{
public:
	MultiplicacionExpr(Expr *e1, Expr *e2);
	string ToString();

	Tipo* validarSemantica();
	Result* Evaluate();
};

class ShiftLeftExpr : public OpBinExpr
{
public:
	ShiftLeftExpr(Expr *e1, Expr *e2);
	string ToString();
	Tipo *validarSemantica();
	Result* Evaluate();
};

class ShiftRightExpr : public OpBinExpr
{
public:
	ShiftRightExpr(Expr *e1, Expr *e2);
	string ToString();
	Tipo *validarSemantica();
	Result* Evaluate();
};
#pragma endregion

 #pragma region UnaryOp
class UnaryExpr : public Expr
{
public:
	Expr *expresion;
	UnaryExpr(Expr *e);	
	int getTipoExpr();
};

class NegateExpr : public UnaryExpr
{
public:
	NegateExpr(Expr *e);

	string ToString();
	Tipo *validarSemantica();
	Result* Evaluate();
};

class InvertExpr : public UnaryExpr
{
public:
	InvertExpr(Expr *e);

	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

#pragma endregion

 #pragma region Constant
class ConstantExpr : public Expr
{
	int getTipoExpr();
};

class NumExpr : public ConstantExpr
{
public:
	NumExpr(int val);
	int value;
	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();

};

class CharExpr : public ConstantExpr
{
public:

	CharExpr(string val);
	string value;
	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

class BooleanExpr : public ConstantExpr
{
public:
	BooleanExpr(bool val);
	bool value;
	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};
#pragma endregion

 #pragma region LValueExpr

class MethodDeclNode;

class LValueExpr : public Expr
{
public:
	string varname;
	MethodDeclNode* enclosingMethod;

	LValueExpr(string nombre);
	int getTipoExpr();
	virtual void setResult(Result* r)=0;
	virtual void SetTipo(Tipo *t) = 0;
};

class IDExpr : public LValueExpr
{
public:
	IDExpr(string nom);

	string ToString();
	Tipo* validarSemantica();
	void SetTipo(Tipo *t);
	void setResult(Result* r);
	Result* Evaluate();
};

class ArrayExpr : public LValueExpr
{
public:
	Expr *index;
	ArrayExpr(string nom,Expr *idx);

	string ToString();
	Tipo* validarSemantica();
	void SetTipo(Tipo *t);
	void setResult(Result* r);
	Result* Evaluate();
};

#pragma endregion

class MethodCallExpr : public Expr
{
public:
	vector<Expr*> Parametros;
	string nombre_funcion;

	MethodCallExpr(string nombre_func);

	string ToString();
	Tipo* validarSemantica();
	Result* Evaluate();
};

#pragma endregion

#pragma region Statements

class MethodDeclNode;

class Statement : public ASTNode
{
public:
	MethodDeclNode* enclosingMethod;
	Statement();
	virtual void validarSemantica()=0;
	virtual void Exec() = 0;
};

class BlockStatement : public Statement
{
public:
	vector<Statement *> statements;
	EntornoTipos* actualTypeEnvironment;
	bool brekio;
	bool continuar;
	BlockStatement();
	string ToString();
	void validarSemantica();
	void Exec();
};

class AssignStatement : public Statement
{
public:
	Expr *leftValue;
	Expr *rightValue;

	AssignStatement(Expr *lvalue, Expr *rvalue);

	string ToString();
	void validarSemantica();
	void Exec();
};

class MethodCallStatement : public Statement
{
public:
	MethodCallExpr *methodCall;

	MethodCallStatement(MethodCallExpr *mtc);

	string ToString();
	void validarSemantica();
	void Exec();
};

class ElseIfBlockStatement : public Statement
{
public:
	Expr *condition;
	BlockStatement *block;
	bool ejecutado;

	ElseIfBlockStatement(Expr *cond, BlockStatement *blck);

	string ToString();
	void validarSemantica();
	void Exec();
};

class IfStatement : public Statement
{
public:
	Expr *condition;
	BlockStatement *ifBlock;
	vector<ElseIfBlockStatement*> elifBlock_list;
	BlockStatement *elseBlock;

	IfStatement(Expr *cond, BlockStatement *ifBlck);

	string ToString();
	void validarSemantica();
	void Exec();
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

	WhileStatement(Expr *cond, BlockStatement *blck);

	string ToString();
	void validarSemantica();
	void Exec();
};

class ForStatement : public IterationStatement
{
public:
	string varname;
	Expr *exprInicial;
	Expr *exprFinal;
	BlockStatement *block;

	ForStatement(string vName);

	string ToString();
	void validarSemantica();
	void Exec();
};

#pragma endregion

class ReturnStatement : public Statement
{
public:
	Expr *expr;
	ReturnStatement(Expr *e);
	
	string ToString();
	void validarSemantica();
	void Exec();
};

class BreakStatement : public Statement
{
public:
	BreakStatement();
	IterationStatement* enclosingCycle;
	string ToString();
	void validarSemantica();
	void Exec();
};

class ContinueStatement : public Statement
{
public:
	ContinueStatement();
	IterationStatement* enclosingCycle;
	string ToString();
	void validarSemantica();
	void Exec();
};

class ReadStatement : public Statement
{
public:
	Expr *value;

	ReadStatement(Expr *val);

	string ToString();
	void validarSemantica();
	void Exec();
};

class PrintStatement : public Statement
{
public:
	vector<Expr *> printlist;

	string ToString();
	void validarSemantica();
	void Exec();
};

#pragma endregion

#pragma region Program

class Sentence: public ASTNode
{
public:
	EntornoTipos* actualTypeEnvironment;
	Sentence();
	virtual void validarSemantica()=0;
	virtual void Interpretar()=0;
};

class FieldDeclNode : public Sentence
{
public:
	AssignStatement *decl_stmnt;

	FieldDeclNode(AssignStatement *decl);
	void validarSemantica();
	void Interpretar();
	string ToString();
};

class MethodDeclNode : public Sentence
{
public:
	string methodName;
	Result* retorno;
	vector<string> methodArguments;
	BlockStatement *block;
	void validarSemantica();
	void Interpretar();

	MethodDeclNode(string name);

	string ToString();
};

class ProgramNode : public Sentence
{
public:
	string name;
	vector<FieldDeclNode *> field_decl_list;
	vector<MethodDeclNode *> method_decl_list;
	void validarSemantica();
	void Interpretar();

	ProgramNode(string nombre);

	string ToString();
};

#pragma endregion 

#pragma region Tipos

enum Types
{
	generico,
	entero,
	booleano,
	charconstant,
	Void,
	arreglo,
	funcion
};

class Tipo
{
public:
	virtual int getTipo();

	virtual bool EsEquivalente(Tipo *t);

	exception TypeError(string descripcion);
};

class Generico : public Tipo
{
public:
	int getTipo();

	bool EsEquivalente(Tipo *t);
};

class Entero : public Tipo
{
public:
	int getTipo();

	bool EsEquivalente(Tipo *t);
};

class Booleano : public Tipo
{
public:
	int getTipo();

	bool EsEquivalente(Tipo *t);
};

class CharConstant : public Tipo
{
public:
	int getTipo();

	bool EsEquivalente(Tipo *t);
};

class VoidF : public Tipo
{
public:
	int getTipo();

	bool EsEquivalente(Tipo *t);
};

class Arreglo : public Tipo
{
public:
	int tamaño;
	Tipo *arraytype;
	int getTipo();
	bool EsEquivalente(Tipo *t);
};

class Funcion : public Tipo
{
public:

	map<string,Tipo*> Parametros;
	Tipo *retorno;
	int getTipo();
	bool EsEquivalente(Tipo *t);
};


#pragma endregion

#pragma region EntornoTipos

class EntornoTipos
{
public:
	map<string, Tipo*> tablaSimbolosEntorno;
	EntornoTipos* entornoAnterior;

	EntornoTipos(EntornoTipos* anterior);
	void Put(string key,Tipo *type);
	void Set(string key,Tipo *type);
	Tipo *get(string key);
	bool Exists(string key); 
};
#pragma endregion

#pragma region Result/Variable
class Result;

class Variable
{
public:
	string name;
	Result* value;
	
	Variable(string nombre, Result* val);
};

enum TipoResult
{
	ResultEntero,ResultCharacter,ResultBoolean
};

class Result
{
public:
	virtual Result* getValue() = 0;
	virtual int getTipo()=0;
	virtual void Print()=0;
};

class IntResult:public Result
{
public:
	int value;
	IntResult(int valor);
	Result* getValue();
	int getTipo();
	void Print();
};

class BoolResult:public Result
{
public:
	bool value;
	BoolResult(bool val);
	Result* getValue();
	int getTipo();
	void Print();
};

class CharResult:public Result
{
public:
	string value;
	CharResult(string val);
	Result* getValue();
	int getTipo();
	void Print();
};
#pragma endregion

#pragma region EntornoVariables
class EntornoVariables
{
public:
	map<string,Variable*> tablaVariables;
};

class PilaEntornos
{
public:
	vector<EntornoVariables*>PilaEntornoVariablesActual;
	void push(EntornoVariables* entvar);
	void pop();
	void put(string key, Variable* var);
	Variable* get(string key);
	bool Exists(string key);
};
#pragma endregion

class Procedure
{
public:
	MethodDeclNode* metodo;
	//EntornoVariables* getEnvironment();
	//BlockStatement* getBlock();
	Procedure(MethodDeclNode* metodo);
};
#endif