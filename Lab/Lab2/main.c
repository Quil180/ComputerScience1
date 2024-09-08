#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

#define NAMEMAX 51

typedef struct student {
  char *lname; // this will require DMA to store a string
  int assignment;
  int finalExam;
  int total;
  int *quizzes; // this will require DMA to store quizzes
} student;

void release_memroy(student **st, int C, int N, int M) {
  for (int i = 0; i < C; i++) {
    for (int j = 0; j < N; j++) {
      free(st[i][j].lname); // first we free the lastname in the student
      free(st[i][j].quizzes); // then we free the quizzes in the students
    }
    free(st[i]); // freeing all the students in the course
  }
  free(st); // freeing all the courses
}

student **readCourses(int *C, int *N, int *M) { // the structure points to an array of courses that points towards an array of students that points to an array of quiz grades.
  int i = 0, j = 0;
  char lname[NAMEMAX];
  // getting the 3 numbers in the beginning of the structured input file.
  scanf("%d %d %d", C, N, M);

  // for loop for the amount of courses
  student **courses = (student **)calloc(*C, sizeof(student *)); // allocating the courses portion of the 2d array of students.
  for (i = 0; i < *C; i++) {
    courses[i] = (student *)calloc(*N, sizeof(student)); // allocating the student amount per course in the 2d array of students for loop for the amount of students
    for (j = 0; j < *N; j++) {
      int totals = 0;
      scanf("%s", lname); // gathers the name and the assignment data for the student.
      int lnamelength = strlen(lname) + 1;

      courses[i][j].lname = (char *)calloc(lnamelength, sizeof(char)); // allocating the memory of the student's lastname
      strcpy(courses[i][j].lname, lname); // copying the name to the student's name
      
      scanf("%d", &courses[i][j].assignment);
      totals += courses[i][j].assignment; // adding it to the total for the student


      courses[i][j].quizzes = (int *)calloc(*M, sizeof(int)); // allocating the memory for the number of quizzes's

      for (int m = 0; m < *M; m++) {
        scanf("%d", &courses[i][j].quizzes[m]); // assigning the quiz score.
        totals += courses[i][j].quizzes[m];
      }

      scanf("%d", &courses[i][j].finalExam);
      totals += courses[i][j].finalExam;

      courses[i][j].total = totals;
    }
  }

  return courses;
};

void printHighestTotal(student **student, int C, int N, int M) {
  int i, j, k, maxTotal = -1, maxI = -1, maxJ = -1;

  for (i = 0; i < C; i++) {
    for (j = 0; j < N; j++) {
      if (student[i][j].total > maxTotal) {
        maxTotal = student[i][j].total;
        maxI = i;
        maxJ = j;
      }
    }
  }

  printf("Name: %s\n", student[maxI][maxJ].lname);
  printf("Assignment: %d\n", student[maxI][maxJ].assignment);
  printf("Quizzes: ");
  for (int m = 0; m < M; m++) {
    printf("%d ", student[maxI][maxJ].quizzes[m]);
  }
  printf("\n");
  printf("Final exam: %d\n", student[maxI][maxJ].finalExam);
  printf("Total: %d\n", student[maxI][maxJ].total);
  printf("Course number: %d\n", maxI + 1);
}

int main() {
  atexit(report_mem_leak); // add this line to your code

  student **courseList;
  int i, j, C, N, M;

  courseList = readCourses(&C, &N, &M);

  printHighestTotal(courseList, C, N, M);

  release_memroy(courseList, C, N, M);

  return 0;
}
