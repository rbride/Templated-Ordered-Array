/*########################################################################
## Notes about this file, for sake of simplicity the Container, which is 
## designed to contain "students", sorts those "students" based on their 
## age attributes.  
########################################################################*/
#include <iostream>
#include <string.h>
#include <compare>
using namespace std;

/* Function Pointer that is used to point towards functions in the container */
typedef void (*container_fun_ptr)(const void * data_ptr);
typedef int(*container_comparison_ptr)(const void *data_ptr1, const void *data_ptr2);
//Basic Student Class used to create Students that are added to the Container
class Student
{
  private:
    string name;
    int age;
  public:
    //Constructor
    Student(string s, int i) {
      name = s; 
      age = i;
    }
    string getName() const { return name; } 
    int getAge() const { return age; }
};
/* Function used to sort Student Items in the container */
int student_sort_cmp( const void * x, const void * y) {
  //Cast the void pointers to student
  Student stu_x = *((Student *) x);
  Student stu_y = *((Student *) y);
  /* First Check by age then by name, if the same 0, 1 means it goes after
  -1 means it comes before, these are the required inputs for the binsearch */
  if (stu_x.getAge() < stu_y.getAge())
    return( -1 );
  else if (stu_x.getAge() > stu_y.getAge()) 
    return( 1 );
  else {
    int temp = stu_x.getName().compare(stu_y.getName());
    if(temp == 0)
      return( 0 );
    else if (temp < 0)
      return( -1 );
    else 
      return( 1 );
    }
}

/* Print student info, prints the info of the student after being given the 
ptr to said info from the class and told to use a double pointer by the struct/class
first cast a variable, temp_stu of type student, that is set equal to the dereferenced
data_ptr that was cast to a student pointer. then simply prints name and age */
void print_student_info(const void * data_ptr){
  Student temp_stu = *((Student *) data_ptr);
  cout << temp_stu.getName() << ' ' << temp_stu.getAge() << '\t' ;
}

struct container
{
  container_comparison_ptr comparator; //used to define the comparison function used to sort container
  void **arr;        // pointer to array of pointer to void
  void *item_ptr;
  int allocation;    // current size of the array
  int size;          // Number of items currently in the array
  //Type used  for map function, / Student pointer
  
  // Construct the array of size
  container(container_comparison_ptr comp) {
    comparator = comp;
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
  /* Maps the print_Student_info to print student info (NOTE: STUDENT CLASS SPECIFIC) */
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
  struct container test_vect( (int (*) (const void *, const void *))student_sort_cmp);
  Student joe("Joe Smith", 33), chris("Chris Jones", 52);
  Student andy("Andy Stelanski", 21), tony("Tony Vilory", 67);
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

}
// int z = 12;
// int *i = &z;
// cout << *(i);