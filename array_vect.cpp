/*########################################################################
## Notes about this file, for sake of simplicity the Container, which is 
## designed to contain "students", sorts those "students" based on their 
## age attributes.  
########################################################################*/
#include <iostream>
#include <string.h>
using namespace std;

/* Function Pointer that is used to point towards functions in the container */
typedef void (*container_fun_ptr)(const void * data_ptr);

//Basic Student Class used to create Students that are added to the Container
class student
{
  private:
    string name;
    int age;
  public:
    //Constructor
    student(string s, int i) {
      name = s; 
      age = i;
    }
    string getName() { return name; } 
    int getAge() { return age; }
};

/* Print student info, prints the info of the student after being given the 
ptr to said info from the class and told to use a double pointer by the struct/class
first cast a variable, temp_stu of type student, that is set equal to the dereferenced
data_ptr that was cast to a student pointer. then simply prints name and age */
void print_student_info(const void * data_ptr){
  student temp_stu = *((student *) data_ptr);
  cout << temp_stu.getName() << ' ' << temp_stu.getAge() << '\t' ;
}

struct container
{
  void **arr;        // pointer to array of pointer to void
  void *item_ptr;
  int allocation;    // current size of the array
  int size;          // Number of items currently in the array
  //Type used  for map function, / Student pointer
  
  // Construct the array of size
  container( ) {
    allocation = 3; 
    size = 0;       
    arr = (void **)malloc(allocation);
  }
  /* Destructor, Simply frees the memory set aside by malloc */
  ~container() { free(arr); }

  
  /* Binary Search Function, used to assist in the insertion and search of the container */
  int container_binsearch(  )
  {
    cout << "rr";
  }
  void insert( void *n_item )
  {
    /*First check if number of items is less in array is less than the memory allocated for it
    if it is than simple insert the item into vector, otherwise, allocate more memory */
    if (size <= (allocation-1)) {
      arr[size] = n_item; 
      size += 1;
    }
    /* if the array is full, new size = 2*(old size + 1) */
    else {
      allocation = 2*(allocation + 1);
      realloc(arr, allocation);
    }

  }
  /* Maps the print_student_info to print student info (NOTE: STUDENT CLASS SPECIFIC) */
  void print() {
    map( (void (*) (const void *)) print_student_info);
    cout << '\n'; //After Printing new line for sake of output readablity
  }
  /* Makes the function given as an arguement to all elements in the container */
  void map(container_fun_ptr map_fun_ptr) 
  {
    for (int i=0; i<size; i++) {
      map_fun_ptr(arr[i]);
    }
  }

};

int main()
{
  struct container test_vect;
  student joe("Joe Smith", 33), chris("Chris Jones", 52);
  student andy("Andy Stelanski", 21), tony("Tony Vilory", 67);
  void *stu_ptr = &joe;
  test_vect.insert(stu_ptr);
  test_vect.print();
  //Should be put in after Joe Smith
  stu_ptr = &chris;
  test_vect.insert(stu_ptr);
  test_vect.print();
  /* test to ensure that Andy is placed at front of the array */
  stu_ptr = &andy;
  test_vect.insert(stu_ptr);
  test_vect.print();


  return 0;
}
// int z = 12;
// int *i = &z;
// cout << *(i);