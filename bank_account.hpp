#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;

void deposit(double&, const double);

bool withdraw(double&, const double);

void overdraft(double&, const double);

double roundDoub (const double num);

double interest_for_month(const double, double);

void string_date_to_int_ptrs(const string,int*, int*, int*);

void string_date_to_ints(const string, int&, int&, int&);

int number_of_first_of_months(const string, const string);

double interest_earned(double, const double, const string, const string);

vector <string> stream_to_vector (string& , string&);

string interest_accrued (const int, double&, const double, const string, const string);

string process_command(const string, string&, double&, const double);

string process_commands(const string, const double);