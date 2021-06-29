#include <ArduinoUnitTests.h>
#include "../Queue.h"

int testSize = 4; // number of elements we'll use in our test queues

unittest(empty)
{
  Queue<int> queue(testSize);
  assertEqual(0, queue.count()); // initially empty
  assertEqual(0, queue.peek());  // 0 happens to be the default int val
  assertEqual(0, queue.pop());
  assertEqual(0, queue.count()); // still empty
}

unittest(filling_and_emptying)
{
  Queue<int> queue(testSize);
  assertEqual(0,        queue.count()); // initially empty
  for (int i = 1; i <= testSize; ++i) {
    queue.push(i * 11);
    assertEqual(i,            queue.count());  // count increases with pushes
  }
  for (int i = 1; i <= testSize; ++i) {
    assertEqual(i * 11,           queue.peek());  // verify FIFO
    assertEqual(testSize + 1 - i, queue.count()); // verify count unchanged
    assertEqual(i * 11,           queue.pop());   // verify FIFO
    assertEqual(testSize - i,     queue.count()); // verify count changed
  }
}

unittest(filling_and_clearing)
{
  Queue<int> queue(testSize);
  assertEqual(0, queue.count()); // initially empty
  for (int i = 1; i <= testSize; ++i) {
    queue.push(i * 11);
    assertEqual(i, queue.count());      // count increases with pushes
  }
  assertEqual(testSize, queue.count()); // now full
  queue.clear();
  assertEqual(0,        queue.count()); // again empty
}

unittest(overfilling)
{
  Queue<int> queue(testSize);
  assertEqual(0,        queue.count()); // initially empty
  for (int i = 1; i <= testSize; ++i) {
    queue.push(i * 11);
  }
  assertEqual(testSize, queue.count()); // now full
  for (int i = (testSize + 1); i <= testSize * 2; ++i) {
    queue.push(i * 11);
    assertEqual(testSize, queue.count()); // still full
  }

  for (int i = 1; i <= testSize; ++i) {
    assertEqual(i * 11,           queue.peek());  // verify FIFO
    assertEqual(testSize + 1 - i, queue.count()); // verify count unchanged
    assertEqual(i * 11,           queue.pop());   // verify FIFO
    assertEqual(testSize - i,     queue.count()); // verify count changed
  }
}

unittest(wrapping)
{
  Queue<int> queue(testSize);
  queue.push(0); // offset the queue so we have to wrap around
  queue.push(1);
  queue.pop();
  queue.pop();

  for (int i = 1; i <= testSize; ++i) {
    queue.push(i * 11);
  }
  assertEqual(testSize, queue.count()); // now full
  for (int i = (testSize + 1); i <= testSize * 2; ++i) {
    queue.push(i * 11);
    assertEqual(testSize, queue.count()); // still full
  }

  for (int i = 1; i <= testSize; ++i) {
    assertEqual(i * 11,           queue.peek());  // verify FIFO
    assertEqual(testSize + 1 - i, queue.count()); // verify count unchanged
    assertEqual(i * 11,           queue.pop());   // verify FIFO
    assertEqual(testSize - i,     queue.count()); // verify count changed
  }
}

unittest_main()
