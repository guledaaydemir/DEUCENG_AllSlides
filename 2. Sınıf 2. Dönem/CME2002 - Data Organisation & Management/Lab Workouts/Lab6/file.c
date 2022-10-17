#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// includes for C Streams
#include <stdio.h>
// include for c strings
#include <string.h>
// Record to save file

struct _Student {
    int studentId;
    char studentName[7];
};

#define REC_SIZE sizeof(struct _Student)

typedef struct _Student Student;

void printStudentData(Student student);
void writeStudentsUsingLowLevelIO(Student *students, int studentcount, char *filename);
void readStudentsUsingLowLevelIO(char *filename);
void writeStudentsUsingCText(Student *students, int studentcount, char *filename);
void readStudentsUsingCText(char *filename);
void writeStudentsUsingCBin(Student *students, int studentcount, char *filename);
void readStudentsUsingCBin(char *filename);

int main(void) {
    Student students[7];
    students[0].studentId=1;
    strcpy(students[0].studentName, "Ali");
    students[1].studentId=2;
    strcpy(students[1].studentName, "Jale");
    students[2].studentId=3;
    strcpy(students[2].studentName, "Veli");
    students[3].studentId=4;
    strcpy(students[3].studentName, "Lale");
    students[4].studentId=5;
    strcpy(students[4].studentName, "Selami");
    students[5].studentId=6;
    strcpy(students[5].studentName, "Hale");
    students[6].studentId=7;
    strcpy(students[6].studentName, "Deniz");
    
    printf("\n==== LOW LEVEL FILE I/O =====\n");
    writeStudentsUsingLowLevelIO(students, 7, "low_level.dat");
    readStudentsUsingLowLevelIO("low_level.dat");
    
    printf("\n====== C TEXT STREAMS =======\n");
    writeStudentsUsingCText(students, 7, "c_text.dat");
    readStudentsUsingCText("c_text.dat");
    
    printf("\n===== C BINARY STREAMS ======\n");
    writeStudentsUsingCBin(students, 7, "c_bin.dat");
    readStudentsUsingCBin("c_bin.dat");
}

void printStudentData(Student student) {
    printf("Student Information\n");
    printf("ID: %d\n", student.studentId);
    printf("Name : %s\n", student.studentName);
}

void writeStudentsUsingLowLevelIO(Student *students, int studentcount, char *filename) {
    int fd = open(filename, O_WRONLY|O_TRUNC|O_CREAT);
    if(fd<0) {
        printf("Error while opening file!");
        return;
    }
    write(fd, students, REC_SIZE*studentcount);
    close(fd);
    chmod(filename, S_IRWXU);
}

void readStudentsUsingLowLevelIO(char *filename) {
    int fd = open(filename, O_RDONLY);
    if(fd<0) {
        printf("Error while opening file!");
        return;
    }
    Student data;
    while(read(fd,&data, REC_SIZE)>0) {
        printStudentData(data);
    }
    close(fd);
}

void writeStudentsUsingCText(Student *students, int studentcount, char *filename) {
    int i;
    FILE *fp = fopen(filename, "w");
    if(!fp) {
        printf("Could not open file!");
        return;
    }
    for(i=0;i<studentcount;i++) {
        fprintf(fp, "%s %d\n", students[i].studentName, students[i].studentId);
    }
    fclose(fp);
}

void readStudentsUsingCText(char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        printf("Could not open file!");
        return;
    }
    Student data;
    //...
    fclose(fp);
}

void writeStudentsUsingCBin(Student *students, int studentcount, char *filename) {
    FILE *fp = fopen(filename, "wb");
    if(!fp) {
        printf("Could not open file");
        return;
    }
    //...
    fclose(fp);
}
void readStudentsUsingCBin(char *filename) {
    FILE *fp = fopen(filename, "rb");
    Student data;
    if(!fp) {
        printf("Could not open file");
        return;
    }
    fread(&data, REC_SIZE, 1, fp);
    while(!feof(fp)) {
        printStudentData(data);
        fread(&data, REC_SIZE, 1, fp);
    }
    fclose(fp);
}
