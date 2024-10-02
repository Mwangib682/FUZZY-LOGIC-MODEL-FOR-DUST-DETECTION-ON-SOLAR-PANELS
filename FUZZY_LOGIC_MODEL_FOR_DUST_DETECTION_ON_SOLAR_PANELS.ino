#include <Fuzzy.h>

// Define pins
const byte LDR_PIN = A0;
const byte VOLTAGE_PIN = A1;
const byte RELAY_PIN = 8;

// Create fuzzy control system
Fuzzy* fuzzy = new Fuzzy();

// Fuzzy sets for light intensity
FuzzySet* lowLight = new FuzzySet(0, 0, 2, 3.5); // Low light (0-3.5V)
FuzzySet* highLight = new FuzzySet(3, 3.5, 4, 4);  // High light (3.5-4V)

// Fuzzy sets for solar voltage
FuzzySet* lowVoltage = new FuzzySet(0, 0, 2.5, 4.5); // Low voltage (0-4.5V)
FuzzySet* highVoltage = new FuzzySet(4, 4.5, 5, 5);  // High voltage (4.5-5V)

// Fuzzy sets for relay control
FuzzySet* relayOn = new FuzzySet(1, 1, 1, 1);  // Relay on
FuzzySet* relayOff = new FuzzySet(0, 0, 0, 0); // Relay off

void setupFuzzy() {
  // Fuzzy input for light intensity
  FuzzyInput* light = new FuzzyInput(1);
  light->addFuzzySet(lowLight);
  light->addFuzzySet(highLight);
  fuzzy->addFuzzyInput(light);

  // Fuzzy input for solar voltage
  FuzzyInput* voltage = new FuzzyInput(2);
  voltage->addFuzzySet(lowVoltage);
  voltage->addFuzzySet(highVoltage);
  fuzzy->addFuzzyInput(voltage);

  // Fuzzy output for relay control
  FuzzyOutput* relay = new FuzzyOutput(1);
  relay->addFuzzySet(relayOn);
  relay->addFuzzySet(relayOff);
  fuzzy->addFuzzyOutput(relay);

  // Fuzzy rules
  FuzzyRuleAntecedent* ifHighLightAndHighVoltage = new FuzzyRuleAntecedent();
  ifHighLightAndHighVoltage->joinWithAND(highLight, highVoltage);
  FuzzyRuleConsequent* thenRelayOff1 = new FuzzyRuleConsequent();
  thenRelayOff1->addOutput(relayOff);
  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifHighLightAndHighVoltage, thenRelayOff1);
  fuzzy->addFuzzyRule(fuzzyRule1);

  FuzzyRuleAntecedent* ifHighLightAndLowVoltage = new FuzzyRuleAntecedent();
  ifHighLightAndLowVoltage->joinWithAND(highLight, lowVoltage);
  FuzzyRuleConsequent* thenRelayOn = new FuzzyRuleConsequent();
  thenRelayOn->addOutput(relayOn);
  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifHighLightAndLowVoltage, thenRelayOn);
  fuzzy->addFuzzyRule(fuzzyRule2);

  FuzzyRuleAntecedent* ifLowLightAndLowVoltage = new FuzzyRuleAntecedent();
  ifLowLightAndLowVoltage->joinWithAND(lowLight, lowVoltage);
  FuzzyRuleConsequent* thenRelayOff2 = new FuzzyRuleConsequent();
  thenRelayOff2->addOutput(relayOff);
  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifLowLightAndLowVoltage, thenRelayOff2);
  fuzzy->addFuzzyRule(fuzzyRule3);

  FuzzyRuleAntecedent* ifLowLightAndHighVoltage = new FuzzyRuleAntecedent();
  ifLowLightAndHighVoltage->joinWithAND(lowLight, highVoltage);
  FuzzyRuleConsequent* thenRelayOff3 = new FuzzyRuleConsequent();
  thenRelayOff3->addOutput(relayOff);
  FuzzyRule* fuzzyRule4 = new FuzzyRule(4, ifLowLightAndHighVoltage, thenRelayOff3);
  fuzzy->addFuzzyRule(fuzzyRule4);
}

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize pin modes
  pinMode(LDR_PIN, INPUT);
  pinMode(VOLTAGE_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Turn off the relay initially
  digitalWrite(RELAY_PIN, LOW);

  // Setup fuzzy logic
  setupFuzzy();
}

void loop() {
  // Read the LDR and voltage values
  float lightIntensity = analogRead(LDR_PIN) * (5.0 / 1023.0); // Convert to 0-5V
  float solarVoltage = analogRead(VOLTAGE_PIN) * (5.0 / 1023.0); // Convert to 0-5V

  // Print values for debugging
  Serial.print("Light Intensity: ");
  Serial.println(lightIntensity);
  Serial.print("Solar Voltage: ");
  Serial.println(solarVoltage);

  // Set fuzzy inputs
  fuzzy->setInput(1, lightIntensity);
  fuzzy->setInput(2, solarVoltage);

  // Execute fuzzy logic
  fuzzy->fuzzify();

  // Get fuzzy output
  float relayState = fuzzy->defuzzify(1);

  // Print fuzzy output for debugging
  Serial.print("Relay State: ");
  Serial.println(relayState);

  // Control relay based on fuzzy output
  if (relayState > 0.5) {
    digitalWrite(RELAY_PIN, HIGH); // Turn on relay
    Serial.println("Relay ON");
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn off relay
    Serial.println("Relay OFF");
  }

  // Small delay to stabilize readings
  delay(1000);

 

