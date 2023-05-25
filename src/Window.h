class Window
{
 public:
  static bool isFullscreen();
  static void changeFullscreen();
  static std::string resolutionLabel();
  static void changeRes(const int &w, const int &h);
 private:
  static std::string m_resolutionString;
  static int m_currentWidth;
  static int m_currentHeight;
};
