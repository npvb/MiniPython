#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

enum TokenType{
		ID,

		//OPERADORES MATEMATICOS
		OP_SUM,OP_REST,OP_MULT,OP_DIV,OP_MOD,
		
		//OPERADORES a NIVEL DE BITS
		OP_SLEFT,OP_SRIGHT,OP_NEGACION,

		//OPERADORES LOGICOS
		OP_MENOR,OP_MAYOR,OP_MAYOR_IGUAL,OP_MENOR_IGUAL,OP_IGUAL_IGUAL,
		OP_DISTINTO_DE,OP_AND,OP_OR,OP_NOT,

		//LITERALES
		LIT_NUM_INT,LIT_NUM_FLOAT,LIT_CADENA,LIT_TRUE,LIT_FALSE,

		//OPERADORES DE PUNTUACION
		SIGN_DOSPUNTOS,SIGN_COMA,SIGNO_BRACKET_IZQ,SIGNO_BRACKET_DER,
		SIGNO_PARENTESIS_IZQ,SIGNO_PARENTESIS_DER,OP_RANGO,OP_ASIG,
		OP_NEWLINE,OP_IDENT,OP_DEDENT,

		//PALABRAS RESERVADAS
		KW_CLASS,KW_DEF,KW_IF,KW_ELIF,KW_ELSE,KW_WHILE,KW_FOR,
		KW_IN,KW_RETURN,KW_BREAK,KW_PRINT,KW_READ,
		
		EOFF

	};

class Token
{

public:
	string lexema;
	TokenType Tipo;
	int fila;
	int columna;

	Token(){}

	Token(string lex,TokenType tip,int fil,int col)
	{
		lexema = lex;
		Tipo = tip;
		fila = fil;
		columna = col;
	}
	
	TokenType getTipo()
	{
		return Tipo;
	}

};