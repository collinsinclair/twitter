// This is the driver and will contain the menu system

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "user.h"
#include "tweet.h"

using namespace std;

void get_lines_from_file(string filename, vector<string> &output_vector);

template <class T>
void write_lines_to_file(string filename, vector<T> &objects);

void print_profile(user u, vector<tweet> tweets);

void ClearScreen();

int main()
{
    //* ############################# IMPORT SAVE DATA #############################

    //* ----------------------------------------------------------------------------
    //* ----------------------------------- USERS ----------------------------------
    //* ----------------------------------------------------------------------------

    vector<string> user_data_lines;
    string user_data_file = "users.txt";
    get_lines_from_file(user_data_file, user_data_lines);

    vector<user> users;

    // Populate the vector of users from save file
    for (auto i : user_data_lines)
    {

        istringstream user_data_stream(i);

        string username, password, name, phone, birthday;

        getline(user_data_stream, username, '|');
        getline(user_data_stream, password, '|');
        getline(user_data_stream, name, '|');
        getline(user_data_stream, phone, '|');
        getline(user_data_stream, birthday, '|');

        user u(username, password, name, phone, birthday);

        string followee;

        while (getline(user_data_stream, followee, '|'))
        {
            if (followee != "")
                u.follow(followee);
        }
        users.push_back(u);
    }

    //* ----------------------------------------------------------------------------
    //* ---------------------------------- TWEETS ----------------------------------
    //* ----------------------------------------------------------------------------

    vector<string> tweets_data_lines;
    string tweets_data_file = "tweets.txt";
    get_lines_from_file(tweets_data_file, tweets_data_lines);

    vector<tweet> tweets;

    for (auto i : tweets_data_lines)
    {
        istringstream tweets_data_stream(i);

        string username, content;

        getline(tweets_data_stream, username, '|');
        getline(tweets_data_stream, content);

        tweet t(username, content);
        tweets.push_back(t);
    }

    //* ############################ SAVE DATA IMPORTED ############################

    //* ----------------------------------------------------------------------------
    //* ------------------------ SIGN IN / ACCOUNT CREATION ------------------------
    //* ----------------------------------------------------------------------------
    ClearScreen();
    cout << "See what’s happening in the world right now - join Twitter today." << endl;

    cout << "Enter username: ";

    string username;
    getline(cin, username);

    // check for spaces in entered username
    int space_index = username.find(' ');
    while (space_index != -1)
    {
        cout << "Invalid username (contained a space). Enter a valid username: ";
        getline(cin, username);
        space_index = username.find(' ');
    }

    // Check if user has an account
    bool has_account = false;
    int current_user;
    for (auto i = 0; i < users.size(); i++)
    {
        if (users[i].get_username() == username)
        {
            current_user = i;
            has_account = true;
            break;
        }
    }

    if (has_account)
    {
        string password;
        cout << "Enter password: ";
        getline(cin, password);

        int password_counter = 0;
        while (password != users[current_user].get_password())
        {
            cout << "Incorrect password. Try again: ";
            getline(cin, password);
            password_counter++;

            if (password_counter == 2)
            {
                cout << "Too many incorrect attempts. Please try again later." << endl;
                return 0;
            }
        }
    }

    else
    {
        cout << "No account found with username '" << username << "' found. Would you like to make an account? (yes/no): ";
        string account_choice;
        getline(cin, account_choice);

        while ((account_choice != "yes") and (account_choice != "no"))
        {
            cout << "Invalid choice. Type 'yes' or 'no': ";
            getline(cin, account_choice);
        }

        if (account_choice == "no")
        {
            cout << "Have a great day!" << endl;
            return 0;
        }

        else
        {
            user new_user = user(username);
            users.push_back(new_user);
            current_user = users.size() - 1;

            write_lines_to_file(user_data_file, users);
        }
    }

    //* ----------------------------------------------------------------------------
    //* ----------------------------------------------------------------------------
    //* ----------------------------------------------------------------------------

    string menu_choice;

    while (true)
    {
        ostringstream menu;
        menu << endl
             << "-----------------------------------------------------------" << endl
             << "What would you like to do?" << endl
             << "-----------------------------------------------------------" << endl
             << "1: Send a Tweet" << endl
             << "2: View Feed" << endl
             << "3: Explore" << endl
             << "4: View Your Profile" << endl
             << "5: Search for a Profile to Follow" << endl
             << "6: Change Your Password" << endl
             << "7: Log off" << endl
             << "-----------------------------------------------------------" << endl
             << endl
             << "Enter a number: ";

        cout << menu.str();

        int menu_choice;
        cin >> menu_choice;

        while (cin.fail() or (menu_choice > 7) or (menu_choice < 1))
        {
            cin.clear();
            string menu_temp;
            getline(cin, menu_temp);
            cout << "Invalid choice, enter a number between 1 and 7: ";
            cin >> menu_choice;
        }

        tweet t;
        string user_search;
        string search_temp;
        string follow_choice;
        bool no_results = true;
        bool is_following = false;

        switch (menu_choice)
        {
        case 1:
            ClearScreen();
            t = tweet(users[current_user]);
            tweets.push_back(t);
            write_lines_to_file(tweets_data_file, tweets);
            break;
        case 2:
            ClearScreen();
            cout << endl;

            if (users[current_user].get_following().size() == 0)
                cout << "You aren't following anyone! Go to 'Explore' to find people to follow." << endl;

            else
            {
                for (auto i : tweets)
                {
                    for (auto j : users[current_user].get_following())
                    {
                        if (i.get_username() == j)
                            i.print_tweet();
                    }
                }
            }
            break;
        case 3:
            ClearScreen();
            cout << endl
                 << "Welcome to Explore! Here you will find the tweets of everyone whom you do not follow." << endl
                 << endl;

            if (users[current_user].get_following().size() == 0)
            {
                for (auto i : tweets)
                {
                    if (i.get_username() != users[current_user].get_username())
                        i.print_tweet();
                }
            }

            else
            {
                for (int i = 0; i < tweets.size(); i++)
                {
                    tweets[i].set_not_checked();
                }

                for (int i = 0; i < tweets.size(); i++)
                {
                    for (auto j : users[current_user].get_following())
                    {
                        if ((!tweets[i].is_checked()) and ((tweets[i].get_username() == j) or (tweets[i].get_username() == users[current_user].get_username())))
                            tweets[i].set_checked();
                    }
                }

                for (auto i : tweets)
                {
                    if (!i.is_checked())
                        i.print_tweet();
                }
            }

            break;
        case 4:
            ClearScreen();
            print_profile(users[current_user], tweets);
            break;
        case 5:
            ClearScreen();
            getline(cin, search_temp);
            cout << "Search Twitter: ";
            getline(cin, user_search);
            for (auto i : users)
            {
                if (user_search == i.get_username())
                {
                    no_results = false;
                    print_profile(i, tweets);
                    cout << "Follow @" << i.get_username() << "? (yes/no): ";
                    getline(cin, follow_choice);

                    while ((follow_choice != "yes") and (follow_choice != "no"))
                    {
                        cout << "Invalid choice. Type 'yes' or 'no': ";
                        getline(cin, follow_choice);
                    }

                    if (follow_choice == "yes")
                    {
                        for (auto k : users[current_user].get_following())
                        {
                            if (user_search == k)
                            {
                                is_following = true;
                                break;
                            }
                        }
                        if (is_following)
                        {
                            cout << "You already follow @" << user_search << endl;
                        }

                        else
                        {
                            users[current_user].follow(user_search);
                            write_lines_to_file(user_data_file, users);
                        }
                    }
                    break;
                }
            }
            if (no_results)
                cout << "No results." << endl;

            break;
        case 6:
            ClearScreen();
            users[current_user].change_password();
            write_lines_to_file(user_data_file, users);
            break;
        case 7:
            write_lines_to_file(user_data_file, users);
            cout << endl
                 << "Have a great day!" << endl
                 << endl;
            return 0;
        default:
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}

void get_lines_from_file(string filename, vector<string> &lines_vector)
{
    // Open input file stream
    ifstream import_data_stream(filename);

    // Check if opening of file stream failed
    if (import_data_stream.fail())
    {
        cout << "Error loading data from file: " << filename << endl;
    }

    string temp; // a place to store each line of data before adding it to data vector

    while (getline(import_data_stream, temp))
    {
        if (temp != "")
            lines_vector.push_back(temp);
    }
}

template <class T>
void write_lines_to_file(string filename, vector<T> &object_vector)
{
    ofstream export_stream(filename);

    if (export_stream.fail())
    {
        cout << "Error exporting data to file: " << filename << endl;
        return;
    }

    // export data to file
    for (auto i : object_vector)
    {
        i.Export(export_stream);
    }
}

void print_profile(user u, vector<tweet> tweets)
{
    cout << endl;
    cout << u.get_name() << endl;
    cout << '@' << u.get_username() << endl;
    cout << u.get_following().size() << " Following" << endl
         << endl;

    for (auto i : tweets)
    {
        if (i.get_username() == u.get_username())
            i.print_tweet();
    }
}

void ClearScreen()
{
    cout << string(100, '\n');
}