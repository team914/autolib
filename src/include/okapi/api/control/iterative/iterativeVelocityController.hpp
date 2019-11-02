/*
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

#include "okapi/api/control/iterative/iterativeController.hpp"

namespace okapi {
template <typename Input, typename Output>
class IterativeVelocityController : public IterativeController<Input, Output> {};
} // namespace okapi
