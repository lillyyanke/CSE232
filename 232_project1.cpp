#include <iomanip>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

/////////////////////////////////////////////////////////
//
// Project 1
// Searches a text for a pattern string
// any character can be replaced by %
// any digit can be replace by #
//
////////////////////////////////////////////////////////

//takes a string, converts it to all lowercase
string Lower(string text)
{
    int len = text.length();
    for (int i = 0; i < len; i++) {
        char ch = tolower(text.at(i));
        text.at(i) = ch;
    }
    return text;
}

//for cases where the % char can match any other char
//returns -1 or the index of the pattern if it's found (place)
int replacePercents(const int& place, const string& str,
    const string& pattern, const string& text)
{
    int index = -1, len_pattern = pattern.length();
    for (int i = 0; i < len_pattern; i++) { //iterates through the section of the text provided
        string new_str = str;
        //iterates through to change diff indexes of the substring of the text to %
        for (int j = i; j < len_pattern; j++) {
            new_str.replace(j, 1, "%");
            if (new_str == pattern) { //checks if the modified str matches the pattern
                return place;
            }
        }
    }
    return index;
}

//for cases where the # char can match any digit
//returns -1 or the index of the pattern if it's found (place)
int replaceHashtags(const int& place, const string& str,
    const string& pattern, const string& text)
{
    int index = -1, len_pattern = pattern.length();
    for (int i = 0; i < len_pattern; i++) { //iterates through portion of text provided
        string new_str = str;
        for (int j = i; j < len_pattern; j++) {
            if (isdigit(new_str.at(j))) {
                new_str.replace(j, 1, "#"); //replaces any digits in the string w #
                if (new_str == pattern) {
                    return place;
                }
            }
        }
    }
    return index;
}

//for cases where chars are replaced by % and digits by #
//returns -1 or the index if the pattern is found
int replaceBoth(const int& place, const string& str,
    const string& pattern, const string& text)
{
    int index = -1, len_pattern = pattern.length();
    for (int i = 0; i < len_pattern; i++) { //iterates through the section of the text
        string new_str = str;
        for (int j = i; j < len_pattern; j++) {
            if (isdigit(new_str.at(j))) { //if it's a digit it's replace w a #
                new_str.replace(j, 1, "#");
                if (new_str == pattern) {
                    return place;
                }
            }
            else {
                new_str.replace(j, 1, "%"); //if it's not a digit it's replaced w a %
                if (new_str == pattern) {
                    return place;
                }
            }
        }
    }
    return index;
}

//iterates through a text looking for pattern
//manipulates texts to account for % and #
bool ImprovedContains(const string& text, const string& pattern,
    const bool* case_sense)
{
    string text_copy = text, pattern_copy = pattern;
    int len_text = text_copy.length(), len_pattern = pattern_copy.length();
    if (*case_sense) {
        text_copy = Lower(text_copy);
        pattern_copy = Lower(pattern_copy);
    }
    if (text_copy.find(pattern_copy) != string::npos) {
        return true;
    }
    //for loop iterates through text in sections the same length as the pattern
    for (int i = 0; i < len_text - len_pattern; i++) {
        string str = text_copy.substr(i, len_pattern);
        if (str == pattern_copy) {
            return true;
        }
        else { //if the functions return -1 the pattern isn't found
            if (replacePercents(i, str, pattern_copy, text_copy) != -1) {
                return true;
            }
            else if (replaceHashtags(i, str, pattern_copy, text_copy) != -1) {
                return true;
            }
            else if (replaceBoth(i, str, pattern_copy, text_copy) != -1) {
                return true;
            }
        }
    }
    return false;
}

//finds the first occurance of the pattern in the text
int ImprovedFindFirstOf(const string& text, const string& pattern,
    const bool* case_sense)
{
    string text_copy = text, pattern_copy = pattern;
    int len_text = text_copy.length(), len_pattern = pattern_copy.length();
    int index = -1;
    if (*case_sense) {
        text_copy = Lower(text_copy);
        pattern_copy = Lower(pattern_copy);
    }
    //for loop iterates through sections of the text
    for (int i = 0; i < len_text - len_pattern + 1; i++) {
        string str = text_copy.substr(i, len_pattern);
        if (str == pattern_copy) {
            return i;
            break;
        }
        else {
            //returns the index of the first occurance
            if (replacePercents(i, str, pattern_copy, text_copy) != -1) {
                return i;
            }
            else if (replaceHashtags(i, str, pattern_copy, text_copy) != -1) {
                return i;
            }
            else if (replaceBoth(i, str, pattern_copy, text_copy) != -1) {
                return i;
            }
        }
    }
    return index;
}

//counts how many times the pattern occurs in the text
int ImprovedMatches(const string& text, const string& pattern,
    const bool* case_sense)
{
    string text_copy = text, pattern_copy = pattern;
    int len_text = text.length(), len_pattern = pattern.length();
    bool pattern_found = ImprovedContains(text_copy, pattern_copy, case_sense);
    int count = 0, index = 0;
    if (pattern_found) { //if it is, go through the text to find if multiple occurences
        while ((len_text >= len_pattern) && (index != -1)) {
            index = ImprovedFindFirstOf(text_copy, pattern_copy, case_sense);
            //if the pattern is found increase count by 1
            if (index != -1) { //if index is -1 the pattern is no longer found in the text
                count++;
                //get rid of the portion of the string with the first
                //occurence of the pattern
                text_copy = text_copy.substr(index + 1);
                len_text = text_copy.length();
            }
            else {
                break;
            }
        }
    }
    return count;
}

//changes text to replace the pattern with given replacement string
void ImprovedReplace(string& text, const string& pattern, const string& replace,
    const bool* case_sense)
{
    string new_text = "";
    int len_pattern = pattern.length(), replace_count = 0;
    int matches = ImprovedMatches(text, pattern, case_sense);
    //while loop iterates through the text the number of times the pattern occurs
    //replaces each instance with the replacement string
    while (replace_count < matches) {
        int index = ImprovedFindFirstOf(text, pattern, case_sense);
        if (index == -1) {
            break;
        }
        int num = 0;
        //adds the text up to the pattern plus the replacement string
        new_text = new_text + text.substr(num, index) + replace;
        num = index + len_pattern;
        text = text.substr(num); //the rest of the string after the pattern occurs
        replace_count++;
    }
    new_text = new_text + text;
    text = new_text;
}

//counts the number of differences between 2 strings
int ImprovedNumberOfDifferences(const string& str, const string& str2,
    const bool& case_sense)
{
    string str_copy = str, str_copy2 = str2;
    if (case_sense) {
        str_copy = Lower(str_copy);
        str_copy2 = Lower(str_copy2);
    }
    int len_str = str.length(), len_str2 = str2.length(), count = 0;
    if (len_str > len_str2) {
        count = len_str - len_str2;
        for (int i = 0; i < len_str2; i++) { //for loop iterates through each char and compares them
            if (str_copy2.at(i) != str_copy.at(i)) {
                count++;
            }
        }
    }
    else {
        count = len_str2 - len_str;
        for (int i = 0; i < len_str; i++) {
            if (str_copy.at(i) != str_copy2.at(i)) {
                count++;
            }
        }
    }
    return count;
}

int main()
{
    return 0;
}