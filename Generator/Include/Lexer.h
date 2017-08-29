#pragma once
#ifndef GENERATOR_LEXER_H
#define GENERATOR_LEXER_H

#include "Token.h"
#include "Utils.h"

class Lexer
{
	public:

		Lexer( );

		Lexer( const std::string& contents );

		~Lexer( ); 

		void EatAllWhiteSpace( ); 

		Token GetNextToken( ); 

		bool RequireToken( TokenType type, bool advance = false );

		Token GetCurrentToken( );

		void SetContents( const std::string& newContents, const std::string& contentsPath = "" );

		std::string GetContentsPath( ) const { return mContentsPath; }

		void ContinueTo( TokenType type );
	
	public: 
		char* mAt = nullptr;

	private:	
		std::string mContentsString;
		std::string mContentsPath;
		char* mContents = nullptr;
		Token mCurrentToken;
};

#endif
