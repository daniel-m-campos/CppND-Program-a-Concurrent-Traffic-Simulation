#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <condition_variable>
#include <deque>
#include <mutex>
#include <random>

#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

// TODO: FP.3 Define a class „MessageQueue“ which has the public methods send
// and receive. Send should take an rvalue reference of type TrafficLightPhase
// whereas receive should return this type. Also, the class should define an
// std::dequeue called _queue, which stores objects of type TrafficLightPhase.
// Also, there should be an std::condition_variable as well as an std::mutex as
// private members.

template <class T>
class MessageQueue {
 public:
 private:
};

enum class TrafficLightPhase {
  kRed,
  kGreen,
};

class TrafficLight : public TrafficObject {
 public:
  TrafficLight();
  void waitForGreen();
  void simulate() override;
  TrafficLightPhase getCurrentPhase();

 private:
  void cycleThroughPhases();
  int getRandom();
  std::default_random_engine _engine;
  std::uniform_int_distribution<> _uniform_dist;

  // TODO: FP.4b : create a private member of type MessageQueue for messages
  // of type TrafficLightPhase and use it within the infinite loop to push
  // each new TrafficLightPhase into it by calling send in conjunction with
  // move semantics.

  std::condition_variable _condition;
  std::mutex _mutex;
  TrafficLightPhase _currentPhase;
};

#endif