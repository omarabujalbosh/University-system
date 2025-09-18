/*
================================================================================
مشروع نظام إدارة الجامعة (JUST University Management System)
تم تطويره بواسطة فريق JUST Logic Team:
1. عمر أبو جلبوش
2. ينال عابد
3. محمد هناندة

هذا المشروع هو نظام متكامل لإدارة العمليات الأكاديمية في الجامعة، ويشمل:
- إدارة بيانات الطلاب والمعلمين والإداريين
- إدارة المقررات الدراسية والتسجيل فيها
- نظام الدرجات والتقييم الأكاديمي
- نظام الشكاوى والتقارير
- إدارة الخطط الدراسية والسجلات الأكاديمية

المميزات الرئيسية للنظام:
1. واجهة مستخدم ملونة وسهلة الاستخدام
2. نظام مصادقة آمن للمستخدمين بأنواعهم المختلفة
3. إدارة كاملة للبيانات الأكاديمية (طلاب، معلمين، مقررات)
4. نظام تسجيل المقررات الإلكتروني
5. نظام العلامات والتقييم الآلي
6. إمكانية حفظ واسترجاع البيانات من/إلى الملفات
7. إحصائيات وتقارير عن الأداء الأكاديمي
8. نظام شكاوى ومقترحات

تم بناء النظام باستخدام:
- لغة C++ مع التوافق مع معيار C++11 أو أحدث
- هياكل البيانات مثل القوائم والمتجهات والخريطة
- برمجة كائنية التوجه (OOP) مع استخدام الوراثة
- قوالب (Templates) للهياكل العامة
- إدارة الملفات للتخزين الدائم للبيانات

================================================================================
*/
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
int main() {
	srand(time(nullptr));
	arrayList<students> studentsList;
	arrayList<teachers> teachersList;
	arrayList<Course> coursesList;
	arrayList<Admin> AdminList;
	bool stope = true;
	students s1;
	teachers t1;
	string courseid;
	LoadStudentsFromFile(studentsList, "students.txt");
	LoadTeachersFromFile(teachersList, "teachers.txt");
	LoadCoursesFromFile(coursesList, "courses.txt");
	LoadAdminFromFile(AdminList, "Admin.txt");

	while (stope) {
		showLoginScreen();
		int choose;
		cin >> choose;
		// //هاي لما نختار خيار الطالب  
		if (choose == 1) {
			system("cls");
			bool stope = true;
			while (stope) {
				showAuthMenu();
				int choose;
				cin >> choose;
				if (choose == 1) {
					system("cls");
					string password;
					long long id;
					loginScreen(id, password);
					long long location;
					location = serchstudentByID(studentsList, id);
					if (location > -1) {
						s1 = studentsList.opp(location);
						if (s1.getPassword() == password) {
							system("cls");
							cout << "\033[38;5;10mThe login process was completed successfully...\033[0m" << endl;
							bool stope = true;
							while (stope) {
								showStudentPortal();
								int choose;
								cin >> choose;
								system("cls");
								switch (choose) {
								case 1:
									system("cls");
									RegisterStudentInCourseUI(courseid);
									s1.Jointhecourse(coursesList, studentsList, courseid, s1.getID(), s1);
									break;
								case 2:
									system("cls");
									RegisterStudentInCourseUI(courseid);
									s1.UnregisterfromCourse(coursesList, studentsList, courseid, s1.getID(), s1);
									break;
								case 3:
									system("cls");
									s1.ViewMyCourses(coursesList);
									break;
								case 4:
									system("cls");
									s1.Showgrades(coursesList);
									break;
								case 5:
									system("cls");
									s1.ViewMyProfile();
									break;
								case 6:
									system("cls");
									s1.EditMyPersonalInfo(studentsList, s1);
									break;
								case 7:
									system("cls");
									s1.submitComplaint();
									break;
								case 8:
									system("cls");
									s1.PrintRegisteredCourses(coursesList);
									break;
								case 9:
									system("cls");
									stope = false;
									break;
								default:
									system("cls");
									cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
									break;
								}
							}
						}
						else {
							system("cls");
							cout << "\033[31mThe password you entered is incorrect....\033[0m" << endl;
						}
					}

				}
				else if (choose == 2) {
					system("cls");
					CreateStudentAccount(studentsList);
					system("cls");
					cout << "\033[92mAccount Created Successfully!\033[0m\n";
					long long length = studentsList.getLength();
					s1 = studentsList.opp(length - 1);
					cout << "\033[1;33mNew account ID number: " << s1.getID() << "\n";
					cout << "\033[1;33mNew account password: " << s1.getPassword() << endl;
				}
				else if (choose == 3) {
					system("cls");
					break;
				}

				else if (choose != 1 && choose != 2 && choose != 3) {
					system("cls");
					cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl << endl;
				}
			}
		}
		//هاي لما نختار خيار المعلم 
		else if (choose == 2) {
			system("cls");
			bool stope = true;
			while (stope) {
				showAuthMenu();
				int choose;
				cin >> choose;
				if (choose == 1) {
					system("cls");
					string password;
					long long id;
					loginScreen(id, password);
					long long location;
					location = serchteacherByID(teachersList, id);
					if (location > -1) {
						t1 = teachersList.opp(location);
						if (t1.getPassword() == password) {
							system("cls");
							cout << "\033[38;5;10mThe login process was completed successfully...\033[0m" << endl;
							bool stope = true;
							while (stope) {
								showTeacherPortal();
								int choose;
								cin >> choose;
								system("cls");
								switch (choose) {
								case 1:
									system("cls");
									t1.ViewMyCourses(coursesList);
									break;
								case 2:
									system("cls");
									t1.StudentsOfMyCourses(coursesList, studentsList);
									break;
								case 3:
									system("cls");
									t1.SubmitComplaint();
									break;

								case 4:
									system("cls");
									t1.EditMyProfile(teachersList, id, t1);
									break;
								case 5:
									system("cls");
									stope = false;
									break;
								default:
									system("cls");
									cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
									break;
								}

							}
						}
						else {
							system("cls");
							cout << "\033[31mThe password you entered is incorrect....\033[0m" << endl;
						}
					}

				}
				else if (choose == 2) {
					system("cls");
					CreateTeacherAccount(teachersList);
					system("cls");
					cout << "\033[92mAccount Created Successfully!\033[0m\n";
					long long length = teachersList.getLength();
					t1 = teachersList.opp(length - 1);
					cout << "\033[1;33mNew account ID number: " << t1.getID() << "\n";
					cout << "\033[1;33mNew account password: " << t1.getPassword() << endl;
				}
				else if (choose == 3) {
					system("cls");
					break;
				}
				else if (choose != 1 && choose != 2 && choose != 3) {
					system("cls");
					cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl << endl;
				}
			}
		}
		//هاي لما نختار خيار ادمن 
		else if (choose == 3) {
			system("cls");
			bool stope = true;
			while (stope) {
				showAuthMenu();
				int choose;
				cin >> choose;
				if (choose == 1) {
					system("cls");
					string password;
					long long id;
					loginScreen(id, password);
					long long location;
					location = serchAdminByID(AdminList, id);
					if (location > -1) {
						Admin a = AdminList.opp(location);
						if (a.getPassword() == password) {
							system("cls");
							cout << "\033[38;5;10mThe login process was completed successfully...\033[0m" << endl;
							bool stope = true;
							while (stope) {
								showAdminPortal();
								int choose;
								cin >> choose;
								system("cls");
								bool stope1 = true;
								int ids;
								switch (choose) {
								case 1:
									while (stope1)
									{
										StudentManagement();
										cin >> choose;
										switch (choose) {
										case 1:
											system("cls");
											a.AddStudent(studentsList);
											break;
										case 2:
											system("cls");
											EnterAspecificStudentsID(ids);
											system("cls");
											a.EditStudent(studentsList, ids);
											break;
										case 3:
											system("cls");
											DeleteAspecificStudentsID(ids);
											a.DeleteStudent(studentsList, ids);
											break;
										case 4:
											system("cls");
											SearchAspecificStudentsID(ids);
											a.SearchStudent(studentsList, ids);
											break;
										case 5:
											system("cls");
											a.PrintAllStudentInformation(studentsList);
											break;
										case 6:
											system("cls");
											stope1 = false;
											break;
										default:
											system("cls");
											cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
											break;
										}

									}
									break;
								case 2:
									while (stope1)
									{
										CourseManagement();
										cin >> choose;
										switch (choose) {
										case 1:
											system("cls");
											a.addcourse(coursesList);
											break;
										case 2:
											system("cls");
											EditACourseUI(courseid);
											system("cls");
											a.editcourse(coursesList, courseid);
											break;
										case 3:
											system("cls");
											DeleteAspecificCourseUI(courseid);
											system("cls");
											a.deletcourse(coursesList, courseid);

											break;
										case 4:
											system("cls");
											a.PrintAllCourseInformation(coursesList);
											break;
										case 5:
											system("cls");
											stope1 = false;
											break;
										default:
											system("cls");
											cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
											break;
										}
									}
									break;
								case 3:
									while (stope1)
									{
										RegistrationMenu();
										cin >> choose;
										switch (choose) {
										case 1:
											system("cls");
											RegisterAspecificStudentsForCourseID(ids);
											system("cls");
											a.RegisterStudentinCourse(studentsList, ids, coursesList, courseid);
											break;
										case 2:
											system("cls");
											UnRegisterAspecificStudentsForCourseID(ids);
											system("cls");
											a.UnRegisterStudentinCourse(studentsList, ids, coursesList, courseid);
											break;
										case 3:
											system("cls");
											ShowStudentsCoursesID(ids);
											system("cls");
											a.ShowStudentSCourses(studentsList, ids, coursesList);
											break;
										case 4:
											system("cls");
											ShowCoursesStudentsID(courseid);
											system("cls");
											a.ShowCourseSStudents(coursesList, courseid, studentsList);
											break;
										case 5:
											system("cls");
											stope1 = false;
											break;
										default:
											system("cls");
											cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
											break;
										}
									}
									break;
								case 4:
									while (stope1)
									{
										GradesManagementMenu();
										cin >> choose;
										switch (choose) {
										case 1:
											system("cls");
											addGrade(coursesList, studentsList);
											break;
										case 2:
											system("cls");
											ShowStudentGrades(coursesList, studentsList);
											break;
										case 3:
											system("cls");
											stope1 = false;
											break;
										default:
											system("cls");
											cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
											break;
										}
									}
									break;
								case 5:
									while (stope1)
									{
										ShowReportsMenuAdmin();
										cin >> choose;
										switch (choose) {
										case 1:
											system("cls");
											a.viewComplaints();
											break;
										case 2:
											system("cls");
											a.Clear();
											break;
										case 3:
											system("cls");
											a.EnrollmentStatistics(studentsList, teachersList, coursesList);
											break;
										case 4:
											system("cls");
											EnterAStudentTranscriptID(ids);
											system("cls");
											a.StudentTranscript(studentsList, ids, coursesList);
											break;
										case 5:
											system("cls");
											stope1 = false;
											break;
										default:
											system("cls");
											cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
											break;
										}
									}
									break;
								case 6:
									system("cls");
									stope = false;
									break;
								default:
									system("cls");
									cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl;
									break;
								}
							}
						}
						else {
							cout << "\033[31mThe password you entered is incorrect....\033[0m" << endl;
						}
					}

				}

				else if (choose == 2) {
					system("cls");
					CreateAdminAccount(AdminList);
					system("cls");
					cout << "\033[92mAccount Created Successfully!\033[0m\n";
					long long length = AdminList.getLength();
					Admin a = AdminList.opp(length - 1);
					cout << "\033[1;33mNew account ID number: " << a.getID() << "\n";
					cout << "\033[1;33mNew account password: " << a.getPassword() << endl;
				}
				else if (choose == 3) {
					system("cls");
					break;
				}
				else if (choose != 1 && choose != 2 && choose != 3) {
					system("cls");
					cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl << endl;
				}
			}
		}
		else if (choose == 4) {
			system("cls");
			cout << "\033[92mThe logout process was completed successfully.\033[0m\n";
			break;
		}
		else if (choose != 1 && choose != 2 && choose != 3 && choose != 4) {
			system("cls");
			cout << "\033[31mYou have entered an incorrect number. Please check it...\033[0m" << endl << endl;
		}
	}
	SaveStudentsToFile(studentsList, "students.txt");
	SaveTeachersToFile(teachersList, "teachers.txt");
	SaveCoursesToFile(coursesList, "courses.txt");
	SaveAdminToFile(AdminList, "Admin.txt");
}

