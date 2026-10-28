# Fuzzy Logic Solar Panel Condition Controller

Arduino fuzzy-rule prototype combining a light-dependent resistor reading and solar-voltage measurement to produce a relay decision.

## What this repository demonstrates

Analog light input A0; voltage input A1; relay output pin 8; fuzzy membership functions and inference rules.

## Source code

Main example: `FUZZY_LOGIC_MODEL_FOR_DUST_DETECTION_ON_SOLAR_PANELS.ino`.

## How to explore

Clone or download the repository, open the source file, and review its dependencies and hardware or dataset assumptions. Arduino sketches require the appropriate Arduino IDE board and libraries; Python scripts require the imports and referenced datasets; web exercises can be opened or adapted locally.

## Scope and limitations

The code implements a rule-based inference model, not a validated direct dust-concentration measurement. Calibration and controlled clean/dirty-panel experiments are required before making dust-detection performance claims.

## Development notes

This repository is maintained as a learning or engineering prototype. Documented behavior is based on source-code inspection; this documentation does not claim independent hardware testing or performance validation.

## Security

Do not add personal data, private datasets, credentials, or API keys to public commits.
