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

		if(par.token.getTipo() == TokenType::EOFF)
		{
			cout<<"Compilacion Exitosa!!"<<endl;
		}

	}catch(exception err){
		cout<<err.what()<<endl;
	}

	system("pause");
	return 0;
}