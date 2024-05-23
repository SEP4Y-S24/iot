echo "Running all native tests..."

echo "Running wifi_connect_state test..."
pio test -e native_test -f "native_tests/test_native_wifi_connect_state"

echo "Running ccp_protocol test..."
pio test -e native_test -f "native_tests/test_native_ccp_protocol"

echo "Running alarm test..."
pio test -e native_test -f "native_tests/test_native_alarm"

echo "Running message_handler test..."
pio test -e native_test -f "native_tests/test_native_message_handler"

echo "Running periodic_request test..."
pio test -e native_test -f "native_tests/test_native_periodic_request"

echo "Running humidity_temperature test..."
pio test -e native_test -f "native_tests/test_native_humidity_temperature"

echo "Running auth_test test..."
pio test -e native_test -f "native_tests/test_native_auth_state"

echo "Running encryption test..."
pio test -e native_test_encryption -f "native_tests/test_native_cryptator"