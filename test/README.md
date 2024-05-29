# IoT Device Testing

This document outlines the testing strategy and frameworks used for testing an IoT device, which utilized the Unity framework for unit testing and the FFF (Fake Function Framework) for mocking external dependencies. The tests were categorized into two main types: native_tests and target_tests, each designed to evaluate the system's behavior in different environments.

## Contents
1. [Native Tests](#native-tests)
2. [Target Tests](#target-tests)
3. [Manual Testing](#manual-testing)

## Native Tests
Native tests were designed to ensure the expected behavior of higher-level modules such as controllers and states. By using FFF to mock external dependencies for low-level modules (e.g., sensor readings, network communication), these tests provided a controlled testing environment.

- **Execution Environment:** Native tests were run on the Operating System and served as an automated verification during workflow runs, helping to protect the main branch from merging defective code.
- **Code Coverage:** Part of the workflow involved uploading the test coverage artifact to CodeCov. Visual Studio Code extension Gcov Viewer was used to better understand the coverage of the tests, identifying parts of the code that lacked testing.
- **Example:** For instance, the function `alarm_create` had coverage of 73.3% due to missing tests for a single if-statement.

### Unit Tests
Critical components of the code were tested in isolation using unit tests. For example:
- **Parsing Requests:** Testing whether the function could parse correct messages and handle invalid formats (e.g., missing a body or having an unknown action type).

### Integration Tests
Integration tests ensured the different parts of the system worked correctly together. For example:
- **Response Handling:** Testing how the system behaves when a response with the correct time is received.

## Target Tests
Target tests were designed to verify the proper behavior of the code on the Arduino Mega 2560, using a Black Box testing strategy. These tests aimed to verify functionality directly on the device, without mocking any code.

- **Execution Environment:** The tests were conducted directly on the hardware, requiring manual preparation of the physical environment.
- **Example:** Testing the DHT11 humidity and temperature sensor to ensure module functionality. Accuracy was determined by comparing measured data to actual room values.

## Manual Testing
All implemented features were also subjected to manual testing. Due to the slower implementation of backend requirements, minimal end-to-end testing was conducted. To address this, a mocked server created by the application Hercules was used.

- **Example:** Testing if the device behaves correctly when receiving a specified message as documented (e.g., a message "MS|10|Hello mama|" is correctly displayed and the appropriate response is sent to the server).
- **Device-Specific Functionalities:** Such as delaying an alarm by waving in front of an ultrasonic sensor, were manually tested.
- **Documentation:** Specifications of manual tests can be found in the chapter "Device Testing" of Appendix I - System Testing.

