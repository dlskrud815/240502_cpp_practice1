#pragma once

#include <vector>
#include <string>

using namespace std;


//�л� ���� ����ü
struct stdInfo
{
	int stdNo, stdAge, stdKoreanAge;
	string stdName, stdBirth;

	//�ʱ�ȭ
	stdInfo() : stdNo(0), stdAge(0), stdKoreanAge(0) {}
};

//���� ���� ����ü
struct sbjInfo
{
	vector <float> sbjScore;
	vector <string> sbjName;
};

//���� ��Ȳ Ȯ�ο� ����ü
struct scoreState
{
	float stdAvgScore;
	float stdMaxScore;
	int stdNoMaxScore;
};

//�л��� ��ü ���� ��� �� ���� Ȯ�ο� ����ü
struct totalRank
{
	float stdTotalAvg;
	int stdTotalRnk;
};


int countSbjNum(int selectSbj);

void CheckBirthInput(vector <stdInfo>& stdInfoVec, int i);
void CalStudentAgeAndInput(vector<stdInfo>& stdInfoVec, int i);

void SelectOption_PrintStudentInfo(int option, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec);
void SelectOption_PrintStudentAgeAverage(int option, vector <stdInfo> stdInfoVec);
void SelectOption_PrintEarlyBirthday(int option, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec);
void SelectOption_EditStudentInfo(int option, int editStdNum, vector <stdInfo>& stdInfoVec);

void PrintStudentInfo(vector<stdInfo> stdInfoVec, int i, vector <sbjInfo> sbjInfoVec);
void PrintSubjectStateAll(vector<scoreState> stdScoreState, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec);
void PrintStudentScore(vector<totalRank> stdTotalRank, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec);

vector<scoreState> SaveSubjectStateAll(vector<scoreState> stdScoreState, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec);
vector<totalRank> SaveTotalScore(vector<totalRank>stdTotalRank, vector <stdInfo> stdInfoVec, vector <sbjInfo> sbjInfoVec);
int ReturnTotalRank(vector<totalRank> stdTotalRank, int i);

float CalStudentAgeAverage(vector<stdInfo> stdInfoVec, bool useKoreanAge);

void PrintEarlyBirthStudentInfo(vector<stdInfo> stdInfoVec, bool useYear, vector <sbjInfo> sbjInfoVec);
