#include "TrafficLight.h"

#include <iostream>
#include <random>

/* Implementation of class "MessageQueue" */

/*
template <typename T>
T MessageQueue<T>::receive()
{
    // TODO: FP.5a : The method receive should use std::unique_lock<std::mutex>
and _condition.wait()
    // to wait for and receive new messages and pull them from the queue using
move semantics.
    // The received object should then be returned by the receive function.
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // TODO: FP.4a : The method send should use the mechanisms
std::lock_guard<std::mutex>
    // as well as _condition.notify_one() to add a new message to the queue and
afterwards send a notification.
}
*/

/* Implementation of class "TrafficLight" */

TrafficLight::TrafficLight()
    : _currentPhase(TrafficLightPhase::kRed),
      _uniform_dist(std::uniform_int_distribution<>(4, 6)) {}

void TrafficLight::waitForGreen() {
  // TODO: FP.5b : add the implementation of the method waitForGreen, in which
  // an infinite while-loop runs and repeatedly calls the receive function on
  // the message queue. Once it receives TrafficLightPhase::green, the method
  // returns.
}

TrafficLightPhase TrafficLight::getCurrentPhase() {
  std::lock_guard<std::mutex> guard(_mutex);
  return _currentPhase;
}

void TrafficLight::simulate() {
  threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto cycle_seconds = getRandom();
    std::lock_guard<std::mutex> guard(_mutex);
    _currentPhase = _currentPhase == TrafficLightPhase::kRed
                        ? TrafficLightPhase::kGreen
                        : TrafficLightPhase::kRed;
  }
}
int TrafficLight::getRandom() { return _uniform_dist(_engine); }
