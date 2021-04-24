
#ifndef _Andromeda_h_
#define _Andromeda_h_

#include<cstdlib>
#include<iostream>
#include<string>

#include "buffer.h"

const char clear_command[] = "cls";

class Andromeda {
	
	public:
		void run();
	private:
	
		void display();
		void execute_command(char command, bool & done);
		
		Buffer buffer_;
		int window_height_;
		std::string error_message_;
};

#endif
