#include "TrafficLight.h"

#include <iostream>
#include <random>

/* Implementation of class "MessageQueue" */

template <typename T>
T MessageQueue<T>::receive() {
  std::unique_lock<std::mutex> lock(_mutex);
  _condition.wait(lock, [this]() { return !_queue.empty(); });
  T message = std::move(_queue.back());
  _queue.pop_back();
  return message;
}

template <typename T>
void MessageQueue<T>::send(T &&msg) {
  std::lock_guard<std::mutex> guard(_mutex);
  _queue.emplace_back(std::move(msg));
  _condition.notify_one();
}

/* Implementation of class "TrafficLight" */

TrafficLight::TrafficLight()
    : _currentPhase(TrafficLightPhase::kRed),
      _uniform_dist(std::uniform_int_distribution<>(4000, 6000)),
      _engine(std::random_device()()) {}

void TrafficLight::waitForGreen() {
  while (true) {
    auto phase = _queue.receive();
    if (phase == TrafficLightPhase::kGreen) return;
  }
}

TrafficLightPhase TrafficLight::getCurrentPhase() { return _currentPhase; }

void TrafficLight::simulate() {
  threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases() {
  auto last = std::chrono::system_clock::now();
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto now = std::chrono::system_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - last)
            .count();
    if (duration >= cycleDurationMillis()) {
      std::lock_guard<std::mutex> guard(_mutex);
      _currentPhase = _currentPhase == TrafficLightPhase::kRed
                          ? TrafficLightPhase::kGreen
                          : TrafficLightPhase::kRed;
      _queue.send(getCurrentPhase());
      last = now;
    }
  }
}
int TrafficLight::cycleDurationMillis() { return _uniform_dist(_engine); }
