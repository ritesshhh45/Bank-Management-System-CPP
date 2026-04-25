#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Account {
public:
    int accNo;
    string name;
    int age;
    float balance;
    string password;

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Set Password: ";
        cin >> password;

        cout << "Enter Initial Balance: ";
        cin >> balance;

        cout << "Account Created Successfully!\n";
    }

    void display() {
        cout << "\n--- ACCOUNT DETAILS ---\n";
        cout << "Acc No: " << accNo << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Balance: " << balance << endl;
    }
};

// Load all accounts
vector<Account> loadAccounts() {
    vector<Account> accs;
    ifstream file("bankdata.txt");

    Account a;
    while (file >> a.accNo >> a.name >> a.age >> a.balance >> a.password) {
        accs.push_back(a);
    }
    file.close();
    return accs;
}

// Save all accounts (overwrite)
void saveAccounts(vector<Account> &accs) {
    ofstream file("bankdata.txt");

    for (auto &a : accs) {
        file << a.accNo << " " << a.name << " "
             << a.age << " " << a.balance << " "
             << a.password << endl;
    }
    file.close();
}

// Search account
int findAccount(vector<Account> &accs, int accNo) {
    for (int i = 0; i < accs.size(); i++) {
        if (accs[i].accNo == accNo)
            return i;
    }
    return -1;
}

// Admin Login
bool adminLogin() {
    string user, pass;
    cout << "Admin Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    return (user == "admin" && pass == "1234");
}

// User Login
int userLogin(vector<Account> &accs) {
    int accNo;
    string pass;

    cout << "Enter Account No: ";
    cin >> accNo;
    cout << "Enter Password: ";
    cin >> pass;

    int index = findAccount(accs, accNo);

    if (index != -1 && accs[index].password == pass) {
        cout << "Login Successful!\n";
        return index;
    }

    cout << "Invalid Login!\n";
    return -1;
}

// MAIN
int main() {
    vector<Account> accounts = loadAccounts();
    int choice;

    cout << "\n1. Admin Login\n2. User Login\nChoice: ";
    cin >> choice;

    // ================= ADMIN =================
    if (choice == 1) {
        if (!adminLogin()) {
            cout << "Wrong Admin Credentials!\n";
            return 0;
        }

        do {
            cout << "\n===== ADMIN MENU =====\n";
            cout << "1. Create Account\n";
            cout << "2. View All Accounts\n";
            cout << "3. Delete Account\n";
            cout << "4. Exit\n";
            cout << "Enter Choice: ";
            cin >> choice;

            if (choice == 1) {
                Account a;
                a.createAccount();
                accounts.push_back(a);
                saveAccounts(accounts);
            }

            else if (choice == 2) {
                for (auto &a : accounts)
                    a.display();
            }

            else if (choice == 3) {
                int accNo;
                cout << "Enter Account No to Delete: ";
                cin >> accNo;

                int index = findAccount(accounts, accNo);

                if (index != -1) {
                    accounts.erase(accounts.begin() + index);
                    saveAccounts(accounts);
                    cout << "Account Deleted!\n";
                } else {
                    cout << "Account Not Found!\n";
                }
            }

        } while (choice != 4);
    }

    // ================= USER =================
    else if (choice == 2) {
        int index = userLogin(accounts);

        if (index == -1) return 0;

        do {
            cout << "\n===== USER MENU =====\n";
            cout << "1. Deposit\n";
            cout << "2. Withdraw\n";
            cout << "3. View Account\n";
            cout << "4. Exit\n";
            cout << "Enter Choice: ";
            cin >> choice;

            if (choice == 1) {
                float amt;
                cout << "Enter Amount: ";
                cin >> amt;

                if (amt > 0) {
                    accounts[index].balance += amt;
                    saveAccounts(accounts);
                    cout << "Deposited!\n";
                } else {
                    cout << "Invalid Amount!\n";
                }
            }

            else if (choice == 2) {
                float amt;
                cout << "Enter Amount: ";
                cin >> amt;

                if (amt > accounts[index].balance) {
                    cout << "Insufficient Balance!\n";
                } else {
                    accounts[index].balance -= amt;
                    saveAccounts(accounts);
                    cout << "Withdrawn!\n";
                }
            }

            else if (choice == 3) {
                accounts[index].display();
            }

        } while (choice != 4);
    }

    return 0;
}