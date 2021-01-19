CC=gcc
CFLAGS=-I/src/include

TESTTEMPFOLDER=tmp-test

.PHONY: help

sqlDocExtractor: src/main.c ## build the project
	mkdir -p dist
	$(CC) $(CFLAGS) src/include/custom-types.c src/main.c -o dist/sqlDocExtractor

help:
	@echo
	@echo "make targets :"
	@echo
	@grep -E '(^[a-zA-Z_-]+:.*?##.*$$)|(^##)' $(MAKEFILE_LIST) \
	| awk 'BEGIN {FS = ":.*?## "}; {printf "\033[32m%-30s\033[0m %s\n", $$1, $$2}' \
	| sed -e 's/\[32m##/[33m/'
	@echo

test: sqlDocExtractor test/* ## run unit tests
	mkdir -p $(TESTTEMPFOLDER)
	for test_dir in $(shell ls test); do \
		./dist/sqlDocExtractor test/$${test_dir}/test-file.sql > $(TESTTEMPFOLDER)/$${test_dir}.json ; \
		diff test/$${test_dir}/expected-output.json $(TESTTEMPFOLDER)/$${test_dir}.json || echo "\nFAIL: $${test_dir}\n" ; \
	done

clean: ## remove output files
	rm -r dist/ $(TESTTEMPFOLDER)