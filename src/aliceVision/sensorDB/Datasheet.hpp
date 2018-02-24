// This file is part of the AliceVision project.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <string>
#include <utility>

namespace aliceVision {
namespace sensorDB {

/**
 * @brief The Database structure
 */
struct Datasheet
{
  Datasheet() = default;

    /**
   * @brief Datasheet Constructor
   * @param brand
   * @param model
   * @param sensorSize
   */
  Datasheet(std::string brand,
            std::string model,
            const double& sensorSize ):
                  _brand(std::move(brand)),
                  _model(std::move(model)),
                  _sensorSize(sensorSize)
  {}

  bool operator==(const Datasheet& ds) const;

  std::string _brand;
  std::string _model;
  double _sensorSize{};
};

} // namespace sensorDB
} // namespace aliceVision
