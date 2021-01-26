#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include "TrafficLight.h"

TEST_CASE("TrafficLight Tests", "[TrafficLightTests]"){
  SECTION("Test Constructor"){
    TrafficLight traffic_light;
  }
}