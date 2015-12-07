#pragma once

enum PayMethod
{
	PAYMETHOD_EQUAL_PRINCIPAL = 0x01,				//等额本金
	PAYMETHOD_EQUAL_PRINCIPAL_AND_INTEREST,			//等额本息
};

struct RateChange
{
	int m_FromMonth;
	double m_NewRate;
};

class BaseLoanCalculator
{
public:
	BaseLoanCalculator(PayMethod payMethod, int loanYears, int loanPrincipal, double loanAnnualInterestRate);
	~BaseLoanCalculator();

	bool AddAunnalInterestRateChange(int fromMoth, double newRate);
	

	void Calculate();	

	double GetTotalInterest(){ return m_totalInterest; }

private:
	int FindNextRateChange(int currIndex);//return the next one, -1 is no next

private:
	PayMethod m_payMethod;		//还款方式
	int m_loanYears;			//贷款年限
	int m_loanPrincipal;		//贷款本金总额
	double m_loanAnnualInterestRate;	//年利率

	double m_totalInterest;		//总利息

	const int m_MONTHS_PER_YEAR = 12;	

#define MAX_RATE_CHANGE  10	//最多支持多少次利率变更
	RateChange m_rateChangeArray[MAX_RATE_CHANGE];

};

