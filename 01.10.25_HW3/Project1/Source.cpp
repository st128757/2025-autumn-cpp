#include <iostream>
#include <string>
#include <vector>

class BankAccount {
private:
	std::string accountNumber;
	double balance;
	std::string accountHolder;
public:
	BankAccount(const std::string& a = "NONUMBER", const double& b = 0, const std::string& c = "NOHOLDER") {
		accountNumber = a;
		balance = b;
		accountHolder = c;
	}

	void Deposit(double& cash) {
		balance += cash;
		std::cout << "Operation is completed\n";
	}

	void Withdraw(double& amount)
	{
		if (balance - amount < 0) {
			std::cout << "It's not enough money on the balance. Operation wasn't completed\n";
		}
		else {
			balance -= amount;
			std::cout << "Operation is completed\n";
		}
	}

	double GetBalance() {
		return balance;
	}

	std::string GetAccountHolder() {
		return accountHolder;
	}

	std::string GetAccountNumber() {
		return accountNumber;
	}

	void PrintAccountInfo() {
		std::cout << "Your balance is " << balance << "\n";
		std::cout << accountHolder << "\n";
		std::cout << accountNumber << "\n";
	}
};

class Bank {
private:
	std::vector<BankAccount> accounts;
public:
	void AddAccount(std::string& accName, std::string& accNumber, double& balance)
	{
		BankAccount A(accNumber, balance, accName);
		accounts.push_back(A);
	}
	void GetTotalBalance() {
		double total = 0.0;
		for (BankAccount& account : accounts) {
			total += account.GetBalance();
		}
		std::cout << "Total balance is: " << total;
	}

	void PrintAllAccounts() {
		for (BankAccount& account : accounts) {
			std::cout << "Holdername: " << account.GetAccountHolder() << "\n"
				<< "Accountnumber: " << account.GetAccountNumber() << "\n"
				<< "Balance: " << account.GetBalance() << "\n";
		}
	}
};

int main() {
	// Создаем банк
	Bank bank;

	// Данные для счетов
	std::string name1 = "John Doe", number1 = "123456789";
	std::string name2 = "Jane Smith", number2 = "987654321";
	std::string name3 = "Bob Johnson", number3 = "555555555";
	double balance1 = 1000.0, balance2 = 2500.0, balance3 = 500.0;

	// Добавляем счета в банк
	bank.AddAccount(name1, number1, balance1);
	bank.AddAccount(name2, number2, balance2);
	bank.AddAccount(name3, number3, balance3);

	// Выводим информацию о всех счетах
	bank.PrintAllAccounts();

	// Проверяем общий баланс
	bank.GetTotalBalance();

	// Демонстрация операций с одним счетом
	std::cout << "\n=== ACCOUNT OPERATIONS ===\n";
	BankAccount account("111111111", 2000.0, "Alice Brown");
	account.PrintAccountInfo();

	double deposit = 500.0;
	std::cout << "Depositing " << deposit << "...\n";
	account.Deposit(deposit);

	double withdraw = 300.0;
	std::cout << "Withdrawing " << withdraw << "...\n";
	account.Withdraw(withdraw);

	// Попытка снять слишком много
	double bigWithdraw = 3000.0;
	std::cout << "Attempting to withdraw " << bigWithdraw << "...\n";
	account.Withdraw(bigWithdraw);

	account.PrintAccountInfo();

	return 0;
}