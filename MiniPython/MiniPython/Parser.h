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
			throw exception("Se Esperaba : despues del Nombre de la Clase");
		}
		}else 
		{
				throw exception ("Se Esperaba Nombre de la Clase");
		}
		}else
		{
				throw exception ("Se Esperaba la palabra Class al Inicio del Programa");
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
			}else 
			{
				throw exception("Falta Cierre de Parentesis");
			}
			if(token.getTipo() == TokenType::SIGN_DOSPUNTOS)
			{
				block();
			}

			}
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

			while(token.getTipo() == TokenType::KW_IF  || token.getTipo() == TokenType::KW_WHILE || token.getTipo() == TokenType::KW_FOR
				|| token.getTipo() == TokenType::KW_RETURN || token.getTipo() == TokenType::KW_BREAK)
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
			/*TODO: evaluar assign y method call*/
			
			#pragma region IF_STATEMENT

				if(token.getTipo() == TokenType::KW_IF)
				{
					expr();
					token = lex->NextToken();

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
								throw exception ("Se Esperaban : al final de la Expresion");
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
								throw exception("Se Esperaba : Luego del Else");
							}
						}else 
						{
							throw exception("Se Esperaba un Else Luego del IF");
						}

					}else 
					{
						throw exception("Se Esperaba : Luego de la Expresion");
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
							throw exception("Se Esperaba Palabra Reservada in");
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

	void assign()
	{
		try
		{
			lvalue();

			if(token.getTipo()  == TokenType::OP_ASIG)
			{
				expr();
			}else
			{
				throw exception("Se Esperaba Operador de Asignacion");
			}

			token = lex->NextToken();
			
		}catch (char* e)
        {
			string error = "assign: ";
			throw exception(error.append(e).c_str());
         }
	}

	void methodcall()
	{
		try
		{
			
		}catch (char* e)
        {
			string error = "methodcall: ";
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
						}else{/*error*/}
					}
			}else
			{
				throw exception("Se Esperaba un ID");
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
			
		}catch (char* e)
        {
			string error = "expr: ";
			throw exception(error.append(e).c_str());
         }
	}

	void InicioBloque()
	{
		try
		{
			
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
			
		}catch (char* e)
        {
			string error = "range: ";
			throw exception(error.append(e).c_str());
         }
	}

	
};