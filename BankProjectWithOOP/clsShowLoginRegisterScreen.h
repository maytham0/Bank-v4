#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsDate.h"
#include <iomanip>
#include <vector>
class clsShowLoginRegisterScreen : protected clsScreen 

{
    string _DateLogin;
    string _LogUser;
    string _Pass;
    string _Pirmission;
    

    static clsShowLoginRegisterScreen _ConvertLinetoLogUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsShowLoginRegisterScreen( vUserData[0], vUserData[1], vUserData[2],
            vUserData[3]);

    }
  static  vector <clsShowLoginRegisterScreen>_vLoadDataFromFile()
    {
        vector <clsShowLoginRegisterScreen> vUsers;

        fstream MyFile;
        MyFile.open("LogUser.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsShowLoginRegisterScreen LogUser = _ConvertLinetoLogUserObject(Line);

                vUsers.push_back(LogUser);
            }

            MyFile.close();

        }

        return vUsers;
    }
  static  void _PrintUserLogCard(clsShowLoginRegisterScreen LogUSER)
    {

      cout << setw(8) << left << "" << "| " << setw(28) << left << LogUSER._DateLogin;
      cout << "| " << setw(20) << left << LogUSER._LogUser;
      cout << "| " << setw(12) << left << LogUSER._Pass;
      cout << "| " << setw(20) << left << LogUSER._Pirmission  ;
       
    }
public :

    clsShowLoginRegisterScreen(string LogDate, string UserLog, string Pass, string pirmisson)
    {
        _DateLogin = LogDate;
        _LogUser = UserLog;
        _Pass = Pass;
        _Pirmission = pirmisson;

    }

  static  void ShowRegisteUser()
    {
      if (!CheckAccessRights(clsUser::enPermissions::pHistoryRegister))
      {
          return;// this will exit the function and it will not continue
      }
        vector <clsShowLoginRegisterScreen>vLogUser = _vLoadDataFromFile();
        string Title = "\t  Register List Screen";
        string SubTitle = "\t    (" + to_string(vLogUser.size()) + ") Register(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout <<left <<setw(28) << "Register Date"
            << left<<"| " << setw(20) << "User Name"
            << left<<"| " << setw(20) << "Password"
            << "| " << setw(20) << "Permission"
            << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLogUser.empty())
            cout << "\t\t\t\tNo Register Available In the System!";
        else

            for (clsShowLoginRegisterScreen LogUserCard : vLogUser)
            {

                _PrintUserLogCard(LogUserCard);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

};

