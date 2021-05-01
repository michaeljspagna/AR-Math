#ifndef ERROR_HPP
    #define ERROR_HPP

    #include<string>

	namespace Error{
		auto throw_error(const std::string&) -> void;
	}
    
#endif /* ERROR_HPP */