#include <iostream>
#include <assert.h>
using namespace std;

class Date{
public:
    Date(int year=1900,int month=1,int day=1);
    Date(const Date& d);
    Date& operator=(const Date& d);
    ~Date(){}
    bool IsInvalid();
    bool isLeapYear(int year);
    int GetMonthDay(int year,int month);
    void Show();
    bool operator==(const Date& d);
    bool operator!=(const Date& d);
    bool operator>=(const Date& d);
    bool operator<=(const Date& d);
    bool operator>(const Date& d);
    bool operator<(const Date& d);
    Date operator+(int day);
    Date& operator+=(int day);
    Date operator-(int day);
    Date& operator-=(int day);
    int operator-(const Date& d);

    Date& operator++();//前置
    Date operator++(int);//后置
    Date& operator--();
    Date operator--(int);
private:
    int _year;
    int _month;
    int _day;
};

//d2(d1)
Date::Date(const Date& d){
    _year = d._year;
    _month = d._month;
    _day = d._day;
}

Date& Date::operator=(const Date& d){
    _year = d._year;
    _month = d._month;
    _day = d._day;

    return *this;
}

void Date::Show(){
    cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
}
Date::Date(int year,int month,int day)
    :_year(year),_month(month),_day(day){
        if(!IsInvalid()){
            assert(false);
            //cout<<"非法日期"<<endl;
            //exit(1);
        }
}

bool Date::IsInvalid(){
    return _year>0 && _month > 0 && _month < 13 && _day > 0 && _day <= GetMonthDay(_year,_month);
}

bool Date::isLeapYear(int year){
    return ((year % 4 == 0 && year % 100 != 0)||year % 400 == 0);
}

int Date::GetMonthDay(int year,int month){
    int days[13] = {-1,31,28,31,30,31,30,31,31,30,31,30,31};
    int monthdays = days[month];
    if(isLeapYear(year) && month == 2){
        monthdays = 29;
    }
    return monthdays;
}

bool Date::operator==(const Date& d){
    return _year == d._year && _month == d._month && _day == d._day;
}

bool Date::operator!=(const Date& d){
    return !((*this)==d);
}

bool Date::operator<(const Date& d){
    if(_year < d._year){
        return true;
    }else if((_year == d._year) && _month < d._month){
        return true;   
    }else if((_year == d._year) && (_month == d._month) && _day < d._day){
        return true;
    }
        return false;
}

bool Date::operator>=(const Date& d){
    return !((*this)<d);
}

bool Date::operator>(const Date& d){
    return !((*this)<d) && !((*this)==d);
}

bool Date::operator<=(const Date& d){
    return !((*this)>d);
}

Date Date::operator+(int day){
    Date tmp(*this);
    tmp._day += day;
    while(tmp._day > GetMonthDay(tmp._year,tmp._month)){
        tmp._day -= GetMonthDay(tmp._year,tmp._month);
        ++tmp._month;
        if(tmp._month > 12){
            tmp._month = 1;
            ++tmp._year;
        }
    }
    return tmp;
}

Date& Date::operator+=(int day){
    (*this) = (*this) + day;
    return (*this);
}

Date Date::operator-(int day){
    Date tmp(*this);
    tmp._day -= day;
    while(tmp._day <= 0){
        --tmp._month;
        if(tmp._month == 0){
            tmp._month = 12;
            --tmp._year;
        }
        tmp._day = GetMonthDay(tmp._year,tmp._month) + tmp._day; 
    }
    return tmp;
//    if(tmp._day > day){
//        tmp._day -= day;
//        return tmp;
//    }else if(tmp._day == day){
//        --tmp._month;
//        tmp._day = GetMonthDay(tmp._year,tmp._month);
//        return tmp;
//    }else {
//        --tmp._month;
//        tmp._day = GetMonthDay(tmp._year,tmp._month) - day;
//        while(tmp._day )
//    }
}

Date& Date::operator-=(int day){
    return ((*this) = (*this)-day);
}

int Date::operator-(const Date& d){
//    if((*this)==d){
//        return 0;
//    }else if((*this)>d){
//        if(_month >= d._month){
//            int i = 0;
//            int sum_yeardays = 0;
//            int sum_monthdays = 0;
//            for(i=d._year;i<_year;++i){
//                sum_yeardays += 365+isLeapYear(i);
//            }
//            for(i=d._month;i<_month;++i){
//                sum_monthdays += GetMonthDay(_year,i);
//            }
//            return sum_yeardays + sum_monthdays + (_day - d._day);
//        }
//    }
//    return 1;
    int flag = 1;
    Date max = (*this);
    Date min = d;
    if((*this) < d){
        max = d;
        min = (*this);
        flag = -1;
    }
    int count = 0;
    while(max != min){
        ++min;
        ++count;
    }
    return flag*count;
}

Date& Date::operator++(){
    return (*this)+=1;
}

Date Date::operator++(int){
    Date tmp(*this);
    (*this) += 1;
    return tmp;
}

Date& Date::operator--(){
    return (*this)-=1;
}
Date Date::operator--(int){
    Date tmp(*this);
    (*this) -= 1;
    return tmp;
}

int main(){
    Date d(2017,6,4);
    Date d2(2016,6,4);
//    d += 58;
//    d -= 2000;
    int ret = d - d2;
    cout<<ret<<endl;
    d.Show();
    d2.Show();
    return 0;
}
