/*************************************************************************************************
 * Tests for tkrzw_logger.h
 *
 * Copyright 2020 Google LLC
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License.  You may obtain a copy of the License at
 *     https://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software distributed under the
 * License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.  See the License for the specific language governing permissions
 * and limitations under the License.
 *************************************************************************************************/

#include "tkrzw_sys_config.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "tkrzw_lib_common.h"
#include "tkrzw_logger.h"
#include "tkrzw_str_util.h"

using namespace testing;

// Main routine
int main(int argc, char** argv) {
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(LoggerTest, LoggerBase) {
  std::stringstream output;
  tkrzw::StreamLogger logger(&output);
  logger.Log(tkrzw::Logger::DEBUG, "debug");
  logger.Log(tkrzw::Logger::INFO, "info");
  logger.Log(tkrzw::Logger::WARN, "warn");
  logger.LogF(tkrzw::Logger::ERROR, "error: %d", 123);
  logger.LogF(tkrzw::Logger::FATAL, "fatal: %s", "hello");
  EXPECT_EQ(std::string::npos, output.str().find(" [DEBUG] debug"));
  EXPECT_NE(std::string::npos, output.str().find(" [INFO] info"));
  EXPECT_NE(std::string::npos, output.str().find(" [WARN] warn"));
  EXPECT_NE(std::string::npos, output.str().find(" [ERROR] error: 123"));
  EXPECT_NE(std::string::npos, output.str().find(" [FATAL] fatal: hello"));
  output.str("");
  logger.SetMinLevel(tkrzw::Logger::ERROR);
  logger.SetSeparator(" | ");
  logger.Log(tkrzw::Logger::DEBUG, "debug");
  logger.Log(tkrzw::Logger::INFO, "info");
  logger.Log(tkrzw::Logger::WARN, "warn");
  logger.LogF(tkrzw::Logger::ERROR, "error: %d", 123);
  logger.LogF(tkrzw::Logger::FATAL, "fatal: %s", "hello");
  EXPECT_EQ(std::string::npos, output.str().find(" | [DEBUG] | debug"));
  EXPECT_EQ(std::string::npos, output.str().find(" | [INFO] | info"));
  EXPECT_EQ(std::string::npos, output.str().find(" | [WARN] | warn"));
  EXPECT_NE(std::string::npos, output.str().find(" | [ERROR] | error: 123"));
  EXPECT_NE(std::string::npos, output.str().find(" | [FATAL] | fatal: hello"));
}

// END OF FILE
