#include <iostream>
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>
#include <list>
using namespace std;


class Problem1
{

	static void print(char it) {
		cout << it;
	}
	static bool pred(const char& it_s) {
		static int count1 = 0;
		if (count1 == 0) {
			if (it_s == '{') {
				count1 = 1;
				return true;
			}
		}

		if (count1 != 0) {
			if (it_s == '{') count1++;
			if (it_s == '}') count1--;
			return true;
		}
		return false;
	}

public:
	static string::iterator remove_brakets(string b) {
		string::iterator result = remove_if(b.begin(), b.end(), pred);
		for_each(b.begin(), result, print);
		return result;
	}

};

class Problem2 {
	static void print(const char it) {
		cout << it;
	}
	static string isXXXNumbers(string::iterator begin, string::iterator end, int size) {

		string result;
		if (size == -1 || end - begin == size) {
			back_insert_iterator<string> insert_(result);
			copy(begin, end, insert_);
			//for_each(result.begin(), result.end(), print);
			//cout << endl;
		}
		return result;
	}
	static bool pr(char it) {
		return (it == ' ');
	}
public:
	static	list<string> word_searching(string st, int number = -1) {
		list<string> result;
		back_insert_iterator<list<string>> insert_(result);

		for (auto i = st.begin(); i != st.end(); i = find_if(i + 1, st.end(), pr)) {
			//insert_++;
			string &s = isXXXNumbers(i == st.begin() ? i : i + 1, find_if(i + 1, st.end(), pr), number);
			if (s != "")
				result.push_back(s);

		}

		//for_each(result.begin(), result.end(), print_string);
		return result;
	}
	static void print_string(string st) {
		for_each(st.begin(), st.end(), print);
		cout << endl;
	}
};

static string s;
class Problem3 {
	class Pred {
		int count_;
		char ch_;

	public:

		Pred() :count_(0), ch_('/0')
		{}

		bool operator ()(const char& ch) {
			if (ch == ch_) {
				count_++;
				return  true;
			}


			if (count_ != 0 && count_ != 1) {
				char *buffer = new char;
				itoa(count_, buffer, 10);
				s += "(";
				s += buffer;
				s += ")";
			}
			s += ch;
			ch_ = ch;
			count_ = 1;
			return false;
		}
		static void print(char& ch) {
			cout << ch;
		}

		void print_s() {
			for_each(s.begin(), s.end(), print);
			cout << endl;
		}
	};
public:


	static string alteration(string st) {
		Pred pred;
		remove_if(st.begin(), st.end(), pred);
		pred.print_s();
		return s;
	}
};

class Problem4 {
	static void print_(const char& ch) {
		cout << ch;
	}
	static void print_string(string st) {
		for_each(st.begin(), st.end(), print_);
		cout << " ";
	}
public:
	static string sorting(string st) {
		list<string> list_s = Problem2::word_searching(st);
		vector<string> vec_s;
		back_insert_iterator<vector<string>> insertor(vec_s);
		copy(list_s.begin(), list_s.end(), insertor);
		sort(vec_s.begin(), vec_s.end());
		string result;
		int _size = vec_s.size();
		while (_size) {
			int g = count(vec_s.begin(), vec_s.end(), vec_s[0]);
			result += vec_s[0];
			string deleteing = vec_s[0];
			remove(vec_s.begin(), vec_s.end(), deleteing);
			if (g != 1) {
				char* buffer = new char;
				itoa(g, buffer, 10);
				result += "(";
				result += buffer;
				result += ")";
			}
			result += " ";
			_size -= g;

		}

		for_each(result.begin(), result.end(), print_);
		cout << endl;
		return result;
	}
};

int main() {
	//Problem1
	cout << "\tRESULT Problem1" << endl;
	string a = "a{1+{2}+3}b{4}c";
	Problem1::remove_brakets(a);
	cout << endl;

	//Problem2
	string b = "alyfa beta gama delta";
	cout << "\n\tRESULT Problem2" << endl;
	auto b1 = Problem2::word_searching(b, 5);
	for_each(b1.begin(), b1.end(), Problem2::print_string);


	//Problem3
	string c = "abbbbbcaaaaddeeef";
	cout << "\n\tRESULT Problem3" << endl;
	Problem3::alteration(c);


	//Problem4
	cout << "\n\tRESULT Problem4" << endl;
	string d = "alpha gamma alpha delta gamma beta alpha ";
	Problem4::sorting(d);

	cin.get();
	return 0;


}
