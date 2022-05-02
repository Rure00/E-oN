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
		cout << "파일 찾지 못함" << endl;
		return;
	}

	string line;
	while (getline(inputfile, line))
	{
		string name, author, pubname, genre;
		string pubyear;

		int index = 0;
		int leng = line.length();

		//name 할당
		while (line[index] != ' ')
		{
			name.push_back(line[index]);
			index++;
		}
		index++;

		//author 할당
		while (line[index] != ' ')
		{
			author.push_back(line[index]);
			index++;
		}
		index++;

		//pubyear 할당
		while (line[index] != ' ')
		{
			pubyear.push_back(line[index]);
			index++;
		}
		index++;

		//pubname 할당
		while (line[index] != ' ')
		{
			pubname.push_back(line[index]);
			index++;
		}
		index++;

		//genre 할당
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
		cout << "파일 찾지 못함" << endl;
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
		cout << bookNum << "번째 책	";
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

	cout << "책의 이름을 입력하세요. : ";
	cin >> name;

	cout << "책의 저자를 입력하세요. : ";
	cin >> author;

	cout << "책의 출판 연도를 입력하세요. : ";
	cin >> pubYear;

	cout << "책의 출판사를 입력하세요. : ";
	cin >> pubName;

	cout << "책의 장르를 입력하세요. : ";
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
	cout << "수정할 책의 제목을 입력하세요. : ";
	cin >> name;

	Book* thisBook = FindBook(name);

	if (thisBook == NULL)
	{
		cout << "찾으시는 책이 없습니다. " << endl;
	}
	else
	{
		cout << endl <<endl;

		PrintBookInfo(thisBook);

		cout << endl <<"수정하겠습니다." << endl;

		cout << "책의 이름을 입력하세요. : ";
		cin >> thisBook->Name;

		cout << "책의 저자를 입력하세요. : ";
		cin >> thisBook->Author;

		cout << "책의 출판 연도를 입력하세요. : ";
		cin >> thisBook->PubYear;

		cout << "책의 출판사를 입력하세요. : ";
		cin >> thisBook->PubName;

		cout << "책의 장르를 입력하세요. : ";
		cin >> thisBook->Genre;
	}
}
void BookList::DeleteBook()
{
	string name;
	cout << "삭제할 책의 제목을 입력하세요. : ";
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
		cout << "찾으시는 책이 없습니다. " << endl;
	}
	else
	{
		exBook->next = thisBook->next;
		delete thisBook;

		cout << "책을 삭제했습니다. " << endl;
	}
}
void BookList::SearchBook()
{
	vector<Book*> findingBooks;
	Book* node = head->next;

	int optionIndex = 0;
	string str;

	cout << "무엇으로 책을 검색할까요??" << endl << "1. 책 이름" << endl << "2. 책의 저자" << endl << "3. 출판연도" << endl <<
		"4. 책 출판사의 이름" << endl << "5. 책의 장르" << endl;
	cout << "입력) ";
	cin >> optionIndex;
	cout << "------------------------------------------------------------------------------------------------------------------" << endl;

	switch (optionIndex)
	{
	case 1:
		cout << "책의 이름을 입력하세요. : ";
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
		cout << "책의 저자를 입력하세요. : ";
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
		cout << "책의 출판연도를 입력하세요. : ";
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
		cout << "책의 출판사를 입력하세요. : ";
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
		cout << "책의 장르를 입력하세요. : ";
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
		cout << "검색결과가 없습니다." << endl;
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
	
	cout << "0. 종료" << endl
		<< "1. 도서 목록 출력" << endl
		<< "2. 도서 추가" << endl
		<< "3. 도서 검색" << endl
		<< "4. 도서 정보 수정" << endl
		<< "5. 도서 삭제" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "다음할 일을 입력하세요. : ";
	cin >> optionIndex;

	cout << endl;

	switch (optionIndex)
	{
	case 0:
		cout << "종료합니다." << endl;
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