#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include<math.h>
#include <sstream>
using namespace std;
//set in the linked list
struct Set {
	string setname;
	int *setnumbers;
	int size;
	Set *nextset;
};
//head of the linked list
struct AllSets {
	Set *head;
};
//struct to power set
struct Powerset{
	string sets;
	string sorted;
	string lastsort;
	int size;
};
//now functions that help me in the code that i used them, to string change int to string,count it counts how many ',' have appeared,swap swap 2 elems in the array
//digit 2 works only for postive numbers and didgit work for both
string tostring(int x){
	  stringstream ss;
	  ss<<x;
	  string s;
	  ss>>s;
	  return s;
}
int count(string s) {
	int count = 0;
	for(unsigned int i=1;i<s.size()-1;i++){
		if(s[i]==','){
			count++;
		}
	}
  return(count);
}
void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}
bool digit2(char str) {
		if ((str!='0')&&(str!='1')&&(str!='2')&&(str!='3')&&(str!='4')&&(str!='5')&&(str!='6')&&(str!='7')&&(str!='8')&&(str!='9')) {
			return false;
		}
	return true;
}
bool digit(string str, int n) {
	int counter=0;
	if(str[counter]=='-'){
		counter++;
	}
	for (int i = counter; i < n; i++) {
		if ((str[i]!='0')&&(str[i]!='1')&&(str[i]!='2')&&(str[i]!='3')&&(str[i]!='4')&&(str[i]!='5')&&(str[i]!='6')&&(str[i]!='7')&&(str[i]!='8')&&(str[i]!='9')) {
			return false;
		}
	}
	return true;
}
//function that creat a set and put it on the linked list if it is empty it makes the head new list other it check if set is in the set
//if not it create other node if it exist it override the existed set
//and on the way i have sorted the ints that are used by the user annd makde a set wich have sorted ints4
//else like problems name more than 8 and empty name and else is error by what the question wants
void CreateSet(AllSets *calc, string name) {
	int *inputs;
	int size = 0;
	getline(cin,name);
	getline(cin,name);
	if(name.length()==0){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	if (name.size() > 8) {
		cerr << "ERROR: invalid input" << endl;
		return;
	} else {
		for (unsigned int i = 0; i < name.size(); i++) {
			if (islower((name.c_str())[i]) || !(isalpha(name.c_str()[i]))||isspace(name.c_str()[i])) {
				cerr << "ERROR: invalid input"<<endl;
				return;
			}
		}
		string d2;
		getline(cin, d2);
		if(d2.length()==0){
			cerr << "ERROR: invalid input"<<endl;
			return;
		}
		if ((d2.compare("{}")) == 0) {
			inputs = 0;
		} else {
			d2 = d2.substr(1, d2.size() - 2);
			int spaces = 0;
			for (unsigned int i = 0; i < d2.size(); i++) {
				if (isspace(d2.c_str()[i])) {
					spaces++;
				}
			}
			string *array=new string[spaces + 1];
			int *set=new int[spaces + 1];
			stringstream ssin(d2);
			int i = 0;
			while (ssin.good() && i < spaces + 1) {
				ssin >> array[i];
				if (!digit(array[i], array[i].size())) {
					cerr << "ERROR: invalid input"<<endl;
					return;
				}
				++i;
			}
			i = 0;
			while (i < spaces + 1) {
				set[i] = atoi(array[i].c_str());
				++i;
			}
			delete []array;
			int y = 1;
			int *check2 = new int[spaces + 1];
			check2[0] = set[0];
			int counter = 1;
			bool isin = false;
			for (int i = 0; i < spaces + 1; i++) {
				for (int w = 0; w < y; w++) {
					if (set[i] == check2[w]) {
						isin = true;
					}
				}
				if (isin == false) {
					check2[y] = set[i];
					y++;
					counter++;
				} else {
					isin = false;
					continue;
				}
			}
			inputs = new int[counter];
			for (int i = 0; i < counter; i++) {
				inputs[i] = check2[i];
			}
			delete[] check2;
			delete []set;
			size = counter;
			for (int i = 0; i < size - 1; i++) {
				for (int j = 0; j < size - i - 1; j++) {
					if (inputs[j] > inputs[j + 1]) {
						swap(inputs[j], inputs[j + 1]);
					}
				}
			}
		}

	}
	if (calc->head == NULL) {
		calc->head = new Set;
		calc->head->setname = name;
		calc->head->setnumbers = inputs;
		calc->head->size = size;
		calc->head->nextset = NULL;
		return;
	} else {
		Set *temp = calc->head;
		while (temp) {
			if (temp->setname.compare(name) == 0) {
				temp->setnumbers = inputs;
				temp->size = size;
				return;
			}
			temp = temp->nextset;
		}
		if (temp == NULL) {
			temp = calc->head;
			calc->head = calc->head->nextset;
			Set *p = new Set;
			calc->head = p;
			p->nextset = temp;
			p->setname = name;
			p->setnumbers = inputs;
			p->size = size;
			return;
		}
		return;
	}
}
//delete set same as create but on this we serach for existed list in the list if it is existed we delete it else we make error that it doesnt exist
void DeleteSet(AllSets *calc, string name) {
	getline(cin,name);
	getline(cin,name);
	if(name.length()==0){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	if (name.size() > 8) {
		cerr << "ERROR: invalid input"<<endl ;
		return;
	}
	for (unsigned int i = 0; i < name.size(); i++) {
		if (islower((name.c_str())[i]) || !(isalpha(name.c_str()[i]))||isspace(name.c_str()[i])) {
			cerr << "ERROR: invalid input"<<endl ;
			return;
		}
	}
	Set *temp = calc->head;
	if (temp == NULL) {
		cerr << "ERROR: "<<name<<" does not exist\n";
		return;
	}
	if ((temp->nextset == NULL) && (temp->setname.compare(name) == 0)) {
		delete[] temp->setnumbers;
		calc->head = NULL;
		return;
	}
	if (temp->setname.compare(name) == 0) {
		Set *temp = calc->head->nextset;
		delete[] calc->head->setnumbers;
		calc->head = temp;
		return;
	}
	while (temp) {
		if (temp->nextset) {
			if (temp->nextset->setname.compare(name) == 0) {
				delete[] temp->nextset->setnumbers;
				temp->nextset = temp->nextset->nextset;
				return;
			}
		}
		temp = temp->nextset;
	}
	cerr << "ERROR: "<<name<<" does not exist\n";
}
//here we first call unionset that call create union set
//we take 2 sets we check if they are both exist and if yes
//we make one set by the union of two sets by making array length with elem that in both or one of two the lists
void CreateSetUnion(AllSets *calc, Set *temp1, Set *temp2) {
	string name;
	int *inputs;
	int *current = new int[temp1->size + temp2->size];
	int size = 0;
	getline(cin,name);
	if(name.length()==0){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	if(name.length()>8){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	for (unsigned int i = 0; i < name.size(); i++) {
		if (islower((name.c_str())[i]) || !(isalpha(name.c_str()[i]))|| isspace(name.c_str()[i])) {
			cerr << "ERROR: invalid input"<<endl;
			return;
		}
	}
	if ((temp1->setnumbers == NULL) && (temp2->setnumbers = NULL)) {
		inputs = NULL;
		delete[] current;
	} else if (temp1->setnumbers == NULL) {
		inputs = temp2->setnumbers;
		delete[] current;
	} else if (temp2->setnumbers == NULL) {
		inputs = temp1->setnumbers;
		delete[] current;
	} else {
		int i;
		for (i = 0; i < temp1->size; i++) {
			current[i] = temp1->setnumbers[i];
		}
		for (int y = 0; y < temp2->size; y++) {
			current[y + temp1->size] = temp2->setnumbers[y];
		}
		//here we start to make our union set by comparing and check if true or false if the elem in the other list
		int y = 1;
		int *check2 = new int[temp1->size + temp2->size];
		check2[0] = current[0];
		int counter = 1;
		bool isin = false;
		for (int i = 0; i < temp1->size + temp2->size; i++) {
			for (int w = 0; w < y; w++) {
				if (current[i] == check2[w]) {
					isin = true;
				}
			}
			if (isin == false) {
				check2[y] = current[i];
				y++;
				counter++;
			} else {
				isin = false;
				continue;
			}
		}
		size = counter;
		inputs = new int[counter];
		for (int i = 0; i < counter; i++) {
			inputs[i] = check2[i];
		}
		delete[] current;
		delete[] check2;
		//sroting algorithm to sort the union set
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				if (inputs[j] > inputs[j + 1]) {
					swap(inputs[j], inputs[j + 1]);
				}
			}
		}
	}
	if (calc->head == NULL) {
		calc->head = new Set;
		calc->head->setname = name;
		calc->head->setnumbers = inputs;
		calc->head->size = size;
		calc->head->nextset = NULL;
		return;
	} else {
		Set *temp = calc->head;
		while (temp) {
			if (temp->setname.compare(name) == 0) {
				temp->setnumbers = inputs;
				temp->size = size;
				return;
			}
			temp = temp->nextset;
		}
		if (temp == NULL) {
			temp = calc->head;
			calc->head = calc->head->nextset;
			Set *p = new Set;
			calc->head = p;
			p->nextset = temp;
			p->setname = name;
			p->setnumbers = inputs;
			p->size = size;
			return;
		}
		return;
	}
}
//here our unionset that check if two names in the list or not and check third name if existed it override other it make new set
//and calling for our first unioncreation to make unionset
void UnionSet(AllSets *calc, string first, string second) {
	//cout << "Enter your sets:";
	string a;
	string check;
	int cl=0;
	getline(cin,a);
	getline(cin,a);
	stringstream ssin(a);
	check=a;
	stringstream w(a);
	while(w>>check){
		cl++;
	}
	if(cl>2){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	ssin>>first;
	ssin>>second;
	if(first.length()==0){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	if(second.length()==0){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	if (first.size() > 8 || second.size() > 8) {
		cerr << "ERROR: invalid input" << endl;
		return;
	}
	for (unsigned int i = 0; i < first.size(); i++) {
		if (islower((first.c_str())[i]) || !(isalpha(first.c_str()[i]))||isspace(first.c_str()[i])) {
			cerr << "ERROR: invalid input"<<endl;
			return;
		}
	}
	for (unsigned int i = 0; i < second.size(); i++) {
		if (islower((second.c_str())[i]) || !(isalpha(second.c_str()[i]))||isspace(second.c_str()[i])) {
			cerr << "ERROR: invalid input"<<endl;
			return;
		}
	}
	Set *temp1 = calc->head;
	Set *temp2 = calc->head;
	while (temp2) { //B
		if (temp2->setname.compare(first) == 0) {
			break;
		}
		temp2 = temp2->nextset;
	}
	if (!temp2) {
		cerr << "ERROR: "<<first<<" does not exist\n";
		return;
	}
	while (temp1) { //A
		if (temp1->setname.compare(second) == 0) {
			break;
		}
		temp1 = temp1->nextset;
	}
	if (!temp1) {
		cerr << "ERROR: "<<second<<" does not exist\n";
		return;
	}
	CreateSetUnion(calc, temp1, temp2);

}
//same as createunion but here we dont check the union we check for intersection and both algorithms not the same
//here we check elems that existed on both listsand we sort them
//we call this function after first funtion checking if the two names legal and third is legal and existed or not if yes it override eles it create new one
void CreateSetIntersection(AllSets *calc, Set *temp1, Set *temp2) {
	string name;
	int *inputs;
	int size = 0;
	getline(cin,name);
	if(name.length()==0){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	if(name.length()>8){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	for (unsigned int i = 0; i < name.size(); i++) {
		if (islower((name.c_str())[i]) || !(isalpha(name.c_str()[i]))||isspace(name.c_str()[i])) {
			cerr << "ERROR: invalid input"<<endl;
			return;
		}
	}
	if ((temp1->setnumbers == NULL) && (temp2->setnumbers = NULL)) {
		inputs = NULL;
	} else if (temp1->setnumbers == NULL) {
		inputs = temp2->setnumbers;
	} else if (temp2->setnumbers == NULL) {
		inputs = temp1->setnumbers;
	} else {
		int i;
		int counter = 0;
		for (i = 0; i < temp1->size; i++) {
			for (int w = 0; w < temp2->size; w++) {
				if (temp1->setnumbers[i] == temp2->setnumbers[w]) {
					counter++;
				}
			}
		}
		size = counter;
		inputs = new int[counter];
		int y = 0;
		for (i = 0; i < temp1->size; i++) {
			for (int w = 0; w < temp2->size; w++) {
				if (temp1->setnumbers[i] == temp2->setnumbers[w]) {
					inputs[y] = temp1->setnumbers[i];
					y++;
				}
			}
		}
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				if (inputs[j] > inputs[j + 1]) {
					swap(inputs[j], inputs[j + 1]);
				}
			}
		}
	}
	if (calc->head == NULL) {
		calc->head = new Set;
		calc->head->setname = name;
		calc->head->setnumbers = inputs;
		calc->head->size = size;
		calc->head->nextset = NULL;
		return;
	} else {
		Set *temp = calc->head;
		while (temp) {
			if (temp->setname.compare(name) == 0) {
				temp->setnumbers = inputs;
				temp->size = size;
				return;
			}
			temp = temp->nextset;
		}
		if (temp == NULL) {
			temp = calc->head;
			calc->head = calc->head->nextset;
			Set *p = new Set;
			calc->head = p;
			p->nextset = temp;
			p->setname = name;
			p->setnumbers = inputs;
			p->size = size;
			return;
		}
		return;
	}
}
//our function the check names and call second func
void IntersectionSet(AllSets *calc, string first, string second) {
	string a;
	string check;
	int cl=0;
	getline(cin,a);
	getline(cin,a);
	stringstream ssin(a);
	check=a;
	stringstream w(a);
	while(w>>check){
		cl++;
	}
	if(cl>2){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	ssin>>first;
	ssin>>second;
	if(first.length()==0){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	if(second.length()==0){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	if (first.size() > 8 || second.size() > 8) {
		cerr << "ERROR: invalid input" << endl;
		return;
	}
	for (unsigned int i = 0; i < first.size(); i++) {
		if (islower((first.c_str())[i]) || !(isalpha(first.c_str()[i]))||isspace(first.c_str()[i])) {
			cerr << "ERROR: invalid input"<<endl;
			return;
		}
	}
	for (unsigned int i = 0; i < second.size(); i++) {
		if (islower((second.c_str())[i]) || !(isalpha(second.c_str()[i]))||isspace(second.c_str()[i])) {
			cerr << "ERROR: invalid input"<<endl;
			return;
		}
	}
	Set *temp1 = calc->head;
	Set *temp2 = calc->head;
	while (temp2) { //B
		if (temp2->setname.compare(first) == 0) {
			break;
		}
		temp2 = temp2->nextset;
	}
	if (!temp2) {
		cerr << "ERROR: "<<first<<" does not exist\n";
		return;
	}
	while (temp1) { //A
		if (temp1->setname.compare(second) == 0) {
			break;
		}
		temp1 = temp1->nextset;
	}
	if (!temp1) {
		cerr << "ERROR: "<<second<<" does not exist\n";
		return;
	}
	CreateSetIntersection(calc, temp1, temp2);
}
//printing our list by check if name legal and existed if yes we print the elements in that set
void Print(AllSets *calc, string name) {
	//cout << "Which set you want to print:";
	getline(cin,name);
	getline(cin,name);
	if(name.length()==0){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	if (name.size() > 8) {
		cerr << "ERROR: invalid input" << endl;
		return;
	}
	for (unsigned int i = 0; i < name.size(); i++) {
		if (islower((name.c_str())[i]) || !(isalpha(name.c_str()[i]))||isspace(name.c_str()[i])) {
			cerr << "ERROR: invalid input" << endl;
			return;
		}
	}
	Set *temp = calc->head;
	while (temp) {
		if (temp->setname.compare(name) == 0) {
			cout << name << "={";
			for (int i = 0; i < temp->size; i++) {
				if (i == temp->size - 1) {
					cout << temp->setnumbers[i];
				} else {
					cout << temp->setnumbers[i] << ",";
				}
			}
			cout << "}" << endl;
			return;
		}
		temp = temp->nextset;
	}
	cerr << "ERROR: "<<name<<" does not exist\n";
	return;
}
//subsets algorithm that take point to the array of the set we want to see its subsets and we get powerset linked list to create our powerset
//we get another point at the begining empty list that is 2^length of out arr and size and starting index and start doing subsets
//at the begining we start getting subsets that doesnt include the first element in the array by recursion and after that the recursion comes back
//and start increasing the j to put in the index j in the subset our subset we want and like that
//my i==n is we create strring and makes it looks like a real subset and after that we append it to the string in the power list
void PSET(int *arr, int *subset,int n,int i,int j,Powerset &p){

	if(i==n){
		int idx = 0;
		p.sets+="{";
		while(idx<j){
			int x=subset[idx];
			p.sets+=tostring(x);
			p.sets.append((idx==j-1)?"":",");
			++idx;
		}
		p.sets+=(n==j)?"}":"} ";
		return;
	}
	PSET(arr,subset,n,i+1,j,p);
	subset[j] = arr[i];
	PSET(arr,subset,n,i+1,j+1,p);
}
//here i sort my subsets by smaller to bigger likes p(1,2,3)=(1  ,  2  ,  3  ,  1 2  ,  1 3  ,2 3  ,  1 2 3)
void sortedsublist(string sets,Powerset &set){
	string temp=sets;
	string word;
	stringstream ss(temp);
	int counter=0;
	while(ss>>word){
		counter++;
	}
	stringstream ww(temp);
	string *a=new string[counter];
	int i=0;
	while(ww>>word){
		a[i++]=word;
	}
	int q,r;
	//here we sort every element that looks like{....} by its length of the , so first { } after {,} after {,,}.....
	for (q = 0; q < counter-1; q++)  {
		for (r = 0; r < counter-q-1; r++)  {
			if (count(a[r]) > count(a[r+1])) {
				swap(a[r],a[r+1]);
			}
		}
	}
		int cnt0=0;
		//getting cnt to have how many elemts like {a}
		for(int i=1;i<counter;i++){
			if(count(a[i])==0){
				cnt0++;
			}
		}
		//we sort {a} from small to big
		for(int i=1;i<cnt0+1;i++){
			int temp1=i;
			const char *x3=a[i].substr(1,a[i].size()-1).c_str();
			int min=atoi(x3);
			for(int j=i+1;j<cnt0+1;j++){
				const char *y=a[j].substr(1,a[j].size()-1).c_str();
				int y1=atoi(y);
				if(y1<min){
					min=y1;
					temp1=j;
				}
			}
			swap(a[i],a[temp1]);
		}
		//algorith that see how many , we have we have {} {,} {,,}.... list we first check , cause we know {} is only one
		//we sort like this {a,b,c} {q,w,e} a==q -> b==w c>e? or a>q? or a==q --> b>w?
		string sym=",";
		for(int i=1;i<10;i++){
			for(int w=1;w<counter;w++){
				if(count(a[w])!=i){
					continue;
				}
				else{
				for(int p=w+1;p<counter;p++){
					bool makeitswitch=true;
					int start1=0;
					int start2=0;
					if(count(a[p])==i){
						string a1=a[w].substr(1,a[w].size()-2);
						string a2=a[p].substr(1,a[p].size()-2);
						size_t end1=a1.find(sym);
						size_t end2=a2.find(sym);
						while((end1!=string::npos)&&(end2!=string::npos)){
							const char* a3=a1.substr(start1,end1-start1).c_str();
							const char* a4=a2.substr(start2,end2-start2).c_str();
							int a5=atoi(a3);
							int a6=atoi(a4);
							if(a5==a6){
								start1=end1+sym.length();
								start2=end2+sym.length();
								end1=a1.find(sym,start1);
								end2=a2.find(sym,start2);
								makeitswitch=true;
							}
							else{
								makeitswitch=false;
								if(a5>a6){
									swap(a[w],a[p]);
									start1=end1+sym.length();
									start2=end2+sym.length();
									end1=a1.find(sym,start1);
									end2=a2.find(sym,start2);
								}
								break;
							}
							break;

						}
						if(makeitswitch==true){
							const char* a3=a1.substr(start1,end1-start1).c_str();
							const char* a4=a2.substr(start2,end2-start2).c_str();
							int a5=atoi(a3);
							int a6=atoi(a4);
							if(a5>a6){
								swap(a[w],a[p]);
							}
						}
					}

				}
			}
		}
		}
		//after all we add it to last sorted list
		for(int i=0;i<counter;i++){
			set.lastsort+=a[i];
			set.lastsort+=(i==counter-1)?"":",";
		}
		delete[]a;
}
//our power function that check if name is legal and existed and calls to get the sublists
void P(AllSets *calc, string name) {
	Powerset power;
	getline(cin,name);
	getline(cin,name);
	if(name.length()==0){
		cerr << "ERROR: invalid input"<<endl;
		return;
	}
	if (name.size() > 8) {
		cerr << "ERROR: invalid input" << endl;
		return;
	}
	for (unsigned int i = 0; i < name.size(); i++) {
		if (islower((name.c_str())[i]) || !(isalpha(name.c_str()[i]))||isspace(name.c_str()[i])) {
			cerr << "ERROR: invalid input\n";
			return;
		}
	}
	Set *temp = calc->head;
	while (temp) {
		if (temp->setname.compare(name) == 0) {
			cout << "P(" << temp->setname << ")={";
			if(temp->size>10){
				cerr << "ERROR: invalid input\n";
				return;
			}
			int x=pow(2,temp->size);
			power.size=x;
			int *a1=new int[x];
			PSET(temp->setnumbers,a1,temp->size,0,0,power);
			sortedsublist(power.sets,power);
			cout<<power.lastsort;
			cout << "}\n";
			return;
		}
		temp = temp->nextset;
	}
	cerr << "ERROR: "<<name<<" does not exist\n";
	return;
}
//our like main finction that take our input and check what it is and go to the right function to do the work
void calculator() {
	string input;
	string name;
	string set1, set2;
	AllSets *calc = new AllSets;
	calc->head = NULL;
	cout<< "[1] add set\n[2] remove set\n[3] union\n[4] intersection\n[5] power set\n[6] print\n[0] exit"<< endl;
	while ((cin >> input) && (input != "0")) {
		if (input == "1") {
			CreateSet(calc, name);
			cout<< "[1] add set\n[2] remove set\n[3] union\n[4] intersection\n[5] power set\n[6] print\n[0] exit"<< endl;
		} else if (input == "2") {
			DeleteSet(calc, name);
			cout<< "[1] add set\n[2] remove set\n[3] union\n[4] intersection\n[5] power set\n[6] print\n[0] exit"<< endl;
		} else if (input == "3") {
			UnionSet(calc, set1, set2);
			cout<< "[1] add set\n[2] remove set\n[3] union\n[4] intersection\n[5] power set\n[6] print\n[0] exit"<< endl;
		} else if (input == "4") {
			IntersectionSet(calc, set1, set2);
			cout<< "[1] add set\n[2] remove set\n[3] union\n[4] intersection\n[5] power set\n[6] print\n[0] exit"<< endl;
		} else if (input == "5") {
			P(calc, set1);
			cout<< "[1] add set\n[2] remove set\n[3] union\n[4] intersection\n[5] power set\n[6] print\n[0] exit"<< endl;
		} else if (input == "6") {
			Print(calc, name);
			cout<< "[1] add set\n[2] remove set\n[3] union\n[4] intersection\n[5] power set\n[6] print\n[0] exit"<< endl;
		} else {
			cerr << "ERROR: invalid command; type 0 for exit" << endl;
			cout<< "[1] add set\n[2] remove set\n[3] union\n[4] intersection\n[5] power set\n[6] print\n[0] exit"<< endl;
		}
	}
}
int main() {
	calculator();
	return 0;
}
