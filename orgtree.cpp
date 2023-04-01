#include "orgtree.h"

/**
 * I the undersigned promise that the submitted assignment is my own work. While I was 
 * free to discuss ideas with others, the work contained is my own. I recognize that 
 * should this not be the case; I will be subject to penalties as outlined in the course 
 * syllabus. 
 * Name: Conner Sommerfield
 * Red ID: 824769654
*/


// Comments shortened to essential information to reduce clutter, for full descriptions please view header file


/**
 * Check if an employee is present in an organization chart. 
 * @param  head the head / root Employee of the organization chart
 * @param  e_id the employee id being searched
 * @return      true or false     
 */

bool Orgtree::isEmployeePresentInOrg(Employee* head, int e_id) {
 
  // base case 1: empty organization chart means employee not in tree
  if (head == nullptr) {
    return false;
  }

  // base case 2: if the employee is found, return true
  if (head->getEmployeeID() == e_id) {
    return true;
  }

  // search employee from each child of the head and return true if found
  for (Employee* directReport : head->getDirectReports()) {
    if (Orgtree::isEmployeePresentInOrg(directReport, e_id)) {   // return true if the employee is found in one of the child subtree
      return true;
    }
  }

  // if not found, return false
  return false;
}


/**
 * Find the level of an employee in an organization chart (level of head is 0)
 * Assumption: e_id is unique among all employee IDs
 *
 * @param  headLevel the level of the head of tree/subtree (used to recursively track level of current node) 
 * @return    level of the employee in the org chart or Employee::NOT_FOUND (-1) if e_id is not present
 */
int Orgtree::findEmployeeLevel(Employee* head, int e_id, int headLevel) {
  
  // base case 1: empty organization chart means employee not in tree
  if (head == nullptr) {
    return Employee::NOT_FOUND;
  }

  // base case 2: the employee is found, returns the employee level
  if (head->getEmployeeID() == e_id) {
      return headLevel;
  }
  
  // search employee from each child of the head
  for (Employee* directReport : head->getDirectReports()) {
    int level = Orgtree::findEmployeeLevel(directReport, e_id, headLevel + 1); //increment headLevel value for each deepening recursive call
    if (level != -1) { // return answer if a recursive call returns a value that isn't -1
      return level; 
    }
  }

  // if not found, return integer -1 (NOT_FOUND defined as field in header file, set to -1)
  return Employee::NOT_FOUND;
}


/**
 * Return pointer to the closest shared manager (employee object pointer) of two employees e1 and e2. 
 * 
 * Two possible organizational relationships between two employees in the org chart:
 *  - e1 or e2 is a manager of the other employee; 
 *  - e1 or e2 is not a manager of the other employee, they have at least one shared manager
 *    
 */
Employee* Orgtree::findClosestSharedManager(Employee* head, int e1_id, int e2_id) {

  // base case 1: empty organization chart means no shared manager
  if (head == nullptr) {
    return nullptr;
  }

  // base case 2: either e1_id or e2_id is the same as the head / root
  // this indicates current is ancestor of other node or other node not in tree; both cases return current node
  if (head->getEmployeeID() == e1_id || head->getEmployeeID() == e2_id) {
    return head;
  }


  // recursive block executes if current is not null or desired node, checks if children are desired nodes
  else {
    vector<Employee*> answerVector; // each level of recursive call that reaches else block stores answers in its own vector
    
    // recursively call function for each child of current node
    for (Employee* directReport : head->getDirectReports()) {
      Employee* sharedManager = Orgtree::findClosestSharedManager(directReport, e1_id, e2_id);
      // if recursive call returns NOT null (base case 2 executes), include in answer vector
      if (sharedManager) {        
        answerVector.push_back(sharedManager);
      }
    }

    // if subtree has one employee but not other, either other employee not in subtree, or current employee is ancestor of other
    // in either case we return that employee (first & only element in answer vector) up the chain or as final answer
    if (answerVector.size() == 1) {
      return answerVector[0];
    }
    // if the subtree contains both employees, the current recursive call's head (the node that "made" the recursive call) must be the shared manager
    if (answerVector.size() == 2) {
      return head;
    }
    // if answer vector contains nothing, the nodes in question aren't in the tree/subtree, jump to return nullptr to return up the chain or as final answer
  }
 
  return nullptr;
}


/**
 * Calculate the number of managers between employee e1 and employee e2. 
 * 
 * The number of managers between employee e1 and employee e2 can be calculated by: 
 *  number of edges between employee 1 and closest shared manager + 
 *  number of edges between employee 2 and closest shared manager - 1
 *
 * @return   number of managers between employee e1 and employee e2 or Employee::NOT_FOUND if either e1 or e2 is not present in the chart
 */
int Orgtree::findNumOfManagersBetween(Employee* head, int e1_id, int e2_id) {
  
  // must find level of closest manager with previous function for calculation of edges
  Employee* sharedManager = Orgtree::findClosestSharedManager(head, e1_id, e2_id);

  if (sharedManager != nullptr) {       // If there is no shared manager, program jumps to return NOT_FOUND
    

    // calculation requires 3 level values - the level of the manager and the two employees involved
    int managerLevel = Orgtree::findEmployeeLevel(head, sharedManager->getEmployeeID(), 0); 
    int e1Level = Orgtree::findEmployeeLevel(head, e1_id, 0);
    int e2Level = Orgtree::findEmployeeLevel(head, e2_id, 0);


    // if the two employees given are actually in the tree, calculate managerCount and return value
    if (e1Level != -1 && e2Level != -1) {
      int managersCount;
      managersCount = (((e1Level - managerLevel) + (e2Level - managerLevel)) - 1); // code version of calculation
      return managersCount;
    }
  }

  // returned if no shared manager OR both employees not in tree
  return Employee::NOT_FOUND;
}


/** Recursively delete a tree 
 * 
 * Traversing from the head / root node, recursively deallocate 
 * the memory of the descendants from the leaf node level. 
 * 
 * Use post order traversal:
 * Before deleting the current node, print its employee ID and a new line
 * 
 */
void Orgtree::deleteOrgtree(Employee* head) {
 
  // base case: empty tree or organization chart means we stop the function
  if (head == nullptr) {
    return;
  }

  // delete each child in vector by calling function recursively
  for (Employee* directReport : head->getDirectReports()) {
    Orgtree::deleteOrgtree(directReport);
  }

  // print current node's employee ID and a new line 
  // will be executed if node is a leaf node as function won't travel into further recursive calls for its children
  // then function will backtrack through recursive calls on stack to give post-order traversal
  std::cout << head->getEmployeeID() << endl;

  // delete the current node (happens after deleting its children)
  delete(head);
}


/*
* Helper function that recursively prints each tree node along with its associated children
*/
void Orgtree::printOrgTree(Employee* head) {
// If tree doesn't exist/ head is null, print Empty node/children values
  if (head == nullptr) {
    std::cout << "Node: " << endl << "Children: " << endl << endl;
    return;
  }

// list current node 
  std::cout << "Node: " << head->getEmployeeID() << " " << endl;
  std::cout << "Children: ";

// for loop iterates through children vector and prints IDs of each node
  for (Employee* child : head->getDirectReports()) {
    std::cout << child->getEmployeeID() << " ";
  }
  std::cout << endl << endl;

// recursively call function for all children of current node
  for (Employee* child : head->getDirectReports()) {
    Orgtree::printOrgTree(child);
  }
}