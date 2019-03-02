/*
||   |||||    |    ||||  ||| ||     |||||     ||     ||
||   |--     |||   |__|  || |||     ||      |||||| ||||||
|||| |||||  || ||  ||  | ||  ||     |||||     ||     ||

DEVELOPED BY:
BHARAT SHARMA
XII-D

*/
#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<iomanip.h>

////function to display a design of borders/////////
void design()
{
randomize();                 //(x,y)  (9,4)->(72,4)
			     //       (9,20)->(72,20)
char ch=1+random(256);
for(int h=0;h<25;++h)
{if(h<4||h>20)
{for(int i=0;i<80;++i)cout<<ch;}
else{gotoxy(1,5+h-4);for(int i=0;i<8;++i)cout<<ch;
gotoxy(73,5+h-4);for(i=0;i<8;++i)cout<<ch;}}
}

void adduser();
float uno;

////function to check input values of variable/////////
void check(int &a,int b,int c=0,int d=1,int e=1)       //checking input values
{        //var   max   min       x         y+1
int f=1;
for(int i=0;i<f;++i)
{
if(a>=c&&a<=b)
return;
else
{--i;
gotoxy(d,e+1);
clreol();
gotoxy(d,e);
cout<<"invalid Input enter again";
clreol();
gotoxy(d,e+1);
cin>>a;
}
}
}

////function to export user number to file/////////
void setuno()                       //set user number
{
ofstream fout("uno.txt");
fout<<uno;
fout.close();
}

////function to import user number from file/////////
void getuno()                       //get user number
{
char ch[5];
ifstream fin("uno.txt");
fin>>ch;
if(ch[0]=='\0')
{uno=0;setuno();}
else
uno=atoi(ch);
fin.close();
}


////USER  CLASS/////////
class user
{
char name[30];
int pin;
int c,score,g[3];
public:
void in();
void out()
{
cout<<name<<"--"<<pin<<"--"<<c<<"--"<<score<<endl;
}
void out2()
{
cout<<name<<"--"<<score<<endl;
}
int getp()
{return pin;}
char* getname()
{return name;}
int retscore()
{return score;}
void addscore(int a)
{score+=a;}
int retg(int x)
{return g[x];}
void addg(int x,int y) // game-1 ,add
{g[x]+=y;}
void setg(int x) // game-1
{g[x]=0;}
int retc()
{return c;}   //class
}h;

void revise(int c);

typedef char string[20][30];       //for game 3

struct Q                          //structure for game 1
{
char question[15];
int answer;
};

struct F                          //structure for game 2
{
char fname[30];
char desc[60];
};

////function to update details of user/////////
void fileupdate()
{
user u;
ifstream f1("userdata.bin",ios::binary);
ofstream f2("ss.bin",ios::binary);
while(f1.read((char*)&u,sizeof(u)))
{
if(strcmpi(u.getname(),h.getname())==0)
f2.write((char*)&h,sizeof(h));
else
f2.write((char*)&u,sizeof(u));
}
f1.close();
f2.close();
ofstream f3("userdata.bin",ios::binary);
ifstream f4("ss.bin",ios::binary);
while(f4.read((char*)&u,sizeof(u)))
{
f3.write((char*)&u,sizeof(u));
}
f3.close();
remove("ss.bin");
}

////FUNCTION TO ENTER DETAILS OF NEW USER/////////
void user::in()                             //input user details
{
clrscr();
char x[5], y[5];
a:
design();
user u;
gotoxy(30,4);
cout<<"NEW   USER   MENU";
gotoxy(15,5);
cout<<"Enter";
gotoxy(15,6);
cout<<"User name";
gotoxy(15,7);
cin>>name;
ifstream fin("userdata.bin",ios::binary);
while(fin.read((char*)&u,sizeof(u)))
{
if(strcmpi(u.getname(),name)==0)
{
clrscr();
gotoxy(15,7);
cout<<"User Name already exists, Enter different User Name";
delay(2000);
clrscr();
goto a;
}
}
fin.close();
m:
gotoxy(15,8);
cout<<"4 Digit(Only) New Password";
gotoxy(15,9);
delline();
insline();
for(int i=0;i<4;++i)
{
gotoxy(15+i,9);
x[i]=getch();
cout<<"*";
}
x[i]='\0';
gotoxy(15,10);
cout<<"Confirm Password";
gotoxy(15,11);
delline();
insline();
for(i=0;i<4;++i)
{
gotoxy(15+i,11);
y[i]=getch();
cout<<"*";
}
y[i]='\0';
int f=atoi(x);
if(strcmpi(x,y)==0&&f!=0)
{
pin=f;
gotoxy(15,12);
cout<<"Class(11/12)";
gotoxy(15,13);
cin>>c;
check(c,12,11,15,14);
score=g[0]=g[1]=g[2]=0;
adduser();
++uno;
setuno();
}
else
{
gotoxy(15,12);
cout<<"Wrong Input Enter again";
delay(1000);
gotoxy(15,11);
delline();delline();
goto m;}
}

////FUNCTION TO ENTER DATA IN GAME 1 FILES/////////
void egame1()
{
clrscr();
char ch[15];
ofstream fout;
int n;
cout<<"Enter class (11/12)"<<endl;
cin>>n;
if(n==11||n==12)
{
switch(n)
{
case 11:{fout.open("game111.bin",ios::app|ios::binary);break;}
case 12:{fout.open("game112.bin",ios::app|ios::binary);break;}
}
Q q;
cout<<"Enter number of header files"<<endl;
cin>>n;
fout.write((char*)&n,sizeof(n));
cout<<"Enter header files"<<endl;
for(int i=0;i<n;++i)
{
gets(ch);
fout.write((char*)&ch,sizeof(ch));
}
cout<<"Enter number of functions"<<endl;
cin>>n;
cout<<"enter"<<endl;
for(i=0;i<n;++i)
{cout<<"function  : ";
gets(q.question);
cout<<"answer(digit)  : ";
cin>>(q.answer);
fout.write((char*)&q,sizeof(q));
}
fout.close();
cout<<"DATA  SAVED";delay(1400);
}
else
cout<<"INVALID INPUT";delay(1400);
}


////FUNCTION TO ENTER DATA IN GAME 2 FILES/////////
void egame2()
{
clrscr();
F f;
int n;
cout<<"Enter class(11/12);"<<endl;
cin>>n;
ofstream fout;
if(n==11||n==12)
{
switch(n)
{
case 11:{fout.open("game211.bin",ios::binary|ios::app);break;}
case 12:{fout.open("game212.bin",ios::binary|ios::app);break;}
};
cout<<"Enter number of functions"<<endl;
cin>>n;
cout<<"Enter"<<endl;
for(int i=0;i<n;++i)
{ cout<<"Function  : ";
gets(f.fname);
cout<<"Description(60) : ";
gets(f.desc);
fout.write((char*)&f,sizeof(f));
}
fout.close();
cout<<"DATA  SAVED";delay(1400);
}
else
cout<<"INVALID INPUT";delay(1400);
}


////FUNCTION TO ENTER DATA IN GAME 3 FILES/////////
void egame3()
{
clrscr();
string strc,strw;
int n,x;
cout<<"Enter class(11/12)"<<endl;
cin>>n;
if(n==11||n==12)
{
ofstream fout;
switch(n)
{
case 11:{fout.open("game311.bin",ios::binary|ios::app);break;}
case 12:{fout.open("game312.bin",ios::binary|ios::app);break;}
};
cout<<"enter number of codes"<<endl;
cin>>n;
cout<<"Enter"<<endl;
for(int i=0;i<n;++i)
{cout<<"Number of lines in code "<<i+1<<" : ";
cin>>x;
fout.write((char*)&x,sizeof(x));
cout<<"Correct Code"<<endl;
for(int j=0;j<x;++j)
{cout<<"Line "<<j+1<<" : ";
gets(strc[j]);
}
cout<<"Wrong code"<<endl;
for(j=0;j<x;++j)
{cout<<"Line "<<j+1<<" : ";
gets(strw[j]);
}
fout.write((char*)&strw,sizeof(strw));
fout.write((char*)&strc,sizeof(strc));
}
fout.close();
cout<<"DATA  SAVED";delay(1400);
}
else
cout<<"INVALID INPUT";delay(1400);
}


////FUNCTION TO DISPLAY DATA OF GAME FILES/////////
void outdata(int x)
{
switch(x)
{
case 1:
case 2:{ifstream fin;ofstream fout;if(x==1){fout.open("g111.txt");fin.open("game111.bin",ios::binary);}else {fout.open("g112.txt");fin.open("game112.bin",ios::binary);}
	int n;char ch[15];Q q;
	fin.read((char*)&n,sizeof(n));
	for(int i=0;i<n;++i)
	{fin.read((char*)&ch,sizeof(ch));
	 fout<<i+1<<" "<<ch<<endl;}
	 while(fin.read((char*)&q,sizeof(q)))
	 {fout<<q.question<<endl<<q.answer<<endl;}
	 fin.close();
	 fout.close();
	 break;
	 }
case 3:
case 4:{ifstream fin;ofstream fout;if(x==3){fout.open("g211.txt");fin.open("game211.bin",ios::binary);}else {fout.open("g212.txt");fin.open("game212.bin",ios::binary);}
	F f;
	 while(fin.read((char*)&f,sizeof(f)))
	 {fout<<f.fname<<endl<<f.desc<<endl;}
	 fin.close();
	 fout.close();
	 break;
	 }
case 5:
case 6:{ifstream fin;ofstream fout;if(x==5){fout.open("g311.txt");fin.open("game311.bin",ios::binary);}else {fout.open("g312.txt");fin.open("game312.bin",ios::binary);}
	int n;string strc,strw;
	 while(fin.read((char*)&n,sizeof(n)))
	 {fin.read((char*)&strc,sizeof(strc));
	fin.read((char*)&strw,sizeof(strw));
	fout<<endl<<"WRONG CODE"<<endl;
	 for(int i=0;i<n;++i)
	 fout<<strc[i]<<endl;
	 fout<<endl<<"CORRECT CODE"<<endl;
	 for(i=0;i<n;++i)
	 fout<<strw[i]<<endl;
	 }
	 fin.close();
	 fout.close();
	 break;
	 }
}
revise(x);
}


////FUNCTION FOR MASTER CONTROL/////////
void manage()
{
d:
clrscr();
gotoxy(30,1);
cout<<"Learn  Plus Plus "<<endl;
gotoxy(34,2);
cout<<"Manager"<<endl;
int n;
cout<<"1. Data"<<endl;
cout<<"2. enter question"<<endl;
cout<<"3. See Data in files"<<endl;
cout<<"0 to exit"<<endl;
cin>>n;
check(n,3,0,1,6);
switch(n)
{
case 0:goto a;
case 1:goto b;
case 2:goto c;
case 3:goto w;
}
b:
{clrscr();
user u;
int i=1;
ifstream fin("userdata.bin",ios::binary);
cout<<"USER Name--password--class--score"<<endl;
while(fin.read((char*)&u,sizeof(u)))
{
cout<<i<<" ";++i;
u.out();
}
fin.close();
cin>>n;
if(n!=0)
{
int i=1;
ifstream f1("userdata.bin",ios::binary);
ofstream f2("ss.bin",ios::binary);
while(f1.read((char*)&u,sizeof(u)))
{
if(i!=n)
f2.write((char*)&u,sizeof(u));
++i;
}
f1.close();
f2.close();
ofstream f3("userdata.bin",ios::binary);
ifstream f4("ss.bin",ios::binary);
while(f4.read((char*)&u,sizeof(u)))
{
f3.write((char*)&u,sizeof(u));
}
f3.close();
remove("ss.bin");
--uno;
setuno();
goto b;
}
goto d;
}
c:
{
clrscr();
cout<<"1.game 1"<<endl<<"2.game 2"<<endl<<"3.game 3"<<endl<<"0 to exit"<<endl;;
cin>>n;
switch(n)
{
case 0:goto d;
case 1:{egame1();break;}
case 2:{egame2();break;}
case 3:{egame3();break;}
};
goto c;
}
w:
{
clrscr();
cout<<"1.game 1(11)"<<endl<<"2.game 1(12)"<<endl<<"3.game 2(11)"<<endl<<"4.game 2(12)"<<endl<<"5.game 3(11)"<<endl<<"6.game 3(12)"<<endl<<"0 to exit"<<endl;
cin>>n;
check(n,6,0,1,9);
switch(n)
{
case 0:goto d;
default :{outdata(n);break;}
}
goto w;
}
a:
}


////FUNCTION TO ADD A NEW USER/////////
void adduser()
{                                               //adding user to file
ofstream fout("userdata.bin",ios::app);
fout.write((char*)&h,sizeof(h));
fout.close();
}

////FUNCTION TO DISPLAY HELP FOR GAMES/////////
void help(int x) //game
{
clrscr();
ifstream fin;
char ch[80];
switch(x)
{
case 1:{fin.open("help1.txt");break;}
case 2:{fin.open("help2.txt");break;}
case 3:{fin.open("help3.txt");break;}
}
int i=0;
while(!fin.eof())
{
fin.getline(ch,80);
gotoxy(15,8+i);
cout<<ch;
++i;
}
fin.close();
gotoxy(15,9+i);
cout<<"PRESS  ANY  KEY  TO START  THE GAME";
getch();
}

////HEADER FILE GAME-1/////////
void game1(int t)
{
clrscr();
int n,score=0,c=h.retc();
ifstream fin;
char ch[15];
Q q;
if(t==0)
h.setg(0);
gotoxy(52,2);
cout<<"HEADER FILES";
gotoxy(9,2);
cout<<"FUNCTION";
gotoxy(2,18);
cout<<"Enter The Number In Front Of Header File For The Above Function or 0 to exit";
int y;
switch(c)
{case 11:{fin.open("game111.bin",ios::binary);break;}
case 12:{fin.open("game112.bin",ios::binary);break;}
};
fin.read((char*)&n,sizeof(n));
gotoxy(48,4);
for(int j=0;j<n;++j)
{gotoxy(48,4+j);
fin.read((char*)&ch,sizeof(ch));         //header files
cout<<j+1<<" "<<ch;
}
fin.seekg(t*sizeof(q),ios::cur);
while(fin.read((char*)&q,sizeof(q)))
{
gotoxy(26,1);
cout<<"SCORE "<<score;
gotoxy(6,4);
cout<<"*  ";
for(j=0;j<strlen(q.question);++j)
{cout<<q.question[j];delay(400);}
cout<<"          ";
gotoxy(9,20);
cin>>y;
if(y==0)
goto a;
else
{
if(y==q.answer)
{
gotoxy(9,22);
cout<<"CORRECT  ANSWER"; ++score;
delay(1100);
}
else
{
gotoxy(9,22);
cout<<"WRONG ANSWER";
gotoxy(9,23);
cout<<"CORRECT  ANSWER IS : "<<q.answer;
delay(2200);
}
h.addg(0,1);
for(int k=0;k<5;++k)
{gotoxy(9,20);delline();}
}
}
h.setg(0);
a:
fin.close();
clrscr();
gotoxy(15,15);
cout<<"YOUR  FINAL  SCORE IS "<<score;
gotoxy(15,16);
cout<<"Press Any Key To Exit";
h.addscore(score);
fileupdate();
getch();
}

////GUESS THE FUNCTION GAME-2/////////
void game2(int t)                        //guess function game
{
clrscr();
if(t==0)
h.setg(1);
int n,score=0,st=h.retc();
ifstream fin;
char star[30];
char c;
F f;
switch(st)
{case 11:{fin.open("game211.bin",ios::binary);break;}
case 12:{fin.open("game212.bin",ios::binary);break;}
};
fin.seekg(t*sizeof(f),ios::beg);
while(fin.read((char*)&f,sizeof(f)))
{
clrscr();
int chance=5;
gotoxy(28,1);
cout<<"GUESS  THE  FUNCTION";
for(int i=0;i<strlen(f.fname);++i)
star[i]='*';
star[i]='\0';
gotoxy(1,4);
cout<<"HINT: "<<f.desc;
delay(1000);
while(strcmpi(f.fname,star)!=0&&chance!=0)
{
gotoxy(1,8);
for(int k=0;k<6;++k)
delline();
gotoxy(60,3);
cout<<"CHANCES__LEFT_: "<<chance;
gotoxy(60,4);
cout<<"SCORE : "<<score;
gotoxy(35,8);
cout<<star<<endl;
gotoxy(1,10);
cout<<"Enter a letter to guess the name of the function or 0 to exit"<<endl;
gotoxy(2,12);
c=getche();
if(c=='0')
goto a;
int v=0;
for(i=0;i<strlen(f.fname);++i)
{
if(c==f.fname[i])
{star[i]=c;++v;}
}
delay(400);
if(v==0)
{--chance;cout<<endl<<"wrong guess, try again";delay(1500);
}
}
clrscr();
if(strcmpi(f.fname,star)==0)
{gotoxy(15,9);
cout<<f.fname;
gotoxy(15,11);
cout<<"Correct answer";
++score;}
else
{gotoxy(15,9);
cout<<"Wrong Answer";      }
h.addg(1,1);
delay(1500);
}
h.setg(1);
a:
fin.close();
clrscr();
gotoxy(15,15);
cout<<"YOUR  FINAL  SCORE IS "<<score;
gotoxy(15,16);
cout<<"Press Any Key To Exit";
h.addscore(score);
fileupdate();
getch();
}

////DECODER GAME-3/////////
void game3(int t)
{
clrscr();
if(t==0)
h.setg(2);
int n,score=0,c=h.retc();
string strc,strw,str1;
ifstream fin;
switch(c)
{case 11:{fin.open("game311.bin",ios::binary);break;}
case 12:{fin.open("game312.bin",ios::binary);break;}
};
fin.seekg(t*(sizeof(n)+2*sizeof(strc)),ios::beg);
while(fin.read((char*)&n,sizeof(n)))
{
int chance=5;
clrscr();
fin.read((char*)&strw,sizeof(strw));
fin.read((char*)&strc,sizeof(strc));
for(int i=0;i<n;++i)
strcpy(str1[i],strw[i]);
l:
gotoxy(10,1);
cout<<"ORIGINAL CODE"<<endl;
for(i=0;i<n;++i)
{
cout<<i+1<<". "<<strw[i]<<endl;
}
gotoxy(55,1);
cout<<"MODIFIED CODE"<<endl;
for(i=0;i<n;++i)
{
gotoxy(42,2+i);
cout<<i+1<<". "<<str1[i]<<endl;
}
gotoxy(55,25);
cout<<"CHANCES LEFT : "<<chance;
char c[2];
gotoxy(5,21);
cout<<"Enter number in front of line to edit line or"<<endl;
gotoxy(5,22);
cout<<"Enter s to submit MODIFIED CODE or 0 to exit"<<endl;
gotoxy(5,23);
cout<<"LINE :";
gotoxy(13,23);
c[0]=getche();
getch();
c[1]='\0';
if(c[0]=='0')
goto b;
if(c[0]!='s')
{
int y=atoi(c);
char ch[30];
gotoxy(5,24);
cout<<"CODE :";
gotoxy(12,24);
gets(ch);
strcpy(str1[y-1],ch);
clrscr();
goto l;
}
else
{
int w=0;
for(i=0;i<n;++i)
{
if(strcmpi(str1[i],strc[i])!=0)
{
clrscr();
--chance;
if(chance!=0)
{
gotoxy(15,8);
cout<<"WRONG ATTEMPT, CHANCES LEFT : "<<chance;
delay(2000);
clrscr();
goto l;
}
else
++w;
}
}
if(chance==0)
{gotoxy(15,8);
cout<<"YOU LOSE";
h.addg(2,1);
goto a;
}
else
{if(w==0)
{clrscr();
gotoxy(15,6);
cout<<"PERFECT  DECODING";
++score;
delay(2000);
h.addg(2,1);
goto a;  }
}
}
a:
}
h.setg(2);
b:
fin.close();
clrscr();
gotoxy(15,15);
cout<<"YOUR  FINAL  SCORE IS "<<score;
gotoxy(15,16);
cout<<"Press Any Key To Exit";
h.addscore(score);
fileupdate();
getch();
}

////FUNCTION TO CHECK SAVED GAMES/////////
void level(int x)
{
int y=h.retg(x-1);
if(y!=0)
{
clrscr();
design();
gotoxy(15,4);
cout<<"Enter number in Front of your choice";
gotoxy(15,5);
cout<<"1. NEW  GAME";
gotoxy(15,6);
cout<<"2. SAVED  GAME";
gotoxy(15,7);
cout<<"enter 0 for previous menu";
int n;
gotoxy(15,8);
cin>>n;
check(n,2,0,15,9);
if(n==0)goto a;
if(n==1)
{
y=0;}
}
switch(x)
{
case 1:{help(1);game1(y);break;}
case 2:{help(2);game2(y);break;}
case 3:{help(3);game3(y);break;}
}
a:
}

////FUNCTION FOR TEXT READING MODE/////////
void revise(int c=h.retc())
{
clrscr();
char n;
int page=0;
char ch[80];
ifstream fin;
switch(c)
{
case 1:{fin.open("g111.txt");break;}
case 2:{fin.open("g112.txt");break;}
case 3:{fin.open("g211.txt");break;}
case 4:{fin.open("g212.txt");break;}
case 5:{fin.open("g311.txt");break;}
case 6:{fin.open("g312.txt");break;}
case 11:{fin.open("revise11.txt");break;}
case 12:{fin.open("revise12.txt");break;}
}
while(!fin.eof())
{
clrscr();
for(int i=0;i<24;++i)
{fin.getline(ch,80);
cout<<ch<<endl;
}
++page;
cout<<"Enter N(next page) ";
if(page!=1)
cout<<"or P(Previuos page) ";
cout<<"or 0(exit)    ";
n=getche();
switch(n)
{
case '0':goto rt;
case 'P':
case 'p':{if(page!=1){fin.seekg(0,ios::beg);for(int y=0;y<(24*(page-2));++y)fin.getline(ch,80);page-=2;break;}}
}
}
rt:
fin.close();
}

////MENU FOR LOGED IN USER/////////
void menu()
{
d:
clrscr();
design();
gotoxy(30,4);
cout<<"MENU";
gotoxy(15,5);
cout<<"Welcome, "<<h.getname();
gotoxy(40,5);
cout<<"Score : "<<h.retscore();
gotoxy(15,7);
cout<<"Enter number in Front of your choice";
gotoxy(15,8);
cout<<"1. Revise C++";
gotoxy(15,9);
cout<<"2. Play Game";
gotoxy(15,10);
cout<<"enter 0 to logout";
int n;
gotoxy(15,12);
cin>>n;
check(n,2,0,15,13);
switch(n)
{
case 0:{goto a;}
case 1:{revise();goto d;}
case 2:{goto c;}
};
c:
clrscr();
design();
gotoxy(30,4);
cout<<"GAMES";
gotoxy(15,5);
cout<<"Welcome, "<<h.getname();
gotoxy(40,5);
cout<<"Score : "<<h.retscore();
gotoxy(15,7);
cout<<"Enter number in Front of your choice";
gotoxy(15,8);
cout<<"1. Header File Game";
gotoxy(15,9);
cout<<"2. Guess The Function Game";
gotoxy(15,10);
cout<<"3. Decoder";
gotoxy(15,11);
cout<<"enter 0 for previous menu";
gotoxy(15,12);
cin>>n;
check(n,3,0,15,13);
if(n==0)goto d;
level(n);
goto c;
a:
}

////MENU FOR NEW USER/////////
void newuser()
{
clrscr();
design();
h.in();
clrscr();
gotoxy(15,7);
cout<<"USER ADDED";
gotoxy(15,8);
cout<<"Press any key to proceed";
getch();
menu();
}

///MENU FOR EXISTING USER/////////
void existinguser()
{
clrscr();
int a=2,z;
char n[30],p[5];
h:
if(a!=0)
{
design();
gotoxy(30,4);
cout<<"EXISTING  USER  MENU";
gotoxy(15,5);
cout<<"Enter";
gotoxy(15,6);
cout<<"User Name";
gotoxy(15,7);
cin>>n;
gotoxy(15,8);
cout<<"PASSWORD";
gotoxy(15,9);
for(int i=0;i<4;++i)
{
gotoxy(15+i,9);
p[i]=getch();
cout<<"*";
}
p[i]='\0';
z=atoi(p);
int f=2;
user y;
ifstream fin("userdata.bin",ios::binary);
while(fin.read((char*)&y,sizeof(y)))
{
if(strcmpi(n,y.getname())==0)
{--f;
break;
}
}
fin.close();
if(z==y.getp()||z==0)
--f;
if(f!=0)
{clrscr();
--a;
gotoxy(15,9);
cout<<"Invalid User Name Or Password";
delay(1800);
clrscr();
goto h;
}
else
{
clrscr();
gotoxy(15,10);
h=y;
cout<<"LOGIN SUCCESSFUL";
delay(800);
menu();
}
}
else
{
clrscr();
gotoxy(15,10);
cout<<"LOGIN UNSUCCESSFUL";
delay(1000);
}
}

//////CLASS FOR LEADERBOARD//////////
struct stud
{char name[30];
int c,s;
}e[40];
void lb()
{
clrscr();
design();
int i=0;
gotoxy(35,6);
cout<<"LEADERBOARD";
gotoxy(13,8);
cout<<"User name---class---score"<<endl;
ifstream fin("userdata.bin",ios::binary);
while(fin.read((char*)&h,sizeof(h)))
{strcpy(e[i].name,h.getname());
e[i].c=h.retc();
e[i].s=h.retscore();
++i;
}
fin.close();
for(int y=0;y<i-1;++y)
{
int max=e[y].s;
int p=y;
for(int j=y+1;j<i;++j)
{if(e[j].s>e[y].s)
{max=e[j].s;
p=j;
}
}
stud w=e[y];
e[y]=e[p];
e[p]=w;
}
for(y=0;y<i;++y)
{gotoxy(13,9+y);
cout<<e[y].name<<"---"<<e[y].c<<"---"<<e[y].s;
}
gotoxy(13,9+y+1);
cout<<"Press Any Key To Exit";
getch();
}

////FUNCTION FOR ABOUT/////////
void about()
{clrscr();
design();
int i=1;
gotoxy(30,7);
cout<<"LEARN  PLUS  PLUS";
gotoxy(33,8);
cout<<"Version 1.0";
char ch[85];
ifstream fin("about.txt");
while(!fin.eof())
{
gotoxy(12,9+i);
fin.getline(ch,80);
cout<<ch;
++i;
}
fin.close();
gotoxy(13,10+i);
cout<<"Press Any Key To Exit";
getch();
}

////FUNCTION FOR STARTUP ANIMATION/////////
void first()
{
clrscr();
ifstream fin("main.txt");
char ch[80];
for(int i=0;i<5;++i)
{
fin.seekg(0,ios::beg);
for(int j=1;j<=i;++j)
fin.getline(ch,80);
fin.getline(ch,80);
gotoxy(1,1+i);
for(int k=0;k<strlen(ch);++k)
{cout<<ch[k];delay(3);}
delay(400);
fin.seekg(0,ios::beg);
for(j=9;j>i;--j)
fin.getline(ch,80);
fin.getline(ch,80);
gotoxy(1,15-i);
for(k=0;k<strlen(ch);++k)
{cout<<ch[k];delay(3);}
delay(400);
}
delay(400);
clrscr();
delay(600);
fin.seekg(0,ios::beg);
for(i=0;i<10;++i)
{
fin.getline(ch,80);
cout<<ch<<endl;
if(i==4)
cout<<endl<<endl<<endl<<endl<<endl;
}
fin.close();
delay(800);
gotoxy(30,19);
cout<<"DEVELOPED  BY :";
delay(500);
gotoxy(30,21);
cout<<"BHARAT   SHARMA";
gotoxy(30,22);
cout<<"XII-D";
for(i=0;i<30;++i)
{
gotoxy(1,24);
clreol();
gotoxy(40+i,24);
cout<<"loading...";
delay(160);
}
}

////THE GOVERNING FUNCTION(MAIN MENU)/////////
void main()
{
first();
getuno();
m:
clrscr();
design();
gotoxy(30,4);
cout<<"MAIN   MENU";
gotoxy(15,5);
cout<<"Enter number in Front of your choice";
gotoxy(15,7);
cout<<"1. New User";
gotoxy(15,8);
cout<<"2. Existing User";
gotoxy(15,9);
cout<<"3. Leaderboard";
gotoxy(15,10);
cout<<"4. About Learn Plus Plus";
gotoxy(15,11);
cout<<"enter 0 to exit";
int n;
gotoxy(15,13);
cin>>n;
if(n!=33)
check(n,4,0,15,14);
switch(n)
{
case 0:{clrscr();gotoxy(30,10);cout<<"BYE";delay(700);exit(0);}
case 1:{newuser();break;}
case 2:{existinguser();break;}
case 3:{lb();break;}
case 4:{about();break;}
case 33:{manage();break;}
}
goto m;
}

/*
||||  |||   ||  ||||
||    || |  ||  ||  ||
|||   ||  | ||  ||   ||
||    ||   |||  ||  ||
||||  ||    ||  ||||
OF CODE
    */
