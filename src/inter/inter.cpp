// inter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "..\interception.h"
#include "utils.h"
#include <windows.h>
enum ScanCode
{
	SCANCODE_X   = 0x2D,
	SCANCODE_Y   = 0x15,
	SCANCODE_ESC = 0x01
};

int _tmain( int argc, TCHAR **argv )
{
	if (argc>1)
	{	HWND hwnd = GetConsoleWindow();
		ShowWindow(hwnd, 0);}
	TCHAR hardware_id[512];
	InterceptionContext context;
	InterceptionDevice device;
	InterceptionKeyStroke stroke;

	raise_process_priority();

	context = interception_create_context();

	interception_set_filter(context, interception_is_keyboard, INTERCEPTION_FILTER_KEY_ALL);

	while(interception_receive(context, device = interception_wait(context), (InterceptionStroke *)&stroke, 1) > 0)
	{
		if (stroke.code==82 || stroke.code==79)
		{
			bool fix=false;
			size_t length = interception_get_hardware_id(context, device, hardware_id, sizeof(hardware_id));
			if (argc>1 && 0==wcscmp(hardware_id,argv[1]))
			{
				fix=true;
			}
			if (argc==1) fix=true;
			if (fix)
			{
				if(length > 0 && length < sizeof(hardware_id))
					_tprintf(L"%s %d\n", hardware_id,stroke.code);
				if(stroke.code == 82){ stroke.code = 79; }

				else if (stroke.code==79) stroke.code=82;
			}
		}
		interception_send(context, device, (InterceptionStroke *)&stroke, 1);
		//if(stroke.code == SCANCODE_ESC) break;
	}

	interception_destroy_context(context);

	return 0;
}