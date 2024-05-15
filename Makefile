setup-env:
	@echo "Setting up environment..."
	chmod +x ./scripts/setup_env.sh
	./scripts/setup_env.sh

test-native:
	@echo "Running native tests..."
	chmod +x ./scripts/test_native.sh
	./scripts/test_native.sh