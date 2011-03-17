//----------------------------------------------------------------------------
// Non-standard Library v 0.6
// Copyright (C) 2008 Alexey Lukyanchikov
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
// Contact: alexey.lukyanchikov@gmail.com
//----------------------------------------------------------------------------
#pragma once
namespace NSD{
	struct Exception
	{
		virtual const char* textMessage() const {return 0;}
		virtual ~Exception(){}
	};
	class Bad_Alloc: public Exception{};
	class Out_Of_Range: public Exception{};

	struct EInvalidIterator
	{
		virtual const char* textMessage() const {return 0;}
		virtual ~EInvalidIterator(){}
	};
}
