#include "basic_class.h"

double Accumulator::getSum(Date date)const
{
	//返回到指定日期的存款或欠款金额按日累积值
	double sum_t = sum + value * (date-lastDate);
	return sum_t ;
}

void Accumulator::change(Date date, double value)
{
	//将上次存取钱的日期更新为当前操作的日期
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
