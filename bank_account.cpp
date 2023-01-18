#include <iostream>
#include "bank_account.hpp"
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using std::string;
using std::cout;
using std::endl;
using std::vector;

//takes ref to balance and modifies to reflect deposit
void deposit(double &balance, const double amount){
    balance = balance + amount;
}

//takes ref to balance and modifies to reflect withdraw
//bool indicates if withdraw was successful
bool withdraw(double &balance, const double amount){
    if ((balance - amount) >= 0){ //checks if theres enough money to withdraw
        balance = balance - amount;
        return true;
    }
    else{
        return false;
    }
}

//takes ref to balance and modifies to reflect withdraw
void overdraft(double &balance, const double amount){
    balance = balance - amount - 35; //$35 overdraft fee
}

//takes num and cuts off trailing decimal
double roundDoub (const double num){
    string str = std::to_string(num);
    if (str.find(".") != string::npos){
        //str = str.substr(0,str.find("." + 3));
        string beg = str.substr(0, str.find("."));
        string end = str.substr(str.find("."), 3);
        double new_num = std::stod(beg+end);
        return new_num;
    }
    else{
        return num; //returns num if an integer
    }
}

//returns interest generated for one month rounded
double interest_for_month(const double balance, double apr){
    apr = (apr/ 100) /12; //apr percentage per month
    double interest = balance * apr;
    double round_int = roundDoub (interest); //rounds interest
    return round_int;
}

//takes date and processes into pointers to month, day, yr
void string_date_to_int_ptrs(const string date, int *year, int *month, int *day){
    int yr = std::stoi(date.substr(0, 4));
    *year = yr;
    int mon = std::stoi(date.substr(5, 2));
    *month = mon;
    int dayy = std::stoi(date.substr(8, 2));
    *day = dayy;
}

//takes date and processes into references to day, month, yr
void string_date_to_ints(const string date, int &year, int &month, int &day){
    int yr = std::stoi(date.substr(0, 4));
    year = yr;
    int mon = std::stoi(date.substr(5, 2));
    month = mon;
    int dayy = std::stoi(date.substr(8, 2));
    day = dayy;
}

//returns number of times interest will accrue bw 2 dates
int number_of_first_of_months(const string earlier, const string later){
    int result, year_earlier, month_earlier, day_earlier,
                                 year_later, month_later, day_later;
    string_date_to_int_ptrs(earlier, &year_earlier, &month_earlier, &day_earlier); 
                                            //gets day, mon, yr of earlier date
    string_date_to_int_ptrs(later, &year_later, &month_later, &day_later); 
                                            //gets day, mon, yr of later date

    if (year_earlier == year_later){ //if it's in the same year
        result = ((year_earlier - year_later) * 12) + std::abs(month_earlier - month_later);
    }   //just worry about diff in months
    else{
        int add = 12 - month_earlier;
        int year_diff = ((year_later - year_earlier) * 12) - 12;
        result = year_diff + month_later + add;
    }
    return result;
}

//calculates the amount on interest accrued bw 2 dates
double interest_earned(double balance, const double apr,
                       const string begin, const string end){
    double beg_bal = balance, interest = interest_for_month(balance, apr);
    int months = number_of_first_of_months(begin, end);
    for (int i = 0; i < months; i++){
        balance = balance + interest; //balance + interest for that month
        interest = interest_for_month(balance, apr); //new interest for new balance
    }
    double int_acc = balance - beg_bal;
    return int_acc;
}

//returns a vector from a command line
//<date, action, amount>
vector <string> stream_to_vector (string &line, string &date){
    if (date.empty())
        date = "00-00-00";
    vector <string> line_vector;
    std::istringstream iss(line); //iterate thru lines into a vector
    copy(std::istream_iterator<string>(iss), std::istream_iterator<string>(),
                                                 back_inserter(line_vector));
    return line_vector;
}

//returns string indicating any interest that has been earned
string interest_accrued (const int times, double &balance, 
                         const double apr, const string date, const string curr_date){
    std::stringstream s;
    double interest = interest_earned(balance, apr, date, curr_date);
    if (interest < 0){ //if the balance is in the negative, no interest accrued
            interest = 0;
        }
        balance = balance + interest;
        string int_str = std::to_string(interest); //in order to cut off trailing decimal from str
        s << "Since " << date << ", interest has accrued " << times << " times.\n";
        s << "$" << int_str.substr(0, int_str.find(".")+3) << " interest has been earned.\n";
    return s.str();

}

//processes a single command to return a str indicating the work done
//updates balance to reflect changes
string process_command(string line, string &date, double &balance,
                                                  const double apr){
    std::stringstream s;
    vector <string> line_vector = stream_to_vector(line, date);
    string curr_date = line_vector.at(0), action = line_vector.at(1),
                                     str_amount = line_vector.at(2);
    double amount = std::stod(str_amount.substr(1));
    if (date == "00-00-00")
        date = curr_date; //set empty date to curr date
    int times = number_of_first_of_months(date, curr_date);
    s << "On " << curr_date << ": Instructed to perform \"" 
                            << action << " " << str_amount << "\"\n";
    if (times > 0){ //if more than one month is bw the dates, then interest is added
        string interest_string = interest_accrued(times, balance, 
                                                  apr, date, curr_date);
        s << interest_string;
    }
    if (action == "Deposit"){
        deposit(balance, amount);
    }
    else if (action == "Withdraw"){
        if (amount > balance){
            overdraft(balance, amount);
            s << "Overdraft!" << "\n";
        }
        else{
            withdraw(balance, amount);
        }
    }
    string str_bal = std::to_string(balance); //to cut off trailing decimal
    s << "Balance: " << str_bal.substr(0, str_bal.find(".")+3) << "\n";
    date = curr_date;
    return s.str();
}


//returns a string to indicate results of performing operations 
string process_commands(const string lines, const double apr){
    std::stringstream ret, ss(lines);
    string line, add, previous_date = "00-00-00";
    double balance = 0;
    while (std::getline(ss, line)){ //read in lines from stream
        add = process_command(line, previous_date, balance, apr);
        ret << add; //process lines and push to output stream
        add = "";
    }
    return ret.str();
}

int main() 
{
    std::cout << "Hello, World!";
    return 0;
}
