#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<map>
#include"Header.h"
using namespace std;
vector<Complaint> Admin::Complaints;
person::person(string name, char gender, string dateOfBirth, string nationality, string bloodType, string address, string joinData, string email, string phoneNumber, string password, string college, string Department, string major) {
	this->name = name;
	this->email = email;
	this->phoneNumber = phoneNumber;
	this->password = password;
	this->gender = gender;
	this->nationality = nationality;
	this->dateOfBirth = dateOfBirth;
	this->bloodType = bloodType;
	this->address = address;
	this->joinData = joinData;
	this->college = college;
	this->Department = Department;
	this->major = major;
	ID = generateRandom6Digit();
}
int person::getID()const {
	return ID;
}
string person::getName()const {
	return name;
}
string person::getEmail() const {
	return email;
}
string person::getPhoneNumber() const {
	return phoneNumber;
}
string person::getPassword() const {
	return password;
}
char person::getGender() const {
	return gender;
}
string person::getNationality() const {
	return nationality;
}
string person::getDateOfBirth() const {
	return dateOfBirth;
}
string person::getBloodType() const {
	return bloodType;
}
string person::getAddress() const {
	return address;
}
string person::getJoinDate() const {
	return joinData;
}
string person::getCollege() const {
	return college;
}
string person::getDepartment() const {
	return Department;
}
string person::getMajor() const {
	return major;
}




students::students()
	: person("No Name", 'M', "2000-01-01", "Unknown", "O+", "Unknown", "2000-01-01",
		"unknown@email.com", "0000000000", "default", "Unknown", "Unknown", "Unknown")
{
	TawjihiAverage = 0.0;
	planVersion = "0000";
	semesterGPA = 0.0;
	GPA = 0.0;
	studyLevel = "Unknown";
	statos = "Inactive";
	completedHours = 0;
	totalHours = 132;
}
students::students(string name, char gender, string dateOfBirth, string nationality, string bloodType, string address, string joinData, string email, string phoneNumber, string password, string college, string Department, string major, float TawjihiAverage, double semesterGPA, double GPA, string studyLevel, string planVersion, string statos, int completedHours, int totalHours)
	:person(name, gender, dateOfBirth, nationality, bloodType, address, joinData, email, phoneNumber, password, college, Department, major) {
	this->name = name;
	this->email = email;
	this->phoneNumber = phoneNumber;
	this->password = password;
	this->gender = gender;
	this->nationality = nationality;
	this->dateOfBirth = dateOfBirth;
	this->bloodType = bloodType;
	this->address = address;
	this->joinData = joinData;
	this->college = college;
	this->Department = Department;
	this->major = major;
	this->TawjihiAverage = TawjihiAverage;
	this->semesterGPA = semesterGPA;
	this->GPA = GPA;
	this->studyLevel = studyLevel;
	this->planVersion = planVersion;
	this->statos = statos;
	this->completedHours = completedHours;
	this->totalHours = totalHours;
}
void students::SaveToFile(ofstream& out) const {
	// حفظ بيانات البيرسون الأساسية
	out << ID << "," << name << "," << email << "," << phoneNumber << "," << password << ","
		<< gender << "," << nationality << "," << dateOfBirth << "," << bloodType << ","
		<< address << "," << joinData << "," << college << "," << Department << ","
		<< major << ",";

	// حفظ بيانات الطالب الإضافية
	out << TawjihiAverage << "," << semesterGPA << "," << GPA << ","
		<< studyLevel << "," << planVersion << "," << statos << ","
		<< completedHours << "," << totalHours << ",";

	// حفظ المواد المسجلة في الفصل الحالي (semestercourses)
	out << semestercourses.size();
	for (const auto& course : semestercourses) {
		out << "," << course;
	}

	// حفظ جميع المواد التي سجلها الطالب (courses)
	out << "," << courses.size();
	for (const auto& course : courses) {
		out << "," << course;
	}

	// حفظ الدرجات (greadcourse map)
	out << "," << greadcourse.size();
	for (const auto& gradePair : greadcourse) {
		const gread& g = gradePair.second;
		out << "," << gradePair.first << "," << g.getfirst() << ","
			<< g.getseconde() << "," << g.getmid() << "," << g.getfinal();
	}

	// حفظ معلومات الفصول السابقة (totalgpa map)
	out << "," << totalgpa.size();
	for (const auto& gpaPair : totalgpa) {
		out << "," << gpaPair.first << "," << gpaPair.second.getsemestergpa()
			<< "," << gpaPair.second.gethours();
	}

	// حفظ البيانات الأخرى
	out << "," << Numberofsemesters << "," << warning;

	out << "\n";
}
bool students::LoadFromFileLine(const string& line) {
	stringstream ss(line);
	string temp;
	try {
		// تحميل بيانات البيرسون الأساسية
		getline(ss, temp, ','); ID = stoi(temp);
		getline(ss, name, ',');
		getline(ss, email, ',');
		getline(ss, phoneNumber, ',');
		getline(ss, password, ',');
		getline(ss, temp, ','); gender = temp[0];
		getline(ss, nationality, ',');
		getline(ss, dateOfBirth, ',');
		getline(ss, bloodType, ',');
		getline(ss, address, ',');
		getline(ss, joinData, ',');
		getline(ss, college, ',');
		getline(ss, Department, ',');
		getline(ss, major, ',');

		// تحميل بيانات الطالب الإضافية
		getline(ss, temp, ','); TawjihiAverage = stof(temp);
		getline(ss, temp, ','); semesterGPA = stod(temp);
		getline(ss, temp, ','); GPA = stod(temp);
		getline(ss, studyLevel, ',');
		getline(ss, planVersion, ',');
		getline(ss, statos, ',');
		getline(ss, temp, ','); completedHours = stoi(temp);
		getline(ss, temp, ','); totalHours = stoi(temp);

		// تحميل المواد المسجلة في الفصل الحالي
		getline(ss, temp, ',');
		int semesterCoursesCount = stoi(temp);
		semestercourses.clear();
		for (int i = 0; i < semesterCoursesCount; i++) {
			getline(ss, temp, ',');
			semestercourses.push_back(temp);
		}

		// تحميل جميع المواد التي سجلها الطالب
		getline(ss, temp, ',');
		int allCoursesCount = stoi(temp);
		courses.clear();
		for (int i = 0; i < allCoursesCount; i++) {
			getline(ss, temp, ',');
			courses.push_back(temp);
		}

		// تحميل الدرجات
		getline(ss, temp, ',');
		int gradesCount = stoi(temp);
		greadcourse.clear();
		for (int i = 0; i < gradesCount; i++) {
			string courseCode;
			double first, seconde, mid, final;

			getline(ss, courseCode, ',');
			getline(ss, temp, ','); first = stod(temp);
			getline(ss, temp, ','); seconde = stod(temp);
			getline(ss, temp, ','); mid = stod(temp);
			getline(ss, temp, ','); final = stod(temp);

			addgread(courseCode, first, seconde, mid, final);
		}

		// تحميل معلومات الفصول السابقة
		getline(ss, temp, ',');
		int gpaCount = stoi(temp);
		totalgpa.clear();
		for (int i = 0; i < gpaCount; i++) {
			int semesterNum;
			double sgpa;
			int hours;

			getline(ss, temp, ','); semesterNum = stoi(temp);
			getline(ss, temp, ','); sgpa = stod(temp);
			getline(ss, temp, ','); hours = stoi(temp);

			hoursgpa hg(sgpa, hours);
			totalgpa[semesterNum] = hg;
		}

		// تحميل البيانات الأخرى
		getline(ss, temp, ','); Numberofsemesters = stoi(temp);
		getline(ss, temp, ','); warning = (temp == "1");
	}
	catch (const exception& e) {
		cerr << "Error parsing student data: " << e.what() << endl;
		return false;
	}
	return true;
}
void students::DataEntry() {
	int Choose;
	bool z = true;
	while (z) {
		cout << "\033[90m" << string(33, '-') << "\033[0m";
		cout << left << setw(41) << "\n\033[1;33m|====== Edit Student Data ======|\033[0m";
		cout << endl;
		cout << "\033[90m" << string(33, '-') << "\033[0m" << endl;
		cout << left << setw(47) << "\033[90m|\033[38;5;14m1) Edit Name" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m2) Edit Gender" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m3) Edit Date of Birth" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m4) Edit Nationality" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m5) Edit Blood Type" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m6) Edit Address" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m7) Edit Join Date" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m8) Edit Email" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m9) Edit Phone Number" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m10) Edit Password" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m11) Edit College" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m12) Edit Department" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m13) Edit Major" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m14) Edit Tawjihi Average" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m15) Edit Plan Version" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m16) Edit Study Level" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m17) Edit Status" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m18) Exit Edit Menu" << "\033[90m|\033[0m\n";

		cout << "\033[90m" << string(33, '-') << "\033[0m" << endl << endl;

		cout << "\033[34mChoose an option: \033[0m";
		cin >> Choose;

		switch (Choose) {
		case 1:
			cout << endl << "Enter the full name" << endl;
			cin >> name;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 2:
			cout << endl << "Enter gender" << endl;
			cin >> gender;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 3:
			cout << endl << "Enter Date of Birth" << endl;
			cin >> dateOfBirth;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 4:
			cout << endl << "Enter Nationality" << endl;
			cin >> nationality;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 5:
			cout << endl << "Enter Blood Type" << endl;
			cin >> bloodType;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 6:
			cout << endl << "Enter Address" << endl;
			cin >> address;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 7:
			cout << endl << "Enter Join Date" << endl;
			cin >> joinData;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 8:
			cout << endl << "Enter Email" << endl;
			cin >> email;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 9:
			cout << endl << "Enter Phone Number" << endl;
			cin >> phoneNumber;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 10:
			cout << endl << "Enter Password" << endl;
			cin >> password;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 11:
			cout << endl << "Enter College" << endl;
			cin >> college;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 12:
			cout << endl << "Enter Department" << endl;
			cin >> Department;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 13:
			cout << endl << "Enter Major" << endl;
			cin >> major;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 14:
			cout << endl << "Enter Tawjihi Average" << endl;
			cin >> TawjihiAverage;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 15:
			cout << endl << "Enter Plan Version" << endl;
			cin >> planVersion;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 16:
			cout << endl << "Enter Study Level" << endl;
			cin >> studyLevel;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 17:
			cout << endl << "Enter Status" << endl;
			cin >> statos;
			cout << endl;
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 18:
			system("cls");
			z = false;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		default:
			cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
			break;
		}
	}
}
float students::getTawjihiAverage() const {
	return TawjihiAverage;
}
double students::getSemesterGPA() const {
	return semesterGPA;
}
double students::getOverallGPA() const {
	return GPA;
}
string students::getStudyLevel() const {
	return studyLevel;
}
string students::getPlanVersion() const {
	return planVersion;
}
string students::getStatus() const {
	return statos;
}
int students::getCompletedHours() const {
	return completedHours;
}
int students::getTotalHours() const {
	return totalHours;
}
string students::getRegisteredCourse(const long long Item) const {
	return semestercourses[Item];
}
long long students::getLengthSemestercourses()const {
	return semestercourses.size();
}
void students::Jointhecourse(arrayList<Course>& list, arrayList<students>& listS, string courseid, int ID, students& s1) {
	int loc1 = serchCourseByID(list, courseid);
	int loc2 = serchstudentByID(listS, ID);
	if (loc1 > -1) {
		Course c1 = list.opp(loc1);
		bool test = MakeSureTheCourseIsNotRegistered(courseid);
		if (test) {
			semestercourses.push_back(courseid);
			c1.AddStudentsInTheCourse(ID);
			listS.replaceAt(loc2, s1);
			list.replaceAt(loc1, c1);
			system("cls");
			cout << "\033[92mThe course was successfully registered!\033[0m\n";
		}
		else {
			system("cls");
			cout << "\033[31mThis course is already registered...\033[0m" << endl;
		}
	}
	else {
		system("cls");
		cout << "\033[31mThe course you are looking for does not exist or is not offered..\033[0m" << endl;
	}
}
void students::UnregisterfromCourse(arrayList<Course>& list, arrayList<students>& listS, string courseid, int ID, students& s1) {
	int loc1 = serchCourseByID(list, courseid);
	int loc2 = serchstudentByID(listS, ID);
	if (loc1 > -1) {
		for (int i = 0; i < semestercourses.size(); i++) {
			string test;
			test = semestercourses[i];
			if (test == courseid) {
				semestercourses.erase(semestercourses.begin() + i);

				Course c1 = list.opp(loc1);
				c1.StudentRemovedFromThisCourse(ID, s1);
				listS.replaceAt(loc2, s1);
				list.replaceAt(loc1, c1);
				system("cls");
				cout << "\033[92mThe course was successfully Unregistered!\033[0m\n";
				return;
			}

		}
	}
	else
		system("cls");
	cout << "\033[31mThe course is not registered\033[0m";
}
void students::ViewMyCourses(arrayList<Course>& list) {
	Course c1;
	bool found = false;
	long long location;
	if (semestercourses.size() > 0) {
		for (int i = 0; i < semestercourses.size(); i++) {
			location = serchCourseByID(list, semestercourses[i]);
			if (location > -1) {
				found = true;
				c1 = list.opp(location);
				cout << "\n\033[90m==============[ \033[1;33mCourse Information\033[90m ]==============\033[0m\n";

				cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCourse Code:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getCourseCode() << "\033[0m\033[90m||\033[0m\n";
				cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCourse Name:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getCourseName() << "\033[0m\033[90m||\033[0m\n";
				cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCredit Hours:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getCreditHours() << "\033[0m\033[90m||\033[0m\n";
				cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mDepartment:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getDepartment() << "\033[0m\033[90m||\033[0m\n";
				cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCollege:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getCollege() << "\033[0m\033[90m||\033[0m\n";
				cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mInstructor Name:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getInstructorName() << "\033[0m\033[90m||\033[0m\n";
				cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mSemester Offered:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getSemesterOffered() << "\033[0m\033[90m||\033[0m\n";
				cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mSchedule:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getSchedule() << "\033[0m\033[90m||\033[0m\n";
				cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mLocation:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getLocation() << "\033[0m\033[90m||\033[0m\n";
				cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCapacity:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getCapacity() << "\033[0m\033[90m||\033[0m\n";
				cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mEnrolled Count:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getEnrolledCount() << "\033[0m\033[90m||\033[0m\n";

				cout << "\033[90m===================================================\033[0m\n\n";



			}
		}
	}
	if (found) {
		cout << "\033[38;5;10mThe operation was successful.....\033[0m" << endl;
	}
	else {
		system("cls");
		cout << "\033[31mThe list is empty. There is no information about any course.\033[0m" << endl;
	}
}
void students::Showgrades(arrayList<Course>& list) {
	long long loc1;
	Course c1;
	gread g1;
	if (semestercourses.size() > 0) {

		for (int i = 0; i < semestercourses.size(); i++) {
			loc1 = serchCourseByID(list, semestercourses[i]);
			if (loc1 > -1) {
				c1 = list.opp(loc1);
				g1 = greadcourse[c1.getCourseCode()];
				if (g1.getTypeCourse() == 0) {
					cout << "\033[90m" << string(77, '-') << "\033[0m" << endl;

					cout << "\033[1;33m" << left
						<< setw(17) << "Course Name"
						<< setw(15) << "First"
						<< setw(15) << "Second"
						<< setw(15) << "Final"
						<< setw(15) << "Total"
						<< "\033[0m" << endl;

					cout << "\033[90m" << string(77, '-') << "\033[0m" << endl;

					cout << "\033[38;5;14m" << left
						<< setw(17) << c1.getCourseName()
						<< setw(15) << (to_string(g1.getfirst()) + "/30")
						<< setw(15) << (to_string(g1.getseconde()) + "/30")
						<< setw(15) << (to_string(g1.getfinal()) + "/40")
						<< setw(15) << (to_string(g1.gettotal()) + "/100")
						<< "\033[0m" << endl;
				}
				else if (g1.getTypeCourse() == 1) {
					cout << "\033[90m" << string(77, '-') << "\033[0m" << endl;
					cout << "\033[90m" << string(54, '-') << "\033[0m" << endl;

					cout << "\033[1;33m" << left
						<< setw(17) << "Course Name"
						<< setw(12) << "Mid"
						<< setw(12) << "Final"
						<< setw(12) << "Total"
						<< "\033[0m" << endl;

					cout << "\033[90m" << string(54, '-') << "\033[0m" << endl;
					cout << "\033[38;5;14m" << left
						<< setw(17) << c1.getCourseName()
						<< setw(12) << (to_string(g1.getmid()) + "/50")
						<< setw(12) << (to_string(g1.getfinal()) + "/50")
						<< setw(12) << (to_string(g1.gettotal()) + "/100")
						<< "\033[0m" << endl;

					cout << "\033[90m" << string(54, '-') << "\033[0m" << endl;
				}
			}
			else {
				cout << "\033[31mThe course is not registered\033[0m";
			}
		}
	}
	else {
		system("cls");
		cout << "\033[31mThe list is empty. There is no information about any course and greads.\033[0m" << endl;
	}

}
void students::ViewMyProfile() {
	cout << "\n\033[90m==============[ \033[1;33mStudent Information\033[90m ]==============\033[0m\n";

	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mName:\033[0m" << "\033[38;5;14m" << setw(29) << getName() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mEmail:\033[0m" << "\033[38;5;14m" << setw(29) << getEmail() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mPhone Number:\033[0m" << "\033[38;5;14m" << setw(29) << getPhoneNumber() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mGender:\033[0m" << "\033[38;5;14m" << setw(29) << getGender() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mNationality:\033[0m" << "\033[38;5;14m" << setw(29) << getNationality() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mDate of Birth:\033[0m" << "\033[38;5;14m" << setw(29) << getDateOfBirth() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mBlood Type:\033[0m" << "\033[38;5;14m" << setw(29) << getBloodType() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mAddress:\033[0m" << "\033[38;5;14m" << setw(29) << getAddress() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mJoin Date:\033[0m" << "\033[38;5;14m" << setw(29) << getJoinDate() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCollege:\033[0m" << "\033[38;5;14m" << setw(29) << getCollege() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mDepartment:\033[0m" << "\033[38;5;14m" << setw(29) << getDepartment() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mMajor:\033[0m" << "\033[38;5;14m" << setw(29) << getMajor() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mTawjihi Average:\033[0m" << "\033[38;5;14m" << setw(29) << (to_string(getTawjihiAverage()) + "%") << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mPlan Version:\033[0m" << "\033[38;5;14m" << setw(29) << getPlanVersion() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mSemester GPA:\033[0m" << "\033[38;5;14m" << setw(29) << getSemesterGPA() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mOverall GPA:\033[0m" << "\033[38;5;14m" << setw(29) << getOverallGPA() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mStudy Level:\033[0m" << "\033[38;5;14m" << setw(29) << getStudyLevel() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mStatus:\033[0m" << "\033[38;5;14m" << setw(29) << getStatus() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCompleted Hours:\033[0m" << "\033[38;5;14m" << setw(29) << getCompletedHours() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mTotal Hours:\033[0m" << "\033[38;5;14m" << setw(29) << getTotalHours() << "\033[0m\033[90m||\033[0m\n";
	cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mStudent ID:\033[0m" << "\033[38;5;14m" << setw(29) << getID() << "\033[0m\033[90m||\033[0m\n";

	cout << "\033[90m===================================================\033[0m\n\n";



	cout << "\033[38;5;10mThe operation was successful.....\033[0m" << endl;
}
void students::EditMyPersonalInfo(arrayList<students>& listS, students& s1) {
	system("cls");
	int Choose;
	bool z = true;
	while (z) {
		cout << "\033[90m" << string(33, '-') << "\033[0m";
		cout << left << setw(41) << "\n\033[1;33m|====== Edit Student Data ======|\033[0m";
		cout << endl;
		cout << "\033[90m" << string(33, '-') << "\033[0m" << endl;
		cout << left << setw(47) << "\033[90m|\033[38;5;14m1) Edit Name" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m2) Edit Gender" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m3) Edit Date of Birth" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m4) Edit Nationality" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m5) Edit Blood Type" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m6) Edit Address" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m7) Edit Join Date" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m8) Edit Email" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m9) Edit Phone Number" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m10) Edit Password" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m11) Edit College" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m12) Edit Department" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m13) Edit Major" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m14) Edit Tawjihi Average" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m15) Edit Plan Version" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m16) Edit Study Level" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m17) Edit Status" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m18) Exit Edit Menu" << "\033[90m|\033[0m\n";

		cout << "\033[90m" << string(33, '-') << "\033[0m" << endl << endl;


		cout << "\033[34mChoose an option: \033[0m";
		cin >> Choose;

		switch (Choose) {
		case 1:
			system("cls");
			cout << endl << "Enter the full name" << endl;
			getline(cin, name);
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 2:
			system("cls");
			cout << endl << "Enter gender" << endl;
			cin >> gender;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 3:
			system("cls");
			cout << endl << "Enter Date of Birth" << endl;
			cin >> dateOfBirth;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 4:
			system("cls");
			cout << endl << "Enter Nationality" << endl;
			cin >> nationality;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 5:
			system("cls");
			cout << endl << "Enter Blood Type" << endl;
			cin >> bloodType;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 6:
			system("cls");
			cout << endl << "Enter Address" << endl;
			cin >> address;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 7:
			system("cls");
			cout << endl << "Enter Join Date" << endl;
			cin >> joinData;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 8:
			system("cls");
			cout << endl << "Enter Email" << endl;
			cin >> email;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 9:
			system("cls");
			cout << endl << "Enter Phone Number" << endl;
			cin >> phoneNumber;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 10:
			system("cls");
			cout << endl << "Enter Password" << endl;
			cin >> password;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 11:
			system("cls");
			cout << endl << "Enter College" << endl;
			cin >> college;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 12:
			system("cls");
			cout << endl << "Enter Department" << endl;
			cin >> Department;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 13:
			system("cls");
			cout << endl << "Enter Major" << endl;
			cin >> major;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 14:
			system("cls");
			cout << endl << "Enter Tawjihi Average" << endl;
			cin >> TawjihiAverage;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 15:
			system("cls");
			cout << endl << "Enter Plan Version" << endl;
			cin >> planVersion;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 16:
			system("cls");
			cout << endl << "Enter Study Level" << endl;
			cin >> studyLevel;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 17:
			system("cls");
			cout << endl << "Enter Status" << endl;
			cin >> statos;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 18:
			system("cls");
			z = false;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		default:
			system("cls");
			cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
			break;
		}
	}
	long long loc = serchstudentByID(listS, s1.getID());
	if (loc > -1) {
		listS.replaceAt(loc, s1);
		system("cls");
		cout << "\033[92mYour information has been updated successfully.!\033[0m\n";
	}
	else {
		system("cls");
		cout << "\033[31mAn error occurred. Please try again..\033[0m" << endl;
	}
}
bool students::MakeSureTheCourseIsNotRegistered(string courseid) {
	for (int i = 0; i < semestercourses.size(); i++) {
		if (courseid == semestercourses[i]) {
			return false;
		}
	}
	return true;
}
void students::CourseRegistration(string courseid) {
	semestercourses.push_back(courseid);
}
void students::PrintRegisteredCourses(arrayList<Course>& listC) {
	gread g1;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[90m " << string(58, ' ') << "\033[1;33m*Welcome Back to JUST System*\033[1;36m" << string(59, ' ') << "\033[90m\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;

	cout << "\033[1;36m============================================================= [ Student Transcript ] ==============================================================" << endl;
	cout << endl << endl;

	cout << string(46, ' ') << "\033[90m" << string(63, '=') << endl;
	cout << string(46, ' ') << "\033[90m||============ [" << "\033[1;33m Transcript for Student " << getID() << " " << "\033[90m] ============||" << endl;
	cout << string(46, ' ') << "\033[90m" << string(63, '=') << endl;
	cout << string(46, ' ') << "\033[90m|" << string(13, ' ') << "\033[1;33mCourse" << string(20, ' ') << "Grade" << string(17, ' ') << "\033[90m|" << endl;
	cout << string(46, ' ') << "\033[90m" << string(63, '-') << "\033[0m" << endl;
	for (int i = 0; i < courses.size(); i++) {
		long long location = serchCourseByID(listC, courses[i]);
		if (location > -1) {
			Course c1 = listC.opp(location);
			g1 = greadcourse[c1.getCourseCode()];
			cout << string(46, ' ') << "\033[90m|\033[1;36m" << string(13, ' ') << left << setw(26) << c1.getCourseName() << g1.getcourseSymbol() << string(15, ' ') << "\033[90m|" << endl;
			cout << string(46, ' ') << "\033[90m" << string(63, '-') << "\033[0m" << endl;
		}
	}
	cout << string(46, ' ') << "\033[90m" << string(63, '=') << endl;
	cout << string(46, ' ') << "\033[90m|\033[1;36m" << string(13, ' ') << "GPA: " << getOverallGPA() << "/4.20" << string(15, ' ') << "TotalHours: " << left << setw(10) << getCompletedHours() << "\033[90m|" << endl;
	cout << string(46, ' ') << "\033[90m" << string(63, '-') << "\033[0m" << endl;
	cout << "\033[0m";
}
void students::addgread(string coursecode, double Sfirst, double Sseconde, double Smid, double Sfinal) {
	greadcourse[coursecode].setGrades(Sfirst, Sseconde, Smid, Sfinal);
}
void students::printcourses(string coursecode) {
	cout << ID << "  " << greadcourse[coursecode].getfirst() << "  " << greadcourse[coursecode].getseconde() << "  " << greadcourse[coursecode].getmid() << greadcourse[coursecode].getfinal();
}
void students::submitComplaint() {
	cin.ignore();
	Admin a;
	cout << "\n\033[1;33mEnter your complaint in English: ";
	string msg;
	getline(cin, msg);

	Complaint c = { "Student", this->ID, msg };
	a.setcomplaints(c);

	cout << endl << "\033[38;5;10mThe operation was successful.....\033[0m" << endl;
}
string students::getsemestercourses(int i) {
	return semestercourses[i];
}
gread students::getgread(string semestercourse) {
	return greadcourse[semestercourse];
}
void students::setsemesterGPA(double semestergpa, int semesterhours) {
	semesterGPA = semestergpa;
	hoursgpa hg(semestergpa, semesterhours);
	Numberofsemesters++;
	totalgpa[Numberofsemesters] = hg;

}
void students::setGPA() {
	double sum = 0;
	int totalhours = 0;
	hoursgpa hg(0, 0);
	for (int i = 0; i < Numberofsemesters; i++) {
		hg = totalgpa[i];
		sum += (hg.getsemestergpa() * hg.gethours());
		totalhours += hg.gethours();
	}
	GPA = (sum / totalhours);
	if (GPA <= 2.1) {
		warning = true;
	}

}
void students::addcours(string course) {
	courses.push_back(course);
}
void students::clearsemestercourses() {
	semestercourses.clear();
}
void students::setstudyLevel() {
	if (totalHours < 33) {
		studyLevel = "first";
	}
	if (totalHours >= 33 && totalHours < 66) {
		studyLevel = "second";
	}
	else if (totalHours >= 66 && totalHours < 99) {
		studyLevel = "third";
	}
	else if (totalHours >= 99 && totalHours < 132) {
		studyLevel = "fourth";
	}
}



teachers::teachers()
	: person("No Name", 'M', "2000-01-01", "Unknown", "O+", "Unknown", "2000-01-01",
		"unknown@email.com", "0000000000", "default", "Unknown", "Unknown", "Unknown")
{
	academicRank = "None";
	salary = 0.0;
	officeHours = "N/A";
	NumberOfHolidays = 0;
}
teachers::teachers(string name, char gender, string dateOfBirth, string nationality, string bloodType, string address, string joinData, string email, string phoneNumber, string password, string college, string Department, string major, string academicRank, double salary, string officeHours, int NumberOfHolidays)
	:person(name, gender, dateOfBirth, nationality, bloodType, address, joinData, email, phoneNumber, password, college, Department, major) {
	this->academicRank = academicRank;
	this->salary = salary;
	this->officeHours = officeHours;
	this->NumberOfHolidays = NumberOfHolidays;
}
void teachers::SaveToFile(ofstream& out) const {
	// حفظ بيانات البيرسون الأساسية
	out << ID << "," << name << "," << email << "," << phoneNumber << "," << password << ","
		<< gender << "," << nationality << "," << dateOfBirth << "," << bloodType << ","
		<< address << "," << joinData << "," << college << "," << Department << ","
		<< major << ",";

	// حفظ بيانات المعلم الإضافية
	out << academicRank << "," << salary << "," << officeHours << "," << NumberOfHolidays << ",";

	// حفظ المواد الخاصة بالمعلم (MyCourses)
	out << MyCourses.size();
	for (const auto& course : MyCourses) {
		out << "," << course;
	}
	out << "\n";
}
bool teachers::LoadFromFileLine(const string& line) {
	stringstream ss(line);
	string temp;

	try {
		// تحميل بيانات البيرسون الأساسية
		getline(ss, temp, ','); ID = stoi(temp);
		getline(ss, name, ',');
		getline(ss, email, ',');
		getline(ss, phoneNumber, ',');
		getline(ss, password, ',');
		getline(ss, temp, ','); gender = temp[0];
		getline(ss, nationality, ',');
		getline(ss, dateOfBirth, ',');
		getline(ss, bloodType, ',');
		getline(ss, address, ',');
		getline(ss, joinData, ',');
		getline(ss, college, ',');
		getline(ss, Department, ',');
		getline(ss, major, ',');

		// تحميل بيانات المعلم الإضافية
		getline(ss, academicRank, ',');
		getline(ss, temp, ','); salary = stod(temp);
		getline(ss, officeHours, ',');
		getline(ss, temp, ','); NumberOfHolidays = stoi(temp);

		// تحميل المواد الخاصة بالمعلم (MyCourses)
		getline(ss, temp, ',');
		int coursesCount = stoi(temp);
		MyCourses.clear();
		for (int i = 0; i < coursesCount; i++) {
			getline(ss, temp, ',');
			MyCourses.push_back(temp);
		}
	}
	catch (const exception& e) {
		cerr << "Error parsing teacher data: " << e.what() << endl;
		return false;
	}
	return true;
}
void teachers::DataEntryteachers() {
	int Choose;
	bool z = true;
	while (z) {
		cout << "\033[33m" << string(33, '-') << "\033[0m";
		cout << left << setw(41) << "\n\033[33m|====== Edit teachers Data ======|\033[0m";
		cout << endl;
		cout << "\033[33m" << string(33, '-') << "\033[0m" << endl;
		cout << left << setw(41) << "\033[33m|\033[0m1) Edit Name" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m2) Edit Gender" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m3) Edit Date of Birth" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m4) Edit Nationality" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m5) Edit Blood Type" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m6) Edit Address" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m7) Edit Join Date" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m8) Edit Email" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m9) Edit Phone Number" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m10) Edit Password" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m11) Edit College" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m12) Edit Department" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m13) Edit Major" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m14) Edit academic Rank" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m15) Edit Salary" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m16) Edit office Hours" << "\033[33m|\033[0m\n";
		cout << left << setw(41) << "\033[33m|\033[0m17) Edit Number Of Holidays" << "\033[33m|\033[0m\n";
		cout << "\033[33m" << string(33, '-') << "\033[0m" << endl << endl;
		cout << "\033[34mChoose an option: \033[0m";
		cin >> Choose;

		switch (Choose) {
		case 1:
			cout << endl << "Enter the full name" << endl;
			getline(cin, name);
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 2:
			cout << endl << "Enter gender" << endl;
			cin >> gender;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 3:
			cout << endl << "Enter Date of Birth" << endl;
			cin >> dateOfBirth;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 4:
			cout << endl << "Enter Nationality" << endl;
			cin >> nationality;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 5:
			cout << endl << "Enter Blood Type" << endl;
			cin >> bloodType;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 6:
			cout << endl << "Enter Address" << endl;
			cin >> address;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 7:
			cout << endl << "Enter Join Date" << endl;
			cin >> joinData;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 8:
			cout << endl << "Enter Email" << endl;
			cin >> email;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 9:
			cout << endl << "Enter Phone Number" << endl;
			cin >> phoneNumber;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 10:
			cout << endl << "Enter Password" << endl;
			cin >> password;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 11:
			cout << endl << "Enter College" << endl;
			cin >> college;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 12:
			cout << endl << "Enter Department" << endl;
			cin >> Department;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 13:
			cout << endl << "Enter Major" << endl;
			cin >> major;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 14:
			cout << endl << "Enter academic Rank" << endl;
			cin >> academicRank;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 15:
			cout << endl << "Enter salary" << endl;
			cin >> salary;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 16:
			cout << endl << "Enter office Hours" << endl;
			cin >> officeHours;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 17:
			cout << endl << "Enter Number Of Holidays" << endl;
			cin >> NumberOfHolidays;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		default:
			cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
			break;
		}

	}
}
void teachers::ViewMyCourses(arrayList<Course>& listC) {
	Course c1;
	if (MyCourses.size() > 0) {
		for (int i = 0; i < MyCourses.size(); i++) {
			long long loc1 = serchCourseByID(listC, MyCourses[i]);
			c1 = listC.opp(loc1);
			cout << "\n\033[90m==============[ \033[38;5;12mCourse Information\033[90m ]===============\033[0m\n";

			cout << left << "\033[90m||\033[0m" << setw(30) << "Course Code:\033[38;5;87m" << setw(27) << c1.getCourseCode() << "\033[0m" << "\033[90m || \033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Course Name:\033[38;5;87m" << setw(28) << c1.getCourseName() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Credit Hours:\033[38;5;87m" << setw(28) << c1.getCreditHours() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Department:\033[38;5;87m" << setw(28) << c1.getDepartment() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "College:\033[38;5;87m" << setw(28) << c1.getCollege() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Instructor Name:\033[38;5;87m" << setw(28) << c1.getInstructorName() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Semester Offered:\033[38;5;87m" << setw(28) << c1.getSemesterOffered() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Schedule:\033[38;5;87m" << setw(28) << c1.getSchedule() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Location:\033[38;5;87m" << setw(28) << c1.getLocation() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Capacity:\033[38;5;87m" << setw(28) << c1.getCapacity() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Enrolled Count:\033[38;5;87m" << setw(28) << c1.getEnrolledCount() << "\033[0m" << "\033[90m||\033[0m" << endl;

			cout << "\033[90m====================================================\033[0m\n";
			cout << endl << endl;
		}
	}
	else {
		cout << "\033[31mThe list is empty. There is no information about any course.\033[0m" << endl;
	}
}
void teachers::StudentsOfMyCourses(arrayList<Course>& listC, arrayList<students>& listS) {
	int counter = 0, choose;
	long long loc1;
	Course c1;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[90m ";
	cout << string(55, ' ') << "\033[1;33m* Welcome to the teacher account *\033[0m" << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[38;5;14m";
	cout << string(42, ' ') << "====================== [ My Courses ] ======================" << endl;
	cout << "\033[0m";
	cout << "\033[36m";
	cout << "\033[90m+--------+--------------------------+\033[0m" << endl;
	cout << "\033[90m|  \033[1;33mNont\033[90m  |     \033[1;33mCourse Name\033[0m          \033[90m|\033[0m" << endl;
	cout << "\033[90m+--------+--------------------------+\033[0m" << endl;

	for (int i = 0; i < MyCourses.size(); i++) {
		counter++;
		loc1 = serchCourseByID(listC, MyCourses[i]);
		c1 = listC.opp(loc1);

		cout << "\033[90m|\033[0m  "
			<< "\033[1;33m" << setw(0) << counter << "\033[0m"
			<< "    \033[90m |\033[0m  "
			<< "\033[36m" << setw(24) << left << c1.getCourseName() << "\033[0m"
			<< "\033[90m|\033[0m" << endl;
	}

	cout << "\033[90m+--------+--------------------------+\033[0m" << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m\n\n";
	cout << "\033[34mPlease choose an option: \033[0m";
	cin >> choose;
	if (choose > 0 && choose <= counter) {
		loc1 = serchCourseByID(listC, MyCourses[choose - 1]);
		c1 = listC.opp(loc1);
		c1.PrintAllStudentsInTheCourse(listS);
		cout << "\033[32mThe operation was successful..\033[0m" << endl;
	}
	else {
		system("cls");
		cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
	}
}
string teachers::getacademicRank()const {
	return academicRank;
}
double teachers::getsalary()const {
	return salary;
}
string teachers::getofficeHours()const {
	return officeHours;
}
int teachers::getNumberOfHolidays()const {
	return NumberOfHolidays;
}
void teachers::EditMyProfile(arrayList<teachers>& list, int id, teachers& t2) {
	int Choose;
	bool z = true;
	while (z) {
		cout << "\033[90m" << string(33, '-') << "\033[0m";
		cout << left << setw(41) << "\n\033[1;33m|====== Edit Lecturer Data ======|\033[0m";
		cout << endl;
		cout << "\033[90m" << string(33, '-') << "\033[0m" << endl;

		cout << left << setw(47) << "\033[90m|\033[38;5;14m1) Edit Name" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m2) Edit Gender" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m3) Edit Date of Birth" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m4) Edit Nationality" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m5) Edit Blood Type" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m6) Edit Address" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m7) Edit Join Date" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m8) Edit Email" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m9) Edit Phone Number" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m10) Edit Password" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m11) Edit College" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m12) Edit Department" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m13) Edit Major" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m14) Edit Academic Rank" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m15) Edit Salary" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m16) Edit Office Hours" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m17) Edit Number of Holidays" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m18) Exit Edit Menu" << "\033[90m|\033[0m\n";

		cout << "\033[90m" << string(33, '-') << "\033[0m" << endl << endl;

		cout << "\033[34mChoose an option: \033[0m";
		cin >> Choose;

		switch (Choose) {
		case 1:
			cout << endl << "Enter the full name" << endl;
			getline(cin, name);
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 2:
			cout << endl << "Enter gender" << endl;
			cin >> gender;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 3:
			cout << endl << "Enter Date of Birth" << endl;
			cin >> dateOfBirth;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 4:
			cout << endl << "Enter Nationality" << endl;
			cin >> nationality;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 5:
			cout << endl << "Enter Blood Type" << endl;
			cin >> bloodType;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 6:
			cout << endl << "Enter Address" << endl;
			cin >> address;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 7:
			cout << endl << "Enter Join Date" << endl;
			cin >> joinData;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 8:
			cout << endl << "Enter Email" << endl;
			cin >> email;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 9:
			cout << endl << "Enter Phone Number" << endl;
			cin >> phoneNumber;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 10:
			cout << endl << "Enter Password" << endl;
			cin >> password;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 11:
			cout << endl << "Enter College" << endl;
			cin >> college;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 12:
			cout << endl << "Enter Department" << endl;
			cin >> Department;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 13:
			cout << endl << "Enter Major" << endl;
			cin >> major;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 14:
			cout << endl << "Enter academic Rank" << endl;
			cin >> academicRank;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 15:
			cout << endl << "Enter salary" << endl;
			cin >> salary;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 16:
			cout << endl << "Enter office Hours" << endl;
			cin >> officeHours;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 17:
			cout << endl << "Enter  Number Of Holidays" << endl;
			cin >> NumberOfHolidays;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		case 18:
			z = false;
			cout << endl;
			cout << "\033[32mThe operation was successful..\033[0m" << endl;
			break;
		default:
			cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
			break;
		}
	}
	int loc = serchteacherByID(list, id);
	if (loc > -1) {
		teachers t1 = list.opp(loc);
		t2 = list.opp(loc);
		list.replaceAt(loc, t1);
		system("cls");
		cout << "\033[92mYour information has been updated successfully.!\033[0m\n";
	}
	else {
		system("cls");
		cout << "\033[31mAn error occurred. Please try again..\033[0m" << endl;
	}
}
void teachers::SubmitComplaint() {
	cin.ignore();
	Admin a;
	cout << "\n\033[1;33mEnter your complaint in English: ";
	string msg;
	getline(cin, msg);

	Complaint c = { "Teacher", this->ID, msg };
	a.setcomplaints(c);

	cout << "\033[38;5;10mComplaint submitted successfully!\033[0m" << endl;
}



Admin::Admin(string name, char gender, string dateOfBirth, string nationality, string bloodType, string address, string joinData, string email, string phoneNumber, string password, string college, string Department, string major, string academicRank, double salary, string officeHours, int NumberOfHolidays) :person(name, gender, dateOfBirth, nationality, bloodType, address, joinData, email, phoneNumber, password, college, Department, major) {
	this->academicRank = academicRank;
	this->salary = salary;
	this->officeHours = officeHours;
	this->NumberOfHolidays = NumberOfHolidays;
}
void Admin::Editteachers(arrayList<teachers>& teachersList, long long ID) {
	long long length, location;
	teachers s1;
	bool IDsearch;
	IDsearch = false;
	length = teachersList.getLength();
	for (int i = 0; i < length; i++) {
		s1 = teachersList.opp(i);
		if (s1.getID() == ID) {
			IDsearch = true;
			location = i;
			break;
		}
		else
			IDsearch = false;
	}
	if (IDsearch) {
		s1.DataEntryteachers();
		teachersList.replaceAt(location, s1);
	}
	else
		cout << "\033[31mThe number you entered does not exist or is incorrect. Please verify it.\033[0m" << endl;
}
void Admin::Deleteteachers(arrayList<teachers>& teachersList, long long ID) {
	long long length, location;
	teachers s1;
	bool IDsearch;
	IDsearch = false;
	length = teachersList.getLength();
	for (int i = 0; i < length; i++) {
		s1 = teachersList.opp(i);
		if (s1.getID() == ID) {
			IDsearch = true;
			location = i;
			break;
		}
		else
			IDsearch = false;
	}
	if (IDsearch) {
		teachersList.removeAT(location);
		system("cls");
		cout << "\033[38;5;10mThe operation was successful.....\033[0m" << endl;
	}
	else {
		system("cls");
		cout << "\033[31mYou have entered an incorrect ID. Please check it...\033[0m" << endl;
	}
}
void Admin::Searchteachers(arrayList<teachers>& teachersList, long long ID) {
	long long length, location;
	teachers s1;
	bool IDsearch;
	IDsearch = false;
	length = teachersList.getLength();
	for (int i = 0; i < length; i++) {
		s1 = teachersList.opp(i);
		if (s1.getID() == ID) {
			IDsearch = true;
			location = i;
			break;
		}
		else
			IDsearch = false;
	}
	if (IDsearch)
		cout << "\033[38;5;10mThe teachers you are looking for is here....\033[0m" << endl;
	else
		cout << "\033[31mThe teachers you are looking for does not exist.....\033[0m" << endl;
}
void Admin::PrintAllteachersInformation(arrayList<teachers>& teachersList) {
	long long length, location;
	teachers s1;
	bool IDsearch;
	length = teachersList.getLength();
	if (length > 0) {
		for (int i = 0; i < length; i++) {
			s1 = teachersList.opp(i);
			cout << "\n\033[90m==============[ \033[38;5;12mteachers Information\033[90m ]==============\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "Name:\033[38;5;87m" << setw(31) << s1.getName() << "\033[0m" << "\033[90m || \033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Email:\033[38;5;87m" << setw(31) << s1.getEmail() << "\033[0m" << "\033[90m || \033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Phone Number:\033[38;5;87m" << setw(31) << s1.getPhoneNumber() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Gender:\033[38;5;87m" << setw(31) << s1.getGender() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Nationality:\033[38;5;87m" << setw(31) << s1.getNationality() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Date of Birth:\033[38;5;87m" << setw(31) << s1.getDateOfBirth() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Blood Type:\033[38;5;87m" << setw(31) << s1.getBloodType() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Address:\033[38;5;87m" << setw(31) << s1.getAddress() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Join Date:\033[38;5;87m" << setw(31) << s1.getJoinDate() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "College:\033[38;5;87m" << setw(31) << s1.getCollege() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Department:\033[38;5;87m" << setw(31) << s1.getDepartment() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Major:\033[38;5;87m" << setw(31) << s1.getMajor() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Academic Rank:\033[38;5;87m" << s1.getacademicRank() << setw(17) << "%\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Salary:\033[38;5;87m" << setw(31) << s1.getsalary() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Office Hours:\033[38;5;87m" << setw(31) << s1.getofficeHours() << "\033[0m" << "\033[90m||\033[0m" << endl;
			cout << left << "\033[90m||\033[0m" << setw(30) << "Number Of Holidays:\033[38;5;87m" << setw(31) << s1.getNumberOfHolidays() << "\033[0m" << "\033[90m || \033[0m" << endl;
			cout << "\033[90m===================================================\033[0m\n";
			cout << endl << endl;
		}
		cout << "\033[38;5;10mThe operation was successful.....\033[0m" << endl;
	}
	else
		cout << "\033[31mThe list is empty. There is no information about any teachers.\033[0m" << endl;
}
void Admin::RegisterStudentinCourse(arrayList<students>& studentsList, long long ID, arrayList<Course>& listC, string courseid) {
	long long location = serchstudentByID(studentsList, ID);
	Course c1;
	if (location > -1) {
		if (listC.getLength() > 0) {
			StudentRegistrationListForaCourse(listC, courseid, c1);
			if (courseid != "NotExisting") {
				students s1 = studentsList.opp(location);
				if (s1.MakeSureTheCourseIsNotRegistered(courseid)) {
					s1.CourseRegistration(courseid);
					studentsList.replaceAt(location, s1);
					c1.AddStudentsInTheCourse(ID);
					long long locationc = serchCourseByID(listC, c1.getCourseCode());
					listC.replaceAt(locationc, c1);
					system("cls");
					cout << "\033[38;5;10mThe registration process was successful....\033[0m" << endl;
				}
				else {
					system("cls");
					cout << "\033[31mThis course is registered....\033[0m" << endl;
				}
			}
			else {
				system("cls");
				cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
			}
		}
		else {
			system("cls");
			cout << "\033[31mThe list is empty...\033[0m" << endl;
		}
	}
	else {
		system("cls");
		cout << "\033[31mYou have entered an incorrect ID. Please check it...\033[0m" << endl;
	}
}
void Admin::UnRegisterStudentinCourse(arrayList<students>& studentsList, long long ID, arrayList<Course>& listC, string courseid) {
	long long location = serchstudentByID(studentsList, ID);
	Course c1;
	if (location > -1) {
		students s1 = studentsList.opp(location);
		if (s1.getLengthSemestercourses() > 0) {
			StudentUnRegistrationListForaCourse(listC, courseid, c1, s1);
			if (courseid != "NotExisting") {
				if (!s1.MakeSureTheCourseIsNotRegistered(courseid)) {
					s1.UnregisterfromCourse(listC, studentsList, courseid, ID, s1);
				}
				else {
					system("cls");
					cout << "\033[31mThis course is Notregistered....\033[0m" << endl;
				}
			}
			else {
				system("cls");
				cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
			}
		}
		else {
			system("cls");
			cout << "\033[31mThe list is empty...\033[0m" << endl;
		}
	}
	else {
		system("cls");
		cout << "\033[31mYou have entered an incorrect ID. Please check it...\033[0m" << endl;
	}
}
void Admin::StudentRegistrationListForaCourse(arrayList<Course>& listC, string& courseid, Course& c1) {
	long long counter = 0, choose, loc1;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m=========================================================== [ Register in Course  ] ================================================================\033[0m\n";
	cout << string(36, ' ') << "\033[1;36m====================== [ the Courses existing ] ======================\033[0m" << endl;
	cout << "\033[0m";
	cout << "\033[36m";
	cout << "\033[90m+--------+--------------------------+\033[0m" << endl;
	cout << "\033[90m|  \033[1;33mNont\033[90m  |     \033[1;33mCourse Name\033[0m          \033[90m|\033[0m" << endl;
	cout << "\033[90m+--------+--------------------------+\033[0m" << endl;

	for (int i = 0; i < listC.getLength(); i++) {
		counter++;
		c1 = listC.opp(i);

		cout << "\033[90m|\033[0m  "
			<< "\033[1;33m" << setw(0) << counter << "\033[0m"
			<< "    \033[90m |\033[0m  "
			<< "\033[36m" << setw(24) << left << c1.getCourseName() << "\033[0m"
			<< "\033[90m|\033[0m" << endl;
	}

	cout << "\033[90m+--------+--------------------------+\033[0m" << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m\n\n";
	cout << "\033[34mPlease choose an option: \033[0m";
	cin >> choose;
	if (choose > 0 && choose <= counter) {
		c1 = listC.opp(choose - 1);
		courseid = c1.getCourseCode();
		system("cls");
	}
	else {
		courseid = "NotExisting";
		system("cls");
	}
}
void Admin::StudentUnRegistrationListForaCourse(arrayList<Course>& listC, string& courseid, Course& c1, students& s1) {

	long long counter = 0, choose, loc1;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m=========================================================== [ UnRegister in Course  ] ================================================================\033[0m\n";
	cout << string(36, ' ') << "\033[1;36m====================== [ the Courses Registered ] ======================\033[0m" << endl;
	cout << "\033[0m";
	cout << "\033[36m";
	cout << "\033[90m+--------+--------------------------+\033[0m" << endl;
	cout << "\033[90m|  \033[1;33mNont\033[90m  |     \033[1;33mCourse Name\033[0m          \033[90m|\033[0m" << endl;
	cout << "\033[90m+--------+--------------------------+\033[0m" << endl;

	for (int i = 0; i < s1.getLengthSemestercourses(); i++) {
		counter++;
		loc1 = serchCourseByID(listC, s1.getRegisteredCourse(i));
		if (loc1 > -1) {
			c1 = listC.opp(loc1);

			cout << "\033[90m|\033[0m  "
				<< "\033[1;33m" << setw(0) << counter << "\033[0m"
				<< "    \033[90m |\033[0m  "
				<< "\033[36m" << setw(24) << left << c1.getCourseName() << "\033[0m"
				<< "\033[90m|\033[0m" << endl;
		}
	}

	cout << "\033[90m+--------+--------------------------+\033[0m" << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m\n\n";
	cout << "\033[34mPlease choose an option: \033[0m";
	cin >> choose;
	if (choose > 0 && choose <= counter) {
		loc1 = serchCourseByID(listC, s1.getRegisteredCourse(choose - 1));
		c1 = listC.opp(loc1);
		courseid = c1.getCourseCode();
		system("cls");
	}
	else {
		courseid = "NotExisting";
		system("cls");
	}
}
void Admin::ShowStudentSCourses(arrayList<students>& studentsList, long long ID, arrayList<Course>& listC) {
	students s1;
	long long location = serchstudentByID(studentsList, ID);
	if (location > -1) {
		s1 = studentsList.opp(location);
		s1.ViewMyCourses(listC);
	}
	else {
		system("cls");
		cout << "\033[31mYou have entered an incorrect ID. Please check it...\033[0m" << endl;
	}
}
void Admin::ShowCourseSStudents(arrayList<Course>& listC, string& courseid, arrayList<students>& studentsList) {
	Course c1;
	long long location = serchCourseByID(listC, courseid);
	if (location > -1) {
		c1 = listC.opp(location);
		c1.PrintAllStudentsInTheCourse(studentsList);
	}
	else {
		system("cls");
		cout << "\033[31mYou have entered an incorrect ID. Please check it...\033[0m" << endl;
	}
}
void Admin::EnrollmentStatistics(arrayList<students>& studentsList, arrayList<teachers>& teachersList, arrayList<Course>& listC) {
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[90m " << string(58, ' ') << "\033[1;33m*Welcome Back to JUST System*\033[1;36m" << string(59, ' ') << "\033[90m\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[1;36m\033[1;36m============================================================ [ Enrollment Statistics ] =============================================================" << endl;
	cout << endl << endl;
	cout << string(46, ' ') << "\033[90m" << string(55, '=') << endl;
	cout << string(46, ' ') << "\033[90m||============ [" << "\033[1;33m Enrollment Statistics " << "\033[90m] ============||" << endl;
	cout << string(46, ' ') << "\033[90m" << string(55, '=') << endl;
	cout << string(46, ' ') << "\033[90m|" << left << setw(51) << "\033[1;33m     1)Total Students : \033[1;36m" << studentsList.getLength() << string(13, ' ') << "\033[90m|" << endl;
	cout << string(46, ' ') << "\033[90m|" << left << setw(51) << "\033[1;33m     2)Total Teachers : \033[1;36m" << teachersList.getLength() << string(13, ' ') << "\033[90m|" << endl;
	cout << string(46, ' ') << "\033[90m|" << left << setw(51) << "\033[1;33m     3)Total Courses  : \033[1;36m" << listC.getLength() << string(13, ' ') << "\033[90m|" << endl;
	cout << string(46, ' ') << "\033[90m|" << left << setw(51) << "\033[1;33m     4)Total Registrations : \033[1;36m" << TotalRegistrations(listC) << string(13, ' ') << "\033[90m|" << endl;
	cout << string(46, ' ') << "\033[90m" << string(55, '=') << endl;
	cout << "\033[0m";
}
void Admin::StudentTranscript(arrayList<students>& studentsList, long long ID, arrayList<Course>& listC) {
	long long location = serchstudentByID(studentsList, ID);
	if (location > -1) {
		students s1 = studentsList.opp(location);
		s1.PrintRegisteredCourses(listC);
	}
	else {
		system("cls");
		cout << "\033[31mYou have entered an incorrect ID. Please check it...\033[0m" << endl;
	}
}
void Admin::viewComplaints() {
	vector<Complaint> Complaints = getcomplaint();

	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m " << string(58, ' ')
		<< "\033[1;33m* Welcome Back to JUST System *\033[1;36m"
		<< string(59, ' ') << "\033[90m\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";

	cout << "\033[1;36m============================================================== [ Complaints Reports ] ==============================================================\033[0m\n\n";

	if (Complaints.empty()) {
		cout << string(46, ' ') << "\033[31mNo complaints found...\033[0m\n";
	}
	else {
		cout << string(46, ' ') << "\033[90m" << string(70, '=') << "\033[0m\n";
		cout << string(46, ' ') << "\033[90m|| " << "\033[1;33m#   Sender Type   |   Sender ID   |   Message"
			<< string(20, ' ') << "\033[90m||\033[0m\n";
		cout << string(46, ' ') << "\033[90m" << string(70, '=') << "\033[0m\n";

		for (int i = 0; i < Complaints.size(); i++) {
			cout << string(46, ' ') << "\033[90m|| \033[1;36m" << setw(3) << i + 1
				<< " \033[0m\033[90m|\033[0m " << setw(12) << Complaints[i].senderType
				<< " \033[90m|\033[0m " << setw(11) << Complaints[i].senderID
				<< " \033[90m|\033[0m " << setw(25) << Complaints[i].message.substr(0, 25)
				<< "...\033[90m ||\033[0m\n";
		}

		cout << string(46, ' ') << "\033[90m" << string(70, '=') << "\033[0m\n";
	}
	cout << "\033[0m";

}
void Admin::setcomplaints(Complaint complaints) {
	Complaints.push_back(complaints);
}
vector<Complaint>& Admin::getcomplaint() {
	return Complaints;
}
Admin::Admin() : person("No Name", 'M', "2000-01-01", "Unknown", "O+", "Unknown", "2000-01-01",
	"unknown@email.com", "0000000000", "default", "Unknown", "Unknown", "Unknown")
{
	academicRank = "None";
	salary = 0.0;
	officeHours = "N/A";
	NumberOfHolidays = 0;
}
void Admin::addcourse(arrayList<Course>& list) {
	string courseCode;        // رمز المادة (مثلاً: CS101)
	string courseName;        // اسم المادة (مثلاً: Introduction to Programming)
	int creditHours;          // عدد الساعات المعتمدة
	string department;        // القسم المسؤول عن المادة
	string college;           // الكلية (لو عندك أكثر من كلية بالنظام)
	string instructorName;    // اسم المدرّس المسؤول
	string semesterOffered;   // الفصل المطروحة فيه (مثلاً: Fall 2025)
	string schedule;          // جدول المادة (مثلاً: Sun-Tue 10:00-11:30)
	string location;          // مكان المحاضرة (مثلاً: Room 205)
	int capacity;             // عدد الطلاب المسموح تسجيلهم
	int enrolledCount;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mJUST System - Course Creation\033[1;36m"
		<< string(56, ' ') << "\033[90m ||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m                             ================================= [ Create a New Course ] ======================================\033[0m\n";

	cout << "\033[90m|\033[1;33mEnter Course Code:\033[0m ";
	getline(cin >> ws, courseCode);

	cout << "\033[90m|\033[1;33mEnter Course Name:\033[0m ";
	getline(cin, courseName);

	cout << "\033[90m|\033[1;33mEnter Credit Hours:\033[0m ";
	cin >> creditHours;
	cin.ignore();

	cout << "\033[90m|\033[1;33mEnter Department:\033[0m ";
	getline(cin, department);

	cout << "\033[90m|\033[1;33mEnter College:\033[0m ";
	getline(cin, college);

	cout << "\033[90m|\033[1;33mEnter Instructor Name:\033[0m ";
	getline(cin, instructorName);

	cout << "\033[90m|\033[1;33mEnter Semester Offered:\033[0m ";
	getline(cin, semesterOffered);

	cout << "\033[90m|\033[1;33mEnter Schedule:\033[0m ";
	getline(cin, schedule);

	cout << "\033[90m|\033[1;33mEnter Location:\033[0m ";
	getline(cin, location);

	cout << "\033[90m|\033[1;33mEnter Capacity:\033[0m ";
	cin >> capacity;

	cout << "\033[90m|\033[1;33mEnter Enrolled Count:\033[0m ";
	cin >> enrolledCount;

	cout << endl;
	Course course(courseCode, courseName, creditHours, department, college, instructorName, semesterOffered, schedule, location, capacity, enrolledCount);
	list.insertEnd(course);
	system("cls");
	cout << "\033[92mCourse Created Successfully!\033[0m\n";
	course = list.opp(list.getLength() - 1);
	cout << "\033[1;33mNew course ID number: " << course.getCourseCode() << "\n";
}
void Admin::deletcourse(arrayList<Course>& list, string coursecode) {
	long long length, location;
	Course c1;
	bool IDsearch;
	IDsearch = false;
	length = list.getLength();
	for (int i = 0; i < length; i++) {
		c1 = list.opp(i);
		if (c1.getCourseCode() == coursecode) {
			IDsearch = true;
			location = i;
			break;
		}
		else
			IDsearch = false;
	}
	if (IDsearch) {
		list.removeAT(location);
		system("cls");
		cout << "\033[38;5;10mThe operation was successful.....\033[0m" << endl;
	}
	else {
		system("cls");
		cout << "\033[31mYou have entered an incorrect ID. Please check it...\033[0m" << endl;
	}
}
void Admin::PrintAllCourseInformation(arrayList<Course>& list) {
	Course c1;
	long long length, location;
	bool IDsearch;
	length = list.getLength();
	if (length > 0) {
		for (int i = 0; i < length; i++) {
			c1 = list.opp(i);
			cout << "\n\033[90m==============[ \033[1;33mCourse Information\033[90m ]==============\033[0m\n";

			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCourse Code:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getCourseCode() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCourse Name:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getCourseName() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCredit Hours:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getCreditHours() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mDepartment:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getDepartment() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCollege:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getCollege() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mInstructor Name:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getInstructorName() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mSemester Offered:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getSemesterOffered() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mSchedule:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getSchedule() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mLocation:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getLocation() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCapacity:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getCapacity() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mEnrolled Count:\033[0m" << "\033[38;5;14m" << setw(29) << c1.getEnrolledCount() << "\033[0m\033[90m||\033[0m\n";

			cout << "\033[90m===================================================\033[0m\n\n";

		}
		cout << "\033[38;5;10mThe operation was successful.....\033[0m" << endl;
	}
	else {
		system("cls");
		cout << "\033[31mThe list is empty. There is no information about any course.\033[0m" << endl;
	}

}
void Admin::addteachers(arrayList<teachers>& list) {
	int ID;
	string name, email, phoneNumber, password;
	char gender;
	string nationality;
	string dateOfBirth;
	string bloodType;
	string address, joinData;
	string college, Department;
	string major;
	string academicRank;
	double salary;
	string officeHours;
	int NumberOfHolidays;
	cout << "Enter ID: ";
	cin >> ID;
	cin.ignore();

	cout << "Enter name: ";
	getline(cin, name);

	cout << "Enter email: ";
	getline(cin, email);

	cout << "Enter phone number: ";
	getline(cin, phoneNumber);

	cout << "Enter password: ";
	getline(cin, password);

	cout << "Enter gender (M/F): ";
	cin >> gender;
	cin.ignore();

	cout << "Enter nationality: ";
	getline(cin, nationality);

	cout << "Enter date of birth: ";
	getline(cin, dateOfBirth);

	cout << "Enter blood type: ";
	getline(cin, bloodType);

	cout << "Enter address: ";
	getline(cin, address);

	cout << "Enter join date: ";
	getline(cin, joinData);

	cout << "Enter college: ";
	getline(cin, college);

	cout << "Enter department: ";
	getline(cin, Department);

	cout << "Enter major: ";
	getline(cin, major);

	cout << "Enter academic rank: ";
	getline(cin, academicRank);

	cout << "Enter salary: ";
	cin >> salary;
	cin.ignore();

	cout << "Enter office hours: ";
	getline(cin, officeHours);

	cout << "Enter number of holidays: ";
	cin >> NumberOfHolidays;
	cin.ignore();
	teachers teacher(name, gender, dateOfBirth, nationality, bloodType, address, joinData, email, phoneNumber, password, college, Department, major, academicRank, salary, officeHours, NumberOfHolidays);
	list.insertEnd(teacher);
}
void Admin::AddStudent(arrayList<students>& list) {
	string name, email, phoneNumber, password;
	char gender;
	string nationality;
	string dateOfBirth;
	string bloodType;
	string address, joinData;
	string college, Department;
	string major;
	float TawjihiAverage;
	double semesterGPA = 0.0, GPA = 0.0;
	string studyLevel, planVersion, statos;
	int completedHours = 0;
	int totalHours = 132;

	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m====================================================== [ Create a New Student Account ] ============================================================\033[0m\n";

	cout << "\033[90m|\033[1;33mEnter Name:\033[0m ";
	cin >> name;

	cout << "\033[90m|\033[1;33mEnter Gender (M/F):\033[0m ";
	cin >> gender;

	cout << "\033[90m|\033[1;33mEnter Date of Birth (YYYY-MM-DD):\033[0m ";
	cin >> dateOfBirth;

	cout << "\033[90m|\033[1;33mEnter Nationality:\033[0m ";
	cin >> nationality;

	cout << "\033[90m|\033[1;33mEnter Blood Type:\033[0m ";
	cin >> bloodType;

	cout << "\033[90m|\033[1;33mEnter Address:\033[0m ";
	cin.ignore();
	getline(cin, address);

	cout << "\033[90m|\033[1;33mEnter Join Date (YYYY-MM-DD):\033[0m ";
	getline(cin, joinData);

	cout << "\033[90m|\033[1;33mEnter Email:\033[0m ";
	cin >> email;

	cout << "\033[90m|\033[1;33mEnter Phone Number:\033[0m ";
	cin >> phoneNumber;

	cout << "\033[90m|\033[1;33mCreate a Password:\033[0m ";
	cin >> password;

	cout << "\033[90m|\033[1;33mEnter College:\033[0m ";
	cin.ignore();
	getline(cin, college);

	cout << "\033[90m|\033[1;33mEnter Department:\033[0m ";
	getline(cin, Department);

	cout << "\033[90m|\033[1;33mEnter Major:\033[0m ";
	getline(cin, major);

	cout << "\033[90m|\033[1;33mEnter Tawjihi Average:\033[0m ";
	cin >> TawjihiAverage;

	cout << "\033[90m|\033[1;33mEnter Plan Version:\033[0m ";
	getline(cin, planVersion);

	cout << "\033[90m|\033[1;33mEnter Status (e.g. Active):\033[0m ";
	getline(cin, statos);

	cout << "\033[90m|\033[1;33mEnter Total Hours:\033[0m ";
	cin >> totalHours;

	cout << endl;
	students studant(name, gender, dateOfBirth, nationality, bloodType, address, joinData, email, phoneNumber, password, college, Department, major, TawjihiAverage, semesterGPA, GPA, studyLevel, planVersion, statos, completedHours, totalHours);
	list.insertEnd(studant);
	system("cls");
	cout << "\033[92mAccount Created Successfully!\033[0m\n";
	studant = list.opp(list.getLength() - 1);
	cout << "\033[1;33mNew account ID number: " << studant.getID() << "\n";
	cout << "\033[1;33mNew account password: " << studant.getPassword() << endl;
}
void Admin::EditStudent(arrayList<students>& studentsList, long long ID) {
	long long length, location;
	students s1;
	bool IDsearch;
	IDsearch = false;
	length = studentsList.getLength();
	for (int i = 0; i < length; i++) {
		s1 = studentsList.opp(i);
		if (s1.getID() == ID) {
			IDsearch = true;
			location = i;
			break;
		}
		else
			IDsearch = false;
	}
	if (IDsearch) {
		s1.DataEntry();
		studentsList.replaceAt(location, s1);
	}
	else {
		system("cls");
		cout << "\033[31mThe number you entered does not exist or is incorrect. Please verify it.\033[0m" << endl;
	}
}
void Admin::DeleteStudent(arrayList<students>& studentsList, long long ID) {
	long long length, location;
	students s1;
	bool IDsearch;
	IDsearch = false;
	length = studentsList.getLength();
	for (int i = 0; i < length; i++) {
		s1 = studentsList.opp(i);
		if (s1.getID() == ID) {
			IDsearch = true;
			location = i;
			break;
		}
		else
			IDsearch = false;
	}
	if (IDsearch) {
		studentsList.removeAT(location);
		system("cls");
		cout << "\033[38;5;10mThe operation was successful.....\033[0m" << endl;
	}
	else {
		system("cls");
		cout << "\033[31mYou have entered an incorrect ID. Please check it...\033[0m" << endl;
	}
}
void Admin::SearchStudent(arrayList<students>& studentsList, long long ID) {
	long long length, location;
	students s1;
	bool IDsearch;
	IDsearch = false;
	length = studentsList.getLength();
	for (int i = 0; i < length; i++) {
		s1 = studentsList.opp(i);
		if (s1.getID() == ID) {
			IDsearch = true;
			location = i;
			break;
		}
		else
			IDsearch = false;
	}
	if (IDsearch) {
		system("cls");
		cout << "\033[38;5;10mThe student you are looking for is here....\033[0m" << endl;
	}
	else {
		system("cls");
		cout << "\033[31mThe student you are looking for does not exist.....\033[0m" << endl;
	}
}
void Admin::PrintAllStudentInformation(arrayList<students>& studentsList) {
	long long length, location;
	students s1;
	bool IDsearch;
	length = studentsList.getLength();
	if (length > 0) {
		for (int i = 0; i < length; i++) {
			s1 = studentsList.opp(i);
			cout << "\n\033[90m==============[ \033[1;33mStudent Information\033[90m ]==============\033[0m\n";

			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mName:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getName() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mEmail:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getEmail() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mPhone Number:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getPhoneNumber() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mGender:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getGender() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mNationality:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getNationality() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mDate of Birth:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getDateOfBirth() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mBlood Type:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getBloodType() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mAddress:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getAddress() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mJoin Date:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getJoinDate() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCollege:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getCollege() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mDepartment:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getDepartment() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mMajor:\033[0m" << "\033[38;5;14m" << setw(29) << getMajor() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mTawjihi Average:\033[0m" << "\033[38;5;14m" << setw(29) << (to_string(s1.getTawjihiAverage()) + "%") << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mPlan Version:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getPlanVersion() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mSemester GPA:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getSemesterGPA() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mOverall GPA:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getOverallGPA() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mStudy Level:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getStudyLevel() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mStatus:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getStatus() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mCompleted Hours:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getCompletedHours() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mTotal Hours:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getTotalHours() << "\033[0m\033[90m||\033[0m\n";
			cout << left << "\033[90m||\033[0m" << setw(30) << "\033[1;33mStudent ID:\033[0m" << "\033[38;5;14m" << setw(29) << s1.getID() << "\033[0m\033[90m||\033[0m\n";

			cout << "\033[90m===================================================\033[0m\n\n";

		}
		cout << "\033[38;5;10mThe operation was successful.....\033[0m" << endl;
	}
	else {
		system("cls");
		cout << "\033[31mThe list is empty. There is no information about any student.\033[0m" << endl;
	}
}
void Admin::editcourse(arrayList<Course>& list, string coursecode) {
	long long length, location;
	Course c1;
	bool IDsearch;
	IDsearch = false;
	length = list.getLength();
	for (int i = 0; i < length; i++) {
		c1 = list.opp(i);
		if (c1.getCourseCode() == coursecode) {
			IDsearch = true;
			location = i;
			break;
		}
		else
			IDsearch = false;
	}
	if (IDsearch) {
		c1.DataEntryCourse();
		list.replaceAt(location, c1);
		system("cls");
	}
	else {
		system("cls");
		cout << "\033[31mThe number you entered does not exist or is incorrect. Please verify it.\033[0m" << endl;
	}
}
void Admin::SaveToFile(ofstream& out) const {
	// حفظ بيانات البيرسون الأساسية
	out << ID << "," << name << "," << email << "," << phoneNumber << "," << password << ","
		<< gender << "," << nationality << "," << dateOfBirth << "," << bloodType << ","
		<< address << "," << joinData << "," << college << "," << Department << ","
		<< major << ",";

	// حفظ بيانات الأدمن الإضافية
	out << academicRank << "," << salary << "," << officeHours << "," << NumberOfHolidays << ",";

	// حفظ الشكاوى
	out << Complaints.size();
	for (const auto& complaint : Complaints) {
		out << "," << complaint.senderType << "," << complaint.senderID << "," << complaint.message;
	}
	out << "\n";
}
bool Admin::LoadFromFileLine(const string& line) {
	stringstream ss(line);
	string temp;

	try {
		// تحميل بيانات البيرسون الأساسية
		getline(ss, temp, ','); ID = stoi(temp);
		getline(ss, name, ',');
		getline(ss, email, ',');
		getline(ss, phoneNumber, ',');
		getline(ss, password, ',');
		getline(ss, temp, ','); gender = temp[0];
		getline(ss, nationality, ',');
		getline(ss, dateOfBirth, ',');
		getline(ss, bloodType, ',');
		getline(ss, address, ',');
		getline(ss, joinData, ',');
		getline(ss, college, ',');
		getline(ss, Department, ',');
		getline(ss, major, ',');

		// تحميل بيانات الأدمن الإضافية
		getline(ss, academicRank, ',');
		getline(ss, temp, ','); salary = stod(temp);
		getline(ss, officeHours, ',');
		getline(ss, temp, ','); NumberOfHolidays = stoi(temp);

		// تحميل الشكاوى
		getline(ss, temp, ',');
		int complaintsCount = stoi(temp);
		Complaints.clear();

		for (int i = 0; i < complaintsCount; i++) {
			Complaint c;
			getline(ss, c.senderType, ',');
			getline(ss, temp, ','); c.senderID = stoi(temp);
			getline(ss, c.message, ',');
			Complaints.push_back(c);
		}
	}
	catch (const exception& e) {
		cerr << "Error parsing admin data: " << e.what() << endl;
		return false;
	}
	return true;
}
// دوال مساعدة للشكاوى
void Admin::addComplaint(const Complaint& complaint) {
	Complaints.push_back(complaint);
}
void Admin::viewComplaints() const {
	if (Complaints.empty()) {
		cout << "No complaints found." << endl;
		return;
	}

	cout << "\n--- Complaints ---\n";
	for (size_t i = 0; i < Complaints.size(); i++) {
		cout << i + 1 << ". [" << Complaints[i].senderType
			<< " ID: " << Complaints[i].senderID << "] - "
			<< Complaints[i].message << "\n";
	}
}
vector<Complaint> Admin::getComplaints() const {
	return Complaints;
}
void Admin::Clear() {
	Complaints.clear();
}



Course::Course() {
	courseCode = "UNKNOWN";
	courseName = "Untitled Course";
	creditHours = 0;
	department = "Undefined";
	college = "Undefined";
	instructorName = "TBD";
	semesterOffered = "TBD";
	schedule = "TBD";
	location = "TBD";
	capacity = 0;
	enrolledCount = 0;
}
Course::Course(string courseCode, string courseName, int creditHours, string department, string college, string instructorName, string semesterOffered, string schedule, string location, int capacity, int enrolledCount) {
	this->courseCode = courseCode;
	this->courseName = courseName;
	this->creditHours = creditHours;
	this->department = department;
	this->college = college;
	this->instructorName = instructorName;
	this->semesterOffered = semesterOffered;
	this->schedule = schedule;
	this->location = location;
	this->capacity = capacity;
	this->enrolledCount = enrolledCount;
}
void Course::SaveToFile(ofstream& out) const {
	out << courseCode << ","
		<< courseName << ","
		<< creditHours << ","
		<< department << ","
		<< college << ","
		<< instructorName << ","
		<< semesterOffered << ","
		<< schedule << ","
		<< location << ","
		<< capacity << ","
		<< enrolledCount << ",";

	// حفظ قائمة الطلاب المسجلين (بدون الدرجات)
	out << StudentsInTheCourse.size();
	for (int id : StudentsInTheCourse) {
		out << "," << id;
	}
	out << "\n";
}
bool Course::LoadFromFileLine(const string& line) {
	stringstream ss(line);
	string temp;

	try {
		getline(ss, courseCode, ',');
		getline(ss, courseName, ',');
		getline(ss, temp, ','); creditHours = stoi(temp);
		getline(ss, department, ',');
		getline(ss, college, ',');
		getline(ss, instructorName, ',');
		getline(ss, semesterOffered, ',');
		getline(ss, schedule, ',');
		getline(ss, location, ',');
		getline(ss, temp, ','); capacity = stoi(temp);
		getline(ss, temp, ','); enrolledCount = stoi(temp);

		// تحميل قائمة الطلاب المسجلين
		getline(ss, temp, ',');
		int studentCount = stoi(temp);
		StudentsInTheCourse.clear();
		for (int i = 0; i < studentCount; i++) {
			getline(ss, temp, ',');
			StudentsInTheCourse.push_back(stoi(temp));
		}
	}
	catch (...) {
		return false;
	}
	return true;
}string Course::getCourseCode() const {
	return courseCode;
}
string Course::getCourseName() const {
	return courseName;
}
int Course::getCreditHours() const {
	return creditHours;
}
string Course::getDepartment() const {
	return department;
}
string Course::getCollege() const {
	return college;
}
string Course::getInstructorName() const {
	return instructorName;
}
string Course::getSemesterOffered() const {
	return semesterOffered;
}
string Course::getSchedule() const {
	return schedule;
}
string Course::getLocation() const {
	return location;
}
int Course::getCapacity() const {
	return capacity;
}
int Course::getEnrolledCount() const {
	return enrolledCount;
}
void Course::setgread() {
	Course c1;
	int choose;
	double editgrate;
	bool stope = true;
	while (stope) {
		cout << "Grades Summary:\n";
		cout << "1-first: \n";
		cout << "2-seconde: \n";
		cout << "3-mid: \n";
		cout << "4-final: \n";
		cout << "5-Exit \n";

		cin >> choose;
		switch (choose) {
		case 1:
			cin >> editgrate;
			c1.cgread.setfirst(editgrate);
			break;
		case 2:
			cin >> editgrate;
			c1.cgread.setseconde(editgrate);
			break;
		case 3:
			cin >> editgrate;
			c1.cgread.setmid(editgrate);
			break;
		case 4:
			cin >> editgrate;
			c1.cgread.setfinal(editgrate);
			break;
		case 5:
			stope = false;
			break;
		}
	}
}
gread Course::getgread() const {
	return cgread;
}
void Course::setCourseCode(string CourseCode) {
	courseCode = CourseCode;
}
void Course::setCourseName(string CourseName) {
	courseName = CourseName;
}
void Course::setCreditHours(int CreditHours) {
	creditHours = CreditHours;
}
void Course::setDepartment(string Department) {
	department = Department;
}
void Course::setCollege(string College) {
	college = College;
}
void Course::setInstructorName(string InstructorName) {
	instructorName = InstructorName;
}
void Course::setSemesterOffered(string SemesterOffered) {
	semesterOffered = SemesterOffered;
}
void Course::setSchedule(string Schedule) {
	this->schedule = Schedule;
}
void Course::setLocation(string Location) {
	location = Location;
}
void Course::setCapacity(int Capacity) {
	capacity = Capacity;
}
void Course::setEnrolledCount(int EnrolledCount) {
	enrolledCount = EnrolledCount;
}
void Course::AddStudentsInTheCourse(int ID) {
	StudentsInTheCourse.push_back(ID);
}
void Course::StudentRemovedFromThisCourse(int ID, students& s1) {
	for (int i = 0; i < StudentsInTheCourse.size(); i++) {
		if (ID == StudentsInTheCourse[i]) {
			StudentsInTheCourse.erase(StudentsInTheCourse.begin() + i);
			break;
		}
	}
}
void Course::PrintAllStudentsInTheCourse(arrayList<students>& listS) {
	students s1;
	bool found = false;
	long long loc1;
	if (StudentsInTheCourse.size() > 0) {
		system("cls");
		cout << "\033[90m+---------+------------------------+-----------------------------+\033[0m\n";

		cout << "\033[90m|\033[0m" << left << setw(15) << "\033[1;33m  ID   " << setw(25) << "\033[0m\033[90m | \033[0m" << setw(19) << "\033[1;33mName" << setw(27) << " \033[0m\033[90m | \033[0m" << setw(23) << "\033[1;33mEmail" << " \033[0m\033[90m | \033[0m\n";
		cout << "\033[90m+---------+------------------------+-----------------------------+\033[0m\n";
		for (int i = 0; i < StudentsInTheCourse.size(); i++) {
			loc1 = serchstudentByID(listS, StudentsInTheCourse[i]);
			if (loc1 > -1) {
				found = true;
				s1 = listS.opp(loc1);
				cout << "\033[90m|\033[0m" << "\033[1;33m  " << setw(6) << " " << "\033[0m\033[90m | \033[0m" << setw(7) << "\033[1; 33m" << setw(21) << " " << " \033[0m" << setw(14) << "\033[90m | \033[0m" << setw(3) << "\033[1; 33m" << setw(24) << " " << setw(0) << " \033[0m" << "\033[90m | \033[0m\n";
				cout << "\033[90m|\033[0m" << "\033[38;5;14m  " << setw(6) << s1.getID() << "\033[0m\033[90m | \033[38;5;14m" << setw(7) << "\033[38;5;14m" << setw(21) << s1.getName() << " \033[0m" << setw(14) << "\033[90m | \033[0m" << setw(3) << "\033[38;5;14m" << setw(24) << s1.getEmail() << setw(0) << " \033[0m" << "\033[90m | \033[0m\n";
			}
		}
		cout << "\033[90m+---------+------------------------+-----------------------------+\033[0m\n";

	}
	else if (!found) {
		system("cls");
		cout << "\033[31mThere are no students registered in your course..\033[0m" << endl;
	}
}
void Course::DataEntryCourse() {
	bool stope1 = true;
	int choose;
	while (stope1) {
		cout << "\033[90m" << string(33, '-') << "\033[0m";
		cout << left << setw(41) << "\n\033[1;33m|====== Edit Course Data ======|\033[0m";
		cout << endl;
		cout << "\033[90m" << string(33, '-') << "\033[0m" << endl;

		cout << left << setw(47) << "\033[90m|\033[38;5;14m1) Edit Course Code" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m2) Edit Course Name" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m3) Edit Credit Hours" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m4) Edit Department" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m5) Edit College" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m6) Edit Instructor Name" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m7) Edit Semester Offered" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m8) Edit Schedule" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m9) Edit Location" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m10) Edit Capacity" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m11) Edit Enrolled Count" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m12) Edit Grade Data" << "\033[90m|\033[0m\n";
		cout << left << setw(47) << "\033[90m|\033[38;5;14m13) Exit Edit Menu" << "\033[90m|\033[0m\n";

		cout << "\033[90m" << string(33, '-') << "\033[0m" << endl << endl;
		cout << "\033[34mChoose an option: \033[0m";

		cin >> choose;
		cin.ignore();
		switch (choose) {
		case 1:
			cout << "\nEnter new Course Code: ";
			getline(cin, courseCode);
			setCourseCode(courseCode);
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m\n";
			break;
		case 2:
			cout << "\nEnter new Course Name: ";
			getline(cin, courseName);
			setCourseName(courseName);
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m\n";
			break;
		case 3:
			cout << "\nEnter new Credit Hours: ";
			cin >> creditHours;
			setCreditHours(creditHours);
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m\n";
			break;
		case 4:
			cout << "\nEnter new Department: ";
			cin.ignore();
			getline(cin, department);
			setDepartment(department);
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m\n";
			break;
		case 5:
			cout << "\nEnter new College: ";
			cin.ignore();
			getline(cin, college);
			setCollege(college);
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m\n";
			break;
		case 6:
			cout << "\nEnter new Instructor Name: ";
			cin.ignore();
			getline(cin, instructorName);
			setInstructorName(instructorName);
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m\n";
			break;
		case 7:
			cout << "\nEnter new Semester Offered: ";
			cin.ignore();
			getline(cin, semesterOffered);
			setSemesterOffered(semesterOffered);
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m\n";
			break;
		case 8:
			cout << "\nEnter new Schedule: ";
			cin.ignore();
			getline(cin, schedule);
			setSchedule(schedule);
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m\n";
			break;
		case 9:
			cout << "\nEnter new Location: ";
			cin.ignore();
			getline(cin, location);
			setLocation(location);
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m\n";
			break;
		case 10:
			cout << "\nEnter new Capacity: ";
			cin >> capacity;
			setCapacity(capacity);
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m\n";
			break;
		case 11:
			cout << "\nEnter new Enrolled Count: ";
			cin >> enrolledCount;
			setEnrolledCount(enrolledCount);
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m\n";
			break;
		case 12:
			// لسا بدها شغل
			setgread();
			system("cls");
			cout << "\033[32mThe operation was successful..\033[0m\n";
			break;
		case 13:
			stope1 = false;
			system("cls");
			cout << "\033[32mExiting course edit menu...\033[0m\n";
			break;
		default:
			system("cls");
			cout << "\033[31mYou have entered an incorrect number. Please try again...\033[0m\n";
			break;
		}


	}
}
vector<int> Course::getStudentsInTheCourse() {
	return StudentsInTheCourse;
}
int Course::getStudentsInTheCourseSize()const {
	return StudentsInTheCourse.size();
}
bool Course::isregist(int id) {
	for (int i = 0; i < StudentsInTheCourse.size(); i++) {
		if (StudentsInTheCourse[i] == id)
			return true;
	}
	return false;
}




gread::gread() {
	first = seconde = mid = final = typeCourse = 0;
}
void gread::setfirst(double first) {
	this->first = first;
}
void gread::setseconde(double seconde) {
	this->seconde = seconde;
}
void gread::setmid(double mid) {
	this->mid = mid;
}
void gread::setfinal(double final) {
	this->final = final;
}
void gread::setTypeCourse(int Case) {
	typeCourse = Case;
}
double gread::getfirst()const {
	return first;
}
double gread::getseconde()const {
	return seconde;
}
double gread::getmid()const {
	return mid;
}
double gread::getfinal()const {
	return final;
}
double gread::gettotal()const {
	return first + seconde + mid + final;
}
int gread::getTypeCourse()const {
	return typeCourse;
}
void gread::setGrades(double nfirst, double nseconde, double nmid, double nfinal) {
	first = nfirst;
	seconde = nseconde;
	mid = nmid;
	final = nfinal;
}
string gread::getcourseSymbol() {
	long long sum = gettotal();
	if (sum >= 95) {
		symbol = "A+";
		return symbol;
	}
	else if (sum < 95 && sum >= 85) {
		symbol = "A";
		return symbol;
	}
	else if (sum < 85 && sum >= 80) {
		symbol = "A-";
		return symbol;
	}
	else if (sum < 80 && sum >= 77) {
		symbol = "B+";
		return symbol;
	}
	else if (sum < 77 && sum >= 73) {
		symbol = "B";
		return symbol;
	}
	else if (sum < 73 && sum >= 70) {
		symbol = "B-";
		return symbol;
	}
	else if (sum < 70 && sum >= 67) {
		symbol = "C+";
		return symbol;
	}
	else if (sum < 67 && sum >= 63) {
		symbol = "C";
		return symbol;
	}
	else if (sum < 63 && sum >= 60) {
		symbol = "C-";
		return symbol;
	}
	else if (sum < 60 && sum >= 57) {
		symbol = "D+";
		return symbol;
	}
	else if (sum < 57 && sum >= 53) {
		symbol = "D";
		return symbol;
	}
	else if (sum < 53 && sum >= 50) {
		symbol = "D-";
		return symbol;
	}
	else {
		symbol = "F";
		return symbol;
	}
}




void loginScreen(long long& id, string& password) {
	string password1;
	long long ID;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome Back to JUST System\033[1;36m" << string(59, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[1;36m============================================================ [ Login to your Account ] =============================================================" << endl;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> ID : \033[0m";

	cin >> ID;

	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl << endl;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> Password : \033[0m";

	cin >> password1;

	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	password = password1;
	id = ID;
}
void RegisterStudentInCourseUI(string& courseid) {
	string courseid1;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m=========================================================== [ Register in Course  ] ================================================================\033[0m\n";
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> courseid : \033[0m";
	cin >> courseid1;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	courseid = courseid1;
}
void EditACourseUI(string& courseid) {
	string courseid1;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m=========================================================== [ Edit in Course  ] ================================================================\033[0m\n";
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> courseid : \033[0m";
	cin >> courseid1;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	courseid = courseid1;
}
void DeleteAspecificCourseUI(string& courseid) {
	string courseid1;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m=========================================================== [ Delete in Course  ] ================================================================\033[0m\n";
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> courseid : \033[0m";
	cin >> courseid1;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	courseid = courseid1;
}
void EnterAspecificStudentsID(int& id) {
	int ID;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m=========================================================== [ Edit Student Data  ] ================================================================\033[0m\n";
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> ID : \033[0m";
	cin >> ID;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	id = ID;
}
void RegisterAspecificStudentsForCourseID(int& id) {
	int ID;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m====================================================== [ Register Student for Course  ] ============================================================\033[0m\n";
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> ID : \033[0m";
	cin >> ID;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	id = ID;
}
void UnRegisterAspecificStudentsForCourseID(int& id) {
	int ID;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m====================================================== [ UnRegister Student for Course  ] ==========================================================\033[0m\n";
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> ID : \033[0m";
	cin >> ID;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	id = ID;
}
void ShowStudentsCoursesID(int& id) {
	int ID;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m========================================================= [ Student for Courses  ] ================================================================\033[0m\n";
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> ID : \033[0m";
	cin >> ID;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	id = ID;
}
void ShowCoursesStudentsID(string& courseid) {
	string courseid1;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m========================================================= [ Course for Students  ] =================================================================\033[0m\n";
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> courseid : \033[0m";
	cin >> courseid1;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	courseid = courseid1;
}
void DeleteAspecificStudentsID(int& id) {
	int ID;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m=========================================================== [ Delete Student Data ] ================================================================\033[0m\n";
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> ID : \033[0m";
	cin >> ID;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	id = ID;
}
void SearchAspecificStudentsID(int& id) {
	int ID;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m=========================================================== [ Search Student Data  ] ===============================================================\033[0m\n";
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> ID : \033[0m";
	cin >> ID;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	id = ID;
}
void showStudentPortal() {
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;


	cout << "\033[90m ";
	cout << string(64, ' ') << string(18, '-');
	cout << endl;
	cout << string(64, ' ') << " \033[90m|\033[1;33m STUDENT PORTAL \033[0m\033[90m|\033[90m" << endl;
	cout << string(65, ' ') << string(18, '-');
	cout << endl;

	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;


	cout << "\033[38;5;14m                               ================================ [ Access your options ] ===============================\033[0m" << endl;


	cout << "\033[38;5;33m";
	cout << "[1] Register in Course         \n";
	cout << "[2] Unregister from Course     \n";
	cout << "[3] View My Courses            \n";
	cout << "[4] View My Grades             \n";
	cout << "[5] View My Profile            \n";
	cout << "[6] Edit My Personal Info      \n";
	cout << "[7] Report a complaint           \n";
	cout << "[8] Know the marks of all skipped subjects      \n";
	cout << "[9] Logout                     \n";


	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[0m"; // Reset color


	cout << endl << endl;
	cout << "\033[34mPlease choose an option: \033[0m";
}
void showTeacherPortal() {
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;

	cout << "\033[90m ";
	cout << string(64, ' ') << string(18, '-');
	cout << endl;
	cout << string(64, ' ') << " \033[90m|\033[1;33m TEACHER PORTAL \033[0m\033[90m|\033[90m" << endl;
	cout << string(65, ' ') << string(18, '-');
	cout << endl;

	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;

	cout << "\033[38;5;14m                               ================================ [ Access your options ] ===============================\033[0m" << endl;

	cout << "\033[38;5;33m";
	cout << "[1] View My Courses             \n";
	cout << "[2] View Students in My Courses \n";
	cout << "[3] Submit a complaint           \n";
	cout << "[4] Edit My Profile             \n";
	cout << "[5] Logout                      \n";

	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[0m";

	cout << endl << endl;
	cout << "\033[34mPlease choose an option: \033[0m";
}
void showAdminPortal() {
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";

	// عنوان
	cout << "\033[90m ";
	cout << string(53, ' ') << "\033[1;33m* WELCOME TO UNIVERSITY MANAGEMENT SYSTEM *\033[0m" << endl;

	cout << "\033[90m" << string(148, '=') << "\033[0m\n";

	// عنوان داخلي
	cout << "\033[38;5;14m";
	cout << string(45, ' ') << "====================== [ ADMIN PORTAL ] ======================" << endl;

	cout << "\033[38;5;33m";
	cout << "[1] Student Management\n";
	cout << "[2] Course Management\n";
	cout << "[3] Registration\n";
	cout << "[4] Grades Management\n";
	cout << "[5] Show Reports\n";
	cout << "[6] Exit\n";

	cout << "\033[0m"; // Reset color

	cout << "\033[90m" << string(148, '=') << "\033[0m\n\n";
	cout << "\033[34mPlease choose an option: \033[0m";
}
void StudentManagement() {
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	//STUDENT MANAGEMENT
	// عنوان
	cout << "\033[90m ";
	cout << string(53, ' ') << "\033[1;33m* WELCOME TO UNIVERSITY MANAGEMENT SYSTEM *\033[0m" << endl;

	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[38;5;14m";
	cout << string(41, ' ') << "====================== [ STUDENT MANAGEMENT ] ======================" << endl;
	cout << "\033[38;5;33m";
	cout << "[1] Add Student\n";
	cout << "[2] Edit Student  \n";
	cout << "[3] Delete Student \n";
	cout << "[4] Search Student\n";
	cout << "[5] Show All Students\n";
	cout << "[6] Back to Main Menu\n";

	cout << "\033[0m"; // Reset color

	cout << "\033[90m" << string(148, '=') << "\033[0m\n\n";
	cout << "\033[34mPlease choose an option: \033[0m";
}
void CourseManagement() {
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";

	// COURSE MANAGEMENT - عنوان
	cout << "\033[90m ";
	cout << string(53, ' ') << "\033[1;33m* WELCOME TO UNIVERSITY MANAGEMENT SYSTEM *\033[0m" << endl;

	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[38;5;14m";
	cout << string(41, ' ') << "====================== [ COURSE MANAGEMENT ] ======================" << endl;
	cout << "\033[38;5;33m";
	cout << "[1] Add Course\n";
	cout << "[2] Edit Course\n";
	cout << "[3] Delete Course\n";
	cout << "[4] Show All Courses\n";
	cout << "[5] Back to Main Menu\n";

	cout << "\033[0m"; // Reset color

	cout << "\033[90m" << string(148, '=') << "\033[0m\n\n";
	cout << "\033[34mPlease choose an option: \033[0m";
}
void RegistrationMenu() {
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";

	// REGISTRATION MENU - عنوان
	cout << "\033[90m ";
	cout << string(53, ' ') << "\033[1;33m* WELCOME TO UNIVERSITY MANAGEMENT SYSTEM *\033[0m" << endl;

	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[38;5;14m";
	cout << string(41, ' ') << "====================== [ REGISTRATION MENU ] ======================" << endl;
	cout << "\033[38;5;33m";
	cout << "[1] Register Student in Course\n";
	cout << "[2] Unregister Student\n";
	cout << "[3] Show Student's Courses\n";
	cout << "[4] Show Course's Students\n";
	cout << "[5] Back to Main Menu\n";

	cout << "\033[0m"; // Reset color

	cout << "\033[90m" << string(148, '=') << "\033[0m\n\n";
	cout << "\033[34mPlease choose an option: \033[0m";
}
void GradesManagementMenu() {
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";

	// GRADES MANAGEMENT - عنوان
	cout << "\033[90m ";
	cout << string(53, ' ') << "\033[1;33m* WELCOME TO UNIVERSITY MANAGEMENT SYSTEM *\033[0m" << endl;

	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[38;5;14m";
	cout << string(41, ' ') << "====================== [ GRADES MANAGEMENT ] ======================" << endl;
	cout << "\033[38;5;33m";

	cout << "[1] Add/Edit Grade\n";
	cout << "[2] Show Student Grades\n";
	cout << "[3] Back to Main Menu\n";

	cout << "\033[0m"; // Reset color

	cout << "\033[90m" << string(148, '=') << "\033[0m\n\n";
	cout << "\033[34mPlease choose an option: \033[0m";
}
void ShowReportsMenuAdmin() {
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";

	cout << "\033[90m ";
	cout << string(53, ' ') << "\033[1;33m* WELCOME TO UNIVERSITY MANAGEMENT SYSTEM *\033[0m" << endl;

	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[38;5;14m";
	cout << string(41, ' ') << "====================== [ REPORTS MENU ] ======================" << endl;
	cout << "\033[38;5;33m";

	cout << "[1] Complaints Box\n";
	cout << "[2] Empty Complaints Box\n";
	cout << "[3] Complete statistics for students,teachers and courses\n";
	cout << "[4] Know the marks of all skipped subjects\n";
	cout << "[5] Back to Main Menu\n";

	cout << "\033[0m";

	cout << "\033[90m" << string(148, '=') << "\033[0m\n\n";
	cout << "\033[34mPlease choose an option: \033[0m";
}
void CreateStudentAccount(arrayList<students>& studentsList) {
	string name, dateOfBirth, nationality, bloodType, address, joinDate;
	string email, phoneNumber, password, college, department, major;
	float tawjihiAverage;
	double semesterGPA = 0.0, GPA = 0.0;
	string studyLevel = "level(1)", planVersion, statos;
	int completedHours = 0, totalHours;
	char gender;

	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m====================================================== [ Create a New Student Account ] ============================================================\033[0m\n";

	cout << "\033[90m|\033[1;33mEnter Name:\033[0m ";
	getline(cin >> ws, name);

	cout << "\033[90m|\033[1;33mEnter Gender (M/F):\033[0m ";
	cin >> gender;

	cout << "\033[90m|\033[1;33mEnter Date of Birth (YYYY-MM-DD):\033[0m ";
	cin >> dateOfBirth;

	cout << "\033[90m|\033[1;33mEnter Nationality:\033[0m ";
	cin >> nationality;

	cout << "\033[90m|\033[1;33mEnter Blood Type:\033[0m ";
	cin >> bloodType;

	cout << "\033[90m|\033[1;33mEnter Address:\033[0m ";
	cin.ignore();
	getline(cin, address);

	cout << "\033[90m|\033[1;33mEnter Join Date (YYYY-MM-DD):\033[0m ";
	getline(cin, joinDate);

	cout << "\033[90m|\033[1;33mEnter Email:\033[0m ";
	cin >> email;

	cout << "\033[90m|\033[1;33mEnter Phone Number:\033[0m ";
	cin >> phoneNumber;

	cout << "\033[90m|\033[1;33mCreate a Password:\033[0m ";
	cin >> password;

	cout << "\033[90m|\033[1;33mEnter College:\033[0m ";
	cin.ignore();
	getline(cin, college);

	cout << "\033[90m|\033[1;33mEnter Department:\033[0m ";
	getline(cin, department);

	cout << "\033[90m|\033[1;33mEnter Major:\033[0m ";
	getline(cin, major);

	cout << "\033[90m|\033[1;33mEnter Tawjihi Average:\033[0m ";
	cin >> tawjihiAverage;

	cout << "\033[90m|\033[1;33mEnter Plan Version:\033[0m ";
	getline(cin, planVersion);

	cout << "\033[90m|\033[1;33mEnter Status (e.g. Active):\033[0m ";
	getline(cin, statos);

	cout << "\033[90m|\033[1;33mEnter Total Hours:\033[0m ";
	cin >> totalHours;

	cout << endl;
	students newStudent(name, gender, dateOfBirth, nationality, bloodType, address, joinDate, email, phoneNumber, password, college, department, major, tawjihiAverage, semesterGPA, GPA, studyLevel, planVersion, statos, completedHours, totalHours);
	studentsList.insertEnd(newStudent);
}
void CreateTeacherAccount(arrayList<teachers>& teachersList) {
	string name, dateOfBirth, nationality, bloodType, address, joinDate;
	string email, phoneNumber, password, college, department, major;
	string academicRank, officeHours;
	int NumberOfHolidays;
	double salary;
	char gender;

	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m==================================================== [ Create a New Teacher Account ] ==============================================================\033[0m\n";

	cout << "\033[90m|\033[1;33mEnter Name:\033[0m ";
	getline(cin >> ws, name);

	cout << "\033[90m|\033[1;33mEnter Gender (M/F):\033[0m ";
	cin >> gender;

	cout << "\033[90m|\033[1;33mEnter Date of Birth (YYYY-MM-DD):\033[0m ";
	cin >> dateOfBirth;

	cout << "\033[90m|\033[1;33mEnter Nationality:\033[0m ";
	cin >> nationality;

	cout << "\033[90m|\033[1;33mEnter Blood Type:\033[0m ";
	cin >> bloodType;

	cout << "\033[90m|\033[1;33mEnter Address:\033[0m ";
	cin.ignore();
	getline(cin, address);

	cout << "\033[90m|\033[1;33mEnter Join Date (YYYY-MM-DD):\033[0m ";
	getline(cin, joinDate);

	cout << "\033[90m|\033[1;33mEnter Email:\033[0m ";
	cin >> email;

	cout << "\033[90m|\033[1;33mEnter Phone Number:\033[0m ";
	cin >> phoneNumber;

	cout << "\033[90m|\033[1;33mCreate a Password:\033[0m ";
	cin >> password;

	cout << "\033[90m|\033[1;33mEnter College:\033[0m ";
	cin.ignore();
	getline(cin, college);

	cout << "\033[90m|\033[1;33mEnter Department:\033[0m ";
	getline(cin, department);

	cout << "\033[90m|\033[1;33mEnter Major:\033[0m ";
	getline(cin, major);

	cout << "\033[90m|\033[1;33mEnter Academic Rank (e.g. Assistant Professor):\033[0m ";
	getline(cin, academicRank);

	cout << "\033[90m|\033[1;33mEnter Salary:\033[0m ";
	cin >> salary;

	cout << "\033[90m|\033[1;33mEnter Office Hours:\033[0m ";
	cin.ignore();
	getline(cin, officeHours);

	cout << "\033[90m|\033[1;33mEnter Number of Holidays:\033[0m ";
	cin >> NumberOfHolidays;

	cout << endl;

	teachers newTeacher(name, gender, dateOfBirth, nationality, bloodType, address, joinDate,
		email, phoneNumber, password, college, department, major,
		academicRank, salary, officeHours, NumberOfHolidays);

	teachersList.insertEnd(newTeacher);

	cout << "\033[92mTeacher account created successfully!\033[0m\n";
}
void CreateAdminAccount(arrayList<Admin>& adminList) {
	string name, dateOfBirth, nationality, bloodType, address, joinDate;
	string email, phoneNumber, password, college, department, major;
	string academicRank, officeHours;
	int NumberOfHolidays;
	double salary;
	char gender;

	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m==================================================== [ Create a New Teacher Account ] ==============================================================\033[0m\n";

	cout << "\033[90m|\033[1;33mEnter Name:\033[0m ";
	getline(cin >> ws, name);

	cout << "\033[90m|\033[1;33mEnter Gender (M/F):\033[0m ";
	cin >> gender;

	cout << "\033[90m|\033[1;33mEnter Date of Birth (YYYY-MM-DD):\033[0m ";
	cin >> dateOfBirth;

	cout << "\033[90m|\033[1;33mEnter Nationality:\033[0m ";
	cin >> nationality;

	cout << "\033[90m|\033[1;33mEnter Blood Type:\033[0m ";
	cin >> bloodType;

	cout << "\033[90m|\033[1;33mEnter Address:\033[0m ";
	cin.ignore();
	getline(cin, address);

	cout << "\033[90m|\033[1;33mEnter Join Date (YYYY-MM-DD):\033[0m ";
	getline(cin, joinDate);

	cout << "\033[90m|\033[1;33mEnter Email:\033[0m ";
	cin >> email;

	cout << "\033[90m|\033[1;33mEnter Phone Number:\033[0m ";
	cin >> phoneNumber;

	cout << "\033[90m|\033[1;33mCreate a Password:\033[0m ";
	cin >> password;

	cout << "\033[90m|\033[1;33mEnter College:\033[0m ";
	cin.ignore();
	getline(cin, college);

	cout << "\033[90m|\033[1;33mEnter Department:\033[0m ";
	getline(cin, department);

	cout << "\033[90m|\033[1;33mEnter Major:\033[0m ";
	getline(cin, major);

	cout << "\033[90m|\033[1;33mEnter Academic Rank (e.g. Assistant Professor):\033[0m ";
	getline(cin, academicRank);

	cout << "\033[90m|\033[1;33mEnter Salary:\033[0m ";
	cin >> salary;

	cout << "\033[90m|\033[1;33mEnter Office Hours:\033[0m ";
	cin.ignore();
	getline(cin, officeHours);

	cout << "\033[90m|\033[1;33mEnter Number of Holidays:\033[0m ";
	cin >> NumberOfHolidays;

	cout << endl;

	Admin newAdmin(name, gender, dateOfBirth, nationality, bloodType, address, joinDate,
		email, phoneNumber, password, college, department, major,
		academicRank, salary, officeHours, NumberOfHolidays);

	adminList.insertEnd(newAdmin);

	cout << "\033[92mTeacher account created successfully!\033[0m\n";
}
void addGrade(arrayList<Course>& courseslist, arrayList<students>& studentlist) {
	string coursecode, filepath;
	double Sfirst, Ssecond, Smid, Sfinal;
	int Sid;
	Course c1;
	students s1;
	vector<int> studentsInTheCourse;

	cout << "\033[1;36mEnter the course code:\033[0m "; // Cyan
	cin >> coursecode;

	int location = serchCourseByID(courseslist, coursecode);
	if (location != -1) {
		cout << "\033[1;36mEnter path of the file:\033[0m "; // Cyan
		cin >> filepath;

		c1 = courseslist.opp(location);
		studentsInTheCourse = c1.getStudentsInTheCourse();

		ifstream infile(filepath);
		if (!infile.is_open()) {
			cout << "\033[1;31mError opening file!\033[0m" << endl; // Red
			return;
		}

		while (infile >> Sid >> Sfirst >> Ssecond >> Smid >> Sfinal) {
			if (c1.isregist(Sid)) {
				int studLoc = serchstudentByID(studentlist, Sid);
				if (studLoc != -1) {
					s1 = studentlist.opp(studLoc);
					s1.addgread(coursecode, Sfirst, Ssecond, Smid, Sfinal);
					studentlist.insertAT(studLoc, s1); // replace or insert
					cout << "\033[1;32mGrade added successfully for student ID "
						<< Sid << "\033[0m" << endl; // Green
				}
				else {
					cout << "\033[1;31mError: student with ID " << Sid
						<< " not found.\033[0m" << endl; // Red
				}
			}
			else {
				cout << "\033[1;33mWarning: student " << Sid
					<< " is not registered in course " << coursecode
					<< "\033[0m" << endl; // Yellow
			}
		}

		infile.close();
	}
	else {
		cout << "\033[1;31mThe course does not exist. Please check the course code.\033[0m" << endl; // Red
	}
}

void ShowStudentGrades(arrayList<Course>& courseslist, arrayList<students>& studentlist) {
	string coursecode;
	students s1;
	Course c1;
	int location, ids;

	cout << "\033[1;36mEnter the course code:\033[0m ";
	cin >> coursecode;

	location = serchCourseByID(courseslist, coursecode);
	if (location == -1) {
		cout << "\033[1;31mError: Course not found!\033[0m" << endl;
		return;
	}

	c1 = courseslist.opp(location);
	vector<int> studentsids = c1.getStudentsInTheCourse();

	cout << "\n\033[1;34m=== Grades for Course " << coursecode << " ===\033[0m\n";

	for (int i = 0; i < studentsids.size(); i++) {
		ids = studentsids[i];
		location = serchstudentByID(studentlist, ids);
		if (location == -1) {
			cout << "\033[1;33mWarning: student ID " << ids << " not found.\033[0m\n";
			continue;
		}

		s1 = studentlist.opp(location);

		// عرض منسق
		cout << "\033[1;32mStudent ID:\033[0m " << ids << endl;
		cout << "-----------------------------" << endl;

		// بافترض printcourses(coursecode) بيرجع string فيه العلامات
		// لو بتطبع لحالها عدلها تطبع كل علامة بسطر
		s1.printcourses(coursecode);

		cout << endl<<endl<<endl; // مسافة بين الطلاب
	}
}

long long TotalRegistrations(arrayList<Course>& listC) {
	Course c1;
	long long sum = 0;
	for (int i = 0; i < listC.getLength(); i++) {
		c1 = listC.opp(i);
		sum += c1.getStudentsInTheCourseSize();
	}
	return sum;
}
int serchstudentByID(arrayList<students>& list, int id) {
	students s;
	for (int i = 0; i < list.getLength(); i++) {
		s = list.opp(i);
		if (s.getID() == id) {
			return i;
		}
	}
	system("cls");
	cout << "\033[31mThe student you are looking for does not exist.....\033[0m" << endl;
	return -1;
}
int serchteacherByID(arrayList<teachers>& list, int id) {
	teachers t;
	for (int i = 0; i < list.getLength(); i++) {
		t = list.opp(i);
		if (t.getID() == id) {
			return i;
		}
	}
	system("cls");
	cout << "\033[31mThe teacher you are looking for does not exist.....\033[0m" << endl;
	return -1;
}
int serchAdminByID(arrayList<Admin>& list, int id) {
	Admin a;
	for (int i = 0; i < list.getLength(); i++) {
		a = list.opp(i);
		if (a.getID() == id) {
			return i;
		}
	}
	system("cls");
	cout << "\033[31mThe Admin you are looking for does not exist.....\033[0m" << endl;
	return -1;
}
int serchCourseByID(arrayList<Course>& list, string id) {
	Course c;
	for (int i = 0; i < list.getLength(); i++) {
		c = list.opp(i);
		if (c.getCourseCode() == id) {
			return i;
		}
	}
	return -1;
}
int generateRandom6Digit() {
	int min = 100000;
	int max = 999999;
	return rand() % (max - min + 1) + min;
}
void SaveStudentsToFile(arrayList<students>& filelist, const string& filename) {
	ofstream out(filename);
	if (!out.is_open()) return;

	for (int i = 0; i < filelist.getLength(); i++) {
		filelist.opp(i).SaveToFile(out);
	}
	out.close();
}
void LoadStudentsFromFile(arrayList<students>& filelist, const string& filename) {
	ifstream in(filename);
	if (!in.is_open()) return;

	string line;
	while (getline(in, line)) {
		students s;
		if (s.LoadFromFileLine(line)) {
			filelist.insertEnd(s);
		}
	}
	in.close();
}
void SaveTeachersToFile(arrayList<teachers>& filelist, const string& filename) {
	ofstream out(filename);
	if (!out.is_open()) {
		cerr << "Error: Cannot open file " << filename << " for writing!" << endl;
		return;
	}

	for (int i = 0; i < filelist.getLength(); i++) {
		filelist.opp(i).SaveToFile(out);
	}
	out.close();
	cout << "Teachers data saved successfully to " << filename << endl;
}
void LoadTeachersFromFile(arrayList<teachers>& filelist, const string& filename) {
	ifstream in(filename);
	if (!in.is_open()) {
		cerr << "Error: Cannot open file " << filename << " for reading!" << endl;
		return;
	}

	string line;
	int loadedCount = 0;
	int errorCount = 0;

	while (getline(in, line)) {
		if (line.empty()) continue; // تخطي الأسطر الفارغة

		teachers t;
		if (t.LoadFromFileLine(line)) {
			filelist.insertEnd(t);
			loadedCount++;
		}
		else {
			errorCount++;
			cerr << "Failed to load teacher data from line: " << line << endl;
		}
	}
	in.close();

	cout << "Loaded " << loadedCount << " teachers from " << filename;
	if (errorCount > 0) {
		cout << " (" << errorCount << " errors)";
	}
	cout << endl;
}
void SaveCoursesToFile(arrayList<Course>& filelist, const string& filename) {
	ofstream out(filename);
	if (!out.is_open()) return;

	for (int i = 0; i < filelist.getLength(); i++) {
		filelist.opp(i).SaveToFile(out);
	}
	out.close();
}
void LoadCoursesFromFile(arrayList<Course>& filelist, const string& filename) {
	ifstream in(filename);
	if (!in.is_open()) return;

	string line;
	while (getline(in, line)) {
		Course c;
		if (c.LoadFromFileLine(line)) {
			filelist.insertEnd(c);
		}
	}
	in.close();
}
void showLoginScreen() {
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;

	cout << string(30, ' ') << "\033[38;5;122m" << string(88, '-') << "\033[0m" << endl;

	cout << string(30, ' ') << "\033[38;5;122m|\033[0m\033[38;5;14m                           Jordan University of Science                               \033[0m\033[38;5;122m|\033[0m\n";
	cout << string(30, ' ') << "\033[38;5;122m|\033[0m\033[38;5;14m                               and Technology - JUST                                  \033[0m\033[38;5;122m|\033[0m\n";

	cout << string(30, ' ') << "\033[38;5;122m" << string(88, '-') << "\033[0m" << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;

	// Welcome message - ASCII art improved
	cout << string(46, ' ') << "\033[38;5;48m __        __   _                            _          \033[0m\n";
	cout << string(46, ' ') << "\033[38;5;48m \\ \\      / /__| | ___ ___  _ __ ___   ___  | |_ ___    \033[0m\n";
	cout << string(46, ' ') << "\033[38;5;48m  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\   \033[0m\n";
	cout << string(46, ' ') << "\033[38;5;48m   \\ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |  \033[0m\n";
	cout << string(46, ' ') << "\033[38;5;48m    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/   \033[0m\n";

	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[38;5;14m                               =============================== [ Select your status ] ================================\033[0m" << endl;
	cout << "\033[90m||\033[0m\033[38;5;33m 1) Student " << string(132, ' ') << "\033[90m||\033[0m" << endl;
	cout << "\033[90m||\033[0m\033[38;5;33m 2) Teacher  " << string(131, ' ') << "\033[90m||\033[0m" << endl;
	cout << "\033[90m||\033[0m\033[38;5;33m 3) Admin " << string(134, ' ') << "\033[90m||\033[0m" << endl;
	cout << "\033[90m||\033[0m\033[38;5;33m 4) Exit " << string(135, ' ') << "\033[90m||\033[0m" << endl;

	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl << endl;

	cout << "\033[34mPlease choose an option: \033[0m";
}
void showAuthMenu() {
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[38;5;14m ";
	cout << string(64, ' ') << string(18, '-');
	cout << endl;
	cout << string(64, ' ') << " | AUTHENTICATION |" << endl;
	cout << string(65, ' ') << string(18, '-');
	cout << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[38;5;14m                               =============================== [ Select your status ] ================================\033[0m" << endl;
	cout << "\033[38;5;33m";
	cout << "[1] Log In\n";
	cout << "[2] Sign Up\n";
	cout << "[3] Back\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	cout << "\033[0m";
	cout << endl << endl;

	cout << "\033[34mPlease choose an option: \033[0m";
}
void EnterAStudentTranscriptID(int& id) {
	int ID;
	cout << "\n\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[90m||" << string(58, ' ') << "\033[1;33mWelcome to JUST System\033[1;36m" << string(64, ' ') << "\033[90m||\n";
	cout << "\033[90m" << string(148, '=') << "\033[0m\n";
	cout << "\033[1;36m=========================================================== [ Student Transcript  ] ================================================================\033[0m\n";
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl;
	cout << "\033[90m|\033[1;33m-> ID : \033[0m";
	cin >> ID;
	cout << "\033[90m" << string(24, '-') << "\033[0m" << endl << endl;
	cout << "\033[90m" << string(148, '=') << "\033[0m" << endl;
	id = ID;
}
void CalculatethesetsemesterGPA(arrayList<students>& studentlist, arrayList<Course>& courselist) {
	for (int i = 0; i < studentlist.getLength(); i++) {
		students s1 = studentlist.opp(i);
		double sum = 0;
		int semesterhours = 0;
		for (int j = 0; j < s1.getLengthSemestercourses(); j++) {
			string course = s1.getsemestercourses(j);
			Course c1 = courselist.opp(serchCourseByID(courselist, course));
			gread gr = s1.getgread(course);
			string courseSymbol = gr.getcourseSymbol();
			int Hours = c1.getCreditHours();
			semesterhours += Hours;
			if (courseSymbol == "A+") {
				sum += 4.2 * Hours;
			}
			else if (courseSymbol == "A") {
				sum += 4 * Hours;
			}
			else if (courseSymbol == "A-") {
				sum += 3.75 * Hours;
			}
			else if (courseSymbol == "B+") {
				sum += 3.5 * Hours;
			}
			else if (courseSymbol == "B") {
				sum += 3, 25 * Hours;
			}
			else if (courseSymbol == "B-") {
				sum += 3 * Hours;
			}
			else if (courseSymbol == "C+") {
				sum += 2, 75 * Hours;
			}
			else if (courseSymbol == "C") {
				sum += 2.5 * Hours;
			}
			else if (courseSymbol == "C-") {
				sum += 2.25 * Hours;
			}
			else if (courseSymbol == "D+") {
				sum += 2 * Hours;
			}
			else if (courseSymbol == "D") {
				sum += 1.75 * Hours;
			}
			else if (courseSymbol == "D-") {
				sum += 1.5 * Hours;
			}
			else if (courseSymbol == "F") {
				sum += 0 * Hours;
			}
			s1.addcours(course);
		}

		s1.setsemesterGPA((sum / semesterhours), semesterhours);
		s1.setGPA();
		s1.clearsemestercourses();
		s1.setstudyLevel();
	}
}
void SaveAdminToFile(arrayList<Admin>& filelist, const string& filename) {
	ofstream out(filename);
	if (!out.is_open()) {
		cerr << "Error: Cannot open file " << filename << " for writing!" << endl;
		return;
	}

	for (int i = 0; i < filelist.getLength(); i++) {
		filelist.opp(i).SaveToFile(out);
	}
	out.close();
	cout << "Admin data saved successfully to " << filename << endl;
}
void LoadAdminFromFile(arrayList<Admin>& filelist, const string& filename) {
	ifstream in(filename);
	if (!in.is_open()) {
		cerr << "Error: Cannot open file " << filename << " for reading!" << endl;
		return;
	}

	string line;
	int loadedCount = 0;
	int errorCount = 0;

	while (getline(in, line)) {
		if (line.empty()) continue;

		Admin a;
		if (a.LoadFromFileLine(line)) {
			filelist.insertEnd(a);
			loadedCount++;
		}
		else {
			errorCount++;
			cerr << "Failed to load admin data from line: " << line << endl;
		}
	}
	in.close();

	cout << "Loaded " << loadedCount << " admins from " << filename;
	if (errorCount > 0) {
		cout << " (" << errorCount << " errors)";
	}
	cout << endl;
}
