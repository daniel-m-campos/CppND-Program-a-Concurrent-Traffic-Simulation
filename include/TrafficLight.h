#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <condition_variable>
#include <deque>
#include <mutex>
#include <random>

#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

template <class T>
class MessageQueue {
 public:
  void send(T&&);
  T receive();

 private:
  std::deque<T> _queue;
  std::mutex _mutex;
  std::condition_variable _condition_variable;
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
  std::mt19937_64 _engine;
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