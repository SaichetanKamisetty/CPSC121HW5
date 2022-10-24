#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;
// For this homework, you are going to implement an extendable vector based queue 
//that 
// uses "jump" trick to save space. 
// Finish function 
//              front() that prints the first element in the queue
//              deque() that dequeues the queue
//           enque(val) that enqueues val to the queue
//              print_vect() that prints out vect_que.
// Demonstrate that your code works in main.
// Refer to class PPT if you forgot all the different cases. 
template <class T>
class vect_queue {
    std::vector<T> vect_que; 
    size_t size_;
    int que_front_;
public:
    // template <class T>
    vect_queue(T val) {
        vect_que.push_back(val);
        size_ = 1;
        que_front_ = 0;
    }
    T front() const;
    void deque();
    void enque(T val);
    void print_vect() const;
};

template <typename T>
T vect_queue<T>::front() const {
    return vect_que[que_front_];
}

template <typename T>
void vect_queue<T>::enque(T val) {
  if (size_ < vect_que.size()) {
    vect_que[(que_front_ + size_) % vect_que.size()] = val;
    size_++;
  } else if (size_ == vect_que.size()) {
      size_t temp_size = std::fmax(1, size_ * 2);
      std::vector<T> temp_vec(temp_size);
      for (int i = 0; i < size_; i++) {
          int b = (que_front_ + size_) % vect_que.size();
          temp_vec[i] = vect_que[b];
      }
      vect_que.swap(temp_vec);
      
      vect_que[(que_front_ + size_) % vect_que.size()] = val;
      size_++;
      que_front_ = 0;
    } else {
        throw std::out_of_range("Error");
    }
} 

template <typename T>
void vect_queue<T>::deque() {
    if (size_ != 1) {
        if (que_front_ == vect_que.size() - 1) {
            que_front_ = 0;
            size_--;
        } else {
            que_front_ = (que_front_ + 1) % vect_que.size();
            size_--;
        }
    } else if (size_ == 1) {
        que_front_ = 0;
        size_--;
    } else {
        throw std::out_of_range("Error");
    }
}

template <typename T>
void vect_queue<T>::print_vect() const {
    std::cout << "Queue: ";
    for (int i = 0; i < size_; i++) {
        int b = (que_front_ + i) % vect_que.size();
        std::cout << vect_que[b] << " ";
    }
    std::cout << std::endl;
    std::cout << "Full Vector: ";
    for (int i = 0; i < vect_que.size(); i++) {
        std::cout << vect_que[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Front Index of Queue in Vector: " << que_front_ << std::endl;
    if (size_ == 0) {
        std::cout << "Back Index of Queue in Vector: " << (que_front_+size_) % vect_que.size() << std::endl; 
    } else {
        std::cout << "Back Index of Queue in Vector: " << (que_front_+size_-1) % vect_que.size() << std::endl;
    }
    std::cout << std::endl;
}

int main()
{   
    //Demonstrate your code works by adding/removing values in a vect_que class 
    //object. Print out your result.
    //You should include front index of queue, back index of queue, and the entire
    //vector (not queue) for each case.
    
    //case 1: add to an empty queue
    
    vect_queue<int> vect(2);
    vect.print_vect();
    
    //case 2: add to a non-empty queue without jump 
    
    vect_queue<int> vect2(2);
    vect2.enque(4);
    vect2.print_vect();
    
    //case 3: add to a non-empty queue with a jump
    
    vect_queue<std::string> vect3("cow");
    vect3.enque("dog");
    vect3.enque("cat");
    vect3.enque("chicken");
    vect3.deque();
    vect3.deque();
    vect3.enque("sheep");           // Case 3 here
    vect3.print_vect();
    
    //case 4: remove from a queue with number of elements > 1 
    //        and que.front not at vect.back
    
    vect_queue<int> vect4(3);
    vect4.enque(6);
    vect4.deque();          // Case 4 here 3 =/= vect.back
    vect4.print_vect();
    
    //case 5: remove from a queue with number of elements > 1 
    //        and que.front at vect.back
    
    vect_queue<int> vect5(2);
    vect5.enque(9);
    vect5.deque();      
    vect5.enque(3);
    vect5.deque();          // Case 5 here que.front = 9 & 9 == vect.back.
    vect5.print_vect();
    
    //case 6: remove from a queue with 1 element in it and que.front 
    //        not at vect[0]
    
    vect_queue<int> vect6(9);
    vect6.enque(4);
    vect6.deque();
    vect6.deque();  // Case 6, Queue has 1 element 4, and it is que.front, and it is not at vect[0]
    vect6.print_vect();
    
    
    cout<<"\nprogram ends here.\n";
    return 0;
}
