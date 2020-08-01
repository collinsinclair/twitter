// This is the user class, where personal information will be loaded and stored for program use

#include "user.h"
#include <string>
#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

user::user(){};

user::user(string username)
{
    this->username = username;

    cout << "Enter a password: ";
    string temp_password;
    getline(cin, temp_password);

    cout << "Confirm password: ";
    string confirm_password;
    getline(cin, confirm_password);

    while (temp_password != confirm_password)
    {
        cout << "Passwords do not match." << endl;

        cout << "Enter a password: ";
        getline(cin, temp_password);

        cout << "Confirm password: ";
        getline(cin, confirm_password);
    }

    this->password = confirm_password;

    cout << "Enter your full name: ";
    getline(cin, this->name);

    cout << "Enter your phone number (ex. 1234567890): ";
    getline(cin, this->phone);
    while (phone.length() != 10)
    {
        cout << "Not a valid phone number. Try again: ";
        getline(cin, this->phone);
    }

    cout << "Enter your birthday (YYYY-MM-DD): ";
    getline(cin, this->birthday);
    while (birthday.length() != 10)
    {
        cout << "Not a valid date format. Try again: ";
        getline(cin, this->birthday);
    }
};

user::user(string username, string password, string name, string phone, string birthday)
{
    this->username = username;
    this->password = password;
    this->name = name;
    this->phone = phone;
    this->birthday = birthday;
};

string user::get_username()
{
    return username;
}

string user::get_password()
{
    return password;
}

string user::get_name()
{
    return name;
}

string user::get_phone()
{
    return phone;
}

string user::get_birthday()
{
    return birthday;
}

void user::follow(string username)
{
    following.push_back(username);
    cout << "You are now following @" << username << '!' << endl;
}

vector<string> user::get_following()
{
    return following;
}

void user::Export(ostream &output_stream)
{
    output_stream << get_username()
                  << '|' << get_password()
                  << '|' << get_name()
                  << '|' << get_phone()
                  << '|' << get_birthday()
                  << '|';

    for (auto i : following)
        output_stream << i << '|';

    output_stream << endl;
}

void user::change_password()
{
    string password_garbage;
    getline(cin, password_garbage);
    cout << "Enter current password: ";
    string current_password;
    getline(cin, current_password);
    int password_counter = 0;
    while (current_password != get_password())
    {
        cout << "Incorrect password. Try again: ";
        getline(cin, current_password);
        password_counter++;

        if (password_counter == 2)
        {
            cout << "Too many incorrect attempts. Please try again later." << endl;
            return;
        }
    }

    cout << "Enter a new password: ";
    string temp_password;
    getline(cin, temp_password);

    cout << "Confirm password: ";
    string confirm_password;
    getline(cin, confirm_password);

    while (temp_password != confirm_password)
    {
        cout << "Passwords do not match." << endl;

        cout << "Enter a password: ";
        getline(cin, temp_password);

        cout << "Confirm password: ";
        getline(cin, confirm_password);
    }

    this->password = confirm_password;
}