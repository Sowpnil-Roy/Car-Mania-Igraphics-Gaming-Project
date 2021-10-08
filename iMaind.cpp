/*
	CSE 1200: Software Development Lab: Final Project
	Project name: CAR MANIA
	Project members: 190104016, 190104019, 190104020, 190104024
	Last updated: 3 SEP 2020
*/
#include "iGraphics.h"
#include <stdio.h>

#include <fstream>
#include <random>
#include <iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>
#include<stdlib.h>
#include <iostream>
#include<cstring>
using namespace std;

//high score file	
FILE *fp;
//char name[20] = {}, point[10] = {};

//MYCODE

vector <pair<int,string> > v;

string toString(int n) { ostringstream ost; ost << n; ost.flush(); return ost.str();}

int toNumber(string s) {stringstream aa(s);int mm; aa>>mm; return mm;}

string chartoString(char nd[])
{
	string s;
	int dd=strlen(nd);
	for(int i=0;i<dd;i++)
	{
		s.push_back(nd[i]);
	}
	return s;
}

//mycode end



	if(gameState == 4)//highscore page
	{
		iShowImage(0, 0, 800, 600, highscorePage);
	
		iSetColor(255, 255, 255);
		//file
		fp= fopen("Highscore file.txt","r");
		int c;
		while(c=getc(fp)!=EOF)
		{
			char name[20];
			char point[10];
			fscanf(fp, "%s %s", name, point);
			
			string s1=chartoString(name);
			
			string s2=chartoString(point);
			
			int p=toNumber(s2);
			v.push_back(make_pair(p,s1));
			
		}
		fclose(fp);
		sort(v.begin(),v.end());
		reverse(v.begin(),v.end());
		int eee;
		int dddd=v.size();
		if(dddd>=5){eee=5;}
		else eee=dddd;
		cout<<eee<<endl;
		int nameposition=400;
	
		for(int i=0;i<eee;i++)
		{
			
			std::string n=v[i].second;
			std::string p=toString(v[i].first);
			
			char nn[20];
			char pp[20];
			strcpy(nn,n.c_str());
			strcpy(pp,p.c_str());
			
			iText(200, nameposition, nn, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(500, nameposition, pp, GLUT_BITMAP_TIMES_ROMAN_24);
			nameposition-=40;
		}
		v.clear();
	}
	