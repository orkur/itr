#include <string>

class MenuItem
{
 public:
  int index();
  bool highlighted();
  void setHighlight (const bool &h);
  std::string label();
  void setLabel(std::string l);
 private:
  bool m_highlighted;
  int m_index;
  std::string m_label;
};
