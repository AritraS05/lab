class BankAccount{
    int AccountNumber;
    float balance;
    String ownerName;
    BankAccount(int accNo, float bal, String owner){
        AccountNumber = accNo;
        balance = bal;
        ownerName = owner;
    }
    void add(int amt){
        balance += amt;
    }
    void subtract(int amt){
        balance -= amt;
    }
}
class AccountManager{
    BankAccount[] accounts;
    AccountManager(int noOfAccounts){
        accounts = new BankAccount[noOfAccounts];
    }
    void create(int accNo, float bal, String owner){
        accounts[accNo] = new BankAccount(accNo, bal, owner);
    }
    void delete(int accNo){
        accounts[accNo] = null;
    }
    void deposit(int accNo, int amt){
        accounts[accNo].add(amt);
    }
    void withdraw(int accNo, int amt){
        accounts[accNo].subtract(amt);
    }
    void display(){
        System.out.println("Account No.\t\tBalance\t\tOwner");
        for(int i = 0; i<accounts.length; i++){
            if(accounts[i] != null){
                System.out.println(i+"\t\t"+accounts[i].balance+"\t\t"+accounts[i].ownerName);
            }
        }
    }
}

class Bank{
    public static void main(String[] args){
        AccountManager am = new AccountManager(5);
        for(int i = 0; i<5; i++){
            am.create(i, 1000*i," owner");
        }
        am.display();
    }
}