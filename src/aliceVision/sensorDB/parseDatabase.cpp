// This file is part of the AliceVision project.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "parseDatabase.hpp"

#include <aliceVision/sensorDB/Datasheet.hpp>

#include <dependencies/stlplus3/filesystemSimplified/file_system.hpp>

#include <boost/algorithm/string.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>

namespace aliceVision {
namespace sensorDB {

bool parseDatabase(const std::string& databaseFilePath, std::vector<Datasheet>& databaseStructure)
{
  std::ifstream iFilein( databaseFilePath );
  if(!iFilein || !stlplus::is_file(databaseFilePath))
    return false;

  std::string line;
  while(iFilein.good())
  {
    getline( iFilein, line);
    if(!line.empty())
    {
      //std::stringstream sStream( line );
      if(line[0] != '#')
      {
        std::vector<std::string> values;
        boost::split(values, line, boost::is_any_of(";"));

        if(values.size() == 3)
        {
          const std::string brand = values[0];
          const std::string model = values[1];
          const double sensorSize = std::stod(values[2]);
          databaseStructure.emplace_back(brand, model, sensorSize);
        }
      }
    }
  }
  return true;
}

bool getInfo(const std::string& brand, const std::string& model, const std::vector<Datasheet>& databaseStructure, Datasheet& datasheetContent)
{
  bool existInDatabase = false;

  Datasheet refDatasheet(brand, model, -1.);
  auto datasheet = std::find(databaseStructure.begin(), databaseStructure.end(), refDatasheet);
  if(datasheet != databaseStructure.end())
  {
    datasheetContent = *datasheet;
    existInDatabase = true;
  }
  return existInDatabase;
}

} // namespace sensorDB
} // namespace aliceVision
