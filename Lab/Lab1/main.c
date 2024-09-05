#include "main.h"
#include <stdio.h>

// structure that gets the max average student and returns it to maxStudent
// struct in the main file.
struct Student getMaxAverageStudent(struct Student *s, int n) {
  // setting up a temporary max variable to compare averages as well as a index
  // variable to store the maximum average's student id.
  float max = -1;
  int idx = 0;
  // comparing between students to see who has the highest average
  for (int i = 0; i < n; i++) {
    if (max < s[i].average) {
      max = s[i].average;
      idx = i;
    }
  }
  // returning the data of whichever student has the highest average back to the
  // main function.
  return s[idx];
};

// a function that reads the inputted file/console data so that it can be
// processed by the getMaxAverageStudent struct.
void readData(struct Student *students, int *c) {
  scanf("%d", c);
  for (int i = 0; i < *c; i++) {
    // getting the data from the text file and then assigning it to a variable
    // in the struct students array.
    scanf("%d", &students[i].student_ID);
    scanf("%d %d %d", &students[i].g1, &students[i].g2, &students[i].g3);

    // calculate the student's average
    students[i].average =
        (students[i].g1 + students[i].g2 + students[i].g3) / 3.0;

    // printing out back the student data as wanted by the assigned (float with
    // 2 decimal places)
    printf("%d %d %d %d %.2f\n", students[i].student_ID, students[i].g1,
           students[i].g2, students[i].g3, students[i].average);
  }
}

int main() {
  // declaring an array for the maximum amount of students possible to be
  // imported at once
  struct Student students[500];
  int n, i;

  // reading the data inputted
  readData(students, &n);

  // finding the student with the max average.
  struct Student maxStudent = getMaxAverageStudent(students, n);
  // outputting the student's average as well as their id number.
  printf("\nMaximum Average is %.2f and the student is %d\n",
         maxStudent.average, maxStudent.student_ID);

  // ending the program.
  return 0;
}
