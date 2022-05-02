#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace ::std;

#pragma region Define_Book_Classes

class Book {
	friend class BookList;

private:
	string Name, Author, PubName, Genre;
	int PubYear;

	Book* next;

	Book() {
		Name = "";
		Author = "";
		PubName = "";
		Genre = "";
		PubYear = 0;

		next = NULL;
	}
};

class BookList {
private:
	Book* head;
	Book* last;

	void PrintBookInfo(Book* book)
	{
		cout.width(20);
		cout << std::left << book->Name << "   ";
		cout.width(20);
		cout << std::left << book->Author;
		cout.width(20); 
		cout << std::left << book->PubYear;
		cout.width(20);
		cout << std::left << book->PubName;
		cout.width(20);
		cout << std::left << book->Genre << endl;
	}
	Book* FindBook(string name)
	{
		Book* thisBook = head;

		while (thisBook != NULL)
		{
			if (name == thisBook->Name)
			{
				return thisBook;
			}

			thisBook = thisBook->next;
		}

		return NULL;
	}

public:
	BookList() {
		Book* headnode = new Book;

		head = headnode;
		last = headnode;
	}

	void LoadFile();
	void SaveFile();

	void ShowBookList();
	void AddBook();
	void ModifyBook();
	void DeleteBook();
	void SearchBook();
};

void BookList::LoadFile()
{
	ifstream inputfile("input.txt");
	if (!inputfile)
	{
		cout << "���� ã�� ����" << endl;
		return;
	}

	string line;
	while (getline(inputfile, line))
	{
		string name, author, pubname, genre;
		string pubyear;

		int index = 0;
		int leng = line.length();

		//name �Ҵ�
		while (line[index] != ' ')
		{
			name.push_back(line[index]);
			index++;
		}
		index++;

		//author �Ҵ�
		while (line[index] != ' ')
		{
			author.push_back(line[index]);
			index++;
		}
		index++;

		//pubyear �Ҵ�
		while (line[index] != ' ')
		{
			pubyear.push_back(line[index]);
			index++;
		}
		index++;

		//pubname �Ҵ�
		while (line[index] != ' ')
		{
			pubname.push_back(line[index]);
			index++;
		}
		index++;

		//genre �Ҵ�
		while (index < line.length())
		{
			genre.push_back(line[index]);
			index++;
		}

		Book* readBook = new Book;

		readBook->Name = name;
		readBook->Author = author;
		readBook->PubYear = stoi(pubyear);
		readBook->PubName = pubname;
		readBook->Genre = genre;

		last->next = readBook;
		last = readBook;
	}

	inputfile.close();
}
void BookList::SaveFile()
{
	ofstream outputfile;

	outputfile.open("input.txt");
	if (!outputfile)
	{
		cout << "���� ã�� ����" << endl;
		return;
	}

	Book* node = head->next;

	while (node != NULL)
	{
		string line;

		line.append(node->Name);
		line.append(" ");

		line.append(node->Author);
		line.append(" ");

		string year = to_string(node->PubYear);
		line.append(year);
		line.append(" ");

		line.append(node->PubName);
		line.append(" ");

		line.append(node->Genre);
		line.append("\n");

		outputfile.write(line.c_str(), line.size());

		node = node->next;
	}

	outputfile.close();
}

void BookList::ShowBookList()
{
	Book* thisBook = head->next;
	int bookNum = 1;

	system("cls");


	while (thisBook != NULL)
	{
		cout << bookNum << "��° å	";
		PrintBookInfo(thisBook);

		bookNum++;
		thisBook = thisBook->next;
	}
}
void BookList::AddBook()
{
	Book* newBook = new Book();
	string name, author, pubName, genre;
	int pubYear;

	cout << "å�� �̸��� �Է��ϼ���. : ";
	cin >> name;

	cout << "å�� ���ڸ� �Է��ϼ���. : ";
	cin >> author;

	cout << "å�� ���� ������ �Է��ϼ���. : ";
	cin >> pubYear;

	cout << "å�� ���ǻ縦 �Է��ϼ���. : ";
	cin >> pubName;

	cout << "å�� �帣�� �Է��ϼ���. : ";
	cin >> genre;


	newBook->Name = name;
	newBook->Author = author;
	newBook->PubName = pubName;
	newBook->Genre = genre;
	newBook->PubYear = pubYear;

	last->next = newBook;
	last = newBook;
}
void BookList::ModifyBook()
{
	string name;
	cout << "������ å�� ������ �Է��ϼ���. : ";
	cin >> name;

	Book* thisBook = FindBook(name);

	if (thisBook == NULL)
	{
		cout << "ã���ô� å�� �����ϴ�. " << endl;
	}
	else
	{
		cout << endl <<endl;

		PrintBookInfo(thisBook);

		cout << endl <<"�����ϰڽ��ϴ�." << endl;

		cout << "å�� �̸��� �Է��ϼ���. : ";
		cin >> thisBook->Name;

		cout << "å�� ���ڸ� �Է��ϼ���. : ";
		cin >> thisBook->Author;

		cout << "å�� ���� ������ �Է��ϼ���. : ";
		cin >> thisBook->PubYear;

		cout << "å�� ���ǻ縦 �Է��ϼ���. : ";
		cin >> thisBook->PubName;

		cout << "å�� �帣�� �Է��ϼ���. : ";
		cin >> thisBook->Genre;
	}
}
void BookList::DeleteBook()
{
	string name;
	cout << "������ å�� ������ �Է��ϼ���. : ";
	cin >> name;

	Book* exBook = head;
	Book* thisBook = NULL;

	while (exBook->next != NULL)
	{
		if (exBook->next->Name == name)
		{
			thisBook = exBook->next;
			break;
		}

		exBook = exBook->next;
	}

	if (exBook->next == NULL)
	{
		cout << "ã���ô� å�� �����ϴ�. " << endl;
	}
	else
	{
		exBook->next = thisBook->next;
		delete thisBook;

		cout << "å�� �����߽��ϴ�. " << endl;
	}
}
void BookList::SearchBook()
{
	vector<Book*> findingBooks;
	Book* node = head->next;

	int optionIndex = 0;
	string str;

	cout << "�������� å�� �˻��ұ��??" << endl << "1. å �̸�" << endl << "2. å�� ����" << endl << "3. ���ǿ���" << endl <<
		"4. å ���ǻ��� �̸�" << endl << "5. å�� �帣" << endl;
	cout << "�Է�) ";
	cin >> optionIndex;
	cout << "------------------------------------------------------------------------------------------------------------------" << endl;

	switch (optionIndex)
	{
	case 1:
		cout << "å�� �̸��� �Է��ϼ���. : ";
		cin >> str;

		while (node != NULL)
		{
			if (str == node->Name)
			{
				findingBooks.push_back(node);
			}

			node = node->next;
		}
		break;
	case 2:
		cout << "å�� ���ڸ� �Է��ϼ���. : ";
		cin >> str;

		while (node != NULL)
		{
			if (str == node->Author)
			{
				findingBooks.push_back(node);
			}

			node = node->next;
		}
		break;
	case 3:
	{
		cout << "å�� ���ǿ����� �Է��ϼ���. : ";
		cin >> str;

		int year = stoi(str);

		while (node != NULL)
		{
			if (year == node->PubYear)
			{
				findingBooks.push_back(node);
			}

			node = node->next;
		}
		break;
	}
	case 4:
		cout << "å�� ���ǻ縦 �Է��ϼ���. : ";
		cin >> str;

		while (node != NULL)
		{
			if (str == node->PubName)
			{
				findingBooks.push_back(node);
			}

			node = node->next;
		}
		break;
	case 5:
		cout << "å�� �帣�� �Է��ϼ���. : ";
		cin >> str;

		while (node != NULL)
		{
			if (str == node->Genre)
			{
				findingBooks.push_back(node);
			}

			node = node->next;
		}
		break;
	}
	cout << "------------------------------------------------------------------------------------------------------------------" << endl;

	int len = findingBooks.size();
	if (len == 0)
	{
		cout << "�˻������ �����ϴ�." << endl;
	}
	for (int i = 0; i < len; i++)
	{
		PrintBookInfo(findingBooks[i]);
	}
}

#pragma endregion

void LibrarySystem(BookList* library)
{
	int optionIndex = 0;
	system("cls");
	
	cout << "0. ����" << endl
		<< "1. ���� ��� ���" << endl
		<< "2. ���� �߰�" << endl
		<< "3. ���� �˻�" << endl
		<< "4. ���� ���� ����" << endl
		<< "5. ���� ����" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "������ ���� �Է��ϼ���. : ";
	cin >> optionIndex;

	cout << endl;

	switch (optionIndex)
	{
	case 0:
		cout << "�����մϴ�." << endl;
		return;
	case 1:
		library->ShowBookList();
		break;
	case 2:
		library->AddBook();
		break;
	case 3:
		library->SearchBook();
		break;
	case 4:
		library->ModifyBook();
		break;
	case 5:
		library->DeleteBook();
		break;
	default:
		break;
	}

	system("PAUSE");

	LibrarySystem(library);
}

int main()
{
	BookList Library;
	BookList* pLibrary = &Library;

	Library.LoadFile();

	LibrarySystem(pLibrary);

	Library.SaveFile();

	return 0;
}