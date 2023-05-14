#include "sequence.h"
#include <iomanip>
#include <iostream>

using namespace std;

// Creates a sequence indexed from 0 to sz
// Input: sz -- size of sequence
Sequence::Sequence(size_type sz) {
  if (sz < 0) { // if size < 0 , throw
    throw exception();
  } else {
    for (size_type i = 0; i < sz; i++) {
      push_back(i); // uses push back method to create nodes in sequence
    }
  }
}

// Copy constructor: creates a copy of the sequence
// Input: s -- sequence to copy
Sequence::Sequence(const Sequence &s) {
  head = s.head;
  head = nullptr;

  // current points to copy head and then adds copies of the elements from other
  // sequence to the copy sequence using push back method
  SequenceNode *current = s.head;
  while (current != nullptr) {
    push_back(current->elt);
    current = current->next;
  }
}

// Destructor: helps free memory from heap by delete used nodes
Sequence::~Sequence() {
  SequenceNode *current = head;
  SequenceNode *delete_me_next;

  // iterates and deletes in order of the list
  while (current != nullptr) {
    delete_me_next = current->next;
    current = nullptr;
    delete [] current;
    current = delete_me_next;
  }
}

// = operator: allows for the element at position [] to change to new element
// provided or allows two sequences to equal one another Input: s -- sequence
// location to copy Return: *this -- the sequence
Sequence &Sequence::operator=(const Sequence &s) {
  head = s.head;
  tail = s.tail;
  numElts = s.numElts;

  SequenceNode *current = new SequenceNode();
  SequenceNode *delete_me_next = new SequenceNode();
  current = head;
  while (current != nullptr) {
    delete_me_next = current->next;
    current = nullptr;
    delete current;
    current = delete_me_next;
  }

  head = nullptr;
  current = s.head;
  // loop to copy elements into the copy sequence
  while (current != nullptr) {
    push_back(current->elt);
    current = current->next;
  }
  return (*this);
}

// [] operator: finds position in sequence
// Input: position -- specific index to find
// Returns: node_at_position -- returns element at desired position
// Reference:
// https://www.geeksforgeeks.org/operator-overloading-c/#:~:text=In%20C%2B%2B%2C%20we%20can%20make%20operators%20work%20for,can%20concatenate%20two%20strings%20by%20just%20using%20%2B.
Sequence::value_type &Sequence::operator[](size_type position) {
  SequenceNode *node_at_position = new SequenceNode();
  node_at_position = head;

  // if position entered is less than 0 or is greater than size of sequence,
  // throw exception
  if (position < 0 || position > size()) {
    throw exception();
  } else {
    // count increases as we iterate through sequence to make sure we don't go
    // past the desired position
    int count = 0;
    while (count < position) {
      // if next node is not null
      if (node_at_position->next != nullptr) {
        node_at_position = node_at_position->next;
      }
      count++;
    }
    return node_at_position->elt;
  }
}

// Push_back: adds new node to the end of the sequence
// Input: value -- the value inserted of the element added
// Reference: class code
void Sequence::push_back(const value_type &value) {
  if (value < 0) {
    throw exception();
  } else {
    SequenceNode *new_push_back = new SequenceNode();
    SequenceNode *current = nullptr;
    new_push_back->elt = value; // set value to the new push back node

    if (head == nullptr) {
      head = new_push_back; // head with equal the new node
    } else {
      if (head->next ==
          nullptr) { // if the next node in the sequence is null, set the new
                     // push back node to head's next node
        head->setNext(new_push_back);
        head->setPrev(nullptr);
      } else {
        current = head;
        while (current->next != nullptr) {
          current = current->next;
        }
        current->next =
            new_push_back; // while getting to the end of the sequence set the
                           // new push back node to the end
        new_push_back->next =
            nullptr; // node will then be pointing to null which means it is the
                     // last node of sequence
      }
    }
  }
}

// code for myself I used before I figured out the os stream code
/*
void Sequence::printForward() {
  if (head == nullptr) {
    cout << "Error: There are no items in the list." << endl;
    } else {
    SequenceNode * current = new SequenceNode();
    current = head;
    cout << "Addresses and elements printed forward: " << endl;
    while (current != nullptr) {
      cout << current << ", " << current->elt << endl;
      current = current->next;
      }
    }
}
*/

// Pop_back: deletes the last node of the sequence
void Sequence::pop_back() {
  if (head == nullptr) { // if  head is null throw exception
    throw exception();
  } else if (head->next == nullptr) { // if node after head is null, make head 0
                                      // and throw exception
    head->elt = 0;
    throw exception();
  } else if (size() == 0) { // if size of sequence is 0 make head a nullptr and
                            // throw exception
    head = nullptr;
    throw exception();
  } else {
    SequenceNode *current = new SequenceNode();
    SequenceNode *before_tail = new SequenceNode();

    current = head;
    before_tail = head;

    // loop to find tail
    while (current->next != nullptr) {
      current = current->next;
    }
    tail = current;

    // loop to find node before tail
    while (before_tail->next->next != nullptr) {
      before_tail = before_tail->next;
    }

    before_tail->next =
        nullptr; // set before tail to null so that I can delete tail
    delete tail;
    tail = before_tail; // set new tail
  }
}

// Insert: inserts value to the desired position
// Input: position -- index of where we want the value entered
// value -- the value of what is entered in the position
void Sequence::insert(size_type position, value_type value) {
  SequenceNode *new_insert_node = new SequenceNode();
  new_insert_node->setNext(nullptr);
  new_insert_node->setPrev(nullptr);

  new_insert_node->elt = value;

  if (position < 0) {
    throw exception();
  } else if (position == 0) {
    new_insert_node->setNext(head);
    head->setPrev(new_insert_node);
    head = new_insert_node;
  } else if (position > size()) {
    throw exception();
  } else {
    SequenceNode *current = new SequenceNode();
    current = head;

    // loop to find position in sequence
    int count = 0;
    while (count < position - 1) {
      if (current != nullptr) {
        current = current->next;
      }
      count++;
    }
    // set new node's next pointer to current's next and new node's previous to
    // current
    new_insert_node->setNext(current->next);
    new_insert_node->setPrev(current);

    // set current's next to the new node inserted
    current->setNext(new_insert_node);
  }
}

// Front: finds first element in sequence
// Returns: element at head
const Sequence::value_type &Sequence::front() const {
  if (head == nullptr) {
    throw exception();
  } else {
    SequenceNode *current = new SequenceNode();
    current = head;
    return head->elt;
  }
}

// Back: finds last element of sequence
// Returns: element at the end of the sequence
const Sequence::value_type &Sequence::back() const {
  if (head == nullptr) {
    throw exception();
  } else {
    SequenceNode *current = new SequenceNode();
    current = head;

    // loops to the last node in sequence
    while (current->next != nullptr) {
      current = current->next;
    }
    return current->elt;
  }
}

// Empty: checks if the sequence is empty
// Returns: 1 if the sequence is empty, 0 otherwise
bool Sequence::empty() const {
  if (head == nullptr) {
    return 1; // means it is empty
  } else {
    return 0; // means it is not empty
  }
}

// Size: finds the number of elements in the sequence
// Returns: number of elements in sequence
Sequence::size_type Sequence::size() const {
  SequenceNode *current = new SequenceNode();
  current = head;

  if (head == nullptr) {
    return 0;
  } else {
    // counter to count while iterating so that it cna return this number
    int counter = 1;
    while (current->next != nullptr) {
      current = current->next;
      counter++;
    }
    return counter;
  }
}

// Clear: clears all nodes within the sequence
void Sequence::clear() {
  SequenceNode *current = new SequenceNode();
  SequenceNode *temp_current = new SequenceNode();
  current = head;

  while (current != nullptr) {
    temp_current = current;       // temp pointing to head
    current = current->next;      // current is now next node
    temp_current->next = nullptr; // temp now is no longer pointing to next node
    delete temp_current;          // allows to delete the temp node
  }
  head = nullptr; // make head a null node after deleting all nodes after head
}

// Erase: will delete a number of nodes starting at a certain index in sequence
// Input: position -- index where delete will start
// count -- the number of nodes to delete from position
void Sequence::erase(size_type position, size_type count) {
  if (position == 0 &&
      count > size()) { // if the position is at first index and the nodes to
                        // delete is greater than the size of sequence, then
                        // clear all nodes in sequence
    clear();
  } else if (position > size() || position < 0 ||
             count >
                 size() -
                     position) { // if position is greater than size of
                                 // sequence, if position is less than zero, or
                                 // if the desired number of nodes to delete is
                                 // greater than the remaining number of nodes
                                 // from position, then throw exception
    throw exception();
  } else if (position == 0) { // if position is starting at head of sequence
    SequenceNode *deleteAt = new SequenceNode();
    SequenceNode *current = new SequenceNode();
    current = head;

    // loop to delete from the beginning of sequence until the number of nodes
    // from count value is sufficed
    int indexCounter = 0;
    while (indexCounter < count) {
      if (current->next != nullptr) {
        deleteAt = current;
        current = current->next;
        deleteAt->next = nullptr;
        delete deleteAt;
      }
      indexCounter++;
    }
    // need to set new head since deleting started at head
    head = current;
    current->setPrev(nullptr);
  } else {
    SequenceNode *deleteAt = new SequenceNode();
    SequenceNode *current = new SequenceNode();
    SequenceNode *before_current = new SequenceNode();
    current = head;
    before_current = head;

    // loop to iterate to the desired position of the sequence
    int indexCounter = 0;
    while (indexCounter < position) {
      if (current != nullptr) {
        current = current->next;
      }
      indexCounter++;
    }

    // loop to iterate to the node right before the desired position of sequence
    int indexCounter0 = 0;
    while (indexCounter0 < position - 1) {
      if (before_current != nullptr) {
        before_current = before_current->next;
      }
      indexCounter0++;
    }

    // loop to delete the number of nodes count has requested
    int indexCounter1 = 1;
    while (indexCounter1 <= count) {
      if (current->next != nullptr) {
        deleteAt = current;
        current = current->next;
        deleteAt->next = nullptr;
        delete deleteAt;
      }
      indexCounter1++;
    }

    // set the before node's next pointer to the new current after the deleted
    // nodes
    before_current->setNext(current);
  }
}

// << ostream operator: when << is used on sequence it can print out sequence
// formatted in a line from head Input: os -- o stream s -- sequence to print
// Returns: os -- which will print from head and iterates through the sequence
ostream &operator<<(ostream &os, Sequence &s) {
  os << s.head->elt << " ";
  Sequence::SequenceNode *current = s.head->next;
  while (current != nullptr) {
    cout << current->elt << " ";
    current = current->next;
  }
  return os;
}