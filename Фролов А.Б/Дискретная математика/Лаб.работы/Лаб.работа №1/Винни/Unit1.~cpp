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
void __fastcall TForm1::Button1Click(TObject *Sender)
{
long x1=0,x2=0,x3=0;
unsigned l1,l2;
l1=(32>Edit1->Text.Length()?Edit1->Text.Length():32);
l2=(32>Edit2->Text.Length()?Edit2->Text.Length():32);
l1=l1<l2?l1:l2;
x1 = readstring(Edit1->Text.c_str());
x2 = readstring(Edit2->Text.c_str());
x3 = normalize(x1,x2,l1);
Label1->Caption="";
if(inc(x1,x2)) Label1->Caption="Грань 2 поглощена гранью 1";
if(inc(x2,x1)) Label1->Caption="Грань 1 поглощена гранью 2";
Edit3->Text=getstring(x3,l1);
}

//---------------------------------------------------------------------------
std::list<long> lst;
unsigned l1;
void __fastcall TForm1::Button2Click(TObject *Sender)
{
        lst.push_back(readstring(Edit4->Text.c_str()));
        Memo1->Lines->Add(Edit4->Text);
        l1 = Edit4->Text.Length();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
        lst.push_back(readstring("10xx01001xxxx101"));
	lst.push_back(readstring("0x11x1xx1x00xx01"));
	lst.push_back(readstring("xxxxxxxxxxxxx01x"));
        Memo1->Lines->Add("10xx01001xxxx101");
        Memo1->Lines->Add("0x11x1xx1x00xx01");
        Memo1->Lines->Add("xxxxxxxxxxxxx01x");
        l1=16;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
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
        Memo1->Clear();
	for(std::list<long>::iterator i = lst.begin(); i!=lst.end() ; ++i)
	{
		long curr = *i;
                Memo1->Lines->Add(getstring(curr,l1));
	}
}
//---------------------------------------------------------------------------

