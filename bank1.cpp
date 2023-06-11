#include <iostream>
#include <cstdlib>
using namespace std;

class accountInfo {
    protected:
        double balance;
        int no_deposits=0;
        int no_withdrawals=0; 
        double aInterestRate;
        double init_balance=0;
        double end_balance = 0; 
        double mCharges=0;
    public:
        accountInfo(double bal = 0, double aIR = 0.01);
        void virtual deposit(double amount);
        void virtual withdraw(double amount);
        void virtual calcInt();
        void virtual monthlyProc();


};

accountInfo::accountInfo(double bal, double aIR){
            balance = bal;
            init_balance = bal;
            aInterestRate = aIR;   
}

void accountInfo::deposit(double amount){
    balance += amount;
    no_deposits += 1;

}

void accountInfo::withdraw(double amount){
    balance -= amount;
    no_withdrawals += 1;
    
}

void accountInfo::calcInt(){
    double mInterestRate = aInterestRate/12;
    double mInterest = balance * mInterestRate;
    balance += mInterest;


}

void accountInfo::monthlyProc(){
    accountInfo::calcInt();
    end_balance = balance; 
    no_deposits = 0;
    no_withdrawals = 0;
    init_balance = end_balance;



}


class Savings : protected accountInfo{
    private:
    double sTot_withdrawals = 0;
    double sTot_deposits = 0;
    bool status;
    public: 
    void Status()
    {
        if (balance < 25){
          status = false ;
          cout << "Inactive" << endl;
       }

        else{
            status = true;
            cout << "Active" << endl;
       }
    }

    void withdraw(double amount)
    {
        int extra;
        if (status){
            accountInfo::withdraw(amount);
            sTot_withdrawals += amount;
            if (no_withdrawals > 4){
                extra = no_withdrawals - 4;
                mCharges = mCharges + extra;
            }
       }
    }

    void deposit(double amount)
    {
        if((amount+balance) > 25 ){
            status = true;
            accountInfo::deposit(amount);

        }

        else {
            accountInfo::deposit(amount);
        }

        sTot_deposits += amount;
    
    }

    void monthlyProc(){
        balance -= mCharges;
        end_balance = balance;
        accountInfo::monthlyProc();
        mCharges = 0;
        Status();
    }

    void print_stats(){
    cout << "Total amount of deposits: "<< sTot_deposits << endl;
    cout << "Total amount of withdrawls: " << sTot_withdrawals << endl;
    cout << "Service Charge: " << mCharges << endl;
    cout << "Beginning Balance: " << init_balance << endl;
    cout << "End Balance: " << balance << endl;
        

}

};



class Checking : protected accountInfo{
    private:
    double cTot_withdrawals = 0;
    double cTot_deposits = 0;
    public:
        void deposit(double amount){
            accountInfo::deposit(amount);
            cTot_deposits += amount;
        }
        void withdraw(double amount){
            if ((balance - amount) < 0){
                balance -= 15;
            }
            accountInfo::withdraw(amount);

            cTot_withdrawals += amount;
            mCharges += (5 + 0.10*no_withdrawals);
        }

        void monthlyProc(){
            balance -= mCharges;
            end_balance = balance;
            accountInfo::monthlyProc();
            mCharges = 0;

        }



        void print_stats(){
            cout << "Total amount of deposits: "<< cTot_deposits << endl;
            cout << "Total amount of withdrawls: " << cTot_withdrawals << endl;
            cout << "Service Charge: " << mCharges << endl;
            cout << "Beginning Balance: " << init_balance << endl;
            cout << "End Balance: " << balance << endl;
        

}

        
};




int main(){

    Savings saving1;
    Checking checking1;
    int choice;
    double amount; 


    do {
        cout << "Bank Account menu: " << endl;
        cout << "1. Savings account deposits: " << endl;
        cout << "2. Savings account withdraw: " << endl;
        cout << "3. Checking account deposits " << endl;
        cout << "4. Checking account withdraw: " << endl;
        cout << "5. Monthly statistics calculation: " << endl;
        cout << "6. statistics print: " << endl;
        cout << "7. Exit: " << endl;
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                cout << "Enter amount you are depositing: " << endl;
                cin >> amount;
                saving1.deposit(amount);
                break;

            case 2:
                cout << "Enter amount you are withdrawing: " << endl;
                cin >> amount;
                saving1.withdraw(amount);
                break;

            case 3:
                cout << "Enter amount you are depositing: " << endl;
                cin >> amount;
                checking1.deposit(amount);
                break;

            case 4:
                cout << "Enter amount you are withdrawing: " << endl;
                cin >> amount;
                checking1.withdraw(amount);
                break;

            case 5:
                saving1.monthlyProc();
                checking1.monthlyProc();
                break;
            
            case 6:
                cout << "Saving account stats: " << endl;
                saving1.print_stats();
                cout << endl;
                cout << "checking account stats: " << endl;
                checking1.print_stats();
                cout << endl;

            case 7:
                break;
            
            default:
                cout << "Invalid input" << endl;
                break;


        }


    }
    while(choice != 7);
    return 0;
}