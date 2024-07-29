#pragma once
class String {
private:
	char* data;
	size_t size;

public:
	String();
	String(const char* str);
	String(size_t repeats, char sym);
	String(const String& other); // lvalue-reference
	String(String&& other) noexcept; // rvalue-reference, .
	~String();

	void print() const;

	String& operator=(const char* str);
	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	String operator+(const char* other) const;
	String operator+(const String& other) const;

	String& insert(size_t index, size_t count, char sym);
	String& insert(size_t index, const String& str);

	String& replace(size_t pos, size_t count, size_t count2, char sym);
	String& replace(size_t pos, size_t count, const String& str);
	
	size_t find(const String& str, size_t pos = 0)const;
	size_t find(const String& str, size_t pos, size_t count)const;

};