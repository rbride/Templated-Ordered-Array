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
void print_student_info(const void * data_ptr) {
  Student temp_stu = *((Student *) data_ptr);
  cout << temp_stu.getName() << ' ' << temp_stu.getAge() << '\t' ;
}

struct container
{
  container_comparison_ptr comparator; //used to define the comparison function used to sort container
  void **container_array;        // pointer to array of pointer to void
  int allocation;    // current size of the array
  int size;          // Number of items currently in the array
  int insert_loc;
  int new_entry_loc;
  // Construct the array of size
  container(container_comparison_ptr comp) {
    comparator = comp;
    allocation = 3; 
    size = 0;       
    container_array = (void **)malloc(allocation);
    insert_loc = 0;
  }
  /* Destructor, Simply frees the memory set aside by malloc */
  ~container() { free(container_array); }

  /* Binary Search Function, used to assist in the insertion and search of the container container_binsearch O(log(n))*/
  int container_binsearch( void *item_to_be_inserted )
  {
    //container_array is the array, and size is the number of items in the array x
    int low, high, mid, comparator;
    /* Reset the flag that indicates if the item was found or not */
    low = 0; 
    high = size-1;
    while(low <= high){
        mid = (low+high) / 2;
        comparator = student_sort_cmp(item_to_be_inserted, container_array[mid]);
        if(comparator == (-1)) {
          high = mid - 1;
        }
        else if(comparator == (1)){
          low = mid + 1;
        }
        else if(comparator == 0){
          //Item found and is a dupelicate so the location to add it is mid+1
          //insert_loc = mid+1;
          cout << mid+1;
          return(mid+1); //return to insert function as the entry has been found. 
        }
    }
    //Else the item has not been found and should be inserted at mid
    //insert_loc = mid;
    return(high+1); //return to the insert function
  }

  void insert( void *n_item )
  {
    int key;
    /* If the size is 0 nothing is inside the container so just insert something */
    if (size == 0 ){
      container_array[0] = n_item;
      size += 1;
    }
    /* If data already exist in the container but the container is not full then
    using outputs from my binary search, insert the array at the correct place */
    else if (size < allocation) {
      key = container_binsearch(n_item);
      int i;

      for(i=allocation-1; (i >= 0 && i > key); i--){
        container_array[i+1] = container_array[i];
      }
      container_array[i+1] = n_item;
      size+=1;

    }
    /* if the array is full, new size = 2*(old size + 1) */
    else {
      allocation = 2*(allocation + 1);
      //realloc(container_array, allocation);
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
    for (int i=0; i<size-1; i++) {
      map_fun_ptr(container_array[i]);
    }
  }
};

int main()
{
  struct container student_container( (int (*) (const void *, const void *))student_sort_cmp);
  Student joe("Joe Smith", 33), chris("Chris Jones", 52);
  Student andy("Andy Stelanski", 21), tony("Tony Vilory", 67);
  void *stu_ptr = &joe;
  student_container.insert(stu_ptr);
  //student_container.print();
  //Should be put in after Joe Smith
  stu_ptr = &chris;
  student_container.insert(stu_ptr);
  student_container.print();
  /* test to ensure that Andy is placed at front of the array */
  stu_ptr = &andy;
  student_container.insert(stu_ptr);
  student_container.print();

  
  return 0;
}