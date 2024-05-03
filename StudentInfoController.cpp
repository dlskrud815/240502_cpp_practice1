#include "StudentInfoController.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;


int countSbjNum(int selectSbj)
{
	//정수 자리수 세기
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

		if (stdInfoVec[i].stdBirth.size() != 8) //생년월일 여덟자리가 아닐 경우
		{
			cout << endl << "* 생년월일 여덟자리를 입력해주세요." << endl
				<< "[재입력]" << endl;
			cin >> stdInfoVec[i].stdBirth;
		}
		else //생년월일이 여덟자리 일 경우
		{	//추가 필요 ** 생년월일이 날짜 형식이 맞는지 ex) 14월 90일 등 입력 불가
			for (int j = 0; j < stdInfoVec[i].stdBirth.size(); j++) //입력한 생년월일에 대해
			{
				if (!isdigit(stdInfoVec[i].stdBirth[j])) //문자가 검출될 경우
				{
					cout << endl << "* 생년월일을 숫자로 입력해주세요." << endl
						<< "[재입력]" << endl;
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

void CalStudentAgeAndInput(vector<stdInfo>& stdInfoVec, int i)//생년월일 이용 나이 계산
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

	//년 나이 계산
	age = c_year - year;
	stdInfoVec[i].stdKoreanAge = age + 1;

	//만나이 계산
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
	case 1: //1) 전체 학생 정보 출력
		for (int i = 0; i < stdInfoVec.size(); i++)
		{
			PrintStudentInfo(stdInfoVec, i, sbjInfoVec);
		}
		break;
	case 2: //2) 특정 학생 정보 출력
		cout << endl << "학생 이름: ";
		cin >> stdName;

		for (int i = 0; i < stdInfoVec.size(); i++)
		{
			if (stdInfoVec[i].stdName == stdName) //벡터 내 검색 이름 존재
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
	case 1: //1) 만 나이 평균 출력
		cout << endl << "학생들의 평균 만 나이는.. "
			<< CalStudentAgeAverage(stdInfoVec, useKoreanAge = false) << "세" << endl;
		break;
	case 2: //2) 년 나이 평균 출력
		cout << endl << "학생들의 평균 년 나이는.. "
			<< CalStudentAgeAverage(stdInfoVec, useKoreanAge = true) << "세" << endl;
		break;
	}
}

void SelectOption_PrintEarlyBirthday(int option, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec)
{
	bool useYear;

	switch (option)
	{
	case 1: //1) 생일이 가장 빠른 학생 정보 출력
		cout << endl << "생일이 가장 빠른 학생은.. " << endl;
		PrintEarlyBirthStudentInfo(stdInfoVec, useYear = false, sbjInfoVec);
		break;
	case 2: //2) 나이가 가장 많은 학생 정보 출력
		cout << endl << "나이가 가장 많은 학생은.. " << endl;
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
				cout << endl << "이름은.. ";
				cin >> stdInfoVec[i].stdName;
				break;
			case 2:
				cout << endl << "생년월일은.. ";
				cin >> stdInfoVec[i].stdBirth;

				//생년월일 자리수 및 숫자 여부 확인
				CheckBirthInput(stdInfoVec, i);
				//나이 계산 후 벡터에 저장
				CalStudentAgeAndInput(stdInfoVec, i);

				break;
			}
		}
	}
}


void PrintStudentInfo(vector<stdInfo> stdInfoVec, int i, vector<sbjInfo> sbjInfoVec)
{
	cout << endl << "------------- " << stdInfoVec[i].stdNo << "번 학생" << endl
		<< "이름: " << stdInfoVec[i].stdName << endl
		<< "년나이: " << stdInfoVec[i].stdKoreanAge << endl
		<< "만나이: " << stdInfoVec[i].stdAge << endl
		<< "생년월일: " << stdInfoVec[i].stdBirth << endl;

	if (sbjInfoVec[i].sbjName.size() != 0)
	{
		for (int j = 0; j < sbjInfoVec[i].sbjName.size(); j++)
		{
			cout << endl << "과목명: " << sbjInfoVec[i].sbjName[j] << endl
				<< "과목 점수: " << sbjInfoVec[i].sbjScore[j] << endl;
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
	//과목별 평균 & 최고점 & 해당 학생 번호
	for (int i = 0; i < sbjInfoVec[0].sbjName.size(); i++) //과목 개수만큼
	{
		float scoreSum = 0, maxScore = 0, maxStdNo = 0;
		for (int j = 0; j < stdInfoVec.size(); j++) //학생 수만큼
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
	//cout << "과목별 평균 & 최고점 & 해당 학생 확인" << endl;
	for (int i = 0; i < stdScoreState.size(); i++)
	{
		cout << endl << "******************** " << sbjInfoVec[0].sbjName[i]
			<< endl << "과목 평균: " << stdScoreState[i].stdAvgScore
			<< endl << "최고점: " << stdScoreState[i].stdMaxScore
			<< endl << endl << "[학생 정보]";

		PrintStudentInfo(stdInfoVec, stdScoreState[i].stdNoMaxScore - 1, sbjInfoVec);
	}
}

void PrintStudentScore(vector<totalRank> stdTotalRank, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec)
{
	int stdNo;

	cout << endl << "성적을 확인하고자 하는 학생 번호: ";
	cin >> stdNo;

	//추가 필요 ** 학생 번호가 아닌 다른 걸 입력받았을 때

	for (int i = 0; i < stdInfoVec.size(); i++)
	{
		if (stdNo == stdInfoVec[i].stdNo)
		{
			cout << endl << "------------ " << stdInfoVec[i].stdNo << "번 학생" << endl
				<< "이름: " << stdInfoVec[i].stdName << endl
				<< "전과목 평균: " << stdTotalRank[i].stdTotalAvg << endl
				<< "전체 석차: " << ReturnTotalRank(stdTotalRank, i) << endl;
		}
	}
}

vector<totalRank> SaveTotalScore(vector<totalRank> stdTotalRank, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec)
{
	//각 학생별 전체 성적 평균
	for (int i = 0; i < stdInfoVec.size(); i++)
	{
		float scoreSum = 0;

		for (int j = 0; j < sbjInfoVec[i].sbjScore.size(); j++)
		{
			scoreSum += sbjInfoVec[i].sbjScore[j];
		}
		stdTotalRank[i].stdTotalAvg = scoreSum / sbjInfoVec[i].sbjScore.size();
	}

	//각 학생 전체 석차
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