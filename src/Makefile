SHELL := /bin/bash

COMPILER=gcc
OUTPUT_FILENAME=out
OPTIMISATION=3
DETAILED=true
LIBRARIES="Data Types/string.c" "Data Types/bigint.c"

debug:
ifeq ($(DETAILED), true)
	@time $(COMPILER) main.c $(LIBRARIES) -O0 -o $(OUTPUT_FILENAME)
	@echo
	@du -h $(OUTPUT_FILENAME)
else
	$(COMPILER) main.c $(LIBRARIES) -O0 -o $(OUTPUT_FILENAME)
endif
	@echo

	@./$(OUTPUT_FILENAME)

optimised:
ifeq ($(DETAILED), true)
	@time $(COMPILER) main.c $(LIBRARIES) -O$(OPTIMISATION) -o $(OUTPUT_FILENAME)
	@echo
	@du -h $(OUTPUT_FILENAME)
else
	@$(COMPILER) main.c $(LIBRARIES) -O$(OPTIMISATION) -o $(OUTPUT_FILENAME)
endif

	@echo

	@./$(OUTPUT_FILENAME)

clean:
	rm $(OUTPUT_FILENAME)
