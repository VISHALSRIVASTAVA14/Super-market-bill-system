#include<iostream>
#include<fstream>
#include<sstream> // for converting any datatype into string
#include<windows.h>
using namespace std;

class Bill
{
    public:
    string Item;
    int Rate,Quantity;

    public:
    Bill():Item(""),Rate(0),Quantity(0){}

    void set_item(string item)
    {
        Item=item;
    }
    void set_rate(int rate)
    {
        Rate=rate;
    }
    void set_quantity(int quantity)
    {
        Quantity=quantity;
    }
    string get_item()
    {
        return Item;
    }
    int get_rate()
    {
        return Rate;
    }
    int get_quantity()
    {
        return Quantity;
    }
};

int add_item(Bill b)
{
    int choice;
    bool close=false;
    while(!close)
    {
        cout<<1<<" Add"<<endl;
        cout<<2<<" Close"<<endl;
        cout<<"enter choice:";
        cin>>choice;

        if(choice==1)
        {
            system("cls");
            string item;
            int rate,quantity;
            cout<<"enter item name:";
            cin>>item;
            b.set_item(item);

            cout<<"enter rate of item:";
            cin>>rate;
            b.set_rate(rate);

            cout<<"enter quantity:";
            cin>>quantity;
            b.set_quantity(quantity);

            ofstream out("D:/bill.txt",ios::app);
            if(!out)
            {
                cout<<"error in opening the file"<<endl;
            }
            else
            {
                out<<b.get_item()<<":"<<b.get_rate()<<":"<<b.get_quantity()<<endl<<endl;
            }
            out.close();
            cout<<"Item added successfully!"<<endl;
            Sleep(3000);
        }
        else
        {
            system("cls");
            choice=true;
            cout<<"Back to main menu";
            Sleep(3000);
            break;
        }
    }
}

void print_bill()
{
    system("cls");
    int choice,count=0;
    bool close=true;
    while(close)
    {
        cout<<1<<" Add Bill"<<endl;
        cout<<2<<" Close session"<<endl;
        cout<<"enter choice:";
        cin>>choice;

        if(choice==1)
        {
            string item;
            int quantity;
            cout<<"enter item:";
            cin>>item;
            cout<<"enter quantity:";
            cin>>quantity;

            ifstream in("D:/bill.txt");
            ofstream out("D:/temp.txt");

            string line;
            bool found=false;
            while(getline(in,line)) //reading from 'in' file and writing in 'line' variable
            {
                stringstream ss;
                ss<<line;

                string item_name;
                int item_rate,item_quantity;
                char delimeter;
                ss>>item_name>>delimeter>>item_rate>>delimeter>>item_quantity;

                if(item==item_name)
                {
                    found=true;
                    if(quantity==item_quantity)
                    {
                        int amount=quantity*item_rate;
                        cout<<"Item | Rate | Quantity | Amount"<<endl;
                        cout<<item_name<<"|"<<item_rate<<"|"<<item_quantity<<"|"<<amount<<endl;
                        int new_qty=item_quantity-quantity;
                        item_quantity=new_qty;
                        count=count+amount;

                        out<<item_name<<":"<<item_rate<<":"<<item_quantity<<endl<<endl;
                    }
                    else
                    {
                        cout<<"sorry "<<item<<" ended!"<<endl;
                    }
                }
                else 
                {
                    out<<line;
                }
                if(!found)
                {
                    cout<<"Item not found"<<endl;
                }
                out.close();
                in.close();
                remove("D:/bill.txt");
                rename("D:/temp.txt","D:/bill.txt");
            }
        }
        else if(choice==2)
        {
            close=false;
            cout<<"Counting total bill"<<endl;
        }
        Sleep(3000);
    }
    system("cls");
    cout<<endl<<endl;
    cout<<"Total bill---------------------"<<count<<endl<<endl;
    cout<<"THANKS FOR THE SHOPPING"<<endl;
    Sleep(5000);
}

int main()
{
    Bill b;
    bool exit=true;
    while(exit)
    {
        system("cls"); // clearing the screen
        int val;
        cout<<"WELCOME TO SUPER MARKET BILLING SYSTEM"<<endl;
        cout<<"**************************************"<<endl;
        cout<<1<<" Add items"<<endl;
        cout<<2<<" Print bill"<<endl;
        cout<<3<<" Exit"<<endl;
        cout<<4<<" Make Choice(1-3):";
        cin>>val;

        if(val==1)
        {
            system("cls");
            add_item(b);
            Sleep(3000);
        }
        else if(val==2)
        {
            print_bill();
        }
        else if(val==3)
        {
            exit=false;
            cout<<endl<<endl;
            cout<<"WISHING YOU GOOD LUCK!!!";
        }
    }

}
