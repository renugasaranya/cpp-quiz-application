#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

class User{
public:
    string n;
    int password;
    virtual void display(){ cout<<"User Details\n"; }
};

class Quiz: public User{
public:
    int score=0,total=5;

    void login(){
        cout<<"Enter Name: ";
        cin>>n;
        cout<<"Enter Password: ";
        cin>>password;  
        cout<<"Login Successful\n";
    }

    void ask(string q,string a,string b,string c,string d,int correct){
        int ans;
        cout<<"\n"<<q<<endl;
        cout<<"1) "<<a<<"\n2) "<<b<<"\n3) "<<c<<"\n4) "<<d<<endl;
        cout<<"Answer: ";
        cin>>ans;
        if(ans==correct){ score++; cout<<"Correct Answer\n"; }
        else cout<<"Wrong Answer\n";
    }

    void startQuiz(){
        int lang,topic;
        cout<<"languages are:"<<endl;
        cout<<"\n1.C\n2.C++\n3.Java\n";
        cout<<"Select Language: ";
        cin>>lang;

        try{
            if(lang<1||lang>3) throw lang;
        }catch(int){
            cout<<"Invalid Language\n";
            return;
        }

        cout<<"\nTopics\n";
        if(lang==1) cout<<"1.Pointers 2.Loops 3.Functions\n";
        else if(lang==2) cout<<"1.Inheritance 2.Polymorphism 3.FileHandling\n";
        else cout<<"1.Arrays 2.Strings 3.ControlStatements\n";

        cout<<"Select Topic: ";
        cin>>topic;

        try{
            if(topic<1||topic>3) throw topic;
        }catch(int){
            cout<<"Invalid Topic\n";
            return;
        }

        if(lang==1 && topic==1){
            ask("Pointer stores?","Value","Address","Loop","Array",2);
            ask("Address operator?","*","&","%","#",2);
            ask("Dereference operator?","&","%","*","@",3);
            ask("Pointer is?","Variable","Loop","Class","File",1);
            ask("Pointer stores address?","Yes","No","Maybe","None",1);
        }
        else if(lang==1 && topic==2){
            ask("Loop executes repeatedly?","Yes","No","Class","File",1);
            ask("Executes at least once?","for","while","do-while","if",3);
            ask("Exit loop?","continue","break","goto","stop",2);
            ask("Skip iteration?","break","stop","continue","exit",3);
            ask("for is a?","Loop","Array","Class","Function",1);
        }
        else if(lang==1 && topic==3){
            ask("Function is?","Array","Block of code","Loop","Class",2);
            ask("Recursion?","Function calls itself","Loop","Array","Variable",1);
            ask("Print output?","printf","scanf","main","return",1);
            ask("Functions help?","Reuse code","Increase errors","Delete code","Nothing",1);
            ask("Avoid repetition?","True","False","None","Maybe",1);
        }
        else if(lang==2 && topic==1){
            ask("Use of inheritance?","Reuse","Duplicate","Delete","Error",1);
            ask("Inheritance symbol?","#",":","@","$",2);
            ask("Parent class?","Derived","Base","Child","Friend",2);
            ask("Inheritance belongs to?","POP","OOP","OS","DBMS",2);
            ask("Inheritance in C++?","Yes","No","Maybe","None",1);
        }
        else if(lang==2 && topic==2){
            ask("Polymorphism means?","One","Many forms","None","Loop",2);
            ask("Runtime polymorphism?","Virtual Function","Array","File","Loop",1);
            ask("Function overloading?","Compile Time","Runtime","None","OS",1);
            ask("Keyword?","virtual","friend","inline","static",1);
            ask("Overriding gives?","Runtime Poly","Loop","File","Array",1);
        }
        else if(lang==2 && topic==3){
            ask("Header file?","math","fstream","vector","string",2);
            ask("ofstream used for?","Read","Write","Loop","Class",2);
            ask("ifstream used for?","Read","Write","Delete","Loop",1);
            ask("Append mode?","ios::app","ios::in","ios::out","ios::end",1);
            ask("Close file?","close()","end()","stop()","exit()",1);
        }
        else if(lang==3 && topic==1){
            ask("Array is?","Collection","Loop","Class","File",1);
            ask("Index starts?","1","0","-1","2",2);
            ask("Array symbol?","()","[]","{}","<>",2);
            ask("Stored in?","Continuous Memory","Disk","File","Random",1);
            ask("Array size?","Fixed","Dynamic","None","Error",1);
        }
        else if(lang==3 && topic==2){
            ask("Strings are?","Mutable","Immutable","Loop","Array",2);
            ask("Length method?","size()","count()","length()","len()",3);
            ask("Uppercase method?","upper()","toUpperCase()","cap()","up()",2);
            ask("Compare strings?","==","compare","equals()","match",3);
            ask("String stores?","Text","Loop","File","Array",1);
        }
        else if(lang==3 && topic==3){
            ask("Decision statement?","if","for","while","array",1);
            ask("Executes once?","for","while","do-while","if",3);
            ask("Terminate loop?","break","stop","end","exit",1);
            ask("Skip iteration?","break","continue","stop","return",2);
            ask("Choose one case?","if","else","switch","while",3);
        }
    }

    void saveScore(){
        ofstream fout("leaderboard.txt",ios::app);
        if(!fout)
        {
        	cout<<"error opening leaderboard.txt"<<endl;
        	return;
		}
        fout<<n<<" "<<score<<endl;
        fout.close();
    }

    void showLeaderboard(){
        vector<string> names;
        vector<int> scores;
        ifstream fin("leaderboard.txt");
        string n; int s;

        while(fin>>n>>s){
            names.push_back(n);
            scores.push_back(s);
        }
        fin.close();

        for(int i=0;i<scores.size();i++)
            for(int j=i+1;j<scores.size();j++)
                if(scores[j]>scores[i]){
                    swap(scores[i],scores[j]);
                    swap(names[i],names[j]);
                }

        cout<<"\n===== TOP 3 =====\n";
        for(int i=0;i<min(3,(int)scores.size());i++)
            cout<<i+1<<". "<<names[i]<<" "<<scores[i]<<endl;
    }

    void display() override{
        
    int wrong=total-score;
    cout<<"---------------FINAL RESULT---------------"<<endl;
    cout<<"USERNAME:"<<n<<endl;
    cout<<"USERPASSWORD:*******"<<endl;
    cout<<"CORRECT ANSWERS:"<<score<<endl;
    cout<<"WRONG ANSWERS:"<<wrong<<endl;
    cout<<"SCORE IS:"<<score<<endl;
    float percentage = (score * 100.0) / total;
cout<<"PERCENTAGE: "<<percentage<<"%"<<endl;
    ofstream fout("result.txt",ios::app);
    fout<<"PERCENTAGE: "<<percentage<<"%"<<endl;
    if(!fout)
    {
    	cout<<"error opening result.txt"<<endl;
    	return;
	}
    fout<<"USERNAME:"<<n<<endl;
    fout<<"USERPASSWORD:*******"<<endl;
    fout<<"CORRECT ANSWERS:"<<score<<endl;
    fout<<"WRONG ANSWERS:"<<wrong<<endl;
    fout<<"SCORE IS:"<<score<<endl;
    fout<<"------------------------"<<endl;
    fout.close();
    if(score==5)
    cout<<"EXCELLENT"<<endl;
   else  if(score>=3)
    cout<<"GOOD JOB"<<endl;
    else
    cout<<"NEED MORE PRACTICE"<<endl;
    }
    
};

int main(){
	char again;
	do
	{
		int choice;

cout<<"===== QUIZ APPLICATION ====="<<endl;
cout<<"1. Start Quiz"<<endl;
cout<<"2. Exit"<<endl;
cout<<"Enter Choice: ";
cin>>choice;

if(choice==2)
{
    cout<<"Thank You!"<<endl;
    return 0;
}
    Quiz q;
    q.login();
    q.startQuiz();

    User *u=&q;
    u->display();

    char ch;
    cout<<"\nShow Leaderboard(y/n): ";
    cin>>ch;

    if(ch=='y'||ch=='Y')
    {
        q.saveScore();
        q.showLeaderboard();
}
cout<<"Do you want to play again? (y/n):";
cin>>again;
}while(again=='y'||again=='Y');
    return 0;
}
