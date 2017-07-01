// @file ByteBuffer.h
// Copyright 2016-2017 John Jackson. All Rights Reserved.

#pragma once
#ifndef ENJON_BYTE_BUFFER_H
#define ENJON_BYTE_BUFFER_H

#include "System/Types.h"
#include "Defines.h"

#define ENJON_BYTE_BUFFER_DEFAULT_CAPACITY	1024

namespace Enjon
{
	class ByteBuffer
	{
		public:
			/*
			* @brief Constructor
			*/
			ByteBuffer( );
			
			/*
			* @brief Destructor
			*/
			~ByteBuffer( );

			/*
			* @brief
			*/
			void ReadFromFile( const Enjon::String& filePath );
			
			/*
			* @brief
			*/
			void WriteToFile( const Enjon::String& filePath );

			/*
			* @brief
			*/
			template <typename T>
			T Read( ); 

			/*
			* @brief
			*/
			template < typename T >
			void Write( const T& val );

			/*
			* @brief
			*/
			const u32 GetSize( ) const;

		private:
			/*
			* @brief Destructor
			*/
			void Resize( usize size );

		private:
			u32 mReadPosition	= 0;
			u32 mWritePosition	= 0;
			u32 mSize			= 0;
			u32 mCapacity		= ENJON_BYTE_BUFFER_DEFAULT_CAPACITY;
			u8* mBuffer			= nullptr;
	};
}

#endif