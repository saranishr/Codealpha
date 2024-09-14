#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int main()
{
    int m;
    cout<<"Welcome to Number Guessing Game!!!\nYou will have limited choices!";
    cout<<"\nEnter the difficulty level(1/2/0):";
    cin>>m;
    if(m>=0)
    {
        srand(time(0));
        int secret=1+(rand()%100);
        int choice;
        if(m==1)
        {
            cout<<"\nYou have 3 chances to find the number";
            int left=3;
            for(int i=0;i<3;i++)
            {
                cout<<"\nEnter a number between 1 to 100:"<<endl;
                cin>>choice;
                if(secret==choice)
                {
                    cout<<"You WON!!!";
                    break;
                }
                else
                {
                    cout<<"Nope"<<endl;
                    if(choice>secret)
                    {
                        cout<<"The secret number is smaller"<<endl;
                    }
                    else
                    {
                        cout<<"The secret number is larger"<<endl;
                    }
                    left--;
                    cout<<left<<" choices are left"<<endl;
                    if(left==0)
                    {
                        cout<<"GAME OVER!"<<endl;
                        cout<<"The secret number was "<<secret<<endl;
                    }
                }
            }
        }
        else if(m==2)
        {
            cout<<"\nYou have 2 chances to find the number";
            int left=2;
            for(int i=0;i<2;i++)
            {
                cout<<"\nEnter a number between 1 to 100:"<<endl;
                cin>>choice;
                if(secret==choice)
                {
                    cout<<"You WON!!!";
                    break;
                }
                else
                {
                    cout<<"Nope"<<endl;
                    if(choice>secret)
                    {
                        cout<<"The secret number is smaller"<<endl;
                    }
                    else
                    {
                        cout<<"The secret number is larger"<<endl;
                    }
                    left--;
                    cout<<left<<" choices are left"<<endl;
                    if(left==0)
                    {
                        cout<<"GAME OVER!"<<endl;
                        cout<<"The secret number was "<<secret<<endl;
                    }
                }
            }
            
        }
        else if(m==0)
        {
            exit(0);
        }
    }
    else
    {
        cout<<"Invalid Choice";
    }
}
