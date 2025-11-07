#include <iostream>
using namespace std;

class Bank {
private:
    string name;
    int accno;
    double balance;
    static int count;

public:
    Bank() {
        name = "";
        accno = 0;
        balance = 0.0;
        count++;
    }
    Bank(string n, int a, double b) {
        name = n;
        accno = a;
        balance = b;
        count++;
    }
    ~Bank() {
        cout << "Destructor called for account: " << name << endl;
        count--;
    }

    void deposit(double amount) {
        balance += amount;
    }
    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            cout << "Insufficient funds for " << name << endl;
        }
    }
    void transfer(Bank &receiver, double amount) {
        if (amount <= balance) {
            withdraw(amount);
            receiver.deposit(amount);
            cout << "Transferred " << amount << " from " << name
                 << " to " << receiver.name << endl;
        } else {
            cout << "Not enough funds to transfer from " << name << endl;
        }
    }
    void display() const {
        cout << "Name: " << name << "\tAccount No: " << accno
             << "\tBalance: " << balance << endl;
    }
    Bank mergeAccount(const Bank &other) const {
        Bank temp;
        temp.name = name + "&" + other.name;
        temp.accno = accno + other.accno;
        temp.balance = balance + other.balance;
        return temp;
    }
    static void showCount() {
        cout << "Number of active accounts: " << count << endl;
    }
};

int Bank::count = 0;
int main() {
    Bank account[2] = {
        Bank("HARISH", 125, 5000),
        Bank("NITHYA", 126, 4000)
    };

    cout << "__Account Details__" << endl;
    for (int i = 0; i < 2; i++) {
        account[i].display();
    }

    Bank::showCount();

    account[0].transfer(account[1], 1000);

    cout << "\n--- After transfer ---" << endl;
    for (int i = 0; i < 2; i++) {
        account[i].display();
    }

    Bank merged = account[0].mergeAccount(account[1]);
    cout << "\n-- Merged Account --" << endl;
    merged.display();

    Bank::showCount();

    return 0;
}
