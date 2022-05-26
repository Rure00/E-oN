#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace ::std;

#pragma region Define_Time_Class

class Time
{
private:
	int hour, minute;

public:
	Time(int h = 0, int m = 0) {
		hour = h;
		minute = m;
	}

	bool SetHour(int h)
	{
		if (h > 24 || h < 0)
		{
			printf("잘못된 시간을 입력했습니다.");
			return false;
		}

		hour = h;
		return true;
	}
	bool SetMinute(int m)
	{
		if (m > 60 || m < 0)
		{
			printf("잘못된 분을 입력했습니다.");
			return false;
		}

		minute = m;
		return true;
	}

	bool operator<(Time comparison)
	{
		if (hour >= comparison.hour)
			return false;
		else if (hour < comparison.hour)
			return true;

		if (minute >= comparison.minute)
			return false;
		else if (minute < comparison.minute)
			return true;
	}
	Time operator-(Time comparsion)
	{
		Time result(0, 0);

		int ToMinute1 = hour * 60 + minute;
		int ToMinute2 = comparsion.hour * 60 + comparsion.minute;

		int gap = abs(ToMinute1 - ToMinute2);

		int h = gap / 60;
		int m = gap - h * 60;

		result.hour = h;
		result.minute = m;

		return result;
	}
	bool operator==(Time comparsion)
	{
		if (hour == comparsion.hour && minute == comparsion.minute)
			return true;

		return false;
	}

	string ToString()
	{
		string str;

		if (hour < 10)
			str.append("0");

		str.append(to_string(hour) + ":");

		if (minute < 10)
			str.append("0");

		str.append(to_string(minute));

		return str;
	}


};

#pragma endregion

#pragma region Define_Train_Classes

class Train {
	friend class TrainList;

private:
	string Departure, Arrival;
	Time TrainTime;
	string TrainName;
	int SeatNum;

	Train* next;

	Train()
	{
		TrainTime = NULL;
		Departure = "";
		Arrival = "";
		TrainName = "";
		SeatNum = 0;

		next = NULL;
	}
	Train(Time trainTime, string departure, string arrival, string trainName, int seatNum)
	{
		TrainTime = trainTime;
		Departure = departure;
		Arrival = arrival;
		TrainName = trainName;
		SeatNum = seatNum;

		next = NULL;
	}

	void PrintTrainInfo()
	{
		if (Departure == "")
		{
			cout << "Train is NULL" << endl;
			return;
		}

		cout << TrainTime.ToString();
		cout << " ";
		cout << std::left << Departure << " -> ";
		cout << std::left << Arrival;
		cout << " ";
		cout << std::left << TrainName;
		cout << " ";
		if (SeatNum != 0)
			cout << std::left << SeatNum << endl;
		else
			cout << std::left << "Sold Out" << endl;
	}
	//head의 Index는 0이다.
	bool Reserve(int index)
	{
		vector<int> ticketIndex = LoadTicket();

		if (SeatNum < 0)
		{
			cout << "자리가 없습니다." << endl;
			return false;
		}

		for (int i = 0; i < (signed)ticketIndex.size(); i++)
		{
			if (ticketIndex[i] == index)
			{
				cout << "이미 예매한 기차입니다." << endl;
				return false;
			}
		}

		ticketIndex.push_back(index);

		bool isSaved = SaveTicket(ticketIndex);
		if (isSaved == false)
		{
			cout << "예매에 실패했습니다..." << endl;
			return false;
		}

		cout << "예매되었습니다." << endl << endl;
		SeatNum--;

		return true;
	}
	bool CancelReserve(int index)
	{
		vector<int> TicketIndex = LoadTicket();
		bool isExist = false;

		for (int i = 0; i < (signed)TicketIndex.size(); i++)
		{
			if (TicketIndex[i] == index)
			{
				TicketIndex.erase(TicketIndex.begin() + i);
				isExist = true;
				break;
			}
		}

		if (isExist == true)
		{
			cout << "예매가 취소되었습니다." << endl << endl;
			SeatNum++;

			SaveTicket(TicketIndex);

			return true;
		}
		else
		{
			cout << "해당 기차 예매 내역을 찾을 수 없습니다." << endl;
			return false;
		}

	}

	vector<int> LoadTicket()
	{
		vector<int> TicketIndex;

		ifstream ticketinList("TicketList.txt");
		if (!ticketinList)
		{
			cout << "파일 찾지 못함" << endl;
			return TicketIndex;
		}

		string line;
		while (getline(ticketinList, line))
		{
			if (EOF && line == "")
				break;

			TicketIndex.push_back(stoi(line));
		}

		ticketinList.close();

		return TicketIndex;
	}
	bool SaveTicket(vector<int> ticketIndex)
	{
		ofstream ticketoutList("TicketList.txt");
		if (!ticketoutList)
		{
			cout << "파일 찾지 못함" << endl;
			return false;
		}

		for (int i = 0; i < (signed)ticketIndex.size(); i++)
		{
			string sindex = to_string(ticketIndex[i]);
			sindex.append("\n");

			ticketoutList.write(sindex.c_str(), sindex.size());
		}

		return true;
	}
};

class TrainList {
private:
	Train* head;
	Train* last;

	Train* GetTrainByIndex(int index)
	{


		Train* node = head;
		for (int i = 1; i <= index; i++)
		{
			node = node->next;
		}

		return node;
	}
	int GetIndexOfTrain(Train* train)
	{
		Train* node = head->next;
		int index = 1;

		while (node != NULL)
		{
			if (train == node)
			{
				return index;
			}


			index++;
			node = node->next;
		}

		return -1;
	}

public:
	TrainList() {
		Train* headnode = new Train();

		head = headnode;
		last = headnode;
	}

	void LoadFile();
	void SaveFile();

	void ShowTrainList();
	void QuickTicketing();
	vector<Train*> QuickSearch();
	void ShowMyTicket();
};

void TrainList::LoadFile()
{
	ifstream listfile("TrainList.txt");
	if (!listfile)
	{
		cout << "파일 찾지 못함" << endl;
		return;
	}

	string line;

	while (getline(listfile, line))
	{
		string hour, minute;
		string departure, arrival;
		string trainName;
		string seatnum;

		int index = 0;

		//Hour 할당
		while (line[index] != ':')
		{
			hour.push_back(line[index]);
			index++;
		}
		index++;

		//minute 할당
		while (line[index] != ' ')
		{
			minute.push_back(line[index]);
			index++;
		}
		index++;


		//departure 할당
		while (line[index] != ' ')
		{
			departure.push_back(line[index]);
			index++;
		}
		index += 4;


		//arrival 할당
		while (line[index] != ' ')
		{
			arrival.push_back(line[index]);
			index++;
		}
		index++;

		//TrainName 할당
		while (line[index] != ' ')
		{
			trainName.push_back(line[index]);
			index++;
		}
		index++;

		//SeatNum 할당
		while (index < (int)line.length())
		{
			seatnum.push_back(line[index]);
			index++;
		}

		Time newtime(stoi(hour), stoi(minute));
		Train* newTrain = new Train(newtime, departure, arrival, trainName, stoi(seatnum));

		last->next = newTrain;
		last = newTrain;
	}

	listfile.close();
}
void TrainList::SaveFile()
{
	ofstream outputfile;

	outputfile.open("TrainList.txt");
	if (!outputfile)
	{
		cout << "파일 찾지 못함" << endl;
		return;
	}

	Train* node = head->next;

	while (node != NULL)
	{
		string line;

		line.append(node->TrainTime.ToString());
		line.append(" ");

		line.append(node->Departure);
		line.append(" -> ");

		line.append(node->Arrival);
		line.append(" ");

		line.append(node->TrainName);
		line.append(" ");

		line.append(to_string(node->SeatNum));
		line.append("\n");

		outputfile.write(line.c_str(), line.size());

		node = node->next;
	}

	outputfile.close();
}

void TrainList::QuickTicketing()
{
	vector<Train*> wishTrain = QuickSearch();
	if (wishTrain.empty())
		return;

	for (int i = 0; i < (signed)wishTrain.size(); i++)
	{
		cout << "No." << i + 1 << " ";
		wishTrain[i]->PrintTrainInfo();
	}

	int optionIndex = 0;
	cout << "예매하시겠습니까? (yes: 1, no : 0) : ";
	cin >> optionIndex;

	switch (optionIndex)
	{
	case 1:
		break;
	case 0:
	default:
		cout << "취소되었습니다.";
		return;
	}

	int trainNum = -1;
	while (1)
	{
		cout << "예매할 기차의 번호를 입력해주세요. : ";
		cin >> trainNum;
		trainNum--;

		if (trainNum >= (signed)wishTrain.size() || trainNum < 0)
			cout << "잘못된 값을 입력했습니다. 다시 입력해주세요." << endl;
		else
			break;
	}

	int trainIndex = GetIndexOfTrain(wishTrain[trainNum]);
	wishTrain[trainNum]->Reserve(trainIndex);
}
vector<Train*> TrainList::QuickSearch()
{
	vector<Train*> TargetTrains;
	Time wishTime;
	string departure, arrival;
	int h = -1, m = -1;
	bool isOkay = false;

	system("cls");
	cout << "---------------빠른 예매---------------" << endl << endl;

	cout << "출발지와 도착지를 입력해주세요. (뒤로가기는 -1)" << endl;
	cin >> departure;
	if (departure == "-1")
	{
		cout << "메뉴로 돌아갑니다..." << endl;
		return TargetTrains;
	}
	cin >> arrival;

	if (arrival == "-1")
	{
		cout << "메뉴로 돌아갑니다..." << endl;
		return TargetTrains;
	}


	while (isOkay == false)
	{
		cout << "원하는 시간을 입력해주세요. ex) 13 50 (뒤로가기는 -1)" << endl;
		cin >> h;
		if (h == -1)
		{
			cout << "메뉴로 돌아갑니다..." << endl;
			return TargetTrains;
		}

		cin >> m;
		if (m == -1)
		{
			cout << "메뉴로 돌아갑니다..." << endl;
			return TargetTrains;
		}

		isOkay = (wishTime.SetHour(h) && wishTime.SetMinute(m));

		if (isOkay == false)
		{
			cout << "잘못된 시간을 입력했습니다. 다시 입력해주세요." << endl;
		}
	}

	cout << "------------------------------------------------------------------------------------------------------------------" << endl;

	Train* node = head;
	while (node != NULL)
	{
		string depar = node->Departure;
		string arriv = node->Arrival;

		if (departure == depar && arrival == arriv)
			TargetTrains.push_back(node);

		node = node->next;
	}

	if (TargetTrains.empty())
	{
		cout << "조건에 맞는 기차가 없습니다..." << endl;
		return TargetTrains;
	}

	int index = 1;
	Time min_gap_time = wishTime - (*TargetTrains[0]).TrainTime;

	vector<Train*> resultList;

	for (int i = 0; i < (signed)TargetTrains.size(); i++)
	{
		Time gapTime = wishTime - (*TargetTrains[i]).TrainTime;

		if (gapTime < min_gap_time)
		{
			min_gap_time = gapTime;

			resultList.clear();
			resultList.push_back(TargetTrains[i]);
		}
		else if (gapTime == min_gap_time)
		{
			resultList.push_back(TargetTrains[i]);
		}
	}

	return resultList;
}
void TrainList::ShowTrainList()
{
	Train* thisTrain = head->next;
	int trainNum = 1;

	system("cls");
	cout << "---------------기차 목록---------------" << endl << endl;

	while (thisTrain != NULL)
	{
		cout << "No." << trainNum << " ";
		thisTrain->PrintTrainInfo();

		trainNum++;
		thisTrain = thisTrain->next;
	}

	cout << "------------------------------------------------------------------------------------------------------------------" << endl;

	int optionIndex = 0;
	cout << "예매하시겠습니까? (yes:1, no:0) : ";
	cin >> optionIndex;

	int targettrainNum = -1;

	switch (optionIndex)
	{
	case 1:
		cout << "예매하려는 기차 번호를 입력해주세요. : ";
		cin >> targettrainNum;
		break;
	default:
		cout << "메뉴로 돌아갑니다..." << endl;
		return;
	}

	Train* targetTrain = GetTrainByIndex(targettrainNum);
	targetTrain->Reserve(targettrainNum);
}
void TrainList::ShowMyTicket()
{
	vector<Train> myTicketlist;

	ifstream ticketinList("TicketList.txt");
	if (!ticketinList)
	{
		cout << "파일 찾지 못함" << endl;
		return;
	}

	vector<int> TicketIndex;
	string line;
	while (getline(ticketinList, line))
	{
		if (EOF && line == "")
		{
			cout << "예매내역이 없습니다." << endl;
			return;
		}

		TicketIndex.push_back(stoi(line));
	}

	system("cls");
	cout << "---------------예매 내역---------------" << endl << endl;

	for (int i = 0; i < (signed)TicketIndex.size(); i++)
	{
		int trainIndex = TicketIndex[i];
		Train* node = GetTrainByIndex(trainIndex);

		myTicketlist.push_back(*node);

		cout << "No." << TicketIndex[i] << " ";
		node->PrintTrainInfo();
	}

	cout << "------------------------------------------------------------------------------------------------------------------" << endl;

	if (TicketIndex.empty())
	{
		cout << "예매된 기차가 없습니다." << endl;
		return;
	}

	int optionIndex = 0;
	cout << "예매를 취소하시겠습니까?(yes:1, no:0) : ";
	cin >> optionIndex;

	switch (optionIndex)
	{
	case 1:
		cout << "취소할 기차의 번호를 입력해주세요. : ";
		cin >> optionIndex;
		break;
	case 0:
	default:
		cout << "메인메뉴로 돌아갑니다..." << endl << endl;
		return;
	}

	Train* targetTrain = GetTrainByIndex(optionIndex);
	targetTrain->CancelReserve(optionIndex);
}

#pragma endregion

void TrainSystem(TrainList* trainList)
{
	int optionIndex = 0;
	system("cls");

	cout << "0. 종료" << endl
		<< "1. 빠른 예매" << endl
		<< "2. 전체 기차 출력" << endl
		<< "3. 나의 예매 정보" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "다음 할 일을 입력하세요. : ";
	cin >> optionIndex;

	cout << endl;

	switch (optionIndex)
	{
	case 0:
		cout << "종료합니다." << endl;
		return;
	case 1:
		trainList->QuickTicketing();
		break;
	case 2:
		trainList->ShowTrainList();
		break;
	case 3:
		trainList->ShowMyTicket();
		break;
	default:
		cout << "잘못된 인덱스값입니다." << endl;
		break;
	}

	system("PAUSE");

	TrainSystem(trainList);
}

int main()
{
	TrainList trainsList;
	TrainList* pTrainList = &trainsList;

	pTrainList->LoadFile();

	TrainSystem(pTrainList);

	pTrainList->SaveFile();

	return 0;
}
