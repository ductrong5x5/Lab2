/*  
  Name            : Duc Trong Nguyen
  NetId           : 000 657421
  DOB             : Nov 20 1998
  Lab description : Using std sort, Quick sort and Quick select to sort data of Last name, First name and Phone number.
*/
//header will be used
#include <iostream>
#include <cstring>
#include <iomanip> 
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
//declare class data
class data {
  public:
    //overloaded operator>> and operator<<
    friend istream & operator>>(istream &, data &);
    friend ostream & operator<<(ostream &, const data &);
    // operator< using lastname, firstname, phone number
    friend bool operator< ( const data& a,const data& b) {
      if(a.lastname==b.lastname){
        if(a.firstname==b.firstname)
          return a.phonenum<b.phonenum;
        else 
          return a.firstname<b.firstname;
      }
      else
        return a.lastname<b.lastname;
    }
   
  private:
    string firstname;
    string lastname;
    string phonenum;
};


//operator>>
istream & operator>>(istream &in, data &r) { 
  // write this to read data object data
  string firstname;
  string lastname;
  string phonenum;
  in>>firstname>>lastname>>phonenum;
  //check eof()
  if(!in.eof()){
    r.firstname=firstname;
    r.lastname=lastname;
    r.phonenum=phonenum;
  }
  return in;
}
//operator<<
ostream & operator<<(ostream &out, const data &r) {
  // write this to write data object data
  out<<setw(26)<<left<<r.lastname +", "+ r.firstname;
  out<<r.phonenum;
  return out;
}
//quicksort 
template <typename Tdata>
void quicksort(std::vector<Tdata> &A, int left,int right) {
  int pindex;
  if (left < right) {
    //create random index
    int random = left + rand() % (right - left);
    //swap data at random index to the right
    swap(A[random], A[right]);
    //make pivot to the right
    Tdata pivot = A[right]; 
    int i = left - 1; 
    //traverse through vector
    for (int j = left; j <= right - 1; j++) 
    { 
        //if current element less than pivot
        if (A[j] < pivot) {
            //increment i before swap
            i++; 
            //swap current element to the left, so on the left will be less than pivot
            swap(A[i], A[j]);
        }
    }
    //swap pivot, so the list will be < then pivot.
    swap(A[i + 1], A[right]);
    int pi = i + 1;
    //recursion to sort element on the left and the right
    quicksort(A, left, pi-1);
    quicksort(A, pi+1, right);
  }
}
//quick select, the same partitioning with quicksort
template <typename Tdata>
void quickselect(vector<Tdata> &A, int left,int k,int right) { 
  while (1) {
    int random = left + rand() % (right - left+1);
    swap(A[random], A[right]);
    Tdata pivot = A[right]; 
    int i = (left - 1); 
    for (int j = left; j <= right - 1; j++) 
    {
        if (A[j] < pivot) {
            i++; 
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[right]);
    int pindex=i+1;
    if (pindex == k)
      return ;
    if (k < pindex) right = pindex-1;
    else            left = pindex+1;
  }
}
//function printlist to print 
template <typename Iterator>
void printlist(Iterator p0, Iterator p1) {  // given iterators, iterate through and printout each element
    for (auto it=p0;it!=p1;it++) {
      cout<<(*it)<<endl;
    }
}

int main(int argc, char *argv[]) {
  // perform command-line error checking
  // usage: Qsort -stl | -rpivot [k0 k1] file.txt

  ifstream fin;
  //open file
  fin.open(argv[argc-1]);
  //declare vector and data class
  vector<data> A;
  data din;
  int k0,k1,N;
  //read data from file and put in vector
  while (fin >> din)
    A.push_back(din);
  //close file
  fin.close();

   //All the situations can happen.
  if(argc==3){
    if(strcmp(argv[1],"-stl")==0)
      //sort data using std sort
      sort(A.begin(), A.end());
    if(strcmp(argv[1],"-rpivot")==0){
      N = (int)A.size();
      //sort data using quick sort
      quicksort(A,0,N-1);
    }

  }
  else if(argc==5){
    if(strcmp(argv[1],"-rpivot")==0){
      N = (int)A.size();
      //convert value of k0 and k1 to int
      k0=atoi(argv[2]);
      k1=atoi(argv[3]);
      //update k0 and k1
      if(k0<0)
        k0 = 0;
      if(k0>N)
        k0 =N-1;
      if(k1>=N)
        k1 = N-1;
      //using quick select
      quickselect(A,0,k0,N-1);
      quickselect(A,k0,k1,N-1);
      quicksort(A,k0,k1);
    }
    else
      return 0;
  }
  //print data to the screen
  printlist(A.begin(), A.end());
  return 0;
}
