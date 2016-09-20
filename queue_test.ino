
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
