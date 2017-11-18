#ifndef DIMSEXCEPTION_H
#define  DIMSEXCEPTION_H
#include <vector>
#include <sstream>

class DimsException : public std::exception{
    std::vector<std::size_t> dims1;
    std::vector<std::size_t> dims2;
public:
    DimsException(const std::vector<std::size_t>& d1, const std::vector<std::size_t>& d2){
        dims1 = d1;
        dims2 = d2;
    }
    virtual const char* what() const noexcept override{
        std::stringstream msg;
        msg<<"Tensor sizes don't match for this operation: lhs has dimensions {";
        for(std::size_t i = 0;i<dims1.size();i++){
            msg<<dims1[i]<<((i!=dims1.size())?",":"");
        }
        msg<<"}, rhs has dimensions {";
        for(std::size_t i = 0;i<dims2.size();i++){
            msg<<dims2[i]<<((i!=dims2.size())?",":"");
        }
        msg<<"}.";
        return msg.str().c_str();
    }
};

#endif //DIMSEXCEPTION_H
