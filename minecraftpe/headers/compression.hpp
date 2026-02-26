#pragma once
#include <string>

namespace compression {
	namespace gzip {
		bool decompress(const std::string&, const std::string&);
		int decompress(FILE*, FILE*);

		bool compress(const std::string&, const std::string&, int);
		int compress(FILE*, FILE*, int);
	}
}
