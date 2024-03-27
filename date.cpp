//#include<iostream>
//#include "date.h"
//using namespace std;
//Date:: Date()
//{
//	cout << "Default Constructor Called...................!" << endl;
//	Day = 1;
//	Month = 1;
//	Year = 1926;
//}
//void Date::print()
//{
//	cout << Day << "/" << Month << "/" << Year << endl;
//}
//Date::Date(int Day, int Month, int Year)
//{
//	cout << "Overloaded Constructor Called...........!" << endl;
//	this->Day = Day;
//	this->Month = Month;
//	this->Year = Year;
//}
//Date::~Date()
//{
//	cout << "Destructor Called.......!" << endl;
//}
//void Date::input()
//{
//	cout << "Enter the Day: " << endl;
//	cin >> Day;
//	cout << "Enter the Month: " << endl;
//	cin >> Month;
//	cout << "Enter the Year: " << endl;
//	cin >> Year;
//}
//int Date::setDay(int x)
//{
//	Day = x;
//	return Day;
//}
//int Date::setMonth(int y)
//{
//	Month = y;
//	return Month;
//}
//int Date::setYear(int z)
//{
//	Year = z;
//	return Year;
//}
////Exercise 08
//int Date::getDay()
//{
//	return Day;
//}
//int Date::getMonth()
//{
//	return Month;
//}
//int Date::getYear()
//{
//	return Year;
//}
//int Date::Compare(Date& obj)
//{
//	if (this->Year > obj.Year)
//	{
//		return 1;
//	}
//	else if (this->Year < obj.Year)
//	{
//		return -1;
//	}
//	else if (this->Year == obj.Year && this->Month > obj.Month)
//	{
//		return 1;
//	}
//	else if (this->Year == obj.Year && this->Month < obj.Month)
//	{
//		return -1;
//	}
//	else if (this->Year == obj.Year && this->Month < obj.Month && this->Day>obj.Day)
//	{
//		return 1;
//	}
//	else if (this->Year == obj.Year && this->Month < obj.Month && this->Day < obj.Day)
//	{
//		return -1;
//	}
//
//
//}
//Date Date::IncrementMonth()
//{
//	Date temp = *this;
//	temp.Month++;
//	if (temp.Month > 12)
//	{
//		temp.Month = 1;
//		temp.Year++;
//	}
//	return temp;
//}