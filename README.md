# libDEMO2  

**!work in progress!**

It's a small demo of a library management system. It is made for learning object oriented c++ purpose and surely shouldn't be implemented in a real librarian environment - the program mainly processes few .txt files, so they are **not encrypted** and can be dangerous for the real life use. 



#### Existing functionality:

- [x] Adding new books to the memory
- [x] Finding books in the memory
- [x] Deleting books from the memory
- [x] Adding new users
- [x] Getting information about certain users from the memory
- [x] Deleting users from memory
- [x] Adding books to user's account
- [x] Fast access to all of the books user possesses 

- [x] Ability to edit already existing books
- [x] Ability to edit already existing users

There are no more planned functions to be made

---

##### Fixed issues:

- [x] No reload of data in both tables after clicking 'Return the book' nor messagebox to approve the action (which is done in the background) 
- [x] When user's account is deleted there is no mechanism to remove his possessions in book.txt record (block the action)
- [x] When book is deleted, user's counter is not decreased (block the action)
- [x] 'Find the book' method not wiping previous searches
- [x] The whole project needs validation of data (year as only 4 number char; email contains '@' etc.)
- [x] ID and emails could be reused for many users (validated)
- [x] 'Delete the user' when clicked shown error about books not being returned, even tho the counter was on 0 (fix: 0 != '0');
- [x] 'Delete the user' was wrongly operating on a file, so every time a user was deleted - the whole Users.txt was gone for the program
- [x] ID numbers could be partly reused which entirely broke the code (limited the numbers of digits to 9 and only 9)
- [x] 'Edit the User' didn't actually edit the user (only changed the data on a table)

##### Known issues to fix:

- [ ] Testing in progress

