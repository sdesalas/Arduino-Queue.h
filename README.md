# Queue.h

Generic C++ circular queue for Arduino embedded projects.

## Constructor

### `Queue<T> queue = Queue(int maxlength);`

Creates a queue of a generic type `T` with a specific maximum queue size. 

NOTE: If the queue grows to `maxlength` items (and you dont take them out) any additional items added *will drop out of the queue*.
Please bear this in mind when defining maxlength so it is a reasonable balance between RAM usage and functional usefulness.

**Examples**

```
Queue<byte> queue = Queue(int maxlength); // Queue of byte
Queue<int> queue = Queue(int maxlength);` // Queue of int
Queue<char> queue = Queue(int maxlength);` // Queue of char
Queue<Point> queue = Queue(int maxlength); // Queue of 'Point', where 'Point' is an Enum 
Queue<String> queue = Queue(int maxlength); // Queue of 'String', where 'String' is a Class
```

## Methods

### `queue.push(T item);`

Adds a generic item (of `T` type) at the back of the queue.

**Example**

```
Queue<byte> queue = Queue(int maxlength);
byte a = 255;
byte b = 0;
queue.push(a);
queue.push(b);
```

### `T item = queue.pop();`

Gets a generic item (of `T` type) from the front of the queue.

**Example**

```
Queue<byte> queue = Queue(int maxlength); 
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

```
Queue<byte> queue = Queue(int maxlength); 
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

```
Queue<byte> queue = Queue(int maxlength); 
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

```cpp
#include "Queue.h":

Queue<char> queue(5);

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
