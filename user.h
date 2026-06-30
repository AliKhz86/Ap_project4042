#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
class user
{
private:
    string name;
    string username;
    string  phone_number;
    string email_addres;
    string password;//رمز هش شده

    void HashPassword(const string& rawpassword);


public:
    user(string nam,string usnam,string phone_n,string email_add,string pass);

    //getters for check possible login or ...

    string getName() const;

    string getUsername() const;

    string getPhone_number()const;

    string getEmail_addres()const;

    string getPassword()const;

    //setters for edit information

    void setUsername(const string& usname);

    void setName(const string& nam);

    void setPhone_number(const string& phnum);

    void setEmailَ_address(const string& emailad);

    void setPassword(const string& pass);

    //check possible information

    bool isValidPhone_number(const string& phone_num) const;

    bool isValidEmail(const string& email_add) const;

    bool isValidPassword(const string& passw)const;

    bool checkPassword(const string& pass)const;

    bool checkUsername(const string& usnam) const ;

    //hash









};

#endif // USER_H
