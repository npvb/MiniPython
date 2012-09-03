#include "Token.h"
#include <map>
#include <sstream>
#include <iostream>
#include <ctype.h>
#include <vector>

extern int fila;
class Lexer
{
public:
	long size_archivo;
	long posicion;
	int nivelIdentacion;
	int columna;
	int estado;
	FILE *pFile;
	char simbolo;
	vector<int>Pila_Identacion;
	map<string,TokenType> MapOperadores;
	map<string,TokenType> MapPalabrasReservadas;

	Lexer(){}

	exception PythonError()
	{
		stringstream msg;
		msg << "Caracter "<<simbolo<<" Invalido.\nLinea: "<<fila<<" Columna: "<<columna<<endl;
		throw exception(msg.str().c_str());
	}

	void InitMaps()
	{
		MapOperadores["+"] = TokenType::OP_SUM;
		MapOperadores["-"] = TokenType::OP_REST;
		MapOperadores["*"] = TokenType::OP_MULT;
		MapOperadores["/"] = TokenType::OP_DIV;
		MapOperadores["%"] = TokenType::OP_MOD;
		
		MapOperadores["<<"] = TokenType::OP_SLEFT;
		MapOperadores[">>"] = TokenType::OP_SRIGHT;
		MapOperadores["~"] = TokenType::OP_NEGACION;
		
		MapOperadores[">"] = TokenType::OP_MAYOR;
		MapOperadores["<"] = TokenType::OP_MENOR;
		MapOperadores[">="] = TokenType::OP_MAYOR_IGUAL;
		MapOperadores["<="] = TokenType::OP_MENOR_IGUAL;
		MapOperadores["=="] = TokenType::OP_IGUAL_IGUAL;
		MapOperadores["!="] = TokenType::OP_DISTINTO_DE;
		MapPalabrasReservadas["and"] = TokenType::OP_AND;
		MapPalabrasReservadas["or"] = TokenType::OP_OR;
		MapPalabrasReservadas["not"] = TokenType::OP_NOT;

		MapOperadores[":"] = TokenType::SIGN_DOSPUNTOS;
		MapOperadores[","] = TokenType::SIGN_COMA;
		MapOperadores["]"] = TokenType::SIGNO_BRACKET_DER;
		MapOperadores["["] = TokenType::SIGNO_BRACKET_IZQ;
		MapOperadores[")"] = TokenType::SIGNO_PARENTESIS_DER;
		MapOperadores["("] = TokenType::SIGNO_PARENTESIS_IZQ;
		MapOperadores["="] = TokenType::OP_ASIG;

		MapPalabrasReservadas["class"] = TokenType::KW_CLASS;
		MapPalabrasReservadas["def"] = TokenType::KW_DEF;
		MapPalabrasReservadas["if"] = TokenType::KW_IF;
		MapPalabrasReservadas["elif"] = TokenType::KW_ELIF;
		MapPalabrasReservadas["else"] = TokenType::KW_ELSE;
		MapPalabrasReservadas["while"] = TokenType::KW_WHILE;
		MapPalabrasReservadas["for"] = TokenType::KW_FOR;
		MapPalabrasReservadas["in"] = TokenType::KW_IN;
		MapPalabrasReservadas["return"] = TokenType::KW_RETURN;
		MapPalabrasReservadas["break"] = TokenType::KW_BREAK;
		MapPalabrasReservadas["print"] = TokenType::KW_PRINT;
		MapPalabrasReservadas["read"] = TokenType::KW_READ;
		MapPalabrasReservadas["false"] = TokenType::LIT_FALSE;
		MapPalabrasReservadas["true"] = TokenType::LIT_TRUE;
		
	}

	Lexer(string archivo)
	{
		estado = 0;
		InitMaps();
		posicion = 0;
		fila = 1;
		columna = 1;
		pFile = fopen(archivo.c_str(),"r+");
		fseek (pFile, 0, SEEK_END);
		size_archivo = ftell (pFile);	
		nivelIdentacion = 0;
		Pila_Identacion.push_back(nivelIdentacion);
	
	}

	char NextSymbol()
	{
		try
        {
			columna++;
			char simbolo;
			if(posicion<size_archivo)
			{
				fseek(pFile,posicion,SEEK_SET);
				int caracter = fgetc(pFile);
			    simbolo = (char)caracter;
				posicion++;

				if(simbolo == 10)
				{
					columna = 1;
					fila++;
				}

				return simbolo;

				

			} else {
				
				return '\0';
			}      

		}catch (char* e)
            {
				string error = "Next Symbol";
				throw exception(error.append(e).c_str());
            }
	
	}

	char CurrentSymbol()
	{
		try{
		char simbolo;
			if(posicion<size_archivo)
			{
				fseek(pFile,posicion,SEEK_SET);
				int caracter = fgetc(pFile);
			    simbolo = (char)caracter;
				//posicion++;

				return simbolo;

			} else {
				
				return '\0';
			}      

		}catch (char* e)
        {
			string error = "Current Symbol: ";
			throw exception(error.append(e).c_str());
        }
	}

	bool esOperadorMatematico()
	{
		if(simbolo == '+' || simbolo == '-' || simbolo == '*' || simbolo == '/' || simbolo == '%')
		{
			return true;
		}else
			return false;
	}

	bool esOperadorPuntuacion()
	{
		if(simbolo == ':' || simbolo == ',' || simbolo == '[' || simbolo == ']' || simbolo == '(' || simbolo == ')' || simbolo == '~')
		{
			return true;
		}else
			return false;
	}

	Token NextToken()
	{
		string lexema = "";
		
		while(true){
			simbolo = CurrentSymbol();
			switch (estado)
			{
				#pragma region CASE 0
				case 0:
					if(simbolo == ' ' || simbolo == '\n')
					{
						estado = 0;
						simbolo = NextSymbol();
					}else if(simbolo == '_' || isalpha(simbolo))
					{
						estado = 1;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else if(isdigit(simbolo))
					{
						estado = 2;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else if(simbolo == '\"')
					{
						estado = 5;
					//	lexema+=simbolo;
						simbolo = NextSymbol();

					}else if(esOperadorMatematico())
					{
						estado = 8;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else if(simbolo == '<')
					{
						estado = 9;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else if(simbolo =='>')
					{
						estado = 11;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else if(simbolo == '!')
					{
						estado = 12;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else if(simbolo == '=')
					{
						estado = 13;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else if(esOperadorPuntuacion())
					{
						estado = 14;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else if(simbolo == '.')
					{
						estado = 15;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else if(simbolo == '\t')
					{
						estado = 18;
						nivelIdentacion++;
						simbolo = NextSymbol();

					}else if(simbolo == '\0')
					{
						if(Pila_Identacion.back() == 0)
						{
							return Token("EOFF",TokenType::EOFF,fila,columna);
						}else
						{
							Pila_Identacion.pop_back();
							return Token("DEDENT",TokenType::OP_DEDENT,fila,columna);
						}

					}else
						//throw exception ("Caracter No Valido");
						PythonError();
						break;
				#pragma endregion estado = 0
				
				#pragma region CASE 1
				case 1:
					if(isalpha(simbolo) || simbolo == '_' || isdigit(simbolo))
					{
						estado = 1;
						lexema+=simbolo;
						simbolo = NextSymbol();
					}else if(MapPalabrasReservadas.count(lexema) > 0)
					{
						estado = 0;
						return Token(lexema,MapPalabrasReservadas[lexema],fila,columna);
					}else {
						estado = 0;
						return Token(lexema,TokenType::ID,fila,columna);
					}
					break;
				#pragma endregion ID
                
				#pragma region CASE 2
				case 2:
					if(isdigit(simbolo))
					{
						estado = 2;
						lexema+=simbolo;
						simbolo = NextSymbol();
					}else{
						estado = 0;
						return Token(lexema,TokenType::LIT_NUM_INT,fila,columna);
					}
				break;
				#pragma endregion NumerosINT

				#pragma region CASE 3
				case 3:
					if(isdigit(simbolo))
					{
						estado = 4;
						lexema+=simbolo;
						simbolo = NextSymbol();
					}else if(simbolo == '.')
					{
						estado = 0;
						lexema+=simbolo;
						simbolo = NextSymbol();
						
					}else
						throw exception("Se Esperaba Un Digito");
					break;
				#pragma endregion NumerosFloat

				#pragma region CASE 4
				case 4:
					if(isdigit(simbolo))
					{
						estado = 4;
						lexema+=simbolo;
						simbolo = NextSymbol();
					}else{
						estado = 0;
						return Token(lexema,TokenType::LIT_NUM_FLOAT,fila,columna);
					}
					break;
				#pragma endregion NumerosFloat	

				#pragma region CASE 5
				case 5:
					if(isalpha(simbolo) || isdigit(simbolo) || simbolo == '_')
					{
						estado = 6;
						lexema+=simbolo;
						simbolo = NextSymbol();
					}else
						throw exception ("Caracter Invalido en Literal String");break;
				#pragma endregion STRINGS

				#pragma region CASE 6
				case 6:
					if(isalpha(simbolo) || isdigit(simbolo) || simbolo == '_' || simbolo == ' ')
					{
						estado = 6;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else if(simbolo == '\"')
					{
						estado = 7;
						simbolo = NextSymbol();
					}else
						throw exception ("Caracter Invalido o Falta Cierre del Literal String");
					break;
				#pragma endregion STRINGS

				#pragma region CASE 7
				case 7:
					estado = 0;
					return Token(lexema, TokenType::LIT_CADENA,fila,columna);
				#pragma endregion RETORNO STRINGS

				#pragma region CASE 8
				case 8:
					estado = 0;
					return Token(lexema,MapOperadores[lexema],fila,columna);
				#pragma endregion RETORNO OPS_MATS

				#pragma region CASE 9
				case 9:
					if(simbolo=='<' ||  simbolo=='=')
					{
						estado = 10;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else
					{
						estado = 0;
						return Token(lexema,MapOperadores[lexema],fila,columna);
						
					}
					break;
				#pragma endregion MENOR o MENOR IGUAL

				#pragma region CASE 10
				case 10:
					estado = 0;
					return Token(lexema,MapOperadores[lexema],fila,columna);
				#pragma endregion RETORNO 

				#pragma region CASE 11
				case 11:
				if(simbolo=='>' ||  simbolo=='=')
					{
						estado = 10;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else
					{
						estado = 0;
						return Token(lexema,MapOperadores[lexema],fila,columna);
					}
					break;
				#pragma endregion MAYOR O MAYOR IGUAL

				#pragma region CASE 12
				case 12:
				if(simbolo=='=')
					{
						estado = 10;
						lexema+=simbolo;
						simbolo = NextSymbol();
					}else
					{
						throw exception("Se Esperada Simbolo de = luego del Operador ! ");
					}
					break;
				#pragma endregion DISTINTO DE

				#pragma region CASE 13
				case 13:
					if(simbolo == '=')
					{
						estado = 10;
						lexema+=simbolo;
						simbolo = NextSymbol();
					}else
					{
						estado = 0;
						return Token(lexema,MapOperadores[lexema],fila,columna);
					}
					break;
				#pragma endregion IGUAL

				#pragma region CASE 14
				case 14:
					estado = 0;
					return Token(lexema,MapOperadores[lexema],fila,columna);

				#pragma endregion OPERADORES DE PUNTUACION

				#pragma region CASE 15
				case 15:
					if(simbolo == '.')
					{
						estado = 16;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else 
						throw exception("Se Esperaba Segundo . para Operados de Secuencia (...)");break;

				#pragma endregion OPERADOR ...

				#pragma region CASE 16
				case 16:
					if(simbolo == '.')
					{
						estado = 17;
						lexema+=simbolo;
						simbolo = NextSymbol();

					}else 
						throw exception("Se Esperaba Tercer . para Operados de Secuencia (...)");break;

				#pragma endregion OPERADOR ...

				#pragma region CASE 17
				case 17:
					estado = 0;
					return Token(lexema,TokenType::OP_RANGO,fila,columna);
				#pragma endregion OPERADOR ...

				#pragma region CASE 18
				case 18:
					if(simbolo == '\t')
					{
						estado = 18;
						nivelIdentacion++;
						simbolo = NextSymbol();
					}else 
					{
						if(nivelIdentacion > Pila_Identacion.back())
						{
							Pila_Identacion.push_back(nivelIdentacion);
							nivelIdentacion = 0;
							estado = 0;
							return Token("INDENT",TokenType::OP_IDENT,fila,columna);

						}else if (nivelIdentacion < Pila_Identacion.back())
						{								
							int pos = 0;
							for(int x = 0;x<Pila_Identacion.size();x++)
							{
								if(nivelIdentacion == Pila_Identacion[x])
								{
									pos = x;
									break;
								}
							}
							
							if(pos>0)
							{								
								Pila_Identacion.pop_back();
								return Token("DEDENT", TokenType::OP_DEDENT, fila, columna);

							}else
								
								throw exception("Lexer: Error de Indentacion");
						}else
						{
							/*NOTHING HAPPENS!!*/
							nivelIdentacion = 0;
							estado = 0;
						}

					}
					break;
				#pragma endregion INDENT

			}	
		}
	}
};