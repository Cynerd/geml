# vim:ts=4:sw=4:noexpandtab

.PHONY: help-test
help-test::
	@echo "General extendable macro language make test targets:"
	@echo " tests       - Executes all tests"
	@echo " help-test   - Prits help for all implemented tests"
	@echo " cppcheck    - Executes cppcheck on all compilled sources"

.PHONY: tests
tests: cppcheck

.PHONY:
cppcheck: $(CSRC)
	@echo " CPPCHECK"
	$(Q)$(CPPCHECK) --enable=all --std=c11 --error-exitcode=1 $(CSRC)
