echo "Running all tests..."

echo "Running wifi_connect_state test..."
pio test -e test_wifi_connect_state -d ".." -f "test/"
echo "Running ccp_protocol test..."
pio test -e test_ccp_protocol -d ".." -f "test/"