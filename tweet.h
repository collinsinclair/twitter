#pragma once
#include <string>
#include "user.h"

using namespace std;

class tweet
{
public:
    tweet();
    tweet(user u);
    tweet(string username, string content);
    string get_username();
    string get_content();
    void print_tweet();
    void Export(ostream &output_stream);
    void set_not_checked();
    void set_checked();
    bool is_checked();

private:
    string username;
    string content;
    bool checked;
};