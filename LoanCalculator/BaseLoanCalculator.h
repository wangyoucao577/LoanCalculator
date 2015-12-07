#pragma once

enum PayMethod
{
	PAYMETHOD_EQUAL_PRINCIPAL = 0x01,				//�ȶ��
	PAYMETHOD_EQUAL_PRINCIPAL_AND_INTEREST,			//�ȶϢ
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
	PayMethod m_payMethod;		//���ʽ
	int m_loanYears;			//��������
	int m_loanPrincipal;		//������ܶ�
	double m_loanAnnualInterestRate;	//������

	double m_totalInterest;		//����Ϣ

	const int m_MONTHS_PER_YEAR = 12;	

#define MAX_RATE_CHANGE  10	//���֧�ֶ��ٴ����ʱ��
	RateChange m_rateChangeArray[MAX_RATE_CHANGE];

};

