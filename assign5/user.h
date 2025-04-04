/*
 * CS106L Assignment 5: TreeBook
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

 #include <iostream>
 #include <string>
 
 class User
 {
 public:
   User(const std::string& name);
   ~User();
   
   // Copy operations
   User(const User& other);
   User& operator=(const User& other);
   
   // Move operations (deleted)
   User(User&& other) = delete;
   User& operator=(User&& other) = delete;
   
   // Member functions
   void add_friend(const std::string& name);
   std::string get_name() const;
   size_t size() const;
   void set_friend(size_t index, const std::string& name);
   
   // Operator overloads
   User& operator+=(User& other);
   bool operator<(const User& other) const;
   
   // Friend function for output
   friend std::ostream& operator<<(std::ostream& os, const User& user);
 
 private:
   std::string _name;
   std::string* _friends;
   size_t _size;
   size_t _capacity;
 };