#include "StudentInfoController.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;


int countSbjNum(int selectSbj)
{
	//���� �ڸ��� ����
	int n, cnt = 0;

	n = selectSbj;
	while (n != 0)
	{
		n = n / 10;
		++cnt;
	}

	return cnt;
}

void CheckBirthInput(vector <stdInfo>& stdInfoVec, int i)
{
	while (1)
	{
		bool birthCheck = true;

		if (stdInfoVec[i].stdBirth.size() != 8) //������� �����ڸ��� �ƴ� ���
		{
			cout << endl << "* ������� �����ڸ��� �Է����ּ���." << endl
				<< "[���Է�]" << endl;
			cin >> stdInfoVec[i].stdBirth;
		}
		else //��������� �����ڸ� �� ���
		{	//�߰� �ʿ� ** ��������� ��¥ ������ �´��� ex) 14�� 90�� �� �Է� �Ұ�
			for (int j = 0; j < stdInfoVec[i].stdBirth.size(); j++) //�Է��� ������Ͽ� ����
			{
				if (!isdigit(stdInfoVec[i].stdBirth[j])) //���ڰ� ����� ���
				{
					cout << endl << "* ��������� ���ڷ� �Է����ּ���." << endl
						<< "[���Է�]" << endl;
					cin >> stdInfoVec[i].stdBirth;

					birthCheck = false;
					break;
				}
			}
			if (birthCheck == true)
			{
				break;
			}
		}
	}
}

void CalStudentAgeAndInput(vector<stdInfo>& stdInfoVec, int i)//������� �̿� ���� ���
{
	time_t timer = time(NULL);
	struct tm t;
	localtime_s(&t, &timer);
	int age, year, month, date, c_year, c_month, c_date;

	year = stoi(stdInfoVec[i].stdBirth.substr(0, 4));
	month = stoi(stdInfoVec[i].stdBirth.substr(4, 2));
	date = stoi(stdInfoVec[i].stdBirth.substr(6, 2));

	c_year = t.tm_year + 1900;
	c_month = t.tm_mon + 1;
	c_date = t.tm_mday;

	//�� ���� ���
	age = c_year - year;
	stdInfoVec[i].stdKoreanAge = age + 1;

	//������ ���
	if (month - c_month > 0)
	{
		age = age - 1;
	}
	else if (month - c_month == 0)
	{
		if (date - c_date > 0)
		{
			age = age - 1;
		}
	}

	stdInfoVec[i].stdAge = age;
}


void SelectOption_PrintStudentInfo(int option, vector <stdInfo> stdInfoVec, vector<sbjInfo> sbjInfoVec)
{
	string stdName;

	switch (option)
	{
	case 1: //1) ��ü �л� ���� ���
		for (int i = 0; i < stdInfoVec.size(); i++)
		{
			PrintStudentInfo(stdInfoVec, i, sbjInfoVec);
		}
		break;
	case 2: //2) Ư�� �л� ���� ���
		cout << endl << "�л� �̸�: ";
		cin >> stdName;

		for (int i = 0; i < stdInfoVec.size(); i++)
		{
			if (stdInfoVec[i].stdName == stdName) //���� �� �˻� �̸� ����
			{
				PrintStudentInfo(stdInfoVec, i, sbjInfoVec);
			}
		}
		break;
	}
}

void SelectOption_PrintStudentAgeAverage(int option, vector <stdInfo> stdInfoVec)
{
	bool useKoreanAge;

	switch (option)
	{
	case 1: //1) �� ���� ��� ���
		cout << endl << "�л����� ��� �� ���̴�.. "
			<< CalStudentAgeAverage(stdInfoVec, useKoreanAge = false) << "��" << endl;
		break;
	case 2: //2) �� ���� ��� ���
		cout << endl << "�л����� ��� �� ���̴�.. "
			<< CalStudentAgeAverage(stdInfoVec, useKoreanAge = true) << "��" << endl;
		break;
	}
}

void SelectOption_PrintEarlyBirthday(int option, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec)
{
	bool useYear;

	switch (option)
	{
	case 1: //1) ������ ���� ���� �л� ���� ���
		cout << endl << "������ ���� ���� �л���.. " << endl;
		PrintEarlyBirthStudentInfo(stdInfoVec, useYear = false, sbjInfoVec);
		break;
	case 2: //2) ���̰� ���� ���� �л� ���� ���
		cout << endl << "���̰� ���� ���� �л���.. " << endl;
		PrintEarlyBirthStudentInfo(stdInfoVec, useYear = true, sbjInfoVec);
		break;
	}
}


void SelectOption_EditStudentInfo(int option, int editStdNum, vector <stdInfo>& stdInfoVec)
{
	for (int i = 0; i < stdInfoVec.size(); i++)
	{
		if (stdInfoVec[i].stdNo == editStdNum)
		{
			switch (option)
			{
			case 1:
				cout << endl << "�̸���.. ";
				cin >> stdInfoVec[i].stdName;
				break;
			case 2:
				cout << endl << "���������.. ";
				cin >> stdInfoVec[i].stdBirth;

				//������� �ڸ��� �� ���� ���� Ȯ��
				CheckBirthInput(stdInfoVec, i);
				//���� ��� �� ���Ϳ� ����
				CalStudentAgeAndInput(stdInfoVec, i);

				break;
			}
		}
	}
}


void PrintStudentInfo(vector<stdInfo> stdInfoVec, int i, vector<sbjInfo> sbjInfoVec)
{
	cout << endl << "------------- " << stdInfoVec[i].stdNo << "�� �л�" << endl
		<< "�̸�: " << stdInfoVec[i].stdName << endl
		<< "�⳪��: " << stdInfoVec[i].stdKoreanAge << endl
		<< "������: " << stdInfoVec[i].stdAge << endl
		<< "�������: " << stdInfoVec[i].stdBirth << endl;

	if (sbjInfoVec[i].sbjName.size() != 0)
	{
		for (int j = 0; j < sbjInfoVec[i].sbjName.size(); j++)
		{
			cout << endl << "�����: " << sbjInfoVec[i].sbjName[j] << endl
				<< "���� ����: " << sbjInfoVec[i].sbjScore[j] << endl;
		}
	}
}


float CalStudentAgeAverage(vector<stdInfo> stdInfoVec, bool useKoreanAge)
{
	float ageSum = 0;

	for (int i = 0; i < stdInfoVec.size(); i++)
	{
		ageSum += useKoreanAge ? stdInfoVec[i].stdKoreanAge : stdInfoVec[i].stdAge;
	}

	return ageSum / stdInfoVec.size();
}


void PrintEarlyBirthStudentInfo(vector<stdInfo> stdInfoVec, bool useYear, vector <sbjInfo> sbjInfoVec)
{
	int birth, minBirth = useYear ? 99991231 : 1231;

	for (int i = 0; i < stdInfoVec.size(); i++)
	{
		birth = useYear ? stoi(stdInfoVec[i].stdBirth) : stoi(stdInfoVec[i].stdBirth.substr(4));

		if (birth < minBirth)
		{
			minBirth = birth;
		}
	}

	for (int i = 0; i < stdInfoVec.size(); i++)
	{
		birth = useYear ? stoi(stdInfoVec[i].stdBirth) : stoi(stdInfoVec[i].stdBirth.substr(4));

		if (birth == minBirth)
		{
			PrintStudentInfo(stdInfoVec, i, sbjInfoVec);
		}
	}
}

vector<scoreState> SaveSubjectStateAll(vector<scoreState> stdScoreState, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec)
{
	//���� ��� & �ְ��� & �ش� �л� ��ȣ
	for (int i = 0; i < sbjInfoVec[0].sbjName.size(); i++) //���� ������ŭ
	{
		float scoreSum = 0, maxScore = 0, maxStdNo = 0;
		for (int j = 0; j < stdInfoVec.size(); j++) //�л� ����ŭ
		{
			scoreSum += sbjInfoVec[j].sbjScore[i];

			if (maxScore <= sbjInfoVec[j].sbjScore[i])
			{
				maxScore = sbjInfoVec[j].sbjScore[i];
				maxStdNo = j + 1;
			}
		}
		stdScoreState[i].stdAvgScore = scoreSum / stdInfoVec.size();
		stdScoreState[i].stdNoMaxScore = maxStdNo;
		stdScoreState[i].stdMaxScore = maxScore;
	}

	return stdScoreState;
}

void PrintSubjectStateAll(vector<scoreState> stdScoreState, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec)
{
	//cout << "���� ��� & �ְ��� & �ش� �л� Ȯ��" << endl;
	for (int i = 0; i < stdScoreState.size(); i++)
	{
		cout << endl << "******************** " << sbjInfoVec[0].sbjName[i]
			<< endl << "���� ���: " << stdScoreState[i].stdAvgScore
			<< endl << "�ְ���: " << stdScoreState[i].stdMaxScore
			<< endl << endl << "[�л� ����]";

		PrintStudentInfo(stdInfoVec, stdScoreState[i].stdNoMaxScore - 1, sbjInfoVec);
	}
}

void PrintStudentScore(vector<totalRank> stdTotalRank, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec)
{
	int stdNo;

	cout << endl << "������ Ȯ���ϰ��� �ϴ� �л� ��ȣ: ";
	cin >> stdNo;

	//�߰� �ʿ� ** �л� ��ȣ�� �ƴ� �ٸ� �� �Է¹޾��� ��

	for (int i = 0; i < stdInfoVec.size(); i++)
	{
		if (stdNo == stdInfoVec[i].stdNo)
		{
			cout << endl << "------------ " << stdInfoVec[i].stdNo << "�� �л�" << endl
				<< "�̸�: " << stdInfoVec[i].stdName << endl
				<< "������ ���: " << stdTotalRank[i].stdTotalAvg << endl
				<< "��ü ����: " << ReturnTotalRank(stdTotalRank, i) << endl;
		}
	}
}

vector<totalRank> SaveTotalScore(vector<totalRank> stdTotalRank, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec)
{
	//�� �л��� ��ü ���� ���
	for (int i = 0; i < stdInfoVec.size(); i++)
	{
		float scoreSum = 0;

		for (int j = 0; j < sbjInfoVec[i].sbjScore.size(); j++)
		{
			scoreSum += sbjInfoVec[i].sbjScore[j];
		}
		stdTotalRank[i].stdTotalAvg = scoreSum / sbjInfoVec[i].sbjScore.size();
	}

	//�� �л� ��ü ����
	return stdTotalRank;
}

int ReturnTotalRank(vector<totalRank> stdTotalRank, int i)
{
	int cnt = 0;
	float cmpScore;

	for (int j = 0; j < stdTotalRank.size(); j++)
	{
		cmpScore = stdTotalRank[j].stdTotalAvg;

		if (cmpScore >= stdTotalRank[i].stdTotalAvg)
		{
			cnt++;
		}
	}

	return cnt;
}