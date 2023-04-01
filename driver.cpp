/**
 * CS 210 Fall 2022
 * @author Conner Sommerfield
 * @date Oct 2022
 */

#include "orgtree.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * Driver test file tests various edge cases of tree data structure functions
 */

/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void assert(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
        exit(EXIT_FAILURE);
    }
}

//console output statements explain testing code - many comments ommitted to prevent redundancy
int main(int argc, char **argv) {
    
    /*
     * First test uses the following organization chart for testing
     *                1
     *           /    \    \
     *           2    3    4
     *          / \  / \   \
     *          5 6  7 8   9
     *         /   \       \
     *         10  11      12
     *        /     
     *      13       
     */     


    std::cout << endl << endl << endl << "Building Tree One - Full Tree" << endl << "_______________________________________________________" << endl << endl;

    Employee* head = new Employee(1, vector<int>{2, 3, 4});
    Employee* e2 = head->getDirectReports().at(0);
    Employee* e3 = head->getDirectReports().at(1);
    Employee* e4 = head->getDirectReports().at(2);

    e2->addDirectReports(vector<int>{5, 6});
    e3->addDirectReports(vector<int>{7, 8});
    e4->addDirectReport(9);

    Employee* e5 = e2->getDirectReports().at(0);
    Employee* e6 = e2->getDirectReports().at(1);
    Employee* e9 = e4->getDirectReports().at(0);

    e5->addDirectReport(10);
    e6->addDirectReport(11);
    e9->addDirectReport(12);


    Orgtree::printOrgTree(head);

    std::cout << "_______________________________________________________" << endl << endl;

    std::cout << endl << "Begin Testing" << endl << endl << endl << endl;
   
  

    std::cout << "*** Test isEmployeePresentInOrg function ***" << endl << endl;
    
    std::cout << "  Test Case 1: Employee Present" << endl;
    bool employeePresent = Orgtree::isEmployeePresentInOrg(head, 6);
    assert(employeePresent, "ID 6 Present in tree");
    std::cout << endl;

    std::cout << "  Test Case 2: Employee Not Present" << endl;
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 99);
    assert(employeePresent == false, "ID 99 Not present in tree");
    std::cout << endl << endl << endl;


    

    std::cout << "*** Test findEmployeeLevel function ***" << endl << endl;

    std::cout << "  Test Case 1: Employee Present - 0th level" << endl;
    int employeeLevel = Orgtree::findEmployeeLevel(head, 1, 0);
    assert(employeeLevel == 0, "Level of ID 1 returns " + to_string(employeeLevel) + ", expected 0");
    std::cout << endl;


    std::cout << "  Test Case 1: Employee Present - 1st level" << endl;
    int employeeLevelOne = Orgtree::findEmployeeLevel(head, 4, 0);
    assert(employeeLevelOne == 1, "Level of ID 4 returns " + to_string(employeeLevelOne) + ", expected 1");
    std::cout << endl;

    std::cout << "  Test Case 2: Employee Present - Deep level" << endl;
    int employeeLevelTwo = Orgtree::findEmployeeLevel(head, 10, 0);
    assert(employeeLevelTwo == 3, "Level of ID 10 returns " + to_string(employeeLevelTwo) + ", expected 3");
    std::cout << endl;


    std::cout << "  Test Case 3: Employee Not Present" << endl;
    int employeeLevelEmpty = Orgtree::findEmployeeLevel(head, 99, 0);
    assert(employeeLevelEmpty == -1, "Level of ID 99 returns " + to_string(employeeLevelEmpty) + ", expected -1");
    std::cout << endl << endl << endl;




    std::cout << "*** Test findClosestSharedManager function ***" << endl << endl;

    std::cout << "  Test Case 1: children of different parent nodes" << endl;
    Employee* closestManager = Orgtree::findClosestSharedManager(head, 10, 11);
    assert(closestManager->getEmployeeID() == 2, "Shared manager between 10 and 11 returns " + to_string(closestManager->getEmployeeID()) + ", expected 2");
    std::cout << endl;

    std::cout << "  Test Case 2: Children at different levels" << endl;
    Employee* closestManagerOne = Orgtree::findClosestSharedManager(head, 6, 3);
    assert(closestManagerOne->getEmployeeID() == 1, "Shared manager between 6 and 3 returns " + to_string(closestManagerOne->getEmployeeID()) + ", expected 1");
    std::cout << endl;
    
    std::cout << "  Test Case 3: children of same parent node" << endl;
    Employee* closestManagerTwo = Orgtree::findClosestSharedManager(head, 7, 8);
    assert(closestManagerTwo->getEmployeeID() == 3, "Shared manager between 7 and 8 returns " + to_string(closestManagerTwo->getEmployeeID()) + ", expected 3");
    std::cout << endl;

    std::cout << "  Test Case 4: One Employee Not In Tree" << endl;
    Employee* closestManagerThree = Orgtree::findClosestSharedManager(head, 4, 99);
    assert(closestManagerThree->getEmployeeID() == 4, "Shared manager between 4 and 99 returns " + to_string(closestManagerThree->getEmployeeID()) + ", expected 4");
    std::cout << endl;

    std::cout << "  Test Case 5: Both Employees Not In Tree" << endl;
    Employee* closestManagerFour = Orgtree::findClosestSharedManager(head, 98, 99);
    if (closestManagerFour == nullptr) {
        assert(-1 == -1, "Shared manager between 98 and 99 returns nullptr, expected nullptr"); 
    }
    else {
        "Values not present in tree but nullptr not returned, test failed";
    }
    std::cout << endl << endl << endl;
    
    


    std::cout << "*** Test findNumOfManagersBetween function ***" << endl << endl;

    std::cout << "  Test Case 1: " << endl;
    int numManagers = Orgtree::findNumOfManagersBetween(head, 10, 11);
    assert(numManagers == 3, "Managers between 10 and 11 returns " + to_string(numManagers) + ", expected 3");
    std::cout << endl;


    std::cout << "  Test Case 2: " << endl;
    int numManagersOne = Orgtree::findNumOfManagersBetween(head, 10, 12);
    assert(numManagersOne == 5, "Managers between 10 and 12 returns " + to_string(numManagersOne) + ", expected 5");
    std::cout << endl;
    
    std::cout << "  Test Case 3: " << endl;
    int numManagersTwo = Orgtree::findNumOfManagersBetween(head, 7, 8);
    assert(numManagersTwo == 1, "Managers between 7 and 8 returns " + to_string(numManagersTwo) + ", expected 1");
    std::cout << endl;

    std::cout << "  Test Case 4: One Employee Not in Tree" << endl;
    int numManagersThree = Orgtree::findNumOfManagersBetween(head, 7, 99);
    assert(numManagersThree == -1, "Managers between 7 and 99 returns " + to_string(numManagersThree) + ", expected -1");
    std::cout << endl;

    std::cout << "  Test Case 5: Two Employees Not in Tree" << endl;
    int numManagersFour = Orgtree::findNumOfManagersBetween(head, 98, 99);
    assert(numManagersFour == -1, "Managers between 98 and 99 returns " + to_string(numManagersFour) + ", expected -1");
    std::cout << endl << endl << endl;
   

    
    std::cout << "*** Prepare to Delete Tree ***" << endl << endl;
    std::cout << "Will Print Nodes In Order Deleted......." << endl << endl;
    Orgtree::deleteOrgtree(head);



    /* Second Tree Test Case Has Only One Node*/

    std::cout << endl << endl << endl << "Building Tree Two - One-Node Tree" << endl << "_______________________________________________________" << endl << endl << endl;
    
    head = new Employee(1);

    Orgtree::printOrgTree(head);

    std::cout << "_______________________________________________________" << endl << endl;


    std::cout << endl << "Begin Testing" << endl << endl << endl << endl;




    std::cout << "*** Test isEmployeePresentInOrg function ***" << endl << endl;
    
    std::cout << "  Test Case 1: Employee Present" << endl;
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 1);
    assert(employeePresent, "ID 1 Present in tree");
    std::cout << endl;

    std::cout << "  Test Case 2: Employee Not Present" << endl;
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 99);
    assert(employeePresent == false, "ID 99 Not present in tree");
    std::cout << endl << endl << endl;



    std::cout << "*** Test findEmployeeLevel function ***" << endl << endl;

    std::cout << "  Test Case 1: Employee Present" << endl;
    employeeLevel = Orgtree::findEmployeeLevel(head, 1, 0);
    assert(employeeLevel == 0, "Level of ID 1 returns " + to_string(employeeLevel) + ", expected 0");
    std::cout << endl;

    
    std::cout << "  Test Case 2: Employee Not Present" << endl;
    employeeLevelEmpty = Orgtree::findEmployeeLevel(head, 99, 0);
    assert(employeeLevelEmpty == -1, "Level of ID 99 returns " + to_string(employeeLevelEmpty) + ", expected -1");
    std::cout << endl << endl << endl;




    std::cout << "*** Test findClosestSharedManager function ***" << endl << endl;

    std::cout << "  Test Case 1: " << endl;
    closestManager = Orgtree::findClosestSharedManager(head, 1, 3);
    assert(closestManager->getEmployeeID() == 1, "Shared manager between 1 and 3 returns " + to_string(closestManager->getEmployeeID()) + ", expected 1");
    std::cout << endl;

    std::cout << "  Test Case 2: " << endl;
    closestManagerOne = Orgtree::findClosestSharedManager(head, 1, -1);
    assert(closestManagerOne->getEmployeeID() == 1, "Shared manager between 1 and -1 returns " + to_string(closestManagerOne->getEmployeeID()) + ", expected 1");
    std::cout << endl;

    std::cout << "  Test Case 3: " << endl;
    closestManagerTwo = Orgtree::findClosestSharedManager(head, 3, 5);
    if (closestManagerTwo == nullptr) {
        assert(-1 == -1, "Shared manager between 98 and 99 returns nullptr, expected nullptr"); 
    }
    else {
        "Values not present in tree but nullptr not returned, test failed";
    }    std::cout << endl << endl << endl;




    std::cout << "*** Test findNumOfManagersBetween function ***" << endl << endl;

    std::cout << "  Test Case 1: " << endl;
    numManagers = Orgtree::findNumOfManagersBetween(head, 1, 1);
    assert(numManagers == -1, "Managers between 1 and 1 returns " + to_string(numManagers) + ", expected -1");
    std::cout << endl;

    std::cout << "  Test Case 2: One Employee Not in Tree" << endl;
    numManagersOne = Orgtree::findNumOfManagersBetween(head, 1, 99);
    assert(numManagersOne == -1, "Managers between 1 and 99 returns " + to_string(numManagersOne) + ", expected -1");
    std::cout << endl;

    std::cout << "  Test Case 3: Two Employee Not in Tree" << endl;
    numManagersTwo = Orgtree::findNumOfManagersBetween(head, 98, 99);
    assert(numManagersTwo == -1, "Managers between 98 and 99 returns " + to_string(numManagersTwo) + ", expected -1");
    std::cout << endl << endl << endl;




    std::cout << "*** Prepare to Delete Tree ***" << endl << endl;
    std::cout << "Will Print Nodes In Order Deleted......." << endl << endl;
    Orgtree::deleteOrgtree(head);

    
    /* Three Tree Test Case Has No Nodes*/
    
    std::cout << endl << endl << endl << "Building Tree Three - Zero-Node Tree" << endl << "_______________________________________________________" << endl << endl << endl;
    

    Orgtree::printOrgTree(nullptr);

    std::cout << "_______________________________________________________" << endl << endl;


    std::cout << endl << "Begin Testing" << endl << endl << endl << endl;




    std::cout << "*** Test isEmployeePresentInOrg function ***" << endl << endl;
    
    std::cout << "  Test Case 1: " << endl;
    employeePresent = Orgtree::isEmployeePresentInOrg(nullptr, 1);
    assert(employeePresent == false, "ID 1 not Present in tree");
    std::cout << endl << endl;




    std::cout << "*** Test findEmployeeLevel function ***" << endl << endl;

    std::cout << "  Test Case 1: " << endl;
    employeeLevel = Orgtree::findEmployeeLevel(nullptr, 1, 0);
    assert(employeeLevel == -1, "Level of ID 1 returns " + to_string(employeeLevel) + ", expected -1");
    std::cout << endl << endl;




    std::cout << "*** Test findClosestSharedManager function ***" << endl << endl;

    std::cout << "  Test Case 1: Both employees not in tree" << endl;
    closestManagerTwo = Orgtree::findClosestSharedManager(nullptr, 98, 99);
    if (closestManagerTwo == nullptr) {
        assert(-1 == -1, "Shared manager between 98 and 99 returns nullptr, expected nullptr"); 
    }
    else {
        "Values not present in tree but nullptr not returned, test failed";
    }    std::cout << endl << endl;




    std::cout << "*** Test findNumOfManagersBetween function ***" << endl << endl;

       std::cout << "  Test Case 1: Both Employee Not in Tree" << endl;
    numManagersTwo = Orgtree::findNumOfManagersBetween(nullptr, 98, 99);
    assert(numManagersTwo == -1, "Managers between 98 and 99 returns " + to_string(numManagersTwo) + ", expected -1");
    std::cout << endl << endl;



    std::cout << "*** Prepare to Delete Tree ***" << endl << endl;
    std::cout << "Will Print Nodes In Order Deleted......." << endl << endl;
    Orgtree::deleteOrgtree(nullptr);
    std::cout << endl << endl;


    /* Fourth Tree Test Case Build This Tree To Check Deletion Order
    *              1
    *           /    \
    *           2    3
    *          / \  / \
    *          5 6  7 8
    */

    std::cout << endl << endl << "Building Tree Four - Full Tree 2 (With Test of Delete Post Traversal)" << endl << "_______________________________________________________" << endl << endl;

    head = new Employee(1, vector<int>{2, 3});
    e2 = head->getDirectReports().at(0);
    e3 = head->getDirectReports().at(1);

    e2->addDirectReports(vector<int>{5, 6});
    e3->addDirectReports(vector<int>{7, 8});

    e5 = e2->getDirectReports().at(0);
    e6 = e2->getDirectReports().at(1);
    Employee* e7 = e3->getDirectReports().at(0);
    Employee* e8 = e3->getDirectReports().at(1);


    Orgtree::printOrgTree(head);
    
    
    std::cout << "_______________________________________________________" << endl << endl;


    std::cout << endl << "Begin Testing" << endl << endl << endl << endl;


    std::cout << "*** Test isEmployeePresentInOrg function ***" << endl << endl;
    
    std::cout << "  Test Case 1: Employee Present" << endl;
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 6);
    assert(employeePresent, "ID 6 Present in tree");
    std::cout << endl;

    std::cout << "  Test Case 2: Employee Not Present" << endl;
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 99);
    assert(employeePresent == false, "ID 99 Not present in tree");
    std::cout << endl << endl << endl;


    

    std::cout << "*** Test findEmployeeLevel function ***" << endl << endl;

    std::cout << "  Test Case 1: Employee Present - 0th level" << endl;
    employeeLevel = Orgtree::findEmployeeLevel(head, 1, 0);
    assert(employeeLevel == 0, "Level of ID 1 returns " + to_string(employeeLevel) + ", expected 0");
    std::cout << endl;


    std::cout << "  Test Case 1: Employee Present - 1st level" << endl;
    employeeLevelOne = Orgtree::findEmployeeLevel(head, 2, 0);
    assert(employeeLevelOne == 1, "Level of ID 4 returns " + to_string(employeeLevelOne) + ", expected 1");
    std::cout << endl;

    std::cout << "  Test Case 2: Employee Present - Deep level" << endl;
    employeeLevelTwo = Orgtree::findEmployeeLevel(head, 5, 0);
    assert(employeeLevelTwo == 2, "Level of ID 5 returns " + to_string(employeeLevelTwo) + ", expected 2");
    std::cout << endl;


    std::cout << "  Test Case 3: Employee Not Present" << endl;
    employeeLevelEmpty = Orgtree::findEmployeeLevel(head, 99, 0);
    assert(employeeLevelEmpty == -1, "Level of ID 99 returns " + to_string(employeeLevelEmpty) + ", expected -1");
    std::cout << endl << endl << endl;




    std::cout << "*** Test findClosestSharedManager function ***" << endl << endl;

    std::cout << "  Test Case 1: children of different parent nodes" << endl;
    closestManager = Orgtree::findClosestSharedManager(head, 5, 8);
    assert(closestManager->getEmployeeID() == 1, "Shared manager between 5 and 8 returns " + to_string(closestManager->getEmployeeID()) + ", expected 1");
    std::cout << endl;

    std::cout << "  Test Case 2: Children at different levels" << endl;
    closestManagerOne = Orgtree::findClosestSharedManager(head, 2, 5);
    assert(closestManagerOne->getEmployeeID() == 2, "Shared manager between 2 and 5 returns " + to_string(closestManagerOne->getEmployeeID()) + ", expected 2");
    std::cout << endl;
    
    std::cout << "  Test Case 3: children of same parent node" << endl;
    closestManagerTwo = Orgtree::findClosestSharedManager(head, 5, 6);
    assert(closestManagerTwo->getEmployeeID() == 2, "Shared manager between 5 and 6 returns " + to_string(closestManagerTwo->getEmployeeID()) + ", expected 2");
    std::cout << endl;

    std::cout << "  Test Case 4: One Employee Not In Tree" << endl;
    closestManagerThree = Orgtree::findClosestSharedManager(head, 5, 99);
    assert(closestManagerThree->getEmployeeID() == 5, "Shared manager between 5 and 99 returns " + to_string(closestManagerThree->getEmployeeID()) + ", expected 5");
    std::cout << endl;

    std::cout << "  Test Case 5: Both Employees Not In Tree" << endl;
    closestManagerFour = Orgtree::findClosestSharedManager(head, 98, 99);
    if (closestManagerFour == nullptr) {
        assert(-1 == -1, "Shared manager between 98 and 99 returns nullptr, expected nullptr"); 
    }
    else {
        "Values not present in tree but nullptr not returned, test failed";
    }
    std::cout << endl << endl << endl;
    
    


    std::cout << "*** Test findNumOfManagersBetween function ***" << endl << endl;

    std::cout << "  Test Case 1: " << endl;
    numManagers = Orgtree::findNumOfManagersBetween(head, 5, 8);
    assert(numManagers == 3, "Managers between 5 and 8 returns " + to_string(numManagers) + ", expected 3");
    std::cout << endl;


    std::cout << "  Test Case 2: " << endl;
    numManagersOne = Orgtree::findNumOfManagersBetween(head, 1, 8);
    assert(numManagersOne == 1, "Managers between 1 and 8 returns " + to_string(numManagersOne) + ", expected 1");
    std::cout << endl;
    
    std::cout << "  Test Case 3: " << endl;
    numManagersTwo = Orgtree::findNumOfManagersBetween(head, 5, 6);
    assert(numManagersTwo == 1, "Managers between 5 and 6 returns " + to_string(numManagersTwo) + ", expected 1");
    std::cout << endl;

    std::cout << "  Test Case 4: One Employee Not in Tree" << endl;
    numManagersThree = Orgtree::findNumOfManagersBetween(head, 5, 99);
    assert(numManagersThree == -1, "Managers between 7 and 99 returns " + to_string(numManagersThree) + ", expected -1");
    std::cout << endl;

    std::cout << "  Test Case 5: Two Employees Not in Tree" << endl;
    numManagersFour = Orgtree::findNumOfManagersBetween(head, 98, 99);
    assert(numManagersFour == -1, "Managers between 98 and 99 returns " + to_string(numManagersFour) + ", expected -1");
    std::cout << endl << endl << endl;



    std::cout << "*** Prepare to Delete Tree ***" << endl << endl;
    std::cout << "Will Print Nodes In Order Deleted......." << endl << endl;
    std::cout << "Post Order Traversal -- Expect order 5 6 2 7 8 3 1" << endl << endl;
    Orgtree::deleteOrgtree(head);
    std::cout << endl << endl;

    std::cout << "Tests Passed - Complete!" << endl;

    exit(EXIT_SUCCESS);
}