//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <iostream>
#include <list>
#include <algorithm>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
long readstring(char* s)
{
    long x1=0;
    for(int i=0; s[i]!=0 && i< 16;i++)
    {
        x1=x1<<2;
        if(s[i]=='1') x1=x1|1;// else x1=x1&&0xfffffe;
        if(s[i]=='0') x1=x1|2;// else x1=x1&&0xfffffe;
        if(s[i]=='x') x1=x1|3;// else x1=x1&&0xfffffe;

    }
    return x1;
}
long normalize(long x1, long x2,int l1)
{
     x1=x1&x2;
     int nc=0;
     long mask=3;
     for(int i=0; i<l1;i++)
     {
        if((x1&mask)==0)
        {
                x1=x1|mask;
                nc++;
        }
        mask=mask<<2;
     }
     if(nc==1)
     return x1;
}
char* getstring(long x3,unsigned l1)
{
        char* ch = new char[32];
        for(int i=0; i<=31;i++) ch[i]=' ';
        for(int i=1; i<=l1;i++)
        {
                long mask=3;
                if((x3&mask)==1) ch[l1-i]='1';
                if((x3&mask)==2) ch[l1-i]='0';
                if((x3&mask)==3) ch[l1-i]='x';
                x3=x3>>2;
        }
        return ch;
}
bool inc(long x1, long x2)
{
        return ((x1 & x2) == (x2));
}

unsigned l1;
std::list<long> lst1;
std::list<long> lst2;

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        lst1.push_back(readstring(Edit4->Text.c_str()));
        Memo1->Lines->Add(Edit4->Text);
        l1 = Edit4->Text.Length();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
        lst1.push_back(readstring("10xx01001xxxx101"));
	lst1.push_back(readstring("0x11x1xx1x00xx01"));
	lst1.push_back(readstring("xxxxxxxxxxxxx01x"));
        Memo1->Lines->Add("10xx01001xxxx101");
        Memo1->Lines->Add("0x11x1xx1x00xx01");
        Memo1->Lines->Add("xxxxxxxxxxxxx01x");
        l1=16;
}
//---------------------------------------------------------------------------

void sokr(std::list<long> &lst)
{
        bool newIteration = true;
	while(newIteration)
	{
		newIteration = false;
		for(std::list<long>::iterator i = lst.begin(); i!=lst.end() && !newIteration;)
		{
			long curr = *i;
			bool weryty = false;
			for(std::list<long>::iterator j = lst.begin(); j!=lst.end(); ++j)
			{
				long nxt = *j;
				if(inc(nxt,curr) && i != j)
				{
					//std::list<long>::iterator k = i;
					//++k;
					//i.remove();
					i = lst.erase(i);
					weryty = true;
					break;
				}
			}
			if(weryty) continue;

			for(std::list<long>::iterator j = lst.begin(); j!=lst.end();)
			{
				long nxt = *j;
				if(inc(curr,nxt) && i != j)
				{
					//std::list<long>::iterator k = j;
					//++k;
					//j.remove();
					j = lst.erase(j);
				}
				else ++j;
			}

			std::list<long>::iterator j = i;
			++j;
			for(; j!=lst.end(); ++j)
			{
				long nxt = *j;
				try
				{
					long abc = normalize(curr , nxt, l1);

					bool absorpted = false;
					for(std::list<long>::iterator q = lst.begin(); q!=lst.end(); ++q)
					{
						long dd = *q;
						if(inc(dd,abc))
						{
							absorpted = true;
							break;
						}
					}
					if(!absorpted)
					{
						lst.push_front(abc);
						newIteration = true;
						break;
					}

				} catch(...){}
			}
			++i;
		}
	}
        //print

}
bool peresek(long x1, long x2)
{
        long mask=3;
        for(int i=0; i<16; i++)
        {
                if ((x1&mask)==1&&(x2&mask)==2||(x1&mask)==2&&(x2&mask)==1)
                return false;
                x1=x1>>2;
                x2=x2>>2;
        }
        return true;
}
bool srav(std::list<long> lst, std::list<long> lst2)
{
        bool newIteration = true;
	while(newIteration)
	{
		newIteration = false;
		for(std::list<long>::iterator i = lst.begin(); i!=lst.end() && !newIteration;)
		{
			long curr = *i;
			bool weryty = false;
			for(std::list<long>::iterator j = lst.begin(); j!=lst.end(); ++j)
			{
				long nxt = *j;
				if(inc(nxt,curr) && i != j)
				{
					//std::list<long>::iterator k = i;
					//++k;
					//i.remove();
					i = lst.erase(i);
					weryty = true;
					break;
				}
			}
			if(weryty) continue;

			for(std::list<long>::iterator j = lst.begin(); j!=lst.end();)
			{
				long nxt = *j;
				if(inc(curr,nxt) && i != j)
				{
					//std::list<long>::iterator k = j;
					//++k;
					//j.remove();
					j = lst.erase(j);
				}
				else ++j;
			}

                        for(std::list<long>::iterator j = lst2.begin(); j!=lst2.end();)
			{
				long nxt = *j;
				if(inc(curr,nxt) && i != j)
				{
					//std::list<long>::iterator k = j;
					//++k;
					//j.remove();
					j = lst2.erase(j);
				}
				else ++j;
			}

			std::list<long>::iterator j = i;
			++j;
			for(; j!=lst.end(); ++j)
			{
				long nxt = *j;
				try
				{
					long abc = normalize(curr , nxt, l1);

					bool absorpted = false;
					for(std::list<long>::iterator q = lst.begin(); q!=lst.end(); ++q)
					{
						long dd = *q;
						if(inc(dd,abc))
						{
							absorpted = true;
							break;
						}
					}
					if(!absorpted)
					{
						lst.push_front(abc);
						newIteration = true;
						break;
					}

				} catch(...){}
			}
			++i;
		}
	}
        return (lst2.empty());
}
void __fastcall TForm1::Button3Click(TObject *Sender)
{



        sokr(lst1);
        for(std::list<long>::iterator i = lst1.begin(); i!=lst1.end() ; )
        {
                long curr = *i;
                bool e=false;
                for(std::list<long>::iterator j = lst2.begin(); j!=lst2.end() ; ++j)
                {
                        long t = *j;
                        if(peresek(curr,t)) e=true;
                }
                if(!e)
                {
                        i=lst1.erase(i);
                } else ++i;
        }

        if(srav(lst1,lst2)) MessageBoxA(Form1->Handle,"2","Результат",MB_OK);
        else
        if(srav(lst2,lst1)) MessageBoxA(Form1->Handle,"1","Результат",MB_OK);
        else  MessageBoxA(Form1->Handle,"0","Результат",MB_OK);


        Memo1->Clear();
	for(std::list<long>::iterator i = lst1.begin(); i!=lst1.end() ; ++i)
	{
		long curr = *i;
                Memo1->Lines->Add(getstring(curr,l1));
	}
        Memo2->Clear();
	for(std::list<long>::iterator i = lst2.begin(); i!=lst2.end() ; ++i)
	{
		long curr = *i;
                Memo2->Lines->Add(getstring(curr,l1));
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
        lst2.push_back(readstring(Edit4->Text.c_str()));
        Memo2->Lines->Add(Edit4->Text);
        l1 = Edit4->Text.Length();
}
//---------------------------------------------------------------------------

