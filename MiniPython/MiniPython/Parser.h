#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include "Lexer.h"
#include "AST.h"

using namespace std;

extern EntornoTipos* environment;
extern MethodDeclNode* funcionActual;
extern int fila;
extern IterationStatement* cicloActual;

class Parser
{
public:

	Lexer *lex;
	Token token;

	#pragma region Aux_Functions
	bool Numero()
	{
		if(token.getTipo() == TokenType::LIT_NUM_FLOAT || token.getTipo() == TokenType::LIT_NUM_INT)
		{
			return true;
		}else 
			return false;
	}

	bool Boolean()
	{
		switch(token.Tipo)
		{
			case TokenType::LIT_FALSE:
			case TokenType::LIT_TRUE:
				return true;

			default: 
				return false;
		}

	}

	bool Es_expresion()
	{
		switch(token.Tipo)
		{
			case TokenType::OP_SUM:
			case TokenType::OP_REST:
			case TokenType::OP_MULT:
			case TokenType::OP_DIV:
			case TokenType::OP_SLEFT:
			case TokenType::OP_SRIGHT:
			case TokenType::OP_MOD:
			case TokenType::ID:
			case TokenType::SIGNO_PARENTESIS_IZQ:

			case TokenType::OP_MENOR:
			case TokenType::OP_MENOR_IGUAL:
			case TokenType::OP_MAYOR:
			case TokenType::OP_MAYOR_IGUAL:
			case TokenType::LIT_CADENA:

			case TokenType::OP_IGUAL_IGUAL:
			case TokenType::OP_DISTINTO_DE:
			case TokenType::OP_NEGACION:

			case TokenType::OP_AND:
			case TokenType::OP_OR:
			case TokenType::OP_NOT:

			case TokenType::LIT_NUM_FLOAT:
			case TokenType::LIT_NUM_INT: 

			case TokenType::LIT_FALSE:
			case TokenType::LIT_TRUE:
	
			return true;

			default:
				return false;
		}
	
	}

	bool OperadorMat()
	{
		
		switch(token.Tipo)
		{
			case TokenType::OP_SUM:
			case TokenType::OP_REST:
			case TokenType::OP_MULT:
			case TokenType::OP_DIV:
			case TokenType::OP_SLEFT:
			case TokenType::OP_SRIGHT:
			case TokenType::OP_MOD:
				return true;

			default:
				return false;
		}
	}

	bool OperadorRel()
	{
		
		switch(token.Tipo)
		{
			case TokenType::OP_MENOR:
			case TokenType::OP_MENOR_IGUAL:
			case TokenType::OP_MAYOR:
			case TokenType::OP_MAYOR_IGUAL:
			case TokenType::OP_DISTINTO_DE:
			case TokenType::OP_IGUAL_IGUAL:
				return true;

			default:
				return false;
		}
	}

	bool OperadorEq()
	{
		
		switch(token.Tipo)
		{
			case TokenType::OP_IGUAL_IGUAL:
			case TokenType::OP_DISTINTO_DE:
				return true;

			default:
				return false;
		}
	}

	bool OperadorCon()
	{
		
		switch(token.Tipo)
		{
			case TokenType::OP_AND:
			case TokenType::OP_OR:
			case TokenType::OP_NOT:
				return true;

			default:
				return false;
		}
	}

	bool isStatement()
	{
		switch(token.Tipo)
		{
			
		case TokenType::KW_IF:
		case TokenType::KW_WHILE:
		case TokenType::KW_FOR:
		case TokenType::KW_RETURN:
		case TokenType::KW_BREAK:
		case TokenType::ID:
		case TokenType::KW_PRINT:
		case TokenType::KW_READ:
		case TokenType::OP_ASIG:
			return true;

		default:
			return false;
		}
	}

	exception PythonError(string nombre_funcion,string descripcion)
	{
		stringstream msg;
		msg << "Error de: "<<nombre_funcion<<"-> "<<descripcion<<"\nFila "<<fila<<" Columna "<<lex->columna<<endl;
		throw exception(msg.str().c_str());
	}

	#pragma endregion

	Parser(Lexer *l)
	{
		lex = l;
		token = Token();
	}

	ASTNode* program()
	{
		try
		{
			token = lex->NextToken();
			if(token.getTipo() == TokenType::KW_CLASS)
			{
				token = lex->NextToken();
				if(token.getTipo() == TokenType::ID)
				{
					environment = new EntornoTipos(NULL);
					
					ProgramNode *prgm = new ProgramNode(token.lexema);

					token = lex->NextToken();
					
					if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
					{
						token = lex->NextToken();

						InicioBloque();

						while(token.getTipo() == TokenType::ID)
						{
							FieldDeclNode *field_dec = dynamic_cast<FieldDeclNode *> (field_decl());
							prgm->field_decl_list.push_back(field_dec);
						}

						while(token.getTipo() == TokenType::KW_DEF)
						{
							MethodDeclNode *method_dec =dynamic_cast<MethodDeclNode *> (method_decl());
							prgm->method_decl_list.push_back(method_dec);
						}

						if(token.getTipo() == TokenType::OP_DEDENT)
						{
							token = lex->NextToken();
						}
						environment = NULL;
						return prgm;
					}else
					{
						throw PythonError("Program","Se Esperaba : despues del Nombre de la Clase");
					}
				}else 
				{
					throw PythonError("Program","Se Esperaba Nombre de la Clase");
				}
			}else
			{
				throw PythonError("Program","Se Esperaba la palabra Class al Inicio del Programa");
			}
		}catch (char* e)
		{
			string error = "program: ";
			throw exception(error.append(e).c_str());
		}
	}

	ASTNode* field_decl()
	{
		try
		{
			AssignStatement *assignStmnt = dynamic_cast<AssignStatement *> (assign());
			return new FieldDeclNode(assignStmnt);
		}catch (char* e)
        {
			throw PythonError("field_decl",e);
        }
	}

	ASTNode* method_decl()
	{
		try
		{
			token = lex->NextToken();

			if(token.getTipo() == TokenType::ID)
			{
				MethodDeclNode *mtd = new MethodDeclNode(token.lexema);
				token = lex->NextToken();

				funcionActual = mtd;
				if(token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ)
				{
					token = lex->NextToken();

					if(token.getTipo() == TokenType::ID)
					{
						mtd->methodArguments.push_back(token.lexema);

						token = lex->NextToken();
						while(token.getTipo() == TokenType::SIGN_COMA)
						{
							token = lex->NextToken();

							if(token.getTipo() == TokenType::ID)
							{
								mtd->methodArguments.push_back(token.lexema);
								token = lex->NextToken();
							}else 
							{
								throw PythonError("method_decl","Se Esperaba un ID despues de la coma");
							}
						}

						if(token.getTipo() == TokenType::SIGNO_PARENTESIS_DER)
						{
							token = lex->NextToken();
						} else {
							throw PythonError("method_decl","Se Esperaba un ) despues de los argumentos");
						}
					}
				}
				
				if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
				{
					token = lex->NextToken();
					mtd->block = dynamic_cast<BlockStatement *> (block());
					funcionActual=NULL;

					return mtd;
				} else {
					throw PythonError("method_decl","Se Esperaba una definicion del metodo");
				}
			}
		}catch (char* e)
		{
			throw PythonError("method_decl",e);
		}
}

	Statement* block()
	{
		try
		{
			InicioBloque();

			EntornoTipos* savedEnv  = environment;
			environment = new EntornoTipos(environment);
			BlockStatement *blck = new BlockStatement();
		
			while(isStatement())
			{
				Statement *stmnt = statement();
				blck->statements.push_back(stmnt);
			}
				
			FinBloque();
			environment = savedEnv;

			return blck;
			
		}catch (char* e)
        {
			throw PythonError("block",e);
         }
	}

	Statement* statement()
	{
		try
		{
			#pragma region Assign
			if(token.getTipo() == TokenType::ID)
			{
				return Statementp();
			}
			#pragma endregion

			#pragma region Read/Print Method_Call
			else if(token.getTipo() == TokenType::KW_READ || token.getTipo() == TokenType::KW_PRINT)
			{
				return methodcall();
			}
			#pragma endregion 

			#pragma region IF_STATEMENT
			else if(token.getTipo() == TokenType::KW_IF)
			{
				token = lex->NextToken();
				Expr *cond = expr();
			
				if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
				{
					token = lex->NextToken();
					BlockStatement *blck = dynamic_cast<BlockStatement *> (block());

					IfStatement *if_stmnt = new IfStatement(cond, blck);
					
					while(token.getTipo() == TokenType::KW_ELIF)
					{
						token = lex->NextToken();
						Expr *elif_cond = expr();
			
						if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
						{
							token = lex->NextToken();
							BlockStatement *elif_blck = dynamic_cast<BlockStatement *>(block());

							ElseIfBlockStatement *elif_blck_stmnt = new ElseIfBlockStatement(elif_cond, elif_blck);

							if_stmnt->elifBlock_list.push_back(elif_blck_stmnt);
						}else 
						{
							throw PythonError("Statement->IF","Se Esperaban : al final de la Expresion");
						}
					}

					if(token.getTipo() == TokenType::KW_ELSE)
					{
						token = lex->NextToken();

						if(token.getTipo() ==TokenType::SIGN_DOSPUNTOS)
						{
							token = lex->NextToken();
							BlockStatement *else_blck = dynamic_cast<BlockStatement *>(block());

							if_stmnt->elseBlock = else_blck;
						}else 
						{
							throw PythonError("Statement->IF->ELSE","Se Esperaba : Luego del Else");
						}
					}

					return if_stmnt;

				}else 
				{
					throw PythonError("Statement->IF","Se Esperaba : Luego de la Expresion");
				}
			}
			#pragma endregion

			#pragma region WHILE_STATEMENT
			else if(token.getTipo() == TokenType::KW_WHILE)
			{
				token = lex->NextToken();
				Expr *cond = expr();	

				if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
				{
					token = lex->NextToken();
					WhileStatement* whiles = new WhileStatement(NULL, NULL);
					cicloActual = whiles;

					BlockStatement *blck = dynamic_cast<BlockStatement *> (block());

					whiles->block = blck;
					whiles->condition = cond;
					cicloActual =  NULL;
					
					return whiles;
				}else 
				{
					throw PythonError("Statement->While","Se Esperaba : Luego de Expr");
				}
			}
			#pragma endregion

			#pragma region FOR_STATEMENT
			else if(token.getTipo() == TokenType::KW_FOR)
			{
				token = lex->NextToken();

				if(token.getTipo() == TokenType::ID)
				{
					ForStatement *for_stmnt = new ForStatement(token.lexema);
					token = lex->NextToken();

					if(token.getTipo() == TokenType::KW_IN)
					{
						token = lex->NextToken();
						range(for_stmnt);

						if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
						{
							token = lex->NextToken();
							cicloActual = for_stmnt;
							for_stmnt->block = dynamic_cast<BlockStatement*>(block());
							cicloActual = NULL;
							return for_stmnt;
						}else
						{ 
							throw PythonError("Statement->FOR","Se Esperaba : luego del Rango");
						}

					}else 
					{
						throw PythonError("Statement->FOR","Se Esperaba Palabra Reservada in");
					}
				}else
				{
					//throw exception("FOR: Se Esperaba un ID");
					throw PythonError("Statement->FOR","Se Esperaba un ID");
				}
			}
			#pragma endregion

			#pragma region RETURN_STATEMENT
			else if(token.getTipo() == TokenType::KW_RETURN)
			{
				token = lex->NextToken();
				Expr *e = expr();
				return new ReturnStatement(e);
			}	
			#pragma endregion

			#pragma region BREAK_STATEMENT
			else if(token.getTipo() == TokenType::KW_BREAK)
			{
				token = lex->NextToken();
				return new BreakStatement();
			}
			#pragma endregion
		}catch (char* e)
        {
			throw PythonError("Statement",e);
        }
	}

	Statement* Statementp()
	{
		try
		{
			if(token.getTipo() == TokenType::ID)
			{
				IDExpr *id = new IDExpr(token.lexema);
				token = lex->NextToken();

				if (token.getTipo() == TokenType::OP_ASIG ||
					token.getTipo() == TokenType::SIGNO_BRACKET_IZQ)
				{
					return assignP(id);
				}
				else if(token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ)
				{
					MethodCallExpr *mtc = new MethodCallExpr(id->varname);
					mtc = (MethodCallExpr *)methodcall2(mtc);
					return new MethodCallStatement(mtc);
				}
			}
		}catch(char* e)
        {
			throw PythonError("Statementp",e);
         }
	}

	Statement* assign()
	{
		try
		{
			IDExpr *id = new IDExpr(token.lexema);
			token = lex->NextToken();

			Expr *lval = lvalue(id);

			if(token.getTipo()  == TokenType::OP_ASIG)
			{
				token = lex->NextToken();
				Expr *rval = expr();
				return new AssignStatement(lval, rval);
			}
			else
			{
				throw PythonError("ASSIGN","Se Esperaba Operador de Asignacion");
			}
		}
		catch (char* e)
        {
			string error = "assign: ";
			throw exception(error.append(e).c_str());
        }
	}

	Statement* assignP(IDExpr *inherit)
	{
		try
		{
			if(token.getTipo() == TokenType::SIGNO_BRACKET_IZQ)
			{
				token = lex->NextToken();
				Expr *idx = expr();

				if(token.getTipo()==TokenType::SIGNO_BRACKET_DER)
				{
					token = lex->NextToken();

					ArrayExpr *arr = new ArrayExpr(inherit->varname, idx);

					if(token.getTipo() == TokenType::OP_ASIG)
					{
						token = lex->NextToken();
						Expr * rval = expr();

						return new AssignStatement(arr, rval);
					}else
					{
						throw PythonError("assignP","Se Esperaba =");
					}
				}else
				{
					throw PythonError("assignP","Se Esperaba ]");
				}
			}

			if(token.getTipo()  == TokenType::OP_ASIG)
			{
				token =lex->NextToken();
				Expr *rval =  expr();
				
				return new AssignStatement(inherit, rval);
			}else
			{
				throw PythonError("assignP","Se Esperaba Operador de Asignacion");
			}			
		}catch (char* e)
        {
			throw PythonError("assignP",e);	
        }
	}

	Statement* methodcall()
	{
		try
		{
			#pragma region PRINT_METHODCALL	
			if(token.getTipo() == TokenType::KW_PRINT) 
			{			
				token = lex->NextToken();

				PrintStatement *print = new PrintStatement();

				if (Es_expresion()) {
					Expr *printexpr = expr();
					print->printlist.push_back(printexpr);
				} else 
				{
					throw PythonError("METHODCALL-> PRINT","Se Esperaba una expresion");
				}

				while(token.getTipo() == TokenType::SIGN_COMA)
				{
					token = lex->NextToken();
					Expr *printexpr = expr();
					print->printlist.push_back(printexpr);
				}

				return print;
			}
			#pragma endregion

			#pragma region READ_METHODCALL
			else if(token.getTipo() == TokenType::KW_READ)
			{
				token = lex->NextToken();
				if(token.getTipo() == TokenType::ID)
				{
					IDExpr *id = new IDExpr(token.lexema);
					token = lex->NextToken();
					Expr *lvlExpr = lvalue(id);

					return new ReadStatement(lvlExpr);
				}else
					throw PythonError("METHODCALL","Se Esperaba un ID despues de la palabra reservada READ");
			}
			#pragma endregion

		}catch (char* e)
        {
			throw PythonError("METHODCALL",e);
        }
	}

	Expr* methodcall2(MethodCallExpr* inherit)
	{
		try
		{
			if(token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ)
			{
				token = lex->NextToken();

				if(Es_expresion())
				{
					Expr *ep = expr();	
					inherit->Parametros.push_back(ep);

					while(token.getTipo() == TokenType::SIGN_COMA)
					{
						token = lex->NextToken();
						Expr *ep = expr();	
						inherit->Parametros.push_back(ep);
					}
				}
			}
			else
				throw PythonError("METHODCALL2","Se esperaba (");

			if(token.getTipo() == TokenType::SIGNO_PARENTESIS_DER)
			{
				token = lex->NextToken();
			}
			else
			{
				throw PythonError("METHODCALL2","Se Esperaba )");
			}

			return inherit;
		}catch (char* e)
        {
			throw PythonError("METHODCALL2",e);
        }
	}

	Expr* lvalue(IDExpr *inherit)
	{
		try
		{
			if(token.getTipo() == TokenType::SIGNO_BRACKET_IZQ)
			{
				Expr *idx = NULL;

				token = lex->NextToken();

				if(Es_expresion())
				{
					idx = expr();
				}else
				{
					throw PythonError("lvalue","Se Esperaba Una Expresion");
				}

				if(token.getTipo() == TokenType::SIGNO_BRACKET_DER)
				{
					token = lex->NextToken();
				}else
				{
					throw PythonError("lvalue","Se Esperaba [ o ]");
				}

				return new ArrayExpr(inherit->varname, idx);
			}
			else
			{
				return inherit;
			}
		}catch (char* e)
        {
			throw PythonError("lvalue",e);
        }
	}

	Expr* expr()
	{
		try
		{
			if(Es_expresion())
			{
				if(token.getTipo() == TokenType::ID /*|| token.getTipo() == TokenType::KW_PRINT || token.getTipo() == TokenType::KW_READ*/
					|| token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ || token.getTipo() == TokenType::LIT_CADENA 
					|| Numero() || Boolean())
				{
					return Relacional();
				}

				#pragma region - <expr> & ~ <expr>
				else if(token.getTipo() == TokenType::OP_REST || token.getTipo() == TokenType::OP_NEGACION)
				{
					if(token.getTipo() == TokenType::OP_REST)
					{
						token = lex->NextToken();
						return new NegateExpr(expr());

					}else if(token.getTipo() == TokenType::OP_NEGACION)
					{
						token = lex->NextToken();
						return new InvertExpr(expr());
					}
				}
				#pragma endregion
			}else
			{
				throw PythonError("expr","Se Esperaba Expresion");
			}
		}catch (char* e)
        {
			throw PythonError("expr",e);
        }
	}

	Expr* Relacional()
	{
		try
		{

			Expr* aritmeticosumaresta1 = ArithmeticoSumaResta();

			while(OperadorRel())
			{
				switch(token.Tipo)
				{
					case TokenType::OP_MENOR:
						token = lex->NextToken();
						aritmeticosumaresta1 = new MenorExpr(aritmeticosumaresta1,ArithmeticoSumaResta());
						break;
					case TokenType::OP_MENOR_IGUAL:
						token = lex->NextToken();
						aritmeticosumaresta1 = new MenorIgualExpr(aritmeticosumaresta1,ArithmeticoSumaResta());
						break;
					case TokenType::OP_MAYOR:
						token = lex->NextToken();
						aritmeticosumaresta1 = new MayorExpr(aritmeticosumaresta1,ArithmeticoSumaResta());
						break;
					case TokenType::OP_MAYOR_IGUAL:
						token = lex->NextToken();
						aritmeticosumaresta1 = new MayorIgualExpr(aritmeticosumaresta1,ArithmeticoSumaResta());
						break;
					case TokenType::OP_DISTINTO_DE:
						token = lex->NextToken();
						aritmeticosumaresta1 = new DistintoExpr(aritmeticosumaresta1,ArithmeticoSumaResta());
						break;
					case TokenType::OP_IGUAL_IGUAL:
						token = lex->NextToken();
						aritmeticosumaresta1 = new IgualExpr(aritmeticosumaresta1,ArithmeticoSumaResta());
						break;

					default:
						continue;
				}
			}

			return aritmeticosumaresta1;

		}catch(char* e)
        {
			throw PythonError("Relacional",e);
         }
	}

	Expr* ArithmeticoSumaResta()
	{
		try
		{
			Expr* produccion1 = Produccion();

			while(token.getTipo() == TokenType::OP_OR || token.getTipo() == TokenType::OP_REST || token.getTipo() == TokenType::OP_SUM)
			{
				switch(token.Tipo)
				{
				case TokenType::OP_OR:
					token = lex->NextToken();
					produccion1 = new OrExpr(produccion1,Produccion());
					break;

				case TokenType::OP_REST:
					token = lex->NextToken();
					produccion1 = new RestaExpr(produccion1,Produccion());
					break;

				case TokenType::OP_SUM:
					token = lex->NextToken();
					produccion1 = new SumaExpr(produccion1,Produccion());
					break;

				default:
						continue;
				}

			}

			return produccion1;

		}catch(char* e)
        {
			throw PythonError("ArithmeticoSumaResta",e);
         }
	}

	Expr* Produccion()
	{
		try
		{
			Expr *shift1 = Shift();

			while(token.getTipo() == TokenType::OP_DIV || token.getTipo() == TokenType::OP_MULT || token.getTipo() == TokenType::OP_MOD
				|| token.getTipo() == TokenType::OP_AND)
			{
				switch(token.Tipo)
				{
				case TokenType::OP_DIV:
					token = lex->NextToken();
					shift1 = new DivisionExpr(shift1,Shift());
					break;

				case TokenType::OP_MULT:
					token = lex->NextToken();
					shift1 = new MultiplicacionExpr(shift1,Shift());
					break;

				case TokenType::OP_MOD:
					token = lex->NextToken();
					shift1 = new ModExpr(shift1,Shift());
					break;

				case TokenType::OP_AND:
					token = lex->NextToken();
					shift1 = new AndExpr(shift1,Shift());
					break;

				default:
						continue;
				}
			}

			return shift1;
		}catch(char* e)
        {
			throw PythonError("Produccion",e);
        }
	}

	Expr* Shift()
	{
		try
		{
			Expr *term1 = Term();

			while(token.getTipo() == TokenType::OP_SLEFT || token.getTipo() == TokenType::OP_SRIGHT)
			{
				if(token.getTipo() == TokenType::OP_SLEFT)
				{
					token = lex->NextToken();
					term1 = new ShiftLeftExpr(term1,Term());

				}else if(token.getTipo() == TokenType::OP_SRIGHT)
				{
					token = lex->NextToken();
					term1 = new ShiftRightExpr(term1,Term());
				}
				
			}

			return term1;

		}catch(char* e)
        {
			throw PythonError("Produccion",e);
        }
	}

	Expr* Term()
	{
		try
		{
			if(Numero() || Boolean() || token.getTipo() == TokenType::LIT_CADENA)
			{
				return constant();
			
			}else if(token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ)
			{
				token = lex->NextToken();
				Expr *termino = expr();

				if(token.getTipo() == TokenType::SIGNO_PARENTESIS_DER)
				{
					token = lex->NextToken();
				}else 
				{
					throw PythonError("term","Se Esperaba )");
				}

				return termino;

			}else if(token.getTipo() == TokenType::ID)
			{
				IDExpr *id = new IDExpr(token.lexema);
				return exprP(id);
			}else
				PythonError("Term","Se Esperaba Termino");

		}catch(char* e)
        {
			throw PythonError("Term",e);
        }
	}

	Expr* exprP(IDExpr *inherit)
	{
		try
		{
				token = lex->NextToken();
			
				if(token.getTipo() == TokenType::SIGNO_BRACKET_IZQ)
				{
					ArrayExpr *arreglo = new ArrayExpr(inherit->varname,expr());
					//expr();

					if(token.getTipo() == TokenType::SIGNO_BRACKET_DER)
					{
						token = lex->NextToken();
					}else 
					{
						throw PythonError("exprP","Se Esperaba ]");
					}

					return arreglo;

				}else if(token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ)
				{
					MethodCallExpr *methodcall = new MethodCallExpr(inherit->varname);

					return methodcall2(methodcall);

				}else
					return inherit;

				/*else if(token.getTipo() == TokenType::KW_PRINT || token.getTipo() == TokenType::KW_READ)
				{
					methodcall();
				}*/

		}catch (char* e)
        {
			throw PythonError("exprP",e);
        }
	}

	void InicioBloque()
	{
		try
		{
			if(token.getTipo() == TokenType::OP_IDENT)
			{
				token = lex->NextToken();
			}else
				throw PythonError("InicioBloque","Se Esperaba Inicio de Bloque");
		}catch (char* e)
        {
			throw PythonError("InicioBloque",e);
         }
	}

	void FinBloque()
	{
		try
		{
			if(token.getTipo() == TokenType::OP_DEDENT)
			{
				token = lex->NextToken();
			}else
				throw PythonError("FinBloque","Se Esperaba Fin de Bloque");
		}catch (char* e)
        {
			throw PythonError("FinBloque",e);
         }
	}
	
	void range(ForStatement *inherit)
	{
		try
		{
			Expr *init = expr();

			if(token.getTipo() == TokenType::OP_RANGO)
			{
				token = lex->NextToken();
				Expr *end = expr();

				inherit->exprInicial = init;
				inherit->exprFinal = end;
			}else 
				throw PythonError("range","Se esperaba ...");

		}catch (char* e)
        {
			throw PythonError("range",e);
         }
	}

	Expr* constant()
	{
		try
		{
			if(Numero())
			{
				token = lex->NextToken();
				return new NumExpr();

			}else if(Boolean())
			{
				return bool_const();

			}else if(token.getTipo() == TokenType::LIT_CADENA || token.getTipo() == TokenType::ID)
			{
				token = lex->NextToken();
				return new CharExpr();
			}
			
		}catch (char* e)
        {
			throw PythonError("constant",e);
         }
	}

	Expr* bool_const()
	{
		try
		{
			if(Boolean())
			{
				token = lex->NextToken();
			}
			return new BooleanExpr();
		}catch (char* e)
        {
			throw PythonError("bool_const",e);
         }
	}
};

#endif