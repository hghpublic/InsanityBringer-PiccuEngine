/* 
* Descent 3 
* Copyright (C) 2024 Parallax Software
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef APPDATABASE
#define APPDATABASE

#include "pstypes.h"

/* oeAppDatabase
	to get info about the application from a managed database (or a custom info file)
	Again, this class should be the parent of a platform specific class like osWinDatabase, for instance.
*/

class oeAppDatabase
{
public:
	oeAppDatabase() {};

//	you can also create a reference to a current database.  this is good if
//	you have a hierachical database.   
	oeAppDatabase(oeAppDatabase *parent) {};
	virtual ~oeAppDatabase() {};

//	creates an empty classification or structure where you can store information
	virtual bool create_record(const char *pathname) = 0;

//	set current database focus to a particular record
	virtual bool lookup_record(const char *pathname) = 0;

//	read either an integer or string from the current record
	virtual bool read(const char *label, char *entry, int *entrylen) = 0;
	virtual bool read(const char *label, void *entry,int wordsize) = 0; 	//read an variable-sized integer
	virtual bool read(const char *label, bool *entry) = 0;

//	write either an integer or string to a record.
	virtual bool write(const char *label, const char *entry, int entrylen) = 0;
	virtual bool write(const char *label, int entry) = 0;
	
// get the current user's name.
	virtual void get_user_name(char* buffer, ulong* size) = 0;
};

// JCA: moved these from the Win32Database

//Handy macro to read an int without having to specify the wordsize
#define read_int(label,varp) read(label,varp,sizeof(*varp))

//Macro to write a string
#define write_string(label,varp) write(label,varp,strlen(varp))

#if defined(SDL3)
#include "sdl\SDLDatabase.h"
#elif defined(WIN32)
#include "win\Win32Database.h"
#elif defined(__LINUX__)
#include "linux/lnxdatabase.h"
#else
#error "appdatabase.h: Unknown environment"
#endif

#endif
