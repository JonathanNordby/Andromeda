//Andromeda.cpp

#include "Andromeda.h"

using namespace std;

void Andromeda::display() {
	const string long_seperator(50, '-');
	const string short_seperator(8, '-');
	
	system(clear_command);
	
	if (!error_message_.empty()) {
        cout << "ERROR: " + error_message_ << endl;
        error_message_.clear();
    }

    string file_name = buffer_.file_name();
    if (file_name.empty())
        cout << "<no file opened>\n";
    else
        cout << file_name << endl;

    cout << long_separator << endl;
    buffer_.display();
    cout << long_separator << endl;
    cout << "  next  previous  open  search  quit\n";
    cout << short_separator << endl;
}

void Andromeda::execute_command(char command, bool & done)
{
    switch (command) {
        case 'n': {
            buffer_.move_to_next_page();
            break;
        }

        case 'o': {
            cout << "file name: ";
            string file_name;
            getline(cin, file_name);
            if (!buffer_.open(file_name))
                error_message_ = "Could not open " + file_name;
            break;
        }

        case 'p': {
            buffer_.move_to_previous_page();
            break;
        }

        case 'q': {
            done = true;
            break;
        }
        case 's': {
            std::string searchword;
            cout << "Enter search query ";
            cin >> searchword;
            if (!buffer_.search(searchword)) {
              error_message_ = "string \"" + search_item + "\" was not found";
            }
            break;
        }
        case 'g': {
        	int link;
        	cout << "link number: ";
        	cin >> link;
        	if (!buffer_.go(link)) {
        		error_message_ = "link cannot be found";	
        	}
			break;
		}
    }
}

void Andromeda::run() {
    cout << "Window height? ";
    cin >> window_height_;
    cin.get();  // '\n'
    cout << '\n';
    buffer_.set_window_height(window_height_);

    bool done = false;
    while (!done) {
        display();

        cout << "command: ";
        char command;
        cin >> command;
        cin.get(); // '\n'

        execute_command(command, done);

        cout << endl;
    }
}
