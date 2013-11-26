/*
 * interface.hpp
 *
 *  Created on: Oct 27, 2009
 *      Author: etiene
 *
 *  This file is part of assignment-3.
 *
 *  assignment-3 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  assignment-3 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with assignment-3.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <GL/glui.h>

#include "common.hpp"

// Live variables
extern int ShowWireLive;

// Panels
GLUI_Panel* DebugPanel;


// Checkbox
extern GLUI_Checkbox* ShowWireCheckbox;


GLUI* glui;

#define CB_QUIT 0
#define CB_NONE 1
#define CB_RADIO 2
#define CB_GEOMETRY 3

void glui_cb(int control)
{

	switch(control)
	{
	case CB_GEOMETRY:
	{
		break;
	}
	case CB_QUIT: exit(1);
				  break;
	case CB_NONE:
	default:
		break;
	}

	glutSetWindow(MainWindowId);
	glutPostRedisplay();
}

inline
void initGlui()
{
	glui = GLUI_Master.create_glui_subwindow(MainWindowId,
											GLUI_SUBWINDOW_LEFT);


	DebugPanel = glui->add_panel("Debug");

	// Show Tettrahedra path
	ShowWireCheckbox = glui->add_checkbox_to_panel(DebugPanel,
		"Show Wire", &ShowWireLive, CB_NONE, (GLUI_Update_CB)glui_cb);
	ShowWireCheckbox->set_int_val(ShowWireLive);


	glui->add_button("Quit", CB_QUIT, (GLUI_Update_CB)glui_cb);



	glui->hide();
}


#endif /* INTERFACE_HPP_ */
