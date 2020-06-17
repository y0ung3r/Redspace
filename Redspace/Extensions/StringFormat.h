#ifndef STRINGFORMAT_H
#define STRINGFORMAT_H

template<typename ... Args>
std::string format(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; 

	if (size <= 0) 
	{ 
		throw std::runtime_error("Error during formatting."); 
	}

	std::unique_ptr<char[]> buffer(new char[size]);
	snprintf(buffer.get(), size, format.c_str(), args ...);

	return std::string(buffer.get(), buffer.get() + size - 1);
}

#endif