// import employee;   // imports NOT CURRENTLY WORKING. FIGURE IT OUT.

#include <iostream>
#include <any>      // std::any, std::make_any, std::any_cast<T&>(some any variable)
#include <cstdlib>  // for EXIT_SUCCESS
#include "format"   // for std::format
#include <limits>   // for std::numeric_limits
#include <compare>  // for the spaceship operator, <=>
#include <array>    // for std::array, for example - std::array<int, 100> arr {};
#include <iterator>
#include <utility>  // for std::pair
#include <optional> // for std::optional<int> or whatever T, template
#include <initializer_list>  // std::initializer_list<T> for arbitrary number of function arguments
#include <stdexcept>  // for std::invalid_argument and exceptions
#include <vector>  // for std::vector<T> container
#include <cstring> // for  C-string methods
#include <string>   // for std::string objects
#include <charconv>  // to deal with low-level numeric conversions std::to_chars(), std::from_chars(), &c. See below for examples.
// TODO: deal with smart pointers in <memory>, unique_ptr<> ptr, shared_ptr<> sptr, &c.


using s_t = std::size_t;
using IntPtr = int*;  // A Type Alias (Intro in C++11) s.t.
                      // int* p1; and
                      // IntPtr p2; are equivalent; hence, p1 = p2; or p2 = p1; is compatible and valid
                      // ** ALWAYS PREFER TYPE ALIAS OVER TYPEDEFS B/C OF ABILITY WITH TEMPLATES **

typedef int* IntegerPtr;  // Equivalent to Type Alias above

struct OddsAndEvens { std::vector<int> odds, evens; };

OddsAndEvens separateOddsAndEvens(const std::vector<int>& arr)
{
  std::vector<int> odds, evens;
  for (auto i : arr) {
    if (i % 2 == 1) {
      odds.push_back(i);
    } else {
      evens.push_back(i);
    }
  }
  return OddsAndEvens { .odds = odds, .evens = evens };
}

// Wrapper around strcpy()
char* copyString(const char* str)
{
  char* result { new char[strlen(str) + 1] };
  strcpy(result, str);     // NOTE: there are functions for secure string concatenation and copy: strcpy_s(), strcat_s(); just need the construct
                           // errno_t strncpy_s(char *restrict dest, rsize_t destsz, const char *restrict src, rsize_t count);
                           // where all is defined in <string.h>. If necessary, do research on this.
  return result;
}

// Wrapper around strcpy() and strcat()
char* appendStrings(const char* str1, const char* str2, const char* str3)
{
  char* result { new char[strlen(str1) + strlen(str2) + strlen(str3) + 1] };
  strcpy(result, str1);
  strcat(result, str2);
  strcat(result, str3);
  return result;
}

enum class PieceType : unsigned long { King = 1, Queen = 2, Rook = 3, Pawn = 4 };

std::string getString() { return "Hello, World!"; };

auto add(int num1, int num2)
{
  std::cout << std::format("Entering function \"{}\"", __func__) << std::endl;
  return num1 + num2;
}

std::optional<int> getData(bool giveIt)
{
  if (giveIt)
  {
    return 42;
  }
  return std::nullopt;   // or simply return {};
}


auto makeSum(std::initializer_list<int> vals)
{
  int total { 0 };
  for (auto val : vals) {
    total += val;
  }
  return total;
}

double divideNums(double numerator, double denominator)
{
  if (denominator == 0)
  {
    throw std::invalid_argument { "Denominator cannot be 0."};
  }
  return numerator / denominator;
}


int main(int argc, char** argv)
{
  const auto noDiceLengthPlusNullTerminator { 8 };
  const char* noDice { new char[noDiceLengthPlusNullTerminator] };

  s_t myInt {}; // initialize to 0
  std::array<char, 3> author_initals {'d', 'f', 'w'};
  std::any yourAge;
  std::any myAge { 37 };

  const char* ballerWorld { R"(Hello, "World-of-Straight-Up-Ballers"!
                              \t\n)" };  // An example of a raw string literal

  std::cout << "\n\n\n\n";

  std::cout << "myInt: " << myInt << std::endl;

  s_t i { 42 };
  std::strong_ordering result { i <=> 0 };

  if (result == std::strong_ordering::less) { std::cout << "less" << std::endl; }
  if (result == std::strong_ordering::greater) { std::cout << "more" << std::endl; } // more
  if (result == std::strong_ordering::equal) { std::cout << "equal" << std::endl; }

  std::cout << std::format("There are {} ways I love you!", 219) << std::endl;
  std::cout << "infinity: " << std::numeric_limits<double>::infinity
            << std::endl; // 1


  auto sum { add(100, 20) };
  std::cout << sum << std::endl;

  std::cout << "\n\n";

  std::cout << "Array author_initals contents: ";
  for (auto it = author_initals.begin(); it != author_initals.end(); it++)
  {
    std::cout << " " << *it << ".";
  }
  std::cout << std::endl;
  std::cout << std::format("Array author_initals size: {}", author_initals.size()) << std::endl;

  std::cout << "yourAge.has_value(): " << yourAge.has_value() << std::endl;
  std::cout << "myAge.has_value(): " << myAge.has_value() << std::endl;
  auto hubbleDeepFieldAge = std::make_any<std::string>("Hubble Deep Field Age is 13.8 billion years old.");
  std::cout << std::format("hubbleDeepFieldAge.has_value(): {}", hubbleDeepFieldAge.has_value()) << std::endl;
  std::cout << std::format("hubbleDeepFieldAge = \"{}\"", std::any_cast<std::string&>(hubbleDeepFieldAge)) << std::endl;
  hubbleDeepFieldAge.reset();
  std::cout << std::format("hubbleDeepFieldAge.has_value(): {}", hubbleDeepFieldAge.has_value()) << std::endl;

  std::pair<char, double> myPair { 'A', 3.141592 };
  std::cout << std::format("myPair: {}, {}", myPair.first, myPair.second) << std::endl;  // first and second are keywords of pair

  PieceType piece { PieceType::King };
  std::cout << std::format("King: {}", piece) << std::endl;


  std::optional<int> data1 { getData(true) };
  std::optional<int> data2 { getData(false) };

  std::cout << "data1.has_value = " << data1.has_value() << std::endl;
  if (!data2) {
    std::cout << "data2 doesn't have a value." << std::endl;
  }


  // Structured Bindings
  std::array values { 11, 22, 33 };
  auto [a, b, c] { values };
  std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;


  struct Point { double m_x, m_y, m_z; };
  Point point;
  point.m_x = 300.01; point.m_y = 500.02; point.m_z = 700.03;
  auto [ x, y, z ] { point };
  std::cout << "3-D Cartesion point: (" << x << ", " << y << ", " << z << ") " << std::endl;

  // CTAD, class template argument deductive
  std::pair<std::string, int> p { "The Boss is in the house!", 37 };
  auto [ theString, theInt ] { p };
  std::cout << std::format("theString: {}", theString) << std::endl;
  std::cout << std::format("theInt: {}", theInt) << std::endl;


  // initializer with enhanced for-loop
  for (std::array arr { 5, 4, 3, 2, 1 }; auto i : arr)
    { std::cout << i << " . . . "; }
  std::cout << std::endl;

  auto a1 { makeSum({ 2, 4, 6 }) };
  auto b1 { makeSum({ 10, 20, 30, 40, 50, 60 }) };
  std::cout << std::format("initializer_list a1, b2 from \"{}\": {}, {}", __func__, a1, b1) << std::endl;

  const std::string& str1 { getString() };
  std::cout << std::format("str1 is an example of reference-to-const,\n which is necessary for references to temporary objects: {}", str1) << std::endl;

  // You can create a reference to any type, including pointer types:
  int* intP { nullptr };
  int*& ptrRef { intP };
  ptrRef = new int;
  *ptrRef = 5;

  int varble { 3 };
  int& varbleRef { varble };
  int* varblePtr { &varbleRef };  // Address of reference is pointer to value.
  *varblePtr = 100;

  std::pair<std::string, long double> aPair { "floccinaucinihilipilificate", 3.1415926535897932384626433832795028841971};
  const auto& [toMakeMeaningless, pi] { aPair };
  std::cout << std::format("{}: v. \'to make meaningless\'\npi: {}", toMakeMeaningless, pi) << std::endl;

  // Try Catch Block
  try {
    std::cout << divideNums(2.5, 0.5) << std::endl;
    std::cout << divideNums(2.3, 0) << std::endl;
  } catch (const std::invalid_argument& exception) {
    std::cout << std::format("Exception caught: {}", exception.what()) << std::endl;
  }

  std::vector<int> vecUnSplit { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  auto oddsAndEvens { separateOddsAndEvens(vecUnSplit) };

  std::cout << "Evens: ";
  for (auto i : oddsAndEvens.evens) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  std::cout << "Odds: ";
  for (auto i : oddsAndEvens.odds) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  std::cout << std::format("\n\nEnter a string to copy with no more than {} charaters: ", noDiceLengthPlusNullTerminator);
  std::scanf("%[^\n]%*c", noDice);  // The [] is the scanset character. [^\n] tells that while the input is not a newline ('\n') take input.
                                    // Then with the %*c it reads the newline character from the input buffer (which is not read),
                                    // and the * indicates that this read in input is discarded (assignment suppression)
  auto* dest1 { new char[noDiceLengthPlusNullTerminator] };
  dest1 = copyString(noDice);
  std::printf("The string of charaters you entered for variable \"noDice\" is: \"%s\"\n\n", dest1);
  delete [] noDice;
  delete [] dest1;

  auto* dest2 { new char[100] };
  auto* s1 { new char[30] };
  auto* s2 { new char[33] };
  auto* s3 { new char[33] };
  std::printf("Enter a three separate C-strings (sizes at most 29, 32, and 32, respectively).\n");
  std::printf("String s1: ");
  std::scanf("%[^\n]%*c", s1);   // Check on these format specifiers. Come for regex specifications?
  std::printf("String s2: ");
  std::scanf("%[^\n]%*c", s2);
  std::printf("String s3: ");
  std::scanf("%[^\n]%*c", s3);
  dest2 = appendStrings(s1, s2, s3);
  std::cout << std::format("The strings concatenated with the function \"appendStrings()\" say: {}", dest2) << std::endl;

  delete [] dest2;
  delete [] s1;
  delete [] s2;
  delete [] s3;

  char theAlphabet [] { "abcdefghijklmnopqrstuvwxyz" };
  s_t alphabetSizeWithNulTerm { sizeof(theAlphabet) }; // is 27
  s_t alphabetSize { strlen(theAlphabet) }; // is 26
  std::cout << std::format("The size of the alphabet with NUL terminator: {}", alphabetSizeWithNulTerm) << std::endl;
  std::cout << std::format("The size of the alphabet without the NUL terminator: {}", alphabetSize) << std::endl << std::endl;

  std::cout << ballerWorld << std::endl;  // displaying a raw string literal

  std::string wallace { "wallace" };  // a string object, where since C++20 std::string is a constexpr class, meaning
                                      // that string can be sued to perform operations at compile time and that
                                      // it can be used in the implementation of constexpr functions and classes.
  std::string gromit { "gromit" };
  std::string WallaceAndGromit = wallace + " and " + gromit;  // string object concatenation like python (and Java?)
  std::cout << WallaceAndGromit << std::endl;

  // NOT CURRENTLY WORKING
  // auto res { gromit <=> wallace };   // spaceship operator
  // if (is_lt(res))
  //   { std::cout << "gromit is less than wallace" << std::endl; }
  // if (is_gt(res))
  //   { std::cout << "gromit is greater than wallace" << std::endl; }
  // if (is_eq(res))
  //   { std::cout << "gromit is equal to wallace" << std::endl; }


  // SEE: https://www.cplusplus.com/reference/string/string/
  std::string strHello { "Hello!!" };
  std::string strWorld { "The World . . ." };
  auto position { strHello.find("!!") };
  std::cout << position << std::endl;
  if (position != std::string::npos) {
    // Found the "!!" substring, now replace it.
    auto startingPositionOfSubstring { 3 };
    auto substringReplacementLength { 6 };
    strHello.replace(position, 2, strWorld.substr(startingPositionOfSubstring, substringReplacementLength));
  }
  std::cout << strHello << std::endl;

  // DON'T FORGET: std::string to_string(T val)
  // EXAMPLE: long double d { 2.71828L };
  //          std::string s { to_string(d) };

  // EXAMPLE:
  const std::string toParse { "    123USD" };
  s_t index { 0 };
  int value { stoi(toParse, &index) };
  std::cout << std::format("Parsed value: {}", value) << std::endl;
  std::cout << std::format("First non-parsed character: '{}'", toParse[index]) << std::endl;

  // LOW-LEVEL NUMERIC CONVERSIONS:
  // You should use these functions if you want highly performant, perfect round-tripping (see pg. 98),
  // locale-independent conversions, for example to serialize/deserialize numerical data to/from
  // human-readable formats such as JSON, XML, and so on.
  // REFERENCE: https://en.cppreference.com/w/cpp/error/errc

  // Basis:
  // struct to_chars_result {
  //   char* ptr;
  //   std::errc ec;
  // };

  // struct from_chars_result {
  //   const char* ptr;
  //   std::errc ec;
  // };


  const s_t BufferSize { 50 };
  std::string out(BufferSize, ' '); // A string of BufferSize space characters

  auto resultingChar { std::to_chars(out.data(), out.data() + out.size(), 12345) };
  if (resultingChar.ec == std::errc())
    { std::cout << out << std::endl; /* Conversion successful */ }

  auto [ptr, error] { std::to_chars(out.data(), out.data() + out.size(), 123456789) };
  if (error == std::errc())
    { std::cout << out << std::endl; /* Conversion successful */ }

  //-------------------------------------------------------------------------------------------------
  // Perfect round-tripping with to_chars() and from_chars()
  // auto value1 { 0.314 };
  // auto [ptr1, error1] { std::to_chars(out.data(), out.data() + out.size(), value1) };
  // if (error1 == std::errc())
  //   { std::cout << out << std::endl; /* Conversion successful */ }

  // double value2;
  // auto [ptr2, error2] { std::from_chars(out.data(), out.data() + out.size(), value2) };
  // if (error2 == std::errc()) {
  //   if (value1 == value2) {
  //     std::cout << "Perfect roundtrip" << std::endl;
  //   } else {
  //     std::cout << "Not perfect roundtrip?!?" << std::endl;
  //   }
  // }
  //-------------------------------------------------------------------------------------------------
  // ERROR MSGs (for above):
  // playground.cpp:348:25: error: call to deleted function 'to_chars'
  // auto [ptr1, error1] { std::to_chars(out.data(), out.data() + out.size(), value1) };
  //
  // playground.cpp:348:8: error: variable has incomplete type 'void'
  // auto [ptr1, error1] { std::to_chars(out.data(), out.data() + out.size(), value1) };
  //
  // Throws the same errors for std::from_chars() and ptr2, so there are 4 errors in total
  // TODO: figure out why this is . . .
  //-------------------------------------------------------------------------------------------------






  std::cout << "\n\n\n\n";


  // .cppm FILES NOT CURRENTLY WORKING
  // Employee emp;
  // emp.firstInitial = 'J';
  // emp.lastInitial = 'D';
  // emp.employeeNum = 42;
  // emp.salary = 120000;
  //
  // std::cout << std::format("Employee: {}{}", emp.firstInitial, emp.lastInitial) << std::endl;
  // std::cout << std::format("Number: {}", emp.employeeNum) << std::endl;
  // std::cout << std::format("Salary: {}", emp.salary) << std::endl;


  return EXIT_SUCCESS;
}
