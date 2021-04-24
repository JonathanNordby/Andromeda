//Buffer.cpp

#include "Buffer.h"

using namespace std;

void Buffer::display() const {

	int ix_stop_line_ = ix_top_line_ + window_height_;
	
	for (int i = ix_top_line_; i < ix_stop_line_; ++i) {
		if (i < v_words_.size())
			cout << setw(6) << i+1 << " " << v_words_[i];
		cout << '\n';	
	}

}

bool Buffer::open(const string & new_file_name) {
	
	ifstream file(new_file_name);
	if (!file) {
		return false;
	}
	
	v_words_.clear();
	
	string word;
	while (file >> word) {
		if (is_anchor(word)) {
			string filename;
			string text;
			file >> filename >> text;
			
			links.push_back(filename);
			v_words_.push_back("<" + text + "[" + to_string(links.size()) + "]");	
		} else if (is_paragraph(word)) {
			v_words_.push_back(to_string('\n'));
			v_words_.push_back(to_string('\n'));
		} else if (is_break(word)) {
			v_words_.push_back(to_string('\n'));
		} else if (word == to_string('\n')) {
			
		} else {
			v_words_.push_back(word);
		}
	}
	 
	file_name_ = new_file_name;
	ix_top_line_ = 0;
	return true;
}

bool Buffer::search(const string & test) {
	for (int i = ix_top_line_; i < v_words_.size(); i++) {
		if (v_words_[i].find(test) == string::npos) {
			return false;
		}
		ix_top_line_ = i;
		return true;
	}
}

bool Buffer::go(int link) {

	history.push_back( file_name_);
	return open(links[link]);

}

bool Buffer::back() {
	if (!open(*(history.end() - 2))) {
		return false;
	}
	history.pop_back();
}

bool is_anchor(string & test) {
	return test == "<a";
}

bool is_paragraph(string & test) {
	return test == "<p>";
}

bool is_break(string & test) {
	return test == "<b>";
}
