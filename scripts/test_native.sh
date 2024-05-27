echo "Running all native tests..."

echo "Running wifi_connect_state test..."
pio test -e native_test_wifi_connect_state -f "./test/native_tests"

echo "Running ccp_protocol test..."
pio test -e native_test_ccp_protocol -f "./test/native_tests"

echo "Running alarm test..."
pio test -e native_test_alarm -f "./test/native_tests"

echo "Running message_handler test..."
pio test -e native_test_message_handler -f "./test/native_tests"

echo "Running periodic_request test..."
pio test -e native_test_periodic_request -f "./test/native_tests"

echo "Running humidity_temperature test..."
pio test -e native_test_humidity_temperature -f "./test/native_tests"

echo "Running auth_test test..."
pio test -e native_test_auth_state -f "./test/native_tests"

echo "Running encryption test..."
pio test -e native_test_cryptorator -f "./test/native_tests"