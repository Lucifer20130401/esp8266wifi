A :=$(abspath $(lastword $(MAKEFILE_LIST)))
B :=$(abspath $(firstword $(MAKEFILE_LIST)))
C :=$(abspath $(MAKEFILE_LIST))
D :=$(abspath $(dir $(MAKEFILE_LIST)))
BB:
	@echo "A=$(A)"
	@echo "B=$(B)"
	@echo "C=$(C)"
	@echo "D=$(D)"