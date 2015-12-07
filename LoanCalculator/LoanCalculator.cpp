// LoanCalculator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#include "BaseLoanCalculator.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Loan Calculator..." << endl;

	int payMth = 2;
	enum PayMethod payMethod;
	int loanYears = 20, loanPrincipal = 60;
	double loanAnnualInterestRate = 4.5;

	cout << "Please tell me something first" << endl;

PayMethodSelect:
	cout << "[1]等额本息 [2]等额本金 : ";
	cin >> payMth;

	if (1 == payMth)
	{
		payMethod = PAYMETHOD_EQUAL_PRINCIPAL_AND_INTEREST;
	}
	else if (2 == payMth)
	{
		payMethod = PAYMETHOD_EQUAL_PRINCIPAL;
	}
	else
	{
		cout << "Wrong answer, try again"<<endl;
		goto PayMethodSelect;
	}

LoanYearsSelect:
	cout << "想贷款多少年 : ";
	cin >> loanYears;
	if (loanYears <= 0 || loanYears > 30)	//最长30年
	{
		cout << "Wrong answer, try again" << endl;
		goto LoanYearsSelect;
	}

LoanPrincipalSelect:
	cout << "公积金想贷款多少钱(万) : ";
	cin >> loanPrincipal;
	if (loanPrincipal <= 0 || loanPrincipal > 80)	//最多80w
	{
		cout << "Wrong answer, try again" << endl;
		goto LoanPrincipalSelect;
	}
	loanPrincipal *= 10000;

loanAnnualInterestRateSelect:
	cout << "公积金贷款利率(%) : ";
	cin >> loanAnnualInterestRate;
	if (loanAnnualInterestRate < 0)
	{
		cout << "Wrong answer, try again" << endl;
		goto loanAnnualInterestRateSelect;
	}
	loanAnnualInterestRate /= 100;

NewRateChangeSelect:
	cout << "是否有利率调整？ [Y/N] :";
	char ifRateChange = 'N';
	cin >> ifRateChange;
	RateChange rc;
	if ('Y' == ifRateChange)
	{
		cout << "新利率其实月份 [2-" << loanYears * 12 << "] :";
		cin >> rc.m_FromMonth;
		cout << "新利率 :";
		cin >> rc.m_NewRate;

		if (rc.m_FromMonth < 2 || rc.m_FromMonth > loanYears * 12 || rc.m_NewRate < 0)
		{
			cout << "Wrong answer, try again" << endl;
			goto NewRateChangeSelect;
		}
	}

	//计算
	BaseLoanCalculator *lc = new BaseLoanCalculator(payMethod, loanYears, loanPrincipal, loanAnnualInterestRate);
	lc->AddAunnalInterestRateChange(rc.m_FromMonth, rc.m_NewRate/100);
	lc->Calculate();

	cout << "Press any Key to continue..." << endl;
	char finish;
	cin >> finish;

	delete lc;
	lc = NULL;

	return 0;
}

