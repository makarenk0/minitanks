#include "toolbox.h"

void saveFile(std::string &file) {
  char const *filterPatterns[2] = {"*.txt", "*.bcm"};
  char const *saveFile = tinyfd_saveFileDialog("Save map", "\\map_default.bcm",
                                               2, filterPatterns, NULL);
  if (saveFile == NULL || saveFile == "cancel") {
  } else {
    std::ofstream myfile(saveFile);
    if (myfile.is_open()) {
      myfile << file;
      myfile.close();
    }
  }
}

std::string openFile() {
  char const *filterPatterns[2] = {"*.txt", "*.bcm"};
  char const *fileAddress = tinyfd_openFileDialog(
      "Open map", "\\map_default.bcm", 2, filterPatterns, NULL, 0);
  if (fileAddress == NULL || fileAddress == "cancel") {

  } else {
	  std::string output;
	  std::ifstream nameFileout;
	  nameFileout.open(fileAddress);
	  std::string line;
	  while (std::getline(nameFileout, line))
	  {
		  output.append(line);
		  output.append("\n");
		  // TODO: assign item_name based on line (or if the entire line is 
		  // the item name, replace line with item_name in the code above)
	  }
	  return output;
  }
}
