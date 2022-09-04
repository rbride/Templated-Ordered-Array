#include <iostream>
#include <string.h>
using namespace std;

struct n_vect;

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

//Printer Helper that allows the print function to print;
void print_student_info(const void * data_ptr){
  student temp_stu = *((student *) data_ptr);
  cout << temp_stu.getAge();
}

struct n_vect
{
  void **arr;        // pointer to array of pointer to void
  void *item_ptr;
  int allocation;    // current size of the array
  int size;          // Number of items currently in the array
  //Type used  for map function, / Student pointer
  typedef void (*n_vect_map_fun_ptr)(void * data_ptr);


  // Construct the array of size
  n_vect() {
    allocation = 3; 
    size = 0;       
    arr = (void **)malloc(allocation);
    item_ptr = arr[0];
  }
  ~n_vect() { free(arr); }

  void insert( void *n_item )
  {
    /*First check if number of items is less in array is less than the memory allocated for it
    if it is than simple insert the item into vector, otherwise, allocate more memory */
    if (size < (allocation-1)) {
      arr[0] = n_item; 
      size += 1;
    }
    /* if the array is full, new size = 2*(old size + 1) */
    else {
      allocation = 2*(allocation + 1);
      realloc(arr, allocation);
    }

  }
  /* Sends a function pointer, i.e what will become a student pointer to the map function
  using the typdef above, as well as the 
  */
  void print() {
     student_map( (void (*) (void *)) print_student_info);
  }
  //map Function takes, any map function and applies to all items in container
  void student_map(n_vect_map_fun_ptr map_fun_ptr){
    for (int i=0; i<size; i++){
      map_fun_ptr(arr[i]);
    }

}

};

int main()
{
  struct n_vect test_vect;
  student joe("Joe Smith", 33);
  student chris("Chris Jones", 52);
  student andy("Andy Stelanski", 21);
  student tony("Tony Vilory", 67);
  void *sp1 = &joe;
  test_vect.insert( sp1 );
  test_vect.print();

  // sp1 = &chris;
  // test_vect.insert(sp1);
  // test_vect.print();





  // int z = 12;
  // int *i = &z;
  // cout << *(i);
  return 0;

}

