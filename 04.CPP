#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<fstream.h>

class ExamSystem {
private:
    char username[20];
    char password[20];
    char filename[20];

    struct Student {
        int rollNo;
        char name[30];
        float marks[3];  // marks for 3 subjects
        char grade;
        int active;
    };
    
    Student students[10];
    int totalStudents;

    void loadStudents() {
        ifstream file(filename);
        if(!file) {
            totalStudents = 0;
            return;
        }
        
        totalStudents = 0;
        char line[100];
        while(file.getline(line, 100) && totalStudents < 10) {
            sscanf(line, "%d|%[^|]|%f|%f|%f|%c|%d", 
                &students[totalStudents].rollNo,
                students[totalStudents].name,
                &students[totalStudents].marks[0],
                &students[totalStudents].marks[1],
                &students[totalStudents].marks[2],
                &students[totalStudents].grade,
                &students[totalStudents].active
            );
            if(students[totalStudents].active == 1) {
                totalStudents++;
            }
        }
        file.close();
    }

    void saveStudents() {
        ofstream file(filename);
        if(!file) {
            gotoxy(20, 20);
            textcolor(LIGHTRED);
            cprintf("Error: Cannot open file for writing!");
            getch();
            return;
        }
        
        for(int i = 0; i < 10; i++) {
            if(students[i].active == 1) {
                file << students[i].rollNo << "|"
                     << students[i].name << "|"
                     << students[i].marks[0] << "|"
                     << students[i].marks[1] << "|"
                     << students[i].marks[2] << "|"
                     << students[i].grade << "|"
                     << students[i].active << endl;
            }
        }
        file.close();
    }

    char calculateGrade(float average) {
        if(average >= 90) return 'A';
        else if(average >= 80) return 'B';
        else if(average >= 70) return 'C';
        else if(average >= 60) return 'D';
        else return 'F';
    }

    void drawBox(int x1, int y1, int x2, int y2) {
        int i, j;
        for(i=x1; i<=x2; i++) {
            gotoxy(i, y1);
            textcolor(LIGHTGREEN);
            cprintf("-");
            gotoxy(i, y2);
            cprintf("-");
        }
        for(j=y1; j<=y2; j++) {
            gotoxy(x1, j);
            textcolor(LIGHTGREEN);
            cprintf("|");
            gotoxy(x2, j);
            cprintf("|");
        }
        gotoxy(x1, y1); cprintf("+");
        gotoxy(x2, y1); cprintf("+");
        gotoxy(x1, y2); cprintf("+");
        gotoxy(x2, y2); cprintf("+");
    }

public:
    ExamSystem() {
	strcpy(username, "aliya");
	strcpy(password, "4405");
        strcpy(filename, "aliya.txt");
        totalStudents = 0;
        for(int i = 0; i < 10; i++) {
            students[i].active = 0;
            students[i].rollNo = i + 1;
        }
        loadStudents();
    }

    void checkLogin() {
        char inputUser[20], inputPass[20];
        while(1) {
            clrscr();
            textbackground(BLACK);
            clrscr();
            
            drawBox(15, 5, 65, 15);
            drawBox(25, 3, 55, 5);
            
            gotoxy(30, 4);
            textcolor(YELLOW);
            cprintf(" EXAMINATION SYSTEM ");
            
            textcolor(WHITE);
            gotoxy(20, 8);
            cprintf("Enter Username: ");
            gotoxy(35, 8);
            textcolor(LIGHTCYAN);
            fflush(stdin);
            gets(inputUser);
            
            gotoxy(20, 11);
            textcolor(WHITE);
            cprintf("Enter Password: ");
            gotoxy(35, 11);
            textcolor(LIGHTCYAN);
            fflush(stdin);
            gets(inputPass);
            
            if(strcmp(inputUser, username) == 0 && strcmp(inputPass, password) == 0) {
                textcolor(LIGHTGREEN);
                gotoxy(20, 17);
                cprintf("LOGIN SUCCESSFUL!");
                getch();
                break;
            } else {
                textcolor(LIGHTRED);
                gotoxy(20, 17);
                cprintf("INVALID USERNAME OR PASSWORD!");
                getch();
            }
        }
    }

    void addStudent() {
        clrscr();
        if(totalStudents >= 10) {
            textcolor(LIGHTRED);
            gotoxy(20, 10);
            cprintf("Maximum student limit reached!");
            getch();
            return;
        }

        drawBox(15, 5, 65, 20);
        textcolor(YELLOW);
        gotoxy(30, 3);
        cprintf("ADD NEW STUDENT");
        
        textcolor(WHITE);
        gotoxy(20, 7);
        cprintf("Enter Name: ");
        fflush(stdin);
        gets(students[totalStudents].name);
        
        gotoxy(20, 9);
        cprintf("Enter marks for Subject 1: ");
        scanf("%f", &students[totalStudents].marks[0]);
        
        gotoxy(20, 11);
        cprintf("Enter marks for Subject 2: ");
        scanf("%f", &students[totalStudents].marks[1]);
        
        gotoxy(20, 13);
        cprintf("Enter marks for Subject 3: ");
        scanf("%f", &students[totalStudents].marks[2]);
        
        float average = (students[totalStudents].marks[0] + 
                        students[totalStudents].marks[1] + 
                        students[totalStudents].marks[2]) / 3;
        students[totalStudents].grade = calculateGrade(average);
        students[totalStudents].active = 1;
        
        saveStudents();
        totalStudents++;
        
        textcolor(LIGHTGREEN);
        gotoxy(20, 17);
        cprintf("Student Added Successfully!");
        getch();
    }

    void showResults() {
        clrscr();
        if(totalStudents == 0) {
            textcolor(LIGHTRED);
            gotoxy(25, 10);
            cprintf("No students found!");
            getch();
            return;
        }

        textcolor(YELLOW);
        gotoxy(30, 2);
        cprintf("EXAMINATION RESULTS");

        drawBox(5, 4, 75, totalStudents + 8);

        textcolor(LIGHTGREEN);
        gotoxy(7, 5);
        cprintf("ROLL");
        gotoxy(13, 5);
        cprintf("NAME");
        gotoxy(30, 5);
        cprintf("SUB1");
        gotoxy(40, 5);
        cprintf("SUB2");
        gotoxy(50, 5);
        cprintf("SUB3");
        gotoxy(60, 5);
        cprintf("AVG");
        gotoxy(70, 5);
        cprintf("GRADE");

        int currentY = 7;
        for(int i = 0; i < totalStudents; i++) {
            float avg = (students[i].marks[0] + students[i].marks[1] + 
                        students[i].marks[2]) / 3;
            
            textcolor(WHITE);
            gotoxy(7, currentY);
            cprintf("%d", students[i].rollNo);
            gotoxy(13, currentY);
            cprintf("%s", students[i].name);
            gotoxy(30, currentY);
            cprintf("%.1f", students[i].marks[0]);
            gotoxy(40, currentY);
            cprintf("%.1f", students[i].marks[1]);
            gotoxy(50, currentY);
            cprintf("%.1f", students[i].marks[2]);
            gotoxy(60, currentY);
            cprintf("%.1f", avg);
            gotoxy(70, currentY);
            cprintf("%c", students[i].grade);
            currentY++;
        }
        getch();
    }

    void searchStudent() {
        clrscr();
        if(totalStudents == 0) {
            textcolor(LIGHTRED);
            gotoxy(25, 10);
            cprintf("No students found!");
            getch();
            return;
        }

        int searchRoll;
        drawBox(15, 5, 65, 20);
        
        textcolor(YELLOW);
        gotoxy(30, 3);
        cprintf("SEARCH STUDENT");
        
        textcolor(WHITE);
        gotoxy(20, 7);
        cprintf("Enter Roll Number: ");
        scanf("%d", &searchRoll);
        
        int found = 0;
        for(int i = 0; i < totalStudents; i++) {
            if(students[i].rollNo == searchRoll) {
                float avg = (students[i].marks[0] + students[i].marks[1] + 
                           students[i].marks[2]) / 3;
                
                textcolor(LIGHTGREEN);
                gotoxy(20, 9);
                cprintf("Student Found!");
                textcolor(WHITE);
                gotoxy(20, 11);
                cprintf("Name: %s", students[i].name);
                gotoxy(20, 12);
                cprintf("Subject 1: %.1f", students[i].marks[0]);
                gotoxy(20, 13);
                cprintf("Subject 2: %.1f", students[i].marks[1]);
                gotoxy(20, 14);
                cprintf("Subject 3: %.1f", students[i].marks[2]);
                gotoxy(20, 15);
                cprintf("Average: %.1f", avg);
                gotoxy(20, 16);
                cprintf("Grade: %c", students[i].grade);
                found = 1;
                break;
            }
        }
        
        if(!found) {
            textcolor(LIGHTRED);
            gotoxy(20, 11);
            cprintf("Student not found!");
        }
        getch();
    }

    void deleteStudent() {
        clrscr();
        if(totalStudents == 0) {
            textcolor(LIGHTRED);
            gotoxy(25, 10);
            cprintf("No students to delete!");
            getch();
            return;
        }

        int deleteRoll;
        drawBox(15, 5, 65, 15);
        
        textcolor(YELLOW);
        gotoxy(30, 3);
        cprintf("DELETE STUDENT");
        
        textcolor(WHITE);
        gotoxy(20, 7);
        cprintf("Enter Roll Number to delete: ");
        scanf("%d", &deleteRoll);
        
        int found = 0;
        for(int i = 0; i < totalStudents; i++) {
            if(students[i].rollNo == deleteRoll) {
                char confirm;
                textcolor(LIGHTRED);
                gotoxy(20, 9);
                cprintf("Delete student %s? (Y/N): ", students[i].name);
                fflush(stdin);
                scanf("%c", &confirm);
                
                if(toupper(confirm) == 'Y') {
                    students[i].active = 0;
                    totalStudents--;
                    saveStudents();
                    textcolor(LIGHTGREEN);
                    gotoxy(20, 11);
                    cprintf("Student deleted successfully!");
                }
                found = 1;
                break;
            }
        }
        
        if(!found) {
            textcolor(LIGHTRED);
            gotoxy(20, 11);
            cprintf("Student not found!");
        }
        getch();
    }

    void menu() {
        int choice;
        do {
            clrscr();
            drawBox(25, 2, 55, 12);
            
            textcolor(YELLOW);
            gotoxy(32, 3);
            cprintf("EXAM SYSTEM MENU");
            
            textcolor(WHITE);
            gotoxy(30, 5);
            cprintf("1. Add Student");
            gotoxy(30, 6);
            cprintf("2. Show Results");
            gotoxy(30, 7);
            cprintf("3. Search Student");
            gotoxy(30, 8);
            cprintf("4. Delete Student");
            gotoxy(30, 9);
            cprintf("5. Exit");
            
            gotoxy(27, 14);
            cprintf("Enter Your Choice: ");
            scanf("%d", &choice);
            
            switch(choice) {
                case 1: addStudent(); break;
                case 2: showResults(); break;
                case 3: searchStudent(); break;
                case 4: deleteStudent(); break;
                case 5:
                    clrscr();
                    gotoxy(25, 12);
                    textcolor(YELLOW);
                    cprintf("Thank you for using the exam system!");
                    getch();
                    exit(0);
                default:
                    gotoxy(27, 16);
                    textcolor(LIGHTRED);
                    cprintf("Invalid Choice! Try again...");
                    getch();
            }
        } while(choice != 5);
    }
};

void main() {
    clrscr();
    ExamSystem e;
    e.checkLogin();
    e.menu();
    getch();
}