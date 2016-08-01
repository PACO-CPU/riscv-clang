#ifndef PACO_H
#define PACO_H

#include <string>

namespace PACO {
  //Keyword for Pragmas
  //Sadly, II.isStr requires a string literal and no const char*, so for changes look in ParsePragma.cpp as well
  const std::string KV_PRAGMA_PACO = "paco";
  const std::string KV_PRAGMA_COMBINE = "combine";
  const std::string KV_PRAGMA_COMBINE_LEAST_PRECISE = "least_precise";
  const std::string KV_PRAGMA_COMBINE_MOST_PRECISE = "most_precise";
  const std::string KV_PRAGMA_COMBINE_ERROR = "error";
  const std::string KV_PRAGMA_INTERMEDIATE_LITERAL = "intermediate_literal";
  const std::string KV_PRAGMA_INTERMEDIATE_LITERAL_PRECISE = "precise";
  const std::string KV_PRAGMA_INTERMEDIATE_LITERAL_MIMIC = "mimic";
  //Keywords for Approx ALU
  const std::string KV_NEGLECT_AMOUNT = "neglect_amount";
  const std::string KV_MASK = "mask"; 
  const std::string KV_INJECT = "inject"; 
  const std::string KV_RELAX = "relax"; 
  const unsigned APPROX_PRECISE = 0x07F;
  const unsigned APPROX_LVL_2 = 0x07E;
  const unsigned APPROX_LVL_4 = 0x07C;
  const unsigned APPROX_LVL_7 = 0x078;
  const unsigned APPROX_LVL_10 = 0x070;
  const unsigned APPROX_LVL_15 = 0x060;
  const unsigned APPROX_LVL_20 = 0x040;
  const unsigned APPROX_LVL_27 = 0x000;
  //Keyword for LUT
  const std::string KV_APPROXIMATION = "approximation"; 
  const std::string KV_STRATEGY = "strategy";
  const std::string KV_NUM_SEGMENTS = "numSegments";
  const std::string KV_BOUNDS = "bounds";
  const std::string KV_SEGMENTS = "segments";
  const std::string KV_UNIFORM = "uniform";
  const std::string KV_LOG_LEFT = "log_left";
  const std::string KV_LOG_RIGHT = "log_right";
  const std::string KV_MIN_ERROR = "min_error";
  const std::string KV_MIN_ERROR_GAIN = "min_error_gain";
  const std::string KV_EXPLICIT_SEGMENTS = "explicit_segments";
}

#endif
