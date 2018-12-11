#include <bits/stdc++.h>
using namespace std;
list <string> stu;
list <string> sub;

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
};

class Subject {
private:
  int totalStu;;
  string subNo;

public:
  vector <Student> students;
  vector <float> summary;
  Subject (string number);
  void setSize(int value);
  void setDetails(int value,string stuCode,char grd);
  string getCode();
  int getTotStu();
  friend void readFile();

};

vector <Subject> subjects;


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

int isCreated(string number){
  int flag = 0;
  list <string> :: iterator it;
  it = find(stu.begin(),stu.end(),number);
  if (it != stu.end()) {
    flag = 1;
  }
  return flag;
}

int Stoi(string s){
    stringstream x(s);
    int y = 0;
    x >> y;
    return y;
}

void readFile() {
  int isCreated(string number);
  string line,number,count;
  ifstream file ("abc");
  if (file.is_open()) {
    while (getline(file,line)) {
      int stuFlag = 0,subFlag = 0;
      int posn = line.find(" ");
      number = line.substr(0,posn);
      if (number.length() == 7) {
        subjects.push_back(Subject(number));
        sub.push_back(number);
        subFlag = 1;
      }
      else if(number.length() == 8){
        subjects.back().students.push_back(Student(number));
        stu.push_back(number);
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
        //subjects.back().students.back().setDetails(value,stuCode,grade);
        subjects.back().students.back().setIndex(stuCode);
        subjects.back().students.back().setMarks(value);
        subjects.back().students.back().setGrade(grade);
        //subjects.back().setDetails(value,stuCode,grade);
        /*setDetails :- set details of students
        getCode :- getsubject code */
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

void displayStu(string key){
  for (int i = 0; i < subjects.size(); i++) {
    cout << "----------" << key << "----------" << endl;
    cout << endl << endl;
    for (int j = 0; j < subjects[i].students.size(); j++) {
      cout << subjects[i].getCode() << "----" << subjects[i].students[j].getMarks() << "----" << subjects[i].students[j].getGrade() << endl;
    }
  }
}


void displaySub(string key){
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
  if(x < 0){
    cout << "Invalid Subject Code!" << endl;
  }
  float avg = 0,sum = 0,SD = 0;
  for (int i = 0; i < subjects[x].students.size(); i++) {
    sum = sum + subjects[x].students[i].getMarks();
  }
  avg = sum / subjects[x].students.size();
  cout << "Average : " << avg << endl;

  for (int i = 0; i < subjects[x].students.size(); i++) {
    SD = SD + pow(subjects[x].students[i].getMarks() - avg, 2);
  }
  SD = sqrt(SD / 10);
  cout << "SD : " << SD << endl;

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
  cout << "A count : " << Ac << endl;
  cout << "B count : " << Bc << endl;
  cout << "C count : " << Cc << endl;
  cout << "D count : " << Dc << endl;
  cout << "F count : " << Fc << endl;

  float Ap,Bp,Cp,Dp,Fp;

  Ap = ((float) Ac / subjects[x].getTotStu())*100;
  Bp = ((float)Bc / subjects[x].getTotStu())*100;
  Cp = ((float)Cc / subjects[x].getTotStu())*100;
  Dp = ((float)Dc / subjects[x].getTotStu())*100;
  Fp = ((float)Fc / subjects[x].getTotStu())*100;

  subjects[x].summary.push_back(Ap);
  subjects[x].summary.push_back(Bp);
  subjects[x].summary.push_back(Cp);
  subjects[x].summary.push_back(Dp);
  subjects[x].summary.push_back(Fp);
  subjects[x].summary.push_back(avg);

}

void saveSummary(string key) {
  string disk = "summdata.txt";
  ofstream file;
  file.open(disk);
  if (file.is_open()) {
    for (int i = 0; i < subjects.size(); i++) {
      file << subjects[i].getCode();
      file << "Average : " << subjects[i].summary[5] << "%";
      file << "A" << subjects[i].summary[0] << "\%";
      file << "B" << subjects[i].summary[1] << "\%";
      file << "C" << subjects[i].summary[2] << "\%";
      file << "D" << subjects[i].summary[3] << "\%";
      file << "F" << subjects[i].summary[4] << "\%";
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

int main(int argc, char const *argv[]) {
  /*readFile();
  displaySub("SCS1201");
  displaySub("SCS1202");
  displaySub("SCS1203");
  displayStu("17000001");
  displaySummary("SCS1201");
  saveSummary("SCS1201");*/
  cout << "**********Select an option : **********" << endl;
  cout << "1 - Display Subject" << endl;
  cout << "2 - Display Student" << endl;
  cout << "3 - Display Subject Summary" << endl;
  cout << "4 - Save Summaries" << endl;
  cout << "5 - Exit Program" << endl;

  int x;
  cout << "Select an option: " << endl;
  cin >> x;

  switch (x) {
    string y;
    case 1:
      cout << "Enter Subject Code : " << endl;
      cin >> y;
      displaySub(y);
    case 2:
      cout << "Enter Student Index No : " << endl;
      cin >> y;
      displayStu(y);
    case 3:
      cout << "Enter Subject Code" << endl;
      cin >> y;
      displaySummary(y);
    case 4:
      cout << "Save Summaries" << endl;
      saveSummary();
    case 5:
      //exit
  }

  return 0;
}
