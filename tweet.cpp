#include "tweet.h"
#include <string>
#include <iostream>

using namespace std;

tweet::tweet(){};

tweet::tweet(user u)
{
    this->username = u.get_username();
    cout << endl
         << "What's happening?" << endl
         << endl;

    string tweet_temp;
    getline(cin, tweet_temp);

    int char_limit = 294; // extra 5% added on because string.length() may not correspond to the actual number of encoded characters in sequences of multi-byte or variable-length characters
    getline(cin, this->content);

    while ((this->content.length() > char_limit) or (content.length() == 0))
    {
        if (content.length() > char_limit)
        {
            cout << "Tweet exceeds character limit by " << this->content.length() - char_limit << " characters. Try again: " << endl;
            getline(cin, this->content);
        }

        else
        {
            cout << "Tweet cannot be empty. Try again: " << endl;
            getline(cin, this->content);
        }
    }

    cout << endl
         << "Tweet sent!" << endl;
};

tweet::tweet(string username, string content)
{
    this->username = username;
    this->content = content;
};

string tweet::get_username()
{
    return username;
}

string tweet::get_content()
{
    return content;
}

void tweet::print_tweet()
{
    cout << '@' << get_username() << ": " << get_content() << endl
         << endl;
}

void tweet::Export(ostream &output_stream)
{
    output_stream << username << '|' << content << endl;
}

void tweet::set_not_checked()
{
    checked = false;
}

void tweet::set_checked()
{
    checked = true;
}

bool tweet::is_checked()
{
    return checked;
}