#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include "Parser.h"

using namespace std;

int main()
{
	try{

		Parser par(new Lexer("PruebaPython.txt"));

		while(par.token.getTipo() != TokenType::EOFF)
		{
			par.program();
		}



	/*	Lexer lx("PruebaPython.txt");
		Token t;

		while(t.Tipo!=TokenType::EOFF)
		{
			t = lx.NextToken();
			cout<<"Lexema: "<<t.lexema;
			cout<<" Tipo: "<<t.Tipo<<endl;
			
		}*/

	}catch(exception err){
		cout<<err.what()<<endl;
	}

	//cout<<"Compilacion Exitosa!"<<endl;

	system("pause");
	return 0;
}