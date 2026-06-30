#include "user.h"
#include <string>
using namespace std;
#include <QCryptographicHash>
user::user(string nam,string usnam,string phone_n,string email_add,string pass)
    :name(nam),username(usnam),phone_number(phone_n),email_addres(email_add),password(pass)
{

}
string user::getName()
{
    return name;
}

string user::getUsername()
{
    return username
}

string user::getPhone_number()
{
    return phone_number
}

string user:: getEmail_addres()
{
    return email_addres
}

string user::getPassword()
{
    return password
}
//setters for edit information

void user::setUsername(const string& usname)
{
    username = usname;
}

void user::setName(const string& nam)
{
    name = nam;
}

void user::setPhone_number(const string& phnum)
{
    phone_number = phnum;
}

void user::setEmail_addres(const string& emailad)
{
    email_addres = emailed;
}

void user::setPassword(const string& pass)
{
    pasword = pass;
}

//check possible information

bool user::isValidPhone_number(const string& phone_num) const
{

    if (phone_num[0]!='0' || phone_num[1] != '9' || phone_num.length()!=11)
    {
        return false;
    }
    for(int i=0;i<phone_num.length();i++)
    {
        if(!isdigit(phone_num[i]))
        {return false;}

    }
    return true;
}

bool user::isValidEmail_address(const string& email_add)
{
    int d = email_add.find('@');
    int r = email_add.find('.',d+1);
    string temp = email_add.substr(0,d);
    string temp1 = email_add.substr(d+1,r-d-1);
    string temp2 = email_add.substr(r + 1);


    if (d == std::npos
        || r ==std::npos
        ||r<=d  || temp.length()==0
        ||temp1.length()==0
        ||temp2.length() == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool user::isValidPassword(const string& passw) const
{
    bool hasupper = false;

    bool haslower = false;

    bool hasdigit = false;

    bool hassymbol = false;

    if (passw.length()<8)
    {
        return false;
    }

    for(int h=0;h<passw.length();h++)
    {
        if(isupper(passw[h]))
            hasupper = true;

        else if(islower(passw[h]))
            haslower = true;

        else if(isdigit(passw[h]))
            hasdigit = true;

        else
        {hassymbol = true;}


    }

}
bool user::checkPassword(const string& pass) const
{
    QByteArray temp3 = pass.toUtf8();
    QByteArray hash2 = QCryptographicHash::hash(temp3,QCryptographicHash::sha256);

    return ( hash2.toHex().toStdString()==password);
}

bool user::checkUsername(const string& usnam) const
{
     return (username == usnam);
}

//hash

void user::HashPassword(const string& rawpassword)
{
    QByteArray temp = rawpassword.toUtf8();
    QByteArray hash = QCryptographicHash::hash(temp,QCryptographicHash::sha256);
    password =hash.toHex().toStdString();
}
