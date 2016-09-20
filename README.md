# Queue.h

Generic C++ circular queue for Arduino embedded projects.

## Constructor

### `Queue<T> queue = Queue(int maxlength = 100);`

Creates a queue of a generic type `T` with a maximum queue size. If `maxlength` is not defined it will default to 100.

NOTE: If the queue grows to `maxlength` items (and you dont take them out) any additional items added *will drop out of the queue*.
Please bear this in mind when defining maxlength so it is a reasonable balance between RAM usage and functional usefulness.

**Examples**

```cpp
Queue<byte> queue = Queue(1000); // Queue of max 1000 bytes
Queue<int> queue = Queue(); // Queue of max 100 int
Queue<char> queue = Queue(260); // Queue of max 260 chars
Queue<Point> queue = Queue(10); // Queue of max 10 'Point', where 'Point' is a struct 
Queue<String> queue = Queue(); // Queue of max 100 'String', where 'String' is a class
```

## Methods

### `queue.push(T item);`

Adds a generic item (of `T` type) at the back of the queue.

**Example**

```cpp
Queue<byte> queue = Queue();
byte a = 255;
byte b = 0;
queue.push(a);
queue.push(b);
```

### `T item = queue.pop();`

Gets a generic item (of `T` type) from the front of the queue.

**Example**

```cpp
Queue<byte> queue = Queue(); 
byte a = 255;
byte b = 0;
queue.push(a);
queue.push(b);
assert(a == queue.pop()); // true
assert(b == queue.pop()); // true
```

### `int front = queue.front();`

Gets the current position in the front of the queue. Used for testing queue logic.

**Example**

```cpp
Queue<byte> queue = Queue(); 
byte a = 255;
byte b = 0;
queue.push(a);
assert(1 == queue.front()); // true
queue.push(b);
assert(2 == queue.front()); // true
```

### `int back = queue.back();`

Gets the current position at the back of the queue. Used for testing queue logic.

**Example**

```cpp
Queue<byte> queue = Queue(); 
byte a = 255;
byte b = 0;
queue.push(a);
assert(0 == queue.back()); // true
assert(1 == queue.front()); // true
queue.pop();
assert(1 == queue.back()); // true
assert(1 == queue.front()); // true
```

## All Together now

The following example is testable using 'Serial Monitor' over USB connection from Arduino IDE.

Make sure you set the `baud rate` to 115200 and `No new line`.

```cpp
#include "Queue.h":

Queue<char> queue(5); // Max 5 chars!

void setup() {
  Serial.begin(115200);
}

void loop() {
  while(Serial.available()) {
    queue.push(Serial.read());
  }

  Serial.print(millis() / 1000);
  Serial.print(": ");
  int count = queue.count();
  if (count > 0) {
    Serial.print("Found ");
    Serial.print(count);
    Serial.print(" items.. '");
    Serial.print(queue.pop());
    Serial.print("' is the oldest. We are ");
    Serial.print(queue.front());
    Serial.print(" in front and ");
    Serial.print(queue.back());
    Serial.print(" in back. Next is.. '");
    Serial.print(queue.pop(true));
    Serial.println("'.");
  } else {
    Serial.println("Nothing to process..."); 
  }
  delay(2000);
}
```
