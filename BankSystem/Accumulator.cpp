#include "basic_class.h"

double Accumulator::getSum(Date date)const
{
	//���ص�ָ�����ڵĴ���Ƿ������ۻ�ֵ
	double sum_t = sum + value * (date-lastDate);
	return sum_t ;
}

void Accumulator::change(Date date, double value)
{
	//���ϴδ�ȡǮ�����ڸ���Ϊ��ǰ����������
	lastDate = date;
	this->value = value;
	sum = getSum(date);
}

void Accumulator::reset(Date date, double value)
{
	lastDate = date;
	this->value = value;
	sum = 0.0;
}
