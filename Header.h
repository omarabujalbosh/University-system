#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<map>

using namespace std;
class students;
template<class elemtype>
/*// =====================================================================================
// الكلاس: arrayList
// الهدف  : يوفر قائمة ديناميكية قابلة للتوسع لتخزين عناصر من أي نوع (Template Class)
//          يعمل كبديل مرن للمصفوفات العادية مع إدارة تلقائية للذاكرة.
//
// الخصائص (Attributes):
//   - length  : عدد العناصر الحالية المخزنة في القائمة.
//   - maxList : السعة القصوى الحالية للقائمة (حجم المصفوفة الداخلية).
//   - list    : مؤشر إلى المصفوفة الديناميكية التي تخزن العناصر.
//
// الدوال (Functions):
//   - arrayList()                              : منشئ افتراضي ينشئ قائمة بسعة 1000 عنصر.
//   - arrayList(long long maxList)             : منشئ ينشئ قائمة بسعة محددة من المستخدم.
//   - arrayList(arrayList<elemtype>& otherList): منشئ نسخ ينشئ قائمة جديدة من قائمة موجودة.
//   - operator=(arrayList<elemtype>& otherList): عامل تعيين ينقل محتويات قائمة إلى أخرى.
//   - insertAT(location, value)                : يدخل عنصر في موقع محدد في القائمة.
//   - insertEnd(value)                         : يدخل عنصر في نهاية القائمة.
//   - removeAT(location)                       : يزيل عنصر من موقع محدد في القائمة.
//   - retrieveAT(location, value)              : يسترجع عنصر من موقع محدد ويخزنه في value.
//   - replaceAt(location, value)               : يستبدل عنصر في موقع محدد بقيمة جديدة.
//   - print()                                  : يطبع جميع العناصر في القائمة (يعتمد على نوع العنصر).
//   - search(ID)                               : يبحث عن عنصر باستخدام رقم ID (لمعرفة إذا كان موجوداً).
//   - clearAT()                                : يمسح جميع العناصر من القائمة (بدون تحرير الذاكرة).
//   - getLength()                              : يعيد عدد العناصر الحالية في القائمة.
//   - resize(maxSize)                          : يغير السعة القصوى للقائمة (يحافظ على العناصر الموجودة).
//   - opp(location)                            : يعيد مرجعاً للعنصر في الموقع المحدد (للوصول المباشر).
//   - ~arrayList()                             : مدمر يقوم بتحرير الذاكرة المخصصة للمصفوفة.
//
// الاستخدام داخل المشروع:
//   يستخدم هذا الكلاس كحاوية لتخزين مجموعات من البيانات في جميع أنحاء النظام:
//   - تخزين قائمة الطلاب (arrayList<students>)
//   - تخزين قائمة المعلمين (arrayList<teachers>)
//   - تخزين قائمة المقررات (arrayList<Course>)
//   - تخزين قائمة الإداريين (arrayList<Admin>)
//
// =====================================================================================*/
class arrayList {
private:
	long long length, maxList;
	elemtype* list;

public:
	arrayList();
	arrayList(long long maxList);
	arrayList(arrayList<elemtype>& otherList);
	arrayList& operator=(arrayList<elemtype>& otherList);

	void insertAT(long long location, elemtype& value);
	void insertEnd(elemtype& value);
	void removeAT(long long location);
	void retrieveAT(long long location, elemtype& value);
	void replaceAt(long long location, elemtype& value);
	void print();
	bool search(long long ID) const;
	void clearAT();
	long long getLength();
	void resize(long long maxSize);
	elemtype& opp(long long location);
	~arrayList();
};
/*// =====================================================================================
// الهيكل: Complaint
// الهدف : يمثل شكوى داخل نظام الجامعة (مقدمة من طالب أو مدرس).
//
// الخصائص (Attributes):
// - senderType : نوع المرسل (مثلاً "Student" أو "Teacher").
// - senderID : رقم هوية المرسل (ID الخاص بالطالب أو المدرس).
// - message : نص الشكوى نفسها.
//
// الاستخدام داخل المشروع:
// هذا الهيكل بسيط ومباشر، الغرض منه تخزين الشكاوى التي يتم إرسالها من الطلاب أو المدرسين.
// عادةً يتم ربطه بكلاس Admin، حيث يقوم المسؤول بعرض الشكاوى والتعامل معها.
// لأنه struct (وليس class)، فجميع الخصائص عامة بشكل افتراضي (public)،
// وهذا مناسب لتخزين البيانات فقط بدون منطق معقد.
//
// أمثلة على الاستخدام:
// Complaint c1 = {"Student", 20231001, "القاعة غير مجهزة بشكل مناسب"};
// Complaint c2 = {"Teacher", 5003, "النظام لا يسجل الطلاب بشكل صحيح"};
// =====================================================================================
*/
struct Complaint {
	string senderType;
	int senderID;
	string message;
};
/*// =====================================================================================
// الكلاس: gread
// الهدف : يمثل العلامات (الدرجات) الخاصة بمادة معينة لطالب في النظام الجامعي.
// هذا الكلاس مصمم لتخزين تفاصيل العلامات الجزئية (أول، ثاني، ميد، فاينل) وحساب المجموع الكلي.
//
// الخصائص (Attributes):
// - first : علامة الامتحان الأول.
// - seconde : علامة الامتحان الثاني.
// - mid : علامة الامتحان النصفي (Midterm).
// - final : علامة الامتحان النهائي (Final).
// - typeCourse : نوع الكورس (قد يمثل مثلاً: عملي = 1، نظري = 2، إلخ حسب التصميم).
// - symbol : الرمز التقديري للمادة (A, B, C, D, E …) الافتراضي هو "E".
//
// الدوال (Functions):
// - gread() : دالة بانية افتراضية، تنشئ كائن درجات فارغ.
// - setfirst(double first) : تعيين علامة الامتحان الأول.
// - setseconde(double seconde) : تعيين علامة الامتحان الثاني.
// - setmid(double mid) : تعيين علامة الامتحان النصفي.
// - setfinal(double final) : تعيين علامة الامتحان النهائي.
// - setTypeCourse(int Case) : تعيين نوع الكورس (عملي/نظري).
// - getfirst() const : إرجاع علامة الامتحان الأول.
// - getseconde() const : إرجاع علامة الامتحان الثاني.
// - getmid() const : إرجاع علامة الامتحان النصفي.
// - getfinal() const : إرجاع علامة الامتحان النهائي.
// - gettotal() const : إرجاع المجموع الكلي للدرجات (first + seconde + mid + final).
// - getTypeCourse() const : إرجاع نوع الكورس.
// - setGrades(double first, double seconde, double mid, double final) : تعيين كل العلامات دفعة واحدة.
// - getcourseSymbol() : إرجاع الرمز التقديري (رمز النجاح/الرسوب) بناءً على العلامة الكلية.
//
// الاستخدام داخل المشروع:
// الكلاس gread بيوفر آلية لتخزين ومعالجة علامات الطالب في كورس معين.
// ممكن يندمج مع كلاس students أو Course بحيث يمثل نتيجة الطالب في المادة.
// الرموز (symbols) زي "A", "B", "C", "D", "E" بتتحدد من خلال العلامة الكلية.
// =====================================================================================
*/
class gread {
	double first;
	double seconde;
	double mid;
	double final;
	int typeCourse;
	string symbol = "E";
public:
	gread();
	void setfirst(double first);
	void setseconde(double seconde);
	void setmid(double mid);
	void setfinal(double final);
	void setTypeCourse(int Case);
	double getfirst()const;
	double getseconde()const;
	double getmid()const;
	double getfinal()const;
	double gettotal()const;
	int getTypeCourse()const;
	void setGrades(double first, double seconde, double mid, double final);
	string getcourseSymbol();
};
/*// =====================================================================================
// الكلاس: Course
// الهدف : يمثل مادة جامعية (كورس) في النظام، مع كل تفاصيلها (الكود، الاسم، المدرس، الطلاب، الجدول، الموقع، إلخ).
//
// الخصائص (Attributes):
// - courseCode : رمز المادة (مثال: CS101).
// - courseName : اسم المادة (مثال: Introduction to Programming).
// - creditHours : عدد الساعات المعتمدة للمادة.
// - department : اسم القسم المسؤول عن المادة.
// - college : اسم الكلية التي تنتمي لها المادة.
// - instructorName : اسم المدرس المسؤول عن الكورس.
// - semesterOffered : الفصل الدراسي الذي تُطرح فيه المادة (مثال: Fall 2025).
// - schedule : جدول المحاضرات (مثال: Sun-Tue 10:00-11:30).
// - location : مكان المحاضرة (مثال: Room 205).
// - capacity : السعة القصوى (عدد الطلاب المسموح تسجيلهم).
// - enrolledCount : عدد الطلاب الحاليين المسجلين في المادة.
// - cgread : كائن من كلاس gread يمثل العلامات الخاصة بالكورس (قد يكون لمتوسط أو مرتبط بطلاب).
// - StudentsInTheCourse : قائمة بأرقام الطلاب (IDs) المسجلين في الكورس.
//
// الدوال (Functions):
// - Course() : دالة بانية افتراضية (تنشئ كورس فارغ).
// - Course(...) : دالة بانية (Constructor) لإنشاء كورس جديد بكافة التفاصيل.
// - SaveToFile(ofstream& out) const : حفظ بيانات الكورس في ملف.
// - LoadFromFileLine(const string& line) : تحميل بيانات الكورس من سطر في ملف.
// - getCourseCode() : إرجاع رمز الكورس.
// - getCourseName() : إرجاع اسم الكورس.
// - getCreditHours() : إرجاع عدد الساعات المعتمدة.
// - getDepartment() : إرجاع اسم القسم.
// - getCollege() : إرجاع اسم الكلية.
// - getInstructorName() : إرجاع اسم المدرس المسؤول.
// - getSemesterOffered() : إرجاع الفصل المطروح فيه الكورس.
// - getSchedule() : إرجاع الجدول الزمني.
// - getLocation() : إرجاع مكان المحاضرة.
// - getCapacity() : إرجاع السعة القصوى.
// - getEnrolledCount() : إرجاع عدد الطلاب الحاليين المسجلين.
// - setgread() : تعيين قيم العلامات الخاصة بالكورس.
// - getgread() const : إرجاع العلامات (كائن gread).
// - setCourseCode(...), setCourseName(...), setCreditHours(...), ... إلخ : دوال لتعيين القيم لكل خاصية.
// - AddStudentsInTheCourse(int ID) : تسجيل طالب جديد (إضافة ID الطالب إلى القائمة).
// - StudentRemovedFromThisCourse(int ID, students& s1) : إزالة طالب من الكورس.
// - PrintAllStudentsInTheCourse(arrayList<students>& listS) : طباعة قائمة الطلاب المسجلين.
// - DataEntryCourse() : إدخال بيانات الكورس يدويًا (عادةً من المستخدم).
// - getStudentsInTheCourse() : إرجاع قائمة الطلاب المسجلين.
// - isregist(int id) : التحقق إذا كان الطالب (ID) مسجل بالفعل في الكورس.
// - getStudentsInTheCourseSize() const : إرجاع عدد الطلاب المسجلين.
//
// الاستخدام داخل المشروع:
// الكلاس Course هو الأساس لإدارة المواد الجامعية: معلوماتها، المدرسين، الطلاب المسجلين، العلامات.
// يرتبط بالكلاسات الأخرى مثل students و teachers و gread، بحيث يعطي صورة متكاملة عن الكورس.
// =====================================================================================
*/
class Course {
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
	gread cgread;
	vector< int > StudentsInTheCourse;
public:
	Course();
	Course(string courseCode, string courseName, int creditHours, string department, string college, string instructorName, string semesterOffered, string schedule, string location, int capacity, int enrolledCount);
	void SaveToFile(ofstream& out) const;
	bool LoadFromFileLine(const string& line);
	string getCourseCode() const;
	string getCourseName() const;
	int getCreditHours() const;
	string getDepartment() const;
	string getCollege() const;
	string getInstructorName() const;
	string getSemesterOffered() const;
	string getSchedule() const;
	string getLocation() const;
	int getCapacity() const;
	int getEnrolledCount() const;
	void setgread();
	gread getgread()const;
	void setCourseCode(string CourseCode);
	void setCourseName(string CourseName);
	void setCreditHours(int CreditHours);
	void setDepartment(string Department);
	void setCollege(string College);
	void setInstructorName(string InstructorName);
	void setSemesterOffered(string SemesterOffered);
	void setSchedule(string Schedule);
	void setLocation(string Location);
	void setCapacity(int Capacity);
	void setEnrolledCount(int EnrolledCount);
	void AddStudentsInTheCourse(int ID);
	void StudentRemovedFromThisCourse(int ID, students& s1);
	void PrintAllStudentsInTheCourse(arrayList<students>& listS);
	void DataEntryCourse();
	vector<int>getStudentsInTheCourse();//اقتران برجع قائمة الطلاب الي مسجلين في الكورس 
	bool isregist(int id);
	int getStudentsInTheCourseSize()const;
};
/* // =====================================================================================
// الكلاس: person
// الهدف  : يمثل أي شخص داخل نظام الجامعة (أساس - Base Class)
//          يستخدم كلاس person كقاعدة (Parent Class) ليورث منه كلاسات ثانية مثل Student و Teacher.
//
// الخصائص (Attributes):
//   - ID            : رقم تعريفي فريد لكل شخص (يُنشأ بشكل تلقائي).
//   - name          : اسم الشخص الكامل.
//   - email         : البريد الإلكتروني للشخص.
//   - phoneNumber   : رقم هاتف الشخص.
//   - password      : كلمة المرور الخاصة بالشخص (للدخول للنظام).
//   - gender        : جنس الشخص ('M' للذكر أو 'F' للأنثى).
//   - nationality   : جنسية الشخص.
//   - dateOfBirth   : تاريخ ميلاد الشخص.
//   - bloodType     : فصيلة دم الشخص.
//   - address       : عنوان السكن.
//   - joinData      : تاريخ الالتحاق بالجامعة.
//   - college       : الكلية التي ينتمي إليها الشخص.
//   - Department    : القسم التابع له الشخص.
//   - major         : التخصص الدراسي.
//
// الدوال (Functions):
//   - person(...)        : الدالة البانية (Constructor) لإنشاء كائن جديد من نوع person وإعطائه جميع البيانات.
//   - getID()            : ترجع رقم الهوية الفريد.
//   - getName()          : ترجع اسم الشخص.
//   - getEmail()         : ترجع البريد الإلكتروني.
//   - getPhoneNumber()   : ترجع رقم الهاتف.
//   - getPassword()      : ترجع كلمة المرور.
//   - getGender()        : ترجع جنس الشخص.
//   - getNationality()   : ترجع الجنسية.
//   - getDateOfBirth()   : ترجع تاريخ الميلاد.
//   - getBloodType()     : ترجع فصيلة الدم.
//   - getAddress()       : ترجع العنوان.
//   - getJoinDate()      : ترجع تاريخ الالتحاق.
//   - getCollege()       : ترجع الكلية.
//   - getDepartment()    : ترجع القسم.
//   - getMajor()         : ترجع التخصص.
//
// الاستخدام داخل المشروع:
//   هذا الكلاس هو حجر الأساس لنظام الجامعة، حيث يخزن المعلومات العامة لأي شخص.
//   الكلاسات الأخرى (مثل Student و Teacher) ترث منه لتستفيد من خصائصه
//   وتضيف خصائص جديدة متخصصة حسب نوع الشخص.
//
// =====================================================================================*/
class person {
protected:
	int ID;
	string name, email, phoneNumber, password;
	char gender;
	string nationality;
	string dateOfBirth;
	string bloodType;
	string address, joinData;
	string college, Department;
	string major;
public:
	person(string name, char gender, string dateOfBirth, string nationality, string bloodType, string address, string joinData, string email, string phoneNumber, string password, string college, string Department, string major);
	int getID()const;
	string getName()const;
	string getEmail() const;
	string getPhoneNumber() const;
	string getPassword() const;
	char getGender() const;
	string getNationality() const;
	string getDateOfBirth() const;
	string getBloodType() const;
	string getAddress() const;
	string getJoinDate() const;
	string getCollege() const;
	string getDepartment() const;
	string getMajor() const;
};
/*// =====================================================================================
// الكلاس: students
// الهدف  : يمثل الطالب داخل نظام الجامعة (مشتق - Derived Class من person)
//          يحتوي على جميع البيانات الأكاديمية الخاصة بالطالب، مثل معدلاته، المواد
//          المسجل فيها، حالته الأكاديمية، بالإضافة إلى إمكانية تقديم الشكاوى.
//
// الخصائص (Attributes):
//   - TawjihiAverage   : معدل التوجيهي عند القبول.
//   - semesterGPA      : المعدل الفصلي الحالي.
//   - GPA              : المعدل التراكمي الكلي.
//   - studyLevel       : المستوى الدراسي (سنة أولى، ثانية ...).
//   - planVersion      : نسخة الخطة الدراسية.
//   - statos           : حالة الطالب (نشط، موقوف ...).
//   - completedHours   : عدد الساعات المكتسبة بنجاح.
//   - totalHours       : مجموع الساعات المطلوبة للتخرج.
//   - semestercourses  : المواد المسجل فيها في الفصل الحالي.
//   - courses          : جميع المواد التي سجلها الطالب.
//   - greadcourse      : خريطة تربط الكورس بعلامات الطالب فيه.
//   - totalgpa         : خريطة تربط رقم الفصل بمعدله وعدد ساعاته.
//   - Numberofsemesters: عدد الفصول التي درسها الطالب.
//   - warning          : مؤشر إنذار أكاديمي في حال المعدل متدنٍ.
//
// الدوال (Functions):
//   - students(...)               : الدوال البانية لإنشاء كائن جديد من الطالب.
//   - SaveToFile(...)             : حفظ بيانات الطالب في ملف.
//   - LoadFromFileLine(...)       : تحميل بيانات الطالب من سطر ملف.
//   - DataEntry()                 : إدخال/تعديل بيانات الطالب من خلال قائمة تفاعلية.
//   - getTawjihiAverage()         : إرجاع معدل التوجيهي.
//   - getSemesterGPA()            : إرجاع المعدل الفصلي.
//   - getOverallGPA()             : إرجاع المعدل التراكمي.
//   - getStudyLevel()             : إرجاع المستوى الدراسي.
//   - getPlanVersion()            : إرجاع نسخة الخطة الدراسية.
//   - getStatus()                 : إرجاع حالة الطالب.
//   - getCompletedHours()         : إرجاع عدد الساعات المكتسبة.
//   - getTotalHours()             : إرجاع الساعات المطلوبة للتخرج.
//   - getRegisteredCourse(...)    : إرجاع كورس معين من المواد المسجلة حالياً.
//   - getLengthSemestercourses()  : إرجاع عدد المواد المسجلة حالياً.
//   - Jointhecourse(...)          : تسجيل الطالب في كورس جديد.
//   - UnregisterfromCourse(...)   : إلغاء تسجيل الطالب من كورس معين.
//   - ViewMyCourses(...)          : عرض جميع المواد الحالية للطالب.
//   - Showgrades(...)             : عرض علامات الطالب في المواد.
//   - ViewMyProfile()             : عرض ملف الطالب الشخصي بالتفصيل.
//   - EditMyPersonalInfo(...)     : تعديل بيانات الطالب الشخصية.
//   - MakeSureTheCourseIsNotRegistered(...): التحقق أن المادة غير مسجلة مسبقاً.
//   - CourseRegistration(...)     : إضافة مادة لقائمة الطالب الحالية.
//   - PrintRegisteredCourses(...) : طباعة جميع المواد والعلامات (الترانسكريبت).
//   - addgread(...)               : إضافة علامات لمادة معينة.
//   - printcourses(...)           : طباعة علامات مادة معينة للطالب.
//   - submitComplaint()           : تقديم شكوى من الطالب للإدارة.
//   - getsemestercourses(...)     : إرجاع اسم مادة من مواد الفصل الحالي.
//   - getgread(...)               : إرجاع علامات الطالب في مادة معينة.
//   - setsemesterGPA(...)         : تعيين المعدل الفصلي وتخزينه.
//   - setGPA()                    : حساب المعدل التراكمي الكلي وتحديث الإنذار.
//   - addcours(...)               : إضافة مادة لقائمة الطالب الكلية.
//   - clearsemestercourses()      : إفراغ المواد المسجلة في الفصل الحالي.
//
// الاستخدام داخل المشروع:
//   الكلاس students هو حجر الأساس لإدارة بيانات الطلاب الأكاديمية.
//   يتيح للنظام تسجيل الكورسات، حساب المعدلات، إدارة الساعات، وعرض الملف الشخصي.
//   كما يسمح للطلاب بالتفاعل مع النظام من خلال التسجيل، الانسحاب، أو تقديم الشكاوى.
//
// =====================================================================================*/
class students :public person {
	float TawjihiAverage;
	double semesterGPA, GPA;
	string studyLevel, planVersion, statos;
	int completedHours;
	int totalHours;
	vector <string> semestercourses;
	vector <string> courses;
	map<string, gread> greadcourse;
	struct hoursgpa {
		double semestergpa;
		int hours;
	public:
		hoursgpa(double sg, int h) {
			semestergpa = sg;
			hours = h;
		}
		hoursgpa() {
			semestergpa = 0;
			hours = 0;
		}
		double getsemestergpa()const {
			return semestergpa;
		}
		int gethours() const {
			return hours;
		}
	};
	map<int, hoursgpa> totalgpa;
	int Numberofsemesters = 0;
	bool warning = false;
public:
	students();
	students(string name, char gender, string dateOfBirth, string nationality, string bloodType, string address, string joinData, string email, string phoneNumber, string password, string college, string Department, string majorfloat, float TawjihiAverage, double semesterGPA, double GPA, string studyLevel, string planVersion, string statos, int completedHours, int totalHours);
	void SaveToFile(ofstream& out) const;
	bool LoadFromFileLine(const string& line);
	void DataEntry();
	float getTawjihiAverage() const;
	double getSemesterGPA() const;
	double getOverallGPA() const;
	string getStudyLevel() const;
	string getPlanVersion() const;
	string getStatus() const;
	int getCompletedHours() const;
	int getTotalHours() const;
	string getRegisteredCourse(const long long Item) const;
	long long getLengthSemestercourses() const;
	void Jointhecourse(arrayList<Course>& list, arrayList<students>& listS, string courseid, int ID, students& s1);
	void UnregisterfromCourse(arrayList<Course>& list, arrayList<students>& listS, string courseid, int ID, students& s1);
	void ViewMyCourses(arrayList<Course>& list);
	void Showgrades(arrayList<Course>& list);
	void ViewMyProfile();
	void EditMyPersonalInfo(arrayList<students>& listS, students& s1);
	bool MakeSureTheCourseIsNotRegistered(string courseid);
	void CourseRegistration(string courseid);
	void PrintRegisteredCourses(arrayList<Course>& listC);
	void addgread(string coursecode, double Sfirst, double Sseconde, double Smid, double Sfinal);
	void printcourses(string coursecode);
	void submitComplaint();
	string getsemestercourses(int i);
	gread getgread(string semestercourse);
	void setsemesterGPA(double semestergpa, int semesterhours);
	void setGPA();
	void addcours(string course);
	void clearsemestercourses();
	void setstudyLevel();

};
/*// =====================================================================================
// الكلاس: teachers
// الهدف : يمثل عضو هيئة التدريس (دكتور/معلم) في نظام الجامعة.
// هذا الكلاس يرث من الكلاس الأساسي person حتى يستفيد من كل بيانات الشخص (الاسم، البريد، رقم الهاتف، الخ...)
// ويضيف خصائص جديدة متعلقة بالمدرس فقط.
//
// الخصائص (Attributes):
// - academicRank : الرتبة الأكاديمية (مثال: أستاذ، أستاذ مساعد، دكتور).
// - salary : الراتب الشهري للمدرس.
// - officeHours : الساعات المكتبية (الأوقات التي يكون فيها المدرس متاح للطلاب).
// - NumberOfHolidays : عدد الإجازات المسموح بها.
// - MyCourses : قائمة بالكورسات (المساقات) التي يدرسها المدرس.
//
// الدوال (Functions):
// - teachers() : دالة بانية افتراضية (Constructor) لإنشاء كائن فارغ.
// - teachers(...) : دالة بانية (Constructor) لإنشاء كائن جديد من نوع teacher بكل التفاصيل (بيانات أساسية + بيانات المدرس).
// - SaveToFile(ofstream& out) : تخزن بيانات المدرس داخل ملف (للحفظ).
// - LoadFromFileLine(const string& line) : تحميل بيانات المدرس من سطر نصي في الملف (للتحميل).
// - DataEntryteachers() : إدخال بيانات المدرس (عادة عبر المستخدم).
// - getacademicRank() : ترجع الرتبة الأكاديمية.
// - getsalary() : ترجع الراتب.
// - getofficeHours() : ترجع الساعات المكتبية.
// - getNumberOfHolidays() : ترجع عدد الإجازات.
// - ViewMyCourses(arrayList<Course>& listC) : تعرض جميع الكورسات التي يدرسها المدرس.
// - StudentsOfMyCourses(arrayList<Course>& listC, arrayList<students>& listS) : تعرض الطلاب المسجلين في كورسات المدرس.
// - EditMyProfile(arrayList<teachers>& list, int id, teachers& t2) : تعديل بيانات المدرس (ملفه الشخصي) في النظام.
// - SubmitComplaint() : تسجيل/إرسال شكوى من قبل المدرس.
//
// الاستخدام داخل المشروع:
// هذا الكلاس مصمم لإدارة كل ما يتعلق بالمدرسين في الجامعة: بياناتهم، كورساتهم، طلابهم، إجازاتهم.
// الكلاس يستفيد من الكلاس person (المعلومات العامة) ويضيف له ميزات متقدمة خاصة بالمدرسين.
// =====================================================================================
*/
class teachers :public person {
	string academicRank;
	double salary;
	string officeHours;
	int NumberOfHolidays;
	vector< string> MyCourses;
public:
	teachers();
	teachers(string name, char gender, string dateOfBirth, string nationality, string bloodType, string address, string joinData, string email, string phoneNumber, string password, string college, string Department, string major, string academicRank, double salary, string officeHours, int NumberOfHolidays);
	void SaveToFile(ofstream& out) const;
	bool LoadFromFileLine(const string& line);
	void DataEntryteachers();
	string getacademicRank()const;
	double getsalary()const;
	string getofficeHours()const;
	int getNumberOfHolidays()const;
	void ViewMyCourses(arrayList<Course>& listC);
	void StudentsOfMyCourses(arrayList<Course>& listC, arrayList<students>& listS);
	void  EditMyProfile(arrayList<teachers>& list, int id, teachers& t2);
	void SubmitComplaint();

};
/*// =====================================================================================
// الكلاس: Admin
// الهدف : يمثل المسؤول الإداري في نظام الجامعة.
// هذا الكلاس يرث من الكلاس الأساسي person ليحصل على جميع بيانات الشخص العامة
// (الاسم، الجنس، البريد الإلكتروني، رقم الهاتف، إلخ)، ويضيف وظائف وخصائص خاصة بالإدارة.
//
// الخصائص (Attributes):
// - academicRank : الرتبة الأكاديمية (مثال: أستاذ، أستاذ مساعد، دكتور).
// - salary : الراتب الشهري للمسؤول.
// - officeHours : الساعات المكتبية (الأوقات التي يكون فيها المسؤول متاحًا للتعامل مع الطلاب والمدرسين).
// - NumberOfHolidays : عدد الإجازات المسموح بها للمسؤول.
// - Complaints : قائمة الشكاوى المقدمة للمسؤول (مخزنة كـ static لأن كل الشكاوى عامة لجميع المسؤولين).
//
// الدوال (Functions):
// - Admin() : دالة بانية افتراضية لإنشاء كائن فارغ.
// - Admin(...) : دالة بانية لإنشاء كائن مسؤول جديد مع جميع التفاصيل (بيانات عامة + بيانات إدارية).
// - addcourse(arrayList<Course>& list) : إضافة كورس جديد إلى النظام.
// - deletcourse(arrayList<Course>& list, string coursecode) : حذف كورس معين من النظام باستخدام الكود.
// - PrintAllCourseInformation(arrayList<Course>& list) : طباعة معلومات كل الكورسات في النظام.
// - addteachers(arrayList<teachers>& list) : إضافة مدرس جديد إلى النظام.
// - Editteachers(arrayList<teachers>& teachersList, long long ID) : تعديل بيانات مدرس موجود.
// - Deleteteachers(arrayList<teachers>& teachersList, long long ID) : حذف مدرس من النظام.
// - Searchteachers(arrayList<teachers>& teachersList, long long ID) : البحث عن مدرس معين.
// - PrintAllteachersInformation(arrayList<teachers>& teachersList) : عرض معلومات كل المدرسين.
// - AddStudent(arrayList<students>& list) : إضافة طالب جديد إلى النظام.
// - EditStudent(arrayList<students>& studentsList, long long ID) : تعديل بيانات طالب موجود.
// - DeleteStudent(arrayList<students>& studentsList, long long ID) : حذف طالب.
// - SearchStudent(arrayList<students>& studentsList, long long ID) : البحث عن طالب معين.
// - PrintAllStudentInformation(arrayList<students>& studentsList) : عرض كل معلومات الطلاب.
// - RegisterStudentinCourse(arrayList<students>& studentsList, long long ID, arrayList<Course>& listC, string courseid) : تسجيل طالب في كورس.
// - UnRegisterStudentinCourse(arrayList<students>& studentsList, long long ID, arrayList<Course>& listC, string courseid) : إلغاء تسجيل الطالب من كورس.
// - StudentRegistrationListForaCourse(arrayList<Course>& listC, string& courseid, Course& c1) : عرض قائمة الطلاب المسجلين لكورس معين.
// - StudentUnRegistrationListForaCourse(arrayList<Course>& listC, string& courseid, Course& c1, students& s1) : إزالة طالب من قائمة الكورس.
// - ShowStudentSCourses(arrayList<students>& studentsList, long long ID, arrayList<Course>& listC) : عرض كورسات طالب معين.
// - ShowCourseSStudents(arrayList<Course>& listC, string& courseid, arrayList<students>& studentsList) : عرض الطلاب المسجلين في كورس معين.
// - EnrollmentStatistics(arrayList<students>& studentsList, arrayList<teachers>& teachersList, arrayList<Course>& listC) : عرض إحصائيات التسجيل.
// - StudentTranscript(arrayList<students>& studentsList, long long ID, arrayList<Course>& listC) : عرض كشف علامات طالب.
// - addComplaint(const Complaint& complaint) : إضافة شكوى جديدة.
// - viewComplaints() : عرض جميع الشكاوى.
// - getComplaints() : الحصول على جميع الشكاوى.
// - SaveToFile(ofstream& out) const : حفظ بيانات المسؤول في ملف.
// - LoadFromFileLine(const string& line) : تحميل بيانات المسؤول من سطر نصي.
//
// الاستخدام داخل المشروع:
// كلاس Admin مسؤول عن إدارة كل شيء يتعلق بالجامعة من ناحية إدارة الكورسات، المدرسين، الطلاب، الشكاوى، والإحصائيات.
// يمكنه إنشاء وتعديل وحذف الكورسات، إدارة تسجيل الطلاب، تعديل بيانات المدرسين، والاطلاع على كل الشكاوى المقدمة.
//
// الميزة: هذا الكلاس يسمح بفصل الدور الإداري عن المدرسين والطلاب ويجمع كل العمليات الإدارية في مكان واحد.
// =====================================================================================
*/
class Admin :public person {
	string academicRank;
	double salary;
	string officeHours;
	int NumberOfHolidays;
	static vector<Complaint> Complaints;
public:
	Admin();
	Admin(string name, char gender, string dateOfBirth, string nationality, string bloodType, string address, string joinData, string email, string phoneNumber, string password, string college, string Department, string major, string academicRank, double salary, string officeHours, int NumberOfHolidays);
	void addcourse(arrayList<Course>& list);
	void deletcourse(arrayList<Course>& list, string coursecode);
	void PrintAllCourseInformation(arrayList<Course>& list);
	void addteachers(arrayList<teachers>& list);
	void AddStudent(arrayList<students>& list);
	void EditStudent(arrayList<students>& studentsList, long long ID);
	void DeleteStudent(arrayList<students>& studentsList, long long ID);
	//Search Student
	void SearchStudent(arrayList<students>& studentsList, long long ID);
	void PrintAllStudentInformation(arrayList<students>& studentsList);
	void editcourse(arrayList<Course>& list, string coursecode);
	void Editteachers(arrayList<teachers>& teachersList, long long ID);
	void Deleteteachers(arrayList<teachers>& teachersList, long long ID);
	void Searchteachers(arrayList<teachers>& teachersList, long long ID);
	void PrintAllteachersInformation(arrayList<teachers>& teachersList);
	void RegisterStudentinCourse(arrayList<students>& studentsList, long long ID, arrayList<Course>& listC, string courseid);
	void UnRegisterStudentinCourse(arrayList<students>& studentsList, long long ID, arrayList<Course>& listC, string courseid);
	void StudentRegistrationListForaCourse(arrayList<Course>& listC, string& courseid, Course& c1);
	void StudentUnRegistrationListForaCourse(arrayList<Course>& listC, string& courseid, Course& c1, students& s1);
	void ShowStudentSCourses(arrayList<students>& studentsList, long long ID, arrayList<Course>& listC);
	void ShowCourseSStudents(arrayList<Course>& listC, string& courseid, arrayList<students>& studentsList);
	void EnrollmentStatistics(arrayList<students>& studentsList, arrayList<teachers>& teachersList, arrayList<Course>& listC);
	void StudentTranscript(arrayList<students>& studentsList, long long ID, arrayList<Course>& listC);
	void viewComplaints();
	void setcomplaints(Complaint complaints);
	static vector<Complaint>& getcomplaint();
	void SaveToFile(ofstream& out) const;
	bool LoadFromFileLine(const string& line);

	// دوال للتعامل مع الشكاوى
	void addComplaint(const Complaint& complaint);
	void viewComplaints() const;
	vector<Complaint> getComplaints() const;
	void Clear();
};


/*
================================================================================
الدوال المساعدة (Helper Functions) - واجهة المستخدم وإدارة النظام
================================================================================

1. دوال واجهة المستخدم (User Interface Functions):
--------------------------------------------------------------------------------
void showStudentPortal();
	الوصف: يعرض واجهة المستخدم الخاصة بالطالب مع خيارات القائمة.

void showTeacherPortal();
	الوصف: يعرض واجهة المستخدم الخاصة بالمعلم مع خيارات القائمة.

void showAdminPortal();
	الوصف: يعرض واجهة المستخدم الخاصة بالإداري مع خيارات القائمة.

void StudentManagement();
	الوصف: يعرض قائمة إدارة الطلاب في واجهة الإداري.

void CourseManagement();
	الوصف: يعرض قائمة إدارة المقررات في واجهة الإداري.

void RegistrationMenu();
	الوصف: يعرض قائمة التسجيل في المقررات في واجهة الإداري.

void GradesManagementMenu();
	الوصف: يعرض قائمة إدارة الدرجات في واجهة الإداري.

void ShowReportsMenuAdmin();
	الوصف: يعرض قائمة التقارير في واجهة الإداري.

void showAuthMenu();
	الوصف: يعرض قائمة المصادقة (تسجيل الدخول/إنشاء حساب).

void showLoginScreen();
	الوصف: يعرض شاشة تسجيل الدخول الرئيسية.

2. دوال إدخال البيانات (Input Functions):
--------------------------------------------------------------------------------
void loginScreen(long long& id, string& password);
	الوصف: يعرض واجهة إدخال بيانات تسجيل الدخول ويخزنها في المتغيرات.

void RegisterStudentInCourseUI(string& courseid);
	الوصف: يعرض واجهة إدخال رمز المقرر لتسجيل الطالب.

void EditACourseUI(string& courseid);
	الوصف: يعرض واجهة إدخال رمز المقرر لتعديله.

void DeleteAspecificCourseUI(string& courseid);
	الوصف: يعرض واجهة إدخال رمز المقرر لحذفه.

void EnterAspecificStudentsID(int& id);
	الوصف: يعرض واجهة إدخال رقم الطالب لتعديل بياناته.

void RegisterAspecificStudentsForCourseID(int& id);
	الوصف: يعرض واجهة إدخال رقم الطالب لتسجيله في مقرر.

void UnRegisterAspecificStudentsForCourseID(int& id);
	الوصف: يعرض واجهة إدخال رقم الطالب لإلغاء تسجيله من مقرر.

void ShowStudentsCoursesID(int& id);
	الوصف: يعرض واجهة إدخال رقم الطالب لعرض مقرراته.

void ShowCoursesStudentsID(string& courseid);
	الوصف: يعرض واجهة إدخال رمز المقرر لعرض الطلاب المسجلين فيه.

void DeleteAspecificStudentsID(int& id);
	الوصف: يعرض واجهة إدخال رقم الطالب لحذفه.

void SearchAspecificStudentsID(int& id);
	الوصف: يعرض واجهة إدخال رقم الطالب للبحث عنه.

void EnterAStudentTranscriptID(int& id);
	الوصف: يعرض واجهة إدخال رقم الطالب لعرض سجله الأكاديمي.

3. دوال إدارة الحسابات (Account Management Functions):
--------------------------------------------------------------------------------
void CreateStudentAccount(arrayList<students>& studentsList);
	الوصف: ينشئ حساب طالب جديد ويضيفه إلى القائمة.

void CreateTeacherAccount(arrayList<teachers>& teachersList);
	الوصف: ينشئ حساب معلم جديد ويضيفه إلى القائمة.

4. دوال البحث والبحث (Search and Lookup Functions):
--------------------------------------------------------------------------------
int serchstudentByID(arrayList<students>& list, int id);
	الوصف: يبحث عن طالب برقمه الجامعي ويعيد موقعه في القائمة.

int serchteacherByID(arrayList<teachers>& list, int id);
	الوصف: يبحث عن معلم برقمه الجامعي ويعيد موقعه في القائمة.

int serchCourseByID(arrayList<Course>& list, string id);
	الوصف: يبحث عن مقرر برمزه ويعيد موقعه في القائمة.

5. دوال المساعدة العامة (General Utility Functions):
--------------------------------------------------------------------------------
int generateRandom6Digit();
	الوصف: يولد رقمًا عشوائيًا مكونًا من 6 أرقام (لرقم الهوية).

long long TotalRegistrations(arrayList<Course>& listC);
	الوصف: يحسب العدد الإجمالي للتسجيلات في جميع المقررات.

6. دوال إدارة الملفات (File Management Functions):
--------------------------------------------------------------------------------
void SaveStudentsToFile(arrayList<students>& filelist, const string& filename);
	الوصف: يحفظ قائمة الطلاب إلى ملف.

void LoadStudentsFromFile(arrayList<students>& filelist, const string& filename);
	الوصف: يحمل قائمة الطلاب من ملف.

void SaveTeachersToFile(arrayList<teachers>& filelist, const string& filename);
	الوصف: يحفظ قائمة المعلمين إلى ملف.

void LoadTeachersFromFile(arrayList<teachers>& filelist, const string& filename);
	الوصف: يحمل قائمة المعلمين من ملف.

void SaveCoursesToFile(arrayList<Course>& filelist, const string& filename);
	الوصف: يحفظ قائمة المقررات إلى ملف.

void LoadCoursesFromFile(arrayList<Course>& filelist, const string& filename);
	الوصف: يحمل قائمة المقررات من ملف.

void SaveAdminToFile(arrayList<Admin>& filelist, const string& filename);
	الوصف: يحفظ قائمة الإداريين إلى ملف.

void LoadAdminFromFile(arrayList<Admin>& filelist, const string& filename);
	الوصف: يحمل قائمة الإداريين من ملف.

7. دوال إدارة الدرجات (Grades Management Functions):
--------------------------------------------------------------------------------
void addgread(arrayList<Course>& courseslist, arrayList<students>& studantlist);
	الوصف: يضيف أو يعدل درجات الطلاب في مقرر معين.

void ShowStudentGrades(arrayList<Course>& courseslist, arrayList<students>& studantlist);
	الوصف: يعرض درجات الطلاب في مقرر معين.

void CalculatethesetsemesterGPA(arrayList<students>& studentlist, arrayList<Course>& courselist);
	الوصف: يحسب المعدل الفصلي والتراكمي للطلاب.

================================================================================
*/
void showStudentPortal();
void showTeacherPortal();
void showAdminPortal();
void StudentManagement();
void CourseManagement();
void RegistrationMenu();
void GradesManagementMenu();
void ShowReportsMenuAdmin();
void loginScreen(long long& id, string& password);
void RegisterStudentInCourseUI(string& courseid);
void EditACourseUI(string& courseid);
void DeleteAspecificCourseUI(string& courseid);
void EnterAspecificStudentsID(int& id);
void RegisterAspecificStudentsForCourseID(int& id);
void UnRegisterAspecificStudentsForCourseID(int& id);
void ShowStudentsCoursesID(int& id);
void ShowCoursesStudentsID(string& courseid);
void DeleteAspecificStudentsID(int& id);
void SearchAspecificStudentsID(int& id);
void showAuthMenu();
void showLoginScreen();
void CreateStudentAccount(arrayList<students>& studentsList);
void CreateTeacherAccount(arrayList<teachers>& teachersList);
int serchstudentByID(arrayList<students>& list, int id);
int serchteacherByID(arrayList<teachers>& list, int id);
int serchCourseByID(arrayList<Course>& list, string id);
int generateRandom6Digit();
void SaveStudentsToFile(arrayList<students>& filelist, const string& filename);
void LoadStudentsFromFile(arrayList<students>& filelist, const string& filename);
void SaveTeachersToFile(arrayList<teachers>& filelist, const string& filename);
void LoadTeachersFromFile(arrayList<teachers>& filelist, const string& filename);
void SaveCoursesToFile(arrayList<Course>& filelist, const string& filename);
void LoadCoursesFromFile(arrayList<Course>& filelist, const string& filename);
void addGrade(arrayList<Course>& courseslist, arrayList<students>& studentlist);
void  ShowStudentGrades(arrayList<Course>& courseslist, arrayList<students>& studantlist);
long long TotalRegistrations(arrayList<Course>& listC);
void EnterAStudentTranscriptID(int& id);
void CalculatethesetsemesterGPA(arrayList<students>& studentlist, arrayList<Course>& courselist);
void SaveAdminToFile(arrayList<Admin>& filelist, const string& filename);
void LoadAdminFromFile(arrayList<Admin>& filelist, const string& filename);
int serchAdminByID(arrayList<Admin>& list, int id);
void CreateAdminAccount(arrayList<Admin>& adminList);
template<class elemtype>
arrayList<elemtype>::arrayList() {
	maxList = 1000;
	length = 0;
	list = new elemtype[maxList];
}
template<class elemtype>
arrayList<elemtype>::arrayList(long long maxList) {
	length = 0;
	if (maxList < 0) {
		this->maxList = 100;
		cout << "The size of the array has become 100 Due to the entry of a smaller size than" << endl;
	}
	else {
		this->maxList = maxList;
		cout << "The size of the array has become " << maxList << endl;
	}
	list = new elemtype[this->maxList];
}
template<class elemtype>
arrayList<elemtype>::arrayList(arrayList<elemtype>& otherList) {
	length = otherList.length;
	maxList = otherList.maxList;
	list = new elemtype[maxList];
	for (int i = 0; i < length; i++)
		list[i] = otherList.list[i];
}
template<class elemtype>
arrayList<elemtype>& arrayList<elemtype>::operator=(arrayList<elemtype>& otherList) {
	if (&otherList != this) {
		delete[] list;
		length = otherList.length;
		maxList = otherList.maxList;
		list = new elemtype[maxList];
		for (int i = 0; i < length; i++)
			list[i] = otherList.list[i];
	}
	return *this;
}
template<class elemtype>
void arrayList<elemtype>::insertAT(long long location, elemtype& value) {
	if (location < 0 || location > length) {
		cout << "out the rang" << endl;
		return;
	}
	if (length >= maxList) {
		cout << "the list is full" << endl;
		return;
	}
	for (int i = length; i > location; i--) {
		list[i] = list[i - 1];
	}
	list[location] = value;
	length++;
}
template<class elemtype>
void arrayList<elemtype>::insertEnd(elemtype& value) {
	if (length >= maxList) {
		cout << "the list is full" << endl;
		return;
	}
	list[length++] = value;
}
template<class elemtype>
void arrayList<elemtype>::removeAT(long long location) {
	if (location < 0 || location >= length) {
		cout << "out the rang" << endl;
		return;
	}
	for (int i = location; i < length - 1; i++)
		list[i] = list[i + 1];
	length--;
}
template<class elemtype>
void arrayList<elemtype>::retrieveAT(long long location, elemtype& value) {
	if (location < 0 || location >= length) {
		cout << "out the rang" << endl;
		return;
	}
	value = list[location];
}
template<class elemtype>
void arrayList<elemtype>::replaceAt(long long location, elemtype& value) {
	if (location < 0 || location >= length) {
		cout << "out the rang" << endl;
		return;
	}
	list[location] = value;
}
template<class elemtype>
void arrayList<elemtype>::print() {
	cout << "name the all student" << endl;
	for (int i = 0; i < length; i++)
		cout << i + 1 << ") " << list[i] << endl;
}
template<class elemtype>
bool arrayList<elemtype>::search(long long ID)const {
	for (int i = 0; i < length; i++)
		if (list[i] == ID) return true;
	return false;
}
template<class elemtype>
void arrayList<elemtype>::clearAT() {
	length = 0;
}
template<class elemtype>
long long arrayList<elemtype>::getLength() {
	return length;
}
template<class elemtype>
void arrayList<elemtype>::resize(long long maxSize) {
	maxList = maxSize;
}
template<class elemtype>
elemtype& arrayList<elemtype>::opp(long long location) {
	return list[location];
}
template<class elemtype>
arrayList<elemtype>::~arrayList() {
	delete[] list;
	list = nullptr;
}
