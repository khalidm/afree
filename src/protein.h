#ifndef CMDLPARSE
#define CMDLPARSE

class Protein {
private:
  std::string header;
  std::string sequence;
  int length;

public:
  Protein();
  ~Protein();
  // void setHeader(string h);
  // void setSequence(string s);
  // void setLength(int l);
  // void getHeader();
  // void getSequence();
  // void getLength();

  void setHeader(string h);

  void setSequence(string s);

  void setLength(int l);

  void getHeader();

  void getSequence();

  void getLength();
};

#endif
