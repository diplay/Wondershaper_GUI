/*
 * wondershaper gui
 * 
 * Copyright 2013 diplay <diplaysuper@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <gtk/gtk.h>
#include <stdlib.h>
#include <net/if.h>



enum STRINGS
{
	ADAPTERS_FAIL = 0,
	TITLE = 1,
	INITIAL_DOWN = 2,
	INITIAL_UP = 3,
	TEXT_DOWN = 4,
	TEXT_UP = 5,
	SET_SPEED = 6,
	CLEAR = 7
};

const char* strings[] = {"Can't get adapters list, enter manually",
							"Speed adjustment",
							"768", "512", "Download(kbit/s)",
							"Upload(kbit/s)", "Set Speed", "Clear"};

