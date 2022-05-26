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
			printf("�߸��� �ð��� �Է��߽��ϴ�.");
			return false;
		}

		hour = h;
		return true;
	}
	bool SetMinute(int m)
	{
		if (m > 60 || m < 0)
		{
			printf("�߸��� ���� �Է��߽��ϴ�.");
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
	//head�� Index�� 0�̴�.
	bool Reserve(int index)
	{
		vector<int> ticketIndex = LoadTicket();

		if (SeatNum < 0)
		{
			cout << "�ڸ��� �����ϴ�." << endl;
			return false;
		}

		for (int i = 0; i < (signed)ticketIndex.size(); i++)
		{
			if (ticketIndex[i] == index)
			{
				cout << "�̹� ������ �����Դϴ�." << endl;
				return false;
			}
		}

		ticketIndex.push_back(index);

		bool isSaved = SaveTicket(ticketIndex);
		if (isSaved == false)
		{
			cout << "���ſ� �����߽��ϴ�..." << endl;
			return false;
		}

		cout << "���ŵǾ����ϴ�." << endl << endl;
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
			cout << "���Ű� ��ҵǾ����ϴ�." << endl << endl;
			SeatNum++;

			SaveTicket(TicketIndex);

			return true;
		}
		else
		{
			cout << "�ش� ���� ���� ������ ã�� �� �����ϴ�." << endl;
			return false;
		}

	}

	vector<int> LoadTicket()
	{
		vector<int> TicketIndex;

		ifstream ticketinList("TicketList.txt");
		if (!ticketinList)
		{
			cout << "���� ã�� ����" << endl;
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
			cout << "���� ã�� ����" << endl;
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
		cout << "���� ã�� ����" << endl;
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

		//Hour �Ҵ�
		while (line[index] != ':')
		{
			hour.push_back(line[index]);
			index++;
		}
		index++;

		//minute �Ҵ�
		while (line[index] != ' ')
		{
			minute.push_back(line[index]);
			index++;
		}
		index++;


		//departure �Ҵ�
		while (line[index] != ' ')
		{
			departure.push_back(line[index]);
			index++;
		}
		index += 4;


		//arrival �Ҵ�
		while (line[index] != ' ')
		{
			arrival.push_back(line[index]);
			index++;
		}
		index++;

		//TrainName �Ҵ�
		while (line[index] != ' ')
		{
			trainName.push_back(line[index]);
			index++;
		}
		index++;

		//SeatNum �Ҵ�
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
		cout << "���� ã�� ����" << endl;
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
	cout << "�����Ͻðڽ��ϱ�? (yes: 1, no : 0) : ";
	cin >> optionIndex;

	switch (optionIndex)
	{
	case 1:
		break;
	case 0:
	default:
		cout << "��ҵǾ����ϴ�.";
		return;
	}

	int trainNum = -1;
	while (1)
	{
		cout << "������ ������ ��ȣ�� �Է����ּ���. : ";
		cin >> trainNum;
		trainNum--;

		if (trainNum >= (signed)wishTrain.size() || trainNum < 0)
			cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է����ּ���." << endl;
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
	cout << "---------------���� ����---------------" << endl << endl;

	cout << "������� �������� �Է����ּ���. (�ڷΰ���� -1)" << endl;
	cin >> departure;
	if (departure == "-1")
	{
		cout << "�޴��� ���ư��ϴ�..." << endl;
		return TargetTrains;
	}
	cin >> arrival;

	if (arrival == "-1")
	{
		cout << "�޴��� ���ư��ϴ�..." << endl;
		return TargetTrains;
	}


	while (isOkay == false)
	{
		cout << "���ϴ� �ð��� �Է����ּ���. ex) 13 50 (�ڷΰ���� -1)" << endl;
		cin >> h;
		if (h == -1)
		{
			cout << "�޴��� ���ư��ϴ�..." << endl;
			return TargetTrains;
		}

		cin >> m;
		if (m == -1)
		{
			cout << "�޴��� ���ư��ϴ�..." << endl;
			return TargetTrains;
		}

		isOkay = (wishTime.SetHour(h) && wishTime.SetMinute(m));

		if (isOkay == false)
		{
			cout << "�߸��� �ð��� �Է��߽��ϴ�. �ٽ� �Է����ּ���." << endl;
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
		cout << "���ǿ� �´� ������ �����ϴ�..." << endl;
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
	cout << "---------------���� ���---------------" << endl << endl;

	while (thisTrain != NULL)
	{
		cout << "No." << trainNum << " ";
		thisTrain->PrintTrainInfo();

		trainNum++;
		thisTrain = thisTrain->next;
	}

	cout << "------------------------------------------------------------------------------------------------------------------" << endl;

	int optionIndex = 0;
	cout << "�����Ͻðڽ��ϱ�? (yes:1, no:0) : ";
	cin >> optionIndex;

	int targettrainNum = -1;

	switch (optionIndex)
	{
	case 1:
		cout << "�����Ϸ��� ���� ��ȣ�� �Է����ּ���. : ";
		cin >> targettrainNum;
		break;
	default:
		cout << "�޴��� ���ư��ϴ�..." << endl;
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
		cout << "���� ã�� ����" << endl;
		return;
	}

	vector<int> TicketIndex;
	string line;
	while (getline(ticketinList, line))
	{
		if (EOF && line == "")
		{
			cout << "���ų����� �����ϴ�." << endl;
			return;
		}

		TicketIndex.push_back(stoi(line));
	}

	system("cls");
	cout << "---------------���� ����---------------" << endl << endl;

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
		cout << "���ŵ� ������ �����ϴ�." << endl;
		return;
	}

	int optionIndex = 0;
	cout << "���Ÿ� ����Ͻðڽ��ϱ�?(yes:1, no:0) : ";
	cin >> optionIndex;

	switch (optionIndex)
	{
	case 1:
		cout << "����� ������ ��ȣ�� �Է����ּ���. : ";
		cin >> optionIndex;
		break;
	case 0:
	default:
		cout << "���θ޴��� ���ư��ϴ�..." << endl << endl;
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

	cout << "0. ����" << endl
		<< "1. ���� ����" << endl
		<< "2. ��ü ���� ���" << endl
		<< "3. ���� ���� ����" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "���� �� ���� �Է��ϼ���. : ";
	cin >> optionIndex;

	cout << endl;

	switch (optionIndex)
	{
	case 0:
		cout << "�����մϴ�." << endl;
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
		cout << "�߸��� �ε������Դϴ�." << endl;
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
