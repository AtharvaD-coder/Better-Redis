#pragma once
#include <exception>
#include <string>

class BucketFullException : public std::exception {
  private:
	std::string message;

  public:
	BucketFullException(const std::string& msg);
	BucketFullException() : message("Bucket is full!") {}

	const char* what() const noexcept override { return message.c_str(); }
};

class SegmentFullException : public std::exception {
  private:
	std::string message;

  public:
	SegmentFullException(const std::string& msg);
	SegmentFullException() : message("Segment is full!") {}

	const char* what() const noexcept override { return message.c_str(); }
};
