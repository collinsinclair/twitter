// This is the user class, where personal information will be loaded and stored for program use

#pragma once
#include <string>
#include <vector>

using namespace std;

class user
{
public:
    user();
    user(string username);
    user(string username, string password, string name, string phone, string birthday);

    string get_username();
    string get_password();
    string get_name();
    string get_phone();
    string get_birthday();

    void follow(string username);
    vector<string> get_following();

    void change_password();

    void Export(ostream &output_stream);

private:
    string username;
    string password;
    string name;
    string phone;
    string birthday;
    vector<string> following;
};