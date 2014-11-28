# Build and run the unit tests (or speed tests) on linux
#
# Should work with recent versions of both gcc and clang.  (To compile with
# clang use "make CXX=clang++".)

CXXFLAGS?=-Wall
CXX11FLAGS?=-std=c++0x

test: tinyformat_test_cxx98 tinyformat_test_cxx11
	@echo running tests...
	@./tinyformat_test_cxx98 && \
		./tinyformat_test_cxx11 && \
		! $(CXX) $(CXXFLAGS) -std=c++98 -DTINYFORMAT_NO_VARIADIC_TEMPLATES \
		-DTEST_WCHAR_T_COMPILE tinyformat_test.cpp 2> /dev/null && \
		echo "No errors" || echo "Tests failed"

doc: tinyformat.html

speed_test: tinyformat_speed_test
	@echo "Running speed tests..."
	@echo 
	@echo "*** printf ***"
	@time -p ./tinyformat_speed_test std::printf > /dev/null
	@echo 
	@echo "*** iostreams ***"
	@time -p ./tinyformat_speed_test std::iostreams > /dev/null
	@echo 
	@echo "*** tinyformat ***"
	@time -p ./tinyformat_speed_test tinyformat > /dev/null
	@echo 
	# @echo "*** boost ***"
	# @time -p ./tinyformat_speed_test boost::format > /dev/null
	@echo 
	@echo "*** xlib::core::String::format ***"
	@time -p ./tinyformat_speed_test xlib::core::String::format > /dev/null
	@echo 
	@echo "*** xlib::Format ***"
	@time -p ./tinyformat_speed_test xlib::Format > /dev/null	
	@echo 	
	@echo "\n"

tinyformat_test_cxx98: tinyformat.h tinyformat_test.cpp Makefile
	$(CXX) $(CXXFLAGS) -std=c++98 -DTINYFORMAT_NO_VARIADIC_TEMPLATES tinyformat_test.cpp -o tinyformat_test_cxx98

tinyformat_test_cxx11: tinyformat.h tinyformat_test.cpp Makefile
	$(CXX) $(CXXFLAGS) $(CXX11FLAGS) -DTINYFORMAT_USE_VARIADIC_TEMPLATES tinyformat_test.cpp -o tinyformat_test_cxx11

tinyformat.html: README.rst
	@echo building docs...
	rst2html.py README.rst > tinyformat.html

tinyformat_speed_test: tinyformat.h tinyformat_speed_test.cpp Makefile
	$(CXX) $(CXXFLAGS) -O3 -DNDEBUG tinyformat_speed_test.cpp -o tinyformat_speed_test -ldl

bloat_test:
	@for opt in '' '-O3 -DNDEBUG' ; do \
		for use in '' '-DUSE_IOSTREAMS' '-DUSE_TINYFORMAT' '-DUSE_TINYFORMAT $(CXX11FLAGS)' '-DUSE_BOOST' ; do \
			echo ; \
			echo ./bloat_test.sh $(CXX) $$opt $$use ; \
			./bloat_test.sh $(CXX) $$opt $$use ; \
		done ; \
	done


clean:
	rm -f tinyformat_test_cxx98 tinyformat_test_cxx11 tinyformat_speed_test
	rm -f tinyformat.html
	rm -f _bloat_test_tmp_*
