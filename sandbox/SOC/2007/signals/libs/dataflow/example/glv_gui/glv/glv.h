#ifndef INC_GLV_H
#define INC_GLV_H

/*	Graphics Library of Views (GLV) - GUI Building Toolkit
	See COPYRIGHT file for authors and license information */

/*! \mainpage GLV - OpenGL GUI library

	\section intro_sec Introduction

	GLV (short for GL View) is an OpenGL based GUI library, currently for OSX, 
	Win32, and Linux. The ideal is to create a reasonably efficient, 
	multi-platform API that makes it simple for the end-user developer to 
	create an application's graphical user interface entirely using GPU-based 
	OpenGL instructions, thus freeing CPU resources for other work 
	(e.g. audio DSP).

*/

/*	
	helpful include file to include all of GLV at once 
*/

// GLV core:
#include "glv_core.h"
#include "glv_behavior.h"
#include "glv_layout.h"

// widgets:
#include "glv_sliders.h"
#include "glv_textview.h"

#endif

