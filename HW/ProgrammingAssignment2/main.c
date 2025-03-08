/* COP 3502C Assignment 2
This program is written by: Yousef Alaa Awad */

#include <stdio.h>
#include <stdlib.h>

// given structs
typedef struct Student {
  int sequenceNumber;
  struct Student *next;
} Student;

typedef struct Queue {
  Student *front;
  Student *back;
  int nodeCount; // garage number
  int k;
  int th;
  int numStudents; // number of students in the queue total
} Queue;

// given functions
int enqueue(Queue *q, int numStudents);
int dequeue(Queue *q);
int isEmpty(Queue *q);
int peek(Queue *q);
void display(Queue *q);

Student *createStudent(int sequence) {
  // dynamically allocates a student and then returns it
  Student *student = (Student *)malloc(sizeof(Student));

  // giving the sequence number that was inputted into the function
  student->sequenceNumber = sequence;
  student->next = NULL;

  return student;
};

void createReverseCircle(Queue *q) {
  // takes in the pointer of a queue
  // then is creates a linked list for that queue containing sequence numbers
  // in reverse order.
  // therefore if n = 5, it would produce a circular linked list from 5 to 1
  // use createStudent and enqueue.

  // creating the students now
  for (int i = q->numStudents; i >= 1; i--) {
    enqueue(q, i); // uses createStudent
  }
}

void rearrangeCircle(Queue *q) {
  // takes in the pointer to a queue, then reverses the list.
  if (!isEmpty(q)) {
    Student *reverse = q->front, *next, *previous = NULL;
    next = reverse->next;
    while (reverse != NULL || reverse != q->back) {
      // going to the end/back of the queue/linked list
      next = reverse->next;
      reverse->next = previous;
      previous = reverse;
      reverse = next;
      if (reverse == q->front) {
        break;
      }
    }
    // the end of the queue/linked list is found
    q->back = q->front;
    q->front = previous;
    q->back->next = q->front;
  }
}

void display(Queue *q) {
  // he likes to walk to places and give me the result (haha, he touches grass)
  Student *walkingStudent = q->front;
  // displays the queue given
  if (walkingStudent == NULL) {
    // the queue/list does not exist
    return;
  }
  // the queue/list exists
  printf("%d ", walkingStudent->sequenceNumber);
  walkingStudent = walkingStudent->next;
  while (walkingStudent != q->back) {
    // print every student in the queue until you reach the back.
    printf("%d ", walkingStudent->sequenceNumber);
    walkingStudent = walkingStudent->next;
  }
  // since we stopped the back, we will then print the number of the last
  // student
  printf("%d", walkingStudent->sequenceNumber);
  walkingStudent = walkingStudent->next;

  printf("\n");
}

void phase1(Queue *q) {
  // the first phase of the Garage Games (get it? like hunger games!!) is the
  // following a group has n students in it. in that, it eliminate the kth
  // student (aka k-1 in the array), after that the 2kth person would eliminated
  // (aka skip k - 1 spots), and do this until th students remain in the group.
  printf("Group for Garage# %d\n", q->nodeCount);
  // going to the kth student and eliminating them
  Student *eliminator5000 = q->front;
  Student *beforeEliminator = NULL;
  int i;

  while (q->numStudents > q->th) {
    // while we have more students than the threshold, keep removing them

    for (i = 1; i < q->k; i++) {
      // go through the k amount of students to the next one
      beforeEliminator = eliminator5000;
      eliminator5000 = eliminator5000->next;
    }

    // make the node before it point to the node after the kth node.
    beforeEliminator->next = eliminator5000->next;

    // checking if the front or the back is being eliminated
    if (eliminator5000 == q->front) {
      // if its the front node that is about to eliminated, then move the front
      // node up by one
      q->front = q->front->next;
    }
    if (eliminator5000 == q->back) {
      // if its the back node that is about to eliminated, then move the back
      // node back by one
      q->back = beforeEliminator;
    }

    // getting rid of the kth node.
    printf("Student# %d eliminated\n", eliminator5000->sequenceNumber);
    free(eliminator5000);

    // decreasing the amount of students that wait in the garage
    q->numStudents -= 1;

    // cycling through the to the next node in the list
    eliminator5000 = beforeEliminator->next;
  }
}

void phase2(Queue *q, int totalStudents) {
  // checking for the largest sequence number at the front
  while (totalStudents > 1) {
    // check to see which garage has the largest student number in the front
    int largestSequence = -1, garageSequence = -1;
    for (int i = 0; i < 10; i++) {
      // cycling through every possible garage
      if (!isEmpty(&q[i])) {
        // if the garage has people wanting it
        if (peek(&q[i]) > largestSequence) {
          // check the first number and see if its the largest line there
          largestSequence = peek(&q[i]);
          garageSequence = i;
        }
      }
    }
    // after this, get rid of that person (rip)
    dequeue(&q[garageSequence]);
    printf("Eliminated student %d from group for garage %d\n", largestSequence,
           garageSequence + 1);
    // and lower the total amount of students wanting garages down by one.
    totalStudents -= 1;
  }
  // we now only have one more student left
  int i = 0;
  while (isEmpty(&q[i]) || (i > 9)) {
    // going to the garage that the student is in
    i++;
  }
  // getting the winner
  int winner = dequeue(&q[i]);
  // and declaring it to the crowd!
  printf("\nStudent %d from the group for garage %d is the winner!", winner,
         i + 1);
}

int enqueue(Queue *q, int value) {
  // creating the temporary student
  Student *temp = createStudent(value);

  if (isEmpty(q)) {
    // if the list doesnt exist yet, make it the first one (L bozo)
    q->front = temp;
    q->back = temp;
  } else {
    // its sadly not the beginning of the list so i have to do more work.
    q->back->next = temp;
    q->back = temp;
    temp->next = q->front;
  }
  // the function succeeded for some reason so we return a success integer.
  return 0;
}

int dequeue(Queue *q) {
  // dequeue is when you take it out of the front and then move the list

  // finding the number that is at the front of the list
  int returNum = peek(q);
  // moving the front of the list forward by one
  Student *oldFront = q->front;
  q->front = q->front->next;
  // moving the back of the list to point to the new front of the list
  q->back->next = q->front;
  // getting rid of the old front of the list (you did well, soldier o7)
  free(oldFront);
  q->numStudents -= 1;
  if (q->numStudents == 0) {
    // if there is no more students in the garage, then get rid of the garage
    q->front = NULL;
    q->back = NULL;
  }
  // returning the value of the old front. (R.I.P)
  return returNum;
}

int isEmpty(Queue *q) {
  // 1 if its empty. 0 if its not empty ;)
  if (q->front == NULL || q->back == NULL) {
    return 1;
  }
  return 0;
}

int peek(Queue *q) {
  // returning the number at the front of the queue without dequeing the front.
  return q->front->sequenceNumber;
}

int main() {
  Queue garages[10];

  // finding out how many garages there are actually students waiting for
  int uniqueGarages = -1;
  scanf("%d", &uniqueGarages);

  for (int i = 0; i < 10; i++) {
    // initializing all 10 possible garages to be empty
    garages[i].front = NULL;
    garages[i].back = NULL;
    garages[i].nodeCount = 0;
    garages[i].numStudents = 0;
    garages[i].k = 0;
    garages[i].th = 0;
  }

  // getting the garages wanted
  for (int i = 0; i < uniqueGarages; i++) {
    // for every garage that a student is actually waiting for
    int garageNumber, numStudents, k, th;
    // find out its data
    scanf("%d %d %d %d", &garageNumber, &numStudents, &k, &th);
    // and then put it into that garage's data
    garages[garageNumber - 1].nodeCount = garageNumber;
    garages[garageNumber - 1].numStudents = numStudents;
    garages[garageNumber - 1].k = k;
    garages[garageNumber - 1].th = th;
    // creating the queue in the linked list
    createReverseCircle(&garages[garageNumber - 1]);
  }
  // printing out the gathered data to the user
  printf("Initial status of nonempty queues\n");
  for (int i = 0; i < 10; i++) {
    if (isEmpty(&garages[i])) {
      break;
    }
    printf("%d ", garages[i].nodeCount);
    display(&garages[i]);
  }

  for (int i = 0; i < 10; i++) {
    // for every single garage that exists on campus, we will reverse their
    // students
    rearrangeCircle(&garages[i]);
  }
  // and then print out the reversed list to the user
  printf("\nAfter ordering status of nonempty queues\n");
  for (int i = 0; i < 10; i++) {
    if (isEmpty(&garages[i])) {
      break;
    }
    printf("%d ", garages[i].nodeCount);
    display(&garages[i]);
  }

  // beginning phase 1 (GL everyone!!!)
  printf("\nPhase1 elimination\n\n");
  for (int i = 0; i < 10; i++) {
    // for every garage in the queue
    // do a phase 1 function call
    if (!isEmpty(&garages[i])) {
      phase1(&garages[i]);
      printf("\n");
    }
  }

  // beginning phase 2 (congrats to all who passed phase 1!!)
  printf("Phase2 elimination\n");
  // finding the total amount of students left in the entire lottery system
  int studentsLeft = 0;
  for (int i = 0; i < 10; i++) {
    // summing all the students waiting for each garage after phase1
    studentsLeft += garages[i].numStudents;
  }
  // calling the phase 2 function
  phase2(garages, studentsLeft);

  // ending the program succesfully
  return 0;
}
