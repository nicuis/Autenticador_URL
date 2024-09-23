#ifndef URL_VALIDATOR_HPP
#define URL_VALIDATOR_HPP

class url_validator {
    private:
        url_validator() = delete;
        ~url_validator() = delete;

    public:
        static void validate(std::string&& url);
};

#endif