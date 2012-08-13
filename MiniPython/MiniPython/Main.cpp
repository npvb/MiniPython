#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include "Lexer.h"

using namespace std;

int main()
{
	try{
		Lexer lx("PruebaLexer.txt");
		Token t;

		while(t.Tipo!=TokenType::EOFF)
		{
			t = lx.NextToken();
			cout<<"Lexema: "<<t.lexema;
			cout<<" Tipo: "<<t.Tipo<<endl;
			
		}

	}catch(exception err){
		cout<<err.what()<<endl;
	}

	system("pause");
	return 0;
}