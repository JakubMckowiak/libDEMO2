

# libDEMO2  

**!work in progress!**

It's a small demo of a library management system. It is made for learning object oriented c++ purpose and surely shouldn't be implemented in a real librarian environment - the program mainly processes few .txt files, so they are **not encrypted** and can be dangerous for the real life use. 

Existing functionality:

- [x] Adding new books to the memory
- [x] Finding books in the memory
- [x] Deleting books from the memory
- [x] Adding new users
- [x] Getting information about certain users from the memory
- [x] Deleting users from memory

- [ ] Adding books to a user account (NEED'S REWORKING!)

Planned functionality:

- [ ] By double clicking User's row, access all of the books he possesses 

Known issues to fix:

- [ ] No reload of data in both tables after clicking 'Return the book' nor messagebox to approve the action (which is done in the background) 

- [ ] When user's account is deleted there is no mechanism to remove his possessions in book.txt record (to block or the construct the method)

- [ ] When book is deleted, user's counter is not decreased (block or construct the method)

- [ ] The whole project needs validation of data

  
