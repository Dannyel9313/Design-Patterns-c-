#include <iostream>
#include <ostream>
#include <vector>

class Account
{
    int balance = 0;
    int overdraft_limit = -1000;
public:
    void deposit_money(int money)
    {
        balance += money;
        std::cout << "You deposit " << money
                  << " lv and your balance is " << balance << std::endl;
    }
    void withdraw_money(int money)
    {
        if((balance - money) > overdraft_limit)
        {
            balance -= money;
            std::cout << "You withdraw " << money
                      << " lv and your balance is " << balance << std::endl;
        }
    }
    friend std::ostream& operator<<(std::ostream& os,const Account& obj)
    {
        os << "Balance: " << obj.balance << "\n";
        return os;
    }

};


class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class MachineCommands :  public Command
{
    Account& account;
    int amount;
public:
    enum Action
    {
        eDeposit,
        eWithDraw
    } action;

    MachineCommands(Account& acc, const Action action, int money_amount)
        :account(acc),
         action(action),
         amount(money_amount){}

    void execute() override
    {
        switch (action)
        {
            case eDeposit:
                account.deposit_money(amount);
            break;
            case eWithDraw:
                account.withdraw_money(amount);
            break;
        }
    }

    void undo() override
    {
        switch (action)
        {
        case eDeposit:
            account.withdraw_money(amount);
        break;
        case eWithDraw:
            account.deposit_money(amount);
        break;
        }
    }


};


int main(int argc, char *argv[])
{
    Account acc;
    std::vector<MachineCommands> commands = {
                                {acc, MachineCommands::Action::eDeposit, 150},
                                {acc, MachineCommands::Action::eDeposit, 100},
                                {acc, MachineCommands::Action::eWithDraw, 230},
                                            };
    std::cout << acc;
    for(auto& cmd : commands)
    {
        cmd.execute();
    }
    std::cout << acc;
    for(auto& cmd : commands)
    {
        cmd.undo();
    }
    std::cout << acc;


    return 0;
}
