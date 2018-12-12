#include <bits/stdc++.h>
using namespace std;

class Student {
private:
  string index;
  int marks;
  char grade;

public:
  Student (string iNo);
  string getIndex();
  int getMarks();
  char getGrade();
  void setIndex(string stuCode);
  void setMarks(int value);
  void setGrade(char grd);
  friend void readFile();
  friend void countSummary(vector <string> vect);
};

class Subject {
private:
  int totalStu;;
  string subNo;

public:
    int Sum;
    float Avg;
    float SD;
    int AC,BC,CC,DC,FC;
    float AP,BP,CP,DP,FP;
  vector <Student> students;
  Subject (string number);
  void setSize(int value);
  void setDetails(int value,string stuCode,char grd);
  string getCode();
  int getTotStu();
  friend void readFile();

};

vector <Subject> subjects;
vector <string> subCodes;


Student :: Student(string iNo){
  index = iNo;
}
void Subject :: setDetails(int value,string stuCode,char grd) {
  students.back().setIndex(stuCode);
  students.back().setMarks(value);
  students.back().setGrade(grd);
}
string Student :: getIndex(){
  return index;
}

int Student :: getMarks(){
  return marks;
}

char Student :: getGrade(){
  return grade;
}

void Student :: setIndex(string stuCode) {
  index = stuCode;
}

void Student :: setMarks(int value){
  marks = value;
}

void Student :: setGrade(char grd){
  grade = grd;
}

int Subject :: getTotStu(){
  return totalStu;
}

Subject :: Subject(string number){
  subNo = number;
}

void Subject :: setSize(int value) {
  totalStu = value;
}

string Subject :: getCode(){
  return subNo;
}


char setGrade(int marks){
  char grade;
  if (marks < 30) {
    grade = 'F';
  }
  else if(marks < 40){
    grade = 'D';
  }
  else if(marks < 55){
    grade = 'C';
  }
  else if(marks < 70){
    grade = 'B';
  }
  else{
    grade = 'A';
  }
  return grade;
}

int Stoi(string s){
    stringstream x(s);
    int y = 0;
    x >> y;
    return y;
}

void readFile() {
  string line,number,count;
  ifstream file ("abc");
  if (file.is_open()) {
    while (getline(file,line)) {
      int stuFlag = 0,subFlag = 0;
      int posn = line.find(" ");
      number = line.substr(0,posn);
      if (number.length() == 7) {
        subjects.push_back(Subject(number));
        subCodes.push_back(number);
        subFlag = 1;
      }
      else if(number.length() == 8){
        subjects.back().students.push_back(Student(number));
        stuFlag = 1;

      }
      else{
        cout << "Error!!!" << endl;
      }
      int posc = line.find("\n");
      count = line.substr(posn+1,posc);
      if (subFlag == 1) {
        int value = Stoi(count);
        subjects.back().setSize(value);  //set student size
      }
      if (stuFlag == 1) {
        int value = Stoi(count); //value = marks
        char grade = setGrade(value); //set grade
        string stuCode = subjects.back().students.back().getIndex ();
        subjects.back().students.back().setIndex(stuCode);
        subjects.back().students.back().setMarks(value);
        subjects.back().students.back().setGrade(grade);
      }
    }
  }
  else{
    cout << "File Not Found!" << endl;
  }
}

int findSub(string key){
  for (int i = 0; i < subjects.size(); i++) {
    if (subjects[i].getCode().compare(key) == 0) {
      return i;
    }
  }
  return -1;
}

int findStu(string key,int y){
  for (int i = 0; i < subjects[y].students.size(); i++) {
    if (subjects[y].students[i].getIndex().compare(key) == 0) {
      return i;
    }
  }
  return -1;
}

void displayStu(const string& key){
  int flag = 0;
  for (int i = 0; i < subjects.size(); i++) {
    int x = findStu(key,i);
    if (x >= 0) {
      if ( flag == 0) {
        cout << "----------" << key << "----------" << endl;
        flag = 1;
      }
      cout << "Subject : " << subjects[i].getCode() << "    Marks : " << subjects[i].students[x].getMarks() << "    Grade : " << subjects[i].students[x].getGrade() << endl;
    }
    else{
      if (i == subjects.size()-1) {
        cout << "Invalid Index Number" << endl;
      }
    }
  }
}


void displaySub(const string& key){
  int x = findSub(key);
  if (x < 0) {
    cout << "Invalid Subject Code!" << endl;
  }
  else{
    cout << "----------" << key << "----------" << endl;
    for (int i = 0; i < subjects[x].students.size(); i++) {
      cout << subjects[x].students[i].getIndex() << "_________" << subjects[x].students[i].getMarks() << " - "<< subjects[x].students[i].getGrade() << endl;
    }
  }
}

void displaySummary(string subCode){
  int x = findSub(subCode);
  if (x < 0) {
    cout << "Invalid Subject Code" << endl;
  }
  else{
    cout << "Average : " << subjects[x].Avg << endl;
    cout << "SD : " << subjects[x].SD << endl;
    cout << "A Count : " << subjects[x].AC << endl;
    cout << "B Count : " << subjects[x].BC << endl;
    cout << "C Count : " << subjects[x].CC << endl;
    cout << "D Count : " << subjects[x].DC << endl;
    cout << "F Count : " << subjects[x].FC << endl;
  }
}

void countSummary(vector <string> vect) {
  for (int k = 0; k < subjects.size(); k++) {
    int x = findSub(vect[k]);
    float avg = 0,sum = 0,SD = 0;
    for (int i = 0; i < subjects[x].students.size(); i++) {
      sum = sum + subjects[x].students[i].getMarks();
      subjects[i].Sum = sum;
    }
    avg = sum / subjects[x].students.size();
    subjects[k].Avg = avg;

    for (int i = 0; i < subjects[x].students.size(); i++) {
      SD = SD + pow(subjects[x].students[i].getMarks() - avg, 2);
    }
    SD = sqrt(SD / 10);
    subjects[k].SD = SD;

    int Ac = 0,Bc = 0,Cc = 0,Dc = 0,Fc = 0;
    for (int i = 0; i < subjects[x].students.size(); i++) {
      char y = subjects[x].students[i].getGrade();
      if ( y == 'A') {
        Ac++;
      }
      else if(y == 'B'){
        Bc++;
      }
      else if(y == 'C'){
        Cc++;
      }
      else if(y == 'D'){
        Dc++;
      }
      else{
        Fc++;
      }
    }


    float Ap,Bp,Cp,Dp,Fp;
    Ap = ((float) Ac / subjects[k].getTotStu())*100;
    Bp = ((float)Bc / subjects[k].getTotStu())*100;
    Cp = ((float)Cc / subjects[k].getTotStu())*100;
    Dp = ((float)Dc / subjects[k].getTotStu())*100;
    Fp = ((float)Fc / subjects[k].getTotStu())*100;
    subjects[k].AC = Ac;
    subjects[k].BC = Bc;
    subjects[k].CC = Cc;
    subjects[k].DC = Dc;
    subjects[k].FC = Fc;
    subjects[k].AP = Ap;
    subjects[k].BP = Bp;
    subjects[k].CP = Cp;
    subjects[k].DP = Dp;
    subjects[k].FP = Fp;
  }
}

void saveSummary() {
  const string disk = "summdata";
  ofstream file;
  file.open(disk);
  if (file.is_open()) {
    for (int i = 0; i < subjects.size(); i++) {
      file << subjects[i].getCode();
      file << " Average : " << subjects[i].Avg << "%";
      file << " A " << subjects[i].AP << "\%";
      file << " B " << subjects[i].BP << "\%";
      file << " C " << subjects[i].CP << "\%";
      file << " D " << subjects[i].DP << "\%";
      file << " F " << subjects[i].FP << "\%";
      file << endl;
    }
    file << EOF;
    file.close();
    cout << "Data Saved" << endl;
  }
  else{
    cout << "Unable to open the file" << endl;
  }
}

int main() {
  readFile();
  countSummary(subCodes);
cout << "**********Select an option : **********" << endl;
for (int i = 0; i < subCodes.size(); i++) {
  cout << subCodes[i] << endl;
}
int exit = 1;
int x = 0;
string y;
while (exit != 0) {
  cout << "1 - Display Subject" << endl;
  cout << "2 - Display Student" << endl;
  cout << "3 - Display Subject Summary" << endl;
  cout << "4 - Save Summaries" << endl;
  cout << "5 - Exit Program" << endl;

  cout << "Select an option: " << endl;
  cin >> x;
  switch (x) {

    case 1:
      cout << "Enter Subject Code : " << endl;
      cin >> y;
      displaySub(y);
      //int c = getchar();
      break;
    case 2:
      cout << "Enter Student Index No : " << endl;
      cin >> y;
      displayStu(y);
      //int c = getchar();
      break;
    case 3:
      cout << "Enter Subject Code" << endl;
      cin >> y;
      displaySummary(y);
      break;
    case 4:
      cout << "Save Summaries" << endl;
      saveSummary();
      break;
    case 5:
      cout << "Exit Program" << endl;
      exit = 0;
      break;
  }
}

  return 0;
}
