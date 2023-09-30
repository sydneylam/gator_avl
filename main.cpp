#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include "AVLTree.h"

using namespace std;

//Checking if IDs are all digits and of length 8
bool checkID(string id) {
    bool validLength = true;
    bool validDigits = true;

    for (int i = 0; i < id.length(); i++) {
        if (!isdigit(id[i])) {
            validDigits = false;
            return false;
        }
    }
    if (id.length() != 8)
    {
        validLength = false;
        return false;
    }

    if (validDigits && validLength)
        return true;

    return false;
}

//Using regex to check if the string is all letters and spaces only
bool checkName(string name)
{
    return std::regex_match(name, regex("^[a-zA-Z\\s]*$"));
}

int main()
{
    AVLTree gatorAVL;
    int numCommands;
    cin >> numCommands;
    string command;

    //Completing commands equal to amount of commands specified
    do
    {
        cin >> command;

        if (command == "insert")
        {
            string name;
            string subName;
            string studentID;
            cin >> name;
            cin >> studentID;

            subName = name;
            subName.erase(remove(subName.begin(), subName.end(), '\"'), subName.end());
            subName.erase(remove(subName.begin(), subName.end(), '"'), subName.end());

            //Gets rid of the parenthesis from the name when it was read in
            if (checkName(subName) && checkID(studentID))
            {
                gatorAVL.setRoot(gatorAVL.insert(gatorAVL.getRoot(), name, stoi(studentID)));
                cout << "successful" << endl;
            }
            else
            {
                cout << "unsuccessful" << endl;
                cout << "unsuccessful" << endl;
                cout << "unsuccessful" << endl;
            }

        }
        else if (command == "remove")
        {
            string studentID;
            cin >> studentID;

            if(checkID(studentID) == true)
            {
                gatorAVL.remove(gatorAVL.getRoot(), stoi(studentID));
            }
            else
            {
                cout << "unsuccessful" << endl;
            }

        }
        else if (command == "search")
        {
            string data;
            string name;
            cin >> data;

            //If the data read in after the command is a ", then it is a name. If not, analyze it as an ID
            if(data[0] == '"')
            {
                if(checkName(data.substr(1,data.length()-2)))
                {
                    gatorAVL.searchName(gatorAVL.getRoot(), data);
                }

            }
            else //analyzing as an ID
            {
                if (checkID(data))
                {
                    auto node = gatorAVL.searchID(gatorAVL.getRoot(), stoi(data));
                    if (node != nullptr) {
                        name = node->studentName;
                        cout << name.substr(1,name.length()-2) << endl;
                    }

                }
            }

        }
        else if (command == "printInorder")
        {
            gatorAVL.printInOrder(gatorAVL.getRoot());
        }
        else if (command == "printPreorder")
        {
            gatorAVL.printPreOrder(gatorAVL.getRoot());
        }
        else if (command == "printPostorder")
        {
            gatorAVL.printPostOrder(gatorAVL.getRoot());
        }
        else if (command == "printLevelCount")
        {
            gatorAVL.printLevelCount(gatorAVL.getRoot());
        }
        else if (command == "removeInorder")
        {

            string studentID;
            cin >> studentID;
            gatorAVL.removeInOrder(gatorAVL.getRoot(), stoi(studentID));

        }

        numCommands--;
    } while (numCommands != 0);

}
