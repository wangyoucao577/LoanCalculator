#include "stdafx.h"
#include "BaseLoanCalculator.h"

#include <iostream>
#include <iomanip>
using namespace std;


BaseLoanCalculator::BaseLoanCalculator(PayMethod payMethod, int loanYears, int loanPrincipal, double loanAnnualInterestRate)
{
	m_payMethod = payMethod;
	m_loanYears = loanYears;
	m_loanPrincipal = loanPrincipal;
	m_loanAnnualInterestRate = loanAnnualInterestRate;

	for (int i = 0; i < MAX_RATE_CHANGE; ++i)
	{
		m_rateChangeArray[i].m_FromMonth = 0;
		m_rateChangeArray[i].m_NewRate = 0.0;
	}
}


BaseLoanCalculator::~BaseLoanCalculator()
{
}

void BaseLoanCalculator::Calculate()
{
	int loanMonths = m_loanYears * m_MONTHS_PER_YEAR;
	double loanMonthInterestRate = m_loanAnnualInterestRate / m_MONTHS_PER_YEAR;

	double currPrincipal = 0;	//当月应还本金
	double currInterest = 0;	//当月应还利息
	double paidPrincipal = 0;	//已付本金总额
	double paidInterest = 0;	//已付利息总额
	double remainPrincipal = m_loanPrincipal;	//剩余本金总额

	if (m_payMethod == PAYMETHOD_EQUAL_PRINCIPAL)
	{
		currPrincipal = (double)m_loanPrincipal / loanMonths;	//等额本金时，每月本金额度相同
	}

	//确认是否有利率变更
	int rateChangeIndex = -1;
	rateChangeIndex = FindNextRateChange(rateChangeIndex);
	
	cout << "月 月利率       当月本金/当月利息      当月应还      已还利息      剩余本金" << endl;

	for (int i = 0; i < loanMonths; ++i)
	{
		if (m_payMethod == PAYMETHOD_EQUAL_PRINCIPAL)
		{
			//等额本金

			if (-1 != rateChangeIndex && i + 1 == m_rateChangeArray[rateChangeIndex].m_FromMonth)
			{
				//利率变更
				loanMonthInterestRate = m_rateChangeArray[rateChangeIndex].m_NewRate / m_MONTHS_PER_YEAR;
				rateChangeIndex = FindNextRateChange(rateChangeIndex);
			}

			currInterest = remainPrincipal * loanMonthInterestRate;
			remainPrincipal -= currPrincipal;
			paidPrincipal += currPrincipal;
			paidInterest += currInterest;

			cout << setw(3) << i + 1 << setw(10) << loanMonthInterestRate*100 << setw(10) << currPrincipal << "/" << setw(10) << currInterest << setw(10) << currPrincipal + currInterest
				<< setw(15) << paidInterest << setw(15) << remainPrincipal << endl;
		}
		else
		{
			//TODO: 等额本息
			
		}
	}
}

bool BaseLoanCalculator::AddAunnalInterestRateChange(int fromMoth, double newRate)
{
	for (int i = 0; i < MAX_RATE_CHANGE; ++i)
	{
		if (0 == m_rateChangeArray[i].m_FromMonth)
		{
			//find a new empty one, insert it
			m_rateChangeArray[i].m_FromMonth = fromMoth;
			m_rateChangeArray[i].m_NewRate = newRate;

			return true;
		}
	}

	return false;
}

int BaseLoanCalculator::FindNextRateChange(int currIndex)
{
	int rateChangeIndex = -1;
	for (int i = (currIndex < 0 ? 0 : currIndex); i < MAX_RATE_CHANGE; ++i)
	{
		if (m_rateChangeArray[i].m_FromMonth != 0)
		{
			rateChangeIndex = i;
			break;
		}
	}

	return rateChangeIndex;
}

