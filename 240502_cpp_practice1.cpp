#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <cmath>

#include "StudentInfoController.h" //함수 헤더파일

using namespace std;


int main()
{
	int stdNum = 0, option1, option2, editStdNum, sbjNum = 0, selectSbj = 0;
	char yesNo;
	bool confirm;

	vector <stdInfo> stdInfoVec; //학생 정보 구조체 벡터
	vector <sbjInfo> sbjInfoVec; //과목 점수 구조체 벡터
	vector <string> sbjName;

	cout << "** c++ 종합 실습 **" << endl << endl;

	//1. 사용자에게 몇 명의 학생을 입력할 것인지 묻기
	cout << "몇 명의 학생 정보를 입력? ";
	cin >> stdNum;

	stdInfoVec.resize(stdNum); //학생 정보 구조체 벡터
	sbjInfoVec.resize(stdNum);

	// 사용자에게 과목을 입력 받을 것인지 
	cout << endl << "학생 점수도 입력? (y or n) ";
	cin >> yesNo;
	yesNo == 'n' ? confirm = false : confirm = true;

	if (confirm)
	{
		cout << endl << "몇 개의 과목 점수를 입력? ";
		cin >> sbjNum;
		sbjName.resize(sbjNum);

		for (int i = 0; i < sbjNum; i++)
		{
			cout << endl << "제 " << i + 1 << " 과목명은? ";
			cin >> sbjName[i];
		}
	}

	//2. 학생 수만큼 "이름 나이 생일" 순서로 한 번에 입력 받기
	//나이를 입력 받지 않고 생년월일로 입력 받은 후 계산
	for (int i = 0; i < stdNum; i++)
	{
		if (i == 0)
		{
			cout << endl << "[입력 예시]" << endl
				<< "0번 학생" << endl
				<< "이름: 이나경" << endl
				<< "생년월일: 20010815" << endl;
		}

		//학생 번호 자동 순차 부여
		stdInfoVec[i].stdNo = i + 1;

		//학생 이름 입력
		cout << endl << i + 1 << "번 학생" << endl << "이름: ";
		cin >> stdInfoVec[i].stdName;

		//학생 생년월일 여덟자리 입력
		cout << "생년월일: ";
		cin >> stdInfoVec[i].stdBirth;

		//생년월일 자리수 및 숫자 여부 확인
		CheckBirthInput(stdInfoVec, i);

		//나이 계산 후 벡터에 저장
		CalStudentAgeAndInput(stdInfoVec, i);

		//과목 성적 입력
		// 추가 필요 * * y or n에서 n을 선택하면 아래 항목 안 뜸! 모든 성적 0으로 할 것?
		// 입력을 안 한 성적은 0으로 처리 -> 정보 수정부에서 정보를 수정할 수 있도록!
		cout << endl << "* 다음 중 점수를 입력할 과목 번호를 선택해주세요 *" << endl;
		//과목 보기 출력
		for (int j = 0; j < sbjName.size(); j++)
		{
			cout << j + 1 << ") " << sbjName[j] << endl;
		}

		if (i == 0) //추가 필요 ** 나중에는 그냥 루프 돌도록 설정
		{
			cout << endl << "[입력예시]" << endl
				<< "1, 2, 3 과목을 선택할 경우 " << endl
				// 추가 필요 ** 10개 이상도 상관 없는 코드로 수정
				<< "입력: 123" << endl << endl; //설마 과목이 10개는 안 되겠징 

			cout << "입력: ";
			cin >> selectSbj;

			while (1)
			{
				// 추가 필요 ** 
				if (countSbjNum(selectSbj) != sbjName.size() || countSbjNum(selectSbj) >= 10)
				{
					cout << endl << "* 과목의 개수가 범위를 벗어납니다." << endl
						<< "[재입력]" << endl << "입력: ";
					cin >> selectSbj;
				}
				else break;
			}
		}

		sbjInfoVec[i].sbjName.resize(sbjName.size());
		sbjInfoVec[i].sbjScore.resize(sbjName.size());

		for (int j = 0; j < sbjName.size(); j++)
		{
			cout << endl << "과목 번호: " << j + 1 << endl
				<< "과목명: " << sbjName[j] << endl
				<< "과목 점수: ";
			sbjInfoVec[i].sbjName[j] = sbjName[j];
			cin >> sbjInfoVec[i].sbjScore[j];
		}
	}

	vector<scoreState> stdScoreState(sbjInfoVec[0].sbjName.size());
	vector<totalRank>  stdTotalRank(stdInfoVec.size());

	//3. 1) 학생 정보 출력, 2) 평균 나이, 3) 가장 빠른 생일, 4) 프로그램 종료 네 가지 기능 모두 구현
	//동명이인이나 같은 생년월일 등 조회 조건이 같을 경우 모두 출력하도록 함
	while (1)
	{
		cout << endl << "[옵션]" << endl
			<< "1) 학생 정보 , 2) 평균 나이, 3) 가장 빠른 생일, 4) 프로그램 종료, 0) 입력 정보 수정, 5) 과목 현황 정보, 6) 학생 성적 확인" << endl;
		cin >> option1;

		switch (option1)
		{
		case 1: //1) 학생 정보
			cout << endl << "1) 전체 학생 정보 출력, 2) 특정 학생 정보 출력" << endl;
			cin >> option2;
			SelectOption_PrintStudentInfo(option2, stdInfoVec, sbjInfoVec);
			break;
		case 2: //2) 평균 나이
			cout << endl << "1) 만 나이 평균 출력, 2) 년 나이 평균 출력" << endl;
			cin >> option2;
			SelectOption_PrintStudentAgeAverage(option2, stdInfoVec);
			break;
		case 3: //3) 가장 빠른 생일
			cout << endl << "1) 생일이 가장 빠른 학생 정보 출력, 2) 나이가 가장 많은 학생 정보 출력" << endl;
			cin >> option2;
			SelectOption_PrintEarlyBirthday(option2, stdInfoVec, sbjInfoVec);
			break;
		case 4: //4) 프로그램 종료
			return 0;
		case 5: //5) 과목 현황 정보
			PrintSubjectStateAll(SaveSubjectStateAll(stdScoreState, stdInfoVec, sbjInfoVec), stdInfoVec, sbjInfoVec);
			break;
		case 6: //6) 학생 총괄 성적
			PrintStudentScore(SaveTotalScore(stdTotalRank, stdInfoVec, sbjInfoVec), stdInfoVec, sbjInfoVec);
			break;
		case 0: //0) 입력 값 수정
			cout << endl << "정보 수정을 원하는 학생 번호는.. ";
			cin >> editStdNum;

			while (1)
			{
				if (editStdNum <= 0 || editStdNum > stdInfoVec.size())
				{
					cout << endl << "* 해당 번호의 학생은 존재하지 않습니다. " << endl
						<< endl << "[재입력]" << endl
						<< "정보 수정을 원하는 학생 번호는.. ";
					cin >> editStdNum;
				}
				else break;
			}

			cout << endl << "1) 이름 수정, 2) 생년월일 수정" << endl;
			cin >> option2;
			SelectOption_EditStudentInfo(option2, editStdNum, stdInfoVec);
		}
	}

	return 0;
}
