Testing of the IoT Device utilized the Unity framework for unit testing and the FFF (Fake Function Framework) for mocking external dependencies. Tests were separated into two main categories - native_tests & target_test, which aimed to test the behavior of the system in different environments. 
Native Tests
The purpose of native tests was to ensure the expected behavior of the higher-level modules such as controllers and states. Using FFF to mock external dependencies for the low-level modules (e.g. sensor readings, network communication) during unit tests, provided a controlled testing environment. 
Native tests were run on the Operating System and served as an automated verification during workflow runs. This process helped protect the main branch from merging defective code, additionally, a part of the workflow involved uploading the test coverage artifact to CodeCov.
Visual Studio Code extension Gcov Viewer was used to better understand the coverage of the tests. Enabling this tool uncovered parts lacking testing. An example of the usage can be seen on the function alarm_create, the provided overview shows the coverage is 73.3% due to missing test for a single if-statement.

Usage of test coverage. The green background shows the lines of code that were tested.

To ensure that critical components of the code behave correctly even in various edge cases, they were tested in isolation using unit tests. One of those components was a function for parsing requests.  

Besides testing whether the function is capable of parsing correct messages, it also tested how the function behaves if a message is in invalid format eg. missing a body, or having an unknown action type.

To ensure that the different parts of the system work correctly together integration tests were written. For example: it was tested how the system behaves when a response with the correct time is received. 

This test ensures that the system is capable of correctly parsing the message, recognizing that it is a TM response and that a function to set the time into ds3231 is called with correct arguments. 
Target Tests
Target tests were created to ensure the proper behavior of the code on the Arduino Mega 2560. The tests were written using the Black Box testing strategy.
The target tests aimed to verify functionality directly on the device. Therefore, no code was mocked during target tests. The biggest advantage of target tests is the possibility of testing the drivers. Checking the actions of the given hardware in the surrounding environment was an important step to ensure the quality of the system. However, the tests still require a manual preparation of the physical environment where the device was run. Due to this attribute, a smaller amount of them was written compared to native tests.
The following test example involves accessing the DHT11 humidity and temperature sensor. The test ensures that the module works. However, to determine the accuracy of the measurements it is required to compare the measured data to the actual values experienced in the room.

Manual Testing 
All implemented features were also tested manually. Due to a slower implementation of requirements in the backend, very little end-to-end testing was conducted. To compensate for this the device was tested using a mocked server created by an application called Hercules. 
It was tested whether the device behaved correctly when a message was received as specified in the documentation (Appendix G - Communication). Those tests were done to ensure easier future integration with the cloud server. Example:  A message is correctly displayed on the screen and a correct response is sent to the server when a request “MS|10|Hello mama|”  is received.
Device-specific functionalities like delaying an alarm by waving in front of an ultrasonic sensor were manually tested.
Specification of manual tests can be found in the chapter Device Testing of Appendix I - System Testing.

