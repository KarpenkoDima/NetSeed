# Makefile
.PHONY: all clean test test-memory test-raw coverage

all:
	mkdir -p build
	cd build && cmake .. && make

clean:
	rm -rf build

test: all
	cd build && ctest --output-on-failure

test-memory: all
	cd build && ./sprouts/tests/memory/test_mbuf

#test-raw: all
#	cd build && ./sprouts/tests/raw/test_raw

coverage:
	mkdir -p build
	cd build && cmake -DENABLE_COVERAGE=ON .. && make
	cd build && ctest
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report