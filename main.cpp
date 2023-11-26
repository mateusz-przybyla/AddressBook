#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct User
{
    int userId = 0;
    string userName = "", password = "";
};

struct Contact
{
    int id = 0;
    string firstName = "", surname = "", phoneNumber = "", email = "", address = "";
};

string readLine()
{
    string input = "";
    getline(cin, input);
    return input;
}

char getChar()
{
    string input = "";
    char character = {0};

    while (true)
    {
        getline(cin, input);

        if (input.length() == 1)
        {
            character = input[0];
            break;
        }
        cout << "This is not a single character. Type again." << endl;
    }
    return character;
}

void showContact(Contact contact)
{
    cout << endl;
    cout << contact.id << "|";
    cout << contact.firstName << "|";
    cout << contact.surname << "|";
    cout << contact.phoneNumber << "|";
    cout << contact.email << "|";
    cout << contact.address << "|";
}

void writeNewContactInFile(Contact contact)
{
    ofstream contactsFile;
    contactsFile.open("address_book.txt", ios::out | ios::app);

    if (contactsFile.good())
    {
        contactsFile << contact.id << "|";
        contactsFile << contact.firstName << "|";
        contactsFile << contact.surname << "|";
        contactsFile << contact.phoneNumber << "|";
        contactsFile << contact.email << "|";
        contactsFile << contact.address << "|" << endl;
        contactsFile.close();
    }
    else
    {
        cout << endl << "Failed to open a file and write data." << endl;
        Sleep(1500);
    }
}

void addContact(vector <Contact> &contacts)
{
    Contact contact;

    system("cls");
    cout << ">>> ADDING NEW CONTACT <<<" << endl << endl;

    contacts.empty() ? contact.id = 1 : contact.id = contacts.back().id + 1;

    cout << endl;
    cout << "Enter first name: ";
    contact.firstName = readLine();
    cout << "Enter surname: ";
    contact.surname = readLine();
    cout << "Enter phone number: ";
    contact.phoneNumber = readLine();
    cout << "Enter email: ";
    contact.email = readLine();
    cout << "Enter address: ";
    contact.address = readLine();

    contacts.push_back(contact);
    writeNewContactInFile(contact);

    cout << endl << "New contact was added." << endl;
    Sleep(1500);
}

Contact getDataFromFile(string lineContent)
{
    Contact contact;
    int numberOfData = 1;
    string singleData = "";

    for (size_t position = 0; position < lineContent.length(); position++)
    {
        if (lineContent[position] != '|')
        {
            singleData += lineContent[position];
        }
        else
        {
            switch (numberOfData)
            {
            case 1: contact.id = atoi(singleData.c_str()); break;
            case 2: contact.firstName = singleData; break;
            case 3: contact.surname = singleData; break;
            case 4: contact.phoneNumber = singleData; break;
            case 5: contact.email = singleData; break;
            case 6: contact.address = singleData; break;
            }
            singleData = "";
            numberOfData++;
        }
    }
    return contact;
}

void getContactsFromFile(vector <Contact> &contacts)
{
    Contact contact;
    string lineContent = "";

    ifstream contactsFile("address_book.txt");

    if (contactsFile.good())
    {
        while (getline(contactsFile, lineContent))
        {
            contact = getDataFromFile(lineContent);
            contacts.push_back(contact);
        }
        contactsFile.close();
    }
    else
    {
        cout << endl << "File with contacts does not exist." << endl;
        Sleep(1500);
    }
}

void searchByFirstName(vector <Contact> contacts)
{
    string nameToFind = "";
    bool contactFound = false;

    system("cls");
    cout << ">>> SEARCH BY FIRST NAME <<<" << endl << endl;

    cout << "Enter the first name you want to find: ";
    nameToFind = readLine();

    for (auto contact : contacts)
    {
        if (contact.firstName == nameToFind)
        {
            showContact(contact);
            contactFound = true;
        }
    }

    if (contactFound)
    {
        cout << endl << endl;
        system("pause");
    }
    else
    {
        cout << endl << "No contact with that first name on the list.";
        Sleep(1500);
    }
}

void searchBySurname(vector <Contact> contacts)
{
    string surnameToFind = "";
    bool contactFound = false;

    system("cls");
    cout << ">>> SEARCH BY SURNAME <<<" << endl << endl;

    cout << "Enter the surname you want to find: ";
    surnameToFind = readLine();

    for (auto contact : contacts)
    {
        if (contact.surname == surnameToFind)
        {
            showContact(contact);
            contactFound = true;
        }
    }

    if (contactFound)
    {
        cout << endl << endl;
        system("pause");
    }
    else
    {
        cout << endl << "No contact with that surname on the list.";
        Sleep(1500);
    }
}

void showAllContacts(vector <Contact> contacts)
{
    system("cls");

    if (!contacts.empty())
    {
        for (auto contact : contacts)
        {
            showContact(contact);
        }
        cout << endl << endl;
        system("pause");
    }
    else
    {
        cout << endl << "No contacts on the list.";
        Sleep(1500);
    }
}

int getContactIdFromLine(string line)
{
    int position = 0;
    string contactId = "";

    while (isdigit(line[position]))
    {
        contactId += line[position];
        position++;
    }

    return atoi(contactId.c_str());
}

void deleteLineInFile(int contactIdToBeDeleted)
{
    string line = "";

    ifstream contactsFile("address_book.txt");
    ofstream tempFile;
    tempFile.open("address_book_temp.txt", ios::out | ios::app);

    if (contactsFile.good())
    {
        while (getline(contactsFile, line))
        {
            if (contactIdToBeDeleted == getContactIdFromLine(line))
            {
                tempFile << "";
            }
            else
            {
                tempFile << line << endl;
            }
        }
        contactsFile.close();
        tempFile.close();
        remove("address_book.txt");
        rename("address_book_temp.txt", "address_book.txt");
    }
}

void deleteContact(vector <Contact> &contacts)
{
    int contactIdToBeDeleted = 0;
    bool contactFound = false;

    system("cls");
    cout << ">>> DELETING SELECTED CONTACT <<<" << endl << endl;
    cout << "Enter the contact ID you want to delete: ";
    contactIdToBeDeleted = atoi(readLine().c_str());

    for (vector <Contact>::iterator itr = contacts.begin(); itr != contacts.end(); itr++)
    {
        if (itr -> id == contactIdToBeDeleted)
        {
            contactFound = true;
            cout << endl << "Confirm with 't': ";

            if (getChar() == 't')
            {
                contacts.erase(itr);
                deleteLineInFile(contactIdToBeDeleted);

                cout << endl << "Contact was deleted.";
                Sleep(1500);
                break;
            }
            else
            {
                cout << endl << "Not confirmed. Try again.";
                Sleep(1500);
            }
        }
    }

    if (!contactFound)
    {
        cout << endl << "No contact with that ID on the list.";
        Sleep(1500);
    }
}

char showSubmenu(char choice)
{
    cout << "Contact details for editing: " << endl << endl;
    cout << "1 - first name" << endl;
    cout << "2 - surname" << endl;
    cout << "3 - phone number" << endl;
    cout << "4 - email" << endl;
    cout << "5 - address" << endl;
    cout << "6 - go to main menu" << endl << endl;
    cout << "Your choice: ";
    choice = getChar();

    return choice;
}

void editDataInFile(int contactIdToBeEdited, vector <Contact> contacts)
{
    string line = "";

    ifstream contactsFile("address_book.txt");
    ofstream tempFile;
    tempFile.open("address_book_temp.txt", ios::out | ios::app);

    if (contactsFile.good())
    {
        while (getline(contactsFile, line))
        {
            if (contactIdToBeEdited == getContactIdFromLine(line))
            {
                for (vector <Contact>::iterator itr = contacts.begin(); itr != contacts.end(); itr++)
                {
                    if (itr -> id == contactIdToBeEdited)
                    {
                        tempFile << itr -> id << "|";
                        tempFile << itr -> firstName << "|";
                        tempFile << itr -> surname << "|";
                        tempFile << itr -> phoneNumber << "|";
                        tempFile << itr -> email << "|";
                        tempFile << itr -> address << "|" << endl;
                    }
                }
            }
            else
            {
                tempFile << line << endl;
            }
        }
        contactsFile.close();
        tempFile.close();
        remove("address_book.txt");
        rename("address_book_temp.txt", "address_book.txt");
    }
}

void editContact(vector <Contact> &contacts)
{
    int contactIdToBeEdited = 0;
    bool contactFound = false;
    char choice;

    system("cls");
    cout << ">>> EDITING SELECTED CONTACT <<<" << endl << endl;
    cout << "Enter the contact ID you want to edit: ";
    contactIdToBeEdited = atoi(readLine().c_str());

    for (vector <Contact>::iterator itr = contacts.begin(); itr != contacts.end(); itr++)
    {
        if (itr -> id == contactIdToBeEdited)
        {
            contactFound = true;
            choice = showSubmenu(choice);

            switch (choice)
            {
                case '1': cout << endl << "Enter new first name: ";   itr -> firstName = readLine();
                          cout << endl << "First name was changed." << endl; break;
                case '2': cout << endl << "Enter new surname: ";      itr -> surname = readLine();
                          cout << endl << "Surname was changed." << endl; break;
                case '3': cout << endl << "Enter new phone number: "; itr -> phoneNumber = readLine();
                          cout << endl << "Phone number was changed." << endl; break;
                case '4': cout << endl << "Enter new email: ";        itr -> email = readLine();
                          cout << endl << "Email was changed." << endl; break;
                case '5': cout << endl << "Enter new address: ";      itr -> address = readLine();
                          cout << endl << "Address was changed." << endl; break;
                case '6': break;
                default: cout << endl << "There is no such option. Try again." << endl << endl; break;
            }
            editDataInFile(contactIdToBeEdited, contacts);
            Sleep(1500);
        }
    }

    if (!contactFound)
    {
        cout << endl << "No contact with that ID on the list.";
        Sleep(1500);
    }
}

void closeApp()
{
    cout << endl << "End of application." << endl;
    exit(0);
}

void writeNewUserInFile(User user)
{
    ofstream usersFile;
    usersFile.open("users.txt", ios::out | ios::app);

    if (usersFile.good())
    {
        usersFile << user.userId << "|";
        usersFile << user.userName << "|";
        usersFile << user.password << "|" << endl;
        usersFile.close();
    }
}

User getUserDataFromFile(string lineContent)
{
    User user;
    int numberOfData = 1;
    string singleData = "";

    for (size_t position = 0; position < lineContent.length(); position++)
    {
        if (lineContent[position] != '|')
        {
            singleData += lineContent[position];
        }
        else
        {
            switch (numberOfData)
            {
            case 1: user.userId = atoi(singleData.c_str()); break;
            case 2: user.userName = singleData; break;
            case 3: user.password = singleData; break;
            }
            singleData = "";
            numberOfData++;
        }
    }
    return user;
}

void getUsersFromFile(vector <User> &users)
{
    User user;
    string lineContent = "";

    ifstream usersFile("users.txt");

    if (usersFile.good())
    {
        while (getline(usersFile, lineContent))
        {
            user = getUserDataFromFile(lineContent);
            users.push_back(user);
        }
        usersFile.close();
    }
    else
    {
        cout << endl << "File with users does not exist." << endl;
        Sleep(1500);
    }
}

bool checkUserName(vector <User> users, string nameSuggestion)
{
    bool ifAvailable = false;

    for (vector <User>::iterator itr = users.begin(); itr != users.end(); itr++)
    {
        if (itr -> userName == nameSuggestion)
        {
            ifAvailable = true;
            break;
        }
    }
    return ifAvailable;
}

void registration(vector <User> &users)
{
    User user;
    string nameSuggestion = "";

    system("cls");
    cout << ">>> ADDING NEW USER <<<" << endl << endl;

    cout << "Enter username: ";
    nameSuggestion = readLine();

    while (true)
    {
        if (checkUserName(users, nameSuggestion))
        {
            cout << endl << "Such a user exists. Enter another user name: ";
            nameSuggestion = readLine();
        }
        else
        {
            user.userName = nameSuggestion;
            break;
        }
    }

    cout << "Enter password: ";
    user.password = readLine();
    users.empty() ? user.userId = 1 : user.userId = users.back().userId + 1;

    users.push_back(user);
    writeNewUserInFile(user);
    cout << endl << "Account created." << endl;
    Sleep(1500);
}

int login(vector <User> users)
{
    string enteredName, enteredPassword;

    cout << endl << "Enter user name: ";
    enteredName = readLine();

    for (vector <User>::iterator itr = users.begin(); itr != users.end(); itr++)
    {
        if (itr -> userName == enteredName)
        {
            for (int attempt = 0; attempt < 3; attempt++)
            {
                cout << "Enter password. Attempts left " << 3 - attempt << ": ";
                enteredPassword = readLine();

                if (itr -> password == enteredPassword)
                {
                    cout << endl << "You logged in.";
                    Sleep(1500);
                    return itr -> userId;
                }
            }
            cout << endl << "You have entered the wrong password 3 times. Wait 3 seconds before next attempt.";
            Sleep(3000);
            return 0;
        }
    }
    cout << endl << "There is no user with that login.";
    Sleep(1500);
    return 0;
}

int main()
{
    vector <User> users;
    vector <Contact> contacts;
    int idOfLoggedInUser = 0;
    char choice;

    getUsersFromFile(users);
    //getContactsFromFile(contacts);

    while (true)
    {
        if (idOfLoggedInUser == 0)
        {
            system("cls");
            cout << "======================================" << endl;
            cout << ">>>>>>>>>>>>>> MAIN MENU <<<<<<<<<<<<<" << endl;
            cout << "======================================" << endl << endl;
            cout << "1. Create an account" << endl;
            cout << "2. Sign in" << endl;
            cout << "9. Close app" << endl;
            cout << "======================================" << endl;
            cout << "Your choice: ";
            choice = getChar();

            switch (choice)
            {
            case '1': registration(users); break;
            case '2': idOfLoggedInUser = login(users); break;
            case '9': exit(0); break;
            }
        }
        else
        {
            system("cls");
            cout << "======================================" << endl;
            cout << ">>>>>>>>>>>>>> USER MENU <<<<<<<<<<<<<" << endl;
            cout << "======================================" << endl << endl;
            cout << "1. Add new contact" << endl;
            cout << "2. Search by first name" << endl;
            cout << "3. Search by surname" << endl;
            cout << "4. Show all contacts" << endl;
            cout << "5. Delete contact" << endl;
            cout << "6. Edit contact" << endl;
            cout << "======================================" << endl;
            cout << "7. Change password" << endl;
            cout << "8. Sign out" << endl;
            cout << "======================================" << endl;
            cout << "Your choice: ";
            choice = getChar();

            switch (choice)
            {
            case '1': addContact(contacts); break;
            case '2': searchByFirstName(contacts); break;
            case '3': searchBySurname(contacts); break;
            case '4': showAllContacts(contacts); break;
            case '5': deleteContact(contacts); break;
            case '6': editContact(contacts); break;
            }
        }
    }
    return 0;
}
