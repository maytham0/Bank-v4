#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputvalidate.h"
#include "clsString.h"
#include "clsDate.h"
#include "Global.h"
class clsTransferScreen :protected clsScreen
{

private :
	string _Date;
	string _SACC;
	string _DAcc;
	string _Amount;
	string _SBalance;
	string _DBalance;
	string _USER;
	//   *
	//  / \
	//   |
	//   |
	//   |
	//   |
	//Need Get&Set
	static string _PrintClintCard()
	{

		string AccNum;
		getline(cin>>ws, AccNum);
		while (!clsBankClient::IsClientExist(AccNum))
		{
			cout << "\nNo Found !\n";
			getline(cin, AccNum);
		}
		clsBankClient client=clsBankClient::Find(AccNum);
		cout << "\nClient Card \n";
		cout << "---------------------\n";
		cout<<"\nFull Name :" << client.FullName();
		cout << "\nAcc. Number :" <<client.AccountNumber();
		cout << "\nAcc.Balanc :" << client.AccountBalance;
		cout << "\n---------------------\n";
		return AccNum;
	}
	static void _ClientCard(clsBankClient Client)
	{
		cout << "\nClient Card \n";
		cout << "---------------------\n";
		cout << "\nFull Name :" << Client.FullName();
		cout << "\nAcc. Number :" << Client.AccountNumber();
		cout << "\nAcc.Balanc :" << Client.AccountBalance;
		cout << "\n---------------------\n";
	}

    static	string _ConverRecordToLine(clsBankClient ClientFrom,clsBankClient ClientTo,double Amount,string Sepreator="#//#")
	{
		string Record = "";
		Record += clsDate::DateToStringWith_HMS(clsDate::SystemDateWithPerSec()) + Sepreator;
		Record += ClientFrom.AccountNumber() + Sepreator;
		Record += ClientTo.AccountNumber() + Sepreator;
		Record +=to_string (Amount) + Sepreator;
		Record += to_string (ClientFrom.AccountBalance )+ Sepreator;
		Record += to_string (ClientTo.AccountBalance) + Sepreator;
		Record += CurrentUser.UserName;
		return Record;

	} 
	static void _SaveTransferHistory( clsBankClient ClientFrom, clsBankClient ClientTo, double Amount)
	{
		fstream Myfile;
		Myfile.open("TransferHistory.txt", ios::out | ios::app);
		
		string DataOfRecord = _ConverRecordToLine(ClientFrom, ClientTo, Amount);
		if (Myfile.is_open())
		{
			Myfile << DataOfRecord << endl;

			Myfile.close();
		}
	}

	static clsTransferScreen _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vTransfer;
		vTransfer = clsString::Split(Line, Seperator);

		return clsTransferScreen(vTransfer[0], vTransfer[1], vTransfer[2],
			vTransfer[3], vTransfer[4], vTransfer[5], vTransfer[6]);

	}
	static vector<clsTransferScreen>_LoadDataFromFileTotrnsferLog()
	{
		vector <clsTransferScreen>vTransfer;
		fstream Myfile;

		Myfile.open("TransferHistory.txt", ios::in);
		string Line;
		if (Myfile.is_open())
		{
			while (getline(Myfile, Line))
			{
				 clsTransferScreen TransferHis=_ConvertLinetoClientObject(Line);
				vTransfer.push_back(TransferHis);
		     }
			Myfile.close();
		}
		return vTransfer;
	}
	static void PrintTransferLogRecordLine(clsTransferScreen TransferLogRecord)
	{

		cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord._Date;
		cout << "| " << setw(8) << left << TransferLogRecord._SACC;
		cout << "| " << setw(8) << left << TransferLogRecord._DAcc;
		cout << "| " << setw(8) << left << TransferLogRecord._Amount;
		cout << "| " << setw(10) << left << TransferLogRecord._SBalance;
		cout << "| " << setw(10) << left << TransferLogRecord._DBalance;
		cout << "| " << setw(8) << left << TransferLogRecord._USER;


	}

public :
	clsTransferScreen(string date, string SAcc, string DAcc, string Amount, string SBalanc, string DBalanc, string User)
	{

		_Date = date;
		_SACC = SAcc;
		_DAcc = DAcc;
		_Amount=Amount	;
		_SBalance=SBalanc;
		_DBalance=DBalanc;
		_USER=User;

	}
	static void ShowTransfer()
	{
		
		_DrawScreenHeader("Transfer Screen");
	
		cout << "Enter Acc Number To transfer From :";
		clsBankClient ClientFrom=clsBankClient::Find (_PrintClintCard());
		//withdrow
		//check max of withdrow from this 

		cout << "\nEnter Acc Number To transfer To :";
		clsBankClient ClientTo = clsBankClient::Find(_PrintClintCard());
		//deposit
		cout << "\nHow Many Amount do you wont transfer ? ";
		double Amount = clsInputValidate::ReadDblNumber();
		while (Amount > ClientFrom.AccountBalance)
		{
			cout << "Amount Exited the avalibal balanc ,Enter Another amount ?";
			Amount = clsInputValidate::ReadDblNumber();
		}
		char Answer = 'n';
		cout << "Are you sure to perform this opreion (y/n)?";
		cin >> Answer;
		if (Answer == 'y' || 'Y')
		{
			ClientFrom.AccountBalance -= Amount;
			ClientTo.AccountBalance += Amount;
			ClientFrom.Save();
			ClientTo.Save();
			cout << "\ntransfer done Successfuly\n";
			_SaveTransferHistory(ClientFrom, ClientTo, Amount);

			_ClientCard(ClientFrom);
			cout << endl;
			_ClientCard(ClientTo);
		}
	}
	static void ShowLogTransfer()
	{

		_DrawScreenHeader("\tTransfer Log List Screen");

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
		cout << "| " << left << setw(8) << "s.Acct";
		cout << "| " << left << setw(8) << "d.Acct";
		cout << "| " << left << setw(8) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(8) << "User";

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;



		for (clsTransferScreen& TransRec : _LoadDataFromFileTotrnsferLog())
		{
			PrintTransferLogRecordLine(TransRec);
			cout << endl;
		}

	}
};

