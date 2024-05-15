make setup-env:
	@echo "Setting up environment..."
	cd ./scripts && chmod +x ./setup_env.sh && ./setup_env.sh

make test-native:
	@echo "Running native tests..."
	chmod +x ./scripts/test_native.sh && ./scripts/test_native.sh