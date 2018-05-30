#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
#include<cmath>
#include<cassert>  // for assert()
#include<set>
#include<cstdio>


using namespace std;


struct Item {
	friend ostream& operator<<(ostream&s, Item& record) 
	{ s<<record.by<<"\t"<<record.dy<<endl; return s; } 
	friend Item operator<(Item& record1, Item& record2)
	{
		if(record1.by<record2.by) return record1;
		return record2;
	}
	int by;  // birth year
	int dy;  // death year
};
  
int main(int argc, char**argv)
{

    vector<Item> v;
    Item entry;
    
    vector<int> vi;
    int first_by=INT_MAX, last_dy = 0, by=0, dy=0, i=0;
    int years = 0, max_number_of_alive_people = 0, max_year=0;
    const char *fname = "sg1.dat";	// TEst only!
    if(argc!=2) {
    	cout<<"Improper number of arguments!\nUsage: sg.exe sg.dat"<<endl;
    	exit(1); // test only
    }
    
    ifstream in(argv[1]);
 
    
    //	1. Read data from file here
    while (!in.fail())
    {  
       in >> by;
       in >> dy;
       
       if(by<first_by) {
       		first_by = by;
       }
       	
       if(last_dy<dy) {
       		last_dy = dy;
       }
       
       entry.by = by;
       entry.dy = dy;
       if (!in.fail()) v.push_back(entry);
    }
    in.close();
    years  = last_dy-first_by+1; // for last array element
    
    cout<<"Total records = "<<v.size()<<endl;
    cout<<"First birth year = "<< first_by<<endl;
    cout<<"Last death year = " << last_dy<<endl;
    cout<<"Years of life span analysis = "<<years<<endl;
    
    int* freq = new int[years];
    memset(freq, 0, years*sizeof(int));
    
    for(i=0;i<v.size();i++) {
    	by = v[i].by - first_by;
    	if(by<0) { cout<<"by<0  by="<<by<<endl; }
    //	dy = last_dy-first_by-1;  // last array element
    
    
    	dy = v[i].dy - first_by; 
    	if(dy<0) { cout<<"dy<0 dy="<<dy<<endl; }
    	
    //	cout<<"by = "<<by<<"\tly = "<<dy<<endl;
    
    	/*
    		freq array has counters for people alive at certain year.
    		Element position 0 corresponds to year first_by - first year of birth;
    		Last element will correspond to year last_dy - last  year of death.
    	*/
    	
    	//	Mark alive people
    	for(;by<=dy;by++) { // put <= in for?
    		++freq[by];	
    	}
    	
    	
    }
    
    cout<<"\n\nFinding max year and max freq"<<endl;
 	cout<<"Year\tNumber of Alive People"<<endl;
 	//	Find max frequency here - only first such year will be printed below.
 	for(i=0;i<years;i++) {
 		
 		//	Print only years when someone is alive only!
 		if(freq[i]) {
 			cout<<i+first_by<<"\t"<<freq[i]<<endl; 
		}
 	//	cerr<<i<<"\t"<<freq[i]<<endl;
 	
 		if(max_number_of_alive_people<freq[i]) {
    			max_year = i;
    			max_number_of_alive_people = freq[i];
    	}
    
 	}
 	cout<<"Max number of alive people "<< max_number_of_alive_people<< " were in "<<max_year+first_by<<endl;
 	
 	// Clean up
 	delete []freq;
 	freq=0;
    return 0;
}
