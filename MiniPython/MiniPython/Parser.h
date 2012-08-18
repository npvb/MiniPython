#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <string>
#include "Lexer.h"

using namespace std;

class Parser
{
public:

	Lexer *lex;
	Token token;

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
		if(token.getTipo() == TokenType::LIT_FALSE || token.getTipo() == TokenType::LIT_TRUE)
		{
			return true;
		}else
			return false;
	}

	bool Es_expresion()
	{
		switch(token.Tipo)
		{
		case TokenType::ID:
		case TokenType::LIT_NUM_FLOAT:
		case TokenType::LIT_NUM_INT:
		case TokenType::LIT_TRUE:
		case TokenType::LIT_FALSE:
		case TokenType::OP_MENOR:
		case TokenType::OP_MENOR_IGUAL:
		case TokenType::OP_NEGACION:
		case TokenType::SIGNO_PARENTESIS_IZQ:
		case TokenType::SIGNO_BRACKET_IZQ:
			/*No se si deba incluir lo de op_bin en Es_expr*/
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
			return true;

		default:
			return false;
		}
	}

	Parser(Lexer *l)
	{
		lex = l;
		token = Token();
	}

	void program()
	{
		try
		{
			token = lex->NextToken();
			if(token.getTipo() == TokenType::KW_CLASS)
			{
				token = lex->NextToken();
			if(token.getTipo() == TokenType::ID)
			{
				token = lex->NextToken();
			if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
			{
				token = lex->NextToken();

				if(token.getTipo() == TokenType::OP_IDENT)
				{
					token = lex->NextToken();
				}

				while(token.getTipo() == TokenType::ID)
				{
					field_decl();
				}

				while(token.getTipo() == TokenType::KW_DEF)
				{
					method_decl();
				}
						
		}else
		{
			throw exception("program-> Se Esperaba : despues del Nombre de la Clase");
		}
		}else 
		{
				throw exception ("program-> Se Esperaba Nombre de la Clase");
		}
		}else
		{
				throw exception ("program-> Se Esperaba la palabra Class al Inicio del Programa");
		}
			
	}catch (char* e)
        {
			string error = "program: ";
			throw exception(error.append(e).c_str());
         }
	}

	void field_decl()
	{
		try
		{
			assign();

		}catch (char* e)
        {
			string error = "field_decl: ";
			throw exception(error.append(e).c_str());
         }
	}

	void method_decl()
	{
		try
		{
			token = lex->NextToken();

			if(token.getTipo() == TokenType::ID)
			{
				token = lex->NextToken();

			if(token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ)
			{
				token = lex->NextToken();
		/*Parte Opcional*/
			if(token.getTipo() == TokenType::ID)
			{
				token = lex->NextToken();
					while(token.getTipo() == TokenType::SIGN_COMA)
					{
							token = lex->NextToken();

						if(token.getTipo() == TokenType::ID)
						{
							token = lex->NextToken();
						}else 
						{
							throw exception("Se Esperaba un ID despues de la coma");
			
						}
					}
			if(token.getTipo() == TokenType::SIGNO_PARENTESIS_DER)
			{
				token = lex->NextToken();

			}if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
			{
				token = lex->NextToken();
				block();
			}

			}
			}else if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
			{
				token = lex->NextToken();
				block();
			}
		}
			
		}catch (char* e)
		{
			string error = "method_decl: ";
			throw exception(error.append(e).c_str());
		}
}

	void block()
	{
		try
		{
			InicioBloque();

			while(isStatement())
			{
				statement();

			}
				
			FinBloque();
			
		}catch (char* e)
        {
			string error = "block: ";
			throw exception(error.append(e).c_str());
         }
	}

	void statement()
	{
		try
		{
			#pragma region Assign | MethodCall
			if(token.getTipo() == TokenType::ID)
			{
				Statementp();

			}else if(token.getTipo() == TokenType::KW_READ || token.getTipo() == TokenType::KW_PRINT)
			{
				methodcall();
			}
			#pragma endregion 
	
			#pragma region IF_STATEMENT

			else if(token.getTipo() == TokenType::KW_IF)
				{
					token = lex->NextToken();
					expr();
					//token = lex->NextToken();

					if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
					{
						block();
						token = lex->NextToken();

						while(token.getTipo() == TokenType::KW_ELIF)
						{
							expr();
							token = lex->NextToken();

							if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
							{
								block();

							}else 
							{
								throw exception ("IF-> Se Esperaban : al final de la Expresion");
							}
						}

						if(token.getTipo() == TokenType::KW_ELSE)
						{
							token = lex->NextToken();

							if(token.getTipo() ==TokenType::SIGN_DOSPUNTOS)
							{
								block();
							}else 
							{
								throw exception("IF-> Se Esperaba : Luego del Else");
							}
						}

					}else 
					{
						throw exception("IF-> Se Esperaba : Luego de la Expresion");
					}
					#pragma endregion

			#pragma region WHILE_STATEMENT
				}else if(token.getTipo() == TokenType::KW_WHILE)
				{
					expr();

					token = lex->NextToken();

					if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
					{
						block();
					}else 
					{
						throw exception("While: Se Esperaba : Luego de Expr");
					}
				#pragma endregion 
					
			#pragma region FOR_STATEMENT
				}else if(token.getTipo() == TokenType::KW_FOR)
				{
					token = lex->NextToken();

					if(token.getTipo() == TokenType::ID)
					{
						token = lex->NextToken();

						if(token.getTipo() == TokenType::KW_IN)
						{
							range();

							if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
							{
									block();
							}else
							{ 
								throw exception("FOR: Se Esperaba : luego del Rango");
							}

						}else 
						{
							throw exception("FOR:Se Esperaba Palabra Reservada in");
						}
					}else
					{
						throw exception("FOR: Se Esperaba un ID");
					}

				#pragma endregion

			#pragma region RETURN_STATEMENT
				}else if(token.getTipo() == TokenType::KW_RETURN)
				{
					expr();
				
			#pragma endregion
			
			#pragma region BREAK_STATEMENT
				}else if(token.getTipo() == TokenType::KW_BREAK)
				{
					token = lex->NextToken();
				}
			#pragma endregion


		}catch (char* e)
        {
			string error = "statement: ";
			throw exception(error.append(e).c_str());
         }
	}

	void Statementp()
	{
		try{
			if(token.getTipo() == TokenType::ID)
			{
				token = lex->NextToken();

				if(token.getTipo() == TokenType::OP_ASIG || token.getTipo() == TokenType::SIGNO_BRACKET_IZQ)
				{
					assignP();

				}else if(token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ)
				{
					methodcall2();

					}else if(token.getTipo() == TokenType::KW_PRINT || token.getTipo() == TokenType::KW_READ)
					{
						methodcall();
					}
			}
		}catch(char* e)
        {
			string error = "Statementp: ";
			throw exception(error.append(e).c_str());
         }
	}

	void assign()
	{
		try
		{
			lvalue();

			if(token.getTipo()  == TokenType::OP_ASIG)
			{
				token = lex->NextToken();
				expr();
			}else
			{
				throw exception("ASSIGN-> Se Esperaba Operador de Asignacion");
			}

			//token = lex->NextToken();
			
		}catch (char* e)
        {
			string error = "assign: ";
			throw exception(error.append(e).c_str());
         }
	}

	void assignP()
	{
		try
		{
		
			if(token.getTipo() == TokenType::SIGNO_BRACKET_IZQ)
			{
				expr();

				if(token.getTipo()==TokenType::SIGNO_BRACKET_DER)
				{
					token = lex->NextToken();

					if(token.getTipo() == TokenType::OP_ASIG)
					{
						expr();
					}else
					{
						throw exception("assignP-> Se Esperaba =");
					}
				}else
				{
					throw exception ("assignP-> Se Esperaba ]");
				}
			}

			if(token.getTipo()  == TokenType::OP_ASIG)
			{
				expr();
			}else
			{
				throw exception("ASSIGN-> Se Esperaba Operador de Asignacion");
			}

			token = lex->NextToken();
			
		}catch (char* e)
        {
			string error = "assignP: ";
			throw exception(error.append(e).c_str());
         }
	}

	void methodcall()
	{
		try
		{
			#pragma region ID_METHODCALL
			if(token.getTipo() == TokenType::ID)
			{
				token = lex->NextToken();

				if(token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ)
				{
					token = lex->NextToken();

					while(Es_expresion())
					{
						expr();

						if(token.getTipo() == TokenType::SIGN_COMA)
						{
							token = lex->NextToken();
						}else
						{
							throw exception("METHODCALL -> Se Esperaba una coma luego de la expresion");
						}

					}
					token = lex->NextToken();
					if(token.getTipo() == TokenType::SIGNO_PARENTESIS_DER)
					{
						token = lex->NextToken();

					}else{
						throw exception("METHODCALL -> Se Esperaba Cierre de Parentesis");
					}
				}
			#pragma endregion 

			#pragma region PRINT_METHODCALL	
			}else if(token.getTipo() == TokenType::KW_PRINT) 
			{
				token = lex->NextToken();
				if(token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ)
				{
					while(Es_expresion())
					{
						expr();

						if(token.getTipo() == TokenType::SIGN_COMA)
						{
							token = lex->NextToken();
						}else
						{
							throw exception("PRINT-> Se Esperaba una coma luego de la expresion");
						}

					}
				}
			#pragma endregion

			#pragma region READ_METHODCALL
			}else if(token.getTipo() == TokenType::KW_READ)
			{
				lvalue();
			}
			#pragma endregion

		}catch (char* e)
        {
			string error = "methodcall: ";
			throw exception(error.append(e).c_str());
         }
	}

	void methodcall2()
	{
		try
		{
			if(token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ)
			{
					token = lex->NextToken();

					if(Es_expresion()){
						expr();	

							while(token.getTipo() == TokenType::SIGN_COMA)
							{
								token = lex->NextToken();
								expr();
							}
							//token = lex->NextToken();
				}
			}else
				throw exception("Se esperaba (");

			if(token.getTipo() == TokenType::SIGNO_PARENTESIS_DER)
			{
				token = lex->NextToken();

			}else{
				throw exception("METHODCALL2 -> Se Esperaba Cierre de Parentesis");
			}

		}catch (char* e)
        {
			string error = "methodcall2: ";
			throw exception(error.append(e).c_str());
         }
	}

	void lvalue()
	{
		try
		{
			if(token.getTipo() == TokenType::ID)
			{
				token = lex->NextToken();
					if(token.getTipo() == TokenType::SIGNO_BRACKET_IZQ)
					{
						expr();
						if(token.getTipo() == TokenType::SIGNO_BRACKET_DER)
						{
							token = lex->NextToken();
						}else
						{
							throw exception("lvalue-> Se Esperaba Cierre de Bracket");
						}
					}
			}else
			{
				throw exception("lvalue-> Se Esperaba un ID");
			}
			
		}catch (char* e)
        {
			string error = "lvalue: ";
			throw exception(error.append(e).c_str());
         }
	}

	void expr()
	{
		try
		{
			#pragma region LVALUE | METHODCALL
			if(token.getTipo() == TokenType::ID)
			{
				exprP();

			}else if(token.getTipo() == TokenType::KW_READ || token.getTipo() == TokenType::KW_PRINT)
			{
				methodcall();
			#pragma endregion

			#pragma region CONSTANT & EXPR <OP_BIN> EXPR
			}
			if (Numero() || Boolean() /*¿¿charconstant??*/)
			{
				constant();

			}
			if(Es_expresion())
			{/*¿No se donde debo consumir el token?*/
				//expr();
				op_bin();
				expr();
			#pragma endregion

			#pragma region - <expr> & ~ <expr>
			}else if(token.getTipo() == TokenType::OP_REST || token.getTipo() == TokenType::OP_NEGACION)
			{
				expr();
			#pragma endregion

			#pragma region ( <expr> )
			}else if(token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ)
			{
				token = lex->NextToken();

				expr();

				if(token.getTipo() == TokenType::SIGNO_PARENTESIS_DER)
				{
					token = lex->NextToken();
				}else 
				{
					throw exception("expr-> Se Esperaba )");
				}
			#pragma endregion

			#pragma region [ <expr> ]		
			}
			if(token.getTipo() == TokenType::SIGNO_BRACKET_IZQ)
			{
				token = lex->NextToken();
				expr();

				while(token.getTipo() == TokenType::SIGN_COMA)
				{
					token = lex->NextToken();
					expr();
				}

				if(token.getTipo() == TokenType::SIGNO_BRACKET_DER)
				{
					token = lex->NextToken();
				}else
					throw exception ("expr-> Se Esperaba ]");	
	
			}
			#pragma endregion

		}catch (char* e)
        {
			string error = "expr: ";
			throw exception(error.append(e).c_str());
         }
	}

	void exprP()
	{
		try
		{
			if(token.getTipo() == TokenType::ID)
			{
				token = lex->NextToken();

				if(token.getTipo() == TokenType::SIGNO_BRACKET_IZQ)
				{
					expr();

					if(token.getTipo() == TokenType::SIGNO_BRACKET_DER)
					{
						token = lex->NextToken();
					}else 
					{
						throw exception("exprP-> Se Esperaba ]");
					}

				}else if(token.getTipo() == TokenType::SIGNO_PARENTESIS_IZQ)
				{
					methodcall2();

					}else if(token.getTipo() == TokenType::KW_PRINT || token.getTipo() == TokenType::KW_READ)
					{
						methodcall();
					}
			}

		}catch (char* e)
        {
			string error = "exprP: ";
			throw exception(error.append(e).c_str());
         }
	}

	void InicioBloque()
	{
		try
		{
			if(token.getTipo() == TokenType::OP_IDENT)
			{
				token = lex->NextToken();
			}
		}catch (char* e)
        {
			string error = "InicioBloque: ";
			throw exception(error.append(e).c_str());
         }
	}

	void FinBloque()
	{
		try
		{
			if(token.getTipo() == TokenType::OP_DEDENT)
			{
				token = lex->NextToken();
			}
		}catch (char* e)
        {
			string error = "FinBloque: ";
			throw exception(error.append(e).c_str());
         }
	}
	
	void range()
	{
		try
		{
			expr();

			token = lex->NextToken();

			if(token.getTipo() == TokenType::OP_RANGO)
			{
				expr();

			}else 
				throw exception("range-> Se esperaba ...");
		}catch (char* e)
        {
			string error = "range: ";
			throw exception(error.append(e).c_str());
         }
	}

	void op_bin()
	{
		try
		{
			if(OperadorMat())
			{
				arith_op();

			}else if(OperadorRel())
			{
				rel_op();

			}else if(OperadorEq())
			{
				eq_op();

			}else if(OperadorCon())
			{
				cond_op();
			}
			
		}catch (char* e)
        {
			string error = "op_bin: ";
			throw exception(error.append(e).c_str());
         }
	}

	void arith_op()
	{
		try
		{
			if(OperadorMat())
			{
				token = lex->NextToken();
			}else
				throw exception("arith_op-> Se Esperaba Operador Matematico");

		}catch (char* e)
        {
			string error = "arith_op: ";
			throw exception(error.append(e).c_str());
         }
	}

	void rel_op()
	{
		try
		{
			if(OperadorRel())
			{
				token = lex->NextToken();
			}else
				throw exception("rel_op-> Se Esperaba Operador Relacional");

		}catch (char* e)
        {
			string error = "rel_op: ";
			throw exception(error.append(e).c_str());
         }
	}

	void eq_op()
	{
		try
		{
			if(OperadorEq())
			{
				token = lex->NextToken();
			}else
				throw exception("eq_op-> Se Esperaba != o ==");

		}catch (char* e)
        {
			string error = "eq_op: ";
			throw exception(error.append(e).c_str());
         }
	}
	
	void cond_op()
	{
		try
		{
			if(OperadorCon())
			{
				token = lex->NextToken();
			}else
				throw exception("cond_op-> Se Esperaba La Palabra AND OR o NOT");

		}catch (char* e)
        {
			string error = "cond_op: ";
			throw exception(error.append(e).c_str());
         }
	}

	void constant()
	{
		try
		{
			if(Numero())
			{
				token = lex->NextToken();

			}else if(Boolean())
			{
				bool_const();

			}/*¿¿CHARCONSTANT*/
			
		}catch (char* e)
        {
			string error = "constant: ";
			throw exception(error.append(e).c_str());
         }
	}

	void bool_const()
	{
		try
		{
			if(Boolean())
			{
				token = lex->NextToken();
			}

		}catch (char* e)
        {
			string error = "range: ";
			throw exception(error.append(e).c_str());
         }
	}
};
