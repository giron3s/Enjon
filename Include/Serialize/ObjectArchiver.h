// Copyright 2016-2017 John Jackson. All Rights Reserved.
// File: ObjectArchiver.h

#pragma once 
#ifndef ENJON_OBJECT_ARCHIVER_H
#define ENJON_OBJECT_ARCHIVER_H 

#include "Base/Object.h"
#include "Serialize/ByteBuffer.h"

namespace Enjon
{
	class ObjectArchiver
	{ 
		public:

			/*
			* @brief
			*/
			ObjectArchiver( );

			/*
			* @brief
			*/
			~ObjectArchiver( );

			/*
			* @brief
			*/
			Result Serialize( const Object* object ); 

			/*
			* @brief
			*/
			Result Deserialize( const String& filePath, Vector< Object* >& out );

			/*
			* @brief
			*/
			Object* Deserialize( const String& filePath );

			/*
			* @brief
			*/
			Result Deserialize( const String& filePath, HashMap< const MetaClass*, Object* >& out );

			/*
			*@brief
			*/
			Result WriteToFile( const String& filePath );

			/*
			* @brief
			* @note Not a huge fun of this being exposed. Otherwise, why not just use a simple byte buffer?
			*/
			template <typename T>
			void WriteToBuffer( const T& value )
			{
				mBuffer.Write< T >( value ); 
			} 

			/*
			* @brief
			* @note Not a huge fun of this being exposed. Otherwise, why not just use a simple byte buffer?
			*/
			template <typename T>
			T ReadFromBuffer( )
			{
				return mBuffer.Read< T >( ); 
			} 

		private:

			/*
			*@brief
			*/ 
			void Reset( );

			/*
			*@brief
			*/ 
			Result SerializeObjectDataDefault( const Object* object, const MetaClass* cls );

			/*
			*@brief
			*/ 
			Result DeserializeObjectDataDefault( const Object* object, const MetaClass* cls );

		private:
			ByteBuffer mBuffer;
	};
	
}

#endif