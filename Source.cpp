#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"

using namespace std;

struct node {
	node *next;
	node *prev;

	string ORIGINALNOMESS;
	string originaldata;
	string cleandata;

};
class reading {

public:

	reading()
	{
		head = nullptr;
		tail = nullptr;
	}
	void readFromFile(string filename) {
		ifstream readFile;
		readFile.open(filename);
		if (readFile.is_open()) { cout << "file is open" << endl << endl; }
		else { cout << "unable to open"; }

		string line;
		string newline;

		while (getline(readFile, line)) {
			newline = "";
			string nomess = line;
			for (int i = 0; i < line.size(); ++i)
			{
				if (!((line[i] == ' ') || (line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z')))
				{
					newline += "";
				}
				else {
					/*if (line[i] >= 'A' && line[i] <= 'Z')
							   newline += line[i] + 32;*/
					if (line[i] >= 'A'&&line[i] <= 'Z')
						line[i] = line[i] + 32;
					newline += line[i];
				}
			}

			addLines(line, newline, nomess);
		}
	}

	void addLines(string line, string newline, string nomess) {
		node *temp = new node;
		temp->originaldata = line;
		temp->cleandata = newline;
		temp->ORIGINALNOMESS = nomess;
		//cout << temp->ORIGINALNOMESS << "HELLO" << endl;
		temp->next = NULL;

		if (head == nullptr)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}

	void addfromsort(string line) {
		node *temp = new node;
		//temp = somenode;
		temp->cleandata = line;
		temp->next = NULL;

		if (head == nullptr)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}
	void sortTheLines() {

		node *look = new node;
		node *cu = new node;
		node *temp = new node;
		node *prev = new node;

		//-----------------------------------------------------------------------------
		//-------------------------------------------------------------------------------
		int count = 0;
		int flag = 0;
		look = head;
		while (look != nullptr) {

			string lastword = look->cleandata;
			lastword = lastword.substr(lastword.find_last_of(" ") + 1);
			cu = look->next;

			while (cu != nullptr) {
				flag = 0;
				string firstword = cu->cleandata;
				firstword = firstword.substr(0, firstword.find_first_of(" "));
				if (firstword == lastword)
				{
					flag = 1;
					cout << "flag: " << flag << endl;
					cout << "my firstword: " << firstword << endl;
					cout << "last word: " << lastword << endl << endl;

					temp->cleandata = look->next->cleandata;
					look->next->cleandata = cu->cleandata;
					cu->cleandata = temp->cleandata;

					temp->ORIGINALNOMESS = look->next->ORIGINALNOMESS;
					look->next->ORIGINALNOMESS = cu->ORIGINALNOMESS;
					cu->ORIGINALNOMESS = temp->ORIGINALNOMESS;

					break;
				}

				cu = cu->next;
			}
			if (flag == 0) {

				count += 1;
				cout << "when flag =0: " << endl << look->cleandata << endl;
				if (count <= 5) {
					string originalCohesive = "";
					string cleanCohesive = "";
					string nomessCohesive = "";

					while (head != look->next) {

						originalCohesive += head->cleandata;
						nomessCohesive += head->ORIGINALNOMESS;
						cleanCohesive += head->cleandata;

						if (head != look) {
							nomessCohesive += "\n";
							originalCohesive += "\n";
							cleanCohesive += "\n";
						}

						head = head->next;
					}

					cout << endl << "!!!!!--------" << endl;
					cout << originalCohesive << " " << " printing clean now : " << endl << cleanCohesive << endl;
					addLines(nomessCohesive, cleanCohesive, nomessCohesive);
				}


			}
			cout << "priting look :   " << look->cleandata << endl;
			look = look->next;

		}


	}
	void displayOriginal(string outfile) {

		string text;
		ofstream writefile;
		writefile.open(outfile);

		node *cu = new node;
		cu = head;
		while (cu != nullptr) {
			cout << cu->ORIGINALNOMESS << endl;
			text = cu->ORIGINALNOMESS;
			writefile << text << endl;
			cu = cu->next;
		}
		writefile.close();
	}
	void displayClean() {
		node *cu = new node;
		cu = head;
		while (cu != nullptr) {
			cout << cu->cleandata << endl;
			cu = cu->next;
		}
	}

private:
	node *head;
	node *tail;

};

//int main() 
int main(int argc, char * argv[])
{

	ArgumentManager am(argc, argv);
	const string in = am.get("input");
	const string out = am.get("output");

	//string in = "input5.txt";
	//string out = "output.txt";

	reading object;
	object.readFromFile(in);
	cout << endl << "printing clean: " << endl;
	object.displayClean();
	cout << endl;
	object.sortTheLines();

	cout << "printing original: " << endl;

	object.displayOriginal(out);

	//cout << endl << "printing clean: " << endl;

	//object.displayClean();

	system("pause");
	return 0;

}
