#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
void ShowMainMenue();
void ShowTransactionsMenue();
void ManageUsersMenueScreen();
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};
struct sUser {
    string UserName;
    string Password;
    int Permissions = 0;
    bool MarkForDelete = false;
};
sUser CurrentUser;
vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; 

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;

}
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);


    return Client;

}
sUser ConvertLineToRecordForUsers(string Line, string Seperator = "#//#") {
    sUser user;
    vector<string> vUserData;
    vUserData = SplitString(Line, Seperator);
    user.UserName = vUserData[0];
    user.Password = vUserData[1];
    user.Permissions = stoi(vUserData[2]);
    return user;

}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}
struct sPermissions {
    int ListClients = 1; 
    int AddClients = 2;  
    int DeleteClients = 4;   
    int UpdateClient = 8;   
    int FindClient = 16;  
    int Transactions = 32;  
    int ManageUsers = 64; 

};
vector <sUser> LoadUsersDataFromFileUsers(string FileName)
{

    vector <sUser> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {

        string Line;
        sUser user;

        while (getline(MyFile, Line))
        {

            user = ConvertLineToRecordForUsers(Line);

            vUsers.push_back(user);
        }

        MyFile.close();

    }

    return vUsers;

}
string ReadUserName() {
    string UserName = "";

    cout << "\nPlease enter User name? ";
    getline(cin >> ws, UserName);
    return UserName;
}
enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };
enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6, eManageUsers = 7, eLogout = 8 };
enum enManageUsersOptions { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue = 6 };
bool FindUserByUserName(string UserName, vector <sUser> vUsers, sUser& User)
{

    for (sUser& Userr : vUsers)
    {

        if (Userr.UserName == UserName)
        {
            User = Userr;
            return true;
        }

    }
    return false;

}

void AccessDenied() {
    cout << "\n_________________________________\n";
    cout << "Access denied ,";
    cout << endl;
    cout << " You dont have Permission To do this, " << endl;
    cout << "PLease contact Your admin\n";
    cout << "\n_________________________________\n";
}
string ConvertRecordToLineForUsers(sUser user, string Seperator = "#//#")
{

    string stUserRecord = "";

    stUserRecord += user.UserName + Seperator;
    stUserRecord += user.Password + Seperator;
    stUserRecord += to_string(user.Permissions);

    return stUserRecord;

}
bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }


            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return false;


}
bool UserExistsByUsername(string UserName, string FileName)
{



    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {

        string Line;
        sUser user;

        while (getline(MyFile, Line))
        {
            user = ConvertLineToRecordForUsers(Line);
            if ((user.UserName == UserName))
            {
                MyFile.close();
                return true;
            }
        }

        MyFile.close();

    }

    return false;


}
bool UserExistsByUserNameOrPassword(string UserName, string Password, string FileName)
{

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {

        string Line;
        sUser user;

        while (getline(MyFile, Line))
        {
            user = ConvertLineToRecordForUsers(Line);
            if ((user.UserName == UserName) && (user.Password == Password))
            {
                CurrentUser = user;
                MyFile.close();
                return true;
            }
        }

        MyFile.close();

    }

    return false;


}
sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }


    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}
int ReadPermissions() {
    sPermissions Permission;
    sUser user;
    char yORn;
    cout << "Do you want to give access to:\n";
    cout << "Show Client list ? y/n?\n";
    cin >> yORn;
    if (yORn == 'y' || yORn == 'Y') {
        user.Permissions |= Permission.ListClients;

    }
    cout << "Add new client ? y/n?\n";
    cin >> yORn;
    if (yORn == 'y' || yORn == 'Y') {
        user.Permissions |= Permission.AddClients;

    }
    cout << "Delete client? y/n?\n";
    cin >> yORn;
    if (yORn == 'y' || yORn == 'Y') {
        user.Permissions |= Permission.DeleteClients;
    }
    cout << "Update client ? y/n?\n";
    cin >> yORn;
    if (yORn == 'y' || yORn == 'Y') {
        user.Permissions |= Permission.UpdateClient;
    }
    cout << "Find client ? y/n?\n";
    cin >> yORn;
    if (yORn == 'y' || yORn == 'Y') {
        user.Permissions |= Permission.FindClient;
    }
    cout << "Transactions ? y/n?\n";
    cin >> yORn;
    if (yORn == 'y' || yORn == 'Y') {
        user.Permissions |= Permission.Transactions;
    }
    cout << "Manage users ? y/n?\n";
    cin >> yORn;
    if (yORn == 'y' || yORn == 'Y') {
        user.Permissions |= Permission.ManageUsers;
    }
    return user.Permissions;
}
sUser ReadNewUser() {
    sUser User;
    char Access = 'y';
    cout << "Please Enter User Name?\n";
    cin >> User.UserName;
    while (UserExistsByUsername(User.UserName, UsersFileName))
    {
        cout << "\nClient with [" << User.UserName << "] already exists, Enter another User Name? ";
        getline(cin >> ws, User.UserName);
    }

    cout << "Please enter Password?\n";
    cin >> User.Password;

    cout << "Do You Want to Give Full access or not?\n";

    cin >> Access;
    if (Access != 'y' && Access != 'Y') {
        User.Permissions = ReadPermissions();
    }
    else {
        User.Permissions = -1;
    }
    return User;
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}
void PrintClientRecordLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}
void PrintUserRecordLine(sUser user)
{

    cout << "| " << setw(15) << left << user.UserName;
    cout << "| " << setw(10) << left << user.Password;
    cout << "| " << setw(40) << left << user.Permissions;

}
void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}
void ShowAllUsersScreen()
{


    vector <sUser> vUsers = LoadUsersDataFromFileUsers(UsersFileName);

    cout << "\n\t\t\t\t\tClient List (" << vUsers.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "username";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permission";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (sUser User : vUsers)
    {

        PrintUserRecordLine(User);
        cout << endl;
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
void ShowAllClientsScreen()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
void ShowTotalBalances()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

}
void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";

}
bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{

    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;

}
sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}
sUser ChangeUserRecord(string UserName) {
    sUser User;
    char Access = 'Y';
    User.UserName = UserName;
    cout << "Enter Password?\n";

    getline(cin >> ws, User.Password);
    cout << "Do You Want to Give Full access or not?\n";

    cin >> Access;
    if (Access != 'y' && Access != 'Y') {
        User.Permissions = ReadPermissions();
    }
    else {
        User.Permissions = -1;
    }
    return User;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;

}
bool MarkUserForDeleteByUserName(string UserName, vector<sUser>& Users)
{

    for (sUser& userSearch : Users)
    {

        if (userSearch.UserName == UserName)
        {
            userSearch.MarkForDelete = true;
            return true;
        }

    }

    return false;

}
vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}
vector <sUser> SaveUsersDataToFile(string FileName, vector <sUser> vUsers)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {

        for (sUser C : vUsers)
        {

            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLineForUsers(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vUsers;

}
void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}
void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}
void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}
void AddNewUser() {
    sUser userToAdd;
    userToAdd = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertRecordToLineForUsers(userToAdd));
}
void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        cout << "Adding New User:\n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";

        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}
bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);
            vClients = LoadCleintsDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}
bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }

            }

            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }

        }
        return false;
    }

}
string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}
void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);

}
void PrintUserCard(sUser User) {
    cout << "\nThe following are the User details:\n";
    cout << "-----------------------------------";
    cout << "\nUser name: " << User.UserName;
    cout << "\nPassword: " << User.Password;
    cout << "\nPermissions: " << User.Permissions;
    cout << "\n-----------------------------------\n";

}
bool DeleteUserBUserName(string UserName, vector <sUser>& vUsers)
{
    if (UserName == "Admin") {
        cout << "You Cant Delete this user \n";
    }
    else {
        sUser User;
        char Answer = 'n';
        if (FindUserByUserName(UserName, vUsers, User))
        {
            PrintUserCard(User);

            cout << "\n\nAre you sure you want delete this User? y/n ? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                MarkUserForDeleteByUserName(UserName, vUsers);
                SaveUsersDataToFile(UsersFileName, vUsers);

                //Refresh Clients 
                vUsers = LoadUsersDataFromFileUsers(UsersFileName);

                cout << "\n\nUser Deleted Successfully.";
                return true;
            }

        }
        else
        {
            cout << "\nUser with Account Number (" << UserName << ") is Not Found!";
            return false;
        }

    }
}
void ShowDeleteUserScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n-----------------------------------\n";
    vector <sUser> vUsers = LoadUsersDataFromFileUsers(UsersFileName);
    string UserName = ReadUserName();
    DeleteUserBUserName(UserName, vUsers);
}
void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}
bool UpdateUserByUserName(string UserName, vector<sUser>& vUsers) {
    sUser User;
    char Answer = 'n';
    if (FindUserByUserName(UserName, vUsers, User)) {
        PrintUserCard(User);
        cout << "\n\nAre you sure you want update this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sUser& Userr : vUsers)
            {

                if (Userr.UserName == UserName)
                {
                    Userr = ChangeUserRecord(UserName);
                    break;

                }

            }
        }
        SaveUsersDataToFile(UsersFileName, vUsers);
        cout << "User updated successfully\n";
        return true;
    }
    else {
        cout << "\nUser with User name (" << UserName << ") is Not Found!";
        return false;
    }
}
void ShowUpdateUserScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate User Info Screen";
    cout << "\n-----------------------------------\n";
    vector <sUser> vUsers = LoadUsersDataFromFileUsers(UsersFileName);
    string UserName = ReadUserName();
    UpdateUserByUserName(UserName, vUsers);
}
void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddNewClients();

}
void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}
void ShowFindUserScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";
    vector <sUser> vUsers = LoadUsersDataFromFileUsers(UsersFileName);
    string UserName = ReadUserName();
    sUser User;
    if (FindUserByUserName(UserName, vUsers, User)) {
        PrintUserCard(User);
    }
    else {
        cout << "\nUser wirh User name[" << UserName << "] is not found!";
    }

}
void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";

}
void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";
    sClient Client;
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }


    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}
void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";
    sClient Client;
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);
    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;
    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}
void ShowTotalBalancesScreen()
{
    ShowTotalBalances();
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}
void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();
}
short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowMainMenue:
    {
        ShowMainMenue();
    }
    }

}
void ShowTransactionsMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}
short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
short ReadManageMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
void CheckNameAndPassword()
{
    string Password;
    string UserName;
    int Perimssions = 0;
    cout << "Enter User name? ";
    cin >> UserName;
    cout << "Enter Password?\n";
    cin >> Password;
    while (!UserExistsByUserNameOrPassword(UserName, Password, UsersFileName))
    {
        cout << "Invalid Username/Password!\n";
        cout << "Enter User name? ";
        cin >> UserName;
        cout << "Enter Password?\n";
        cin >> Password;
    }

}
void ShowLogInScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tLogin Screen\n";
    cout << "===========================================\n";
    CheckNameAndPassword();
    ShowMainMenue();
}
void Logout() {
    ShowLogInScreen();
}
void GoBackToManageUsersMenue() {
    cout << "\n\nPress any key to go back to Manage users Menue...";
    system("pause>0");
    ManageUsersMenueScreen();
}
void PerformManageUsersOptions(enManageUsersOptions ManageUsersOptions) {

    switch (ManageUsersOptions) {
    case enManageUsersOptions::eAddNewUser: {
        system("cls");

        AddNewUsers();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eListUsers: {
        system("cls");
        ShowAllUsersScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eFindUser: {
        system("cls");
        ShowFindUserScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eDeleteUser: {
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eUpdateUser: {
        system("cls");
        ShowUpdateUserScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eMainMenue: {
        ShowMainMenue();
        break;
    }

    }
}
void ManageUsersMenueScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tManage Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Users List.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User Info.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6]Main Menue.\n";
    PerformManageUsersOptions(enManageUsersOptions(ReadManageMenueOption()));
}
bool CheckAccess(int Permission)
{
    if (CurrentUser.Permissions == -1)
        return true;

    return (CurrentUser.Permissions & Permission);
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    sPermissions Permission;
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        if (CheckAccess(Permission.ListClients)) {
            system("cls");
            ShowAllClientsScreen();
            GoBackToMainMenue();
        }
        else { AccessDenied(); }
        break;
    }
    case enMainMenueOptions::eAddNewClient: {
        if (CheckAccess(Permission.AddClients)) {
            system("cls");
            ShowAddNewClientsScreen();
            GoBackToMainMenue();
        }
        else { AccessDenied(); }
        break;
    }
    case enMainMenueOptions::eDeleteClient: {
        if (CheckAccess(Permission.DeleteClients)) {
            system("cls");
            ShowDeleteClientScreen();
            GoBackToMainMenue();
        }
        else { AccessDenied(); }
        break;
    }
    case enMainMenueOptions::eUpdateClient: {
        if (CheckAccess(Permission.UpdateClient)) {
            system("cls");
            ShowUpdateClientScreen();
            GoBackToMainMenue();
        }
        else { AccessDenied(); }
        break;
    }
    case enMainMenueOptions::eFindClient: {
        if (CheckAccess(Permission.FindClient)) {
            system("cls");
            ShowFindClientScreen();
            GoBackToMainMenue();
        }
        else {
            AccessDenied();
        }
        break;
    }
    case enMainMenueOptions::eShowTransactionsMenue: {
        if (CheckAccess(Permission.Transactions)) {
            system("cls");
            ShowTransactionsMenue();
        }
        else {
            AccessDenied();
        }
        break;
    }
    case enMainMenueOptions::eManageUsers: {
        if (CheckAccess(Permission.ManageUsers)) {
            system("cls");
            ManageUsersMenueScreen();
        }
        else {
            AccessDenied();
        }
        break;
    }
    case enMainMenueOptions::eLogout: {
        system("cls");
        Logout();
        break;
    }
    }
   }
void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
int main()

{
    ShowLogInScreen();
    system("pause>0");
    return 0;

}
