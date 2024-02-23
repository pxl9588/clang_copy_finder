#include <iostream>
#include <map>

struct Data
{
  Data() { std::cout << "Data::Data()\n"; }
  Data(const Data &) { std::cout << "Data::Data(const Data&)\n"; }
  Data &operator=(const Data &)
  {
    // When does this trigger?
    std::cout << "Data::operator=(const Data&)\n";
    return *this;
  }
  Data(Data &&) { std::cout << "Data::Data(Data&&)\n"; }
  Data &operator=(Data &&)
  {
    // When does this trigger?
    std::cout << "Data::operator=(Data&&)\n";
    return *this;
  }
};

int main()
{
  std::cout << "Created map\n";
  std::map<int, Data> aMap = {{1, Data()}, {2, Data()}};
  std::cout << "Expecting to call &operator=(const Data&)\n";
  const Data d1 = Data();
  Data d2;
  d2 = d1;
  std::cout << "Start of loops\n";
  for (const std::pair<int, Data> &value : aMap)
  {
    std::cout << value.first << '\n';
  };
  // without copy assignment
  for (const std::pair<const int, Data> &value : aMap)
  {
    std::cout << value.first << '\n';
  };
  for (const std::map<int, Data>::value_type &value : aMap)
  {
    std::cout << value.first << '\n';
  };
}
