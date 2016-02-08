//!
//! (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpnicore.
//!
//! libpnicore is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpnicore is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//! Created on: Feb 8, 2016
//!     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#pragma once

#ifdef MSVC
	#ifdef DLL_BUILD
		#define PNICORE_EXPORT __declspec(dllexport)
	#else
		#define PNICORE_EXPORT __declspec(dllimport)
	#endif
#else 
	#define PNICORE_EXPORT
#endif

