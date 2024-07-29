#include "String.hpp"
#include <iostream>
String::String() : size(0) {
	data = new char[1] { '\0' };
}

String::String(const char* str) {
	size_t counter{}; 
	while (*(str + counter++) != '\0');
	data = new char[counter];
	for (size_t i{}; i < counter; ++i)
		data[i] = str[i];
	size = counter - 1;
}

String::String(size_t repeats, char sym) : size(repeats) {
	data = new char[repeats + 1];
	for (size_t i = 0; i < repeats; ++i)
		data[i] = sym;
	data[repeats] = '\0';

}

String::String(const String& other) : size(other.size) {
	data = new char[size + 1];
	for (size_t i{}; i < size + 1; ++i)
		data[i] = other.data[i];
}

String::String(String&& other) noexcept : String() {
	// std::cout << "Move-constructor\n";
	std::swap(data, other.data);
	std::swap(size, other.size);
}

String::~String() {
	delete[] data;
}

void  String::print() const {
	std::cout << data << std::endl;
}

String& String::operator=(const char* str) {
	delete[] data;

	size_t counter{}; 
	while (*(str + counter++) != '\0');
	data = new char[counter];
	for (size_t i{}; i < counter; ++i)
		data[i] = str[i];
	size = counter - 1;

	return *this;
}

String& String::operator=(const String& other) {
	delete[] data;

	size = other.size;
	data = new char[size + 1];
	for (size_t i{}; i < size + 1; ++i)
		data[i] = other.data[i];

	return *this;
}
String& String::operator=(String&& other) noexcept {
	std::swap(data, other.data);
	std::swap(size, other.size);
	return *this;
}
String String::operator+(const char* other) const {
	return String();
}
String String::operator+(const String& other) const {
	return String();
}

String& String::insert(size_t index, size_t count, char sym) {
	if (index > size)
		throw std::exception("Index is so big!");
	if (count == 0) {
		return *this;
	}
	String tmp = new char[size + 1 + count];
	tmp.size = size + count;
	if (index != 0)
		for (size_t i{}; i < index; ++i) {
			tmp.data[i] = this->data[i];
		}
	for (size_t i{ index }, j = 0; j < count; ++i, ++j) {
		tmp.data[i] = sym;
	}
	if (index != size)
		for (size_t i{ index + count }, j{ 0 }; i < tmp.size; ++i, ++j) {
			tmp.data[i] = this->data[index + j];
		}
	delete[] data;
	size = tmp.size;
	data = new char[size + 1];
	for (size_t i{}; i < size + 1; ++i) {
		data[i] = tmp.data[i];
	}
	data[size] = '\0';
	return *this;
}

String& String::insert(size_t index, const String& str) {
	if (index > size)
		throw std::exception("Index is so big!");
	String tmp = new char[size + 1 + str.size];
	tmp.size = size + str.size;
	if (index != 0)
		for (size_t i{}; i < index; ++i) {
			tmp.data[i] = this->data[i];
		}
	for (size_t i{ index }, j = 0; j < str.size; ++i, ++j) {
		tmp.data[i] = str.data[j];
	}
	if (index != size)
		for (size_t i{ index + str.size }, j{ 0 }; i < tmp.size; ++i, ++j) {
			tmp.data[i] = this->data[index + j];
		}
	delete[] data;
	size = tmp.size;
	data = new char[size + 1];
	for (size_t i{}; i < size + 1; ++i) {
		data[i] = tmp.data[i];
	}
	data[size] = '\0';
	return *this;
}

String& String::replace(size_t pos, size_t count, size_t count2, char sym) {
	if (pos > size)
		throw std::exception("No found");
	if (pos + count2 - count >= size)
		throw std::exception("The string is overflow!");
	String tmp = new char[size + 1 - count + count2];
	tmp.size = size - count + count2;
	if (pos != 0)
		for (size_t i{}; i < pos; ++i) {
			tmp.data[i] = this->data[i];
		}
	for (size_t i{ pos }, j = 0; j < count2; ++i, ++j) {
		tmp.data[i] = sym;
	}
	if (pos != size)
		for (size_t i{ pos + count2 }, j{ 0 }; i < tmp.size; ++i, ++j) {
			tmp.data[i] = this->data[pos + count + j];
		}
	delete[] data;
	size = tmp.size;
	data = new char[size + 1];
	for (size_t i{}; i < size + 1; ++i) {
		data[i] = tmp.data[i];
	}
	data[size] = '\0';
	return *this;
}

String& String::replace(size_t pos, size_t count, const String& str) {
	if (pos > size)
		throw std::exception("No found");
	if (pos + str.size - count >= size)
		throw std::exception("Size of str is so big!");
	String tmp = new char[size + 1 - count + str.size];
	tmp.size = size + str.size;
	if (pos != 0)
		for (size_t i{}; i < pos; ++i) {
			tmp.data[i] = this->data[i];
		}
	for (size_t i{ pos }, j = 0; j < str.size; ++i, ++j) {
		tmp.data[i] = str.data[j];
	}
	if (pos != size)
		for (size_t i{ pos + str.size }, j{ 0 }; i < tmp.size; ++i, ++j) {
			tmp.data[i] = this->data[pos + count + j];
		}
	delete[] data;
	size = tmp.size;
	data = new char[size + 1];
	for (size_t i{}; i < size + 1; ++i) {
		data[i] = tmp.data[i];
	}
	data[size] = '\0';
	return *this;
}

size_t String::find(const String& str, size_t pos) const {
	if (pos > size)
		throw std::exception("No found");
	size_t tmp_pos = 0;
	size_t count = 0;
	for (size_t i{ pos }; i < size; ++i) {
		if (data[i] == str.data[0]) {
			tmp_pos = i;
			count = 1;
			for (size_t j{ 1 }; j < str.size; ++j) {
				if (data[i + j] == str.data[j])
					++count;
				else
					break;
			}
		}
		if (count == str.size) {
			return tmp_pos;
		}
	}
	return -1;
}

size_t String::find(const String& str, size_t pos, size_t count) const {
	if (pos > size)
		throw std::exception("No found");
	if (count > str.size)
		throw std::exception("Count is so big than Size of str!");
	size_t tmp_pos = 0;
	size_t my_count = 0;
	for (size_t i{ pos }; i < size; ++i) {
		if (data[i] == str.data[0]) {
			tmp_pos = i;
			my_count = 1;
			for (size_t j{ 1 }; j < count; ++j) {
				if (data[i + j] == str.data[j])
					++my_count;
				else
					break;
			}
		}
		if (my_count == count) {
			return tmp_pos;
		}
	}
	return -1;
}