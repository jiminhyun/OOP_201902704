#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;

void ask();
void page(string s);
void readline();
void readInstruction(string s);
string sumVec(vector<string> v);
void makeVec(string);
vector<string> v;
int current = 0;
int lineNum = 0;
bool flag = false;
string str;
string instruction;
string line;

int main()
{
	ifstream myFile;
	myFile.open("C:\\Users\\jimin\\Desktop\\학교\\2-2\\객체지향설계\\2020-2학기 객체지향설계 텀 프로젝트\\test.txt");

	if (myFile.is_open())
	{
		getline(myFile, str);
		makeVec(str);
		readline();
		ask();
		myFile.close();
	}
	return 0;
}

class TextEditor
{
private:
	TextEditor() {};
	static TextEditor* instance;
public:
	static TextEditor* getInstance()
	{
		if (!instance)
			instance = new TextEditor;
		return instance;
	}
	~TextEditor() { delete instance; };
	void Insert(int line, int num, string word);
	void Delete(int line, int num);
	void Search(string word);
	void Convert(string s1, string s2);
	void Save();
};

TextEditor* TextEditor::instance = 0;

void ask()
{
	while (instruction != "t") {
		for (int i = 0; i < 79; i++)
		{
			cout << "-";
		}
		cout << "\nn:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장 후 종료\n";
		for (int i = 0; i < 79; i++)
		{
			cout << "-";
		}
		cout << "\n";
		cin >> instruction;
		for (int i = 0; i < 79; i++)
		{
			cout << "-";
		}
		cout << "\n";
		readInstruction(instruction);
	}
}

void page(string s)
{
	if (s[0] == 'p')
	{
		if (current == 20)
		{
			cout << "첫번째 페이지\n";
			return;
		}
		else
		{
			if (flag)
			{
				current = current - lineNum - 20;
				lineNum = 0;
				flag = false;
			}
			else
			{
				current = current - (20 * 2);
			}
			readline();

		}
	}
	else if (s[0] == 'n')
	{
		if (current == (v.size()))
		{
			cout << "마지막 페이지\n";
			return;
		}
		else
		{
			readline();
		}
	}
}

void readline()
{
	if (current + 20 > v.size()) {
		current = v.size() - 20;
	}
	else if (current < 0) {
		current = 0;
	}
	for (int i = 1; i <= 20; i++)
	{
		cout << i << "| ";
		cout << v[current++] << "\n";
	}
}

void TextEditor::Insert(int line, int num, string word)
{
	string str;
	int index = 0, wordNum = 0;
	vector<string> s;

	if ((line > 20) || num < 0)
	{
		cout << "line <= 20, num >= 0로 입력하시오.\n";
		return;
	}
	if (word.size() > 75)
	{
		cout << "75자 이하로 입력하시오.\n";
		return;
	}
	if (flag)
	{
		if (line > lineNum)
		{
			cout << "line을 다시 입력하시오.\n";
			return;
		}
		index = current + (line - 1) - lineNum;
		flag = false;
	}
	else
	{
		index = current + (line - 1) - 20;
	}

	str = v[index];
	istringstream ss(str);
	string stringBuffer, sum;

	while (getline(ss, stringBuffer, ' '))
	{
		s.push_back(stringBuffer);
		wordNum++;

	}
	if (wordNum < num)
	{
		cout << "오류 : " << num << "번째 단어는 없습니다.\n";
		return;
	}
	for (int i = 0; i < num; i++)
	{
		sum += s[i] + ' ';
	}
	if (wordNum == num) 
	{
		if (str[str.size() - 1] == ' ')
		{
			sum += word + ' ';
		}
		else
		{
			sum += word;
		}
	}
	else
	{
		sum += word + ' ';
		for (int i = num; i < wordNum - 1; i++)
		{
			sum += s[i] + ' ';
		}
		if (str[str.size() - 1] == ' ')
		{
			sum += s[wordNum - 1] + ' ';
		}
		else
		{
			sum += s[wordNum - 1];
		}
	}
	v[index] = sum;
	sumVec(v);
	current -= 20;
	readline();

}

void TextEditor::Delete(int line, int num)
{
	string str;
	int index = 0, wordNum = 0;
	vector<string> s;

	if ((line > 20) || num < 0)
	{
		cout << "line <= 20, num >= 0로 입력하시오.\n";
		return;
	}
	if (flag)
	{
		if (line > lineNum)
		{
			cout << "line을 다시 입력하시오.\n";
			return;
		}
		index = current + (line - 1) - lineNum;
		cout << "currentLine : " << current << endl;
		flag = false;
	}
	else
	{
		index = current + (line - 1) - 20;
	}
	str = v[index];
	istringstream ss(str);
	string stringBuffer, sum;

	while (getline(ss, stringBuffer, ' '))
	{
		s.push_back(stringBuffer);
		wordNum++;

	}
	if (wordNum < num)
	{
		cout << "오류 : " << num << "번째 단어는 없습니다.\n";
		return;
	}
	for (int i = 0; i < num - 1; i++)
	{
		sum += s[i] + ' ';
	}
	for (int i = num; i < wordNum; i++)
	{
		sum += s[i] + ' ';
	}
	if (str[str.size() - 1] == ' ')
	{
		v[index] = sum;
		sumVec(v);

	}
	else
	{
		sum = sum.substr(0, sum.size() - 1);
		v[index] = sum;
		sumVec(v);
	}
	current -= 20;
	readline();
}

void TextEditor::Convert(string s1, string s2)
{
	if (flag) {
		flag = false;
	}
	string s = sumVec(v);
	string change = "", sum = "", last = "";
	int word = s.find(s1);
	while (word != -1)
	{
		change = s.substr(0, word);
		change += s2;
		s = s.substr(word + s1.size());
		last = s;
		word = s.find(s1);
		sum += change;
	}
	sum += last;
	makeVec(sum);
	current -= 20;
	readline();
}

void TextEditor::Search(string find)
{
	int word = 0, index = -1;
	for (int i = 0; i < v.size(); i++)
	{
		word = v[i].find(find);
		if (word != -1)
		{
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "찾을 수 없습니다.\n";
		return;
	}
	current = index;
	int j = 1;
	if (current + 20 > v.size())
	{
		flag = true;
		for (int i = current; i < v.size(); i++)
		{
			cout << j++ << "| ";
			cout << v[current++] << "\n";
			lineNum++;
		}
	}
	else
		readline();
}

void TextEditor::Save()
{
	ofstream writeFile;
	writeFile.open("C:\\Users\\jimin\\Desktop\\학교\\2-2\\객체지향설계\\2020-2학기 객체지향설계 텀 프로젝트\\test.txt");
	string save = sumVec(v);

	if (writeFile.is_open())
	{
		writeFile << save;
	}

	writeFile.close();
}

string sumVec(vector<string> vec)
{
	string s = "";
	for (int i = 0; i < vec.size(); i++)
	{
		s += vec[i];
	}
	makeVec(s);
	return s;
}

void makeVec(string s)
{
	istringstream st(s);
	string cut = "", last = "";
	line = "";

	if (!v.empty())
	{
		while (!v.empty())
		{
			v.pop_back();
		}
	}
	while (getline(st, cut, ' ')) {
		if (line.size() + cut.size() + 1 <= 75)
		{
			line += cut + " ";
		}
		else
		{
			v.push_back(line);
			line = cut + " ";
		}
	}
	line = line.substr(0, line.size() - 1);
	v.push_back(line);
}
bool isInt(const string& s)
{
	for (const char& c : s)
	{
		if (isdigit(c))
			return true;
	}
	return false;
}

void readInstruction(string instruction)
{
	string buffer, word;
	int line, num;
	int error = 0, find = 0;
	vector<string> s;

	error = instruction.find(' ');
	if (error != string::npos) {
		cout << "공백 없이 다시 입력하시오.\n";
		return;
	}

	if (instruction.size() == 1)
	{
		if (instruction[0] == 'n' || instruction[0] == 'p')
		{
			page(instruction);
			return;
		}

		else if (instruction[0] == 't')
		{
			TextEditor::getInstance()->Save();
			return;
		}
		else
		{
			cout << "다시 입력하시오.\n";
			return;
		}
	}
	else if (instruction.size() > 1)
	{
		if ((instruction[1] == '(') && (instruction[instruction.size() - 1] == ')'))
		{
			buffer = instruction.substr(2, instruction.size() - 3); 
			istringstream ss(buffer);
			if ((instruction[0] == 'i'))
			{
				while (getline(ss, buffer, ','))
				{
					s.push_back(buffer);
				}
				if (s.size() != 3)
				{
					cout << "인자 개수 오류. 다시 입력하시오.\n";
					return;
				}
				if (!isInt(s[0]) && !isInt(s[1]))
				{
					cout << "첫번째, 두번째 인자는 숫자로 입력하시오.\n";
					return;
				}
				line = atoi(s[0].c_str());
				num = atoi(s[1].c_str());
				word = s[2];
				TextEditor::getInstance()->Insert(line, num, word);
				return;
			}
			else if ((instruction[0] == 'd'))
			{
				while (getline(ss, buffer, ','))
				{
					s.push_back(buffer);
				}
				if (s.size() != 2)
				{
					cout << "인자 개수 오류. 다시 입력하시오.\n";
					return;
				}
				if (!isInt(s[0]) && !isInt(s[1]))
				{
					cout << "첫번째, 두번째 인자는 숫자로 입력하시오. 다시 입력하시오.\n";
					return;
				}
				line = atoi(s[0].c_str());
				num = atoi(s[1].c_str());
				TextEditor::getInstance()->Delete(line, num);
				return;
			}
			else if ((instruction[0]) == 's')
			{
				while (getline(ss, buffer, ','))
				{
					s.push_back(buffer);
				}
				if (s.size() != 1)
				{
					cout << "인자 개수 오류.\n";
					return;
				}
				word = s[0];
				TextEditor::getInstance()->Search(word);
				return;
			}
			else if ((instruction[0]) == 'c')
			{
				while (getline(ss, buffer, ','))
				{
					s.push_back(buffer);
				}
				if (s.size() != 2)
				{
					cout << "인자 개수 오류.\n";
					return;
				}
				TextEditor::getInstance()->Convert(s[0], s[1]);
				return;
			}
			else
			{
				cout << "다시 입력하시오.\n";
				return;
			}
		}
		else
		{
			cout << "다시 입력하시오.\n";
			return;
		}
	}
}