// LoanCalculator.cpp : �������̨Ӧ�ó������ڵ㡣
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
	cout << "[1]�ȶϢ [2]�ȶ�� : ";
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
	cout << "���������� : ";
	cin >> loanYears;
	if (loanYears <= 0 || loanYears > 30)	//�30��
	{
		cout << "Wrong answer, try again" << endl;
		goto LoanYearsSelect;
	}

LoanPrincipalSelect:
	cout << "��������������Ǯ(��) : ";
	cin >> loanPrincipal;
	if (loanPrincipal <= 0 || loanPrincipal > 80)	//���80w
	{
		cout << "Wrong answer, try again" << endl;
		goto LoanPrincipalSelect;
	}
	loanPrincipal *= 10000;

loanAnnualInterestRateSelect:
	cout << "�������������(%) : ";
	cin >> loanAnnualInterestRate;
	if (loanAnnualInterestRate < 0)
	{
		cout << "Wrong answer, try again" << endl;
		goto loanAnnualInterestRateSelect;
	}
	loanAnnualInterestRate /= 100;

NewRateChangeSelect:
	cout << "�Ƿ������ʵ����� [Y/N] :";
	char ifRateChange = 'N';
	cin >> ifRateChange;
	RateChange rc;
	if ('Y' == ifRateChange)
	{
		cout << "��������ʵ�·� [2-" << loanYears * 12 << "] :";
		cin >> rc.m_FromMonth;
		cout << "������ :";
		cin >> rc.m_NewRate;

		if (rc.m_FromMonth < 2 || rc.m_FromMonth > loanYears * 12 || rc.m_NewRate < 0)
		{
			cout << "Wrong answer, try again" << endl;
			goto NewRateChangeSelect;
		}
	}

	//����
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

