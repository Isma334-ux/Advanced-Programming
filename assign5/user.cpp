#include "user.h"
#include <algorithm>

User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

User::~User() {
    delete[] _friends;
}

User::User(const User& other)
  : _name(other._name)
  , _size(other._size)
  , _capacity(other._capacity)
{
    _friends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _friends[i] = other._friends[i];
    }
}

User& User::operator=(const User& other) {
    if (this != &other) {
        delete[] _friends;
        
        _name = other._name;
        _size = other._size;
        _capacity = other._capacity;
        
        _friends = new std::string[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            _friends[i] = other._friends[i];
        }
    }
    return *this;
}

void User::add_friend(const std::string& name) {
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

std::string User::get_name() const {
  return _name;
}

size_t User::size() const {
  return _size;
}

void User::set_friend(size_t index, const std::string& name) {
  _friends[index] = name;
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "User(name=" << user._name << ", friends=[";
    for (size_t i = 0; i < user._size; ++i) {
        if (i != 0) os << ", ";
        os << user._friends[i];
    }
    os << "])";
    return os;
}

User& User::operator+=(User& other) {
    this->add_friend(other.get_name());
    other.add_friend(this->get_name());
    return *this;
}

bool User::operator<(const User& other) const {
    return this->_name < other._name;
}