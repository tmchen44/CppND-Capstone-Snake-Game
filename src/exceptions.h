#include <exception>
#include <filesystem>

// To be raised when a file cannot be opened.
class CannotOpenFileException : public std::exception
{
public:
    CannotOpenFileException(std::filesystem::path &path) : _path(path) {}

    const char *what() const throw()
    {
        std::string
            msg(std::string("File ") + _path.string() + " cannot be opened.");
        return msg.c_str();
    }

private:
    // Path of the file that cannot be opened.
    std::filesystem::path _path;
};

// To be raised when a level file has incorrect dimensions.
class IncorrectLevelDimensionsException : public std::exception
{
public:
    IncorrectLevelDimensionsException(
        std::string dim_name,
        int expected_value,
        int incorrect_value) : dim_name(dim_name), expected_value(expected_value), incorrect_value(incorrect_value) {}

    const char *what() const throw()
    {
        char *msg{0};
        std::sprintf(msg,
                     "Incorrect %s. Expected %i, received %i",
                     dim_name.c_str(), expected_value, incorrect_value);

        return msg;
    }

private:
    std::string dim_name;
    int expected_value;
    int incorrect_value;
};
